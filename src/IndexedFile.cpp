/*
 * IndexedFile.cpp
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "IndexedFile.h"

#include "export.h"

IndexedFile::IndexedFile(file_id file_) :
	file(file_),
	last_indexed_time(0),
	words() {}

IndexedFile::~IndexedFile()
{
	save();
}

void IndexedFile::append(word_id id)
{
	words.push_back(id);
}

void IndexedFile::clear()
{
	words.clear();
}

void IndexedFile::save()
{
	char buff[256];
	sprintf(buff, FILE_INDEX_PATTERN, file);
	DataOutputStream out(buff);
	if (!out.successful())
	{
		printf("Unable to save file %s\n", get_file_manager().get_path(file));
		exit(1);
	}

	int length = words.size();
	out.write(length);

	auto end = words.end();
	for (auto it = words.begin(); it != end; ++it)
	{
		out.write(*it);
	}
}

void IndexedFile::reset_indexed_time()
{
	time(&last_indexed_time);
}

time_t IndexedFile::get_last_indexed_time()
{
	return last_indexed_time;
}

std::unique_ptr<IndexedFile> get_indexed_file(file_id file)
{
	char buff[256];
	sprintf(buff, FILE_INDEX_PATTERN, file);

	std::unique_ptr<IndexedFile> ret(new IndexedFile(file));

	DataInputStream in(buff);
	if (!in.successful())
	{
		return ret;
	}

	int length = in.read_int();
	for (int i = 0; i < length; i++)
	{
		ret->append(in.read_int());
	}

	return ret;
}

