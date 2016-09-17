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
	}
	vector<BYTE> byteString;
	byteString.assign(fileString, fileString + size);
	return byteString;
}

vector<int> createIntVector(vector<BYTE> inputString) {
	vector<int> output (inputString.size() + 3, 0);
	for (vector<int>::size_type i = 0; i < inputString.size(); ++i) {
		output[i] = inputString[i];
	}
	return output;
}

void printHex(vector<BYTE> input, int pos, int maxLen) {
	int printMax = pos + min(maxLen, (int)input.size() - pos);
	for (int i = pos; i < printMax; i++) {
		cout << hex << setfill('0') << setw(2)
				<< (int)input[i] << " ";

	}
	cout << dec;
}

