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
#include <string>
#include <iostream>

using namespace std;

inline int absval(int a)
{
	return (a < 0 ? -a : a);
}

class Compare {
public:
	bool operator()(int a, int b)
	{
		return absval(a) < absval(b);
	}
};

string s1 = "abc";
string s2 = "abd";

int vec1[] = {1, 9, 14};
int vec2[] = {-5, 12, 17};

int main()
{

	cout << lexicographical_compare(s1.begin(), s1.end(),
	    s2.begin(), s2.end()) << endl;

	cout << lexicographical_compare(vec1, vec1 + 2,
	    vec2, vec2 + 2, Compare()) << endl;

	return 0;
}
