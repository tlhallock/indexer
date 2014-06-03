/*
 * Indexer.cc
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "index/Indexer.h"

#include "include/export.h"

static void add_word(const char *token, int offset, FileId file, WordAccumulator &accum)
{
	get_index_entry_cache().get_index_entry(token).add_file(file);
	if (!get_settings().should_index_substrings())
	{
		get_strings_list().add(token);
	}
	if (get_settings().should_index_files())
	{
		accum.append(token, offset);
	}
}

static void encountered_token(const char *token, int offset, FileId file, WordAccumulator &accum)
{
	if (!get_settings().should_small_words() && strlen(token) <= 2)
	{
		return;
	}

	if (!get_settings().should_index_substrings())
	{
		add_word(token, offset, file, accum);
		return;
	}

	SubstringIterator subs(token);
	while (subs.has_next())
	{
		add_word(subs.current(), offset + subs.offset(), file, accum);
		subs.next();
	}
}

void index(const char *path)
{
	FileId file = get_file_mapper().get_id(path);
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
		encountered_token(token, t.last_start(), file, accum);
	}

	if (get_settings().should_index_files())
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
