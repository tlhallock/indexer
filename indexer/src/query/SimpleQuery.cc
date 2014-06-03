/*
 * SimpleQuery.cpp
 *
 *  Created on: May 31, 2014
 *      Author: thallock
 */

#include <query/SimpleQuery.h>

#include "include/export.h"

FileListQuery::FileListQuery(const char* word) :
		current(-1),
		it(word)
{
}

FileListQuery::~FileListQuery()
{
}

bool FileListQuery::has_next() const
{
	return it.has_next();
}



const QueryResults &FileListQuery::next()
{
	current = it.next();
	return current;
}















FileOffsetListQuery::FileOffsetListQuery(const char* word_) :
		word(word_),

		current(-1, -1),

		oit(word),
		iit(nullptr)
{
}

FileOffsetListQuery::~FileOffsetListQuery()
{
	if (iit != nullptr)
	{
		delete iit;
	}
}

bool FileOffsetListQuery::has_next() const
{
	return oit.has_next() || (iit != nullptr && iit->has_next());
}

const QueryResults &FileOffsetListQuery::next()
{
	while (iit == nullptr || !iit->has_next())
	{
		if (!oit.has_next())
		{
			return current;
		}

		int fid = oit.next();
		current.set_file(fid);
		if (iit != nullptr)
		{
			delete iit;
		}

		iit = new OccuranceIterator(fid, word);
	}

	current.set_offset(iit->next());
	return current;
}




















FileListQueryResults::FileListQueryResults(FileId file_) :
		file(file_)
{
}
FileListQueryResults::~FileListQueryResults()
{
}

void FileListQueryResults::display() const
{
	std::cout << "File " << get_file_mapper().get_path(file) << " matches." << std::endl;
}

FileOffsetListQueryResults::FileOffsetListQueryResults(FileId file_, int offset_) :
		file(file_), offset(offset_)
{
}

FileOffsetListQueryResults::~FileOffsetListQueryResults()
{
}

void FileOffsetListQueryResults::display() const
{
	std::cout << "File " << get_file_mapper().get_path(file) << " matches at offset " << offset << "." << std::endl;
}

void FileOffsetListQueryResults::set_file(int file_)
{
	file = file_;
}
void FileOffsetListQueryResults::set_offset(int offset_)
{
	offset = offset_;
}

