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
	file_id file = get_file_mapper().get_id(path);
	if (file == INVALID_FILE)
	{
		return;
	}

	fprintf(stdout, "Indexing %d: %s\n", file, path);

	IndexedFile ifile(file);
	if (!ifile.needs_reindex())
	{
		return;
	}

	WordAccumulator accum(&ifile);

	Tokenizer t{file};
	const char *token = nullptr;
	while ((token = t.next()) != nullptr)
	{
		if (!get_settings().include_small_words() && strlen(token) <= 2)
		{
			continue;
		}

		get_index_entry_cache().get_index_entry(token).add_file(file);

		if (!get_settings().index_files())
		{
			continue;
		}

		if (!get_settings().use_massive_storage())
		{
			accum.append(token, 13);
			continue;
		}

		SubstringIterator subs(token);
		while (subs.has_next())
		{
			accum.append(subs.current(), subs.offset());
			subs.next();
		}
	}

	if (get_settings().index_files())
	{
		accum.save();
	}
	get_index_entry_cache().flush();

	std::cout << "Number of entries in the IndexEntryCache: " << get_index_entry_cache().get_size() << std::endl;
}

static void index_function(int len, const char *path)
{
	index(path);
}

void index_all(const char *directory)
{
	recurse_all_children(directory, &index_function);
}
