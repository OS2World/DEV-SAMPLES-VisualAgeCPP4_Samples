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

int vec1[] = {1, 2, 3, 4, 5};
int vec2[] = {1, 2, 3, 5, 4};

int main()
{
	pair<int*, int*> p = mismatch(vec1, vec1 + 5, vec2);

	cout << "element value in first sequence = " << *p.first << endl;
	cout << "element value in second sequence = " << *p.second << endl;

	return 0;
}
