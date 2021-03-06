/*
 * State.cpp
 *
 *  Created on: Jun 6, 2014
 *      Author: thallock
 */

#include "parser/fsm/State.h"

State::State() : accepting(false) {}
State::State(bool accepting_) : accepting(accepting_) {}
State::~State() {}

void State::add(CHARACTER c, state_ptr next)
{
	get_states(c).insert(next);
}

bool State::is_accepting() const
{
	return accepting;
}

void State::set_accepting(bool accepting_)
{
	accepting = accepting_;
}

#define stat_ptr int

std::set<state_ptr>& State::get_states(CHARACTER transition)
{
	std::map<CHARACTER, std::set<state_ptr>>::iterator it = transitions.find(transition);
	if (it == transitions.end())
	{
		std::set<state_ptr> *s = new std::set<state_ptr>;
		return *s;
//		return nullptr; //std::set<state_ptr>;
	}
	return it->second;
}
