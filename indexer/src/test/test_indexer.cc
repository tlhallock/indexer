/*
 * test_indexer.cc
 *
 *  Created on: May 31, 2014
 *      Author: thallock
 */

#include "test/tests.h"

#include "include/export.h"

void test_indexer(int argc, char **argv)
{
	delete_file(BASE_DIR);

	const char *str = "foo";

	index_all(".");

	std::cout << "Number of files: " << get_file_manager().get_num_files() << "\n";
	std::cout << "Files containing " << str << ":\n";

	FileOffsetListQuery q(str);

	double time = q.run();
	std::cout << "Took " << time << "ms\n";

	fflush(stdout);
}
