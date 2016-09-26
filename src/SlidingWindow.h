/*
 * sliding_window.h
 *
 *  Created on: 21Sep.,2016
 *      Author: mark
 */

#ifndef SLIDINGWINDOW_H_
#define SLIDINGWINDOW_H_

#include "patterns.h"

vector<Pattern> searchPatterns(const vector<BYTE> &input, int minLen, int maxLen);
vector<Pattern> searchPatternsMap(const vector<BYTE> &input, int minLen, int maxLen);
vector<Pattern> searchMap(const vector<BYTE> &input, int minLen, int maxLen);

#endif /* SLIDINGWINDOW_H_ */
