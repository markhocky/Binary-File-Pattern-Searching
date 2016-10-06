/*
 * KMP.cpp
 *
 * Algorithm taken from:
 * 	http://igm.univ-mlv.fr/~lecroq/string/node8.html#SECTION0080
 * Modified to work with c++ vectors
 */
#include "KMP.h"
#include <algorithm>

using namespace std;

void preKmp(BYTE *x, int m, int kmpNext[]) {
   int i, j;

   i = 0;
   j = kmpNext[0] = -1;
   while (i < m) {
      while (j > -1 && x[i] != x[j])
         j = kmpNext[j];
      i++;
      j++;
      if (i < m && x[i] == x[j])
         kmpNext[i] = kmpNext[j];
      else
         kmpNext[i] = j;
   }
}

/* KMP inputs
 *
 * x - pattern to search for.
 * m - length of pattern
 * y - the string to look in
 * n - the length of the string
 */

vector<int> KMP(BYTE *x, int m, BYTE *y, int n) {
	vector<int> positions;
    int i, j, kmpNext[m+1];

	/* Preprocessing */
	preKmp(x, m, kmpNext);

	/* Searching */
	i = j = 0;
	while (j < n) {
	  while (i > -1 && x[i] != y[j])
		 i = kmpNext[i];
	  ++i;
	  ++j;
	  if (i >= m) {
		 positions.push_back(j - i);
		 i = kmpNext[i];
	  }
	}
	return positions;
}


vector<Pattern> KMPsearchLength(vector<BYTE> &input, int len, int support) {
	vector<Pattern> patterns;
	vector<int> patternPositions (input.size(), 0);
	int n = (int)input.size();
	for (int i = 0; i < (n - len); ++i) {
		if (patternPositions[i] > 0) {
			continue;
		}
		vector<int> positions = KMP(&input[i], len, &input[i], n - i);
		int occ = (int)positions.size();

		for (vector<int>::iterator pos = positions.begin(); pos != positions.end(); ++pos) {
			patternPositions[*pos + i] = occ;
		}

		Pattern pattern = Pattern(len, i, occ);
		patterns.push_back(pattern);
	}
	sort(patterns.begin(), patterns.end(), compareOccurrences);
	return patterns;
}


vector<Pattern> KMPsearch(vector<BYTE> &input, int minLen, int maxLen,
		int numResults, int support) {
	vector<Pattern> patterns;
	for (int len = minLen; len <= maxLen; ++len) {
		vector<Pattern> pttn = KMPsearchLength(input, len, support);
		// Note we only want to copy over enough results for printing
		int slice = min(numResults, (int)pttn.size());
		patterns.insert(patterns.end(), pttn.begin(), pttn.begin() + slice);
	}
	sort(patterns.begin(), patterns.end(), compareOccurrences);
	return patterns;
}
