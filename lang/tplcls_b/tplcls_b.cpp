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

#include <vector>
#include <string>
#include <list>
#include <iostream>

using namespace std;

template <class T, template<class, class = allocator<T> > class B>
class C {
	B<T> storage;
public:
	void push(T x) {storage.push_back(x);}
	T top() {return storage.back();}
};

int main()
{
	C<int, vector> c1;
	C<string, list> c2;

	c1.push(37);
	cout << c1.top() << endl;

	c2.push("testing");
	cout << c2.top() << endl;

	return 0;
}
