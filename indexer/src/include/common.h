/*
 * common.h
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "include/config.h"

#include <cstring>
#include <ctime>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <climits>

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

#define BASE_DIR "/home/thallock/.indexes"
#define WORDS_BASE_DIR "/home/thallock/.indexes/words.d"
#define FILES_BASE_DIR "/home/thallock/.indexes/files.d"
#define FILES_FILE "/home/thallock/.indexes/files.txt"

typedef int file_id;

#endif /* COMMON_H_ */
