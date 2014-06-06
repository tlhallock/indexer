/*
 * IndexedFile.h
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#ifndef INDEXEDFILE_H_
#define INDEXEDFILE_H_

#include "include/common.h"

#include "utils/DataOutputStream.h"
#include "index/Tokenizer.h"

class IndexedFile;


class OccuranceIterator
{
public:
	OccuranceIterator();
	virtual ~OccuranceIterator();

	virtual bool has_next() const = 0;
	virtual FileOffset next() = 0;
};

class IndexedOccuranceIterator : public OccuranceIterator
{
public:
	IndexedOccuranceIterator(FileId file, const char *key);
	~IndexedOccuranceIterator();

	bool has_next() const;
	FileOffset next();
private:
	int num;
	int count;
	std::unique_ptr<DataInputStream> in;
};

class OriginalOccuranceIterator : public OccuranceIterator
{
public:
	OriginalOccuranceIterator(FileId file, const char *key);
	~OriginalOccuranceIterator();

	bool has_next() const;
	FileOffset next();
private:
	void search();

	const char *query;
	Tokenizer original;
	bool done;
	int current_substring_offset;
};

OccuranceIterator *create_occurance_iterator(FileId file, const char *key);

class IndexedFile
{
public:
	IndexedFile(FileId file_);
	~IndexedFile();

	void clear();

	bool needs_reindex() const;
	time_t get_last_indexed_time() const;

	const char *get_real_path() const;
private:
	FileId file;
	const char *real_path;
};

//std::shared_ptr<TmpIndexedFile> get_indexed_file(file_id file);

#endif /* INDEXEDFILE_H_ */
