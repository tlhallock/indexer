/*
 * dfs_generator.cc
 *
 *  Created on: Jun 19, 2014
 *      Author: thallock
 */

dfs_state::dfs_state()
{
	for (int i = 0; i < kNumChars; i++)
	{
		next[i] = nullptr;
	}
}
dfs_state::~dfs_state()
{
}

int dfs_state::get_id()
{
	return id;
}

void dfs_state::set_id(int _id)
{
	id = _id;
}

bool dfs_state::equals(dfs_state *other)
{
	if (other->states.size() != states.size())
	{
		return false;
	}

	auto it1 = states.begin();
	auto it2 = other->states.begin();

	auto end1 = states.end();

	while (it1 != end1)
	{
		if (*it1 != *it2)
		{
			return false;
		}

		++it1;
		++it2;
	}

	return true;
}

void dfs_state::fill()
{
	int orig_size = 0;
	do
	{
		orig_size = states.size();
		std::set<state_ptr> states_cpy(states);

		auto end = states.end();
		for (auto it = states.begin(); it != end; ++it)
		{
			state_ptr ptr = *it;
			std::set<state_ptr> &extras = it->get_states(EPSILON);
			states.insert(extras.begin(), extras.end());
		}
	} while (orig_size != states.size());
}

dfs_state *dfs_state::transition(CHARACTER c)
{
	dfs_state *ret_val = new dfs_state();

	auto end = states.end();
	for (auto it = states.begin(); it != end; ++it)
	{
		state_ptr ptr = *it;
		std::set<state_ptr> &next = ptr->get_states(c);
		states.insert(next.begin(), next.end());
	}

	ret_val->fill();

	ret_val->references.insert(this);
	next[c] = ret_val;

	return ret_val;
}

void dfs_state::replace(dfs_state *other)
{
	auto end = references.end();
	for (auto it = references.begin(); it != references.end(); ++it)
	{
		dfs_state *prev = *it;
		for (int i = 0; i < kNumChars; i++)
		{
			if (prev->next[i] == this)
			{
				prev->next[i] = other;
			}
		}
	}
}




























int get_id(const std::vector<dfs_state *> &discovered, dfs_state *state)
{
	for (int i = 0; i < discovered.size(); i++)
	{
		if (state->equals(discovered.at(i)))
		{
			return i;
		}
	}
	return -1;
}


DFS *create_dfs(NFA *nfa)
{
	std::vector<dfs_state *> horizon;
	std::vector<dfs_state *> discovered;

	dfs_state *reject = new dfs_state;
	horizon.push_back(reject);

	dfs_state *start = new dfs_state;
	start->states.insert(nfa->get_start());
	start->fill();
	horizon.push_back(start);

	while (horizon.size() != 0)
	{
		dfs_state *next = *horizon.begin();
		horizon.erase(horizon.begin());

		int id = get_id(discovered, next);
		if (id >= 0)
		{
			next->replace(discovered.at(id));

			delete next;
			continue;
		}

		next->set_id(discovered.size());
		discovered.push_back(next);

		for (int i = 0; i < kNumChars; i++)
		{
			horizon.push_back(next->transition(i));
		}
	}

	int size = discovered.size();
	int **delta = create_delta(size);

	std::set<int> accepting_states;
	state_ptr accepting = nfa->get_accepting();

	for (int id = 0; id < size; id++)
	{
		for (int i = 0; i < kNumChars; i++)
		{
			delta[i][id] = discovered.at(id)->next[i]->get_id();
		}

		std::set<state_ptr> &states = discovered.at(id)->states;
		if (states.find(accepting) == states.end())
		{
			continue;
		}

		accepting_states.insert(id);
	}

	return new DFS(delta, accepting_states);
}
