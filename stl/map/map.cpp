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
#include <iostream>

using namespace std;

int main()
{
	map<string,int> m;

	m["Mary"] = 23;
	m["Harry"] = 25;
	m["Nancy"] = 28;

	m["Perry"];

	typedef map<string,int>::const_iterator Iter;

	for (Iter p = m.begin(); p != m.end(); p++)
		cout << p->first << "," << p->second << endl;

	return 0;
}
