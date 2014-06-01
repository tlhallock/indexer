/*
 * test_indexer.cc
 *
 *  Created on: May 31, 2014
 *      Author: thallock
 */

#include "include/export.h"

void main(int argc, char **argv)
{
	delete_file(BASE_DIR);

	const char *str = "foo";

	index_all(".");

	get_file_mapper().write();

	std::cout << "Number of files: " << get_file_mapper().get_num_files() << "\n";
	std::cout << "Files containing " << str << ":\n";

	FileOffsetListQuery q(str);

	double time = q.run();
	std::cout << "Took " << time << "ms\n";

	fflush(stdout);
}
