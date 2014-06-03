/*
 * common.h
 *
 *  Created on: May 26, 2014
 *      Author: thallock
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <cstring>
#include <ctime>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <climits>
#include <cstdio>

#include <set>
#include <map>
#include <vector>
#include <memory>
#include <bits/shared_ptr.h>

#if 0
	#include <unordered_map>
#else
	#include <boost/unordered_map.hpp>
#endif

typedef int FileId;

char *concatenate(const char *str1, const char *str2);

#include "app/Settings.h"

#endif /* COMMON_H_ */
