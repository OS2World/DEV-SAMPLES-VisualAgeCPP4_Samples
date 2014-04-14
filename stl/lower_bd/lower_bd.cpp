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
	vector<int> vec(5);
	typedef vector<int>::iterator Iter;

	vec[0] = 1;
	vec[1] = 2;
	vec[2] = 2;
	vec[3] = 2;
	vec[4] = 3;

	Iter i = lower_bound(vec.begin(), vec.end(), 2);
	Iter j = upper_bound(vec.begin(), vec.end(), 2);

	while (i < j) {
		cout << *i << endl;
		i++;
	}

	return 0;
}
