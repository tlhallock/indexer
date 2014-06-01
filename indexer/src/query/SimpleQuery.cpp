/*
 * SimpleQuery.cpp
 *
 *  Created on: May 31, 2014
 *      Author: thallock
 */

#include <query/SimpleQuery.h>

FileListQuery::FileListQuery(const char* word) :
		current(-1),
		it(word)
{
}

FileListQuery::~FileListQuery()
{
}

bool FileListQuery::has_next()
{
	return it.has_next();
}

void FileListQuery::next()
{
	current = it.next();
}

void FileListQuery::display()
{
	printf("Found file containing given word: %d", current);
}















FileOffsetListQuery::FileOffsetListQuery(const char* word_) :
		word(word_),

		current_file(-1),
		current_offset(-1),

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

bool FileOffsetListQuery::has_next()
{
	return !iit->has_next() && !oit.has_next();
}

void FileOffsetListQuery::next()
{
	if (iit != nullptr && iit->has_next())
	{
		current_offset = iit->next();
		return;
	}

	while (!iit->has_next())
	{
		if (!oit.has_next())
		{
			return;
		}

		current_file = oit.next();
		if (iit != nullptr)
		{
			delete iit;
		}

		iit = new OccuranceIterator(current_file, word);
	}

	current_offset = iit->next();
}

void FileOffsetListQuery::display()
{
	printf("File %d contains %s at offset %d\n", current_file, word, current_offset);
}
