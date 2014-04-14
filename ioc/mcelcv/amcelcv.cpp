/******************************************************************************
* .FILE:         amcelcv.cpp                                                  *
*                                                                             *
* .DESCRIPTION:  Canvas Classes Example 3 - Multi Cell Canvas                 *
*                                                                             *
* .CLASSES:      APushButtonHandler                                           *
*                AMultiCellCanvas                                             *
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
#include <imsgbox.hpp>
#include <istring.hpp>
#include <ireslib.hpp>
#include <icoordsy.hpp>
#include "amcelcv.h"
#include "amcelcv.hpp"

/******************************************************************************/
/* main  - Application entry point                                            */
/******************************************************************************/
int main()
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::kOriginLowerLeft );
  AMultiCellCanvas mainWindow(WND_MAIN);
  IApplication::current().run();
  return 0;
} /* end main */

/******************************************************************************
* Class AMultiCellCanvas :: AMultiCellCanvas - Constructor for  main window   *
*                                                                             *
* Defines itself as an IFrameWindow.                                          *
* Create a multicell canvas to layout the controls.                           *
* Create the two title strings of text.                                       *
* Create the two check boxes.                                                 *
* Create the two radio buttons.                                               *
******************************************************************************/
AMultiCellCanvas::AMultiCellCanvas(unsigned long windowId)
  : IFrameWindow(windowId)
  , clientCanvas( WND_MCCANVAS, this, this )
  , status( WND_STATUS, &clientCanvas, &clientCanvas )
  , title1( WND_TITLE1, &clientCanvas, &clientCanvas )
  , title2( WND_TITLE2, &clientCanvas, &clientCanvas )
  , check1( WND_CHECK1, &clientCanvas, &clientCanvas )
  , check2( WND_CHECK2, &clientCanvas, &clientCanvas )
  , radio1( WND_RADIO1, &clientCanvas, &clientCanvas )
  , radio2( WND_RADIO2, &clientCanvas, &clientCanvas )
  , pushButton( WND_PUSHBUT, &clientCanvas, &clientCanvas )
{
/*----------------------------------------------------------------------------|
| Set the icon and the multi cell client canvas.                              |
-----------------------------------------------------------------------------*/
  setIcon( id() );
  setClient( &clientCanvas );

/*----------------------------------------------------------------------------|
| Set the text and it attributes for the titles and the status area.          |
-----------------------------------------------------------------------------*/
  status.setAlignment( IStaticText::centerCenter );
  status.setText( STR_STATUS );

  title1.setAlignment( IStaticText::centerLeft );
  title1.setText( STR_TITLE1 );

  title2.setAlignment( IStaticText::centerLeft );
  title2.setText( STR_TITLE2 );

/*----------------------------------------------------------------------------|
| Set the text for the check boxes, the radio buttons, and the push button.   |
-----------------------------------------------------------------------------*/
  check1.setText( STR_CHECK1 );
  check2.setText( STR_CHECK2 );
  radio1.setText( STR_RADIO1 );
  radio2.setText( STR_RADIO2 );
  pushButton.setText( STR_PUSHBUT );

/*----------------------------------------------------------------------------|
| Preselect one radio button.                                                 |
| Set tabstops and group styles.                                              |
| Initialize the push button handler                                          |
|
-----------------------------------------------------------------------------*/
  radio1.select();
  check1.enableGroup().enableTabStop();
  radio1.enableGroup().enableTabStop();
  pushButton.enableGroup().enableTabStop();
  pushButtonHandler.setOwnerWindow(this);
  pushButtonHandler.handleEventsFor(&clientCanvas);

/*----------------------------------------------------------------------------|
| Place controls into cells on the multicell canvas and configure size        |
|   of cells.                                                                 |
-----------------------------------------------------------------------------*/
  clientCanvas.addToCell(&status  , 1, 1, 5, 1);
  clientCanvas.addToCell(&title1  , 1, 3, 2, 1);
  clientCanvas.addToCell(&title2  , 3, 3, 2, 1);
  clientCanvas.addToCell(&check1  , 2, 4);
  clientCanvas.addToCell(&check2  , 2, 5);
  clientCanvas.addToCell(&radio1  , 4, 4);
  clientCanvas.addToCell(&radio2  , 4, 5);
  clientCanvas.addToCell(&pushButton , 2, 7);

  clientCanvas.setRowHeight(2, 20, true);
  clientCanvas.setRowHeight(6, 40);
  clientCanvas.setColumnWidth(5, 0, true);

/*----------------------------------------------------------------------------|
| Set focus to the first check box and show the main window.                  |
-----------------------------------------------------------------------------*/
  check1.setFocus();
  show();

} /* end AMultiCellCanvas :: AMultiCellCanvas(...) */

/******************************************************************************
* Class AMultiCellCanvas :: displayButtonStatus - display a message box       *
******************************************************************************/
AMultiCellCanvas& AMultiCellCanvas::displayButtonStatus()
{
  unsigned long str_id1, str_id2, str_id3;
  IMessageBox msgbox(this);
  IResourceLibrary  reslib = IApplication::current().userResourceLibrary();
  msgbox.setTitle( IResourceId(STR_MSGBOX) );
  str_id1 = check1.isSelected() ? STR_CHK1_SEL : STR_CHK1_NOSEL;
  str_id2 = check2.isSelected() ? STR_CHK2_SEL : STR_CHK2_NOSEL;
  IString  str1 = reslib.loadString(str_id1),
           str2 = reslib.loadString(str_id2),
           str3 = reslib.loadString( radio1.selectedIndex() + STR_RAD1_SEL );

  str1 += str2 + str3;
  msgbox.show( (char *)str1 , IMessageBox::okButton         |
                              IMessageBox::informationIcon  |
                              IMessageBox::applicationModal |
                              IMessageBox::moveable         );
  return *this;
}

/*****************************************************************************
* Class APushButtonHandler :: command - handle some command events           *
*****************************************************************************/
bool APushButtonHandler::command( ICommandEvent& evt )
{
  bool fProcessed = false;

  if (evt.commandId() == WND_PUSHBUT && window)
  {
    window->displayButtonStatus();
    fProcessed = true;
  }
  return fProcessed;
}
