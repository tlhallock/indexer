/*
 * StringsList.h
 *
 *  Created on: Jun 3, 2014
 *      Author: thallock
 */

#ifndef STRINGSLIST_H_
#define STRINGSLIST_H_

#include "include/common.h"

#include "utils/StringIterator.h"

class StringsList;

class SuperStringIterator : public StringIterator
{
	friend class StringsList;
public:
	~SuperStringIterator();

	bool has_next() const;
	const char *next();

	const char *get_query();
private:
	SuperStringIterator(std::vector<std::string> &words, const char *string);

	void search();

	const char *string;
	const char *current;

	std::vector<std::string>::iterator it;
	std::vector<std::string>::iterator end;
};

class StringsList
{
public:
	StringsList();
	~StringsList();

	void add(const char *string);
	SuperStringIterator *iterator(const char *string);

	int count() const;

	void clear();
private:
	std::vector<std::string> words;
};

StringsList &get_strings_list();

#endif /* STRINGSLIST_H_ */
