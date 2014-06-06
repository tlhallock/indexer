/*
 * Or.cpp
 *
 *  Created on: Jun 6, 2014
 *      Author: thallock
 */

#include "parser/regs/Or.h"

Or::Or() {}
Or::~Or() {}

void Or::add(Regex* child)
{
	children.push_back(child);
}

NFA* Or::create() const
{
	NFA *nfa = new NFA();

	state_ptr start(nfa->get_start());
	state_ptr end(nfa->get_accepting());

	auto iend = children.end();
	for (auto it = children.begin(); it != iend; ++it)
	{
		NFA *child_nfa = (*it)->create();

		start->add(EPSILON, child_nfa->get_start());
		child_nfa->get_accepting()->add(EPSILON, start);

		delete child_nfa;
	}

	return nfa;
}
