/*
 * IndexedFile.cpp
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "IndexedFile.h"

#include "export.h"

FilesWordIterator::FilesWordIterator(std::map<const char *, int> &words) :
		end(words.end()), it(words.begin()) {}

FilesWordIterator::~FilesWordIterator() {}

const char *FilesWordIterator::next()
{
	if (it == end)
	{
		return nullptr;
	}

	return (it++)->first;
}















IndexedFile::IndexedFile(file_id file_) :
	file(file_),
	last_indexed_time(0),
	current_tokens(0),
	words(),
	orders() {}

IndexedFile::~IndexedFile()
{
	save();
	clear();
}

void IndexedFile::append(const char *token)
{
	auto it = words.find(token);

	int index;
	if (it == words.end())
	{
		index = orders.size();
		words.insert(std::pair<const char *, int> (strdup(token), index));
		orders.push_back(new std::set<int>);
	}
	else
	{
		index = it->second;
	}

	orders.at(index)->insert(current_tokens++);
}

void IndexedFile::clear()
{
	auto oend = orders.end();
	for (auto it = orders.begin(); it != oend; ++it)
	{
		delete *it;
	}
	auto wend = words.end();
	for (auto it = words.begin(); it != wend; ++it)
	{
		delete it->first;
	}

	words.clear();
	orders.clear();

	current_tokens = 0;
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
//		out.write(*it);
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

std::shared_ptr<IndexedFile> get_indexed_file(file_id file)
{
	char buff[256];
	sprintf(buff, FILE_INDEX_PATTERN, file);

	IndexedFile *ifile = new IndexedFile(file);
	std::shared_ptr<IndexedFile> ret(ifile);

	DataInputStream in(buff);
	if (!in.successful())
	{
		return ret;
	}

	int length = in.read_int();
	for (int i = 0; i < length; i++)
	{
//		ifile->append(in.read_str());
	}

	return ret;
}

FilesWordIterator &IndexedFile::get_iterater()
{
	return *(new FilesWordIterator(words));
}

