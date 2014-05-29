/*
 * CacheFileHashMap.cpp
 *
 *  Created on: May 29, 2014
 *      Author: thallock
 */

#include "CacheFileHashMap.h"

#include <cstring>
#include <stdio.h>

long primes[NUM_PRIMES] = {263, 31, 491, 997};
long hash(const char *str, int collision)
{
	long prime = primes[collision];

	long ret = 0;
	long acc = 1;

	while (*str)
	{
		ret += acc * *str;
		acc *= prime;

		++str;
	}

	return ret;
}

static void get_file(const char *key, char *out_path)
{
	int collision_count = 0;

	bool match = false;
	for (int i = 0; i < NUM_PRIMES && !match; i++)
	{
		long hash = hash(key, i);
		sprintf(out_path, "./index/%ld", hash);
		DataInputStream in(out_path);
		if (!in.successful())
		{
			return;
		}

		char *token = in.read_str();
		match = strcmp(token, key);
		free(token);
	}


	if (!match)
	{
		puts("too many collisions!");
		return;
	}
}


void create_random_filename(char *out)
{
	constexpr int len = strlen(VALID_FILENAME_CHARS);
	for (int i = 0; i < ENTRY_FILENAME_SIZE; i++)
	{
		out[i] = VALID_FILENAME_CHARS[rand() % len];
	}
	out[ENTRY_FILENAME_SIZE] = '\0';
}


CacheFileHashMap::CacheFileHashMap()
{
	// TODO Auto-generated constructor stub

}

CacheFileHashMap::~CacheFileHashMap()
{
	// TODO Auto-generated destructor stub
}

