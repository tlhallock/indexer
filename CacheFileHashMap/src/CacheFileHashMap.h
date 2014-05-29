/*
 * CacheFileHashMap.h
 *
 *  Created on: May 29, 2014
 *      Author: thallock
 */

#ifndef CACHEFILEHASHMAP_H_
#define CACHEFILEHASHMAP_H_




#define NUM_PRIMES 4




class FileCacheEntry
{
private:
	const char *str;

};















#define VALID_FILENAME_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._"
#define ENTRY_FILENAME_SIZE 16
#define BTREE_SIZE 50







void create_random_filename(char *out);


class CacheFileHashMap
{
public:
	CacheFileHashMap();
	virtual ~CacheFileHashMap();

	void put(const char *key, const Serializable &s);
	Serializable &get(const char *key);
};

#endif /* CACHEFILEHASHMAP_H_ */
