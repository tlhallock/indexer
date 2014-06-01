/*
 * SubstringIterator.cpp
 *
 *  Created on: May 31, 2014
 *      Author: thallock
 */

#include "index/SubstringIterator.h"

#include "include/export.h"

SubstringIterator::SubstringIterator(const char* str_) :
	len(strlen(str_)),
	str(strdup(str_)),
	cs(str),
	ce(str + len),
	cur_value((char *) malloc (sizeof (*cur_value) * len))
{
	create_current();
}

SubstringIterator::~SubstringIterator()
{
	free(str);
	free(cur_value);
}

bool SubstringIterator::has_next()
{
	return ce != cs;
}

const char* SubstringIterator::next()
{
	if (ce == cs)
	{
		return nullptr;
	}

	ce--;
	if (ce != cs)
	{
		return create_current();
	}

	cs++;
	ce = str + len;

	if (ce == cs)
	{
		return nullptr;
	}

	return create_current();
}


const char *SubstringIterator::create_current()
{
	char *dest = cur_value;
	char *src = cs;


	while (src != ce)
	{
		*(dest++) = *(src++);
	}

	*dest = '\0';

	return cur_value;
}

int SubstringIterator::offset()
{
	return cs - str;
}

const char* SubstringIterator::current()
{
	return cur_value;
}
