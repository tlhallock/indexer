/*
 * Literal.cpp
 *
 *  Created on: Jun 6, 2014
 *      Author: thallock
 */

#include <parser/regs/Literal.h>

Literal::Literal(CHARACTER c_) : c(c_) {}
Literal::~Literal() {}

NFA* Literal::create() const
{
	NFA *fsm = new NFA();
	fsm->get_start()->add(c, fsm->get_accepting());
	return fsm;
}
