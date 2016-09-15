/*
 * patterns.cpp
 *
 *  Contains algorithms and structures for finding
 *  and reporting on patterns in the string
 */

#include <vector>
#include <iostream>
#include <stdio.h>
#include "patterns.h"

using namespace std;

// Constructor
Pattern::Pattern(int length, int position, int occurrences) {
	this->length = length;
	this->position = position;
	this->occurrences = occurrences;
}

bool compareOccurrences(const Pattern &a, const Pattern &b) {
	// sorts descending order of occurrences
	return a.occurrences > b.occurrences;
}

vector<Pattern> findPatternsOfLength(int m, vector<int> LCP) {
	vector<Pattern> patterns;
	int LCP_len = LCP.size();
	int occ = 0;
	for (int i = 0; i < LCP_len; i++) {
		if (LCP[i] >= m) {
			occ++;
		} else {
			if (occ == 0) continue;
			int position = i - occ;
			occ++;
			patterns.push_back(Pattern(m, position, occ));
			occ = 0;
		}
	}
	return patterns;
}

