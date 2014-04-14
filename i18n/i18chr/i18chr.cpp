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
	locale loc = locale::classic();

	const ctype<char>& ct = use_facet< ctype<char> > (loc);

	cout << ct.is(ctype_base::digit, '9') << endl;

	char* s = "abC";
	const char* p = ct.scan_is(ctype_base::upper, s, s + 3);
	cout << *p << endl;

	p = ct.scan_not(ctype_base::upper, s, s + 3);
	cout << *p << endl;

    }
    catch (runtime_error err_msg) {
        cerr << "Caught runtime exception while creating locale." << endl;
        cerr << "Make sure the locale exists on your system." << endl;
    }
    return 0;
}
