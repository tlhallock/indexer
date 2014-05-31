/*
 * boost_file_utils.h
 *
 *  Created on: May 31, 2014
 *      Author: thallock
 */

#ifndef BOOST_FILE_UTILS_H_
#define BOOST_FILE_UTILS_H_

#include "include/common.h"

bool file_exists(const char *p);
bool directory_exists(const char *p);
FILE *try_to_open(const char *p, const char *perms);
bool ensure_directory(const char *p);
uintmax_t delete_file(const char *p);
uintmax_t delete_directory(const char *p);
bool is_file(const char *p);
bool is_directory(const char *p);
time_t get_last_write_time(const char *p);

#endif /* BOOST_FILE_UTILS_H_ */
