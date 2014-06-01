/*
 * test_substrings.cc
 *
 *  Created on: May 31, 2014
 *      Author: thallock
 */

#include "include/export.h"

#if 0
int main(int argc, char **argv)
{
	SubstringIterator it("foobar");

	while(it.has_next())
	{
		printf("%d: %s\n", it.offset(), it.current());
		it.next();
	}

	return 0;
}

#endif
