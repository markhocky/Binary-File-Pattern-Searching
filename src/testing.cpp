/*
 * testing.cpp
 *
 *  Created on: 19Sep.,2016
 *      Author: mark
 */

#include <vector>
#include <iostream>
#include "testing.h"

using namespace std;

const char * testFile() {
	return "Sample Files/test.txt";
}
/*
 * Other example files:
 * "Sample Files/mapsettings.cfg"
 * "Sample Files/mapsettings1.cfg"
 * "Sample Files/mapsettings3.cfg"
 * "/media/sf_D_DRIVE/Uni/Sem152/CSI6110 - Software Development Processes/CSP2151 Lectures.zip"
 * "/media/sf_D_DRIVE/Uni/Sem152/CSI6110 - Software Development Processes/Sommerville - Software Engineering - 9th Ed.pdf"
*/

void checkSAandLCP(vector<int> SA, vector<int> LCP) {
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
