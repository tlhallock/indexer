/*
 * IndexEntry.cpp
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "query/IndexEntry.h"

#include "include/export.h"

IndexEntryIterater::IndexEntryIterater(const char *word) :
		num_left(0), in(nullptr)
{
	char *path = get_file_or_dir(WORDS_BASE_DIR, word, false);
	if (path == nullptr)
	{
		return;
	}

	in = new DataInputStream(path);
	if (!in->successful())
	{
		delete in;
		in = nullptr;
		return;
	}

	in->read_str();
	num_left = in->read_int();

	free(path);
}

IndexEntryIterater::~IndexEntryIterater()
{
	if (in == nullptr)
	{
		return;
	}

	delete in;
}

bool IndexEntryIterater::has_next() const
{
	return num_left > 0;
}

file_id IndexEntryIterater::next()
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
	word(token),
	path(get_file_or_dir(WORDS_BASE_DIR, word, false)),
	files()
{
}

IndexEntry::~IndexEntry()
{
	free((char *) path);
}

void IndexEntry::add_file(file_id file)
{
	files.insert(file);
}

void IndexEntry::remove_file(file_id file)
{
//	auto it = files.find(file);
//	if (it == files.end())
//	{
//		return;
//	}
	files.erase(file);
}

int IndexEntry::get_num_refs() const
{
	return files.size();
}

void IndexEntry::save() const
{
	if (path == nullptr)
	{
		return;
	}

	if (get_num_refs() == 0)
	{
		delete_file(buff);
		return;
	}

	DataOutputStream out(path);
	if (!out.successful())
	{
		printf("Can't open '%s' for saving!\n", path);
		exit(1);
	}
	free(buff);

	out.write(word);
	out.write((int) files.size());

	auto end = files.end();
	for (auto it = files.begin(); it != end; ++it)
	{
		out.write(*it);
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

void IndexEntryCache::clear()
{
	auto end = entries.end();
	for (auto it = entries.begin(); it != end; ++it)
	{
		delete it->first;
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
		char *word = strdup(token);
		entry = new IndexEntry(word);
		entries.insert(std::pair<const char *, IndexEntry *>(word, entry));
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
