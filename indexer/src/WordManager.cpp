/*
 * WordManager.cpp
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "WordManager.h"

#include "export.h"

















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

WordManager::WordManager() /*:
			root(nullptr)*/ {}

WordManager::~WordManager() {}



