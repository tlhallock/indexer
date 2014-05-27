/*
 * Main.cc
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "export.h"

int main(int argc, char **argv)
{
//	mkdir("/home/thallock/.indexes/");
//	mkdir("/home/thallock/.indexes/file_lists/");
//	mkdir( "/home/thallock/.indexes/files/");

	const char *str = "foo";

	index_all(".");

	std::cout << "Number of files: " << get_file_manager().get_num_files() << "\n";

	std::cout << "Files containing " << str << ":\n";

	double time = query(str);
	std::cout << "Took " << time << "ms\n";

	fflush(stdout);

	get_file_manager().write(FILES_FILE);
	get_word_manager().write(WORDS_FILE);

	return 0;
}
