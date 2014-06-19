/*
 * DFS.h
 *
 *  Created on: Jun 6, 2014
 *      Author: thallock
 */

#ifndef DFS_H_
#define DFS_H_

#include <set>

#define STATE_BAD_STATE (-1)

constexpr int kNumChars = (2 * 26 + 10 + strlen(get_settings().get_delims()));

class DFS
{
public:
	DFS(int **delta, const std::set<int> &accept_states);
	virtual ~DFS();

	bool accepting() const;
	void next(char c);

private:
	int state;
	int **delta;

	std::set<int> accept_states;
};

int **create_delta(int num_states);
int get_index(CHARACTER c);


#endif /* DFS_H_ */
