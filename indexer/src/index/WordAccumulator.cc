/*
 * WordAccumulator.cpp
 *
 *  Created on: May 31, 2014
 *      Author: thallock
 */

#include "index/WordAccumulator.h"

#include "include/export.h"

WordAccumulator::WordAccumulator(IndexedFile *f) :
	file(f),
	read_time(-1),
	words(),
	orders()
{
	time(&read_time);
}

WordAccumulator::~WordAccumulator()
{
	auto oend = orders.end();
	for (auto it = orders.begin(); it != oend; ++it)
	{
		delete *it;
	}
	auto wend = words.end();
	for (auto it = words.begin(); it != wend; ++it)
	{
		delete it->first;
	}
}

std::set<int> *WordAccumulator::get_index(const char *word)
{
	auto it = words.find(word);
	if (it != words.end())
	{
		*it;
	}

	int index = orders.size();

	std::set<int> *ret_val = new std::set<int>;
	orders.push_back(ret_val);

	words.insert(std::pair<const char *, int>(strdup(word), index));

	return ret_val;
}

void WordAccumulator::append(const char *token, int offset)
{
	get_index(token)->insert(offset);
}

void WordAccumulator::save() const
{
	auto wend = words.end();
	for (auto wit = words.begin(); wit != wend; ++wit)
	{
		const char *key = wit->first;
		char *key_file = get_file_or_dir(file->get_index_path(), key, false);
		if (key_file == nullptr)
		{
			puts("Failure 510975610356");
			continue;
		}

		DataOutputStream out(key_file);
		if (!out.successful())
		{
			std::cout << "Unable to open " << key_file << " for writing\n";
			continue;
		}
		free(key_file);

		std::set<int> &s = *orders.at(wit->second);

		out.write(key);
		out.write((int) s.size());

		auto send = s.end();
		for (auto sit = s.begin(); sit != send; ++sit)
		{
			int offset = *sit;
			out.write(offset);
		}
	}

	{
		DataOutputStream o(file->get_index_attr_path());
		o.write(file->get_real_path());
		o.write(read_time);
	}
}

