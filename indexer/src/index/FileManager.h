/*
 * FileManager.h
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_

#include "include/common.h"

#define INVALID_FILE (-1)

class FileMapper
{
public:
	FileMapper();
	~FileMapper();

	FileId get_id(const char *path);
	const char *get_path(FileId id) const;

	FILE *read(FileId file) const;
	int get_num_files() const;
	size_t get_memory() const;

	bool write() const;
	bool read();
private:
	boost::unordered_map<std::string, FileId> by_path;
	boost::unordered_map<int, std::string> by_id;
};

FileMapper &get_file_mapper();

#endif /* FILEMANAGER_H_ */
