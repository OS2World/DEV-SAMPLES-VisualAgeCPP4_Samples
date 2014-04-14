/*******************************************************************************
* .FILE:         asplitcv.cpp
*                                                                              *
* .DESCRIPTION:  Split Canvas Example:  Class Implementation                   *
*                                                                              *
* .CLASSES:      ASplitCanvas                                                  *
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
*******************************************************************************/
#include <iapp.hpp>
#include <icoordsy.hpp>
#include "asplitcv.hpp"
#include "asplitcv.h"

/******************************************************************************
* main  - Application entry point                                             *
*******************************************************************************/
int main()
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::kOriginLowerLeft );
  ASplitCanvas mainWindow(WND_MAIN);
  IApplication::current().run();
  return 0;
} /* end main */

/******************************************************************************
* ASplitCanvas :: ASplitCanvas - Constructor for our main window              *
*                                                                             *
* Constructs the window as an IFrameWindow.                                   *
* Initializes the horizontal split canvas.                                    *
* Initializes the vertical canvas.                                            *
* Places the text string in each window                                       *
******************************************************************************/

ASplitCanvas :: ASplitCanvas( unsigned long windowId )
  : IFrameWindow( windowId )
  , horzCanvas( WND_CANVAS, this, this )
  , vertCanvas( WND_CANVAS2, &horzCanvas, &horzCanvas )
  , lText( WND_TXTL, &vertCanvas, &vertCanvas )
  , rText( WND_TXTR, &vertCanvas, &vertCanvas )
  , bText( WND_TXTB, &horzCanvas, &horzCanvas )
{
/*-----------------------------------------------------------------------------|
|  Set the icon for the main window.                                           |
------------------------------------------------------------------------------*/
  setIcon( id() );

/*-----------------------------------------------------------------------------|
| Set the canvas to a horizontal split bar and make it the client area.        |
------------------------------------------------------------------------------*/
  horzCanvas.setOrientation( ISplitCanvas::horizontalSplit );
  setClient( &horzCanvas );

/*-----------------------------------------------------------------------------|
| Set the cavas to a vertical split bar.                                       |
------------------------------------------------------------------------------*/
  vertCanvas.setOrientation( ISplitCanvas::verticalSplit );

/*----------------------------------------------------------------------------|
|  Sets and places the static text in the top left window.                    |
-----------------------------------------------------------------------------*/
  lText.setText(STR_TOPLEFT);
  lText.setAlignment( IStaticText::centerCenter );

/*----------------------------------------------------------------------------|
|  Sets and places the static text in the top right window.                   |
-----------------------------------------------------------------------------*/
  rText.setText(STR_TOPRIGHT);
  rText.setAlignment( IStaticText::centerCenter );

/*----------------------------------------------------------------------------|
|  Sets and places the static text in the bottom window.                      |
-----------------------------------------------------------------------------*/
  bText.setText(STR_BOTTOM);
  bText.setAlignment( IStaticText::centerCenter );

/*-----------------------------------------------------------------------------|
| Set focus to the main window and show the window on the screen.              |
------------------------------------------------------------------------------*/
  setFocus().show();

} /* end ASplitCanvas :: ASplitCanvas(...) */
