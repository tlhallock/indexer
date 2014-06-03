/*
 * SuperStringQuery.cpp
 *
 *  Created on: Jun 3, 2014
 *      Author: thallock
 */

#include "query/SuperStringQuery.h"

#include "include/export.h"

SuperStringQuery::SuperStringQuery(const char *query) :
		outer(get_strings_list().iterator(query)),
		subquery(nullptr) {}

SuperStringQuery::~SuperStringQuery()
{
	if (subquery != nullptr)
	{
		delete subquery;
	}
	subquery = nullptr;
}

bool SuperStringQuery::has_next() const
{
	return outer.has_next() || (subquery != nullptr && subquery->has_next());
}

const QueryResults& SuperStringQuery::next()
{
	while (subquery == nullptr || !subquery->has_next())
	{
		if (!outer.has_next())
		{
			puts("37019837501938750139875");
			exit(1);
		}
		const char *superstring = outer.next();
		if (subquery != nullptr)
		{
			delete subquery;
		}
		subquery = new FileOffsetListQuery(superstring);
	}

	return subquery->next();
}