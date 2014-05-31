
#ifndef EXPORT_H_
#define EXPORT_H_

#include "common.h"

void escape(const char *in, char *&out, int &out_size);
void descape(const char *in, char *&out, int &out_size);

void index_all(const char *directory);
void recurse_all_children(const char *dir,void (*fctn)(const int, const char *));

#include "Index.h"
#include "DataOutputStream.h"
#include "Query.h"
#include "Tokenizer.h"
#include "IndexedFile.h"
#include "Hash.h"
#include "IndexEntry.h"
#include "SubstringIterator.h"
#include "boost_file_utils.h"

#endif
