/******************************************************************************
* .FILE:         dmsamp1.cpp                                                  *
*                                                                             *
* .DESCRIPTION:  Direct Manipulation Sample Program 1: Class Implementation   *
*                                                                             *
* .CLASSES:                                                                   *
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
#include <iframe.hpp>
#include <ientryfd.hpp>
#include <idmefit.hpp>
#include <idmhndlr.hpp>
#include <icoordsy.hpp>
#include "dmsamp1.h"

/*------------------------------------------------------------------------------
| main - Application Entry point                                               |
------------------------------------------------------------------------------*/
int main()
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::kOriginLowerLeft );

/*-----------------------------------------------------------------------------|
| Create a generic frame window.                                               |
------------------------------------------------------------------------------*/
  IFrameWindow
    frame( WND_MAIN );

/*-----------------------------------------------------------------------------|
| Create 2 entry fields for the client area.                                   |
------------------------------------------------------------------------------*/
  IEntryField
    client( 1000, &frame, &frame ),
    ext   ( 1001, &frame, &frame );

/*-----------------------------------------------------------------------------|
| Enable source and target direct manipulation support for both entry fields.  |
------------------------------------------------------------------------------*/
  IDMHandler::enableDragDropFor( &client );
  IDMHandler::enableDragDropFor( &ext );

/*-----------------------------------------------------------------------------|
| Frame setup - Put both entry fields in the client area, with one  added as   |
| an extension.                                                                |
------------------------------------------------------------------------------*/
  frame
    .setIcon( frame.id() )
    .setClient( &client )
    .addExtension( &ext, IFrameWindow::belowClient, 0.5 )
    .setFocus()
    .show();

/*-----------------------------------------------------------------------------|
| Run Direct Manipulation Sample 1                                             |
|-----------------------------------------------------------------------------*/
  IApplication::current().run();
  return 0;
}
