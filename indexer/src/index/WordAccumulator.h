/*
 * WordAccumulator.h
 *
 *  Created on: May 31, 2014
 *      Author: thallock
 */

#ifndef WORDACCUMULATOR_H_
#define WORDACCUMULATOR_H_

#include "query/IndexedFile.h"

#include "include/common.h"

class WordAccumulator
{
public:
	WordAccumulator();
	virtual ~WordAccumulator();
};

class TmpIndexedFile
{
public:
	TmpIndexedFile(IndexedFile *f);
	virtual ~TmpIndexedFile();

	void append(const char *token, int offset);
	void save() const;
private:
	std::set<int> *get_index(const char *word);

	IndexedFile *file;
	time_t read_time;

	std::map<const char *, int> words;
	std::vector<std::set<int>*> orders;
};

#endif /* WORDACCUMULATOR_H_ */
