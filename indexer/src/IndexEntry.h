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

class IndexEntryIterater
{
public:
	IndexEntryIterater(const char *word);
	~IndexEntryIterater();

	file_id next();
	int get_num_left();
private:
	int num_left;
	FILE *in;
};

class IndexEntry
{
public:
	IndexEntry(const char *word);
	virtual ~IndexEntry();

	void add_file(file_id file);
	void remove_file(file_id file);

	void print_list() const;
	long hash_code() const;

	bool unused();

	void save();
	char *get_file();

	int get_num_refs();
private:

	const char *entry;
	std::set<file_id> files;
};

#endif /* INDEXENTRY_H_ */
