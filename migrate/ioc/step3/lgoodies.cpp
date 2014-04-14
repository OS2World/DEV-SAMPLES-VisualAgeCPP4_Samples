/******************************************************************************
* FILE NAME: lgoodies.cpp                                                     *
*                                                                             *
* Classes:                                                                    *
*   LAskUser                                                                  *
*   LAskUserCommandHandler                                                    *
*   LWindow                                                                   *
*                                                                             *
* COPYRIGHT:                                                                  *
*   Licensed Materials - Property of IBM                                      *
*   (C) Copyright IBM Corporation 1992, 1995                                  *
*   All Rights Reserved                                                       *
*   US Government Users Restricted Rights - Use, duplication, or disclosure   *
*   restricted by GSA ADP Schedule Contract with IBM Corp.                    *
******************************************************************************/
#include "lgoodies.hpp"
#include "lancelot.h"

/******************************************************************************
* Class LAskUser - Constructor                                                *
*   Up to 4 lines of text can be added to this frame window                   *
******************************************************************************/
LAskUser::LAskUser( unsigned long id, IWindow* parent, IWindow* owner,
                    const IString& theText1,
                    const IString& theText2,
                    const IString& theText3,
                    const IString& theText4 )
     :IFrameWindow         ( id, parent, owner, IRectangle(),
                             titleBar | dialogBackground
                             | dialogBorder | systemMenu ),
      title                ( this, STR_ASKUSER_TITLE ),
      canvas               ( ID_ASKUSER_CANVAS, this, this ),
      bCanvas              ( ID_ASKUSER_BUTTON_CANVAS, &canvas, &canvas ),
      staticText1          ( ID_ASKUSER_TEXT, &canvas, &canvas, IRectangle(),
                             IStaticText::classDefaultStyle
                             | IStaticText::wordBreak ),
      staticText2          ( ID_ASKUSER_TEXT, &canvas, &canvas, IRectangle(),
                             IStaticText::classDefaultStyle
                             | IStaticText::wordBreak ),
      staticText3          ( ID_ASKUSER_TEXT, &canvas, &canvas, IRectangle(),
                             IStaticText::classDefaultStyle
                             | IStaticText::wordBreak ),
      staticText4          ( ID_ASKUSER_TEXT, &canvas, &canvas, IRectangle(),
                             IStaticText::classDefaultStyle
                             | IStaticText::wordBreak ),
      entry                ( ID_ASKUSER_ENTRY, &canvas, &canvas, IRectangle(),
                             IEntryField::classDefaultStyle
                             | IControl::tabStop ),
      okButton             ( ID_BUTTON_OK, &bCanvas, &bCanvas, IRectangle(),
                             IPushButton::classDefaultStyle
                             | IPushButton::defaultButton
                             | IControl::tabStop | IControl::group ),
      cancelButton         ( ID_BUTTON_CANCEL, &bCanvas, &bCanvas, IRectangle(),
                             IPushButton::classDefaultStyle ),
      cmdHdr               ( this ),
      ok                   ( false )
{
/*-----------------------------------------------------------------------------
| Set the text for each static text object                                    |
-----------------------------------------------------------------------------*/
   staticText1.setText( theText1 );
   staticText2.setText( theText2 );
   staticText3.setText( theText3 );
   staticText4.setText( theText4 );
   okButton.setText( STR_OK );
   cancelButton.setText( STR_CANCEL );

/*-----------------------------------------------------------------------------
| Add the objects to the canvas                                               |
-----------------------------------------------------------------------------*/
   canvas.addToCell( &staticText1,  2,  2, 10,  1 );
   canvas.addToCell( &staticText2,  2,  3, 10,  1 );
   canvas.addToCell( &staticText3,  2,  4, 10,  1 );
   canvas.addToCell( &staticText4,  2,  5, 10,  1 );
   canvas.addToCell( &entry,        2,  7, 10,  2 );
   canvas.addToCell( &bCanvas,      3, 11 );

/*-----------------------------------------------------------------------------
| Set the client to be the canvas                                             |
-----------------------------------------------------------------------------*/
    setClient( &canvas );

/*-----------------------------------------------------------------------------
| Start handling command events                                               |
-----------------------------------------------------------------------------*/
    cmdHdr.handleEventsFor( this );

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
| Set focus to the entryfield                                                 |
| Show the frame window modally                                               |
-----------------------------------------------------------------------------*/
   entry.setFocus();
   showModally();
}


/******************************************************************************
* Class LAskUser - Destructor                                                 *
******************************************************************************/
LAskUser::~LAskUser()
{
   cmdHdr.stopHandlingEventsFor( this );
}


/******************************************************************************
* Class LAskUserCommandHandler - Constructor for command handler              *
*                                                                             *
* Create yourself as an ICommandHandler                                       *
* Store the owner window                                                      *
******************************************************************************/
LAskUserCommandHandler::LAskUserCommandHandler( LAskUser* owner )
     :ICommandHandler(),
      theOwner( owner )
{}


/******************************************************************************
* Class LAskUserCommandHandler - Destructor                                   *
******************************************************************************/
LAskUserCommandHandler::~LAskUserCommandHandler()
{}


/******************************************************************************
* Class LAskUserCommandHandler :: command()                                   *
*   Handle any command events for the frame window                            *
******************************************************************************/
IBase::Boolean LAskUserCommandHandler::command( ICommandEvent& event )
{
   Boolean
      retCode = false;

   switch ( event.commandId() )
   {
/*-----------------------------------------------------------------------------
| If the user pressed the OK button,                                          |
| - Set the pressed OK button flag to true                                    |
| - Dismiss the frame window                                                  |
-----------------------------------------------------------------------------*/
      case ID_BUTTON_OK:
      {
         theOwner->setOk( true );
         theOwner->dismiss();
         retCode = true;
         break;
      }
/*-----------------------------------------------------------------------------
| If the user pressed the CANCEL button,                                      |
| - Set the pressed OK button flag to false                                   |
| - Dismiss the frame window                                                  |
-----------------------------------------------------------------------------*/
      case ID_BUTTON_CANCEL:
      {
         theOwner->setOk( false );
         theOwner->dismiss();
         retCode = true;
         break;
      }
   }

   return retCode;
}


/******************************************************************************
* Class LFrameWindow - Constructor                                            *
*   Common frame window functions.                                            *
******************************************************************************/
LFrameWindow::LFrameWindow()
{}


/******************************************************************************
* Class LFrameWindow - Destructor                                             *
******************************************************************************/
LFrameWindow::~LFrameWindow()
{}


/******************************************************************************
* Class LFrameWindow::bestFit()                                               *
*   If a frame window spans past the desktop window size,                     *
*   recalculate the best location for the frame window.                       *
******************************************************************************/
IPoint LFrameWindow::bestFit( IFrameWindow* frameWin )
{
   int
      oldXPosition = frameWin->rect().left(),
      oldYPosition = frameWin->rect().bottom();

   if ( oldXPosition < 0 )
      oldXPosition = 0;
   if ( oldYPosition < 0 )
      oldYPosition = 0;

   ISize
      desktopSize( IWindow::desktopWindow()->size() );
   int
      newXPosition = frameWin->rect().right() - desktopSize.width(),
      newYPosition = frameWin->rect().top() - desktopSize.height();
   if ( newXPosition > 0 )
   {
      newXPosition = oldXPosition - newXPosition;
      if ( newXPosition < 0 )
         newXPosition = 0;
   }
   else
      newXPosition = oldXPosition;
   if ( newYPosition > 0 )
   {
      newYPosition = oldYPosition - newYPosition;
      if ( newYPosition < 0 )
         newYPosition = 0;
   }
   else
      newYPosition = oldYPosition;

   return IPoint( newXPosition, newYPosition );
}
