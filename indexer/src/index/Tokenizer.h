/*
 * Tokenizer.h
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include "include/common.h"


// could be a string iterator...

bool is_delimiter(const char &c);
bool is_alpha_numeric(const char &c);

class Tokenizer
{
public:
	Tokenizer(FileId file);
	virtual ~Tokenizer();

	const char *next();
	long last_start();
private:
	const char *current_string();
	void ensure(size_t size);
	bool is_binary() const;

	FILE *file;
	FileId id;

	int index;
	size_t buff_size;
	char *buff;

	char next_char;
	int unreadable;
	long bytes_read;

	long last_index;
};

#endif /* TOKENIZER_H_ */
