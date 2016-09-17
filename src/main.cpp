/*
 * main.cpp
 *
 *  Created on: 14Sep.,2016
 *      Author: mark
 */
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <map>
#include "sanfoundry_suffix_array.h"
#include "DC3.h"
#include "Kasai_LCP.h"
#include "patterns.h"
#include "projectIO.h"

using namespace std;

int main()
{
	const char *file_path = "/media/sf_D_DRIVE/Uni/Sem162/CSG6224 - Special Topic/Project Code/Sample Files/test.txt";
//	const char *file_path = "/media/sf_D_DRIVE/Uni/Sem152/CSI6110 - Software Development Processes/CSP2151 Lectures.zip";
	cout << "Reading: " << file_path << "..." << endl;
	vector<BYTE> inputString = getFileByteVector(file_path);
	cout << "File read successfully:" << endl;
	printHex(inputString, 0, 30);
	cout << endl;

	int n = inputString.size();
	cout << "n = " << n << endl;

	// Note: DC3 algorithm requires integers representing the
	// lexicographic order of the character in the dictionary
	cout << "Creating integer input..." << endl;
	vector<int> inputInts = createIntVector(inputString);

	// Size of dictionary 'K'
    int K = 256;

    vector<int> SA_vec (n+3, 0);
//    int SA[inputString.size() + 3] = {0};

    cout << "Calculating SA..." << endl;
    DC3(inputInts.data(), SA_vec.data(), (int)inputString.size(), K);
//    DC3(inputInts.data(), SA, (int)inputString.size(), K);
//    vector<int> SA_vec;
//    SA_vec.assign(SA, SA + n);

    cout << "Calculating LCP..." << endl;
    vector<int> LCP = kasai(inputString, SA_vec);
    cout << endl << "DC3 SA and LCP:" << endl;
    cout << "SA\tLCP\tSUFFIX" << endl;
    int maxPrint = min(n, 20);
	for (int i = 0; i < maxPrint; i++) {
		cout << SA_vec[i] << "\t"
			 << LCP[i] << "\t";
		printHex(inputString, SA_vec[i], 30);
		cout << endl;
	}

	vector<Pattern> patterns = findPatternsOfLength(4, LCP);
	cout << "\nPatterns found: " << patterns.size() << endl;
	sort(patterns.begin(), patterns.end(), compareOccurrences);


	printf("Common patterns\n");
	int numPrint = min(5, (int)patterns.size());
	for (int i = 0; i < numPrint; i++) {
		Pattern p = patterns[i];
		cout << "Pattern: ";
		printHex(inputString, p.start(SA_vec), p.length);
		cout << ", count: " << p.occurrences << endl;

	}

	// Below is to test SA construction for 'test.txt'
//	  string text = "abbaaabbaaabbacabaabbacab";
//    printf("\n\n");
//    SuffixArray suffixarray(text);
//    printf("Sanfoundry SA:\n");
//    suffixarray.createSuffixArray();

}


