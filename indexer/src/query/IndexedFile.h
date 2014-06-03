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

class IndexedFile;

class OccuranceIterator
{
public:
	OccuranceIterator(FileId file, const char *key);
	OccuranceIterator(const IndexedFile &ifile, const char *key);

	~OccuranceIterator();

	bool has_next() const;
	int next();
private:
	int num;
	int count;
	DataInputStream *in;
};


class IndexedFile
{
public:
	IndexedFile(FileId file_);
	virtual ~IndexedFile();

	void clear();

	bool needs_reindex() const;
	time_t get_last_indexed_time() const;

	const char *get_index_path() const;
	const char *get_index_attr_path() const;
	const char *get_real_path() const;
private:
	FileId file;
	const char *real_path;
	const char *base_dir;
	const char *index_path;
};

//std::shared_ptr<TmpIndexedFile> get_indexed_file(file_id file);

#endif /* INDEXEDFILE_H_ */
