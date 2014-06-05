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
	~SubstringIterator();

	bool has_next() const;
	const char *next();

	int offset();
	const char *current();
private:
	const char *create_current();

	int len;

	char *str;
	char *current_start;
	char *current_end;

	char *cur_value;
};

#endif /* SUBSTRINGITERATOR_H_ */
