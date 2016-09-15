/*
 * main.cpp
 *
 *  Created on: 14Sep.,2016
 *      Author: mark
 */
#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <map>
#include "sanfoundry_suffix_array.h"
#include "DC3.h"
#include "Kasai_LCP.h"
#include "patterns.h"

using namespace std;

int main()
{

	string text = "abbaaabbaaabbacabaabbacab";
	int n = text.size();

	// Note: DC3 algorithm requires integers representing the
	// lexicographic order of the character in the dictionary
	map<char, int> dict;
	dict['a'] = 1;
	dict['b'] = 2;
	dict['c'] = 3;

	int T[n+3] = {0};
	for (int i = 0; i < n; i++) {
		T[i] = dict[text[i]];
	}

    int K = dict.size();
    int SA[n + 3] = {0};

    DC3(T, SA, n, K);

    vector<int> SA_vec;
    SA_vec.assign(SA, SA + n);

    vector<int> LCP = kasai(text, SA_vec);
    printf("\nDC3 SA and LCP:\n");
    printf("SA\tLCP\tSUFFIX\n");
	for (int i = 0; i < n; i++) {
		cout << SA[i] << "\t"
			 << LCP[i] << "\t"
			 << text.substr(SA[i], n) << endl;
	}

	vector<Pattern> patterns = findPatternsOfLength(4, LCP);
	cout << "\nPatterns found: " << patterns.size() << endl;
	sort(patterns.begin(), patterns.end(), compareOccurrences);


	printf("Common patterns\n");
	for (unsigned int i = 0; i < patterns.size(); i++) {
		Pattern p = patterns[i];

		string substring = text.substr(p.start(SA_vec), p.length);
		cout << "Pattern: " << substring
				<< ", count: " << p.occurrences << endl;
	}


//    printf("\n\n");
//    SuffixArray suffixarray(text);
//    printf("Sanfoundry SA:\n");
//    suffixarray.createSuffixArray();

}


