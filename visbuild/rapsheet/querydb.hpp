#ifndef _QUERYDB_
#define _QUERYDB_
/******************************************************************************
* .FILE:        querydb.hpp                                                   *
*                                                                             *
* .DESCRIPTION: Header file for data query functions                          *
*                                                                             *
* .CLASSES:                                                                   *
*                                                                             *
* .COPYRIGHT:                                                                 *
*    Licensed Material - Program-Property of IBM                              *
*    (C) Copyright IBM Corp. 1992, 1996 - All Rights Reserved                 *
*                                                                             *
* .DISCLAIMER:                                                                *
*   The following [enclosed] code is sample code created by IBM               *
*   Corporation.  This sample code is not part of any standard IBM product    *
*   and is provided to you solely for the purpose of assisting you in the     *
*   development of your applications.  The code is provided 'AS IS',          *
*   without warranty of any kind.  IBM shall not be liable for any damages    *
*   arising out of your use of the sample code, even if they have been        *
*   advised of the possibility of such damages.                               *
*                                                                             *
* .NOTE: WE RECOMMEND USING A FIXED SPACE FONT TO LOOK AT THE SOURCE          *
*                                                                             *
******************************************************************************/
#include "ivbsamps.h"
#include <istring.hpp>
#include <iseq.h>

#define BLANK ' '
#define OBJID_LEN 5

#define SUSPECT_APPNAME  "suspects"
#define SUSPECT_INI      "suspects.ini"
#define ALIAS_APPNAME    "aliases"
#define ALIAS_INI        "aliases.ini"
#define ARREST_APPNAME   "arrests"
#define ARREST_INI       "arrests.ini"

IResultRecord IVBSAMP_IMPORT getAllSuspects();
IResultRecord IVBSAMP_IMPORT getAllAliases(unsigned long bookNumber);
IResultRecord IVBSAMP_IMPORT getAllArrests(unsigned long bookNumber);
void error(const char *message);

#endif

