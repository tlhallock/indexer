/*
 * IndexEntry.cpp
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "query/IndexEntry.h"

#include "include/export.h"

IndexEntryIterater::IndexEntryIterater(const char *word) :
		num_left(0), in(read_word_index(word))
{
	if (!in->successful())
	{
		in = nullptr;
		return;
	}
	if (in != nullptr)
	{
		num_left = in->read_int();
	}
}

IndexEntryIterater::~IndexEntryIterater() {}

bool IndexEntryIterater::has_next() const
{
	return in != nullptr && num_left > 0;
}

FileId IndexEntryIterater::next()
{
	if (!has_next())
	{
		return -1;
	}

	--num_left;
	return in->read_int();
}

int IndexEntryIterater::get_num_left() const
{
	return num_left;
}

IndexEntry::IndexEntry(const char* token) :
	word(strdup(token)),
	files()
{

	IndexEntryIterater it(token);
	while (it.has_next())
	{
		files.insert(it.next());
	}
}

IndexEntry::~IndexEntry()
{
	free((char *) word);
}

void IndexEntry::add_file(FileId file)
{
	files.insert(file);
}

void IndexEntry::remove_file(FileId file)
{
	files.erase(file);
}

int IndexEntry::get_num_refs() const
{
	return files.size();
}

void IndexEntry::save() const
{
	if (get_num_refs() == 0)
	{
		remove_word_index(word);
		return;
	}

	std::unique_ptr<DataOutputStream> out(write_word_index(word));
	if (out == nullptr)
	{
		printf("Can't open '%s' for saving!\n", out->get_path());
		exit(1);
	}

	out->write((int) files.size());

	auto end = files.end();
	for (auto it = files.begin(); it != end; ++it)
	{
		out->write(*it);
	}
}

IndexEntryCache::IndexEntryCache() :
		entries()
{
}

IndexEntryCache::~IndexEntryCache()
{
	clear();
}

int IndexEntryCache::get_size()
{
	return entries.size();
}

void IndexEntryCache::clear()
{
	auto end = entries.end();
	for (auto it = entries.begin(); it != end; ++it)
	{
		delete it->second;
	}
	entries.clear();
}

IndexEntry& IndexEntryCache::get_index_entry(const char* token)
{
	IndexEntry *entry;

	auto it = entries.find(token);
	if (it == entries.end())
	{
		entry = new IndexEntry(token);
		entries.insert(std::pair<std::string, IndexEntry *>(token, entry));
	}
	else
	{
		entry = it->second;
	}

	return *entry;
}

void IndexEntryCache::flush()
{
	auto end = entries.end();
	for (auto it = entries.begin(); it != end; ++it)
	{
		it->second->save();
	}

//	if (get_size() > 1000)
//	{
//		clear();
//	}
}

IndexEntryCache& get_index_entry_cache()
{
	static IndexEntryCache *cache;
	if (cache == nullptr)
	{
		cache = new IndexEntryCache();
	}
	return *cache;
}
