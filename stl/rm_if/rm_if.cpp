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

class Compare {
public:
	bool operator()(int i)
	{
		return i == 5;
	}
};

int main()
{
	int ivec[] = {1, 3, 5, 1, 5};

	int* ip = remove_if(ivec, ivec + 5, Compare());

	for (int* p = ivec; p != ip; p++)
		cout << *p << endl;

	return 0;
}
