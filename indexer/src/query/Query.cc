/*
 * Query.cpp
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "query/Query.h"

#include "include/export.h"

QueryResults::QueryResults() {}
QueryResults::~QueryResults() {}

Query::Query() {}
Query::~Query() {}

double Query::run()
{
	clock_t start_time = clock();

	while (has_next())
	{
		next().display();
	}

	return 1000.0 * (clock() - start_time) / CLOCKS_PER_SEC;
}
