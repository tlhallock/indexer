/*
 * includer.cc
 *
 *  Created on: May 27, 2014
 *      Author: thallock
 */


#include <set>
#include <map>
#include <iostream>
#include <string>

#include <boost/regex.hpp>

#include <cstring>

#include <stdio.h>
#include <sys/stat.h>

#define INCLUDE_REGEX "#include *\"(.*)\""
#define FIND_FILE "/work/file_lists.txt"
#define MAX_PATH_LENGTH 256

struct ConstCharComparator
{
   bool operator()(const char * A, const char * B) const
   {
      return strcmp(A, B) < 0;
   }
};
class UnresolvedInclude;

static std::set<const char*, ConstCharComparator> include_paths;
static std::vector<UnresolvedInclude *> cfiles;
static boost::regex include_expression (INCLUDE_REGEX);

static bool is_resolved(const char *include)
{
	struct stat buffer;

	auto end = include_paths.begin();
	for (auto it = include_paths.begin(); it != end; ++it)
	{
		char buff[MAX_PATH_LENGTH];
		sprintf(buff, "%s/%s", *it, include);
		if (stat(buff, &buffer) == 0)
		{
			return true;
		}
	}
	return false;
}

class UnresolvedInclude
{
public:
	UnresolvedInclude(const char *cfile) :
		original_len(strlen(cfile)),
		original(cfile),
		needed() {}
	~UnresolvedInclude() {}

	void includes(const char *str)
	{
		if (is_resolved(str))
		{
			puts("(resolved)");
			return;
		}

		puts("(unresolved)");
		needed.insert(std::pair<const char *, std::string *>(str, nullptr));
	}

	void offer(const char *file, int len)
	{
		auto end = needed.end();
		for (auto it = needed.begin(); it != end; ++it)
		{
			update_best(file, len, it);
		}
	}

	int size()
	{
		return needed.size();
	}

	void dump(std::set<const char*, ConstCharComparator> &extras)
	{
		auto end = needed.end();
		for (auto it = needed.begin(); it != end; ++it)
		{

			char *path = strdup(it->second->c_str());
			*strrchr(path, '/') = '\0';
			extras.insert(path);
		}
	}
private:
	void update_best(const char *file, int len, std::map<const char*, std::string *, ConstCharComparator>::iterator &it)
	{
		if (!satisfies(file, len, it->first))
		{
			return;
		}
		std::cout << "Can resolve " << it->first << " with " << file << std::endl;
		if (!is_preferrable(file, len, it->second))
		{
			return;
		}
		if (it->second != nullptr)
		{
			delete it->second;
		}

		it->second = new std::string(file);
	}

	bool satisfies(const char *alt, int altlen, const std::string &include) const
	{
		if (altlen <= (int) include.length())
		{
			return false;
		}

		int len = include.length();
		for (int i=1; i<=len; i++)
		{
			if (alt[altlen - i] != include.at(len - i))
			{
				return false;
			}
		}
		return alt[altlen - len - 1] == '/';
	}

	bool is_preferrable(const char *alt, int altlen, std::string *current_best) const
	{
		if (current_best == nullptr)
		{
			return true;
		}

		for (int i=0; i<original_len; i++)
		{
			bool a = alt[i] == original[i];
			bool c = current_best->at(i) == original[i];
			if (a && c)
			{
				continue;
			}

			return a && !c;
		}

		return false;
	}

	int original_len;
	const char *original;
	std::map<const char*, std::string *, ConstCharComparator> needed;
};

static void fill_include_paths(int argc, char **argv)
{
	for (int i=0; i<argc; i++)
	{
		if (argv[i][0] != '-')
		{
			continue;
		}
		if (argv[i][1] != 'I')
		{
			continue;
		}

		const char *path;
		if (argv[i][2] == '\0')
		{
			path = argv[++i];
		}
		else
		{
			path = argv[i] + 2;
		}

		include_paths.insert(path);
		printf("Include path: %s\n", path);
	}
}

static void fill_needed(FILE *input_stream, const char *cfile)
{
	UnresolvedInclude *include = new UnresolvedInclude(cfile);

	size_t size = 0;
	char *line = nullptr;

	while (getline(&line, &size, input_stream) >= 0)
	{
		boost::smatch cm;
		std::string s(line);

		if (!boost::regex_search(s, cm, include_expression))
		{
			continue;
		}

		std::string str(cm[1]);

		std::cout << "Found include " << str << std::endl;
		include->includes(str.c_str());
	}

	if (include->size() == 0)
	{
		delete include;
	}
	else
	{
		cfiles.push_back(include);
	}

	free(line);
}

static void get_c_files(int argc, char **argv)
{
	for (int i=1; i<argc; i++)
	{
		if (argv[i][0] == '-')
		{
			if (argv[i][1] == 'o')
			{
				i++;
			}
			else if ((argv[i][1] == 'I' || argv[i][1] == 'L')
					&& argv[i][2] == '\0')
			{
				i++;
			}
			continue;
		}

		FILE *f = fopen(argv[i], "r");
		if (f == NULL)
		{
			continue;
		}

		fill_needed(f, argv[i]);
		fclose(f);
	}
}

static void find_needed()
{
	if (cfiles.size() == 0)
	{
		return;
	}

	size_t size = 0;
	char *line = nullptr;

	FILE *in = fopen(FIND_FILE, "r");
	while (getline(&line, &size, in) >= 0)
	{
		int len = strlen(line);
		line[--len] = '\0'; // cut-off new line
		auto end = cfiles.end();
		for (auto it = cfiles.begin(); it != end; ++it)
		{
			(*it)->offer(line, len);
		}
	}
	fclose(in);

	free(line);
}

static void print_extras()
{
	std::set<const char*, ConstCharComparator> extras;

	auto end = cfiles.end();
	for (auto it = cfiles.begin(); it != end; ++it)
	{
		(*it)->dump(extras);
	}

	auto oend = extras.end();
	for (auto it = extras.begin(); it != oend; ++it)
	{
		std::cout << "-I" << *it << std::endl;
	}
}

int main(int argc, char **argv)
{
	argc = 8;
	argv = (char **) malloc (sizeof (*argv) * argc);
	argv[0] = (char *) "g++";
	argv[1] = (char *) "-c";
	argv[2] = (char *) "foo.c";
	argv[3] = (char *) "-I";
	argv[4] = (char *) "/some/dir";
	argv[5] = (char *) "-Ianother_dir";
	argv[6] = (char *) "-o";
	argv[7] = (char *) "a.out";

	fill_include_paths(argc, argv);
	get_c_files(argc, argv);
	if (cfiles.size() == 0)
	{
		return 0;
	}
	find_needed();
	print_extras();
}

