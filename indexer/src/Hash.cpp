/*
 * Hash.cpp
 *
 *  Created on: May 29, 2014
 *      Author: thallock
 */

#include "Hash.h"

#include "export.h"

#define MAX_PRIME 2147483629


Hash::Hash(const char *key)
{
	int accs[NUM_HASHES];

	for (int i = 0; i < NUM_HASHES; i++)
	{
		hashes[i] = 1804289383;  // <- random number
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

	char buff[NUM_MAX_HASH_CHARS];
	for (int i = 0; i < NUM_HASHES; i++)
	{
		sprintf(buff, "%x.", hashes[i]);
		strcat(out, buff);
	}

	sprintf(buff, "%x", collision_num);
	strcat(out, buff);
}

char *get_file_or_dir(const char *dir, const char *key, bool is_dir)
{
	int collision_count = 0;
	Hash h(key);
	char fname[NUM_MAX_HASH_CHARS];

	char *out = (char *) malloc (sizeof(*out) * (strlen(dir) + 1 + NUM_MAX_HASH_CHARS + 5 + 1));
	out[0] = '\0';

	bool match = false;
	do
	{
		h.print(fname, collision_count++);

		if (is_dir)
		{
			sprintf(out, "%s/%s/index", dir, fname);
		}
		else
		{
			sprintf(out, "%s/%s", dir, fname);
		}

		DataInputStream in(out);
		if (!in.successful())
		{
			break;
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

	sprintf(out, "%s/%s", dir, fname);

	return out;
}

