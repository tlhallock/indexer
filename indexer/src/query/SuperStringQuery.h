/*
 * SuperStringQuery.h
 *
 *  Created on: Jun 3, 2014
 *      Author: thallock
 */

#ifndef SUPERSTRINGQUERY_H_
#define SUPERSTRINGQUERY_H_

#include "include/common.h"

#include "index/StringsList.h"

#include "query/Query.h"
#include "query/SimpleQuery.h"

class SuperStringQuery : public Query
{
public:
	SuperStringQuery(const char *query);
	virtual ~SuperStringQuery();

	bool has_next() const;
	const QueryResults &next();

private:
	SuperStringIterator outer;
	FileOffsetListQuery *subquery;
};

#endif /* SUPERSTRINGQUERY_H_ */
