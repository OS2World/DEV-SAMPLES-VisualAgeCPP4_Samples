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

#include <iosfwd>
#include <streambuf>
#include <iostream>

using namespace std;

class outbuf : public basic_streambuf<char, char_traits<char> > {
public:
	outbuf(char* buf, streamsize sz)
	{
		setbuf(buf, sz);
		setp(buf, buf + sz);
	}
};

class oarraystream : public ostream {
	outbuf sb;
public:
	oarraystream(char* buf, streamsize sz) : sb(buf, sz), ostream(&sb) {}
};

int main()
{
	char buf[100];
	oarraystream out(buf, 100);

	out << "the value = " << 12.34 << endl;
	out << "12345 as a hex value = " << hex << 12345 << endl;

	cout << buf;

	return 0;
}
