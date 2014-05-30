
#ifndef EXPORT_H_
#define EXPORT_H_

#include "common.h"

void escape(const char *in, char *&out, int &out_size);
void descape(const char *in, char *&out, int &out_size);

void index_all(const char *directory);
void recurse_all_children(const char *dir,void (*fctn)(const int, const char *));

bool file_exists(const char *p);
bool directory_exists(const char *p);
FILE *try_to_open(const char *p, const char *perms);
bool ensure_directory(const char *p);
uintmax_t delete_file(const char *p);
uintmax_t delete_directory(const char *p);
bool is_file(const char *p);
bool is_directory(const char *p);
time_t get_last_write_time(const char *p);

#include "Index.h"
#include "DataOutputStream.h"
#include "Query.h"
#include "Tokenizer.h"
#include "IndexedFile.h"
#include "Hash.h"
#include "IndexEntry.h"

#endif
