/*
 * SubstringIndex.h
 *
 *  Created on: Jun 4, 2014
 *      Author: thallock
 */

#ifndef SUBSTRINGINDEX_H_
#define SUBSTRINGINDEX_H_

#include "include/common.h"

class StringListIterator;

class StringList
{
	friend class StringListIterator;
public:
	StringList(std::string *str, StringList *next);
	~StringList();

	bool contains(std::string *str) const;
	void print() const;
private:
	std::string *str;
	StringList *next;
};

class StringListIterator
{
public:
	StringListIterator(std::string str, StringList *first);
	~StringListIterator();

	bool has_next() const;
	const char *next;
private:
	void search();

	std::string str;
	StringList *current;
};

class SubstringIndex
{
public:
	SubstringIndex(int n);
	~SubstringIndex();

	void add(const char *word);
	StringListIterator *iterator(const char *word) const;

	void print() const;
	int count() const;
private:
	int n;
	boost::unordered_map<std::string, std::pair<int, StringList *>> cache;
};

SubstringIndex &get_exp_index();

#endif /* SUBSTRINGINDEX_H_ */
