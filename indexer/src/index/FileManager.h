/*
 * FileManager.h
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_

#include "include/common.h"

class FileMapper
{
public:
	FileMapper();
	~FileMapper();

	file_id get_id(const char *path);
	const char *get_path(file_id id) const;

	FILE *read(file_id file) const;
	int get_num_files() const;
	size_t get_memory() const;

	bool write() const;
	bool read();
private:
	boost::unordered_map<std::string, file_id> by_path;
	std::map<file_id, const char *> by_id;
};

FileMapper &get_file_mapper();

#endif /* FILEMANAGER_H_ */
