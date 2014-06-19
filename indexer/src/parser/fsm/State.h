/*
 * State.h
 *
 *  Created on: Jun 6, 2014
 *      Author: thallock
 */

#ifndef STATE_H_
#define STATE_H_

#include <set>
#include <map>
#include <memory>
#include <bits/shared_ptr.h>

typedef int CHARACTER;
#define EPSILON 257

class State;
typedef std::shared_ptr<State> state_ptr;

class State
{
public:
	State();
	State(bool accepting);
	virtual ~State();

	void add(CHARACTER c, state_ptr next);

	bool is_accepting() const;
	void set_accepting(bool accepting);

	std::set<state_ptr> &get_states(CHARACTER transition);
private:

	bool accepting;
	std::map<CHARACTER, std::set<state_ptr>> transitions;
};


#endif /* STATE_H_ */
