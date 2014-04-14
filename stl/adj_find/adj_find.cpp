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
#include <iostream>

using namespace std;

int main()
{
	int vec[] = {1, 2, 3, 5, 5, 5, 8};

	int sz = sizeof(vec) / sizeof(int);

	int* ip = adjacent_find(vec, vec + sz);

	if (ip != vec + sz) {
		int n = *ip;
		do
			cout << *ip++ << " ";
		while (ip != vec + sz && *ip == n);
		cout << endl;
	}
	else {
		cout << "not found" << endl;
	}

	return 0;
}
