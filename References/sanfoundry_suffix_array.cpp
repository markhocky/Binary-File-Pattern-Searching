/*
 * sanfoundry_suffix_array.cpp
 *
 * Copied from: http://www.sanfoundry.com/cpp-program-implement-suffix-array/
 */

/*
 * C++ Program to Implement Suffix Array
 */
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include "sanfoundry_suffix_array.h"

using namespace std;

// Constructor
SuffixArray::SuffixArray(string text)
{
	this->text = new string[text.length()];
	for (unsigned int i = 0; i < text.length(); i++)
	{
		this->text[i] = text.substr(i, 1);
	}
	this->length = text.length();
	this->index = new int[length];
	for (int i = 0; i < length; i++)
	{
		index[i] = i;
	}
	suffix = new string[length];
}


void SuffixArray::createSuffixArray()
{
	for(int ix = 0; ix < length; ix++)
	{
		string text = "";
		for (int text_index = ix; text_index < length; text_index++)
		{
			text += this->text[text_index];
		}
		suffix[ix] = text;
	}
	int back;
	for (int iteration = 1; iteration < length; iteration++)
	{
		string key = suffix[iteration];
		int keyindex = index[iteration];
		for (back = iteration - 1; back >= 0; back--)
		{
			if (suffix[back].compare(key) > 0)
			{
				suffix[back + 1] = suffix[back];
				index[back + 1] = index[back];
			}
			else
			{
				break;
			}
		}
		suffix[back + 1] = key;
		index[back + 1 ] = keyindex;
	}
	cout<<"INDEX \tSUFFIX"<<endl;
	for (int iterate = 0; iterate < length; iterate++)
	{
		cout<<index[iterate] << "\t" << suffix[iterate]<<endl;
	}
}



