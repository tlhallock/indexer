/*
 * Index.cpp
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "Index.h"
#include "export.h"

#define ENTRY_CACHE_SIZE 10
static std::map<word_id, IndexEntry *> entry_cache;

IndexEntry &get_entry(word_id id)
{
	auto it = entry_cache.find(id);
	if (it != entry_cache.end())
	{
		return *it->second;
	}

	if (entry_cache.size() > ENTRY_CACHE_SIZE)
	{
		// should find a better one...
		auto it = entry_cache.begin();
		delete it->second;
		entry_cache.erase(it);
	}


	IndexEntry *ret = new IndexEntry(id);
	entry_cache.insert(std::pair<word_id, IndexEntry *> (id, ret));


	char buff[256];
	sprintf(buff, FILE_LIST_PATTERN, id);

	DataInputStream in(buff);
	if (!in.successful())
	{
		return *ret;
	}

	int len = in.read_int();
	for (int i = 0; i < len; i++)
	{
		ret->add_file(in.read_int());
	}

	return *ret;
}

double query(const char* query)
{
	clock_t start_time = clock();

	Query q(query);

	word_id id;
	while( (id = q.next()) >= 0)
	{
		IndexEntry &entry = get_entry(id);
		entry.print_list();
	}

	return 1000.0 * (clock() - start_time) / CLOCKS_PER_SEC;
}

