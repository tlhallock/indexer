/*
 * WordManager.h
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#ifndef WORDMANAGER_H_
#define WORDMANAGER_H_

#include "common.h"

#include "FileManager.h"

#define VALID_FILENAME_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._"
#define ENTRY_FILENAME_SIZE 16
#define BTREE_SIZE 50



void create_random_filename(char *out);

class Node
{
public:
	Node(Node *parent, int parents_index);
	~Node();

	int get_index(const char *query, bool &found) const;
	int get_id() const;

	void save() const;
	void read(int id);

	void insert(const char *token);
	void remove(const char *token);

	bool contains(const char *token) const;
private:
	int size;
	Node *parent;
	int parents_index;

	char *keys[BTREE_SIZE];
	char paths[BTREE_SIZE][ENTRY_FILENAME_SIZE + 1];
	Node *children[BTREE_SIZE];
};

class WordManager
{
public:
	WordManager();
	virtual ~WordManager();

	void register_entry(const char *token, file_id file);
	void remove_entries(file_id file);

	bool write(const char *path);
	bool read(const char *path);

	int get_num_words();
	size_t get_memory();

	int length();
private:
	Node *root;
};

WordManager &get_word_manager();

#endif /* WORDMANAGER_H_ */
