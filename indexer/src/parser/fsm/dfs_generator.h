/*
 * dfs_generator.h
 *
 *  Created on: Jun 19, 2014
 *      Author: thallock
 */

#ifndef DFS_GENERATOR_H_
#define DFS_GENERATOR_H_

#include "parser/fsm/DFS.h"
#include "parser/fsm/FiniteStateMachine.h"

DFS *create_dfs(NFA *nfa);

class dfs_state
{
public:
	dfs_state();
	~dfs_state();

	int get_id();
	void set_id(int _id);

	bool equals(dfs_state *other);

	void fill();
	dfs_state *transition(CHARACTER c);

	void replace(dfs_state *other);

	std::set<state_ptr> states;
	dfs_state *next[256];
	std::set<dfs_state *> references;
	int id;
};

#endif /* DFS_GENERATOR_H_ */
