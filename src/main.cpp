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
#include "DC3.h"
#include "Kasai_LCP.h"
#include "patterns.h"
#include "projectIO.h"
#include "testing.h"

using namespace std;

int main( int argc, char *argv[] )
{
	// Check input arguments
	const char *file_path = argv[1];
	bool testing = false;
	if (strcmp(file_path, "test") == 0) {
		file_path = testFile();
		testing = true;
	}

	// Get numeric arguments;
	istringstream ss2(argv[2]);
	int numResults;
	if (!(ss2 >> numResults)) {
		cerr << "Invalid results number: " << argv[2] << endl;
	}

	istringstream ss3(argv[3]);
	int smallestPattern;
	if (!(ss3 >> smallestPattern)) {
		cerr << "Invalid pattern length: " << argv[3] << endl;
	}

	istringstream ss4(argv[4]);
	int biggestPattern;
	if (!(ss4 >> biggestPattern)) {
		cerr << "Invalid pattern length: " << argv[4] << endl;
	}

	cout << "Reading: " << file_path << "..." << endl;
	vector<BYTE> inputString = getFileByteVector(file_path);
	int n = inputString.size();
	cout << "File read successfully. Num bytes read: " << n << endl;

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
    printSAandLCP(SA, LCP, inputString, 30);

    vector<Pattern> patterns = findPatterns(smallestPattern, biggestPattern,
    		numResults, LCP, SA);
	printPatterns(patterns, inputString, SA, numResults);

	if (testing) {
		checkSAandLCP(SA, LCP);
	}
	return 0;
}


