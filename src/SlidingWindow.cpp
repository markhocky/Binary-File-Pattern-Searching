/*
 * sliding_window.cpp
 *
 *  Created on: 21Sep.,2016
 *      Author: mark
 */

#include "SlidingWindow.h"

#include <iostream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;


void incrementPattern(vector<Pattern> &patterns, int index) {
	Pattern pattern = patterns[index];
	pattern.occurrences++;
	patterns[index] = pattern;
	if (pattern.prefixIndex >= 0) {
		incrementPattern(patterns, pattern.prefixIndex);
	}
}

int getIndex(string patternString, vector <Pattern> &results,
				map <string, int> &index, int pos, int minLen) {

	int len = (int)patternString.length();

	if (len < minLen) {
		return -1;
	}

	int patternIndex;

	if (index.find(patternString) == index.end()) {
		// Create pattern
		string prefixString = patternString.substr(0, len - 1);
		int prefixIndex = getIndex(prefixString, results, index, pos, minLen);
		Pattern pattern = Pattern(len, pos, 1, prefixIndex);
		results.push_back(pattern);
		patternIndex = results.size() - 1;
		index[patternString] = patternIndex;

	} else {
		// increment pattern
		patternIndex = index[patternString];
		incrementPattern(results, patternIndex);
	}
	return patternIndex;
}


vector<Pattern> searchPatterns(const vector<BYTE> &input, int minLen, int maxLen) {
	vector <Pattern> patterns;
	map <string, int> index;
	int n = (int)input.size();
	for (int i = 0; i <= (n - minLen); ++i) {
		int endPos = min(n, i + maxLen);
		string patternString (input.begin() + i, input.begin() + endPos);
		getIndex(patternString, patterns, index, i, minLen);
	}
	sort(patterns.begin(), patterns.end(), compareOccurrences);
	return patterns;
}

vector<Pattern> searchPatternsMap(const vector<BYTE> &input, int minLen, int maxLen) {
	vector <Pattern> patterns;
	map <string, Pattern> index;
	int n = (int)input.size();
	for (int i = 0; i <= (n - minLen); ++i) {
		int endPos = min(n, i + maxLen);
		string patternString (input.begin() + i, input.begin() + endPos);

		while ((int)patternString.length() >= minLen) {
			int len = (int)patternString.length();
			if (index.find(patternString) == index.end()) {
				// Create pattern
				Pattern pattern = Pattern(len, i, 1);
				index[patternString] = pattern;
			} else {
				index[patternString].occurrences++;
			}
			patternString = patternString.substr(0, len - 1);
		}
	}
	for( map<string, Pattern>::iterator it = index.begin(); it != index.end(); ++it ) {
		patterns.push_back(it->second);
	}
	sort(patterns.begin(), patterns.end(), compareOccurrences);
	return patterns;
}

