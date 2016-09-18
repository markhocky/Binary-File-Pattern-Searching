/*
 * main.cpp
 *
 *  Created on: 14Sep.,2016
 *      Author: mark
 */
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include "sanfoundry_suffix_array.h"
#include "DC3.h"
#include "Kasai_LCP.h"
#include "patterns.h"
#include "projectIO.h"

using namespace std;

int main( int argc, char *argv[] )
{
	// Check input args
	const char *file_path = argv[1];
	bool testing = false;
	if (strcmp(file_path, "test") == 0) {
		file_path = "/media/sf_D_DRIVE/Uni/Sem162/CSG6224 - Special Topic/Project Code/Sample Files/test.txt";
		testing = true;
	}

	// Get numeric arguments;
	istringstream ss2(argv[2]);
	int patternLength;
	if (!(ss2 >> patternLength)) {
		cerr << "Invalid pattern length: " << argv[2] << endl;
	}

	istringstream ss3(argv[3]);
	int numResults;
	if (!(ss3 >> numResults)) {
		cerr << "Invalid pattern length: " << argv[3] << endl;
	}

	/*
	 * Other example files:
		"/media/sf_D_DRIVE/Uni/Sem152/CSI6110 - Software Development Processes/CSP2151 Lectures.zip"
	*/
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

    cout << "Calculating SA..." << endl;
    vector<int> SA = DC3(inputInts, (int)inputString.size(), K);

    cout << "Calculating LCP..." << endl;
    vector<int> LCP = kasai(inputString, SA);

    // Print the SA and LCP arrays
    printSAandLCP(SA, LCP, inputString);

	vector<Pattern> patterns = findPatternsOfLength(patternLength, LCP);
	printPatterns(patterns, inputString, SA, numResults);

	if (testing) {
		// Compare SA and LCP for text.txt
		vector<int> expected_SA {3,8,4,17,9,23,15,0,5,18,10,21,13,24,2,7,16,20,12,1,6,19,11,22,14};
		vector<int> expected_LCP {6,2,5,8,1,2,2,9,4,7,1,4,0,1,7,3,2,5,1,8,3,6,0,3,0};

		if (SA != expected_SA) {
			cout << "\nSA error:" << endl;
			for (vector<int>::size_type i = 0; i < expected_SA.size(); ++i) {
				if (expected_SA[i] != SA[i]) {
					cout << "Mismatch pos " << i << ": Expected "
							<< expected_SA[i] << ", Got "
							<< SA[i] << endl;
				}
			}
		} else {
			cout << "\nSA build ok." << endl;
		}
		if (LCP != expected_LCP) {
			cout << "\nLCP error" << endl;
			for (vector<int>::size_type i = 0; i < expected_LCP.size(); ++i) {
				if (expected_LCP[i] != LCP[i]) {
					cout << "Mismatch pos " << i << ": Expected "
							<< expected_LCP[i] << ", Got "
							<< LCP[i] << endl;
				}
			}
		} else {
			cout << "LCP build ok." << endl;
		}
	}
	return 0;
}


