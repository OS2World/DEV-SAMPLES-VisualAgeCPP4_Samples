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
#include <utility>
#include <iostream>

using namespace std;

int vec[] = {1, -3, 5, 19, -25, 37, 59, -59, 79, -101};

inline int absval(int i)
{
	return (i < 0 ? -i : i);
}

class Compare {
public:
	bool operator()(int a, int b)
	{
		return absval(a) < absval(b);
	}
};

int main()
{
	pair<int*, int*> p = equal_range(vec, vec + 10, 59, Compare());

	int* ipfirst = p.first;
	int* iplast = p.second;

	while (ipfirst < iplast) {
		cout << *ipfirst << endl;
		ipfirst++;
	}

	return 0;
}
