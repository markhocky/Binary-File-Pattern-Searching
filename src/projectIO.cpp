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
#include <iomanip>
#include "projectIO.h"

using namespace std;

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

void printPatterns(vector<Pattern> patterns, vector<BYTE> input, vector<int> SA, int displayMax) {
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



