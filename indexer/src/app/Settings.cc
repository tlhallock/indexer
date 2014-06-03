/*
 * Settings.cpp
 *
 *  Created on: May 31, 2014
 *      Author: rever
 */

#include "Settings.h"

#include "include/export.h"

const Settings &get_settings()
{
	static Settings *settings;
	if (settings == nullptr)
	{
		settings = new Settings();
	}
	return *settings;
}

Settings::Settings()
{
#if 1
	home_folder = "/home/thallock/.indexes";
#else
	home_folder = "/home/rever/.indexes";
#endif

	words_base_dir = concatenate(home_folder, "/words.d");
	files_base_dir = concatenate(home_folder, "/files.d");
	files_file = concatenate(home_folder, "/files.txt");

}

Settings::~Settings()
{
	free((char *) words_base_dir);
	free((char *) files_base_dir);
	free((char *) files_file);
}

const char* Settings::get_base_dir() const
{
	return home_folder;
}

const char* Settings::get_words_base_dir() const
{
	return words_base_dir;
}

const char* Settings::get_files_base_dir() const
{
	return files_base_dir;
}

const char* Settings::get_files_file() const
{
	return files_file;
}

const char* Settings::get_delims() const
{
	return ".!@#$%^&*()_+-={}|[];':\",.<>/?\\ \t\n\r^`~";
}

double Settings::get_max_unreadable_percentage() const
{
	return .1;
}

bool Settings::should_index_substrings() const
{
	return false;
}

bool Settings::should_small_words() const
{
	return true;
}

bool Settings::should_index_files() const
{
	return true;
}

bool Settings::human_readable_indices() const
{
	return true;
}
