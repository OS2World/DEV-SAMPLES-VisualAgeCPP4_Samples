/******************************************************************************
* .FILE:        ahellow1.cpp                                                  *
*                                                                             *
* .DESCRIPTION: Hello World Sample Program Version 1:  Implementation         *
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
#include <istattxt.hpp>
#include <iframe.hpp>
#include <icoordsy.hpp>
#include "ahellow1.h"

/**************************************************************************
* main  - Application entry point for Hello World Version 1.              *
*                                                                         *
* Creates a new object mainWindow of class IFrameWindow                   *
* Creates a new object hello of class IStaticText                         *
* Sets the static text value and aligns it                                *
* Sets the static text as the client of the mainWindow                    *
* Sets the size of mainWindow                                             *
* Sets the window focus to mainWindow                                     *
* Displays the mainWindow                                                 *
* Starts the events processing for the application                        *
**************************************************************************/
int main()
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::kOriginLowerLeft );
  IFrameWindow mainWindow (WND_MAIN);
  IStaticText hello(WND_HELLO, &mainWindow, &mainWindow);
  hello.setText(STR_HELLO);
  hello.setAlignment(IStaticText::centerCenter);
  mainWindow.setClient(&hello);

  mainWindow.sizeTo(ISize(400,300));
  mainWindow.setFocus();
  mainWindow.show();
  IApplication::current().run();
  return 0;
} /* end main() */
