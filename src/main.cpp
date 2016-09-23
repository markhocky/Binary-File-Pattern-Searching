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
#include "sais.h"
#include "Kasai_LCP.h"
#include "sliding_window.h"
#include "patterns.h"
#include "projectIO.h"
#include "testing.h"

using namespace std;

int main( int argc, char *argv[] )
{

	// Check number of inputs
	if (argc < 2) {
		showProgramUsage(argv[0]);
		return 1;
	}

	// Set up input parameters
	const char *file_path;
	int numResults = 20;
	int smallestPattern = 4;
	int biggestPattern = 12;
	string algorithm = "SA_IS";
	vector<string> implementedAlgorithms = {"SA_IS", "SA_DC3", "SW_M", "SW_MV", "KMP"};

	// Get File Path
	string firstArg = argv[1];
	if (firstArg == "-h" || firstArg == "--help") {
		showProgramUsage(argv[0]);
		return 0;
	} else {
		file_path = argv[1];
	}
	//bool testing = false;
	if (strcmp(file_path, "test") == 0) {
		file_path = testFile();
		//testing = true;
	}

	for (int i = 2; i < argc; ++i) {
		string arg = argv[i];
		if (i + 1 != argc) {
			if (arg == "-n" || arg == "--number") {
				numResults = getInputInt(argv[i+1], "");
			} else if (arg == "-p" || arg == "--patternmin") {
				smallestPattern = getInputInt(argv[i+1], "");
			} else if (arg == "-P" || arg == "--patternmax") {
				biggestPattern = getInputInt(argv[i+1], "");
			} else if (arg == "-a" || arg == "algorithm") {
				algorithm = argv[i+1];
			}
		}
	}

	if (smallestPattern > biggestPattern) {
		int temp = smallestPattern;
		smallestPattern = biggestPattern;
		biggestPattern = temp;
	}

	if (find(implementedAlgorithms.begin(), implementedAlgorithms.end(), algorithm) == implementedAlgorithms.end()) {
		cout << "Algorithm: " << algorithm << " not implemented." << endl;
		return 1;
	}

	cout << "Reading: " << file_path << "..." << endl;
	vector<BYTE> inputString = getFileByteVector(file_path);
	int n = inputString.size();
	cout << "File read successfully. Num bytes read: " << n << endl;

	vector<Pattern> patterns;

	if (algorithm == "SA_IS") {
		cout << "Running Induced Sort Suffix Array." << endl;
		cout << "Calculating SA..." << endl;
		// Using SAIS
		vector<int> SA (inputString.size(), 0);
		int result = sais(inputString.data(), SA.data(), n);
		if (result == -1) {
			cerr << "Problem with SAIS calculation" << endl;
		}
		cout << "Calculating LCP..." << endl;
		vector<int> LCP = kasai(inputString, SA);
		patterns = findPatterns(smallestPattern, biggestPattern,
		    		numResults, LCP, SA);

	} else if (algorithm == "SA_DC3") {
		cout << "Running Difference Cover Modulo 3 Suffix Array." << endl;
		// Note: DC3 algorithm requires integers representing the
		// lexicographic order of the character in the dictionary
		vector<int> inputInts = createIntVector(inputString);
		cout << "Calculating SA..." << endl;
		// Using DC3
		int K = 256; // Size of dictionary 'K'
		vector<int> SA = DC3(inputInts, (int)inputString.size(), K);
		cout << "Calculating LCP..." << endl;
		vector<int> LCP = kasai(inputString, SA);
		patterns = findPatterns(smallestPattern, biggestPattern,
		    		numResults, LCP, SA);

	} else if (algorithm == "SW_M") {
		cout << "SW_M not yet implemented." << endl;
		return 1;

	} else if (algorithm == "SW_MV") {
		cout << "Running Sliding Window search using map and vector." << endl;
		cout << "Searching patterns..." << endl;
		patterns = searchPatterns(inputString, smallestPattern, biggestPattern);

	} else if (algorithm == "KMP") {
		cout << "Running Knuth-Morris-Pratt brute force search." << endl;
		cout << "KMP not yet implemented." << endl;
		return 1;
		if (biggestPattern > 6) {
			cout << "Reducing pattern search space, limiting largest pattern to 6" << endl;
		}

	} else {
		cerr << "Algorithm: " << algorithm << " not implemented. Check help for options." << endl;
		return 1;
	}

	printPatterns(patterns, inputString, numResults);

	return 0;
}


