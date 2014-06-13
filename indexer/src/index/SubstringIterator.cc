/*
 * SubstringIterator.cpp
 *
 *  Created on: May 31, 2014
 *      Author: thallock
 */

#include "index/SubstringIterator.h"

#include "include/export.h"

SubstringIterator::SubstringIterator(const char* str_) :
		SubstringIterator(str_, 1, INT_MAX) {}

SubstringIterator::SubstringIterator(const char* str_, int min_, int max_) :
			len(strlen(str_)),
			str(strdup(str_)),
			cur_value((char *) malloc (sizeof (*cur_value) * (len + 1))),
			start(0),
			stop(start + min_),
			min(min_),
			max(max_)
{
	if (min <= 0)
	{
		min = 1;
		stop = start + min;
	}
	done = len == 0 || max < 0 || min > max;
}

SubstringIterator::~SubstringIterator()
{
	free(str);
	free(cur_value);
}

bool SubstringIterator::has_next() const
{
	return !done;
}

void SubstringIterator::search()
{
	do
	{
		if (stop >= len || stop - start >= max)
		{
			if (start >= len - min)
			{
				done = true;
				return; // can't continue
			}
			else
			{
				start++;
			}
			stop = start + min;
		}
		else
		{
			stop++;
		}
	} while (start == stop);
}

const char* SubstringIterator::next()
{
	create_current();
	search();
	return cur_value;
}


void SubstringIterator::create_current()
{
	int j = 0;
	for (int i = start; i < stop; i++)
	{
		cur_value[j++] = str[i];
	}
	cur_value[j] = '\0';
}

int SubstringIterator::next_offset()
{
	return start;
}

const char* SubstringIterator::current()
{
	return cur_value;
}
