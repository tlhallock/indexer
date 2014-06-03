/*
 * IndexEntry.cpp
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "query/IndexEntry.h"

#include "include/export.h"

void IndexEntryIterater::init(const char *word, const char *path)
{
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

	free(in->read_str());
	num_left = in->read_int();
}

IndexEntryIterater::IndexEntryIterater(const char *word) :
		num_left(0), in(nullptr)
{
	char *path = get_file_or_dir(get_settings().get_words_base_dir(), word, false);

	init(word, path);

	free(path);
}

IndexEntryIterater::IndexEntryIterater(const char *word, const char *path) :
		num_left(0), in(nullptr)
{
	init(word, path);
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
	word(token),
	path(get_file_or_dir(get_settings().get_words_base_dir(), word, false)),
	files()
{
	IndexEntryIterater it(token, path);
	while (it.has_next())
	{
		files.insert(it.next());
	}
}

IndexEntry::~IndexEntry()
{
	free((char *) word);
	free((char *) path);
}

void IndexEntry::add_file(FileId file)
{
	files.insert(file);
}

void IndexEntry::remove_file(FileId file)
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
		delete_file(path);
		return;
	}

	DataOutputStream out(path);
	if (!out.successful())
	{
		printf("Can't open '%s' for saving!\n", path);
		exit(1);
	}

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
		entry = new IndexEntry(strdup(token));
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
