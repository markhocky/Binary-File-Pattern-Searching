/*
 * main.cpp
 *
 *  Created on: 14Sep.,2016
 *      Author: mark
 */
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <time.h>

#include "Kasai_LCP.h"
#include "KMP.h"
#include "patterns.h"
#include "projectIO.h"
#include "SA_DC3.h"
#include "SA_IS.h"
#include "SW_M_MV.h"

using namespace std;

// This timer struct taken from RAMitchell
// https://github.com/RAMitchell/prefix_doubling/blob/master/prefix_doubling/main.cpp
struct Timer{
	size_t start;
	Timer(){
		reset();
	}
	void reset(){
		start = clock();
	}
	double elapsed(){
		return ((double)clock() - start) / CLOCKS_PER_SEC;
	}
	void printElapsed(string label){
		cout << label << ": " << elapsed() << "s\n";
	}
};


int main( int argc, char *argv[] )
{
	// Set up input parameters
	vector<BYTE> inputString;
	int numResults;
	int smallestPattern;
	int biggestPattern;
	string algorithm;
	bool verbose;

	printMemUsage("Program start.");

	int errors = getParameters(argc, argv, inputString,
			numResults, smallestPattern, biggestPattern, algorithm,
			verbose);
	if (errors != 0) {
		return 1;
	}

	// Start of pattern searching.
	Timer timer;
	vector<Pattern> patterns;

	if (algorithm == "SA_IS") {
		if (verbose) {
			printOut("Running Induced Sort Suffix Array.");
			printOut("Calculating SA...");
		}
		// Using SAIS
		vector<int> SA (inputString.size(), 0);
		int result = sais(inputString.data(), SA.data(), (int)inputString.size());
		if (result == -1) {
			printError("Problem with SAIS calculation");
		}
		if (verbose) {
			printOut("Calculating LCP...");
		}
		vector<int> LCP = kasai(inputString, SA);
		patterns = findPatterns(smallestPattern, biggestPattern,
		    		numResults, LCP, SA);

	} else if (algorithm == "SA_DC3") {
		if (verbose) printOut("Running Difference Cover Modulo 3 Suffix Array.");
		// Note: DC3 algorithm requires integers representing the
		// lexicographic order of the character in the dictionary
		vector<int> inputInts = createIntVector(inputString);
		if (verbose) printOut("Calculating SA...");
		// Using DC3
		int K = 256; // Size of dictionary 'K'
		vector<int> SA = DC3(inputInts, (int)inputString.size(), K);
		if (verbose) printOut("Calculating LCP...");
		vector<int> LCP = kasai(inputString, SA);
		patterns = findPatterns(smallestPattern, biggestPattern,
		    		numResults, LCP, SA);

	} else if (algorithm == "SW_M") {
		if (verbose) {
			printOut("Running Sliding Window search using map.");
			printOut("Searching patterns...");
		}
		patterns = searchPatternsMap(inputString, smallestPattern, biggestPattern);

	} else if (algorithm == "SW_MV") {
		if (verbose) {
			printOut("Running Sliding Window search using map and vector.");
			printOut("Searching patterns...");
		}
		patterns = searchPatterns(inputString, smallestPattern, biggestPattern);

	} else if (algorithm == "KMP") {
		if (verbose) printOut("Running Knuth-Morris-Pratt search.");
		// Support is the minimum number of occurrences required before a pattern
		// is reported on.
		int support = 2;
		patterns = KMPsearch(inputString, smallestPattern, biggestPattern, numResults, support);


	} else {
		printError("Algorithm: " + algorithm + " not implemented. Check help for options.");
		return 1;
	}
	timer.printElapsed(algorithm + " search time");
	printMemUsage("After search.");

	printPatterns(patterns, inputString, numResults);
	printMemUsage("At conclusion.");

	return 0;
}


