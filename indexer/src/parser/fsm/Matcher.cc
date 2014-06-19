/*
 * Matcher.cc
 *
 *  Created on: Jun 19, 2014
 *      Author: thallock
 */

#include <parser/fsm/Matcher.h>


Matcher::Matcher(DFS* dfs_, const char* filename) :
	dfs(dfs_),
	in(fopen(filename, "r")),
	offset(0)
{
}

Matcher::~Matcher()
{
	if (in != nullptr)
	{
		fclose(in);
	}
}

long Matcher::next()
{
	if (in == nullptr)
	{
		return -1;
	}

	int r;
	while ((r = fgetc(in)) >= 0)
	{
		dfs->next(r);
		offset++;

		if (dfs->accepting())
		{
			return offset;
		}
	}

	fclose (in);
	in = nullptr;

	return -1;
}
