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
#include <sstream>
#include <string>
#include <ctime>
#include <iostream>

using namespace std;

int main()
{
    try {
	//Set the global locale to "en_US".  Since all locale object rely on the 'C'
	//global locale data structures the program should maintain one consistent
	//locale for consistencies sake.
    locale::global( locale("en_US") );
    //All locale objects depend on the global C locale data structures. Thus,
    //the locale object loc requires the the system locale to remain constant
    //for consistent behaviour. 
    //Code such as:
    //	locale loc1("en_US");	<- calls setlocale(LC_ALL, "en_US");
    //	locale loc2("ja_JP");	<- calls setlocale(LC_ALL, "ja_JP");
    //is discouraged.
	locale loc("en_US");

	typedef istreambuf_iterator<char> In_Iter;
	typedef ostreambuf_iterator<char> Out_Iter;
	ios_base::iostate err;

	// number formatting

	const num_get<char>& ng = use_facet< num_get<char> > (loc);
	const num_put<char>& np = use_facet< num_put<char> > (loc);
	string in_string = "1234";
	//All new template iostream objects have an associated locale object.
	//This object is initialized to be a copy of the global locale object 
	//by default.  The new locale object's constructor calls setlocale().
	//Without the initial call to: locale::global( locale("en_US") the 
	//sytem 'C' locale would be changed to the default value of 'C'.  This 
	//would affect the operation of object loc.
	istringstream istr(in_string);
	ostringstream ostr;
	long lng;
	ng.get(In_Iter(istr), In_Iter(), istr, err, lng);
	np.put(Out_Iter(ostr), ostr, err, lng);
	cout << ostr.str() << endl;

	// number punctuation

	const numpunct<char>& npu = use_facet< numpunct<char> > (loc);
	cout << "decimal point = " << npu.decimal_point() << endl;
	cout << "boolean \"true\" name = " << npu.truename() << endl;

	// dates and times

	time_t currt;
	time(&currt);
	struct tm* tmbuf = gmtime(&currt);
	const time_get<char>& tg = use_facet< time_get<char> > (loc);
	const time_put<char>& tp = use_facet< time_put<char> > (loc);
	char* fmt = "%x";
	ostringstream time_ostr1;
	tp.put(Out_Iter(time_ostr1), time_ostr1, ' ', tmbuf, fmt, fmt + 2);
	cout << time_ostr1.str() << endl;
	istringstream time_istr(time_ostr1.str());
	struct tm tmbufx;
	tg.get_date(In_Iter(time_istr), In_Iter(), time_istr, err, &tmbufx);
	ostringstream time_ostr2;
	tp.put(Out_Iter(time_ostr2), time_ostr2, ' ', &tmbufx, fmt, fmt + 2);
	cout << time_ostr2.str() << endl;

	// money punctuation
	const moneypunct<char>& mp = use_facet< moneypunct<char> > (loc);
	cout << "frac dig = " << mp.frac_digits() << endl;

	// currency formats

	string s;
	const money_get<char>& mg = use_facet< money_get<char> > (loc);
	istringstream mp_istr("12.34");
	//money_get.get always returns an integral value.  Therefore, this 
	//call returns 1234, the number of pennies in twelve dollars and 
	//thirty-four cents.
	mg.get(In_Iter(mp_istr), In_Iter(), false, cin, err, s);
	//correct output is: 1234
	cout << s << endl;
	const money_put<char>& mput = use_facet< money_put<char> > (loc);
	//money_put.put parses the input 12.34 as though it is 12.34 pennies.
	mput.put(Out_Iter(cout), false, cout, ' ', "12.34");
	//Correct output is 0.12.  The input value is parsed as 12 cents.
	cout << endl;
    }
    catch (runtime_error err_msg) {
        cerr << "Caught runtime exception while creating locale." << endl;
        cerr << "Make sure the locale exists on your system." << endl;
    }
    return 0;
}
