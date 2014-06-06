/*
 * Repitition.h
 *
 *  Created on: Jun 6, 2014
 *      Author: thallock
 */

#ifndef REPITITION_H_
#define REPITITION_H_

#include "parser/regs/Regex.h"

class Repitition : public Regex
{
public:
	Repitition(Regex *child_);
	virtual ~Repitition();

	NFA *create() const;
private:
	Regex *child;
};

#endif /* REPITITION_H_ */
