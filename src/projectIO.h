/*
 * projectIO.h
 *
 *  Created on: 17Sep.,2016
 *      Author: mark
 */

#ifndef PROJECTIO_H_
#define PROJECTIO_H_

#include <vector>

typedef unsigned char BYTE;

using namespace std;

vector<BYTE> getFileByteVector(const char* filePath);

vector<int> createIntVector(vector<BYTE> inputString);

void printHex(vector<BYTE> inputString, int pos, int maxLen = 20);

#endif /* PROJECTIO_H_ */
