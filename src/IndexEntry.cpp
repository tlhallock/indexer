/*
 * IndexEntry.cpp
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "IndexEntry.h"

#include "export.h"


IndexEntry::IndexEntry(word_id entry_) :
	entry(entry_),
	files() {}

IndexEntry::~IndexEntry()
{
	save();
}

void IndexEntry::add_file(file_id file)
{
	files.insert(file);
}

void IndexEntry::remove_file(file_id file)
{
	files.erase(files.find(file));
}

bool IndexEntry::contains(const char* query) const
{
	return strstr(get_word_manager().get_word(entry), query) != NULL;
}

void IndexEntry::print_list() const
{
	auto end = files.end();
	for (auto it = files.begin(); it != end; ++it)
	{
		fprintf(stdout, "\t%s\n", get_file_manager().get_path(*it));
	}
}

void IndexEntry::save()
{
	char buff[256];
	sprintf(buff, FILE_LIST_PATTERN, entry);

	DataOutputStream out(buff);
	if (!out.successful())
	{
		printf("Can't open %s for saving!\n", buff);
		exit(1);
	}

	out.write(files.size());

	auto end = files.end();
	for (auto it = files.begin(); it != end; ++it)
	{
		out.write(*it);
	}
}







