/*
 * IBM VisualAge C++ Professional, Version 4.0
 *
 * Licensed Materials - Property of IBM
 *
 * (C) Copyright IBM Corp. 1998. All Rights Reserved.
 *
 * The following [enclosed] code is sample code created by IBM
 * Corporation.  This sample code is not part of any standard IBM product
 * and is provided to you solely for the purpose of assisting you in the
 * development of your applications.  The code is provided 'AS IS',
 * without warranty of any kind.  IBM shall not be liable for any damages
 * arising out of your use of the sample code, even if they have been
 * advised of the possibility of such damages.
 */

#include <algorithm>
#include <vector>
#include <string>
#include <iterator>
#include <iostream>

using namespace std;

class Compare {
public:
	bool operator()(string s)
	{
		return s[0] == 'a';
	}
};

int main()
{
	vector<string> vecin(3);
	vector<string> vecout;

	vecin[0] = "apple";
	vecin[1] = "banana";
	vecin[2] = "avocado";

	replace_copy_if(vecin.begin(), vecin.end(), back_inserter(vecout),
	    Compare(), "");

	for (int i = 0; i < vecout.size(); i++)
		cout << vecout[i] << endl;

	return 0;
}
