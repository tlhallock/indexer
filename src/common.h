/*
 * common.h
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#ifndef COMMON_H_
#define COMMON_H_

//#define __GXX_EXPERIMENTAL_CXX0X__ 1

#include <cstring>
#include <ctime>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>

#include <set>
#include <map>
#include <vector>
#include <memory>
#include <bits/shared_ptr.h>

struct ConstCharComparator
{
   bool operator()(const char * A, const char * B) const
   {
      return strcmp(A, B) < 0;
   }
};

#define DELIMITERS  ".!@#$%^&*()_+-={}|[];':\",.<>/?\\ \t\n\r^`~"
#define MAX_UNREADABLE .1

#define FILE_LIST_PATTERN "/home/thallock/.indexes/file_lists/%ld.%d"
#define FILE_INDEX_PATTERN "/home/thallock/.indexes/indices/%d"
#define WORDS_FILE "/home/thallock/.indexes/words"
#define FILES_FILE "/home/thallock/.indexes/files"


#endif /* COMMON_H_ */
