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
#include <cctype>
#include <iostream>

using namespace std;

bool pred(string s)
{
	return isupper(s[0]);
}

int main()
{
	vector<string> vec;

	vec.push_back("apple");
	vec.push_back("peach");
	vec.push_back("Pear");
	vec.push_back("tangerine");

	vector<string>::iterator iter =
	    find_if(vec.begin(), vec.end(), pred);

	cout << *iter << endl;

	return 0;
}
