#ifndef _IKEYPAD_
#define _IKEYPAD_
/******************************************************************************
* .FILE:        ikeypad.hpp                                                   *
*                                                                             *
* .DESCRIPTION: Header file for the class, IKeypad                            *
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

#include <istring.hpp>
#include <istdntfy.hpp>
#include "ivbsamps.h"

//**************************************************************************
// Class:   IKeypad
//
// Purpose: Describes IKeypad Class.
//   This is a numeric keypad for applications such as the Calculator.
//**************************************************************************

class IVBSAMP_IMPORT IKeypad : public IStandardNotifier
{
public:
           IKeypad            ();
  virtual  ~IKeypad ();

//
// List of Part Events
//

static INotificationId digitId;

//
// List of Part Attributes - (query and set members)
//

virtual IString
  digit () const;

virtual IKeypad&
  setDigit (IString iDigit);

//
// List of Part Actions
//


protected:
//
// List of data members
//

  IString dDigit;

};

#endif
