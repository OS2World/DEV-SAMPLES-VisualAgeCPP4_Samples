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

#include <bitset>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	string bits = "00001111";
	bitset<8> b1(bits);
	bitset<8> b2 = 0xaUL;
	bitset<8> b3;

	b3[0] = true;

	b1 &= b2; // b1 now 00001010
	b1 |= b3; // b1 now 00001011

	for (int i = 7; i >= 0; i--)
		cout << b1[i];
	cout << endl;

	return 0;
}
