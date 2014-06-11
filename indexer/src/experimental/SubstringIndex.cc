/*
 * SubstringIndex.cpp
 *
 *  Created on: Jun 4, 2014
 *      Author: thallock
 */

#include "experimental/SubstringIndex.h"
#include "index/SubstringIterator.h"
#include "utils/Hash.h"

SubstringIndex::SubstringIndex() :
	cache()
{
}

SubstringIndex::~SubstringIndex()
{
}


StringListIterator::StringListIterator(const std::string &str_, const std::set<std::string> &set) :
		str(str_),
		end(set.end()),
		it(set.begin())
{
	search();
}

StringListIterator::~StringListIterator()
{
}

bool StringListIterator::has_next() const
{
	return it != end;
}

void StringListIterator::search()
{
	while (it != end)
	{
		if (it->find(str) != std::string::npos)
		{
			break;
		}

		++it;
	}
}

const char *StringListIterator::next()
{
	// could get destroyed...
	const char *ret = it->c_str();
	search();
	return ret;
}

void SubstringIndex::add(const char* word)
{
	// should pass in range here...
	SubstringIterator subs(word);
	while (subs.has_next())
	{
		const char *substring = subs.next();
		int len = subs.offset();

		if (len < get_settings().get_minimum_substring_index())
		{
			continue;
		}

		if (len > get_settings().get_maximum_substring_index())
		{
			continue;
		}

		get(substring)->add(word);
	}
}

StringListIterator* SubstringIndex::iterator(const char* full_word)
{
	int len = strlen(full_word);
	if (len < get_settings().get_minimum_substring_index())
	{
		puts("uh oh 13987139487109374139874");
		exit(1);
	}
	if (len > get_settings().get_maximum_substring_index())
	{
		len = get_settings().get_maximum_substring_index();
	}

	// could be much smarter about this...
	char *substr = strndup(full_word, len);
	auto it = cache.find(substr);
	free(substr);

	if (it != cache.end())
	{
		return it->second->iterator();
	}

	// there are none
	return new StringListIterator(full_word, std::set<std::string>{});
}


void SubstringIndex::print() const
{
	for (int i = 0; i < 80; i++)
	{
		std::cout << "#";
	}
	std::cout << std::endl;
	auto end = cache.end();
	for (auto it = cache.begin(); it != end; ++it)
	{
//		std::cout << it->first << " (" << it->second->get_size() << ") :\n\t";
//		auto iend = it->second.end();
//		for (auto iit = it->second.begin(); iit != iend; ++iit)
//		{
//			std::cout << "'" << *iit << "' ";
//		}
		std::cout << std::endl;
	}
	for (int i = 0; i < 80; i++)
	{
		std::cout << "#";
	}
	std::cout << std::endl;
}

SubstringIndex& get_exp_index()
{
	static SubstringIndex *index;
	if (index == nullptr)
	{
		index = new SubstringIndex();
	}
	return *index;
}


int SubstringIndex::count() const
{
	int count = 0;

	auto end = cache.end();
	for (auto it = cache.begin(); it != end; ++it)
	{
		count += it->second->get_size();
	}

	return count;
}

SuperStringList::SuperStringList(const std::string &key_) :
		size(0),
		superstrings(nullptr),
		memory_usage(0),
		num_accessed(0),
		key(key_)
{
}

SuperStringList::~SuperStringList()
{
	if (superstrings != nullptr)
	{
		delete superstrings;
	}
}

int SuperStringList::get_size() const
{
	if (superstrings != nullptr)
	{
		size = superstrings->size();
	}
	return size;
}

bool SuperStringList::cached() const
{
	return superstrings != nullptr;
}

void SuperStringList::add(const std::string& superstring)
{
	if (superstrings == nullptr)
	{
		puts("Error 6310605176438756134");
		exit(1);
	}

	auto it = superstrings->find(superstring);
	if (it != superstrings->end())
	{
		return;
	}

	superstrings->insert(superstring);
	memory_usage += superstring.size();
}

void SuperStringList::remove(const std::string& superstring)
{
	if (superstrings == nullptr)
	{
		puts("Error 0759287509287409875");
		exit(1);
	}
	auto it = superstrings->find(superstring);
	if (it == superstrings->end())
	{
		return;
	}

	superstrings->erase(superstring);
	memory_usage -= superstring.size();
}

void SuperStringList::load()
{
	if (superstrings != nullptr)
	{
		// Already loaded...
		return;
	}
	superstrings = new std::set<std::string>;

	std::unique_ptr<DataInputStream> input = read_substring_index(key.c_str());
	if (input == nullptr)
	{
		return;
	}

	try
	{
		size = input->read_int();
		for (int i = 0; i < size; i++)
		{
			superstrings->insert(*input->read_str());
		}
	}
	catch (UnexpectedInputException &exception)
	{
		std::cout << "Error reading key for \'" << key << "'" << std::endl;
		superstrings->clear();
	}
}

void SuperStringList::save() const
{
	if (superstrings == nullptr)
	{
		return; // nothing to save
	}

	std::unique_ptr<DataOutputStream> output = write_substring_index(key.c_str());

	output->write(size = superstrings->size());

	auto end = superstrings->end();
	for (auto it = superstrings->begin(); it != end; ++it)
	{
		output->write(it->c_str());
	}
}

StringListIterator* SuperStringList::iterator()
{
	return new StringListIterator(key, *superstrings);
}

size_t SuperStringList::get_memory_usage() const
{
	return memory_usage;
}

void SubstringIndex::save() const
{
}

void SubstringIndex::read()
{
}

std::shared_ptr<SuperStringList> SubstringIndex::get(const char* key)
{
	auto it = cache.find(key);
	if (it != cache.end())
	{
		return it->second;
	}

	std::shared_ptr<SuperStringList> ptr(new SuperStringList(key));
	cache.insert(std::pair<std::string, std::shared_ptr<SuperStringList>>(key, ptr));
	return ptr;
}
