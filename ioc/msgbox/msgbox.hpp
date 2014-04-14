/******************************************************************************
* .FILE:         msgbox.hpp                                                   *
*                                                                             *
* .DESCRIPTION:  Message Box Sample Program:  Class Header                    *
*                                                                             *
* .CLASSES:      AMsgBoxDemo                                                  *
*                                                                             *
* .COPYRIGHT:                                                                 *
*    IBM Open Class Library                                                   *
*    Licensed Material - Program-Property of IBM                              *
*    (C) Copyright IBM Corp. 1992, 1997 - All Rights Reserved                 *
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
#ifndef _MSGBOX_HPP
#define _MSGBOX_HPP

#include <imsgbox.hpp>
#include <iwindow.hpp>
#include <iframe.hpp>
#include <iexcept.hpp>
#include <ireslib.hpp>
#include <itrace.hpp>
#include <istring.hpp>
#include <ihelp.hpp>
#include <imle.hpp>
#include <icconst.h>

#include "msgbox.h"

/**************************************************************************
* Class AMsgBoxDemo - Creates a main window to display the responses      *
*   to a series of messages boxes.                                        *
**************************************************************************/
class AMsgBoxDemo : public IFrameWindow
{
  public:
/*---------------------------- Constructor -------------------------------|
| Constructs the object with:                                             |
| 1) the window id                                                        |
-------------------------------------------------------------------------*/
    AMsgBoxDemo(unsigned long windowId);

/*----------------------------- Destructor -------------------------------|
| Destructs the object with:                                              |
| 1) no parameters                                                        |
-------------------------------------------------------------------------*/
    virtual
     ~AMsgBoxDemo() { };

/*--------------------- Run Message Box Demonstration --------------------|
| The runDemo function loops through a series of IMessageBox::show        |
|   function calls, with the final show prompting the user for another    |
|   time through the loop.  This function traces its progress to the      |
|   ITrace destination and to the IMultiLineEdit window in the frame.     |
|                                                                         |
| The following protected functions are used by runDemo to produce the    |
|   demonstration:                                                        |
|     traceReply - Formats the message box reply to an IString, traces    |
|                  traces the IString to the ITrace destination,          |
|                  returns the IString to the caller.                     |
|     throwException - Generates an IAccessError to demonstrate use of    |
|                  a message box to display an exception.                 |
|------------------------------------------------------------------------*/
    AMsgBoxDemo
     &runDemo();

  protected:
    AMsgBoxDemo
     &traceReply(IMessageBox::Response);
    AMsgBoxDemo
     &throwException();

  private:
    IMultiLineEdit
      mbResponses;
    IMessageBox
      mb;
    IHelpWindow
      mbHelp;
};

#endif
