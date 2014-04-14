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

#include <iomanip>
#include <sstream>
#include <iostream>

using namespace std;

class Bound;

// Complex number type, with (real,imaginary) values
class Complex {
	double re;
	double im;
public:
	Complex(double r, double i) : re(r), im(i) {}
	friend ostream& operator<<(ostream&, const Complex&);
};

// Format details for a complex number
struct Fmt {
	int prec;
	Fmt(int p = 6) {prec = p;}
	Bound operator()(Complex) const;
};

// A complex number and format, together as a bound unit
struct Bound {
	const Fmt& f;
	Complex val;
	Bound(const Fmt& fmt, Complex c) : f(fmt), val(c) {}
};

// Output a complex number
ostream& operator<<(ostream& os, const Complex& c)
{
	return os << "(" << c.re << "," << c.im << ")";
}

// Output a bound object
ostream& operator<<(ostream& os, const Bound& b)
{
	ostringstream s;

	s.precision(b.f.prec);
	s << b.val;
	return os << s.str();
}

// Create a bound object comprised of (format,value)
Bound Fmt::operator()(Complex c) const {return Bound(*this, c);}

// A manipulator to insert ":  " into the output stream
ostream& colon(ostream& os)
{
	return os << ":  ";
}

int main()
{
	cout << 12.3456 << endl;

	// Formatting of double types, using precision, scientific, and fixed

	double d = 12.3456;
	cout << setprecision(2) << d << endl;
	cout << scientific << setprecision(4) << d << endl;

	// Check stream state

	if (cout.rdstate() & ios_base::badbit)
		cerr << "Output operation failed" << endl;

	// Reset to default

	cout << setprecision(6);
	cout.setf(ios_base::floatfield);

	// Formatting of booleans, with output as "true" or "1"

	cout << true << endl << boolalpha << true << noboolalpha << endl;

	// User-defined manipulator

	cout << "The number is" << colon << d << endl;

	// Output a complex number

	Complex c(12.3456, 98.7654);
	Fmt f(4);
	cout << c << endl;    // default precision
	cout << f(c) << endl; // precision 4

	cout << 12.3456 << endl;

	return 0;
}
