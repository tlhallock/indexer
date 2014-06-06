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









typedef enum { pass, fail, inconclusive } test_result;

test_result test_empty_file()
{
	return inconclusive;
}
test_result test_empty_string()
{
	return inconclusive;
}
test_result test_start_of_file()
{
	return inconclusive;
}
test_result test_end_of_file()
{
	return inconclusive;
}
test_result test_no_match()
{
	return inconclusive;
}
test_result test_end_of_superstring()
{
	return inconclusive;
}
test_result test_start_of_superstring()
{
	return inconclusive;
}
test_result test_exact_match()
{
	return inconclusive;
}

test_result test_strlen_1_match()
{
	return inconclusive;
}
test_result test_strlen_2_match()
{
	return inconclusive;
}
test_result test_strlen_3_match()
{
	return inconclusive;
}
test_result test_strlen_4_match()
{
	return inconclusive;
}
test_result test_strlen_5_match()
{
	return inconclusive;
}
test_result test_strlen_6_match()
{
	return inconclusive;
}
test_result test_strlen_10_match()
{
	return inconclusive;
}
test_result test_strlen_50_match()
{
	return inconclusive;
}

test_result test_strlen_1_no_match()
{
	return inconclusive;
}
test_result test_strlen_2_no_match()
{
	return inconclusive;
}
test_result test_strlen_3_no_match()
{
	return inconclusive;
}
test_result test_strlen_4_no_match()
{
	return inconclusive;
}
test_result test_strlen_5_no_match()
{
	return inconclusive;
}
test_result test_strlen_6_no_match()
{
	return inconclusive;
}
test_result test_strlen_10_no_match()
{
	return inconclusive;
}
test_result test_strlen_50_no_match()
{
	return inconclusive;
}

test_result test_update__no_match_to_match()
{
	return inconclusive;
}
test_result test_update__match_to_no_match()
{
	return inconclusive;
}

test_result test_no_files()
{
	return inconclusive;
}

#endif
