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

#include <list>
#include <iterator>
#include <iostream>

using namespace std;

int main()
{
	list<int> lst;

	lst.push_back(5);
	lst.push_back(17);
	lst.push_back(23);

	front_insert_iterator < list<int> > iter = front_inserter(lst);

	*iter++ = 11;
	*iter++ = 16;

	for (list<int>::iterator i = lst.begin(); i != lst.end(); i++)
		cout << *i << endl;

	return 0;
}
