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
}

FileId FileMapper::get_id(const char* untrusted_path)
{
	if (!*untrusted_path)
	{
		return INVALID_FILE;
	}
	char *real_path = realpath(untrusted_path, nullptr);
	if (real_path == nullptr || !*real_path)
	{
		return INVALID_FILE;
	}

	auto it = by_path.find(real_path);
	if (it != by_path.end())
	{
		free(real_path);
		return it->second;
	}

	FileId next_id = by_id.size();

	by_id.insert(std::pair<FileId, const char *>(next_id, real_path));
	by_path.insert(std::pair<std::string, FileId>(std::string(real_path), next_id));

	return next_id;
}

const char* FileMapper::get_path(FileId id) const
{
	auto it = by_id.find(id);
	if (it == by_id.end())
	{
		return nullptr;
	}
	return it->second.c_str();
}

FILE* FileMapper::read(FileId file) const
{
	const char *path = get_path(file);
	if (path == nullptr)
	{
		return nullptr;
	}
	return fopen(path, "r");
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
		memory += it->second.size();
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
	auto end = by_id.end();
	for (auto it = by_id.begin(); it != end; ++it)
	{
		out.write(it->first);
		out.write(it->second.c_str());
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

	try
	{
		int size = in.read_int();
		for (int i = 0; i < size; i++)
		{
			int id = in.read_int();
			std::string path(*in.read_str());
			by_id.insert(std::pair<int, std::string>(id, path));
			by_path.insert(std::pair<std::string, int>(path, id));
		}
	}
	catch (UnexpectedInputException &ex)
	{
		std::cout << "Unable to read old file list..." << std::endl;
	}

	return true;
}
