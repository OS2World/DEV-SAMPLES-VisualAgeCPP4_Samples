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
	vector<int> v(2);

	v[0] = 100;
	v[1] = 200;

	cout << "v[0] = " << v[0] << " " << "v[1] = " << v[1] << endl;
	swap(v[0], v[1]);
	cout << "v[0] = " << v[0] << " " << "v[1] = " << v[1] << endl;

	return 0;
}
