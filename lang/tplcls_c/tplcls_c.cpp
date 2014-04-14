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

class A {};

class B : public A {};

template <class T> class Test {};

template <class T> class Ref {
	T* ptr;
public:
	Ref(T* p) {ptr = p;}
	template <class U> operator Ref<U>();
};

template <class T> template <class U> Ref<T>::operator Ref<U>()
{
	cout << "convert T to U" << endl;

	return Ref<U>(ptr);
}

int main()
{
	B b;
	A a = b;			// OK

	Test<B> btest;
	//Test<A> atest = btest;	// invalid

	Ref<B> bref(&b);
	Ref<A> aref = bref;		// OK

	Ref<A> aref2(&a);
	//Ref<B> bref2 = aref2;		// invalid

	return 0;
}
