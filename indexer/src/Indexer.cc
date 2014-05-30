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

	TmpIndexedFile ifile(file);
	if (!ifile.needs_reindex())
	{
		return;
	}

	ifile.clear();

	const char *token = NULL;
	while ((token = t.next()) != NULL)
	{
//		if (token[0] == 'f' && token[1] == 'o' && token[2] == 'o' && token[3] == '\0')
//		{
//			printf("File %d contains '%s'\n", file, token);
//		}
		wmanager.register_entry(token, file);
		ifile.append(token);
	}

	ifile.save();
}

static void index_function(int len, const char *path)
{
	index(get_file_manager().get_id(path));
}

void index_all(const char *directory)
{
	recurse_all_children(directory, &index_function);
}
