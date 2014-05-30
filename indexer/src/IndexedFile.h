/*
 * IndexedFile.h
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#ifndef INDEXEDFILE_H_
#define INDEXEDFILE_H_

#include "WordManager.h"
#include "DataOutputStream.h"

class FilesWordIterator
{
public:
	FilesWordIterator(std::map<const char *, int> &words);
	~FilesWordIterator();

	bool has_next() const;
	const char *next();
private:
	std::map<const char *, int>::iterator end;
	std::map<const char *, int>::iterator it;
};


class OccuranceIterator
{
public:
	OccuranceIterator(file_id file, const char *key);
	~OccuranceIterator();

	bool has_next();
	int next();
private:
	int num;
	int count;
	DataInputStream *in;
};





class TmpIndexedFile
{
public:
	TmpIndexedFile(file_id file_);
	virtual ~TmpIndexedFile();

	void append(const char *token);
	void clear();

	char *get_index_path() const;
	char *get_index_attr_path() const;
	void save() const;

	time_t get_last_indexed_time() const;

	FilesWordIterator &get_iterater() const;

	bool needs_reindex() const;
private:
	void free_mem();
	file_id file;
	time_t read_time;

	int current_tokens;
	std::map<const char *, int> words;
	std::vector<std::set<int>*> orders;
};

//std::shared_ptr<TmpIndexedFile> get_indexed_file(file_id file);

#endif /* INDEXEDFILE_H_ */
