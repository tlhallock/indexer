/*
 * FiniteStateMachine.h
 *
 *  Created on: Jun 6, 2014
 *      Author: thallock
 */

#ifndef FINITESTATEMACHINE_H_
#define FINITESTATEMACHINE_H_

#include "parser/fsm/State.h"

class NFA
{
public:
	NFA();
	~NFA();

	state_ptr get_start() const;
	state_ptr get_accepting() const;

	void add_state(state_ptr s);
	void add_states(const NFA *const other);
private:
	state_ptr start;
	state_ptr accept;
	std::set<state_ptr> states;
};

#endif /* FINITESTATEMACHINE_H_ */
