/*
 * IndexedFile.cpp
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "query/IndexedFile.h"

#include "include/export.h"

#define META_FILE "/index"

IndexedFile::IndexedFile(file_id file_) :
	file(file_),
	real_path(get_file_mapper().get_path(file)),
	base_dir(get_file_or_dir(get_settings().get_files_base_dir(), real_path, true)),
	index_path(concatenate(base_dir, META_FILE)) {}

IndexedFile::~IndexedFile()
{
	free((char *)base_dir);
	free((char *)index_path);
}

void IndexedFile::clear()
{
	delete_file(base_dir);
}

const char *IndexedFile::get_index_path() const
{
	return base_dir;
}
const char *IndexedFile::get_index_attr_path() const
{
	return index_path;
}

const char *IndexedFile::get_real_path() const
{
	return real_path;
}

time_t IndexedFile::get_last_indexed_time() const
{
	DataInputStream in(index_path);
	if (!in.successful())
	{
		return (time_t) -1;
	}
	free(in.read_str()); // throw file name away
	return in.read_long();
}

bool IndexedFile::needs_reindex() const
{
	time_t edited_time = get_last_write_time(real_path);
	time_t indexed_time = get_last_indexed_time();
	return  edited_time >= indexed_time;
}



















OccuranceIterator::OccuranceIterator(file_id file, const char *key) :
	num(0),
	count(0),
	in(nullptr)
{
	const char *real_path = get_file_mapper().get_path(file);
	if (real_path == nullptr)
	{
		std::cout << "No file with id " << file << std::endl;
		return;
	}
	char *file_dir = get_file_or_dir(get_settings().get_files_base_dir(), real_path, true);
	if (file_dir == nullptr)
	{
		return;
	}

	char *file_path = get_file_or_dir(file_dir, key, false);
	free(file_dir);

	if (file_path == nullptr)
	{
		return;
	}

	in = new DataInputStream(file_path);
	free(file_path);

	if (!in->successful())
	{
		delete in;
		in = nullptr;
	}

	// throw away word...
	free(in->read_str());

	try
	{
		num = in->read_int();
	}
	catch (UnexpectedInputException &ex)
	{
		std::cout << "Unable to read " << ex.get_description() << std::endl;
		num = 0;
	}
}
OccuranceIterator::~OccuranceIterator()
{
	if (in != nullptr)
	{
		delete in;
	}
}

bool OccuranceIterator::has_next() const
{
	return in != nullptr
			&& count < num;
}

int OccuranceIterator::next()
{
	if (!has_next())
	{
		return -1;
	}

	++count;
	return in->read_int();
}

