/*
 * DataoutputStream.cpp
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "DataOutputStream.h"

#include "export.h"

DataOutputStream::DataOutputStream(const char *path) :
		file(try_to_open(path, "w")), success(file != nullptr) {}

DataOutputStream::~DataOutputStream()
{
	if (success)
	{
		fclose(file);
	}
}

void DataOutputStream::write(int i)
{
	if (HUMAN_READABLE)
	{
		fprintf(file, "%d\n", i);
	}
	else
	{
		fputc((i >> 0) & 0xff, file);
		fputc((i >> 8) & 0xff, file);
		fputc((i >> 16) & 0xff, file);
		fputc((i >> 24) & 0xff, file);
	}
}

void DataOutputStream::write(long int i)
{
	if (HUMAN_READABLE)
	{
		fprintf(file, "%ld\n", i);
	}
	else
	{
		fputc((i >>  0) & 0xff, file);
		fputc((i >>  8) & 0xff, file);
		fputc((i >> 16) & 0xff, file);
		fputc((i >> 24) & 0xff, file);
		fputc((i >> 32) & 0xff, file);
		fputc((i >> 40) & 0xff, file);
		fputc((i >> 48) & 0xff, file);
		fputc((i >> 56) & 0xff, file);
	}
}

void DataOutputStream::write(const char *str)
{
	if (HUMAN_READABLE)
	{
		fprintf(file, "%s\n", str);
	}
	else
	{
		int len = strlen(str);
		write(len);
		for (int i = 0; i < len; i++)
		{
			fputc(str[i], file);
		}
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
	if (HUMAN_READABLE)
	{
		int ret;
		fscanf(file, "%d", &ret);
		return ret;
	}
	else
	{
		int i = 0;

		i |= (fgetc(file) & 0xff) << 0;
		i |= (fgetc(file) & 0xff) << 8;
		i |= (fgetc(file) & 0xff) << 16;
		i |= (fgetc(file) & 0xff) << 24;

		return i;
	}
}


long int DataInputStream::read_long()
{
	long int ret_val = 0;
	if (HUMAN_READABLE)
	{
		fscanf(file, "%ld", &ret_val);
	}
	else
	{
		ret_val |= (fgetc(file) & 0xffL) <<  0;
		ret_val |= (fgetc(file) & 0xffL) <<  8;
		ret_val |= (fgetc(file) & 0xffL) << 16;
		ret_val |= (fgetc(file) & 0xffL) << 24;

		ret_val |= (fgetc(file) & 0xffL) << 32;
		ret_val |= (fgetc(file) & 0xffL) << 40;
		ret_val |= (fgetc(file) & 0xffL) << 48;
		ret_val |= (fgetc(file) & 0xffL) << 56;
	}
	return ret_val;
}

char *DataInputStream::read_str()
{
	if (HUMAN_READABLE)
	{
		char *ret_val = nullptr;
		size_t size = 0;

		getline(&ret_val, &size, file);
		ret_val[strlen(ret_val) - 1] = '\0';

		return ret_val;
	}
	else
	{
		int len = read_int();
		char *ret_val = (char *) malloc(sizeof(*ret_val) * (len + 1));
		for (int i = 0; i < len; i++)
		{
			ret_val[i] = fgetc(file);
		}
		return ret_val;
	}
}


bool DataInputStream::successful()
{
	return success;
}
