/*
 * IndexedFile.h
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#ifndef INDEXEDFILE_H_
#define INDEXEDFILE_H_

#include "WordManager.h"

class FilesWordIterator
{
public:
	FilesWordIterator(std::map<const char *, int> &words);
	~FilesWordIterator();

	const char *next();
private:
	std::map<const char *, int>::iterator end;
	std::map<const char *, int>::iterator it;
};




class IndexedFile
{
public:
	IndexedFile(file_id file_);
	virtual ~IndexedFile();

	void append(const char *token);
	void clear();

	void save();

	void reset_indexed_time();
	time_t get_last_indexed_time();

	FilesWordIterator &get_iterater();
private:
	file_id file;
	time_t last_indexed_time;

	int current_tokens;
	std::map<const char *, int> words;
	std::vector<std::set<int>*> orders;
};

std::shared_ptr<IndexedFile> get_indexed_file(file_id file);

#endif /* INDEXEDFILE_H_ */
