/*
 * Exponent.h
 *
 *  Created on: Jun 6, 2014
 *      Author: thallock
 */

#ifndef EXPONENT_H_
#define EXPONENT_H_

#include <parser/regs/Regex.h>

class Exponent: public Regex
{
public:
	Exponent(Regex *child);
	virtual ~Exponent();
private:
	Regex *child;
	int min;
	int max;
};

#endif /* EXPONENT_H_ */
