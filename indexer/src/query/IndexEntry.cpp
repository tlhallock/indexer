/*
 * IndexEntry.cpp
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "query/IndexEntry.h"

#include "include/export.h"



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
