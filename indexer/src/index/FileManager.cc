/*
 * FileManager.cpp
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "index/FileManager.h"

#include "include/export.h"

FileMapper& get_file_mapper()
{
	static FileMapper *manager;
	if (manager == nullptr)
	{
		manager = new FileMapper();
	}

	return *manager;
}

FileMapper::FileMapper() :
		by_path(),
		by_id()
{
	read();
}

FileMapper::~FileMapper()
{
	puts("Writing the file mapper...");
	write();

	auto end = by_id.end();
	for (auto it = by_id.begin(); it != end; ++it)
	{
		free((char *) it->second);
	}
}

file_id FileMapper::get_id(const char* untrusted_path)
{
	char *real_path = realpath(untrusted_path, nullptr);

	auto it = by_path.find(real_path);
	if (it != by_path.end())
	{
		free(real_path);
		return it->second;
	}

	file_id next_id = by_id.size();

	by_id.insert(std::pair<file_id, const char *>(next_id, real_path));
	by_path.insert(std::pair<std::string, file_id>(std::string(real_path), next_id));

	return next_id;
}

const char* FileMapper::get_path(file_id id) const
{
	return by_id.at(id);
}

FILE* FileMapper::read(file_id file) const
{
	return fopen(get_path(file), "r");
}

int FileMapper::get_num_files() const
{
	return by_id.size();
}

size_t FileMapper::get_memory() const
{
	size_t memory = 0;

	auto end = by_id.end();
	for (auto it = by_id.begin(); it != end; ++it)
	{
		memory += strlen(it->second);
	}

	return memory;
}

bool FileMapper::write() const
{
	DataOutputStream out(get_settings().get_files_file());
	if (!out.successful())
	{
		return false;
	}

	int size = by_id.size();
	out.write(size);
	for (int i = 0; i < size; i++)
	{
		out.write(i);
		out.write(by_id.at(i));
	}
	return true;
}

bool FileMapper::read()
{
	DataInputStream in(get_settings().get_files_file());
	if (!in.successful())
	{
		return false;
	}

	int size = in.read_int();
	for (int i = 0; i < size; i++)
	{
		int id = in.read_int();
		char *path = in.read_str();
		get_id(path);
		free(path);
	}

	return true;
}
