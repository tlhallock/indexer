/*
 * Indexer.cc
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "index/Indexer.h"

#include "include/export.h"

void index(const char *path)
{
	file_id file = get_file_manager().get_id(path);
	fprintf(stdout, "Indexing %d: %s\n", file, path);

	IndexedFile ifile(file);
	if (!ifile.needs_reindex())
	{
		return;
	}

	WordAccumulator accum(&ifile);

	Tokenizer t{file};
	const char *token = NULL;
	while ((token = t.next()) != NULL)
	{
		SubstringIterator subs(token);
		get_index_entry_cache().get_index_entry(token).add_file(file);

		while (subs.has_next())
		{
			accum.append(subs.current(), subs.offset());
			subs.next();
		}
	}

	accum.save();
	get_index_entry_cache().flush();
}

static void index_function(int len, const char *path)
{
	index(path);
}

void index_all(const char *directory)
{
	recurse_all_children(directory, &index_function);
}
