/*
 * Indexer.cc
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "export.h"

void index(file_id file)
{
//	fprintf(stdout, "Indexing %s\n", get_file_manager().get_location(file));

	Tokenizer t{file};

	WordManager &wmanager = get_word_manager();
	std::unique_ptr<IndexedFile> ifile = get_indexed_file(file);
	ifile->clear();

	const char *token = NULL;
	while ((token = t.next()) != NULL)
	{
		word_id id = wmanager.get_word(token);
		get_entry(id).add_file(file);
		ifile->append(id);
	}

	ifile->reset_indexed_time();
}

static void index_function(int len, const char *path)
{
	index(get_file_manager().get_id(path));
}

void index_all(const char *directory)
{
	recurse_all_children(directory, &index_function);
}
