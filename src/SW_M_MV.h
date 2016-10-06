/*
 * sliding_window.h
 *
 *  Created on: 21Sep.,2016
 *      Author: mark
 */

#ifndef SW_M_MV_H_
#define SW_M_MV_H_

#include "patterns.h"

vector<Pattern> searchPatterns(const vector<BYTE> &input, int minLen, int maxLen);
vector<Pattern> searchPatternsMap(const vector<BYTE> &input, int minLen, int maxLen);
vector<Pattern> searchMap(const vector<BYTE> &input, int minLen, int maxLen);

#endif /* SW_M_MV_H_ */
