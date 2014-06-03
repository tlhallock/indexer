/*
 * SimpleQuery.h
 *
 *  Created on: May 31, 2014
 *      Author: thallock
 */

#ifndef SIMPLEQUERY_H_
#define SIMPLEQUERY_H_

#include "query/Query.h"
#include "query/IndexEntry.h"
#include "query/IndexedFile.h"

class FileListQueryResults : public QueryResults
{
public:
	FileListQueryResults(FileId file_);
	~FileListQueryResults();

	void display() const;
private:
	FileId file;
};

class FileListQuery : public Query
{
public:
	FileListQuery(const char *word);
	virtual ~FileListQuery();

	bool has_next() const;
	const QueryResults &next();
private:
	FileListQueryResults current;
	IndexEntryIterater it;
};


class FileOffsetListQueryResults : public QueryResults
{
public:
	FileOffsetListQueryResults(FileId file_, int offset_);
	~FileOffsetListQueryResults();

	void display() const;

	void set_file(int file_);
	void set_offset(int offset_);
private:
	FileId file;
	int offset;
};

class FileOffsetListQuery : public Query
{
public:
	FileOffsetListQuery(const char *word);
	virtual ~FileOffsetListQuery();

	bool has_next() const;
	const QueryResults &next();
private:
	const char *word;

	FileOffsetListQueryResults current;

	IndexEntryIterater oit;
	OccuranceIterator *iit;
};

#endif /* SIMPLEQUERY_H_ */
