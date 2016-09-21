/*
 * patterns.h
 *
 *  Created on: 15Sep.,2016
 *      Author: mark
 */

#ifndef PATTERNS_H_
#define PATTERNS_H_

#include <vector>

using namespace std;

typedef unsigned char BYTE;

class Pattern {
	public:
		int position;
		int length;
		int occurrences; // how many times the pattern occurs.
		// Constructors
		Pattern();
		Pattern(int length, int position, int occurrences);
		// Functions
		bool allZeroes(vector<BYTE> input);
};

bool compareOccurrences(const Pattern &a, const Pattern &b);

vector<Pattern> findPatternsOfLength(int m, vector<int> LCP, vector<int> SA);
vector<Pattern> findPatterns(int start, int end, int numResults, vector<int> LCP, vector<int> SA);

#endif /* PATTERNS_H_ */
