/*
 * WordManager.cpp
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "WordManager.h"

#include "export.h"

Node::Node(Node *parent_, int parents_index_) :
		size(0),
		parent(parent_),
		parents_index(parents_index_)
{
	for (int i = 0; i < BTREE_SIZE; i++)
	{
		keys[i] = nullptr;
		children[i] = nullptr;
	}
}

Node::~Node()
{
	for (int i = 0; i < BTREE_SIZE; i++)
	{
		if (keys[i] != nullptr)
		{
			free(keys[i]);
		}
		if (children[i] != nullptr)
		{
			delete children[i];
		}
	}
}

int Node::get_index(const char *query, bool &match) const
{
	if (size == 0)
	{
		return 0;
	}

	int cmp = strcmp(query, keys[0]);
	if (cmp <= 0)
	{
		match = cmp == 0;
		return 0;
	}
	cmp = strcmp(query, keys[size-1]);
	if (cmp >= 0)
	{
		match = cmp == 0;
		return size-1;
	}

	int max = size - 1;
	int min = 0;

	while (max > min + 1)
	{
		int mid = (max + min) / 2;
		cmp = strcmp(query, keys[mid]);

		if (cmp == 0)
		{
			match = true;
			return mid;
		}

		if (cmp < 0)
		{
			max = mid;
		}
		else
		{
			min = mid;
		}
	}

	cmp = strcmp(query, keys[min]);
	if (cmp == 0)
	{
		match = true;
		return min;
	}

	if (min == max)
	{
		match = false;
		return min;
	}
	cmp = strcmp(query, keys[max]);
	if (cmp == 0)
	{
		match = true;
		return max;
	}

	match = false;
	return min;
}

int Node::get_id() const
{
	int acc = 0;

	const Node *c = this;
	int size = BTREE_SIZE;

	while (c != NULL)
	{
		acc += c->parents_index;
		acc += size;

		size *= BTREE_SIZE;
		c = c->parent;
	}

	return acc;
}

void Node::save() const
{
}























void WordManager::register_entry(const char *token, file_id file)
{
	const char *ptr = token;
	while (*ptr)
	{
//		root->insert(ptr);
		std::shared_ptr<IndexEntry> error_once = get_index_entry(ptr);
		IndexEntry *entry = error_once.get();
		entry->add_file(file);
		ptr++;
	}
}

void WordManager::remove_entries(file_id file)
{
	std::shared_ptr<IndexedFile> fptr = get_indexed_file(file);
	IndexedFile *error_once = fptr.get();

	FilesWordIterator it = error_once->get_iterater();
	const char *str;
	while ((str = it.next()) != NULL)
	{
		while (*str)
		{
			std::shared_ptr<IndexEntry> entry = get_index_entry(str);
			IndexEntry *error_again = entry.get();
			error_again->remove_file(file);
			if (error_again->get_num_refs() == 0)
			{
//				root->remove(str);
			}
			str++;
		}
	}
}

/*
IndexEntry &search(const char *query)
{
	return nullptr;
}
*/





static WordManager *manager_ = nullptr;
WordManager& get_word_manager()
{
	if (manager_ == nullptr)
	{
		manager_ = new WordManager();
	}

	return *manager_;
}

WordManager::WordManager() :
			root(nullptr) {}

WordManager::~WordManager() {}



void create_random_filename(char *out)
{
	constexpr int len = strlen(VALID_FILENAME_CHARS);
	for (int i = 0; i < ENTRY_FILENAME_SIZE; i++)
	{
		out[i] = VALID_FILENAME_CHARS[rand() % len];
	}
	out[ENTRY_FILENAME_SIZE] = '\0';
}
