
#ifndef EXPORT_H_
#define EXPORT_H_

#include "include/common.h"

#include "index/FileManager.h"
#include "index/Indexer.h"
#include "index/SubstringIterator.h"
#include "index/Tokenizer.h"
#include "index/WordAccumulator.h"

#include "query/IndexedFile.h"
#include "query/IndexEntry.h"
#include "query/SimpleQuery.h"
#include "query/Query.h"

#include "test/tests.h"

#include "utils/boost_file_utils.h"
#include "utils/DataOutputStream.h"
#include "utils/Hash.h"

void escape(const char *in, char *&out, int &out_size);
void descape(const char *in, char *&out, int &out_size);

void recurse_all_children(const char *dir, void (*fctn)(const int, const char *));

#endif
