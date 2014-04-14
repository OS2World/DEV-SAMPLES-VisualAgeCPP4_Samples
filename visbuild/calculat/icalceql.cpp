/******************************************************************************
* .FILE:        icalceql.cpp                                                  *
*                                                                             *
* .DESCRIPTION: Implementation for the class, ICalcEqualFunction              *
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

#include "icalceql.hpp"                 //ICalcEqualFunction class header
#include "icalcpu.hpp"                  //ICalcPU header


//*******************************************************************
// Manager Member Functions (Not Part Actions)
//*******************************************************************


ICalcEqualFunction :: ICalcEqualFunction()
{
}

ICalcEqualFunction :: ~ICalcEqualFunction()
{
}

//*******************************************************************
// Implementor Member Functions (not Part Actions)                   
//*******************************************************************

ICalcEqualFunction & ICalcEqualFunction::perform(ICalcPU& aPU)
{
 aPU.evaluateOperator();       //aPU, evaluate yourself
 return *this;
}

