/*
 * Hash.h
 *
 *  Created on: May 29, 2014
 *      Author: thallock
 */

#ifndef HASH_H_
#define HASH_H_

#include <cstring>

constexpr int NUM_HASHES = 5;
constexpr int primes[NUM_HASHES] = {757, 773, 829, 599, 467};
constexpr int NUM_MAX_HASH_CHARS = (NUM_HASHES * strlen("0x7FFFFFFFL") + /* for collision count.*/ strlen("0x7FFFL"));

char *get_file_or_dir(const char *dir, const char *key, bool is_dir);

class Hash
{
public:
	Hash(const char *key);
	~Hash();

	void print(char *out, int collision_num);
private:
	int hashes[NUM_HASHES];
};


#endif /* HASH_H_ */
