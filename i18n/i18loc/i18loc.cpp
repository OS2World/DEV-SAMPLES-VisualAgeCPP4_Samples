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

#include <locale>
#include <iostream>

using namespace std;

int main()
{
    try {
	locale loc1 = locale();			// default
	locale loc2 = locale::classic();	// same as locale("C")
	locale loc3("en_US");			// specific named locale

	cout << loc1.name() << endl;		// display locale names
	cout << loc2.name() << endl;
	cout << loc3.name() << endl;

	locale prevloc = locale::global(loc3);	// set the global locale

    }
    catch (runtime_error err_msg) {
        cerr << "Caught runtime exception while creating locale." << endl;
        cerr << "Make sure the locale exists on your system." << endl;
    }
    return 0;
}
