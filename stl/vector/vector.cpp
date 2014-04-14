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
#include <iostream>

using namespace std;

int main()
{
	vector<int> vec;

	typedef vector<int>::iterator Iter;

	vec.push_back(47);
	vec.push_back(101);
	vec.push_back(201);
	vec.push_back(213);

	vec[0] = 48;

	Iter p = find(vec.begin(), vec.end(), 101);
	vec.insert(p, 100);

	p = find(vec.begin(), vec.end(), 201);
	vec.erase(p);

	for (int i = 0; i < vec.size(); i++)
		cout << vec[i] << endl;

	return 0;
}
