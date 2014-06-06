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
	WordAccumulator(IndexedFile *f);
	virtual ~WordAccumulator();

	void append(const char *token, FileOffset offset);
	void save() const;
private:
	std::set<FileOffset> *get_index(const char *word);

	IndexedFile *file;
	time_t read_time;

	boost::unordered_map<std::string, int> words;
	std::vector<std::set<FileOffset>*> orders;
};

#endif /* WORDACCUMULATOR_H_ */
