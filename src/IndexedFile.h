/*
 * IndexedFile.h
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#ifndef INDEXEDFILE_H_
#define INDEXEDFILE_H_

#include "FileManager.h"
#include "WordManager.h"

class IndexedFile
{
public:
	IndexedFile(file_id file_);
	virtual ~IndexedFile();

	void append(word_id id);
	void clear();

	void save();

	void reset_indexed_time();
	time_t get_last_indexed_time();
private:
	file_id file;
	time_t last_indexed_time;
	std::vector<int> words;
};

std::unique_ptr<IndexedFile> get_indexed_file(file_id file);

#endif /* INDEXEDFILE_H_ */
