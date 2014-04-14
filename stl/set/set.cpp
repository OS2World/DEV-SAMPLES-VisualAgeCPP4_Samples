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

#include <set>
#include <iostream>

using namespace std;

int main()
{
	set<int> s;

	s.insert(1);
	s.insert(5);
	s.insert(4);
	s.insert(2);
	s.insert(2);

	if (s.find(5) != s.end())
		cout << "5 is in the set" << endl;

	s.erase(4);

	for (set<int>::iterator ip = s.begin(); ip != s.end(); *ip++)
		cout << *ip << endl;

	return 0;
}
