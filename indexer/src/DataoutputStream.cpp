/*
 * DataoutputStream.cpp
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "DataOutputStream.h"

#include <cstring>
#include <stdlib.h>


DataOutputStream::DataOutputStream(const char *path) :
		file(fopen(path, "w")), success(file != nullptr) {}

DataOutputStream::~DataOutputStream()
{
	if (success)
	{
		fclose(file);
	}
}

void DataOutputStream::write(int i)
{
	fputc((i >>  0) & 0xff, file);
	fputc((i >>  8) & 0xff, file);
	fputc((i >> 16) & 0xff, file);
	fputc((i >> 24) & 0xff, file);
}

void DataOutputStream::write(const char *str)
{
	int len = strlen(str);
	write(len);
	for (int i = 0; i < len; i++)
	{
		fputc(str[i], file);
	}
}

bool DataOutputStream::successful()
{
	return success;
}


DataInputStream::DataInputStream(const char *path) :
	file(fopen(path, "r")), success(file != nullptr) {}

DataInputStream::~DataInputStream()
{
	if (success)
	{
		fclose(file);
	}
}

int DataInputStream::read_int()
{
	int i = 0;

	i |= (fgetc(file) & 0xff) <<  0;
	i |= (fgetc(file) & 0xff) <<  8;
	i |= (fgetc(file) & 0xff) << 16;
	i |= (fgetc(file) & 0xff) << 24;

	return i;
}

char *DataInputStream::read_str()
{
	int len = read_int();
	char *ret_val = (char *) malloc(sizeof(*ret_val) * (len + 1));
	for (int i = 0; i < len; i++)
	{
		ret_val[i] = fgetc(file);
	}
	return ret_val;
}


bool DataInputStream::successful()
{
	return success;
}
