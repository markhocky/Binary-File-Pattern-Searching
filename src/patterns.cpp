/*
 * patterns.cpp
 *
 *  Contains algorithms and structures for finding
 *  and reporting on patterns in the string
 */

#include <vector>
#include <algorithm>
#include "patterns.h"

using namespace std;

// Default Constructor
Pattern::Pattern() {
	this->length = 0;
	this->position = 0;
	this->occurrences = 0;
	this->prefixIndex = -1;
}

// Constructor
Pattern::Pattern(int length, int position, int occurrences) {
	this->length = length;
	this->position = position;
	this->occurrences = occurrences;
	this->prefixIndex = -1;
}

Pattern::Pattern(int length, int position, int occurrences,
		int prefixIndex) {
	this->length = length;
	this->position = position;
	this->occurrences = occurrences;
	this->prefixIndex = prefixIndex;
}

bool Pattern::allZeroes(vector<BYTE> input) {
	bool all_zeroes = true;
	BYTE zero = 0;
	for (int i = position; i < (position + length); ++i) {
		if (input[i] != zero) {
			all_zeroes = false;
			break;
		}
	}
	return all_zeroes;
}

bool compareOccurrences(const Pattern &a, const Pattern &b) {
	// sorts descending order of occurrences
	return a.occurrences > b.occurrences;
}

vector<Pattern> findPatternsOfLength(int m, vector<int> LCP, vector<int> SA) {
	vector<Pattern> patterns;
	int LCP_len = LCP.size();
	int occ = 0;
	for (int i = 0; i < LCP_len; i++) {
		if (LCP[i] >= m) {
			occ++;
		} else {
			if (occ == 0) continue;
			int index = i - occ;
			occ++;
			patterns.push_back(Pattern(m, SA[index], occ));
			occ = 0;
		}
	}
	sort(patterns.begin(), patterns.end(), compareOccurrences);
	return patterns;
}

vector<Pattern> findPatterns(int smallest, int largest, int numResults, vector<int> LCP, vector<int> SA) {
	vector<Pattern> patterns;
    for (int i = smallest; i <= largest; i++) {
    	vector<Pattern> pttn = findPatternsOfLength(i, LCP, SA);
    	// Note we only want to copy over enough results for printing
    	int slice = min(numResults, (int)pttn.size());
    	patterns.insert(patterns.end(), pttn.begin(), pttn.begin() + slice);
    	sort(patterns.begin(), patterns.end(), compareOccurrences);
    }
	return patterns;
}

