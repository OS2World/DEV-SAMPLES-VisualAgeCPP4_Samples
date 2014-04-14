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
#include <iostream>

using namespace std;

int vec1[] = {1, 3};
int vec2[] = {2, 4};

int main()
{
	cout << vec1[0] << " " << vec1[1] << endl;
	cout << vec2[0] << " " << vec2[1] << endl;

	swap_ranges(vec1, vec1 + 2, vec2);

	cout << vec1[0] << " " << vec1[1] << endl;
	cout << vec2[0] << " " << vec2[1] << endl;

	return 0;
}
