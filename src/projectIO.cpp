/*
 * projectIO.cpp
 *
 *  Created on: 17Sep.,2016
 *      Author: mark
 */
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "projectIO.h"

using namespace std;

void showProgramUsage(string name) {
	cerr << "Usage: " << name
		 << "FILENAME [Options]" << endl
		 << "Options:" << endl
		 << "\t-h, --help\t\tShow this help message." << endl
		 << "\t-n, --number\t\tNumber of results to print (default 20)" << endl
		 << "\t-p, --patternmin\tMin pattern length to search (default 4)" << endl
		 << "\t-P, --patternmax\tMax pattern length to search (default 12)" << endl
		 << "\t-a, --algorithm\t\tSelect the algorithm type:" << endl
		 << "\t\t\t\tSA_IS\tInduced Sorting Suffix Array" << endl
		 << "\t\t\t\tSA_DC3\tDifference Cover Modulo 3 Suffix Array" << endl
		 << "\t\t\t\tSW_M\tSliding window search using map data structure" << endl
		 << "\t\t\t\tSW_MV\tSliding window search using map and vector" << endl
		 << "\t\t\t\tKMP\tKnuth-Morris-Pratt brute force string search, if this " << endl
		 << "\t\t\t\t\tis selected max pattern length limited to 6." << endl;
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

void printHex(vector<BYTE> input, int pos, int maxLen) {
	int printMax = pos + min(maxLen, (int)input.size() - pos);
	for (int i = pos; i < printMax; i++) {
		cout << hex << setfill('0') << setw(2)
				<< (int)input[i] << " ";

	}
	cout << dec;
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



