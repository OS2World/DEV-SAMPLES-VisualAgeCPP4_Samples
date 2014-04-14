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
#include <iterator>
#include <iostream>

using namespace std;

int main()
{
	vector<int> vec1(3);
	vector<int> vec2(3);
	vector<int> vec3;

	vec1[0] = 1;
	vec1[1] = 3;
	vec1[2] = 19;

	vec2[0] = 2;
	vec2[1] = 3;
	vec2[2] = 19;

	set_intersection(vec1.begin(), vec1.end(), vec2.begin(),
	    vec2.end(), back_inserter(vec3));

	for (int i = 0; i < vec3.size(); i++)
		cout << vec3[i] << " ";

	cout << endl;

	return 0;
}
