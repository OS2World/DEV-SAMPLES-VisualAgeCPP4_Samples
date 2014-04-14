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

void f1() {cout << "::f1() called" << endl;}
int x = 0;

namespace A {
	void f1() {cout << "A::f1() called" << endl;}
	int x = 0;
}

namespace A {
	void f2() {cout << "A::f2() called" << endl;}
}

int main()
{
	f1();
	A::f1();

	x = 10;
	A::x = 20;

	cout << "x = " << x << endl;
	cout << "A::x = " << A::x << endl;

	return 0;
}
