/*
 * projectIO.cpp
 *
 *  Created on: 17Sep.,2016
 *      Author: mark
 */
#include <string>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "projectIO.h"
#include "MemUsage.h"
#include "testing.h"

using namespace std;

void showProgramUsage(string name) {
	cerr << "Usage: " << name
		 << "FILENAME [Options]" << endl
		 << "Options:" << endl
		 << "\t-h, --help\t\tShow this help message." << endl
		 << "\t-v, --verbose\t\tSwitch on verbose output." << endl
		 << "\t-n, --number\t\tNumber of results to print (default 20)" << endl
		 << "\t-p, --patternmin\tMin pattern length to search (default 4)" << endl
		 << "\t-P, --patternmax\tMax pattern length to search (default 12)" << endl
		 << "\t-a, --algorithm\t\tSelect the algorithm type:" << endl
		 << "\t\t\t\tSA_IS\tInduced Sorting Suffix Array" << endl
		 << "\t\t\t\tSA_DC3\tDifference Cover Modulo 3 Suffix Array" << endl
		 << "\t\t\t\tSW_M\tSliding window search using map data structure" << endl
		 << "\t\t\t\tSW_MV\tSliding window search using map and vector" << endl
		 << "\t\t\t\tKMP\tKnuth-Morris-Pratt string search." << endl;
}

int getInputInt(string arg, string errorMessage) {
	istringstream ss(arg);
	int input;
	if (!(ss >> input)) {
		cerr << errorMessage << ": " << arg << endl;
	}
	return input;
}

vector<BYTE> getFileByteVector(const char* filePath) {
	BYTE *fileString;
	streampos size;
	ifstream file (filePath, ios::in|ios::binary|ios::ate);
	if (file.is_open()) {
		size = file.tellg();
		fileString = new BYTE[size];
		file.seekg(0, ios::beg);
		file.read((char*)fileString, size);
		file.close();
	} else {
		cout << "Could not open file." << endl;
		throw exception();
	}
	vector<BYTE> byteString;
	byteString.assign(fileString, fileString + size);
	return byteString;
}

int getParameters(int argc, char *argv[],
		vector<BYTE> &inputString, int &numResults,
		int &smallestPattern, int &biggestPattern, string &algorithm,
		bool &verbose) {
	// Check number of inputs
	if (argc < 2) {
		showProgramUsage(argv[0]);
		return 1;
	}

	// Set up input parameters
	const char *file_path;
	numResults = 20;
	smallestPattern = 4;
	biggestPattern = 12;
	algorithm = "SA_IS";

	// Get File Path
	string firstArg = argv[1];
	if (firstArg == "-h" || firstArg == "--help") {
		showProgramUsage(argv[0]);
		return 1;
	} else {
		file_path = argv[1];
	}
	if (strcmp(file_path, "test") == 0) {
		file_path = testFile();
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
			} else if (arg == "-a" || arg == "--algorithm") {
				algorithm = argv[i+1];
			}
		}
		if (arg == "-v" || arg == "--verbose") {
			verbose = true;
		}
	}

	if (smallestPattern > biggestPattern) {
		int temp = smallestPattern;
		smallestPattern = biggestPattern;
		biggestPattern = temp;
	}

	if (verbose) {
		printOut("Reading: " + (string)file_path);
	}
	inputString = getFileByteVector(file_path);
	if (verbose) {
		int n = inputString.size();
		cout << "File read successfully. Num bytes read: " << n << endl;
	}
	return 0;
}

void printHex(vector<BYTE> input, int pos, int maxLen) {
	int printMax = pos + min(maxLen, (int)input.size() - pos);
	for (int i = pos; i < printMax; i++) {
		cout << hex << setfill('0') << setw(2)
				<< (int)input[i] << " ";

	}
	cout << dec;
}

void printOut(string output) {
	cout << output << endl;
}

void printError(string message) {
	cerr << message << endl;
}

void printMemUsage(string tag) {
	double vm, rss;
	process_mem_usage(vm, rss);
	cout << tag
		 << " VM: " << vm
		 << "; RSS: " << rss << endl;
}

void printSAandLCP(vector<int> SA, vector<int> LCP, vector<BYTE> input, int displayMax) {
    // Print the SA and LCP arrays
    cout << endl << "DC3 SA and LCP:" << endl;
    cout << "SA\tLCP\tSUFFIX" << endl;
    int maxPrint = min((int)input.size(), displayMax);
	for (int i = 0; i < maxPrint; i++) {
		cout << SA[i] << "\t"
			 << LCP[i] << "\t";
		printHex(input, SA[i], 30);
		cout << endl;
	}
}

void printPatterns(vector<Pattern> patterns, vector<BYTE> input, int displayMax) {
	cout << "\n#\tCount\tPattern" << endl;
	int numPrint = min(displayMax, (int)patterns.size());
	int rowNum = 1;
	for (int i = 0; i < numPrint; ++i) {
		Pattern p = patterns[i];
		if (p.allZeroes(input)) {
			++numPrint;
			continue;
		} else {
			cout << rowNum++ << "\t";
			cout << p.occurrences << "\t";
			printHex(input, p.position, p.length);
			cout << endl;
		}

	}
}



