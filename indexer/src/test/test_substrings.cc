/*
 * test_substrings.cc
 *
 *  Created on: May 31, 2014
 *      Author: thallock
 */

#include "test/tests.h"

#include "include/export.h"

void test_substrings(int argc, char **argv)
{
	SubstringIterator it("foobar");

	while(it.has_next())
	{
		printf("%d: %s\n", it.offset(), it.current());
		it.next();
	}
}
