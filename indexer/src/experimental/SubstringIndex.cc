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
	auto end = cache.end();
	for (auto it = cache.begin(); it != end; ++it)
	{
		delete it->second.second;
	}
}

StringList::StringList(std::string* str_, StringList* next_) :
		str(str_),
		next(next_)
{
}

StringList::~StringList()
{
	if (next != nullptr)
	{
		delete next;
	}
	// str causes a memory leak...
}

StringListIterator::StringListIterator(std::string str_, StringList* first_) :
		str(str_),
		current(first_)
{
	search();
}

StringListIterator::~StringListIterator()
{
}

bool StringListIterator::has_next() const
{
	return current != nullptr;
}

void StringListIterator::search()
{
	StringList *ptr = current;
	current = nullptr;
	while (ptr != nullptr)
	{
		if (ptr->str->find(str) != std::string::npos)
		{
			current = ptr;
			break;
		}

		ptr = ptr->next;
	}
}

void SubstringIndex::add(const char* word)
{
	int len = strlen(word);
	if (len < n)
	{
		return;
	}

	char *substr = (char *) alloca (sizeof(*substr) * (n + 1));

	std::string *single = new std::string(word);

	for (int i = 0; i < len - n + 1; i++)
	{
		for (int j = 0; j < n; j++)
		{
			substr[j] = word[i + j];
		}
		substr[n] = '\0';

		auto it = cache.find(substr);
		if (it != cache.end())
		{
			StringList *l = it->second.second;
			if (l->contains(single))
			{
				continue;
			}
			it->second.first++;
			it->second.second = new StringList(single, it->second.second);
		}
		else
		{
			cache.insert(
					std::pair<std::string, std::pair<int, StringList *>>(substr,
							std::pair<int, StringList *>(1, new StringList(single, nullptr))));
		}
	}
}

StringListIterator* SubstringIndex::iterator(const char* word) const
{
	char *substr = strndup(word, n);
	auto it = cache.find(substr);
	free(substr);

	if (it == cache.end())
	{
		return nullptr;
	}
	return new StringListIterator(word, it->second.second);
}

bool StringList::contains(std::string* str_) const
{
	if (str->compare(*str_) == 0)
	{
		return true;
	}

	if (next == nullptr)
	{
		return false;
	}

	return next->contains(str_);
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
		std::cout << it->first << " (" << it->second.first << ") :\n\t";
		it->second.second->print();
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
		index = new SubstringIndex(2);
	}
	return *index;
}

void StringList::print() const
{
	std::cout << " '" << *str << "' ";

	if (next == nullptr)
	{
		std::cout << std::endl;
	}
	else
	{
		next->print();
	}
}

int SubstringIndex::count() const
{
	int count = 0;

	auto end = cache.end();
	for (auto it = cache.begin(); it != end; ++it)
	{
		count += it->second.first;
	}

	return count;
}
