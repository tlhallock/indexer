/*
 * recurse.cc
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>

void recurse_all_children(const char *dir,void (*fctn)(const int, const char *))
{
	struct dirent *dp;
	DIR *dfd;

	if ((dfd = opendir(dir)) == NULL)
	{
		printf("Skipping \"%s\"\n", dir);
		return;
	}

	while ((dp = readdir(dfd)) != NULL)
	{
		struct stat stbuf;

		int child_len = strlen(dp->d_name);
		if (child_len == 1 && dp->d_name[0] == '.')
		{
			continue;
		}
		if (child_len == 2 && dp->d_name[0] == '.' && dp->d_name[1] == '.')
		{
			continue;
		}

		int clen = 1 + strlen(dir) + child_len;
		char *childname = (char *) malloc ((1 + clen) * sizeof(*childname));
		sprintf(childname, "%s/%s", dir, dp->d_name);

		if (stat(childname, &stbuf) == -1)
		{
			printf("Skipping \"%s\"\n", childname);
			free(childname);
			continue;
		}

		if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
		{
			recurse_all_children(childname, fctn);
			free(childname);
			continue;
		}

		// Process file
		fctn(clen, childname);
		free(childname);
	}
}
