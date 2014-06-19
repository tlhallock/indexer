/*
 * Matcher.h
 *
 *  Created on: Jun 19, 2014
 *      Author: thallock
 */

#ifndef MATCHER_H_
#define MATCHER_H_

#include "parser/fsm/DFS.h"

#include <stdio.h>

class Matcher
{
public:
	Matcher(DFS *dfs, const char *filename);
	virtual ~Matcher();

	long next();
private:
	DFS *dfs;
	FILE *in;
	long offset;
};

#endif /* MATCHER_H_ */
