/*
 * projectIO.h
 *
 *  Created on: 17Sep.,2016
 *      Author: mark
 */

#ifndef PROJECTIO_H_
#define PROJECTIO_H_

#include <string>
#include <vector>
#include "patterns.h"

using namespace std;

int getParameters(int argc, char *argv[],
		vector<BYTE> &inputString, int &numResults,
		int &smallestPattern, int &biggestPattern, string &algorithm,
		bool &verbose);

void printOut(string output);
void printError(string message);

void printMemUsage(string tag = "");

void printSAandLCP(vector<int> SA, vector<int> LCP,
		vector<BYTE> input, int displayMax);

void printHex(vector<BYTE> inputString, int pos, int maxLen = 20);

void printPatterns(vector<Pattern> patterns, vector<BYTE> input, int displayMax);

#endif /* PROJECTIO_H_ */
