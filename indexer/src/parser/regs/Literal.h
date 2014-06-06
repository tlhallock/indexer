/*
 * Literal.h
 *
 *  Created on: Jun 6, 2014
 *      Author: thallock
 */

#ifndef LITERAL_H_
#define LITERAL_H_

#include "parser/regs/Regex.h"

class Literal: public Regex
{
public:
	Literal(CHARACTER c);
	virtual ~Literal();

	NFA *create() const;
private:
	CHARACTER c;
};

#endif /* LITERAL_H_ */
