/*
 * Sequence.cc
 *
 *  Created on: Jun 6, 2014
 *      Author: thallock
 */

#include <parser/regs/Sequence.h>

Sequence::Sequence() {}
Sequence::~Sequence() {}

void Sequence::add(Regex* regex)
{
	regs.push_back(regex);
}

NFA* Sequence::create() const
{
	NFA *nfa = new NFA();

	state_ptr current(nfa->get_start());

	auto end = regs.end();
	for (auto it = regs.begin(); it != end; ++it)
	{
		NFA *child_nfa = (*it)->create();

		current->add(EPSILON, child_nfa->get_start());
		current = child_nfa->get_accepting();

		delete child_nfa;
	}

	return nfa;
}
