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
//	delete_file(get_settings().get_base_dir());

	const char *str = "foo";

	index_all("./src");

	get_file_mapper().write();

	std::cout << "Number of files: " << get_file_mapper().get_num_files() << "\n";
	std::cout << "Files containing " << str << ":\n";

	Query *q;
	if (get_settings().use_massive_storage())
	{
		q = new FileOffsetListQuery(str);
	}
	else
	{
		q = new SuperStringQuery(str);
	}

	double time = q->run();
	std::cout << "Took " << time << "ms\n";


	delete q;

	return 0;
}
#endif
