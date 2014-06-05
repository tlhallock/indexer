/*
 * SubstringIndex.cpp
 *
 *  Created on: Jun 4, 2014
 *      Author: thallock
 */

#include <experimental/SubstringIndex.h>

SubstringIndex::SubstringIndex(int n_) :
	n(n_),
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

void SubstringIndex::add(const char* word)
{
//	int len = strlen(word);
//	if (len < n)
//	{
//		return;
//	}
//
//	char *substr = (char *) alloca (sizeof(*substr) * (n + 1));
//
//	for (int i = 0; i < len - n + 1; i++)
//	{
//		for (int j = 0; j < n; j++)
//		{
//			substr[j] = word[i + j];
//		}
//		substr[n] = '\0';

	const char *substr = word;

		auto it = cache.find(substr);
		if (it != cache.end())
		{
			it->second.insert(word);
		}
		else
		{
			std::set<std::string> *set = new std::set<std::string>;
			set->insert(word);
			cache.insert(std::pair<std::string, std::set<std::string>>(substr, *set));
			delete set;
		}
//	}
}

StringListIterator* SubstringIndex::iterator(const char* word) const
{
	// could be much smarter about this...
	char *substr = strndup(word, n);
	auto it = cache.find(substr);
	free(substr);

	if (it == cache.end())
	{
		return nullptr;
	}

	return new StringListIterator(word, it->second);
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
		std::cout << it->first << " (" << it->second.size() << ") :\n\t";
		auto iend = it->second.end();
		for (auto iit = it->second.begin(); iit != iend; ++iit)
		{
			std::cout << "'" << *iit << "' ";
		}
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
		index = new SubstringIndex(3);
	}
	return *index;
}


int SubstringIndex::count() const
{
	int count = 0;

	auto end = cache.end();
	for (auto it = cache.begin(); it != end; ++it)
	{
		count += it->second.size();
	}

	return count;
}
