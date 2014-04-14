/******************************************************************************
* .FILE:        ikeypad.cpp                                                   *
*                                                                             *
* .DESCRIPTION: Implementation for the class, IKeypad                         *
*                                                                             *
* .CLASSES:     IKeypad                                                       *
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

#include "ikeypad.hpp"                 //IKeypad class header
#include <inotifev.hpp>

//
// Events
//

INotificationId IKeypad :: digitId = "IKeypad::digit";

/*******************************************************************
 * Contructors/Destructors
 *******************************************************************/

IKeypad :: IKeypad() :
        dDigit("")

{
}

IKeypad :: ~IKeypad()
{
}


/*******************************************************************
 * Access Member Functions (Part Attributes/Actions)
 *******************************************************************/

IString IKeypad :: digit () const
{
  return dDigit;
}


IKeypad & IKeypad :: setDigit
  (IString iDigit)
{
  dDigit = iDigit;                    
  notifyObservers(INotificationEvent(digitId,*this));
  return *this;
}

