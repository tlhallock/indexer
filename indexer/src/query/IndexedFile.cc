/*
 * IndexedFile.cpp
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "query/IndexedFile.h"

#include "include/export.h"

#define META_FILE "/index"

IndexedFile::IndexedFile(FileId file_) :
	file(file_),
	real_path(get_file_mapper().get_path(file)) {}

IndexedFile::~IndexedFile() {}

void IndexedFile::clear()
{
	remove_file_index(real_path);
}

const char *IndexedFile::get_real_path() const
{
	return real_path;
}

time_t IndexedFile::get_last_indexed_time() const
{
	std::unique_ptr<DataInputStream> in(read_file_index(get_real_path(), nullptr));
	if (in == nullptr || !in->successful())
	{
		return (time_t) -1;
	}
	return in->read_long();
}

bool IndexedFile::needs_reindex() const
{
	time_t edited_time = get_last_write_time(real_path);
	time_t indexed_time = get_last_indexed_time();
	return  edited_time >= indexed_time;
}



















OccuranceIterator::OccuranceIterator(FileId file, const char *key) :
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
	in = read_file_index(real_path, key);

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
OccuranceIterator::~OccuranceIterator() {}

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

