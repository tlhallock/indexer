/*
 * Repitition.cpp
 *
 *  Created on: Jun 6, 2014
 *      Author: thallock
 */

#include <parser/regs/Repitition.h>

Repitition::Repitition(Regex *child_ ) : child(child_) {}
Repitition::~Repitition()
{
	delete child;
}

NFA* Repitition::create() const
{
	NFA *nfa = child->create();

	nfa->get_start()->add(EPSILON, nfa->get_accepting());
	nfa->get_accepting()->add(EPSILON, nfa->get_start());

	return nfa;
}
