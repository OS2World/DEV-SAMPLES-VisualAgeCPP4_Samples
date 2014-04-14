#ifndef _ICALCFUNC_
#define _ICALCFUNC_
/******************************************************************************
* .FILE:        icalcfnc.hpp                                                  *
*                                                                             *
* .DESCRIPTION: Header file for the class, ICalcFunction                      *
*                                                                             *
* .CLASSES:     ICalcFunction                                                 *
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
#include <istdntfy.hpp>
#include "ivbsamps.h"

//Forward declarations of other classes
class ICalcPU;

//**************************************************************************
// Class:   ICalcFunction
//
// Purpose: Describes ICalcFunction
//   This is the abstract base class for all calculator unary functions.
//   This defines the pluggable interface for all unary type functions.
//**************************************************************************

class IVBSAMP_IMPORT ICalcFunction : public IStandardNotifier
{
public:
           ICalcFunction();      //constructor
  virtual  ~ICalcFunction();     //destructor


//Implementor Method Functions

virtual ICalcFunction& perform(ICalcPU& aPUObject) = 0; //pure virtual function; which makes
                                                        //this class Abstract Base Class

};

#endif
