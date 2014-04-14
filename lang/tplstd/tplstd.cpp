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

// case #1

template <class T> void f1(T) {}
template <class T> class A1 {
	//friend void f1(T);	// results in an unresolved at link time
	friend void f1<T>(T);
public:
	A1() {T t(0); f1(t);}
};

// case #2

template <class T> class A2 {
public:
	typedef int TT;
};
template <class T> class A22 : public A2<T> {
public:
	A22()
	{
		//TT x;   // invalid
		typename A2<T>::TT x;
	}
};

// case #3

int f3glob = 0;
int f3cls = 0;
int x = 0;
void f3() {f3glob = 1;}

template <class T> class A3 {
public:
	int x;
	void f3() {f3cls = 1;}
	A3() {x = 0;}
};
template <class T> class A33 : public A3<T> {
public:
	A33()
	{
		x = 1;		// global
		this->x = 1;
		f3();		// global
		this->f3();
	}
};

int main()
{
	A1<int> a1;
	A22<int> a22;
	A33<int> a33;

	if (f3glob != 1 || f3cls != 1 || x != 1 || a33.x != 1)
		cout << "error in A3/A33" << endl;

	return 0;
}
