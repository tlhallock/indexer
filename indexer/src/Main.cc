/*
 * Main.cc
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include "export.h"

int main(int argc, char **argv)
{

#if 1
	SubstringIterator it("foobar");

	while(it.has_next())
	{
		printf("%d: %s\n", it.offset(), it.current());
		it.next();
	}

#elif 0
	delete_file(BASE_DIR);

	const char *str = "foo";

	index_all(".");

	std::cout << "Number of files: " << get_file_manager().get_num_files() << "\n";
	std::cout << "Files containing " << str << ":\n";

	double time = query(str);
	std::cout << "Took " << time << "ms\n";

	fflush(stdout);

	get_file_manager().write(FILES_FILE);
#elif 0

	const char *str = "'foobar:{}_@^$*(_^LKSHEG(P&$PHLKGJLSDGsgsdg./1`";

	//	void escape(const char *in, char *&out, int &out_size);
	//	void descape(const char *in, char *out, int &out_size);

	printf("%s\n", str);


	char *ptr = nullptr;
	int size = 0;

	escape(str, ptr, size);

	printf("%s\n", ptr);

	char *ptr2 = nullptr;
	int size2 = 0;

	descape(ptr, ptr2, size2);

	printf("%s\n", ptr2);
#endif

	return 0;
}
