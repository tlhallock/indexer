/*
 * Hash.cpp
 *
 *  Created on: May 29, 2014
 *      Author: thallock
 */

#include "Hash.h"


#define MAX_PRIME 2147483629


Hash::Hash(const char *key)
{
	int accs[NUM_HASHES];

	for (int i = 0; i < NUM_HASHES; i++)
	{
		hashes[i] = 0;
		accs[i] = primes[i];
	}

	while (*key)
	{
		for (int i = 0; i < NUM_HASHES; i++)
		{
			hashes[i] += (int) ((accs[i] * (long) *key) % MAX_PRIME);
			accs[i] *= primes[i];
		}

		++key;
	}
}

Hash::~Hash()
{
}

void Hash::print(char *out, int collision_num)
{
	out[0] = '\0';

	char buff[265];
	for (int i = 0; i < NUM_HASHES; i++)
	{
		sprintf(buff, "%ld.", hashes[i]);
		strcat(out, buff);
	}

	sprintf(buff, "%d", collision_num);
	strcat(out, buff);
}

void get_file(const char *dir, const char *key, char *out)
{
	int collision_count = 0;
	Hash h(key);
	char fname[256];

	bool match = false;
	do
	{
		h.print(fname, collision_count++);

		sprintf(out, "%s/%s", dir, fname);

		DataInputStream in(out);
		if (!in.successful())
		{
			return;
		}
		char *token = in.read_str();
		match = strcmp(token, key);
		free(token);
	} while (match && collision_count > 0);

	if (collision_count < 0)
	{
		puts("56109760539706531976531");
		exit(0);
	}
}
