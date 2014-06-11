/*
 * Hash.h
 *
 *  Created on: May 29, 2014
 *      Author: thallock
 */

#ifndef HASH_H_
#define HASH_H_

#include "include/common.h"

#include "utils/DataOutputStream.h"

constexpr int NUM_HASHES = 5;
constexpr int primes[NUM_HASHES] = {757, 773, 829, 599, 467};
constexpr int NUM_MAX_HASH_CHARS = (NUM_HASHES * strlen("0x7FFFFFFFL") + /* for collision count.*/ strlen("0x7FFFL"));

std::unique_ptr<DataInputStream> read_file_index(const char *original_file_name, const char *key);
std::unique_ptr<DataOutputStream> write_file_index(const char *original_file_name, const char *key);
void remove_file_index(const char *original_file_name);

std::unique_ptr<DataInputStream> read_word_index(const char *key);
std::unique_ptr<DataOutputStream> write_word_index(const char *key);
void remove_word_index(const char *key);

std::unique_ptr<DataInputStream> read_super_string_index(const char *key);
std::unique_ptr<DataOutputStream> write_super_string_index(const char *key);
void remove_super_string_index(const char *key);

std::unique_ptr<DataInputStream> read_substring_index(const char *key);
std::unique_ptr<DataOutputStream> write_substring_index(const char *key);

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
