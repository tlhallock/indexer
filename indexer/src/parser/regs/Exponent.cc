/*
 * Exponent.cc
 *
 *  Created on: Jun 6, 2014
 *      Author: thallock
 */

#include <parser/regs/Exponent.h>

Exponent::Exponent(Regex *child_) : child(child_) {}
Exponent::~Exponent()
{
	delete child;
}

