/*
 * Regex.h
 *
 *  Created on: Jun 6, 2014
 *      Author: thallock
 */

#ifndef REGEX_H_
#define REGEX_H_

#include "parser/fsm/FiniteStateMachine.h"

class Regex
{
public:
	Regex();
	virtual ~Regex();

	virtual NFA *create() const = 0;
};

#endif /* REGEX_H_ */
