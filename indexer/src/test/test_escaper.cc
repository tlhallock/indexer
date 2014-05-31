/*
 * test_escaper.cc
 *
 *  Created on: May 31, 2014
 *      Author: thallock
 */

#include "test/tests.h"

#include "include/export.h"

void test_escaper(int argc, char **argv)
{
	const char *str = "'foobar:{}_@^$*(_^LKSHEG(P&$PHLKGJLSDGsgsdg./1`";

	printf("%s\n", str);

	char *ptr = nullptr;
	int size = 0;

	escape(str, ptr, size);

	printf("%s\n", ptr);

	char *ptr2 = nullptr;
	int size2 = 0;

	descape(ptr, ptr2, size2);

	printf("%s\n", ptr2);
}
