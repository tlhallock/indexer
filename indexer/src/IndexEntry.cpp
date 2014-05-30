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

char *IndexEntry::get_file() const
{
	return get_file_or_dir(WORDS_BASE_DIR, entry, false);
}

void IndexEntry::save() const
{
	char *buff = get_file();
	if (buff == nullptr)
	{
		return;
	}

	if (get_num_refs() == 0)
	{
		delete_file(buff);
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

	out.write(entry);
	out.write((int) files.size());

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

int IndexEntry::get_num_refs() const
{
	return files.size();
}














IndexEntryIterater::IndexEntryIterater(const char *word) :
		num_left(0), in(nullptr)
{
	char *path = get_file_or_dir(WORDS_BASE_DIR, word, false);
	if (path == nullptr)
	{
		return;
	}

	in = new DataInputStream(path);
	if (!in->successful())
	{
		delete in;
		in = nullptr;
		return;
	}

	in->read_str();
	num_left = in->read_int();

	free(path);
}

IndexEntryIterater::~IndexEntryIterater()
{
	if (in == nullptr)
	{
		return;
	}

	delete in;
}

bool IndexEntryIterater::has_next() const
{
	return num_left > 0;
}

file_id IndexEntryIterater::next()
{
	if (!has_next())
	{
		return -1;
	}

	--num_left;
	return in->read_int();
}

int IndexEntryIterater::get_num_left() const
{
	return num_left;
}
