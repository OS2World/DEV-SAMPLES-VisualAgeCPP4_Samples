/******************************************************************************
* LANCELOT SAMPLE APPLICATION - lancelot.cpp                                  *
*                                                                             *
* Classes                                                                     *
*   -None-                                                                    *
*                                                                             *
* DISCLAIMER OF WARRANTIES:                                                   *
*   The following [enclosed] code is sample code created by IBM               *
*   Corporation.  This sample code is not part of any standard IBM product    *
*   and is provided to you solely for the purpose of assisting you in the     *
*   development of your applications.  The code is provided "AS IS",          *
*   without warranty of any kind.  IBM shall not be liable for any damages    *
*   arising out of your use of the sample code, even if they have been        *
*   advised of the possibility of such damages.                               *
*                                                                             *
* COPYRIGHT:                                                                  *
*   Licensed Materials - Property of IBM                                      *
*   (C) Copyright IBM Corporation 1992, 1995                                  *
*   All Rights Reserved                                                       *
*   US Government Users Restricted Rights - Use, duplication, or disclosure   *
*   restricted by GSA ADP Schedule Contract with IBM Corp.                    *
*                                                                             *
*******************************************************************************/

#ifndef _IBASE_                         //Make sure ibase.hpp is included
  #include <ibase.hpp>                  //  since that is where IC_<environ>
#endif                                  //  is defined.
#include <iapp.hpp>
#include <ithread.hpp>
#include <imsgbox.hpp>
#include "lmainwin.hpp"

int main()
{
   IApplication::current().setUserResourceLibrary("lancres");

/*-----------------------------------------------------------------------------
| Set the default IToolBarButton styles for the entire application.           |
| Test if .INI files can be accessed from the current directory.              |
|   If they can't, tell the user and end the application.                     |
| Create the main window for the application                                  |
| Start the event processing loop                                             |
-----------------------------------------------------------------------------*/
   IToolBarButton::setDefaultStyle(
     IToolBarButton::classDefaultStyle
     &~IToolBarButton::standardFormat );

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

