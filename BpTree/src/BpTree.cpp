/*
 * BpTree.cpp
 *
 *  Created on: May 29, 2014
 *      Author: thallock
 */

#include "BpTree.h"

Node::Node(Node *parent_, int parents_index_) :
		size(0),
		parent(parent_),
		parents_index(parents_index_)
{
	for (int i = 0; i < BTREE_SIZE; i++)
	{
		keys[i] = nullptr;
		children[i] = nullptr;
	}
}

Node::~Node()
{
	for (int i = 0; i < BTREE_SIZE; i++)
	{
		if (keys[i] != nullptr)
		{
			free(keys[i]);
		}
		if (children[i] != nullptr)
		{
			delete children[i];
		}
	}
}

int Node::get_index(const char *query, bool &match) const
{
	if (size == 0)
	{
		return 0;
	}

	int cmp = strcmp(query, keys[0]);
	if (cmp <= 0)
	{
		match = cmp == 0;
		return 0;
	}
	cmp = strcmp(query, keys[size-1]);
	if (cmp >= 0)
	{
		match = cmp == 0;
		return size-1;
	}

	int max = size - 1;
	int min = 0;

	while (max > min + 1)
	{
		int mid = (max + min) / 2;
		cmp = strcmp(query, keys[mid]);

		if (cmp == 0)
		{
			match = true;
			return mid;
		}

		if (cmp < 0)
		{
			max = mid;
		}
		else
		{
			min = mid;
		}
	}

	cmp = strcmp(query, keys[min]);
	if (cmp == 0)
	{
		match = true;
		return min;
	}

	if (min == max)
	{
		match = false;
		return min;
	}
	cmp = strcmp(query, keys[max]);
	if (cmp == 0)
	{
		match = true;
		return max;
	}

	match = false;
	return min;
}

int Node::get_id() const
{
	int acc = 0;

	const Node *c = this;
	int size = BTREE_SIZE;

	while (c != NULL)
	{
		acc += c->parents_index;
		acc += size;

		size *= BTREE_SIZE;
		c = c->parent;
	}

	return acc;
}

void Node::save() const
{
}






