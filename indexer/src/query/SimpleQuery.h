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

class FileListQuery : public Query
{
public:
	FileListQuery(const char *word);
	virtual ~FileListQuery();

	bool has_next();
	void next();
	void display();
private:
	file_id current;
	IndexEntryIterater it;
};

class FileOffsetListQuery : public Query
{
public:
	FileOffsetListQuery(const char *word);
	virtual ~FileOffsetListQuery();

	bool has_next();
	void next();
	void display();
private:
	const char *word;

	file_id current_file;
	int current_offset;

	IndexEntryIterater oit;
	OccuranceIterator *iit;
};

#endif /* SIMPLEQUERY_H_ */
