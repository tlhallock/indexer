/*
 * Index.cpp
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "Index.h"
#include "export.h"

#define ENTRY_CACHE_SIZE 10

static std::map<const char *, std::shared_ptr<IndexEntry> > entry_cache;

std::shared_ptr<IndexEntry> get_index_entry(const char *token)
{
	auto it = entry_cache.find(token);
	if (it != entry_cache.end())
	{
		return it->second;
	}

	if (entry_cache.size() > ENTRY_CACHE_SIZE)
	{
		// should find a better one...
		entry_cache.erase(entry_cache.begin());
	}

	IndexEntry *e = new IndexEntry(token);
	std::shared_ptr<IndexEntry> ret(e);
	entry_cache.insert(std::pair<const char *, std::shared_ptr<IndexEntry> > (token, ret));

	char *buff = e->get_file();

	DataInputStream in(buff);
	if (!in.successful())
	{
		free(buff);
		return ret;
	}

	int len = in.read_int();
	for (int i = 0; i < len; i++)
	{
		e->add_file(in.read_int());
	}

	free(buff);
	return ret;
}

double query(const char* query)
{
	clock_t start_time = clock();

//	Query q(query);
//
//	while( (id = q.next()) >= 0)
//	{
//		IndexEntry &entry = get_entry(id);
//		entry.print_list();
//	}

	return 1000.0 * (clock() - start_time) / CLOCKS_PER_SEC;
}

