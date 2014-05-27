/*
 * Query.cpp
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "Query.h"

Query::Query(const char *query_) : query(query_), index(0) {}
Query::~Query() {}

word_id Query::next()
{
	WordManager &manager = get_word_manager();
	while (index < manager.length())
	{
		if (manager.word_contains(index, query))
		{
			return index++;
		}

		index++;
	}
	return -1;
}
