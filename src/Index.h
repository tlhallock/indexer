/*
 * Index.h
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#ifndef INDEX_H_
#define INDEX_H_

#include "IndexEntry.h"

double query(const char* query);


std::shared_ptr<IndexEntry> get_index_entry(const char *token);

#endif
