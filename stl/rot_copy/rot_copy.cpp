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

int main()
{
	string vec1[] = {"apple", "orange", "peach"};
	vector<string> vec2;

	rotate_copy(vec1, vec1 + 2, vec1 + 3, back_inserter(vec2));

	for (int i = 0; i < vec2.size(); i++)
		cout << vec2[i] << endl;

	return 0;
}
