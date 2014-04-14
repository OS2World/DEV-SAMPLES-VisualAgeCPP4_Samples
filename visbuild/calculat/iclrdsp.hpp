/******************************************************************************
* .FILE:        iclrdsp.hpp                                                   *
*                                                                             *
* .DESCRIPTION: Header file for the class, IClearDisplay                      *
*                                                                             *
* .CLASSES:     IClearDisplay                                                 *
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
#include <icmdhdr.hpp>   // ICommandHandler

#ifndef _IENTRYFD_
#include <ientryfd.hpp>
#endif

#ifndef _IPUSHBUT_
#include <ipushbut.hpp>
#endif

#include "ivbsamps.h"

#define WND_clearpb    10000  // The window ID for the clear push button
                              // the CalculatorView was arbitrarily set
                              // to be high enough to not conflict with any
                              // window IDs on the system.


//**************************************************************************
// Class:   IClearDisplay
//
// Purpose: Clears the entry field using the
//          ICommandHandler class
//
//***************************************************************************

class IVBSAMP_IMPORT IClearDisplay : public ICommandHandler

{
public:

  IClearDisplay(IEntryField & theDisplay, IPushButton & theClearPushButton);
  ~IClearDisplay();     //destructor

// Implementor Method Functions

protected:

bool command(ICommandEvent& cmdEvent);

private:

// private member data

IEntryField  &display;
IPushButton &clearPushButton;

};   //IClearDisplay

