/*
 * Optional.h
 *
 *  Created on: Jun 6, 2014
 *      Author: thallock
 */

#ifndef OPTIONAL_H_
#define OPTIONAL_H_

#include <parser/regs/Regex.h>

class Optional: public Regex
{
public:
	Optional(Regex *regex);
	virtual ~Optional();

	NFA *create() const;
private:
	Regex *regex;
};

#endif /* OPTIONAL_H_ */
