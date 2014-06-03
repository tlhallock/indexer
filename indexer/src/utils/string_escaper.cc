/*
 * string_escaper.cc
 *
 *  Created on: May 29, 2014
 *      Author: thallock
 */

#include <stdlib.h>
#include <cstring>

// Not here for any reason in particular...
char *concatenate(const char *str1, const char *str2)
{
	char *ret_val = (char *) malloc (sizeof(*ret_val) * (strlen(str1) + strlen(str2) + 1));

	ret_val[0] = '\0';
	strcat(ret_val, str1);
	strcat(ret_val, str2);

	return ret_val;
}



#define ESCAPE_CHAR '.'
#define VALID_FILENAME_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"

#include <stdlib.h>
#include <cstring>
#include <stdio.h>

static void ensure(char *&out, int &out_size, int min_length)
{
	if (out_size > min_length)
	{
		return;
	}

	if (out_size < 0)
	{
		out_size = 512;
	}
	else
	{
		out_size *= 2;
	}

	if (out_size < min_length)
	{
		out_size = min_length + 10;
	}

	out = (char *) realloc(out, out_size);
}

static bool is_ok(char c)
{
	constexpr int valid_length = strlen(VALID_FILENAME_CHARS);

	for (int i = 0; i < valid_length; i++)
	{
		if (VALID_FILENAME_CHARS[i] == c)
		{
			return true;
		}
	}
	return false;
}












void escape(const char *in, char *&out, int &out_size)
{
	if (out == nullptr || out_size <= 0)
	{
		out_size = 512;
		out = (char *) malloc (sizeof (*out) * out_size);
	}

	int slen = 0;
	while(*in)
	{
		char c = *(in++);
		ensure(out, out_size, slen + 5);

		if (is_ok(c))
		{
			out[slen++] = c;
			continue;
		}
		else
		{
			sprintf(out + slen, "%c%03d", ESCAPE_CHAR, c);
			slen += 4;
		}
	}
}

static int readi(const char *in)
{
	int ret_val = 0;
	ret_val = 10 * ret_val + (in[0] - '0');
	ret_val = 10 * ret_val + (in[1] - '0');
	ret_val = 10 * ret_val + (in[2] - '0');
	return ret_val;
}

void descape(const char *in, char *&out, int &out_size)
{
	if (out == nullptr || out_size <= 0)
	{
		out_size = strlen(in) + 1;
		out = (char *) malloc (sizeof (*out) * out_size);
	}

	int len = 0;
	while (*in)
	{
		char c = *(in++);

		if (c == ESCAPE_CHAR)
		{
			c = (char) readi(in);
			in += 3;
		}

		ensure(out, out_size, len + 1);
		out[len++] = c;
	}

	ensure(out, out_size, len + 1);
	out[len] = '\0';
}

