/*
 * SubstringIterator.h
 *
 *  Created on: May 31, 2014
 *      Author: thallock
 */

#ifndef SUBSTRINGITERATOR_H_
#define SUBSTRINGITERATOR_H_

class SubstringIterator
{
public:
	SubstringIterator(const char *str_);
	virtual ~SubstringIterator();

	bool has_next();
	const char *next();

	int offset();
	const char *current();
private:
	const char *create_current();

	int len;

	char *str;
	char *cs;
	char *ce;

	char *cur_value;
};

#endif /* SUBSTRINGITERATOR_H_ */
