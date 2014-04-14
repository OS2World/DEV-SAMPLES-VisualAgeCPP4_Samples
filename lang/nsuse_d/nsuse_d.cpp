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

namespace B {
	void g() {cout << "B::g() called" << endl;}
}

namespace C {
	void f() {cout << "C::f() called" << endl;}
	void h() {cout << "C::h() called" << endl;}
}

namespace D {
	using namespace A;
	using namespace B;
	using C::h;
}
using namespace D;

int main()
{
	f();
	g();
	h();

	return 0;
}
