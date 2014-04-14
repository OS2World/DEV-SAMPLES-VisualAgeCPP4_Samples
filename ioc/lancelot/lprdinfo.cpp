/******************************************************************************
* .FILE:         lprdinfo.cpp                                                 *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Implementation   *
*                                                                             *
* .CLASSES:      LProdInfoDialog                                              *
*                                                                             *
* .COPYRIGHT:                                                                 *
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
#include "lprdinfo.hpp"
#include "lancelot.h"


/***********************************************************/
/* Constructor for the product information dialog class.   */
/***********************************************************/
LProdInfoDialog::LProdInfoDialog( IWindow *owner )
  :IFrameWindow( ID_PRODINFO, IWindow::desktopWindow(), owner,
                 IRectangle(),
                 IFrameWindow::systemMenu
                 | IFrameWindow::dialogBackground
                 | IFrameWindow::dialogBorder )
  ,canvas( ID_PRODINFO_CANVAS, this, this )
  ,iconCtl( ID_PRODINFO_ICON, &canvas, &canvas )
  ,text1( ID_PRODINFO_TEXT1, &canvas, &canvas )
  ,text2( ID_PRODINFO_TEXT2, &canvas, &canvas )
  ,text3( ID_PRODINFO_TEXT3, &canvas, &canvas )
  ,text4( ID_PRODINFO_TEXT4, &canvas, &canvas )
  ,text5( ID_PRODINFO_TEXT5, &canvas, &canvas )
  ,button( ID_PRODINFO_OK, &canvas, &canvas )
{
   // Set self as command event handler
   handleEventsFor(this);

   // Set text for the controls
   iconCtl.setIcon( ID_MAIN );
   text1.setText( IResourceId( STR_MAIN_TITLE ) );
   text1.setForegroundColor( IColor::kRed );
   text2.setText( IResourceId( STR_PRODINFO_TEXT2 ) );
   text3.setText( IResourceId( STR_PRODINFO_TEXT3 ) );
   text4.setText( IResourceId( STR_PRODINFO_TEXT4 ) );
   text5.setText( IResourceId( STR_PRODINFO_TEXT5 ) );
   button.setText( IResourceId( STR_OK ) );

   // Set the canvas orientation to veritical
   // Set the canvas alignment to center all the controls
   canvas.setDeckOrientation( ISetCanvas::vertical );
   canvas.setAlignment( ISetCanvas::centerCenter );

   // Set the client as the canvas
   setClient( &canvas );

/*-----------------------------------------------------------------------------
| Resize the window based on the minimum size of the canvas                   |
-----------------------------------------------------------------------------*/
   moveSizeToClient( IRectangle( IPoint(
                     IWindow::desktopWindow()->size().width()/2,
                     IWindow::desktopWindow()->size().height()/2 ),
                     canvas.minimumSize() ) );

/*-----------------------------------------------------------------------------
| Center the frame window                                                     |
-----------------------------------------------------------------------------*/
   moveSizeTo( rect().centerAt( IWindow::desktopWindow()->rect().center() ) );

/*-----------------------------------------------------------------------------
| Show the dialog window                                                      |
-----------------------------------------------------------------------------*/
   setFocus();
   show();

}


/***********************************************************/
/* Destructor for the product information dialog class.    */
/***********************************************************/
LProdInfoDialog :: ~LProdInfoDialog()
{
   stopHandlingEventsFor(this);
}



/***********************************************************/
/* Command handler function for the product information    */
/* dialog. There is only one control to handle.            */
/***********************************************************/
bool LProdInfoDialog :: command( ICommandEvent& cmdevt)
{
  switch ( cmdevt.commandId() )
  {
     case ID_PRODINFO_OK:
        dismiss(ID_PRODINFO_OK);
        return true;
  }

  return false;
}
