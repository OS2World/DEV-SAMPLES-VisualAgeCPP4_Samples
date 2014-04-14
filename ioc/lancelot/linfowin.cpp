/******************************************************************************
* .FILE:         linfowin.cpp                                                 *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Implementation   *
*                                                                             *
* .CLASSES:      LInfoWindow                                                  *
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
#include <ireslib.hpp>
#include <irect.hpp>
#include <imsgbox.hpp>
#include <istring.hpp>
#include <isysmenu.hpp>
#include "linfowin.hpp"
#include "lgoodies.hpp"
#include "lancelot.h"

/******************************************************************************
* Class LInfoWindow :: LInfoWindow - Constructor for the information window   *
*   given an employee.                                                        *
*                                                                             *
* Define yourself as an IFrameWindow                                          *
* Create title                                                                *
* Create notebook                                                             *
* Create help window                                                          *
* Store pointer to container object                                           *
* Store query flag                                                            *
******************************************************************************/
LInfoWindow::LInfoWindow   ( unsigned long windowId,
                             IWindow* parent, IWindow* owner,
                             IPoint bottomLeft,
                             LCnrObject* object,
                             LEmployeeData& employee,
                             bool isQuery )
     :IFrameWindow         ( windowId, parent, owner, IRectangle(),
                             classDefaultStyle |
                             dialogBackground  |
                             dialogBorder ),
      title                ( this ),
      notebook             ( this, this, employee, isQuery ),
      help                 ( ID_HELP_TABLE3, this ),
      pObject              ( object ),
      isAQuery             ( isQuery )
{
/*-----------------------------------------------------------------------------
| If this window was launched from a cnr object,                              |
| - set as open                                                               |
| - increment usage count                                                     |
-----------------------------------------------------------------------------*/
   if ( pObject )
   {
      pObject->setOpen();
      pObject->incrementUsage();
   }

/*-----------------------------------------------------------------------------
| Attempt to load the help file                                               |
-----------------------------------------------------------------------------*/
   try
   {
      help.addLibraries( "lanchelp.hlp" );
      help.setTitle( STR_HELP_TITLE );
   }
   catch( ... )
   {}

/*-----------------------------------------------------------------------------
| Handle command events for this frame window                                 |
-----------------------------------------------------------------------------*/
   ICommandHandler::handleEventsFor( this );

/*-----------------------------------------------------------------------------
| Determine the title for this frame window                                   |
-----------------------------------------------------------------------------*/
   if ( isQuery )
      title.setTitleText( STR_MAIN_TITLE, STR_QUERY_INFO_WINDOW );
   else if ( ! employee.employeeNumber().length() )
       title.setTitleText( STR_MAIN_TITLE, STR_NEW_INFO_WINDOW );
   else
       title.setTitleText( IApplication::current().userResourceLibrary().
                           loadString( STR_MAIN_TITLE ),
                           IString( employee.lastName()  +
                           ", " + employee.firstName() ) );

/*-----------------------------------------------------------------------------
| Set the frame's icon                                                        |
| Set the frame's client to be the notebook                                   |
-----------------------------------------------------------------------------*/
   setIcon( ID_ICON_PERSON4 );
   setClient( &notebook );

/*-----------------------------------------------------------------------------
| Resize the window based on the minimum size of the notebook                 |
-----------------------------------------------------------------------------*/
   moveSizeToClient( IRectangle( bottomLeft,
                     notebook.minimumSize() ) );

/*-----------------------------------------------------------------------------
| Move the frame window to the best location for the display size             |
| Set the focus to the frame                                                  |
| Show the frame                                                              |
-----------------------------------------------------------------------------*/
   IPoint
      newLocation( LFrameWindow::bestFit( this ) );
   moveTo( newLocation );
   if ( ( ! newLocation.x() ) || ( !newLocation.y() ) )
      maximize();
   setFocus().show();
}


/******************************************************************************
* Class LInfoWindow :: LInfoWindow - Constructor for the information window   *
*   given a query string.                                                     *
*                                                                             *
* Define yourself as an IFrameWindow                                          *
* Create title                                                                *
* Create notebook                                                             *
* Create help window                                                          *
* Store pointer to container object                                           *
* Store query flag                                                            *
******************************************************************************/
LInfoWindow::LInfoWindow   ( unsigned long windowId,
                             IWindow* parent, IWindow* owner,
                             IPoint bottomLeft,
                             LMainCnr* cnr,
                             LCnrObject* object,
                             IString queryName )
     :IFrameWindow         ( windowId, parent, owner, IRectangle(),
                             classDefaultStyle |
                             dialogBackground  |
                             dialogBorder ),
      title                ( this ),
      notebook             ( this, this, cnr, queryName ),
      help                 ( ID_HELP_TABLE3, this ),
      pObject              ( object ),
      isAQuery             ( true )
{
/*-----------------------------------------------------------------------------
| If this window was launched from a valid cnr object,                        |
| - set as open                                                               |
| - increment usage count                                                     |
-----------------------------------------------------------------------------*/
   if ( pObject )
   {
      pObject->setOpen();
      pObject->incrementUsage();
   }

/*-----------------------------------------------------------------------------
| Attempt to load the help file                                               |
-----------------------------------------------------------------------------*/
   try
   {
      help.addLibraries( "lanchelp.hlp" );
      help.setTitle( STR_HELP_TITLE );
   }
   catch( ... )
   {}

/*-----------------------------------------------------------------------------
| Handle command events for this frame window                                 |
-----------------------------------------------------------------------------*/
   ICommandHandler::handleEventsFor( this );

/*-----------------------------------------------------------------------------
| Set the title of this frame window to indicate a query                      |
-----------------------------------------------------------------------------*/
   title.setTitleText( STR_MAIN_TITLE, STR_QUERY_INFO_WINDOW );

/*-----------------------------------------------------------------------------
| Set the frame's icon                                                        |
| Set the frame's client to be the notebook                                   |
-----------------------------------------------------------------------------*/
   setIcon( ID_ICON_PERSON4 );
   setClient( &notebook );

/*-----------------------------------------------------------------------------
| Resize the window based on the minimum size of the notebook                 |
-----------------------------------------------------------------------------*/
   moveSizeToClient( IRectangle( bottomLeft,
                     notebook.minimumSize() ) );

/*-----------------------------------------------------------------------------
| Move the frame window to the best location for the display size             |
| Set the focus to the frame                                                  |
| Show the frame                                                              |
-----------------------------------------------------------------------------*/
   IPoint
      newLocation( LFrameWindow::bestFit( this ) );
   moveTo( newLocation );
   if ( ( !newLocation.x() ) || ( ! newLocation.y() ) )
      maximize();
   setFocus().show();
}


/******************************************************************************
* Class LInfoWindow :: ~LInfoWindow - Destructor for the info window          *
******************************************************************************/
LInfoWindow::~LInfoWindow()
{
/*-----------------------------------------------------------------------------
| If this window was launched from a valid cnr object,                        |
| - decrement usage count                                                     |
| - if no other information windows are via the cnr object,                   |
|   indicate it is closed                                                     |
-----------------------------------------------------------------------------*/
   if ( pObject )
   {
      pObject->decrementUsage();
      if ( ! pObject->usageCount() )
         pObject->setClosed();
   }
}


/******************************************************************************
* Class LInfoWindow :: systemCommand()                                        *
*   Handle any system command events for this frame window                    *
******************************************************************************/
bool LInfoWindow::systemCommand( ICommandEvent& event )
{
   bool
      retCode = false;

/*-----------------------------------------------------------------------------
| If the user is attempting to close the window,                              |
| - if this is not a query window, then save the personnel data               |
-----------------------------------------------------------------------------*/
   if ( event.commandId() == ISystemMenu::idClose )
   {
      if ( !isAQuery & !notebook.verifyPages( "" ) )
         retCode = true;
   }

   return retCode;
}
