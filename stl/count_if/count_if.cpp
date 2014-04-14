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
#include <iterator>
#include <iostream>

using namespace std;

int vec[] = {1, -3, 5, -7, 9};

bool pred(int a)
{
	return a < 0;
}

int main()
{
	iterator_traits<int*>::difference_type n =
	    count_if(vec, vec + 5, pred);

	cout << n << endl;

	return 0;
}
