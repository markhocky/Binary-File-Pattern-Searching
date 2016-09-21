/*
 * sliding_window.cpp
 *
 *  Created on: 21Sep.,2016
 *      Author: mark
 */

#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include "sliding_window.h"

using namespace std;

vector<Pattern> searchPatterns(vector<BYTE> input, int minLen, int maxLen) {
	vector <Pattern> results;
	map <string, int> patternIndex;
	int n = (int)input.size();

	for (int i = 0; i < (n - maxLen); ++i) {

		string patternString (input.begin() + i, input.begin() + i + maxLen);

		if (patternIndex.find(patternString) == patternIndex.end()) {
			// Create pattern
			Pattern pattern = Pattern(maxLen, i, 1);
			results.push_back(pattern);
			patternIndex[patternString] = results.size() - 1;

		} else {
			// increment pattern
			results[patternIndex[patternString]].occurrences += 1;
		}
	}
	sort(results.begin(), results.end(), compareOccurrences);
	return results;
}

