/*
 * Query.h
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#ifndef QUERY_H_
#define QUERY_H_

class QueryResults
{
public:
	QueryResults();
	virtual ~QueryResults();

	virtual void display() const = 0;
};


class Query
{
public:
	Query();
	virtual ~Query();

	virtual bool has_next() const = 0;
	virtual const QueryResults &next() = 0;

	double run();
};

double query(Query &q);

#endif /* QUERY_H_ */
