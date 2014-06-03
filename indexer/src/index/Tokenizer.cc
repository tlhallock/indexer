/*
 * Tokenizer.cpp
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "include/export.h"

#define INITIAL_BUFFER_SIZE 256

Tokenizer::Tokenizer(FileId file_) :
	file(get_file_mapper().read(file_)),
	id(file_),
	index(0),
	buff_size(INITIAL_BUFFER_SIZE),
	buff((char *) malloc (sizeof(*buff) * buff_size)),
	next_char('\0'),
	unreadable(0),
	bytes_read(0) {}

Tokenizer::~Tokenizer()
{
	fclose(file);
	free(buff);
}

bool is_delimiter(const char &c)
{
	return strchr(get_settings().get_delims(), c) != NULL;
}

bool is_alpha_numeric(const char &c)
{
	if ('a' <= c && c <= 'z')
	{
		return true;
	}

	if ('A' <= c && c <= 'Z')
	{
		return true;
	}
	if ('0' <= c && c <= '9')
	{
		return true;
	}

	return false;
}

const char *Tokenizer::current_string()
{
	buff[index] = '\0';
	index = 0;

//	fprintf(stdout, "Found string: %s\n", buff);
	return buff;
}

bool Tokenizer::is_binary() const
{
	if (bytes_read < 1 / get_settings().get_max_unreadable_percentage())
	{
		return false;
	}
	bool binary = (unreadable / (double) bytes_read) > get_settings().get_max_unreadable_percentage();
	if (binary)
	{
//		printf("%d / %ld\n", unreadable, bytes_read);
		fprintf(stdout, "Binary file: %s\n", get_file_mapper().get_path(id));
	}
	return binary;
}

const char *Tokenizer::next()
{

	if (is_binary())
	{
		return NULL;
	}

	if (next_char != '\0')
	{
		last_index = bytes_read - 1;

		buff[0] = next_char;
		buff[1] = '\0';

		next_char = '\0';
		return buff;
	}

	last_index = bytes_read;

	for (;;)
	{
		int c = fgetc(file);
		bytes_read++;

		if (c < 0)
		{
			if (index == 0)
			{
				return NULL;
			}

			return current_string();
		}

		bool delim = is_delimiter(c);
		bool alpha = is_alpha_numeric(c);

		if (!delim && !alpha)
		{
			unreadable++;
			if (is_binary())
			{
				return NULL;
			}
			last_index = bytes_read;
		}

		if (delim || !alpha)
		{
			if (index == 0)
			{
				if (alpha)
				{
					continue;
				}
				else
				{
					buff[0] = c;
					buff[1] = '\0';
					return buff;
				}
			}
			else
			{
				next_char = c;
				return current_string();
			}
		}

		ensure(index + 2);
		buff[index++] = c;
	}

	puts("Shouldn't get here!!! 2875942870924");
	return NULL;
}



void Tokenizer::ensure(size_t size)
{
	if (buff_size >= size)
	{
		return;
	}

	buff_size *= 2;
	buff = (char *) realloc(buff, buff_size);
}

long Tokenizer::last_start()
{
	return last_index;
}
