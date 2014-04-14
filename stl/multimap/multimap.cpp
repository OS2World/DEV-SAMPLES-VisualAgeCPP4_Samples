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

#include <map>
#include <string>
#include <utility>
#include <iostream>

using namespace std;

int main()
{
	multimap<string,int> m;

	m.insert(make_pair("Harry", 32));
	m.insert(make_pair("Mary", 59));
	m.insert(make_pair("Roger", 18));
	m.insert(make_pair("Nancy", 37));
	m.insert(make_pair("Mary", 23));

	typedef multimap<string,int>::const_iterator Iter;

	for (Iter p = m.begin(); p != m.end(); p++)
		cout << p->first << "," << p->second << endl;

	return 0;
}
