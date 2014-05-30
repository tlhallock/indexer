/*
 * DataoutputStream.h
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#ifndef DATAOUTPUTSTREAM_H_
#define DATAOUTPUTSTREAM_H_

#include <stdio.h>

#define HUMAN_READABLE 1

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

	int read_int();
	char *read_str();
	long int read_long();

	bool successful();
private:
	FILE *file;
	bool success;
};

#endif /* DATAOUTPUTSTREAM_H_ */
