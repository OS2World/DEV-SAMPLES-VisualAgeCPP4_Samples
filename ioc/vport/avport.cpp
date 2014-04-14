/******************************************************************************
* .FILE:         avport.cpp                                                   *
*                                                                             *
* .DESCRIPTION:  Canvas Classes Example 4 - ViewPort (Implementation)         *
*                                                                             *
* .CLASSES:      aviewport                                                    *
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
#include <ireslib.hpp>
#include <icoordsy.hpp>
#include "avport.h"
#include "avport.hpp"

/*******************************************************************************
* main - Application entry point                                               *
*******************************************************************************/
int main()
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::kOriginLowerLeft );
  AViewPort mainWindow(WND_MAIN);
  IApplication::current().run();
  return 0;
} /* end main() */

/******************************************************************************
* Class AViewPort :: AViewPort - constructor for our main window              *
******************************************************************************/

AViewPort :: AViewPort(unsigned long windowId)
  : IFrameWindow( windowId )
  , clientViewPort( WND_VIEWPORT, this, this )
  , bitmap( WND_BITMAP, &clientViewPort, &clientViewPort , IResourceId(BMP_ID) )
{
/*-----------------------------------------------------------------------------|
| Size the screen to be slighly smaller than the bitmap.                       |
| Set the viewport as the client area.                                         |
| Set focus to the main window and then show it.                               |
------------------------------------------------------------------------------*/
  sizeTo( ISize( bitmap.minimumSize().width()*0.8,
                 bitmap.minimumSize().height()*0.9 ) );
  setIcon( id() );
  setClient( &clientViewPort );
  setFocus().show();
} /* end AViewPort :: AViewPort(...) */
