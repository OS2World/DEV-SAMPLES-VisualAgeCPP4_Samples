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

inline int absval(int a)
{
	return (a < 0 ? -a : a);
}

bool pred(int a, int b)
{
	return absval(a) == absval(b);
}

int main()
{
	int vec1[] = {1, 1, 2, 3, -3, 5, -8, 8, 13, 21};
	vector<int> vec2;

	unique_copy(vec1, vec1 + 10, back_inserter(vec2), pred);

	for (int i = 0; i < vec2.size(); i++)
		cout << vec2[i] << endl;

	return 0;
}
