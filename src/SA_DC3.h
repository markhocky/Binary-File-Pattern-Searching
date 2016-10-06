/*
 * DC3.h
 *
 *  Created on: 15Sep.,2016
 *      Author: mark
 */

#ifndef SA_DC3_H_
#define SA_DC3_H_

#include <vector>
#include "projectIO.h"

vector<int> createIntVector(vector<BYTE> inputString);

vector<int> DC3(int* inputInts, int n, int K);
vector<int> DC3(vector<int> &inputInts, int n, int K);

#endif /* SA_DC3_H_ */
