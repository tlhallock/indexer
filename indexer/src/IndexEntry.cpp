/*
 * IndexEntry.cpp
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "IndexEntry.h"

#include "export.h"


IndexEntry::IndexEntry(const char *entry_) :
	entry(entry_),
	files() {}

IndexEntry::~IndexEntry()
{
	save();
}

void IndexEntry::add_file(file_id file)
{
	files.insert(file);
}

void IndexEntry::remove_file(file_id file)
{
	files.erase(files.find(file));
}

void IndexEntry::print_list() const
{
	auto end = files.end();
	for (auto it = files.begin(); it != end; ++it)
	{
		fprintf(stdout, "\t%s\n", get_file_manager().get_path(*it));
	}
}

void IndexEntry::save()
{
	char *buff = get_file();
	if (buff == nullptr)
	{
		return;
	}

	if (get_num_refs() == 0)
	{
		// delete file...
		free(buff);
		return;
	}

	DataOutputStream out(buff);
	if (!out.successful())
	{
		printf("Can't open '%s' for saving!\n", buff);
		exit(1);
	}
	free(buff);

	out.write(files.size());

	auto end = files.end();
	for (auto it = files.begin(); it != end; ++it)
	{
		out.write(*it);
	}
}

long IndexEntry::hash_code() const
{
	long ret = 0;
	long acc = 1;

	const char *ptr = entry;
	while (*ptr)
	{
		ret += acc * *ptr;
		acc *= 31;

		++ptr;
	}

	return ret;
}


char *IndexEntry::get_file()
{

	/*
	int collision_count = 0;
	long hash = hash_code();

	bool match = false;
	do
	{
		sprintf(out_path, FILE_LIST_PATTERN, hash, collision_count++);
		DataInputStream in(out_path);
		if (!in.successful())
		{
			return;
		}
		char *token = in.read_str();
		match = strcmp(token, entry);
		free(token);
	} while (match);
	*/

	if (*entry == '\0')
	{
		return nullptr;
	}

	const char *prefix = "/home/thallock/.indexer/file_lists/";

	char *ret_val = nullptr;
	int len = 0;
	escape(entry, ret_val, len);


	char *ret = (char *)malloc(strlen(prefix) + strlen(entry) + 1);
	sprintf(ret, "%s%s", prefix, entry);

	free(ret_val);

	return ret;
}

int IndexEntry::get_num_refs()
{
	return files.size();
}


