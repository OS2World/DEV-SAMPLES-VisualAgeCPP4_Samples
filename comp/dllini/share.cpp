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

#ifdef __OS2__

#include <os2.h>
#define ATT_FLAG 0

#else

#include <windows.h>
#define ATT_FLAG DLL_PROCESS_ATTACH

#endif

extern "C" int _CRT_init(void);
extern "C" int _CRT_term(void);
extern "C" void __ctordtorInit(int);
extern "C" void __ctordtorTerm(int);

#ifdef __OS2__

extern "C" unsigned long _System _DLL_InitTerm(unsigned long hModule,
    unsigned long ulFlag)

#else

extern "C" unsigned long __stdcall _DLL_InitTerm(unsigned long hModule,
    unsigned long ulFlag, long*)

#endif
{
	// called when DLL starts up

	if (ulFlag == ATT_FLAG) {
		_CRT_init();		// C runtime initialization
		__ctordtorInit(0);	// C++ initialization
	}

	// called when DLL shuts down

	else {
		__ctordtorTerm(0);	// C++ termination
		_CRT_term();		// C termination
	}

	return 1UL;			// indicate success
}

class A {
	int x;
public:
	A() {x = 100;}
	int get() {return x;}
};

A a; // data member x gets zeroed by default

int _Export f() {return a.get();}	// return 100 if constructors have
					// been run, else 0
