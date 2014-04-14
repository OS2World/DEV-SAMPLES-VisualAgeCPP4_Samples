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

#include <cstring>
#include <iostream>

using namespace std;

template <class T> class Vector {
public:
	Vector() {cout << "Vector<T>::Vector" << endl;}
};

template <> class Vector<bool> {
public:
	Vector() {cout << "Vector<bool>::Vector" << endl;}
};

template <class T> class Vector<T*> {
public:
	Vector() {cout << "Vector<T*>::Vector" << endl;}
};

template <class T> bool less(T a, T b)
{
	return a < b;
}

template <> bool less(const char* a, const char* b)
{
	return strcmp(a, b) < 0;
}

int main()
{
	Vector<double> v1;
	Vector<char*> v2;
	Vector<bool> v3;

	cout << less(50, 100) << endl;
	cout << less("orange", "apple") << endl;
	cout << less("apple", "orange") << endl;

	return 0;
}
