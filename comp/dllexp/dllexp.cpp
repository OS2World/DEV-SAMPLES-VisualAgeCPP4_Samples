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

#include "share.h"

using namespace std;

int main()
{
	int i;

	i = x1;			// globals
	i = x2;
	i = f1();
	i = f2();

	A a;			// constructor
	i = a.f1();		// regular function
	i = a.f3();		// static funcion
	i = a + 37;		// operator function
//???	i = a;			// conversion operator
	i = A::x1;		// static data member
	//i = A::x2;		// unexported static data member
	i = a.g(25);		// overloaded member function
	//i = a.g(12.34);	// unexported overloaded member function

	B b;			// constructor
	i = b.f1();		// regular function
	i = b.f3();		// static funcion
	i = b + 37;		// operator function
	i = b;			// conversion operator
	i = B::x1;		// static data member
	//i = B::x2;		// unexported static data member
	i = b.g(25);		// overloaded member function
	//i = b.g(12.34);	// unexported overloaded member function

	C c;
	i = c.f();		// regular function
	i = c.g();		// static function

	return 0;
}
