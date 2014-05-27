/*
 * WordManager.cpp
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "WordManager.h"
#include "export.h"

static WordManager *manager_ = nullptr;

WordManager& get_word_manager()
{
	if (manager_ == nullptr)
	{
		manager_ = new WordManager();
		if (!manager_->read(WORDS_FILE))
		{
			char str[2];
			str[1] = '\0';
			const int len = strlen(DELIMITERS);
			for (int i = 0; i < len; i++)
			{
				str[0] = DELIMITERS[i];
				manager_->get_word(str);
			}
		}
	}

	return *manager_;
}

WordManager::WordManager() :
			by_word(),
			by_id() {}

WordManager::~WordManager()
{
	auto end = by_id.end();
	for (auto it = by_id.begin(); it != end; ++it)
	{
		delete *it;
	}
}

word_id WordManager::get_word(const char* word)
{
	auto it = by_word.find(word);
	if (it != by_word.end())
	{
		return it->second;
	}

	word_id next_id = by_id.size();

	const char *dword = strdup(word);

	by_id.push_back(dword);
	by_word.insert(std::pair<const char *, word_id>(dword, next_id));

	return next_id;
}

const char* WordManager::get_word(word_id id)
{
	return by_id.at(id);
}

int WordManager::get_num_words()
{
	return by_id.size();
}


size_t WordManager::get_memory()
{
	size_t mem = 0;

	auto end = by_id.end();
	for (auto it = by_id.begin(); it != end; ++it)
	{
		mem += strlen((*it));
	}
	return mem;
}

bool WordManager::write(const char *path)
{
	DataOutputStream out(path);
	if (!out.successful())
	{
		return false;
	}

	int size = by_id.size();
	out.write(size);
	for (int i = 0; i < size; i++)
	{
		out.write(by_id.at(i));
	}

	return true;
}

bool WordManager::read(const char *path)
{
	DataInputStream in(path);
	if (!in.successful())
	{
		return false;
	}

	int size = in.read_int();
	for (int i = 0; i < size; i++)
	{
		get_word(in.read_str());
	}
	return true;
}

bool WordManager::word_contains(word_id id, const char *str)
{
	return strstr(get_word(id), str) != NULL;
}

int WordManager::length()
{
	return by_id.size();
}
