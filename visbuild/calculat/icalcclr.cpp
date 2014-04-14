/******************************************************************************
* .FILE:        icalcclr.cpp                                                  *
*                                                                             *
* .DESCRIPTION: Implementation for the class, ICalcClearFunction              *
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

#include "icalcclr.hpp"                 //ICalcClearFunction class header
#include "icalcpu.hpp"                  //ICalcPU header

//*******************************************************************
// Manager Member Functions (Not Part Actions)
//*******************************************************************

ICalcClearFunction :: ICalcClearFunction()
{
}

ICalcClearFunction :: ~ICalcClearFunction()
{
}

//*******************************************************************
// Implementor Member Functions (not Part Actions)                   
//*******************************************************************


ICalcClearFunction & ICalcClearFunction::perform(ICalcPU& aPUObject)
{
 aPUObject.clearCalc();   // aPUObject, clear your Calculator
 return *this;
}

