/*
 * sanfoundry_suffix_array.h
 *
 *  Created on: 14Sep.,2016
 *      Author: mark
 */

#ifndef SANFOUNDRY_SUFFIX_ARRAY_H_
#define SANFOUNDRY_SUFFIX_ARRAY_H_

#include <string>
using namespace std;

class SuffixArray
{
    private:
        string *text;
        int length;
        int *index;
        string *suffix;

    public:
        SuffixArray(string text);

        void createSuffixArray();
};


#endif /* SANFOUNDRY_SUFFIX_ARRAY_H_ */
