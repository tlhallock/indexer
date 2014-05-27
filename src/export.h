
#ifndef EXPORT_H_
#define EXPORT_H_

#include "common.h"

#include "Index.h"
#include "DataOutputStream.h"
#include "Query.h"
#include "Tokenizer.h"
#include "IndexedFile.h"

void index_all(const char *directory);
void recurse_all_children(const char *dir,void (*fctn)(const int, const char *));

#endif
