/*
 * WordManager.h
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#ifndef WORDMANAGER_H_
#define WORDMANAGER_H_

#include "common.h"

#include "FileManager.h"

class WordManager
{
public:
	WordManager();
	virtual ~WordManager();

	void register_entry(const char *token, file_id file);
	void remove_entries(file_id file);

	bool write(const char *path);
	bool read(const char *path);

	int get_num_words();
	size_t get_memory();

	int length();
private:
//	Node *root;
};

WordManager &get_word_manager();

#endif /* WORDMANAGER_H_ */
