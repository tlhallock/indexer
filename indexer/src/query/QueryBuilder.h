/*
 * QueryBuilder.h
 *
 *  Created on: Jun 3, 2014
 *      Author: thallock
 */

#ifndef QUERYBUILDER_H_
#define QUERYBUILDER_H_

#include "include/common.h"

#include "query/Query.h"

class QueryBuilder
{
public:
	QueryBuilder();
	virtual ~QueryBuilder();

	Query *build_query(const char *string);
};

#endif /* QUERYBUILDER_H_ */
