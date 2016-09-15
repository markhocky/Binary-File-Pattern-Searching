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

class Pattern {
	public:
		int position;
		int length;
		int occurrences; // how many times the pattern occurs.
		Pattern(int length, int position, int occurrences);
		int start(vector<int> SA) {
			return SA[this->position]; // returns starting position of pattern
		}
};

bool compareOccurrences(const Pattern &a, const Pattern &b);

vector<Pattern> findPatternsOfLength(int m, vector<int> LCP);

#endif /* PATTERNS_H_ */
