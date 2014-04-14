/******************************************************************************
* .FILE:         version.cpp                                                  *
*                                                                             *
* .DESCRIPTION:  Version Sample Application:   Implementation                 *
*                                                                             *
* .CLASSES:                                                                   *
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
#include <iapp.hpp>
#include <ititle.hpp>
#include <istring.hpp>
#include <istattxt.hpp>
#include <iframe.hpp>
#include <ireslib.hpp>
#include <iversion.hpp>
#include "version.h"

int main()
{
  IResourceLibrary
    reslib;

/*----------------------------------------------------------------------------|
| Create the main window with a window id of 0x1000                           |
-----------------------------------------------------------------------------*/
  IFrameWindow mainWindow (WND_MAIN);

/*----------------------------------------------------------------------------|
| Create a title for the main window                                          |
| Set the title text with a string from the resource file                     |
-----------------------------------------------------------------------------*/
  ITitle mainTitle(&mainWindow);
  mainTitle.setTitleText(WND_MAIN);

/*----------------------------------------------------------------------------|
| Create static text for showing the macro results of the version             |
| Create static text for showing the IVersion results of the version          |
-----------------------------------------------------------------------------*/
  IStaticText macroVersion (WND_TEXT1, &mainWindow, &mainWindow);
  IStaticText objectVersion(WND_TEXT2, &mainWindow, &mainWindow);

/*----------------------------------------------------------------------------|
| Set each static text string with the version information                    |
| Set the alignment of the text to the center of the static text              |
-----------------------------------------------------------------------------*/
  macroVersion.setText(reslib.loadString(STR_MACRO_INFO)+
                       reslib.loadString(STR_MAJOR)+
                       IString(IC_MAJOR_VERSION)+
                       reslib.loadString(STR_SPACES)+
                       reslib.loadString(STR_MINOR)+
                       IString(IC_MINOR_VERSION));
  objectVersion.setText(reslib.loadString(STR_OBJECT_INFO)+
                       reslib.loadString(STR_MAJOR)+
                       IString(IVersion::libraryVersion().major())+
                       reslib.loadString(STR_SPACES)+
                       reslib.loadString(STR_MINOR)+
                       IString(IVersion::libraryVersion().minor()));

  macroVersion.setAlignment (IStaticText::centerCenter);
  objectVersion.setAlignment(IStaticText::centerCenter);

/*----------------------------------------------------------------------------|
| Set the IVersion static text as a bottom frame extension using 50%          |
| Set the remaining client area to the macro static text.                     |
-----------------------------------------------------------------------------*/
  mainWindow.addExtension(&objectVersion, IFrameWindow::belowClient, 0.50);
  mainWindow.setClient(&macroVersion);

/*----------------------------------------------------------------------------|
| Set the size of the main window, change the focus to the main window, and   |
|   show the main window.                                                     |
| Run the application.                                                        |
-----------------------------------------------------------------------------*/
  mainWindow.sizeTo(ISize(400,150));
  mainWindow.setFocus();
  mainWindow.show();
  IApplication::current().run();
  return 0;
} /* end main */
