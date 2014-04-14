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
#include <vector>

using namespace std;

template <class T> class A {
public:
	void f(int) {}
};

template <class T> void f(T) {}

template class vector<double>;		// instantiate a class
template class A<double>;		// another class
template void A<short>::f(int);		// a member
template void f(long);			// a function

int main()
{
	return 0;
}
