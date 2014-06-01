/*
 * DataoutputStream.h
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#ifndef DATAOUTPUTSTREAM_H_
#define DATAOUTPUTSTREAM_H_

#include "include/common.h"

class UnexpectedInputException : public std::exception
{
public:
	UnexpectedInputException(const char *description_) :
		description(strdup(description_)) {}

	~UnexpectedInputException()
	{
		free(description);
	}

	const char *get_description()
	{
		return description;
	}
private:
	char *description;
};

class DataOutputStream
{
public:
	DataOutputStream(const char *path);
	~DataOutputStream();

	void write(int i);
	void write(const char *str);
	void write(long int i);

	bool successful();
private:
	FILE *file;
	bool success;
};

class DataInputStream
{
public:
	DataInputStream(const char *path);
	~DataInputStream();

	int read_int() throw (UnexpectedInputException);
	char *read_str() throw (UnexpectedInputException);
	long int read_long() throw (UnexpectedInputException);

	bool successful();
private:
	const char *path;
	FILE *file;
	bool success;
};

#endif /* DATAOUTPUTSTREAM_H_ */
