/******************************************************************************
* .FILE:         ahellow3.cpp                                                 *
*                                                                             *
* .DESCRIPTION:  Hello World Sample Program Version 3:  Class Implementation  *
*                                                                             *
* .CLASSES:      ACommandHandler                                              *
*                AHellowWindow                                                *
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
#include <ifont.hpp>
#include <icoordsy.hpp>
#include "ahellow3.hpp"
#include "ahellow3.h"

/**************************************************************************
* main  - Application entry point for Hello World Version 3.              *
*                                                                         *
* Creates a new object mainWindow of class AHelloWindow                   *
* Sets Hello World window alignment                                       *
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
  mainWindow.setTextAlignment(AHelloWindow::left);
  mainWindow.sizeTo(ISize(400,300));
  mainWindow.setFocus();
  mainWindow.show();
  IApplication::current().run();
  return 0;
} /* end main() */

/**************************************************************************
* Class AHelloWindow :: AHelloWindow - Constructor for the main window    *
*                                                                         *
* Define itself as an IFrameWindow                                        *
* Create a menu bar                                                       *
* Create status line                                                      *
* Create static text in client window.                                    *
* Create information area object                                          *
* Create a command handler to process command events from                 *
**************************************************************************/

AHelloWindow :: AHelloWindow(const unsigned long windowId)
  :IFrameWindow(IFrameWindow::defaultStyle() |
                IFrameWindow::minimizedIcon,
                windowId)
  ,menuBar(windowId, this)
  ,statusLine(WND_STATUS,this,this)
  ,hello(WND_HELLO, this, this)
  ,infoArea(this)
  ,commandHandler(this)
{

/*------------------------------------------------------------------------|
|  Set the hello world static text window as the client window.           |
|------------------------------------------------------------------------*/
  setClient(&hello);


/*------------------------------------------------------------------------|
|  Add the status line as an extension to the frame above the client      |
|    window with the height calculated from the maximum height of a       |
|    character in the current font.                                       |
|------------------------------------------------------------------------*/
  addExtension(&statusLine,
               IFrameWindow::aboveClient,
               IFont(&statusLine).maxCharHeight());


/*------------------------------------------------------------------------|
|  Set the values for the text controls from strings in the resource file.|
|    The infoArea default text is displayed when no menu item is active.  |
|------------------------------------------------------------------------*/
  hello.setText(STR_HELLO);
  infoArea.setDefaultText(STR_INFO);


/*------------------------------------------------------------------------|
|  Have the command handler handle commands sent from the frame window.   |
|    The command handler's command() function is called to process        |
|    menu item selections.                                                |
|------------------------------------------------------------------------*/
  commandHandler.handleEventsFor(this);


/*------------------------------------------------------------------------|
| Align the static text, set the status line, and set the check mark in   |
|   the menu bar.                                                         |
|------------------------------------------------------------------------*/
  setTextAlignment(center);

} /* end AHelloWindow :: AHelloWindow(...) */



/**************************************************************************
* Class AHelloWindow :: ~AHelloWindow - Destructor for the main window    *
**************************************************************************/
AHelloWindow :: ~AHelloWindow()
{
  commandHandler.stopHandlingEventsFor(this);
} /* end AHelloWindow :: ~AHelloWindow() */



/**************************************************************************
* Class AHelloWindow :: setTextAlignment - Align static text in client    *
*   window                                                                *
**************************************************************************/
AHelloWindow &
  AHelloWindow :: setTextAlignment(const Alignment alignment)
{
/*------------------------------------------------------------------------|
|  Depending on the value passed, update the window as follows:           |
|    Set the alignment of the static text control in the client window.   |
|    Set the text of the alignment status line static text control.       |
|    Check the selected menu item; remove check marks from the other two. |
|------------------------------------------------------------------------*/
  switch(alignment)
  {
    case left:
      hello.setAlignment(IStaticText::centerLeft);
      statusLine.setText(STR_LEFT);
      menuBar.uncheckItem(MI_CENTER);
      menuBar.checkItem(MI_LEFT);
      menuBar.uncheckItem(MI_RIGHT);
      break;
    case center:
      hello.setAlignment(IStaticText::centerCenter);
      statusLine.setText(STR_CENTER);
      menuBar.checkItem(MI_CENTER);
      menuBar.uncheckItem(MI_LEFT);
      menuBar.uncheckItem(MI_RIGHT);
      break;
    case right:
      hello.setAlignment(IStaticText::centerRight);
      statusLine.setText(STR_RIGHT);
      menuBar.uncheckItem(MI_CENTER);
      menuBar.uncheckItem(MI_LEFT);
      menuBar.checkItem(MI_RIGHT);
      break;
 }
 return (*this);
} /* end AHelloWindow :: setTextAlignment(...) */



/**************************************************************************
* Class ACommandHandler :: ACommandHandler - Constructor for the Command  *
*   Handler for the main window.                                          *
*                                                                         *
* Store the frame that events will be handled for                         *
**************************************************************************/
ACommandHandler :: ACommandHandler(AHelloWindow *helloFrame)
  :frame(helloFrame)
{
} /* end ACommandHandler :: ACommandHandler(...) */



/**************************************************************************
* Class ACommandHandler :: command -- Handles menu commands for the main  *
*   window                                                                *
**************************************************************************/
bool  ACommandHandler :: command(ICommandEvent & cmdEvent)
{
  bool eventProcessed(true);         //Assume event will be processed

/*------------------------------------------------------------------------|
|  Depending on the command event ID, call the AHelloWindow::setAlignment |
|    function with the appropriate AHelloWorld::Alignment value.          |
|------------------------------------------------------------------------*/
  switch (cmdEvent.commandId())
  {
    case MI_CENTER:
      frame->setTextAlignment(AHelloWindow::center);
      break;
    case MI_LEFT:
      frame->setTextAlignment(AHelloWindow::left);
      break;
    case MI_RIGHT:
      frame->setTextAlignment(AHelloWindow::right);
      break;
    default:
/*------------------------------------------------------------------------|
| The event was not processed                                             |
|------------------------------------------------------------------------*/
      eventProcessed=false;
  } /* end switch */

  return(eventProcessed);
} /* end ACommandHandler :: command(...) */
