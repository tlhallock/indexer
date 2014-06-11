/*
 * Indexer.cc
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "index/Indexer.h"

#include "include/export.h"

static void encountered_token(const char *token, FileOffset offset, FileId file, WordAccumulator &accum)
{
	get_index_entry_cache().get_index_entry(token).add_file(file);
	if (get_settings().should_index_files())
	{
		accum.append(token, offset);
	}

	if (!get_settings().should_index_substrings())
	{
		get_strings_list().add(token);
		return;
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
	std::cout << "Number of entries in the String List: " << get_strings_list().count() << std::endl;
	std::cout << "Number of entries in the exp index: " << get_exp_index().count() << std::endl;

	static int count;
	static FILE *plot;
	if (plot == nullptr)
	{
		plot = fopen("plot.txt", "w");
	}
	if (!(count++ % 100))
	{
		fprintf(plot, "%d %d; ...\n", count++, get_exp_index().count());
		fflush(plot);
	}

	std::cout << (count / 733810.0) << std::endl;
}

static void index_function(int len, const char *path)
{
	index(path);
}

void index_all(const char *directory)
{
	recurse_all_children(directory, &index_function);
}
