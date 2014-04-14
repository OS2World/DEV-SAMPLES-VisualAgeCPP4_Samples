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

template <class T, class U> T findmin(U a, U b)
{
	return T(a < b ? a : b);
}

template void f<double>();

template char findmin<char>(double, double);

int main()
{
	f<double>();

	char c = findmin<char>(56.78, 67.89);

	cout << c << endl;

	return 0;
}
