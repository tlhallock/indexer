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
#include "DataOutputStream.h"

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

class IndexEntry
{
public:
	IndexEntry(const char *word);
	virtual ~IndexEntry();

	void add_file(file_id file);
	void remove_file(file_id file);

	void print_list() const;
	long hash_code() const;

	bool is_unused() const;

	void save() const;
	char *get_file() const;

	int get_num_refs() const;
private:

	const char *entry;
	std::set<file_id> files;
};

#endif /* INDEXENTRY_H_ */
