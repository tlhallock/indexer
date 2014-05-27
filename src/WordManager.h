/*
 * WordManager.h
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#ifndef WORDMANAGER_H_
#define WORDMANAGER_H_

#include "common.h"

typedef int word_id;

class WordManager
{
public:
	WordManager();
	virtual ~WordManager();

	word_id get_word(const char *word);
	const char *get_word(word_id id);

	int get_num_words();
	size_t get_memory();

	bool write(const char *path);
	bool read(const char *path);

	bool word_contains(word_id id, const char *str);
	int length();
private:
	std::map<const char *, word_id, ConstCharComparator> by_word;
	std::vector<const char *> by_id;
};

WordManager &get_word_manager();

#endif /* WORDMANAGER_H_ */
