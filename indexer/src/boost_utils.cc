/*
 * boost_utils.cc
 *
 *  Created on: May 30, 2014
 *      Author: thallock
 */

#include "export.h"

#include <stdio.h>
#include <iostream>

#include <boost/filesystem.hpp>

bool file_exists(const char *p)
{
	return is_file(p);
}

bool directory_exists(const char *p)
{
	return is_directory(p);
}

FILE *try_to_open(const char *p, const char *perms)
{
	boost::filesystem::path pa(p);
	ensure_directory(pa.parent_path().generic_string().c_str());
	return fopen(p, perms);
}

bool ensure_directory(const char *p)
{
	if (file_exists(p))
	{
		printf("Trying to create directory '%s' when a file by that name already exists!", p);
		exit(0);
	}

	if (directory_exists(p))
	{
		return true;
	}

	boost::filesystem::path pa(p);
	return boost::filesystem::create_directories(pa);
}

uintmax_t delete_file(const char *p)
{
	return delete_directory(p);
}

uintmax_t delete_directory(const char *p)
{
	boost::filesystem::path pa(p);
	return boost::filesystem::remove_all(pa);
}

bool is_file(const char *p)
{
	return boost::filesystem::exists(p) && boost::filesystem::is_regular_file(p);
}

bool is_directory(const char *p)
{
	return boost::filesystem::exists(p) && boost::filesystem::is_directory(p);
}

time_t get_last_write_time(const char *p)
{
	if (!file_exists(p))
	{
		return (time_t) -1;
	}
	boost::filesystem::path pa(p);
	return boost::filesystem::last_write_time(pa);
}
