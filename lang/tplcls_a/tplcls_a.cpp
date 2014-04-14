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

template <class T> class A {
public:
	void f() {cout << "A<T>::f()" << endl;}
};

template <class T, class U = int> class B {
public:
	void f() {cout << "sizeof U = " << sizeof(U) << endl;}
};

template <class T, int N = 100> class C {
public:
	void f() {cout << "N = " << N << endl;}
};

template <class T, template<class> class U = A> class D {
public:
	void f() {U<int> u; u.f();}
};

int main()
{
	B<short, char> b1;
	B<float> b2;
	b1.f();
	b2.f();

	C<long, 200> c1;
	C<short> c2;
	c1.f();
	c2.f();

	D<int> d1;
	d1.f();

	return 0;
}
