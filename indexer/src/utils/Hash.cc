/*
 * Hash.cpp
 *
 *  Created on: May 29, 2014
 *      Author: thallock
 */

#include "utils/Hash.h"

#include "include/export.h"

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


static std::unique_ptr<DataInputStream> single_hash(const char *dir, const char *key, bool returnNonExists)
{
	if (dir == nullptr || !*dir || key == nullptr || !*key)
	{
		return nullptr;
	}

	int file_collision_count = 0;

	Hash k(key);

	char *out = (char *) malloc (sizeof(*out) * (strlen(dir) + 1 + NUM_MAX_HASH_CHARS + 1));
	out[0] = '\0';

	sprintf(out, "%s/", dir);

	char *dir_offset = out + strlen(out);

	do
	{
		k.print(dir_offset, file_collision_count);

		std::unique_ptr<DataInputStream> in(new DataInputStream(out));
		if (!in->successful())
		{
			if (returnNonExists)
			{
				return in;
			}
			else
			{
				return std::unique_ptr<DataInputStream>(nullptr);
			}
		}

		if (in->read_str()->compare(key) != 0)
		{
			file_collision_count++;
			continue;
		}

		return in;
	} while (file_collision_count >= 0);

	puts("56109760539706531976531");
	exit(1);
}


std::unique_ptr<DataInputStream> read_file_index(const char *original_file_name, const char *key, bool returnNonExists)
{
	if (original_file_name == nullptr || !*original_file_name || (key != nullptr && !*key))
	{
		return nullptr;
	}

	int file_collision_count = 0;
	int  key_collision_count = 0;

	Hash f(original_file_name);
	std::unique_ptr<Hash> k(key == nullptr ? nullptr : new Hash(key));

	const char *dir = get_settings().get_files_base_dir();

	char *out = (char *) malloc (sizeof(*out) * (strlen(dir) + 1 + NUM_MAX_HASH_CHARS + 1 + NUM_MAX_HASH_CHARS + 1));
	out[0] = '\0';

	sprintf(out, "%s/", dir);

	char *dir_offset = out + strlen(out);

	do
	{
		f.print(dir_offset, file_collision_count);
		char *koffset = out + strlen(out);
		if (key == nullptr)
		{
			koffset[0] = 'i';
			koffset[1] = 'n';
			koffset[2] = 'd';
			koffset[3] = 'e';
			koffset[4] = 'x';
			koffset[5] = '\0';
		}
		else
		{
			k->print(koffset, key_collision_count);
		}

		std::unique_ptr<DataInputStream> in(new DataInputStream(out));
		if (!in->successful())
		{
			if (returnNonExists)
			{
				return in;
			}
			else
			{
				return std::unique_ptr<DataInputStream>(nullptr);
			}
		}

		if (in->read_str()->compare(original_file_name) != 0)
		{
			file_collision_count++;
			continue;
		}
		if (key != nullptr && in->read_str()->compare(key) != 0)
		{
			key_collision_count++;
			continue;
		}

		return in;
	} while (file_collision_count >= 0 && key_collision_count >= 0);

	puts("56109760539706531976531");
	exit(1);
}

std::unique_ptr<DataOutputStream> write_file_index(const char *original_file_name, const char *key)
{
	std::unique_ptr<DataInputStream> in = read_file_index(original_file_name, key, true);
	if (in.get() == nullptr)
	{
		return nullptr;
	}
	std::unique_ptr<DataOutputStream> out(new DataOutputStream(in->get_path()));
	out->write(original_file_name);
	if (key != nullptr)
	{
		out->write(key);
	}
	return out;
}

std::unique_ptr<DataInputStream> read_word_index(const char *key, bool returnNonExists)
{
	return single_hash(get_settings().get_words_base_dir(), key, returnNonExists);
}
std::unique_ptr<DataOutputStream> write_word_index(const char *key)
{
	std::unique_ptr<DataInputStream> in = read_word_index(key, true);
	if (in.get() == nullptr)
	{
		return nullptr;
	}
	std::unique_ptr<DataOutputStream> out(new DataOutputStream(in->get_path()));
	out->write(key);
	return out;
}

std::unique_ptr<DataInputStream> read_super_string_index(const char *key, bool returnNonExists)
{
	return single_hash(get_settings().get_super_string_base_dir(), key, returnNonExists);
}

std::unique_ptr<DataOutputStream> write_super_string_index(const char *key)
{
	std::unique_ptr<DataInputStream> in = read_super_string_index(key, true);
	if (in.get() == nullptr)
	{
		return nullptr;
	}
	std::unique_ptr<DataOutputStream> out(new DataOutputStream(in->get_path()));
	out->write(key);
	return out;
}

void remove_file_index(const char* original_file_name)
{
	// everything gets removed anyway...
}

void remove_word_index(const char* key)
{
	// everything gets removed anyway...
}

void remove_super_string_index(const char* key)
{
	// everything gets removed anyway...
}

std::unique_ptr<DataInputStream> read_substring_index(const char* key, bool returnNonExists)
{
	return single_hash(get_settings().get_substrings_base_dir(), key, returnNonExists);
}

std::unique_ptr<DataOutputStream> write_substring_index(const char* key)
{
	std::unique_ptr<DataInputStream> in = read_substring_index(key, true);
	if (in.get() == nullptr)
	{
		return nullptr;
	}
	std::unique_ptr<DataOutputStream> out(new DataOutputStream(in->get_path()));
	out->write(key);
	return out;
}
