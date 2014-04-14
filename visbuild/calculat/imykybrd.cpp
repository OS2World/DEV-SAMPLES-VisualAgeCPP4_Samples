/******************************************************************************
* .FILE:        imykybrd.cpp                                                  *
*                                                                             *
* .DESCRIPTION: Implementation for the class, ICaptureMyKeys                  *
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

#ifndef _ITRACE_
#include <itrace.hpp>
#endif

#ifndef _IPUSHBUT_
#include <ipushbut.hpp>
#endif

#include "ikeypad.hpp"    // IKeypad class header
#include "imykybrd.hpp"   // ICaptureMyKeys class header

//***************************************************************************
// Override the characterKeyPress of the IKeyboardHandler class to
// capture the + - * / = keys and pass the rest of the keys on
// to be processed by someone else.
//***************************************************************************

ICaptureMyKeys :: ICaptureMyKeys(IPushButton & ipluspb, IPushButton & isubpb,
                                 IPushButton & imultpb, IPushButton & idivpb,
                                 IPushButton & iequalpb,IKeypad & ikeypad) :
                                 PlusPB(ipluspb), MinusPB(isubpb),
                                 MultiplicationPB(imultpb), DivisionPB(idivpb),
                                 EqualPB(iequalpb),Keypad(ikeypad)

{}                                    // constructor

ICaptureMyKeys :: ~ICaptureMyKeys()   // destructor
{}

bool  ICaptureMyKeys::characterKeyPress(IKeyboardEvent& keyevt)
{
  // valid keys are: 0-9,+,-,*,/,=
  bool bRc = true;         // assume non-numeric key to start with

  IFUNCTRACE_DEVELOP();
  ITRACE_DEVELOP("captured key: "+ IString(keyevt.character()));

    switch (keyevt.character())
      {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9': /* let cases for 0-9 fall through here */
                  Keypad.setDigit(keyevt.character()); // set the digit in the keypad
                                                       // this kicks off the notifications
                                                       // and the rest of the calculator
                                                       // code takes over the processing
                                                       // of this keyevent
                  keyevt.setResult(true);              // mark key as not processed
                  ITRACE_DEVELOP("captured key: "+ IString(keyevt.character()));
                  break;
        case '+': keyevt.setResult(true);       /* mark key as processed */
                  PlusPB.click();
                  ITRACE_DEVELOP("captured key: "+ IString(keyevt.character()));
                  break;
        case '-': keyevt.setResult(true);     /*mark key as processed */
                  MinusPB.click();
                  ITRACE_DEVELOP("captured key: "+ IString(keyevt.character()));
                  break;
        case '*': keyevt.setResult(true);
                  MultiplicationPB.click();
                  ITRACE_DEVELOP("captured key: "+  IString(keyevt.character()));
                  break;
        case '/': keyevt.setResult(true);
                  DivisionPB.click();
                  break;
        case '=': keyevt.setResult(true);
                  EqualPB.click();
                  ITRACE_DEVELOP("captured key: "+ IString(keyevt.character()));
                  break;
        default:  // DosBeep(100, 100);        // inform the user and eat the key
                  // MessageBeep (0);
                  keyevt.setResult(false);   // pass event on
                  ITRACE_DEVELOP("default=captured key: "+IString(keyevt.character()));
                  break;
      }

    return bRc;
}

