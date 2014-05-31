/*
 * IndexEntry.h
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#ifndef INDEXENTRY_H_
#define INDEXENTRY_H_

#include "include/common.h"

#include "utils/DataOutputStream.h"

class IndexEntryIterater
{
public:
	IndexEntryIterater(const char *word);
	~IndexEntryIterater();

	bool has_next() const;
	file_id next();
	int get_num_left() const;
private:
	int num_left;
	DataInputStream *in;
};

#endif /* INDEXENTRY_H_ */
