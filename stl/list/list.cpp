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

#include <algorithm>
#include <list>
#include <iostream>

using namespace std;

int main()
{
	list<int> lst1;
	typedef list<int>::iterator Iter;

	lst1.push_back(37);
	lst1.push_back(21);
	lst1.push_front(19);
	lst1.push_back(47);

	lst1.remove(21);

	cout << "front = " << lst1.front() << endl;
	cout << "back = " << lst1.back() << endl;

	list<int> lst2;

	lst2.push_front(59);
	lst2.push_back(67);
	lst2.push_front(73);

	Iter pos = find(lst1.begin(), lst1.end(), 37);
	lst1.splice(pos, lst2);

	for (Iter p = lst1.begin(); p != lst1.end(); p++)
		cout << *p << endl;

	return 0;
}
