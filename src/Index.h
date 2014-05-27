/*
 * Index.h
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#ifndef INDEX_H_
#define INDEX_H_

#include "IndexEntry.h"

IndexEntry &get_entry(word_id id);
double query(const char* query);

#endif
