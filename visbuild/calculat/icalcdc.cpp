/******************************************************************************
* .FILE:        icalcdc.cpp                                                   *
*                                                                             *
* .DESCRIPTION: Implementation for the class, ICalcDivisionChip               *
*                                                                             *
* .CLASSES:     ICalcDivisionChip                                             *
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

#include "icalcdc.hpp"                  //ICalcDivisionChip class header
#include <iexcbase.hpp>

/*******************************************************************
 * Manager Member Functions (Not Part Actions)
 *******************************************************************/

ICalcDivisionChip :: ICalcDivisionChip()
{
}

ICalcDivisionChip :: ~ICalcDivisionChip()
{
}

/*******************************************************************
 * Implementor Member Functions (not Part Actions)
 *******************************************************************/

double ICalcDivisionChip ::
  evaluate (double operand1, double operand2)
{
  if (operand2 == 0)
     {
        throw IException("RED ALERT!  RED ALERT!  This is NOT a Drill!  Division by Zero Attack!  Math Flunkies have siezed the Helm!  Computer override, PLEASE!");
     }

  else return setResult ( operand1 / operand2 );

  return (-999);
}
