/*
 * SubstringIterator.h
 *
 *  Created on: May 31, 2014
 *      Author: thallock
 */

#ifndef SUBSTRINGITERATOR_H_
#define SUBSTRINGITERATOR_H_

#include "utils/StringIterator.h"

class SubstringIterator : public StringIterator
{
public:
	SubstringIterator(const char *str_);
	SubstringIterator(const char *str_, int min, int max);
	~SubstringIterator();

	bool has_next() const;
	const char *next();

	int next_offset();
	const char *current();
private:
	void search();
	void create_current();

	int len;

	char *str;
	char *cur_value;

	int start;
	int stop;

	int min;
	int max;

	bool done;
};

#endif /* SUBSTRINGITERATOR_H_ */
