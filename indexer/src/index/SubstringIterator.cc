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
	current_start(str),
	current_end(str + len),
	cur_value((char *) malloc (sizeof (*cur_value) * (len + 1)))
{
	create_current();
}

SubstringIterator::~SubstringIterator()
{
	free(str);
	free(cur_value);
}

bool SubstringIterator::has_next() const
{
	return current_end != current_start;
}

const char* SubstringIterator::next()
{
	if (current_end == current_start)
	{
		return nullptr;
	}

	current_end--;
	if (current_end != current_start)
	{
		return create_current();
	}

	current_start++;
	current_end = str + len;

	if (current_end == current_start)
	{
		return nullptr;
	}

	return create_current();
}


const char *SubstringIterator::create_current()
{
	char *dest = cur_value;
	char *src = current_start;


	while (src != current_end)
	{
		*(dest++) = *(src++);
	}

	*dest = '\0';

	return cur_value;
}

int SubstringIterator::offset()
{
	return current_start - str;
}

const char* SubstringIterator::current()
{
	return cur_value;
}
