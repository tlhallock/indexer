/*
 * FileManager.cpp
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "FileManager.h"

#include "export.h"

static FileManager *manager_ = nullptr;

FileManager& get_file_manager()
{
	if (manager_ == nullptr)
	{
		manager_ = new FileManager();
		manager_->read(FILES_FILE);
	}

	return *manager_;
}

FileManager::FileManager() :
			by_path(),
			by_id() {}

FileManager::~FileManager()
{
	auto end = by_id.end();
	for (auto it = by_id.begin(); it != end; ++it)
	{
		delete it->second;
	}
}

file_id FileManager::get_id(const char* path)
{
	auto it = by_path.find(path);
	if (it != by_path.end())
	{
		return it->second;
	}

	file_id next_id = by_id.size();

	const char *dpath = strdup(path);

	by_id.insert(std::pair<file_id, const char *>(next_id, dpath));
	by_path.insert(std::pair<const char *, file_id>(dpath, next_id));

	return next_id;
}

const char* FileManager::get_path(file_id id)
{
	return by_id.at(id);
}

FILE* FileManager::read(file_id file)
{
	return fopen(get_path(file), "r");
}


int FileManager::get_num_files()
{
	return by_id.size();
}

size_t FileManager::get_memory()
{
	size_t memory = 0;

	auto end = by_id.end();
	for (auto it = by_id.begin(); it != end; ++it)
	{
		memory += strlen(it->second);
	}

	return memory;
}


bool FileManager::write(const char *path)
{
	DataOutputStream out(path);
	if (!out.successful())
	{
		return false;
	}

	int size = by_id.size();
	out.write(size);
	for (int i = 0; i < size; i++)
	{
		out.write(by_id.at(i));
	}
	return true;
}

bool FileManager::read(const char *path)
{
	DataInputStream in(path);
	if (!in.successful())
	{
		return false;
	}

	int size = in.read_int();
	for (int i = 0; i < size; i++)
	{
		get_id(in.read_str());
	}

	return true;
}
