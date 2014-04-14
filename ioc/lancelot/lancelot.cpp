/******************************************************************************
* .FILE:         lancelot.cpp                                                 *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Implementation   *
*                                                                             *
* .CLASSES:      None                                                         *
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
#include <ithread.hpp>
#include <imsgbox.hpp>
#include <icoordsy.hpp>
#include "lmainwin.hpp"

int main()
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::kOriginLowerLeft );

/*-----------------------------------------------------------------------------
| Set the default IHelpWindow style for the entire application.               |
| If USE_IPF is defined, use IPF help.  Otherwise, use Windows RTF help.      |
-----------------------------------------------------------------------------*/
   #if (defined IC_WIN && defined USE_IPF)
   IHelpWindow::setDefaultStyle( IHelpWindow::defaultStyle()
                                 | IHelpWindow::ipfCompatible );
   #endif

/*-----------------------------------------------------------------------------
| Set the default IToolBarButton styles for the entire application.           |
-----------------------------------------------------------------------------*/
   IToolBarButton::setDefaultStyle(
     IToolBarButton::classDefaultStyle
     &~IToolBarButton::standardFormat );

/*-----------------------------------------------------------------------------
| Test if .INI files can be accessed from the current directory.              |
|   If they can't, tell the user and end the application.                     |
| Create the main window for the application                                  |
| Start the event processing loop                                             |
-----------------------------------------------------------------------------*/
   try
   {
      IProfile testing( "lsaveqry.ini" );
   }
   catch(...)
   {
      IMessageBox
         msgBox( IWindow::desktopWindow() );
      msgBox.show( STR_NO_DB_ACCESS, IMessageBox::catastrophic );
      return 2;
   }

   LMainWindow mainWindow;

   IApplication::current().run();

   return 0;
}

