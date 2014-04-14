#ifndef _IEQUALFUNC_
#define _IEQUALFUNC_
/******************************************************************************
* .FILE:        icalceql.hpp                                                  *
*                                                                             *
* .DESCRIPTION: Header file for the class, ICalcEqualFunction                 *
*                                                                             *
* .CLASSES:     ICalcEqualFunction                                            *
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
// Class:   ICalcEqualFunction
//
// Purpose: Describes ICalcEqualFunction
//   Defines the calculator Equal function.
//**************************************************************************  */

class IVBSAMP_IMPORT ICalcEqualFunction : public ICalcFunction
{
public:
           ICalcEqualFunction();      //constructor
  virtual  ~ICalcEqualFunction();     //destructor

//Implementor Method Functions

ICalcEqualFunction & perform(ICalcPU& aPU);
};

#endif
