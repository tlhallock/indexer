/*
 * test_indexer.cc
 *
 *  Created on: May 31, 2014
 *      Author: thallock
 */

#include "include/export.h"

#if 1
int main(int argc, char **argv)
{
	delete_file(get_settings().get_base_dir());

	const char *str = "foo";

	index_all("./src");
//	index_all("/media/thallock/0e53aea8-0c7a-4c02-9cba-f283a18835ba/work/cleanup/cef.old/chromium/src");

	get_file_mapper().write();

	get_exp_index().print();

	std::cout << "Number of files: " << get_file_mapper().get_num_files() << "\n";
	std::cout << "Files containing " << str << ":\n";


	Query *q = get_builder().build_query(str);

	double time = q->run();
	std::cout << "Took " << time << "ms\n";


	delete q;

	return 0;
}
#endif
