/*
 * FileManager.h
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_

#include "common.h"

typedef int file_id;

class FileManager
{
public:
	FileManager();
	~FileManager();

	file_id get_id(const char *path);
	const char *get_path(file_id id);

	FILE *read(file_id file);
	int get_num_files();
	size_t get_memory();

	bool write(const char *path);
	bool read(const char *path);

private:
	std::map<const char *, file_id, ConstCharComparator> by_path;
	std::vector<const char *> by_id;
};

FileManager &get_file_manager();

#endif /* FILEMANAGER_H_ */
