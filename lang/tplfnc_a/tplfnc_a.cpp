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

#include <iostream>

using namespace std;

template <class T> void f()
{
}

template <class T> T findmin(T a, T b)
{
	return (a < b ? a : b);
}

template <class T, class U> T findmax(U a, U b)
{
	return T(a > b ? a : b);
}

int main()
{
	f<double>();

	// (invalid) cout << findmin(10, 12.3456) << endl;
	cout << findmin<double>(10, 12.3456) << endl;

	short s = findmax<short>(12.34, 23.45);
	cout << s << endl;

	return 0;
}
