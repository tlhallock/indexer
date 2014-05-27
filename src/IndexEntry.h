/*
 * IndexEntry.h
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#ifndef INDEXENTRY_H_
#define INDEXENTRY_H_

#include "FileManager.h"
#include "WordManager.h"

class IndexEntry
{
	word_id entry;
	std::set<file_id> files;
public:
	IndexEntry(word_id word);
	virtual ~IndexEntry();

	void add_file(file_id file);
	void remove_file(file_id file);

	bool contains(const char *query) const;
	void print_list() const;

	void save();
};

#endif /* INDEXENTRY_H_ */
