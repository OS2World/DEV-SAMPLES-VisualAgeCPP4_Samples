#ifndef _ICLEARFUNC_
#define _ICLEARFUNC_
/******************************************************************************
* .FILE:        icalcclr.hpp                                                  *
*                                                                             *
* .DESCRIPTION: Header file for the class, ICalcClearFunction                 *
*                                                                             *
* .CLASSES:     ICalcClearFunction                                            *
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

#include <istring.hpp>
#include "ivbsamps.h"
#include "icalcfnc.hpp"

//**************************************************************************
// Class:   ICalcClearFunction
//
// Purpose: Describes ICalcClearFunction
//   Defines the calculator Clear All function.
//***************************************************************************

class IVBSAMP_IMPORT ICalcClearFunction : public ICalcFunction
{
public:
           ICalcClearFunction();      //constructor
  virtual  ~ICalcClearFunction();     //destructor

//Implementor Method Functions

ICalcClearFunction & perform(ICalcPU& aPUObject);

};

#endif
