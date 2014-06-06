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


















OccuranceIterator::OccuranceIterator() {}
OccuranceIterator::~OccuranceIterator() {}






















IndexedOccuranceIterator::IndexedOccuranceIterator(FileId file, const char *key) :
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
		num = in->read_long();
	}
	catch (UnexpectedInputException &ex)
	{
		std::cout << "Unable to read " << ex.get_description() << std::endl;
		num = 0;
	}
}
IndexedOccuranceIterator::~IndexedOccuranceIterator() {}

bool IndexedOccuranceIterator::has_next() const
{
	return in != nullptr
			&& count < num;
}

FileOffset IndexedOccuranceIterator::next()
{
	if (!has_next())
	{
		return -1;
	}

	++count;
	return in->read_long();
}



















OriginalOccuranceIterator::OriginalOccuranceIterator(FileId file, const char* key) :
		query(strdup(key)),
		original(file),
		done(false),
		current_substring_offset(0)
{
	search();
}

OriginalOccuranceIterator::~OriginalOccuranceIterator()
{
	free((char *)query);
}

bool OriginalOccuranceIterator::has_next() const
{
	return !done;
}

FileOffset OriginalOccuranceIterator::next()
{
	if (done)
	{
		return -1;
	}
	FileOffset current = original.last_start() + current_substring_offset;
	search();
	return current;
}

void OriginalOccuranceIterator::search()
{
	for (;;)
	{
		const char *token = original.next();
		if (token == nullptr)
		{
			done = true;
			break;
		}

		const char *occ = strstr(token, query);
		if (occ == nullptr)
		{
			continue;
		}
		current_substring_offset = occ - token;
		break;
	}
}


OccuranceIterator* create_occurance_iterator(FileId file, const char* key)
{
	if (get_settings().should_index_files())
	{
		try
		{
			return new IndexedOccuranceIterator(file, key);
		}
		catch (UnexpectedInputException &ref)
		{
			std::cout << "Unable to get indexed file " << file << " for " << key << std::endl;
		}
	}

	return new OriginalOccuranceIterator(file, key);
}
