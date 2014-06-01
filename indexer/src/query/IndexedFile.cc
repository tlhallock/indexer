/*
 * IndexedFile.cpp
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "query/IndexedFile.h"

#include "include/export.h"

#define META_FILE "index"

IndexedFile::IndexedFile(file_id file_) :
	file(file_),
	real_path(get_file_mapper().get_path(file)),
	base_dir(get_file_or_dir(FILES_BASE_DIR, real_path, true)),
	index_path(get_file_or_dir(base_dir, META_FILE, false)) {}

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
	in.read_str(); // throw file name away
	return in.read_long();
}

bool IndexedFile::needs_reindex() const
{
	return get_last_write_time(real_path) >= get_last_indexed_time();
}



















OccuranceIterator::OccuranceIterator(file_id file, const char *key)
	: num(0), count(0), in(nullptr)
{

	const char *real_path = get_file_mapper().get_path(file);
	const char *file_dir = get_file_or_dir(FILES_BASE_DIR, real_path, true);
	if (file_dir == nullptr)
	{
		return;
	}

	const char *file_path = get_file_or_dir(file_dir, key, false);
	if (file_path == nullptr)
	{
		return;
	}

	in = new DataInputStream(file_path);
	if (!in->successful())
	{
		delete in;
		in = nullptr;
	}

	num = in->read_int();
}
OccuranceIterator::~OccuranceIterator()
{
	if (in != nullptr)
	{
		delete in;
	}
}

bool OccuranceIterator::has_next()
{
	return in != nullptr && count < num;
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

