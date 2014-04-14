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

int vec1[] = {3, -5, -17, 1, -3, -5, 17, 19};
int vec2[] = {3, -5, -17};

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
	int* p = find_end(vec1, vec1 + 8, vec2, vec2 + 3, pred);

	if (p == vec1 + 8)
		cout << "not found" << endl;
	else
		cout << "found at offset " << p - vec1 << endl;

	return 0;
}
