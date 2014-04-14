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

#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;

// Complex data type
class Complex {
	double re;
	double im;
public:
	Complex(double r, double i) : re(r), im(i) {}
	friend ostream& operator<<(ostream&, const Complex&);
	friend istream& operator>>(istream&, Complex&);
};

// output for Complex
ostream& operator<<(ostream& ost, const Complex& c)
{
	return ost << "(" << c.re << "," << c.im << ")";
}

// input for Complex
istream& operator>>(istream& ist, Complex& c)
{
	double r, i;
	char ch = 0;

	ist >> ch;
	if (ch == '(') {
		ist >> r >> ch;
		if (ch == ',')
			ist >> i >> ch;
		if (ch != ')')
			ist.clear(ios_base::failbit);// set failbit (not clear)
	}
	else {
		ist.clear(ios_base::failbit);// set failbit (not clear)
	}

	if (ist)
		c = Complex(r, i);

	return ist;
}

int main()
{
	// unformatted boolean input

	bool b;
	istringstream istr1("1");
	b = false;
	istr1 >> b;
	cout << b << endl;

	// formatted boolean input

	istringstream istr2("true");
	b = false;
	istr2 >> boolalpha >> b;
	cout << b << endl;

	// hex formatted integer input

	istringstream istr3("12 34");
	int i, j;
	istr3 >> i >> hex >> j;
	cout << i << " " << j << endl;

	// input data of wrong type

	istringstream istr4("abc");
	istr4 >> i;
	if (istr4.rdstate() & ios_base::failbit)
		cout << "operation failed" << endl;

	// check eof bit

	istringstream istr5("abc");
	char buf[10];
	istr5 >> buf;
	if (istr5.rdstate() & ios_base::eofbit)
		cout << "eof seen" << endl;
	cout << buf << endl;

	// input a user-defined type

	istringstream istr6("(12.34,97.65)");
	Complex com(0, 0);
	istr6 >> com;
	cout << com << endl;

	return 0;
}
