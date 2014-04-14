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
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    try {
    //Creating a new locale object calls setlocale() internally.  This changes
    //the global 'C' locale.  Since all locale (C++) objects rely on the 'C'
    //locale this can cause side effect for other locale objects.
	locale loc("en_US");

	// sort strings according to a locale

	string list[] = {"abc", "DEF", "ABC", "def"};
	sort(list, list + 4, loc);
	for (int i = 0; i < 4; i++)
		cout << list[i] << endl;

	// compare character sequences for a given locale

	const collate<char>& cc = use_facet< collate<char> > (loc);
	char* s = "abc";
	char* t = "abd";
	cout << cc.compare(s, s + 3, t, t + 3) << endl;

	// Convert character strings to strings, which can be
	// lexicographically compared.  This can be more efficient
	// when comparisons need to be done over and over; for example
	// when repeatedly searching a list.


	//Once locale floc has been instantiated the behaviour of loc will also
	//change.  Both objects will collate according to German sorting rules.
	//This occurs because both objects rely on strcoll().
	locale floc("De_DE");
	
	
	const collate<char>& ccc = use_facet< collate<char> > (floc);

	for (int i = 0; i < 4; i++) {
		const char* cstr = list[i].data();
		list[i] = ccc.transform(cstr, cstr + list[i].length());
	}
	sort(list, list + 4);

	string st = cc.transform(s, s + 3);
	string* p = find(list, list + 4, st);
	if (p != list + 4)
		cout << "found at " << p - list << endl;

    }
    catch (runtime_error err_msg) {
        cerr << "Caught runtime exception while creating locale." << endl;
        cerr << "Make sure the locale exists on your system." << endl;
    }
    return 0;
}
