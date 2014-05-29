/*
 * Hash.h
 *
 *  Created on: May 29, 2014
 *      Author: thallock
 */

#ifndef HASH_H_
#define HASH_H_

#define NUM_HASHES 5
constexpr int primes[NUM_HASHES] {757, 773, 829, 599, 467};

void get_file(const char *dir, const char *key, char *out);

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
