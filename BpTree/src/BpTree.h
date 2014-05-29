/*
 * BpTree.h
 *
 *  Created on: May 29, 2014
 *      Author: thallock
 */

#ifndef BPTREE_H_
#define BPTREE_H_

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

#endif /* BPTREE_H_ */
