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

class IndexEntryCache;

class IndexEntryIterater
{
public:
	IndexEntryIterater(const char *word);
	IndexEntryIterater(const char *word, const char *path);

	~IndexEntryIterater();

	bool has_next() const;
	file_id next();
	int get_num_left() const;
private:
	void init(const char *word, const char *path);

	int num_left;
	DataInputStream *in;
};

class IndexEntry
{
public:
	friend class IndexEntryCache;

	~IndexEntry();

	void add_file(file_id file);
	void remove_file(file_id file);

	void save() const;

	int get_num_refs() const;
private:
	IndexEntry(const char *token);

	const char *word;
	const char *path;
	std::set<file_id> files;
};

class IndexEntryCache
{
public:
	IndexEntryCache();
	~IndexEntryCache();

	IndexEntry &get_index_entry(const char *token);

	int get_size();

	void flush();
private:
	void clear();
	std::map<const char *, IndexEntry *> entries;
};

IndexEntryCache &get_index_entry_cache();


#endif /* INDEXENTRY_H_ */
