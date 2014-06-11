/*
 * Or.h
 *
 *  Created on: Jun 6, 2014
 *      Author: thallock
 */

#ifndef OR_H_
#define OR_H_

#include "parser/regs/Regex.h"

#include <vector>

class Or : public Regex
{
public:
	Or();
	virtual ~Or();

	void add(Regex *child);

	NFA* create() const;
private:
	std::vector<Regex *> children;
};

#endif /* OR_H_ */
