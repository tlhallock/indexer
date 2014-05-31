/*
 * Indexer.cc
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "export.h"











void TmpIndexedFile::free_mem()
{
	auto oend = orders.end();
	for (auto it = orders.begin(); it != oend; ++it)
	{
		delete *it;
	}
	auto wend = words.end();
	for (auto it = words.begin(); it != wend; ++it)
	{
		delete it->first;
	}

	words.clear();
	orders.clear();
}





class TmpIndexedFile
{
public:
	TmpIndexedFile(IndexedFile f);
	virtual ~TmpIndexedFile();

	void append(const char *token)
	{

	}

	void save() const
	{
		auto wend = words.end();
		for (auto wit = words.begin(); wit != wend; ++wit)
		{
			const char *key = wit->first;
			char *key_file = get_file_or_dir(file_dir, key, false);
			if (key_file == nullptr)
			{
				puts("Failure 510975610356");
				continue;
			}

			DataOutputStream out(key_file);
			if (!out.successful())
			{
				std::cout << "Unable to open " << key_file << " for writing\n";
				continue;
			}
			free(key_file);

			std::set<int> &s = *orders.at(wit->second);

			out.write(key);
			out.write((int) s.size());

			auto send = s.end();
			for(auto sit = s.begin(); sit != send; ++sit)
			{
				int offset = *sit;
				out.write(offset);
			}
		}

		{
			char *index_file = (char *) malloc (strlen (file_dir) + 1 + 5 + 1);
			sprintf(index_file, "%s/index", file_dir);

			DataOutputStream o(index_file);
			o.write(path);
	//		o.write(last_indexed_time);

			free(index_file);
		}

		free((void *) file_dir);
	}

	time_t get_last_indexed_time() const;

	bool needs_reindex() const;
private:
	void free_mem();
	IndexedFile *file;
	time_t read_time;

	int current_tokens;
	std::map<const char *, int> words;
	std::vector<std::set<int>*> orders;
};

void index(file_id file)
{
//	fprintf(stdout, "Indexing %s\n", get_file_manager().get_location(file));

	Tokenizer t{file};

	WordManager &wmanager = get_word_manager();

	TmpIndexedFile ifile(file);
	if (!ifile.needs_reindex())
	{
		return;
	}

	ifile.clear();

	const char *token = NULL;
	while ((token = t.next()) != NULL)
	{
//		if (token[0] == 'f' && token[1] == 'o' && token[2] == 'o' && token[3] == '\0')
//		{
//			printf("File %d contains '%s'\n", file, token);
//		}
		wmanager.register_entry(token, file);
		ifile.append(token);
	}

	ifile.save();
}

static void index_function(int len, const char *path)
{
	index(get_file_manager().get_id(path));
}

void index_all(const char *directory)
{
	recurse_all_children(directory, &index_function);
}
