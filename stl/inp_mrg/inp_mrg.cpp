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

inline int absval(int a)
{
	return (a < 0 ? -a : a);
}

bool pred(int a, int b)
{
	return absval(a) < absval(b);
}

int main()
{
	int vec[] = {-5, -13, -29, 8, 19, 37};

	inplace_merge(vec, vec + 3, vec + 6, pred);

	for (int i = 0; i < 6; i++)
		cout << vec[i] << endl;

	return 0;
}
