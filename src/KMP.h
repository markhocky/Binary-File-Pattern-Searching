/*
 * KMP.h
 *
 *  Created on: 25Sep.,2016
 *      Author: mark
 */

#ifndef KMP_H_
#define KMP_H_

#include <vector>
#include "patterns.h"

using namespace std;

vector<Pattern> KMPsearch(vector<BYTE> &input, int minLen, int maxLen,
		int numResults, int support);

#endif /* KMP_H_ */
