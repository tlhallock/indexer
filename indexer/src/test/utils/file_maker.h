/*
 * file_maker.h
 *
 *  Created on: Jun 6, 2014
 *      Author: thallock
 */

#ifndef FILE_MAKER_H_
#define FILE_MAKER_H_

#include "include/common.h"

const char *alpha_numeric = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const char *delims = get_settings().get_delims();
const char *all_chars = concatenate(alpha_numeric, delims);

void write_delims(FILE *out, int num, const char *ignore = nullptr, std::set<std::string> *nosubs = nullptr);
void write_alpha_numeric(FILE *out, int num, const char *ignore = nullptr, std::set<std::string> *nosubs = nullptr);
void write_binary(FILE *out, int num);
void write_ad(FILE *out, int num, const char *ignore = nullptr, std::set<std::string> *nosubs = nullptr);

bool create_random_file(const char *path, FileOffset length, std::set<std::string> *nosubs = nullptr);

char *create_random_alphanumeric_string(int len, const char *ignore = nullptr);
char *create_random_delim_string(int len, const char *ignore = nullptr);
char *create_random_ad_string(int len, const char *ignore = nullptr);
char *create_random_binary_string(int len, const char *ignore = nullptr);

bool file_contains(std::string path, const char *substring);
void grep_files(std::string dir_path, const char *substring, std::set<std::string> &out_paths);



#endif /* FILE_MAKER_H_ */
