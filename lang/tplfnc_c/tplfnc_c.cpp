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

int f(char*) {return 1;}

template <class T> int f(T) {return 2;}

template <class T> int f(T*) {return 3;}

template <> int f<double>(double) {return 4;}

int main()
{
	char* s = "testing";
	char** sp = &s;

	// calls f(char*)
	cout << f(s) << endl;

	// calls f(T*)
	cout << f(sp) << endl;

	// calls f(T)
	cout << f(37) << endl;

	// calls f<double>(double)
	cout << f(12.34) << endl;

	return 0;
}
