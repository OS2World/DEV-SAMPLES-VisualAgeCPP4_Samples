/******************************************************************************
* .FILE:        icalcop.cpp                                                   *
*                                                                             *
* .DESCRIPTION: Implementation for the class, ICalcOperator                   *
*                                                                             *
* .CLASSES:     ICalcOperator                                                 *
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

#include "icalcop.hpp"                  //ICalcOperator class header
#include <inotifev.hpp>

//
// Events
//

INotificationId ICalcOperator :: resultId = "ICalcOperator::result";

/*******************************************************************
 * Constructors/Destructors
 *******************************************************************/

ICalcOperator :: ICalcOperator() :
        dResult(0)
{
}

ICalcOperator :: ~ICalcOperator()
{
}

/*******************************************************************
 * Access Member Functions (no Event for dResult)
 *******************************************************************/

double ICalcOperator :: result () const
{
  return dResult;
}

double ICalcOperator :: setResult
  (double iResult)
{
  dResult = iResult;
  notifyObservers(INotificationEvent(resultId,*this));

  return dResult;
}

