/*
 * projectIO.h
 *
 *  Created on: 17Sep.,2016
 *      Author: mark
 */

#ifndef PROJECTIO_H_
#define PROJECTIO_H_

#include <vector>
#include "patterns.h"

using namespace std;

vector<BYTE> getFileByteVector(const char* filePath);

void printSAandLCP(vector<int> SA, vector<int> LCP,
		vector<BYTE> input, int displayMax);

void printHex(vector<BYTE> inputString, int pos, int maxLen = 20);

void printPatterns(vector<Pattern> patterns, vector<BYTE> input, int displayMax);

#endif /* PROJECTIO_H_ */
