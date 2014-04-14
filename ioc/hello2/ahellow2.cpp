/******************************************************************************
*                                                                             *
* .FILE:         ahellow2.cpp                                                 *
*                                                                             *
* .DESCRIPTION:  Hello World Sample Program Version 2: Class Implementation   *
*                                                                             *
* .CLASSES:      AHellowWindow                                                *
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
#include <icoordsy.hpp>
#include "ahellow2.hpp"
#include "ahellow2.h"

/**************************************************************************
* main  - Application entry point for Hello World Version 2.              *
*                                                                         *
* Creates a new object mainWindow of class AHelloWindow                   *
* Sets the size of mainWindow                                             *
* Sets the window focus to mainWindow                                     *
* Displays the mainWindow                                                 *
* Starts the events processing for the application                        *
**************************************************************************/
int main()
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::kOriginLowerLeft );
  AHelloWindow mainWindow (WND_MAIN);
  mainWindow.sizeTo(ISize(400,300));
  mainWindow.setFocus();
  mainWindow.show();
  IApplication::current().run();
  return 0;
} /* end main () */


/**************************************************************************
* Class AHelloWindow :: AHelloWindow - Constructor for the main window    *
*                                                                         *
* Define itself as an IFrameWindow                                        *
* Create static text in client window.                                    *
* Create information area                                                 *
**************************************************************************/
AHelloWindow :: AHelloWindow(const unsigned long windowId)
  : IFrameWindow(IFrameWindow::defaultStyle() |
                 IFrameWindow::minimizedIcon,
                 windowId)
   ,hello(WND_HELLO, this, this)
   ,infoArea(this)
{

/*------------------------------------------------------------------------|
|  Set the hello world static text window as the client window.           |
|------------------------------------------------------------------------*/
  setClient(&hello);


/*------------------------------------------------------------------------|
|  Set the values for the text controls from strings in the resource file.|
|    The infoArea default text is displayed when no menu item is active.  |
|------------------------------------------------------------------------*/
  hello.setText(STR_HELLO);
  infoArea.setDefaultText(STR_INFO);


/*------------------------------------------------------------------------|
| Align the static text in the client window.                             |
|------------------------------------------------------------------------*/
  hello.setAlignment(IStaticText::centerCenter);

} /* end AHelloWindow :: AHelloWindow (...) */
