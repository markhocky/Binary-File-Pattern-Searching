/*
 * Kasai_LCP.h
 *
 *  Created on: 15Sep.,2016
 *      Author: mark
 */

#ifndef KASAI_LCP_H_
#define KASAI_LCP_H_

#include <vector>
#include <string>
#include "projectIO.h"

using namespace std;
vector<int> kasai(string txt, vector<int> suffixArr);
vector<int> kasai(vector<BYTE> txt, vector<int> suffixArr);

#endif /* KASAI_LCP_H_ */
