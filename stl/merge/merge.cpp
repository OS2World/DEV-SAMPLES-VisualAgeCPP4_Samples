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
#include <cstring>
#include <string>
#include <iterator>
#include <iostream>

using namespace std;

int main()
{
	char* s1 = "1357";
	char* s2 = "2468";
	basic_string<char> s3;

	merge(s1, s1 + strlen(s1), s2, s2 + strlen(s2), back_inserter(s3));

	cout << s3 << endl;

	return 0;
}
