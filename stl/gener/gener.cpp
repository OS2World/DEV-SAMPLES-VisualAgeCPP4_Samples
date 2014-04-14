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

long fac()
{
	static long n = 1;
	static long curr = 1;

	curr *= n++;
	return curr;
}

int main()
{
	long vec[10];

	generate(vec, vec + 10, fac);

	for (int i = 0; i < 10; i++)
		cout << vec[i] << endl;

	return 0;
}
