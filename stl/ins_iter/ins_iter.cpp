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
#include <iterator>
#include <iostream>

using namespace std;

int main()
{
	vector<int> vec;

	vec.push_back(5);
	vec.push_back(17);
	vec.push_back(23);

	insert_iterator < vector<int> > iter =
	    inserter(vec, vec.begin() + 1);

	*iter++ = 11;
	*iter++ = 16;

	for (int i = 0; i < vec.size(); i++)
		cout << vec[i] << endl;

	return 0;
}
