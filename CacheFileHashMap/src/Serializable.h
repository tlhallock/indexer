/*
 * Serializable.h
 *
 *  Created on: May 29, 2014
 *      Author: thallock
 */

#ifndef SERIALIZABLE_H_
#define SERIALIZABLE_H_

#include <stdio.h>

class Serializable
{
public:
	Serializable() {};
	virtual ~Serializable() {};

	virtual void write(FILE *out) const = 0;
	virtual void read(FILE *in) = 0;
};

#endif /* SERIALIZABLE_H_ */
