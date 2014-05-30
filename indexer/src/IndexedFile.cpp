/*
 * IndexedFile.cpp
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "IndexedFile.h"

#include "export.h"

FilesWordIterator::FilesWordIterator(std::map<const char *, int> &words) :
		end(words.end()), it(words.begin()) {}

FilesWordIterator::~FilesWordIterator() {}

const char *FilesWordIterator::next()
{
	if (it == end)
	{
		return nullptr;
	}

	return (it++)->first;
}















TmpIndexedFile::TmpIndexedFile(file_id file_) :
	file(file_),
	read_time(0),
	current_tokens(0),
	words(),
	orders()
{
	time(&read_time);
}

TmpIndexedFile::~TmpIndexedFile()
{
//	save();
	free_mem();
}

void TmpIndexedFile::append(const char *token)
{
	auto it = words.find(token);

	int index;
	if (it == words.end())
	{
		index = orders.size();
		words.insert(std::pair<const char *, int> (strdup(token), index));
		orders.push_back(new std::set<int>);
	}
	else
	{
		index = it->second;
	}

	orders.at(index)->insert(current_tokens++);
}

void TmpIndexedFile::free_mem()
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

	words.clear();
	orders.clear();
}

void TmpIndexedFile::clear()
{
	free_mem();

	current_tokens = 0;

	char *filename = get_index_path();
	delete_file(filename);
	free(filename);
}

char *TmpIndexedFile::get_index_path() const
{
	const char *real_path = get_file_manager().get_path(file);
	return get_file_or_dir(FILES_BASE_DIR, real_path, true);
}

void TmpIndexedFile::save() const
{
	const char *path = get_file_manager().get_path(file);

	std::cout << "Saving index for " << path << std::endl;

	const char *file_dir = get_index_path();
	if (file_dir == nullptr)
	{
		std::cout << "Unable to find " << file << "'s for writing\n";
		return;
	}

	auto wend = words.end();
	for (auto wit = words.begin(); wit != wend; ++wit)
	{
		const char *key = wit->first;
		char *key_file = get_file_or_dir(file_dir, key, false);
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
		for(auto sit = s.begin(); sit != send; ++sit)
		{
			int offset = *sit;
			out.write(offset);
		}
	}

	{
		char *index_file = (char *) malloc (strlen (file_dir) + 1 + 5 + 1);
		sprintf(index_file, "%s/index", file_dir);

		DataOutputStream o(index_file);
		o.write(path);
//		o.write(last_indexed_time);

		free(index_file);
	}

	free((void *) file_dir);
}

time_t TmpIndexedFile::get_last_indexed_time() const
{
	const char *file_dir = get_index_path();
	if (file_dir == nullptr)
	{
		return (time_t) -1;
	}

	char *index_file = (char *) malloc(strlen(file_dir) + 1 + 5 + 1);
	sprintf(index_file, "%s/index", file_dir);
	free((void *) file_dir);

	time_t last_indexed_time = get_last_write_time(index_file);

	free(index_file);

	return last_indexed_time;
}

bool TmpIndexedFile::needs_reindex() const
{
	const char *path = get_file_manager().get_path(file);
	char *index_path = get_index_path();

	time_t last_file_modification = get_last_write_time(path);
	time_t last_index = get_last_indexed_time();

	free(index_path);

	return last_file_modification >= last_index;
}

#if 0
std::shared_ptr<TmpIndexedFile> get_indexed_file(file_id file)
{
	char buff[256];
	sprintf(buff, FILE_INDEX_PATTERN, file);

	TmpIndexedFile *ifile = new TmpIndexedFile(file);
	std::shared_ptr<TmpIndexedFile> ret(ifile);

	DataInputStream in(buff);
	if (!in.successful())
	{
		return ret;
	}

	int length = in.read_int();
	for (int i = 0; i < length; i++)
	{
//		ifile->append(in.read_str());
	}

	return ret;
}
#endif

#if 0
FilesWordIterator &TmpIndexedFile::get_iterater() const
{
	return *(new FilesWordIterator(words));
}
#endif

OccuranceIterator::OccuranceIterator(file_id file, const char *key)
	: num(0), count(0), in(nullptr)
{

	const char *real_path = get_file_manager().get_path(file);
	const char *file_dir = get_file_or_dir(FILES_BASE_DIR, real_path, true);
	if (file_dir == nullptr)
	{
		return;
	}

	const char *file_path = get_file_or_dir(file_dir, key, false);
	if (file_path == nullptr)
	{
		return;
	}

	in = new DataInputStream(file_path);
	if (!in->successful())
	{
		delete in;
		in = nullptr;
	}

	num = in->read_int();
}
OccuranceIterator::~OccuranceIterator()
{
	if (in != nullptr)
	{
		delete in;
	}
}

bool OccuranceIterator::has_next()
{
	return in != nullptr && count < num;
}

int OccuranceIterator::next()
{
	if (!has_next())
	{
		return -1;
	}

	++count;
	return in->read_int();
}

