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

#include "share.h"

// globals

int _Export x1 = 10;
int x2 = 20;
#pragma export(x2)

int _Export f1() {return 1;}
int f2() {return 2;}
#pragma export(f2)

// definitions for A

_Export A::A() {}

int _Export A::f1() {return 1;}

int _Export A::f3() {return 3;}

int _Export A::operator+(int) {return 4;}

_Export A::operator int() {return 5;}

int _Export A::x1 = 6;
int A::x2 = 7;

int _Export A::g(int) {return 8;}
int A::g(double) {return 9;}

// definitions for B

_Export B::B() {}
#pragma export(B::B)

int B::f1() {return 1;}
#pragma export (B::f1)

int B::f3() {return 3;}
#pragma export (B::f3)

int B::operator+(int) {return 4;}
#pragma export (B::operator+)

B::operator int() {return 5;}
#pragma export(B::operator int)

int B::x1 = 6;
#pragma export (B::x1)
int B::x2 = 7;

int B::g(int) {return 8;}
#pragma export(B::g(int))
int B::g(double) {return 9;}

// definitions for C

int C::f() {return 100;}
int C::g() {return 200;}
