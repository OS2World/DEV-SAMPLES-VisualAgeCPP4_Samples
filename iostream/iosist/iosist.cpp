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
#include <cstring>
#include <streambuf>
#include <iostream>

using namespace std;

class inbuf : public basic_streambuf<char, char_traits<char> > {
public:
	inbuf(char* buf, streamsize sz)
	{
		setbuf(buf, sz);
		setg(buf, buf, buf + sz);
	}
};

class iarraystream : public istream {
	inbuf sb;
public:
	iarraystream(char* buf, streamsize sz) : sb(buf, sz), istream(&sb) {}
};

int main()
{
	char buf[100];
	strcpy(buf, "12345 abc");
	iarraystream inp(buf, 100);
	int i = 0;
	int j = 0;

	inp >> i;
	cout << "i = " << i << endl;
	inp >> hex >> j;
	cout << "j = " << j << endl;

	return 0;
}
