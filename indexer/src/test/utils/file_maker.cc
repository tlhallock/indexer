
#include "export.h"

static bool contains(const char *string, std::set<std::string> *nosubs)
{
	if (nosubs == nullptr)
	{
		return false;
	}

	auto end = nosubs->end();
	for (auto it = nosubs->begin(); it != end; ++it)
	{
		if (it->find(string) != std::string::npos)
		{
			return true;
		}
	}

	return false;
}

void write_delims(FILE* out, int num, const char* ignore, std::set<std::string>* nosubs)
{
	char *ptr = nullptr;

	do
	{
		if (ptr != nullptr)
		{
			free(ptr);
		}
		ptr = create_random_delim_string(num, ignore);
	} while (contains(ptr, nosubs));

	for (int i = 0; i < num; i++)
	{
		fputc(ptr[i], out);
	}

	free(ptr);
}


void write_alpha_numeric(FILE* out, int num, const char* ignore, std::set<std::string>* nosubs)
{
	char *ptr = nullptr;

	do
	{
		if (ptr != nullptr)
		{
			free(ptr);
		}
		ptr = create_random_alphanumeric_string(num, ignore);
	} while (contains(ptr, nosubs));

	for (int i = 0; i < num; i++)
	{
		fputc(ptr[i], out);
	}

	free(ptr);
}


void write_binary(FILE* out, int num)
{
	for (int i = 0; i < num; i++)
	{
		fputc(rand() % 255, out);
	}
}

void write_ad(FILE *out, int num, const char *ignore, std::set<std::string> *nosubs)
{
	char *ptr = nullptr;

	do
	{
		if (ptr != nullptr)
		{
			free(ptr);
		}
		ptr = create_random_ad_string(num, ignore);
	} while (contains(ptr, nosubs));

	for (int i = 0; i < num; i++)
	{
		fputc(ptr[i], out);
	}

	free(ptr);
}


bool create_random_file(const char* path, FileOffset length, std::set<std::string>* nosubs)
{
	FILE *out = fopen(path, "w");
	if (out == nullptr)
	{
		return false;
	}

	write_ad(out, length, nullptr, nosubs);

	fclose(out);

	return true;
}


char* create_random_alphanumeric_string(int len, const char* ignore)
{
	char *ret_val = (char *) malloc (sizeof(*ret_val) * (len + 1));
	size_t numchars = strlen(alpha_numeric);

	for (int i = 0; i < len; i++)
	{
		do
		{
			ret_val[i] = alpha_numeric[rand() % numchars];
		} while (strchr(ignore, ret_val[i]) != nullptr);
	}

	ret_val[len] = '\0';
	return ret_val;
}


char* create_random_delim_string(int len, const char* ignore)
{
	char *ret_val = (char *) malloc (sizeof(*ret_val) * (len + 1));
	size_t numchars = strlen(delims);

	for (int i = 0; i < len; i++)
	{
		do
		{
			ret_val[i] = delims[rand() % numchars];
		} while (ignore == nullptr || strchr(ignore, ret_val[i]) != nullptr);
	}

	ret_val[len] = '\0';
	return ret_val;
}


char* create_random_ad_string(int len, const char* ignore)
{
	char *ret_val = (char *) malloc (sizeof(*ret_val) * (len + 1));
	size_t numchars = strlen(all_chars);

	for (int i = 0; i < len; i++)
	{
		do
		{
			ret_val[i] = all_chars[rand() % numchars];
		} while (ignore == nullptr || strchr(ignore, ret_val[i]) != nullptr);
	}

	ret_val[len] = '\0';
	return ret_val;
}


char* create_random_binary_string(int len, const char* ignore)
{
	char *ret_val = (char *) malloc (sizeof(*ret_val) * (len + 1));

	for (int i = 0; i < len; i++)
	{
		do
		{
			ret_val[i] = 1 + (rand() % 254);
		} while (ignore == nullptr || strchr(ignore, ret_val[i]) != nullptr);
	}

	ret_val[len] = '\0';
	return ret_val;
}


bool file_contains(std::string path, const char* substring)
{
	bool contains = false;

	int len = strlen(substring);
	char *buffer = (char *) calloc (len + 1, sizeof(*buffer));

	FILE *input = fopen(path.c_str(), "r");

	char *ptr = buffer;
	for (int i = 0; i < len; i++)
	{
		int c = fgetc(input);
		if (c < 0)
		{
			return false;
		}
		*(ptr++) = c;
	}

	if (strstr(buffer, substring) != nullptr)
	{
		contains = true;
	}

	int c;
	while ((c = fgetc(input)) >= 0)
	{
		for (int i = 0; i < len - 1; i++)
		{
			buffer[i] = buffer[i+1];
		}
		buffer[len-1] = c;

		if (strstr(buffer, substring) != nullptr)
		{
			contains = true;
			break;
		}
	}

	fclose(input);
	free(buffer);

	return contains;
}


void grep_files(std::string dir_path, const char* substring, std::set<std::string>& out_paths)
{
}

/*
 * file_maker.cc
 *
 *  Created on: Jun 6, 2014
 *      Author: thallock
 */
