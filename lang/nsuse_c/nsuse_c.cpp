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

namespace A {
	void f() {cout << "A::f() called" << endl;}
}
namespace A_ALIAS = A;
using namespace A_ALIAS;

namespace B {
	void f() {cout << "B::f() called" << endl;}
	void g() {cout << "B::g() called" << endl;}
}
//using namespace B;
using B::g;

int main()
{
	f();
	g();

	return 0;
}
