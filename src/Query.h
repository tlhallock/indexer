/*
 * Query.h
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#ifndef QUERY_H_
#define QUERY_H_

#include "WordManager.h"

class Query
{
public:
	Query(const char *query);
	virtual ~Query();

	word_id next();
private:
	const char *query;
	int index;
};

#endif /* QUERY_H_ */
