/******************************************************************************
* .FILE:         asetcv.cpp                                                   *
*                                                                             *
* .DESCRIPTION:  Set Canvas Example:  Class Implementation                    *
*                                                                             *
* .CLASSES:      ASetCanvas                                                   *
*                AButtonHandler                                               *
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
#include <ipoint.hpp>
#include <istring.hpp>
#include <icoordsy.hpp>
#include "asetcv.hpp"
#include "asetcv.h"

/******************************************************************************
* main  - Application entry point                                             *
******************************************************************************/
int main()
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::kOriginLowerLeft );
  ASetCanvas mainWindow(ID_MAIN);
  IApplication::current().run();
  return 0;
} /* end main */

/******************************************************************************
* ASetCanvas :: ASetCanvas - Constructor for our main window                  *
******************************************************************************/
ASetCanvas::ASetCanvas(unsigned long windowId)
  : IFrameWindow( windowId )
  /*---------------------------------------------------------------------------|
  |  Create the ISplitCanvases                                                 |
  ----------------------------------------------------------------------------*/
  , horzCanvas1( ID_HORIZCANVAS1, this, this )
  , vertCanvas1( ID_VERTCANVAS1,  &horzCanvas1, &horzCanvas1 )
  , vertCanvas2( ID_VERTCANVAS2,  &horzCanvas1, &horzCanvas1 )
  , vertCanvas3( ID_VERTCANVAS3,  &horzCanvas1, &horzCanvas1 )
  /*---------------------------------------------------------------------------|
  |  Create the ISetCanvases                                                   |
  ----------------------------------------------------------------------------*/
  , setCanvas1( ID_SETCANVAS1, &vertCanvas1, &vertCanvas1 )
  , setCanvas2( ID_SETCANVAS2, &vertCanvas1, &vertCanvas1 )
  , setCanvas3( ID_SETCANVAS3, &vertCanvas2, &vertCanvas2 )
  , setCanvas4( ID_SETCANVAS4, &vertCanvas2, &vertCanvas2 )
  , setCanvas5( ID_SETCANVAS5, &vertCanvas3, &vertCanvas3 )
  , setCanvas6( ID_SETCANVAS6, &vertCanvas3, &vertCanvas3 )
  /*---------------------------------------------------------------------------|
  |  Create the radio buttons for each ISetCanvases                            |
  ----------------------------------------------------------------------------*/
  , vRadioGroup1( ID_VRADIO,      &setCanvas1, 5, AButtons::vertical )
  , vRadioGroup2( ID_VRADIO + 5,  &setCanvas3, 6, AButtons::vertical )
  , vRadioGroup3( ID_VRADIO + 11, &setCanvas5, 7, AButtons::vertical )
  , hRadioGroup1( ID_HRADIO,      &setCanvas2, 5, AButtons::horizontal )
  , hRadioGroup2( ID_HRADIO + 5,  &setCanvas4, 6, AButtons::horizontal )
  , hRadioGroup3( ID_HRADIO + 11, &setCanvas6, 7, AButtons::horizontal )
{
/*-----------------------------------------------------------------------------|
|  Set the icon for the main window and make the split canvas the client area  |
------------------------------------------------------------------------------*/
  setIcon( id() );
  setClient( &horzCanvas1 );

/*-----------------------------------------------------------------------------|
|  Set the split canvas orientation                                            |
------------------------------------------------------------------------------*/
  horzCanvas1.setOrientation( ISplitCanvas::horizontalSplit );
  vertCanvas1.setOrientation( ISplitCanvas::verticalSplit );
  vertCanvas2.setOrientation( ISplitCanvas::verticalSplit );
  vertCanvas3.setOrientation( ISplitCanvas::verticalSplit );

/*-----------------------------------------------------------------------------|
|  Set three ISetCanvases to have 3 vertical decks                             |
------------------------------------------------------------------------------*/
  setCanvas1.setDeckOrientation( ISetCanvas::vertical );
  setCanvas3.setDeckOrientation( ISetCanvas::vertical );
  setCanvas5.setDeckOrientation( ISetCanvas::vertical );

/*-----------------------------------------------------------------------------|
|  Set three ISetCanvases to have 3 horizontal decks                           |
------------------------------------------------------------------------------*/
  setCanvas2.setDeckOrientation( ISetCanvas::horizontal );
  setCanvas4.setDeckOrientation( ISetCanvas::horizontal );
  setCanvas6.setDeckOrientation( ISetCanvas::horizontal );

/*-----------------------------------------------------------------------------|
|  Set each ISetCanvases to have 3 decks                                       |
------------------------------------------------------------------------------*/
  setCanvas1.setDeckCount( 3 );
  setCanvas2.setDeckCount( 3 );
  setCanvas3.setDeckCount( 3 );
  setCanvas4.setDeckCount( 3 );
  setCanvas5.setDeckCount( 3 );
  setCanvas6.setDeckCount( 3 );

  show();

} /* end ASetCanvas :: ASetCanvas */

/******************************************************************************
* ASetCanvas::~ASetCanvas - Destructor for the application                    *
******************************************************************************/
ASetCanvas::~ASetCanvas()
{
} /* end ASetCanvas :: ~ASetCanvas */

/******************************************************************************
* Class AButtons::AButtons - Creates the number of radio buttons              *
******************************************************************************/
AButtons::AButtons( unsigned long firstButtonId
                   ,ISetCanvas * parentOwnerWindow
                   ,unsigned long number
                   ,MyCanvasType canvasType )
  :numberOfButtons( number )
{

/*-----------------------------------------------------------------------------|
|  Create the radio buttons.                                                   |
|  If the fourth button, create a push button instead.                         |
------------------------------------------------------------------------------*/
  for ( unsigned long i = 0 ; i < numberOfButtons; i++ )
  {
    if ( i != 3 )
      button[i] = new IRadioButton( firstButtonId + i,
                  parentOwnerWindow, parentOwnerWindow );
    else
      button[i] = new IPushButton( firstButtonId + i,
                  parentOwnerWindow, parentOwnerWindow );

/*-----------------------------------------------------------------------------|
|  If the first radio button, indicate if in a vertical or horizontal deck.    |
|  Otherwise, give the radio button a number.                                  |
------------------------------------------------------------------------------*/
    if ( i == 0 )
    {
      if ( canvasType == vertical )
        button[i]->setText( STR_VERTICAL );
      else
        button[i]->setText( STR_HORIZONTAL );
    }
    else
      button[i]->setText( STR_TEXT + i );

  }

/*-----------------------------------------------------------------------------|
|  Sets the first button to the tabStop and Group Styles.                      |
|  Selects the first radio button in the group.                                |
|  Sets focus to the first button                                              |
------------------------------------------------------------------------------*/
  button[0]->enableGroup().enableTabStop();
  ((IRadioButton*)button[0])->select();
  button[0]->setFocus();

/*-----------------------------------------------------------------------------|
|  Increase the size of the push button to demonstrate how various window      |
|    sizes appear in horizontal and vertical decks.                            |
------------------------------------------------------------------------------*/
  ISize
    sz = ((IPushButton*)button[3])->minimumSize();
  button[3]->setMinimumSize( sz *= 2 );

} /* end AButtons :: AButtons */

/******************************************************************************
* AButtons::~AButtons - Destructor for the radio buttons                      *
******************************************************************************/
AButtons::~AButtons()
{
  for (unsigned int i = 0; i < numberOfButtons; i++ )
  {
    delete button[i];
  }

} /* end AButtons :: ~AButtons */

