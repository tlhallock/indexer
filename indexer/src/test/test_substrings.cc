/*
 * test_substrings.cc
 *
 *  Created on: May 31, 2014
 *      Author: thallock
 */

#include "include/export.h"

#if 0


static void print_all(const char *str, int min, int max)
{
	SubstringIterator it(str, min, max);

	printf("'%s' %d-%d:\n", str, min, max);

	while(it.has_next())
	{
		int offset = it.next_offset();
		const char *str = it.next();
		printf("%d: '%s'\n", offset, str);
	}
}

#define SOME_STRING "foobar"

int main(int argc, char **argv)
{
	printf("Start\n");
	printf("--------------------------------------------------------------------\n");
	print_all(SOME_STRING, 0, INT_MAX);
	printf("--------------------------------------------------------------------\n");
	print_all("/", 0, INT_MAX);
	printf("--------------------------------------------------------------------\n");
	print_all("", 0, INT_MAX);
	printf("--------------------------------------------------------------------\n");
	print_all(SOME_STRING, 2, INT_MAX);
	printf("--------------------------------------------------------------------\n");
	print_all(SOME_STRING, 0, 3);
	printf("--------------------------------------------------------------------\n");
	print_all(SOME_STRING, 2, 2);
	printf("--------------------------------------------------------------------\n");
	print_all(SOME_STRING, 0, strlen(SOME_STRING));
	printf("--------------------------------------------------------------------\n");
	print_all(SOME_STRING, 0, 0);
	printf("--------------------------------------------------------------------\n");
	print_all(SOME_STRING, strlen(SOME_STRING), strlen(SOME_STRING));
	printf("--------------------------------------------------------------------\n");
	print_all(SOME_STRING, -50, strlen(SOME_STRING));
	printf("--------------------------------------------------------------------\n");
	print_all(SOME_STRING, 0, -50);
	printf("--------------------------------------------------------------------\n");
	print_all(SOME_STRING, 2, 3);
	printf("--------------------------------------------------------------------\n");
	printf("Stop\n");

	return 0;
}




#endif
