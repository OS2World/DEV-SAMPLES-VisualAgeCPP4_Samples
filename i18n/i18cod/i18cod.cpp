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
    //The global locale is initially defined to be the 'C' locale
    //The user can change it's value during program execution. 
    //Programs that depend on the global locale should explicitly set it's value
    locale::global( locale("C") );

	locale loc = locale();

	typedef codecvt<wchar_t, char, mbstate_t> CC;
	const CC& c = use_facet<CC> (loc);
	CC::state_type st = 0;

	char s1[3] = {'a', 'b', 0};
	const char* s11;
	wchar_t s2[2];
	wchar_t* s22;
	const wchar_t* s222;
	char* s111;

	c.in(st, s1, s1 + 2, s11, s2, s2 + 2, s22);
	c.out(st, s2, s2 + 2, s222, s1, s1 + 2, s111);

    }
    catch (runtime_error err_msg) {
        cerr << "Caught runtime exception while creating locale." << endl;
        cerr << "Make sure the locale exists on your system." << endl;
    }
    return 0;
}
