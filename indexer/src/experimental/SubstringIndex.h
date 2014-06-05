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
	boost::unordered_map<std::string, std::set<std::string>> cache;
};

SubstringIndex &get_exp_index();

#endif /* SUBSTRINGINDEX_H_ */
