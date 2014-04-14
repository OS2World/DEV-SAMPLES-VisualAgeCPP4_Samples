/******************************************************************************
* .FILE:        iclrdsp.cpp                                                   *
*                                                                             *
* .DESCRIPTION: Implementation for the class, IClearDisplay                   *
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
#include <iwindow.hpp>  // IWindow class
#include <icmdhdr.hpp>   // ICommandHandler

#ifndef _ITRACE_        
#include <itrace.hpp>   
#endif               
   
#include "iclrdsp.hpp"    // IClearDisplay class header

//***************************************************************************
// Class:   IClearDisplay
//
// Purpose: Clears the display values via the ICommandHandler sub class
//
//***************************************************************************

IClearDisplay :: IClearDisplay(IEntryField & theDisplay, IPushButton & theClearPushButton) :
        display(theDisplay), clearPushButton(theClearPushButton)
{
}

IClearDisplay :: ~IClearDisplay()
{
}
 
bool IClearDisplay::command(ICommandEvent& cmdEvent)
{
 if ( cmdEvent.commandId() == clearPushButton.id() )
    {
    IFUNCTRACE_DEVELOP();
    ITRACE_DEVELOP(" firing connection : ClearDisplay PushButton(clicked), to Entry Field(removeAll)");
    try {display.removeAll();}
    catch (IException& exc) {};
    return (true);
    }
 else return(false);
}
