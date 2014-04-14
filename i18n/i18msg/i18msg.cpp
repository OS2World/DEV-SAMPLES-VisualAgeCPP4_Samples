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
#include <string>
#include <iostream>
#include "mess_msg.h"

using namespace std;

int main()
{
    try {
	locale loc("en_US");

	typedef messages<char> MC;
	const MC& msgcat = use_facet<MC> (loc);

	MC::catalog cat = msgcat.open("./mess.cat", loc);
	if (cat < 0) {
		cerr << "could not open message catalog" << endl;
		return 1;
	}

	string str = msgcat.get(cat, SET_1, aMSG_2, "default messsage");

	cout << "Retrieved message = " << str << endl;

	msgcat.close(cat);
    }
    catch (runtime_error err_msg) {
        cerr << "Caught runtime exception while creating locale." << endl;
        cerr << "Make sure the locale exists on your system." << endl;
    }


    return 0;
}
