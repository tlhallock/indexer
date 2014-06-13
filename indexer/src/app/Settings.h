/*
 * Settings.h
 *
 *  Created on: May 31, 2014
 *      Author: rever
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

class Settings
{
public:
	Settings();
	virtual ~Settings();

	const char *get_base_dir() const;
	const char *get_words_base_dir() const;
	const char *get_files_base_dir() const;
	const char *get_super_string_base_dir() const;
	const char *get_substrings_base_dir() const;

	const char *get_files_file() const;

	const char *get_delims() const;
	double get_max_unreadable_percentage() const;

	bool should_index_substrings() const;
	bool should_index_files() const;
	bool should_index_all_substrings() const;

	bool human_readable_indices() const;

	int get_maximum_substring_index() const;
	int get_minimum_substring_index() const;

private:
	const char *home_folder;
	const char *words_base_dir; // indices of words (including all substrings) referencing files
	const char *files_base_dir; // indices of files
	const char *super_strings_base_dir; // indices of words (not including substrings) referencing files
	const char *substrings_base_dir; // indices of substrings with maximum size referencing super_stirngs_base_dir;
	const char *files_file;
};

const Settings &get_settings();

#endif /* SETTINGS_H_ */
