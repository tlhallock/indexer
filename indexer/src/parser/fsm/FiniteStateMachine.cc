/*
 * FiniteStateMachine.cc
 *
 *  Created on: Jun 6, 2014
 *      Author: thallock
 */

#include "parser/fsm/FiniteStateMachine.h"

NFA::NFA() :
		start(new State(false)),
		accept(new State(true)),
		states()
{
}

NFA::~NFA()
{
}

state_ptr NFA::get_start() const
{
	return start;
}

void NFA::add_state(state_ptr s)
{
	states.insert(s);
}

state_ptr NFA::get_accepting() const
{
	return accept;
}

void NFA::add_states(const NFA* const other)
{
	auto end = other->states.end();
	for (auto it = other->states.begin(); it != end; ++it)
	{
		states.insert(*it);
	}
}
