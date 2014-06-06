/*
 * Optional.cpp
 *
 *  Created on: Jun 6, 2014
 *      Author: thallock
 */

#include "parser/regs/Optional.h"

Optional::Optional(Regex *regex_) : regex(regex_) {}
Optional::~Optional()
{
	delete regex;
}

