/******************************************************************************
* .FILE:        imykybrd.hpp                                                  *
*                                                                             *
* .DESCRIPTION: Header file for the class, ICaptureMyKeys                     *
*                                                                             *
* .CLASSES:     ICaptureMyKeys                                                *
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
#include <ikeyevt.hpp>   // IKeyboardEvent
#include <ikeyhdr.hpp>   // IKeyboardHandler

#ifndef _IENTRYFD_
#include <ientryfd.hpp>
#endif

#ifndef _IPUSHBUT_
#include <ipushbut.hpp>
#endif

#include "ivbsamps.h"
#include "ikeypad.hpp"

//**************************************************************************
// Class:   ICaptureMyKeys
//
// Purpose: Captures the numeric keys entered from the keyboard and the
//          arithmetic operation keys plus the equal (=) sign.
//
//***************************************************************************

class IVBSAMP_IMPORT ICaptureMyKeys : public IKeyboardHandler

{
public:

  ICaptureMyKeys :: ICaptureMyKeys(IPushButton & ipluspb,IPushButton & isubpb,
                                IPushButton & imulpb, IPushButton & idivpb,
                                IPushButton & iequalpb,IKeypad & ikeypad);
  ~ICaptureMyKeys();     //destructor

// Implementor Method Functions

protected:

bool  characterKeyPress(IKeyboardEvent& keyevt);


private:

// private member data

IPushButton & PlusPB;
IPushButton & MinusPB;
IPushButton & MultiplicationPB;
IPushButton & DivisionPB;
IPushButton & EqualPB;
IKeypad & Keypad;

};   //ICaptureMyKeys

