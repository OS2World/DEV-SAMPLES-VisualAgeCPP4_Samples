/******************************************************************************
* FILE NAME: linfowin.cpp                                                     *
*                                                                             *
* Classes:                                                                    *
*   LInfoWindow                                                               *
*                                                                             *
* COPYRIGHT:                                                                  *
*   Licensed Materials - Property of IBM                                      *
*   (C) Copyright IBM Corporation 1992, 1995                                  *
*   All Rights Reserved                                                       *
*   US Government Users Restricted Rights - Use, duplication, or disclosure   *
*   restricted by GSA ADP Schedule Contract with IBM Corp.                    *
******************************************************************************/

#ifndef _IBASE_                         //Make sure ibase.hpp is included
  #include <ibase.hpp>                  //  since that is where IC_<environ>
#endif                                  //  is defined.
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
                             Boolean isQuery )
     :IFrameWindow         ( windowId, parent, owner ),
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
     :IFrameWindow         ( windowId, parent, owner ),
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
IBase::Boolean LInfoWindow::systemCommand( ICommandEvent& event )
{
   Boolean
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
