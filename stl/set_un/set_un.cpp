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
#include <iostream>

using namespace std;

class Compare {
public:
	bool operator()(char* a, char* b)
	{
		return strcmp(a, b) < 0;
	}
};

char* vec1[] = {"1", "2", "5", "8", "9"};
char* vec2[] = {"2", "7"};
char* vec3[10];

int main()
{

	set_union(vec1, vec1 + 5, vec2, vec2 + 2, vec3, Compare());

	for (int i = 0; vec3[i]; i++)
		cout << vec3[i] << " ";

	cout << endl;

	return 0;
}
