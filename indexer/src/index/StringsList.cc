/*
 * StringsList.cpp
 *
 *  Created on: Jun 3, 2014
 *      Author: thallock
 */

#include <index/StringsList.h>

StringsList::StringsList() {}

StringsList::~StringsList() {}

SuperStringIterator::~SuperStringIterator() {}

bool SuperStringIterator::has_next() const
{
	return current != nullptr;
}

const char* SuperStringIterator::next()
{
	const char *ret = current;
	search();
	return ret;
}

SuperStringIterator::SuperStringIterator(std::vector<std::string> &words, const char *string_) :
		string(string_),
		current(nullptr),
		it (words.begin()),
		end(words.end())
{
	search();
}

void StringsList::add(const char* string)
{
	words.push_back(string);
}

SuperStringIterator *StringsList::iterator(const char* string)
{
	return new SuperStringIterator(words, string);
}

const char* SuperStringIterator::get_query()
{
	return string;
}

void SuperStringIterator::search()
{
	current = nullptr;

	while (it != end && current == nullptr)
	{
		if (it->find(string) != std::string::npos)
		{
			current = it->c_str();
		}
		++it;
	}
}

StringsList& get_strings_list()
{
	static StringsList *list;
	if (list == nullptr)
	{
		list = new StringsList();
	}
	return *list;
}

int StringsList::count() const
{
	return words.size();
}

void StringsList::clear()
{
	words.clear();
}
