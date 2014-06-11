/*
 * SubstringIndex.h
 *
 *  Created on: Jun 4, 2014
 *      Author: thallock
 */

#ifndef SUBSTRINGINDEX_H_
#define SUBSTRINGINDEX_H_

#include "include/common.h"

#include "utils/StringIterator.h"

class StringListIterator : public StringIterator
{
public:
	StringListIterator(const std::string &str, const std::set<std::string> &set);
	~StringListIterator();

	bool has_next() const;
	const char *next();
private:
	void search();

	std::string str;
	std::set<std::string>::iterator end;
	std::set<std::string>::iterator it;
};

class SuperStringList
{
public:
	SuperStringList(const std::string &key);
	~SuperStringList();

	int get_size() const;
	bool cached() const;

	void add(const std::string &superstring);
	void remove(const std::string &superstring);

	void load();
	void save() const;

	StringListIterator *iterator();

	size_t get_memory_usage() const;
private:
	mutable int size;
	std::set<std::string> *superstrings;

	size_t memory_usage;
	int num_accessed;

	std::string key;
};



class SubstringIndex
{
public:
	SubstringIndex();
	~SubstringIndex();

	void add(const char *word);
	StringListIterator *iterator(const char *word);

	void save() const;
	void read();

	void print() const;
	int count() const;
private:
	std::shared_ptr<SuperStringList> get(const char *key);

	boost::unordered_map<std::string, std::shared_ptr<SuperStringList>> cache;
};

SubstringIndex &get_exp_index();

#endif /* SUBSTRINGINDEX_H_ */
