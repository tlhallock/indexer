/*
 * Sequence.h
 *
 *  Created on: Jun 6, 2014
 *      Author: thallock
 */

#ifndef SEQUENCE_H_
#define SEQUENCE_H_

#include <parser/regs/Regex.h>

class Sequence: public Regex
{
public:
	Sequence();
	virtual ~Sequence();

	void add(Regex *regex);

	NFA *create() const;
private:
	std::vector<Regex *> regs;
};

#endif /* SEQUENCE_H_ */
