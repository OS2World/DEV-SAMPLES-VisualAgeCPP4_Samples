/******************************************************************************
* .FILE:         ahellow4.cpp                                                 *
*                                                                             *
* .DESCRIPTION:  Hello World Sample Program Version 3:  Class Implementation  *
*                                                                             *
* .CLASSES:      ACommandHandler                                              *
*                AHellowWindow                                                *
*                ATextDialog                                                  *
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
#include <istring.hpp>
#include <icoordsy.hpp>
#include "ahellow4.hpp"
#include "ahellow4.h"
#include "adialog4.hpp"

/**************************************************************************
* main  - Application entry point for Hello World Version 4.              *
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
} /* end main */

/**************************************************************************
* Class AHelloWindow :: AHelloWindow - Constructor for the main window    *
*                                                                         *
* Define itself as an IFrameWindow                                        *
* Create a menu bar                                                       *
* Create status line                                                      *
* Create static text in client window.                                    *
* Create a set canvas that contains the push buttons                      *
* Create the push buttons that are in the set canvas                      *
* Create information area object                                          *
* Create a command handler to process command events from                 *
**************************************************************************/

AHelloWindow :: AHelloWindow(const unsigned long windowId)
  :IFrameWindow(IFrameWindow::defaultStyle() |
                IFrameWindow::minimizedIcon  |
                IFrameWindow::accelerator,
                windowId)
  ,menuBar(windowId, this)
  ,statusLine(WND_STATUS, this, this)
  ,hello(WND_HELLO, this, this)
  ,buttons(WND_BUTTONS, this, this)
  ,leftButton(MI_LEFT, &buttons, &buttons)
  ,centerButton(MI_CENTER, &buttons, &buttons)
  ,rightButton(MI_RIGHT, &buttons, &buttons)
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
  addExtension(&statusLine, IFrameWindow::aboveClient,
                 IFont(&statusLine).maxCharHeight());

/*------------------------------------------------------------------------|
|  Set the values for the text controls from strings in the resource file.|
|    The infoArea default text is displayed when no menu item is active.  |
|------------------------------------------------------------------------*/
  hello.setText(STR_HELLO);
  leftButton.setText(STR_LEFTB);
  centerButton.setText(STR_CENTERB);
  rightButton.setText(STR_RIGHTB);
  infoArea.setDefaultText(STR_INFO);

/*------------------------------------------------------------------------|
|  Enable the first button as a tab stop.                                 |
|  Set the canvas margins and padding between buttons to zero.            |
|  Add the set canvas that contains the push buttons to the frame window  |
|    as an extension immediately below the client window with a height    |
|    equal to the minimum height of the push buttons.  You must set the   |
|    text in the push buttons first.                                      |
|------------------------------------------------------------------------*/
  leftButton.enableTabStop();
  buttons.setMargin(ISize());
  buttons.setPad(ISize());
  addExtension(&buttons, IFrameWindow::belowClient,
                (unsigned long)buttons.minimumSize().height());

/*------------------------------------------------------------------------|
|  Have the command handler handle commands sent from the frame window.   |
|    The command handler's command() function is called to process        |
|    menu item, push button, and accelerator key selections.              |
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
 return (*this);                        //Return a reference to the frame

} /* end AHelloWindow :: setAlignment(...) */

/**************************************************************************
* Class AHelloWindow :: editText -- Creates a dialog window to edit the   *
*   "Hello World!!" static text string                                    *
**************************************************************************/
AHelloWindow &
  AHelloWindow :: editText()
{
/*------------------------------------------------------------------------|
|  Store the current value of the text to be changed.                     |
|  Set the text in the information area from the dialog information       |
|    string in the resource file.                                         |
|------------------------------------------------------------------------*/
  IString textValue(hello.text());
  infoArea.setDefaultText(STR_INFODLG);

/*------------------------------------------------------------------------|
|  Create a new text dialog with textValue as the string to edit and      |
|    AHelloWindow as the owner window.                                    |
|  Show the dialog modally.  This means that the owner window cannot have |
|    the focus back until the dialog is ended.                            |
|------------------------------------------------------------------------*/
  ATextDialog textDialog(textValue,this);
  textDialog.showModally();

/*------------------------------------------------------------------------|
|  If the OK button was used to end the dialog, then the static text,     |
|    hello, is set to the textValue string.  Else, it is not changed.     |
|  Reset the information area inactive text.                              |
|------------------------------------------------------------------------*/
  if (textDialog.result() == DID_OK)
        hello.setText(textValue);
  infoArea.setDefaultText(STR_INFO);

  return (*this);                       //Return a reference to the frame
}  /* end AHelloWindow :: editText() */

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
* Class ACommandHandler :: command -- Handles menu and button commands    *
*   for the main window.                                                  *
**************************************************************************/
bool ACommandHandler :: command(ICommandEvent & cmdEvent)
{
  bool eventProcessed(true);         //Assume event will be processed

/*------------------------------------------------------------------------|
|  Depending on the command event ID, call the AHelloWindow::setAlignment |
|    function with the appropriate AHelloWorld::Alignment value.          |
|  Do this except when the Text menu item is selected;                    |
|    then call the AHelloWindow::editText function for changing the       |
|    Hello World text using a dialog.                                     |
|------------------------------------------------------------------------*/
  switch (cmdEvent.commandId()) {
    case MI_CENTER:
      frame->setTextAlignment(AHelloWindow::center);
      break;
    case MI_LEFT:
      frame->setTextAlignment(AHelloWindow::left);
      break;
    case MI_RIGHT:
      frame->setTextAlignment(AHelloWindow::right);
      break;
    case MI_TEXT:
      frame->editText();
      break;

    default:
/*------------------------------------------------------------------------|
| The event was not processed                                             |
|------------------------------------------------------------------------*/
      eventProcessed=false;
  } /* end switch */

  return(eventProcessed);
} /* end ACommandHandler :: command(...) */
