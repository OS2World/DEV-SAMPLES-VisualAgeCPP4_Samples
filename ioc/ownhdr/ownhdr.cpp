/******************************************************************************
* .FILE:         ownhdr.cpp                                                   *
*                                                                             *
* .DESCRIPTION:  Create Your Own Handler Window : Class Implementation        *
*                                                                             *
* .CLASSES:      MyWindow                                                     *
*                MyTimeHandler                                                *
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
#include <itime.hpp>
#include <icoordsy.hpp>
#include "timehdr.hpp"
#include "ownhdr.hpp"
#include "ownhdr.h"

int main()
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::kOriginLowerLeft );
  MyWindow win;
  IApplication::current().run();
  return 0;
}

/******************************************************************************
* Class MyWindow :: MyWindow - Constructor for the main window                *
*                                                                             *
* Define yourself as an IFrameWindow                                          *
* Create static text                                                          *
* Create time handler                                                         *
******************************************************************************/
MyWindow::MyWindow()
  :IFrameWindow( ID_MAIN )
  ,title( this, ID_MAIN_TITLE )
  ,staticText( ID_TEXT, this, this )
  ,timeHdr( &staticText )
{
/*-----------------------------------------------------------------------------
| Begin handling timer events for this window                                 |
 ----------------------------------------------------------------------------*/
  timeHdr.handleEventsFor( this );

/*-----------------------------------------------------------------------------
| Set the static text font                                                    |
| Set the static text alignment to be center vertically and horizontally      |
 ----------------------------------------------------------------------------*/
  staticText.setFont( IFont( "Courier", 24 ) );
  staticText.setAlignment( IStaticText::centerCenter );

/*-----------------------------------------------------------------------------
| Set the application icon                                                    |
| Set the client to the static text                                           |
| Set focus to the frame window and show                                      |
 ----------------------------------------------------------------------------*/
  setIcon( ID_ICON );
  setClient( &staticText );
  setFocus().show();
}


/******************************************************************************
* Class MyWindow :: ~MyWindow - Destructor for the main window                *
*                                                                             *
******************************************************************************/
MyWindow::~MyWindow()
{
/*-----------------------------------------------------------------------------
| Stop handling timer events for this window                                  |
 ----------------------------------------------------------------------------*/
  timeHdr.stopHandlingEventsFor( this );
}


/******************************************************************************
* Class MyTimeHandler :: MyTimeHandler - Constructor for an time handler      *
*                                                                             *
* Define yourself as an ATimeHandler                                          *
* Store the static text pointer                                               *
******************************************************************************/
MyTimeHandler::MyTimeHandler( IStaticText* staticText )
  :ATimeHandler()
  ,pText( staticText )
{
}

/******************************************************************************
* Class MyTimeHandler :: tick - Override for time events                      *
******************************************************************************/
bool MyTimeHandler::tick( IEvent& event )
{
/*-----------------------------------------------------------------------------
| Set the static text to the current time                                     |
| Return false indicating we didn't handle the event                          |
 ----------------------------------------------------------------------------*/
  pText->setText( ITime().asString() );
  return false;
}
