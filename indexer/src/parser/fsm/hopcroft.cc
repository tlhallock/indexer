/*
 * hopcroft.cc
 *
 *  Created on: Jun 20, 2014
 *      Author: thallock
 */

#include "parser/fsm/hopcroft.h"

#include <set>

typedef std::set<int> partition;

static std::set<partition *> *get_initial_set(DFS *dfs, partition *f)
{
	std::set<partition *> *ret_val = new std::set<partition *>;

	bool *accepting = dfs->get_accepting();

	partition *q = new partition;

	int old_size = dfs->get_num_states();
	for (int i = 0; i < old_size; i++)
	{
		if (accepting[i])
		{
			f->insert(i);
		}
		else
		{
			q->insert(i);
		}
	}

	ret_val->insert(f);
	ret_val->insert(q);

	return ret_val;
}

partition *cap(partition *X, partition *Y)
{
	partition *ret = new partition;

	auto xend = X->end();
	auto yend = Y->end();
	for (auto it = X->begin(); it != xend; ++it)
	{
		if (Y->find(*it) == yend)
		{
			continue;
		}
		ret->insert(*it);
	}

	return ret;
}

partition *mod(partition *X, partition *Y)
{
	partition *ret = new partition;

	ret->insert(X->begin(), X->end());

	auto yend = Y->end();
	auto xend = X->end();

	for (auto it = Y->begin(); it != yend; ++it)
	{
		auto location = ret->find(*it);
		if (location == ret->end())
		{
			continue;
		}
		ret->erase(location);
	}

	return ret;
}


#if 0
static bool is_Y(partition *X, partition *Y)
{
	// X \cap Y =/= {}
	// Y \ X =/= {}
	bool c1 = false;
	bool c2 = false;

	auto end = Y->states.end();
	for (auto it = Y->states.begin(); it != end; ++it)
	{
		bool contained_in_X = X->states.find(*it) != X->states.end();
		if (contained_in_X)
		{
			c1 = true;
		}
		else
		{
			c2 = true;
		}

		if (c1 && c2)
		{
			return true;
		}
	}

	return false;
}
#endif

DFS *hapcroft(DFS *dfs)
{
	// Algorithm taken from en.wikipedia.org/wiki/DFA_minimization
	int num_states = dfs->num_states();

	partition *f = new partition;
	// P := {F, Q \ F};
	std::set<partition*> *P = get_initial_set(dfs, f);
	// W := {F};
	std::set<partition*> *W = new std::set<partition>;
	W->insert(f);


	// while (W is not empty) do
	while (W->size() != 0)
	{
		//  choose and remove a set A from W
		partition *A = *W->begin();
		W->erase(W->begin());

		// for each c in ∑ do
		for (int c = 0; c < kNumChars; c++)
		{
			// let X be the set of states for which a transition on c leads to a state in A
			partition *X = new partition;
			for (int i = 0; i < num_states; i++)
			{
				if (A->find(dfs->get_delta()[c][i]) != A->end())
				{
					X->insert(i);
				}
			}

			// for each set Y in P
			for (auto it = P->begin(); it != P->end(); ++it)
			{
				partition *Y = *it;

				// for which X ∩ Y is nonempty and Y \ X is nonempty do
				partition *inter = cap(X, Y);
				if (inter->size() == 0)
				{
					delete inter;
					continue;
				}

				partition *m = mod(Y, X);
				if (m->size() == 0)
				{
					delete m;
					delete inter;
					continue;
				}

				//replace Y in P by the two sets X ∩ Y and Y \ X
				*it = inter;
				P->insert(m);

				// if Y is in W
				auto yit = W->find(Y); // obviously not right now...
				if (yit == W->end())
				{
					// replace Y in W by the same two sets
				}
				else
				{
					// if |X ∩ Y| <= |Y \ X|
					if (inter->size() <= m->size())
					{
						// add X ∩ Y to W
						W->insert(inter);
					}
					else
					{
						// add Y \ X to W
						W->insert(m);
					}
				}
				delete Y;
			}
		}
	}

	int new_size = P->size();
	int **new_delta = create_delta(new_size);
	for (int i = 0; i < new_size; i++)
	{

	}


	DFS *ret = new DFS(new_size, delta, ...);

	return ret;
}
