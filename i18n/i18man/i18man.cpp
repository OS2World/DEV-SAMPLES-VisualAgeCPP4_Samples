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

	const ctype<char>& ctc = use_facet< ctype<char> > (loc);
	const ctype<wchar_t>& ctw = use_facet< ctype<wchar_t> > (loc);

	cout << ctc.toupper('a') << endl;
	char s[4] = {'a', 'b', 'c', '\0'};
	ctc.tolower(s, s + 3);
	cout << s << endl;

	wchar_t wc = ctw.widen('a');
	cout << wc << endl;

	char c = ctw.narrow(L'\xfff', 'z');
	cout << (int)c << endl;

    }
    catch (runtime_error err_msg) {
        cerr << "Caught runtime exception while creating locale." << endl;
        cerr << "Make sure the locale exists on your system." << endl;
    }
    return 0;
}
