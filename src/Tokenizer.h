/*
 * Tokenizer.h
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include "FileManager.h"

#include "common.h"

bool is_delimiter(const char &c);
bool is_alpha_numeric(const char &c);

class Tokenizer
{
public:
	Tokenizer(file_id file);
	virtual ~Tokenizer();

	const char *next();
private:
	const char *current_string();
	void ensure(size_t size);
	bool is_binary() const;

	FILE *file;
	file_id id;

	int index;
	size_t buff_size;
	char *buff;

	char next_char;
	int unreadable;
	long bytes_read;
};

#endif /* TOKENIZER_H_ */
