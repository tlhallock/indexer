/*
 * StringIterator.h
 *
 *  Created on: Jun 4, 2014
 *      Author: thallock
 */

#ifndef STRINGITERATOR_H_
#define STRINGITERATOR_H_

class StringIterator
{
public:
	StringIterator();
	virtual ~StringIterator();

	virtual bool has_next() const = 0;
	virtual const char *next() = 0;
};

#endif /* STRINGITERATOR_H_ */
