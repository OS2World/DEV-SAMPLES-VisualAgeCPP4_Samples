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

extern int x1;
extern int x2;

int f1();
int f2();

class A {
public:
	A();
	int f1();
	int f2() {return 2;}
	static int f3();
	int operator+(int);
	operator int();
	static int x1;
	static int x2;
	int g(int);
	int g(double);
};

class B {
public:
	B();
	int f1();
	static int f3();
	int operator+(int);
	operator int();
	static int x1;
	static int x2;
	int g(int);
	int g(double);
};

class _Export C {
public:
	int f();
	static int g();
};
