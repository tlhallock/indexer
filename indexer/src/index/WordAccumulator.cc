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
}

std::set<int> *WordAccumulator::get_index(const char *word)
{
	auto it = words.find(word);
	if (it != words.end())
	{
		int index = it->second;
		if (index > (int) orders.size() || orders.at(index) == nullptr)
		{
			puts("Error 57190187509318650135");
			exit(1);
		}
		return orders.at(index);
	}

	int index = orders.size();

	std::set<int> *ret_val = new std::set<int>;
	orders.push_back(ret_val);

	words.insert(std::pair<std::string, int>(word, index));

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
		const char *key = wit->first.c_str();

		std::unique_ptr<DataOutputStream> out(write_file_index(file->get_real_path(), key));
		if (out == nullptr || !out->successful())
		{
			std::cout << "Unable to open index for " << file->get_real_path() << "::" << key << " for writing\n";
			continue;
		}

		std::set<int> &s = *orders.at(wit->second);

		out->write((int) s.size());

		auto send = s.end();
		for (auto sit = s.begin(); sit != send; ++sit)
		{
			out->write(*sit);
		}
	}

	write_file_index(file->get_real_path(), nullptr)->write(read_time);
}

