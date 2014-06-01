/*
 * Query.h
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#ifndef QUERY_H_
#define QUERY_H_

class Query
{
public:
	Query();
	virtual ~Query();

	virtual bool has_next() = 0;
	virtual void next() = 0;
	virtual void display() = 0;

	double run();
};

double query(Query &q);

#endif /* QUERY_H_ */
