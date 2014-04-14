/*
-------------------------------------------------------------------------------
Copyright (c) IBM Corporation 1996, 1997.
All Rights Reserved.

Permission is granted to copy, use, modify, and merge this software into your
applications and to permit others to do any of the foregoing. You must include
this permission and copyright notice in all copies and modified versions of
this software. THIS SOFTWARE IS PROVIDED IN ITS 'AS IS' CONDITION.
IBM DISCLAIMS ANY LIABILITY OF ANY KIND FOR DAMAGES WHATSOEVER RESULTING
FROM THE USE OF THIS SOFTWARE.
-------------------------------------------------------------------------------
*/

#include "2dpaint.hpp"
#include "2dpglbl.h"
#include <iiconctl.hpp>
#include <ifontdlg.hpp>
#include <iostream.h>
#include <stdlib.h>

#ifndef _ISTRMMOD_
#include <istrmmod.hpp>
#endif

IStreamModule gSampleStreamModule("PrintTestStreamModule");

// global color pallet
IBaseColor *colorTable[PALLETCANVAS_SQUARE][PALLETCANVAS_SQUARE];

const  GCoordinate kMMPerInch = 25.4;
const  GCoordinate dpiAlbert = 72.0;

//*************************************************************************
// Class IColorSelector: method definitions                               *
//*************************************************************************

/*
 * Function: IColorSelector::IColorSelector
 *
 * Parameters:
 *   id     : the window's id
 *   parent : a pointer to the parent window
 *   owner  : a pointer to the owner window
 *   t      : specifies type (Red_type, Green_type, Blue_type
 *   h      : specifies horizontal (true) or vertical (false) orientation
 *
 * Return value: NONE
 *
 * Purpose: constructor for IColorSelector
 *
*/

IColorSelector::IColorSelector(long id, IWindow* parent, IWindow* owner,
                               IColorSelector::ColorType t, bool h)
  : ICanvas(id, parent, owner, IRectangle(), ICanvas::defaultStyle() |
                                             IWindow::clipSiblings),
    win(owner),
    value(0),
    type(t),
    capturing(false),
    horizontal(h)
{
  // start up the event handlers
  IMouseHandler::handleEventsFor(this);
  IPaintHandler::handleEventsFor(this);

  // size with respect to orientation
  if(horizontal)
     sizeTo(ISize(IGPoint2D(COLORSELECTOR_WIDTH,COLORSELECTOR_HEIGHT).fX,
                  IGPoint2D(COLORSELECTOR_WIDTH,COLORSELECTOR_HEIGHT).fY));

  else
     sizeTo(ISize(IGPoint2D(COLORSELECTOR_WIDTH,COLORSELECTOR_HEIGHT).fY,
                  IGPoint2D(COLORSELECTOR_WIDTH,COLORSELECTOR_HEIGHT).fX));

  managedPresSpacePtr = new IManagedPresSpaceHandle(this);

}

/*
 * Function: IColorSelector::~IColorSelector
 *
 * Parameters: NONE
 *
 * Return Value: NONE
 *
 * Purpose: destructor for IColorSelector
 *
*/

IColorSelector::~IColorSelector()
{
  // shut down the event handlers
  IMouseHandler::stopHandlingEventsFor(this);
  IPaintHandler::stopHandlingEventsFor(this);

  delete managedPresSpacePtr;

}

/*
 * Function: IColorSelector::GetValue
 *
 * Parameters: NONE
 *
 * Return Value: the current color value selected
 *
 * Purpose: returns the current color value (between 0 and 1) selected
 *
*/

CharIntensity IColorSelector::GetValue()
{
  return value;

}

/*
 * Function: IColorSelector::SetValue
 *
 * Parameters:
 *   val : the new value to be selected/set range 0-255
 *
 * Return value: returns the previous selection value
 *
 * Purpose: changes the current value of the selection and
 *          repositions the selection indicator
 *
*/

CharIntensity IColorSelector::SetValue(CharIntensity val)
{
  // create the rendering devices
  IBaseRootGrafPort myDisplayPort(this->presSpace());

  CharIntensity oldVal = value;    // the current selection
  CharIntensity valPos = value / (255/COLORSELECTOR_COLORS);
  
  // erase the old selection indicator
  if(horizontal) {

     for(CharIntensity i = valPos-1; (i < valPos+2) && (i <= COLORSELECTOR_COLORS); i++) {

      IGLine2D line(IGPoint2D(i,0),IGPoint2D(i,COLORSELECTOR_HEIGHT));
      CharIntensity j = i*(255/COLORSELECTOR_COLORS);
      if(j < 0) j = 0;

      switch(type) {

        case Red_type:
          myDisplayPort.draw(line,IFrameBundle(IBaseColor(j,0,0),2));
          break;

        case Green_type:
          myDisplayPort.draw(line,IFrameBundle(IBaseColor(0,j,0),2));
          break;

        case Blue_type:
          myDisplayPort.draw(line,IFrameBundle(IBaseColor(0,0,j),2));
          break;

        case Gray_type:
          myDisplayPort.draw(line,IFrameBundle(IBaseColor(j),2));
          break;

      }

    }

    // render the new selection indicator
    valPos = val / (255/COLORSELECTOR_COLORS);
    IGRect2D selection(IGPoint2D(valPos-1,0),IGPoint2D(valPos+1,COLORSELECTOR_HEIGHT));
    myDisplayPort.draw(selection,IFrameBundle(IBaseColor(IBaseColor::kWhite)));

  }

  else {  // vertical

     for(CharIntensity i = valPos-1; (i < valPos+2) && (i <= COLORSELECTOR_COLORS); i++) {

      IGLine2D line(IGPoint2D(0,i),IGPoint2D(COLORSELECTOR_HEIGHT,i));
      CharIntensity j = i*(255/COLORSELECTOR_COLORS);
      if(j < 0) j = 0;

      switch(type) {

        case Red_type:
          myDisplayPort.draw(line,IFrameBundle(IBaseColor(j,0,0),2));
          break;

        case Green_type:
          myDisplayPort.draw(line,IFrameBundle(IBaseColor(0,j,0),2));
          break;

        case Blue_type:
          myDisplayPort.draw(line,IFrameBundle(IBaseColor(0,0,j),2));
          break;

        case Gray_type:
          myDisplayPort.draw(line,IFrameBundle(IBaseColor(j),2));
          break;

      }

    }

    // render the new selection indicator
    valPos = val / (255/COLORSELECTOR_COLORS);
    IGRect2D selection(IGPoint2D(0,valPos-1),IGPoint2D(COLORSELECTOR_HEIGHT,valPos+1));
    myDisplayPort.draw(selection,IFrameBundle(IBaseColor(IBaseColor::kWhite)));

  }

  value = val;
  return oldVal;

}

/*
 * Function: IColorSelector::paintWindow
 *
 * Parameter:
 *   event: the type of paint event to be handled - ignored in this method
 *
 * Return value: returns true if painting is done - in this case; always true
 *
 * Purpose: renders the control to the screen when update required
 *
*/

bool IColorSelector::paintWindow(IPaintEvent &event)
{
  // create the rendering devices
  IBaseRootGrafPort myDisplayPort(this->presSpace());

  CharIntensity valPos;     // the indicator position

  // render the gradient field
  if(horizontal) {

     for(CharIntensity i = 0; i <= COLORSELECTOR_COLORS; i++) {

      IGLine2D line(IGPoint2D(i,0),IGPoint2D(i,COLORSELECTOR_HEIGHT-1));

      CharIntensity j = i * (255/COLORSELECTOR_COLORS);
          if (j < 0) j = 0;

      switch(type) {

        case Red_type:
          myDisplayPort.draw(line,IFrameBundle(IBaseColor(j,0,0),2));
          break;

        case Green_type:
          myDisplayPort.draw(line,IFrameBundle(IBaseColor(0,j,0),2));
          break;

        case Blue_type:
          myDisplayPort.draw(line,IFrameBundle(IBaseColor(0,0,j),2));
          break;

        case Gray_type:
          myDisplayPort.draw(line,IFrameBundle(IBaseColor(j),2));
          break;

      }

    }

    // render the selection indicator
    valPos = value / (255/COLORSELECTOR_COLORS);
    IGRect2D selection(IGPoint2D(valPos-1,0),IGPoint2D(valPos+1,COLORSELECTOR_HEIGHT-1));
    myDisplayPort.draw(selection,IFrameBundle(IBaseColor(IBaseColor::kWhite)));
}

  else {  // vertical

     for(CharIntensity i = 0; i <= COLORSELECTOR_COLORS; i++) {

      IGLine2D line(IGPoint2D(0,i),IGPoint2D(COLORSELECTOR_HEIGHT-1,i));

      CharIntensity j = i * (255/COLORSELECTOR_COLORS);
          if (j < 0) j = 0;

      switch(type) {

        case Red_type:
          myDisplayPort.draw(line,IFrameBundle(IBaseColor(j,0,0),2));
          break;

        case Green_type:
          myDisplayPort.draw(line,IFrameBundle(IBaseColor(0,j,0),2));
          break;

        case Blue_type:
          myDisplayPort.draw(line,IFrameBundle(IBaseColor(0,0,j),2));
          break;

        case Gray_type:
          myDisplayPort.draw(line,IFrameBundle(IBaseColor(j),2));
          break;

      }

    }

    // render the selection indicator
    valPos = value / (255/COLORSELECTOR_COLORS);
    IGRect2D selection(0,valPos-1,COLORSELECTOR_HEIGHT-5,valPos+1);
    myDisplayPort.draw(selection,IFrameBundle(IBaseColor(IBaseColor::kWhite)));

  }

  return true;

}

/*
 * Function: IColorSelector::mouseClicked
 *
 * Parameters:
 *   event: used to describe the type of the mouse click event
 *
 * Return value: returns true if the event was processed
 *
 * Purpose: handles mouse clicks for updating the current selection
 *
*/

bool IColorSelector::mouseClicked(IMouseClickEvent &event)
{
  bool result = false;     // the return result

  if ( event.mouseButton() == IMouseClickEvent::button1 &&
       event.mouseAction() == IMouseClickEvent::down ) {

    CharIntensity val;     // the value of the current selection

    // capture the mouse pointer to allow dragging of the indicator
    capturing = true;
    capturePointer();

    // create the rendering devices
    IBaseRootGrafPort myDisplayPort(this->presSpace());

    // Get the mouse position in world space
    IGPoint2D talPoint;
    IPoint point(event.mousePosition());
    talPoint = myDisplayPort.pixelToPointSize().transformPoint(IGPoint2D(point));

    // calculate the value selection from the mouse position
    if(horizontal)
      val = (CharIntensity)(talPoint.fX * (255/COLORSELECTOR_COLORS));

    else
      val = (CharIntensity)(talPoint.fY * (255/COLORSELECTOR_COLORS));

    // do some range checking/adjustment
    if(val > 255) val = 255;

    else if(val < 0) val = 0;

    // set the new selection and do nescessary paint updates
    SetValue(val);
    ((IPalletDialog*)win)->SetValue(value,type);

    result = true;

  }

  else if( event.mouseButton() == IMouseClickEvent::button1 &&
           event.mouseAction() == IMouseClickEvent::up ) {

    // disable mouse pointer capturing when the mouse is released
    capturePointer(false);
    capturing = false;
    result = true;

  }

  return result;

}

/*
 * Function: IColorSelector::mouseMoved
 *
 * Parameteres:
 *   event: contains the mouse position
 *
 * Return value: returns true when the event is processed
 *
 * Purpose: handles dragging of the selection indicator
 *
*/

bool IColorSelector::mouseMoved(IMouseEvent &event)
{
  bool result = false;     // the return result

  if(capturing) {  // if the mouse is down...

    CharIntensity val;

    // create rendering devices
    IBaseRootGrafPort myDisplayPort(this->presSpace());

    // get the mouse position in world space
    IPoint point(event.mousePosition());
    IGPoint2D talPoint;
    talPoint = myDisplayPort.pixelToPointSize().transformPoint(IGPoint2D(point));

    // get the value with respect to the mouse position
    if(horizontal)
      val = (CharIntensity)(talPoint.fX * (255/COLORSELECTOR_COLORS));

    else
      val = (CharIntensity)(talPoint.fY * (255/COLORSELECTOR_COLORS));

    // do some range checking/adjustment
    if(val > 255) val = 255;

    else if(val < 0) val = 0;

    // set the value and do paint updates where necessary
    SetValue(val);
    ((IPalletDialog*)win)->SetValue(value,type);

    result = true;

  }

  return result;

}

//*************************************************************************
// Class IColorSquare: method definitions                                 *
//*************************************************************************

/*
 * Function: IColorSquare::IColorSquare
 *
 * Parameters:
 *   id    : the windows id
 *   parent: pointer to the parent window
 *   owner : pointer to the owner window
 *
 * Return value: NONE
 *
 * Purpose: constructor for IColorSquare
 *
*/

IColorSquare::IColorSquare(const unsigned long id, IWindow* parent, IWindow* owner)
  : ICanvas(id,parent,owner),
  win(parent->parent())
{
  // start up the event handlers
  IPaintHandler::handleEventsFor(this);

  managedPresSpacePtr = new IManagedPresSpaceHandle(this);
  sizeTo(ISize(IGPoint2D(COLORSQUARE_WIDTH,COLORSQUARE_WIDTH).fX,
               IGPoint2D(COLORSQUARE_WIDTH,COLORSQUARE_WIDTH).fY));

  moveTo(IPoint(IGPoint2D(PALLETCANVAS_SIZE+2*PALLETDIALOG_SPACER,PALLETDIALOG_SPACER)));
}

/*
 * Function: IColorSquare::~IColorSquare
 *
 * Parameters: NONE
 *
 * Return value: NONE
 *
 * Purpose: destructor for IColorSquare
 *
*/

IColorSquare::~IColorSquare()
{
  // shut down the event handlers
  IPaintHandler::stopHandlingEventsFor(this);

  delete managedPresSpacePtr;
}

/*
 * Function: IColorSquare::paintWindow
 *
 * Parameters:
 *   event: the type of paint event to be handled - ignored in this method
 *
 * Return value: returns true if painting is done - always true in this case
 *
 * Purpose: renders the control to the screen when update is required
 *
*/

bool IColorSquare::paintWindow(IPaintEvent& event)
{
  // create the rendering devices
  IBaseRootGrafPort myDisplayPort(this->presSpace());
  
  IGPoint2D talPoint;
  talPoint = myDisplayPort.pixelToPointSize().transformPoint(IGPoint2D(COLORSQUARE_WIDTH-1,COLORSQUARE_WIDTH-1));
  IGRect2D theRect(IGPoint2D(0,0),talPoint);
  
  myDisplayPort.draw(theRect,IFillAndFrameBundle(((IPalletDialog*)win)->color(),
                IBaseColor(IBaseColor::kBlack)));

  return true;

}


/*
 * Function: IPalletCanvas::IPalletCanvas
 *
 * Parameters:
 *   id    : the window's id
 *   parent: a pointer to the parent window
 *   owner : a pointer to the owner window
 *
 * Return value: NONE
 *
 * Purpose: constructor for IPalletCanvas
 *
*/

IPalletCanvas::IPalletCanvas(const unsigned long id, IWindow* parent, IWindow* owner, int& pX, int& pY)
  : ICanvas(id,parent,owner,
    IGRect2D((IGPoint2D(0,0)),
              IGPoint2D(PALLETCANVAS_SIZE,PALLETCANVAS_SIZE))),
    win(parent->parent())
{
  // start up the event handlers
  IMouseHandler::handleEventsFor(this);
  IPaintHandler::handleEventsFor(this);

  // do some initial range checking/adjustments
  if(pX > (PALLETCANVAS_SQUARE-1)) pX = (PALLETCANVAS_SQUARE-1);
  if(pX < 0) pX = 0;
  if(pY > (PALLETCANVAS_SQUARE-1)) pY = (PALLETCANVAS_SQUARE-1);
  if(pY < 0) pY = 0;

  // hold on to the referenced indexes
  posX = &pX;
  posY = &pY;

  // initialize
  InitTables();
  paintAllFlag = 1;

  managedPresSpacePtr = new IManagedPresSpaceHandle(this);
}

/*
 * Function: IPalletCanvas::~IPalletCanvas
 *
 * Parameters: NONE
 *
 * Return valu: NONE
 *
 * Purpose: destructor for IPalletCanvas
 *
*/

IPalletCanvas::~IPalletCanvas()
{
  IMouseHandler::stopHandlingEventsFor(this);
  IPaintHandler::stopHandlingEventsFor(this);

  for(int i = 0;i < PALLETCANVAS_SQUARE;i++) {

    for(int j = 0;j< PALLETCANVAS_SQUARE; j++) {

      delete squareTable[i][j];

    }

  }

  delete managedPresSpacePtr;

}

/*
 * Function: IPalletCanvas::color
 *
 * Parameters: NONE
 *
 * Return value: the currently selected color from a global color table
 *
 * Purpose: returns the currently selected color from the color table
 *
*/

IBaseColor IPalletCanvas::color()
{
  return *colorTable[*posX][*posY];

}

/*
 * Function: IPalletCanvas::setColor
 *
 * Parameters: NONE
 *
 * Return value: NONE
 *
 * Purpose: called to update the pallet as the slider indicators are moved
 *
*/

void IPalletCanvas::SetColor()
{
  // create the rendering devices
   IBaseRootGrafPort myDisplayPort(this->presSpace());

  // create the attribute bundle with the appropriate color
  IFillAndFrameBundle bundle(*colorTable[*posX][*posY],IBaseColor(IBaseColor::kBlack));

  // render the affected portion of the pallet to the screen
  myDisplayPort.draw(*squareTable[*posX][*posY],bundle);
}

/*
 * Function: IPalletCanvas::paintWindow
 *
 * Parameters:
 *   event: gives detail on the type of paint event that occured
 *
 * Return value: returns true when painting is handled - always true here
 *
 * Purpose: repaints the pallet when the need arises
 *
*/

bool IPalletCanvas::paintWindow(IPaintEvent& event)
{
  if(paintAllFlag) {  // if painting required...

    // create the rendering devices
    IBaseRootGrafPort myDisplayPort(this->presSpace());

    // draw the table
   for(int i = 0; i < PALLETCANVAS_SQUARE; i++) {  

      for(int j = 0; j < PALLETCANVAS_SQUARE; j++) {

        IFillAndFrameBundle bundle(*colorTable[i][j],IBaseColor(IBaseColor::kBlack));
        myDisplayPort.draw(*squareTable[i][j],bundle);

      }

    }

  }

  paintAllFlag = 1;
  return true;

}

/*
 * Function: IPalletCanvas::mouseClicked
 *
 * Parameters:
 *   event: gives detail on what type of mouse click occurred
 *
 * Return value: returns true when the event is processed
 *
 * Purpose: used to change the currently selected color from the table
 *
*/

bool IPalletCanvas::mouseClicked(IMouseClickEvent& event)
{
  bool result = false;     // the return result

  if ( event.mouseButton() == IMouseClickEvent::button1 &&
       event.mouseAction() == IMouseClickEvent::down ) {

    // create the rendering devices
    IBaseRootGrafPort myDisplayPort(this->presSpace());

    // get the mouse position in world space
    IGPoint2D talPoint;
    IPoint point(event.mousePosition());
    talPoint = IGPoint2D(point);

    // calculate the table entry clicked on
    *posX = ((int)(talPoint.fX))/PALLETCANVAS_SQUAREWIDTH;
    *posY = ((int)(talPoint.fY))/PALLETCANVAS_SQUAREWIDTH;

    // do some range checking/adjustments
    if(*posX > (PALLETCANVAS_SQUARE-1)) *posX = (PALLETCANVAS_SQUARE-1);
    if(*posY > (PALLETCANVAS_SQUARE-1)) *posY = (PALLETCANVAS_SQUARE-1);

    // update the values for the dialog and do necessary painting; rgb and equivalent greyscale
    ((IPalletDialog*)win)->SetValues(colorTable[*posX][*posY]->redMix(),colorTable[*posX][*posY]->greenMix(),colorTable[*posX][*posY]->blueMix(),
                                     0.3*(colorTable[*posX][*posY]->redMix())+0.59*(colorTable[*posX][*posY]->greenMix())+0.11*(colorTable[*posX][*posY]->blueMix()));
    ((IPalletDialog*)win)->SetColor(*colorTable[*posX][*posY]);

    result = true;

    paintAllFlag = 0;

  }

  return result;

}

/*
 * Function: IPalletCanvas::InitTables
 *
 * Parameters: NONE
 *
 * Return value: NONE
 *
 * Purpose: initailizes the square table consisting of 64 rectangles
 *
*/

void IPalletCanvas::InitTables()
{
  IBaseRootGrafPort myDisplayPort(this->presSpace());
  for(int i = 0; i < PALLETCANVAS_SQUARE; i++) {

    for(int j = 0; j < PALLETCANVAS_SQUARE; j++) {

      IGPoint2D p1 = myDisplayPort.pixelToPointSize().transformPoint(IGPoint2D( 0+i*PALLETCANVAS_SQUAREWIDTH, 0+j*PALLETCANVAS_SQUAREWIDTH));
      IGPoint2D p2 = myDisplayPort.pixelToPointSize().transformPoint(IGPoint2D(PALLETCANVAS_SQUAREWIDTH+i*PALLETCANVAS_SQUAREWIDTH,
                               PALLETCANVAS_SQUAREWIDTH+j*PALLETCANVAS_SQUAREWIDTH));
      squareTable[i][j] = new IGRect2D(p1,p2);

    }

  }

}

//*************************************************************************
// Class IControlCanvas: method definitions                               *
//*************************************************************************

/*
 * Function: IControlCanvas::command
 *
 * Parameters:
 *   event: contains the id of the command event
 *
 * Return value: returns true if the command event if handled
 *
 * Purpose: used for dismissal of the dialog
 *
*/

bool IControlCanvas::command(ICommandEvent& event)
{
  bool result = false;

  switch(event.commandId()) {

    case ID_OK: {  // Ok button pressed

       ((IFrameWindow*)parent())->dismiss(ID_OK);
      result = true;
      break;
    }

   default:
    case ID_CANCEL: {  // Cancel button pressed

      ((IFrameWindow*)parent())->dismiss(0);
      result = true;
      break;
    }

  }

  return result;

}

//*************************************************************************
// Class IPalletDialog: method definitions                                *
//*************************************************************************

/*
 * Function: IPalletDialog::IPalletDialog
 *
 * Parameters:
 *   title: the windows title
 *   pX   : the horizontal index of the initial color to be selected
 *   pY   : the vertical index of the initial color to be selected
 *
 * Return value: NONE
 *
 * Purpose: constructor for IPalletCanvas
 *
*/

IPalletDialog::IPalletDialog(const char* title, int& pX, int &pY, IWindow * ownerWnd)
  : IFrameWindow(IResourceId(WND_PALLET),
                  IWindow::desktopWindow(),
                  ownerWnd,
      IRectangle(),
      IFrameWindow::classDefaultStyle &
      ~IFrameWindow::minimizeButton &
      ~IFrameWindow::maximizeButton &
      ~IFrameWindow::sizingBorder |
      IFrameWindow::titleBar |
      IFrameWindow::dialogBackground |
      IFrameWindow::dialogBorder),
    controlCanvas(0x8008,this,this),
    palletCanvas(0x8007,&controlCanvas,&controlCanvas,pX,pY),
    colorSquare(0x8006,&controlCanvas,&controlCanvas),
    OkBut(ID_OK,&controlCanvas,&controlCanvas),
    CancelBut(ID_CANCEL,&controlCanvas,&controlCanvas),
    rSelector(0x8005,&controlCanvas,this,IColorSelector::Red_type,true),
    gSelector(0x8004,&controlCanvas,this,IColorSelector::Green_type,true),
    bSelector(0x8003,&controlCanvas,this,IColorSelector::Blue_type,true),
    grSelector(0x8002,&controlCanvas,this,IColorSelector::Gray_type,false),
    grayColor(false),
    dialogTitle(this)
{
  setClient(&controlCanvas);

  OkBut.setText("OK");
  CancelBut.setText("Cancel");
  dialogTitle.setText(title);

  controlCanvas.setLayoutDistorted(IWindow::immediateUpdate,0);

  // size the controls (in world space)
  controlCanvas.sizeTo(ISize(IPoint(IGPoint2D(300,270))));
  sizeTo(ISize(IPoint(IGPoint2D(300,270))));
  OkBut.sizeTo(ISize(IPoint(IGPoint2D(45,40))));
  CancelBut.sizeTo(ISize(IPoint(IGPoint2D(75,40))));

  // position the controls (in world space)
  OkBut.moveTo(IPoint(IGPoint2D(32,200)));
  CancelBut.moveTo(IPoint(IGPoint2D(82,200)));
  palletCanvas.moveTo(IPoint(IGPoint2D(PALLETDIALOG_SPACER,PALLETDIALOG_SPACER)));
  rSelector.moveTo(IPoint(IGPoint2D(PALLETCANVAS_SIZE+2*PALLETDIALOG_SPACER,
                                    COLORSQUARE_WIDTH+2*PALLETDIALOG_SPACER)));
  gSelector.moveTo(IPoint(IGPoint2D(PALLETCANVAS_SIZE+2*PALLETDIALOG_SPACER,
                                    COLORSQUARE_WIDTH+3*PALLETDIALOG_SPACER+COLORSELECTOR_HEIGHT)));
  bSelector.moveTo(IPoint(IGPoint2D(PALLETCANVAS_SIZE+2*PALLETDIALOG_SPACER,
                                    COLORSQUARE_WIDTH+4*PALLETDIALOG_SPACER+2*COLORSELECTOR_HEIGHT)));
  grSelector.moveTo(IPoint(IGPoint2D(PALLETCANVAS_SIZE+3*PALLETDIALOG_SPACER+COLORSELECTOR_WIDTH,
                                     COLORSQUARE_WIDTH+2*PALLETDIALOG_SPACER)));

  // set the initial values
  fColor = IBaseColor(*colorTable[pX][pY]);
  SetValues(colorTable[pX][pY]->redMix(),
            colorTable[pX][pY]->greenMix(),
            colorTable[pX][pY]->blueMix(),0);

  // draw!
  refresh();
  setFocus();

}

/*
 * Function: IPalletDialog::~IPalletDialog
 *
 * Parameters: NONE
 *
 * Return value: NONE
 *
 * Purpose: destructor for IPalletDialog
 *
*/

IPalletDialog::~IPalletDialog()
{

}

/*
 * Function: IPalletDialog::color
 *
 * Parameters: NONE
 *
 * Return value: the paint constructed from the currently selected color
 *
 * Purpose: returns the paint constructed from the currently selected color
 *
*/

IBaseColor IPalletDialog::color()
{

  return fColor;

}

/*
 * Function: IPalletDialog::SetValues
 *
 * Parameters:
 *   rV : the red value to be set
 *   gV : the green value to be set
 *   bV : the blue value to be set
 *   grV: the gray value to be set
 *
 * Return value: NONE
 *
 * Purpose: updates the dialog to reflect the indicated values
 *
*/

void IPalletDialog::SetValues(CharIntensity rV, CharIntensity gV, CharIntensity bV, CharIntensity grV)
{
  char value[5];

  // set the selector values
  rSelector.SetValue(rV);
  gSelector.SetValue(gV);
  bSelector.SetValue(bV);
  grSelector.SetValue(grV);

  // set the values for the dialog
  rVal = rV;
  gVal = gV;
  bVal = bV;
  grVal = grV;

  // construct the paint from the appropriate color type
  if(grayColor) fColor = IBaseColor(grVal);

  else fColor = IBaseColor(rVal,gVal,bVal);

  // do the necessary painting, and do it now!
  colorSquare.refresh(IWindow::paintAllImmediate);

}

/*
 * Function: IPalletDialog::SetValue
 *
 * Parameters:
 *   val: the value to be set
 *   t  : the type of value being set (Red_type, Green_type, Blue_type, Gray_type)
 *
 * Return value: NONE
 *
 * Purpose: set the value of the specifed type ( t )
 *
*/

void IPalletDialog::SetValue(CharIntensity val, IColorSelector::ColorType t)
{
  int pX, pY;
  char value[5];

  // set the value with respect to the type
  switch(t) {

    case IColorSelector::Red_type: {

      rVal = val;
      break;

    }

    case IColorSelector::Green_type: {

      gVal = val;
      break;

    }

    case IColorSelector::Blue_type: {

      bVal = val;
      break;

    }

    case IColorSelector::Gray_type: {

      grVal = val;
      if(!grayColor) {

        grayColor = true;

      }

      SetValues(grVal,grVal,grVal,grVal);

      // set the paint
      fColor = IBaseColor(grVal);
      colorSquare.refresh(IWindow::paintAllImmediate);

      return;

    }

  }

  if(grayColor) {  // if the gray color has changed...

    grayColor = false;
    SetValues(rVal,gVal,bVal,0);     // update all indicators

  }

  // set the paint
  fColor = IBaseColor(rVal,gVal,bVal);

  // update the indices
  pX = palletCanvas.GetPosX();
  pY = palletCanvas.GetPosY();

  // reflect the change int the color table
  delete colorTable[pX][pY];
  colorTable[pX][pY] = new IBaseColor(rVal,gVal,bVal);

  // reflect the change in the palletCanvas
  palletCanvas.SetColor();

  // reflect the change in the colorSquare
  colorSquare.refresh(IWindow::paintAllImmediate);

}

/*
 * Function: IPalletDialog::setColor
 *
 * Parameters:
 *   color: the new color (in paint form) to be set
 *
 * Return value: NONE
 *
 * Purpose: to set the currently selected color (in paint form)
 *
*/

void IPalletDialog::SetColor(IBaseColor color)
{
  fColor = color;

}

//*************************************************************************
// Class ITextDialog: method definitions                                  *
//*************************************************************************

/*
 * Function: ITextDialog::ITextDialog
 *
 * Parameters:
 *   title: the window's title
 *
 * Return value: none
 *
 * Purpose: constructor for ITextDialog
 *
*/

ITextDialog::ITextDialog(const char* title, IWindow * ownerWnd)
  : IFrameWindow(IResourceId(WND_TEXT),
                  IWindow::desktopWindow(),
                  ownerWnd,
      IRectangle(),
      IFrameWindow::classDefaultStyle &
      ~IFrameWindow::minimizeButton &
      ~IFrameWindow::maximizeButton &
      ~IFrameWindow::sizingBorder |
      IFrameWindow::titleBar |
      IFrameWindow::dialogBackground |
      IFrameWindow::dialogBorder),
    controlCanvas(0x8008,this,this),
    entryField(0x8009,&controlCanvas,&controlCanvas),
    OkBut(ID_OK,&controlCanvas,&controlCanvas),
    dialogTitle(this)
{
  // start the event handler
  handleEventsFor(this);

  setClient(&controlCanvas);

  // initialize the text controls
  OkBut.setText("Ok");
  dialogTitle.setText(title);

  sizeTo(ISize(360,120));

  // position the entry field
  controlCanvas.addToCell(&entryField,2,2,6,2);

  // position/size/set the Ok button
  OkBut.sizeTo(ISize(45,40));
  OkBut.moveTo(IPoint(155,50));
  OkBut.enableDefault();

  entryField.setFocus();

}

/*
 * Function: ITextDialog::command
 *
 * Parameters:
 *   event: contains the command event id
 *
 * Return value: returns true
 *
 * Purpose: used to dismiss the dialog
 *
*/

bool ITextDialog::command(ICommandEvent& event)
{
   bool result = false;
 
   switch(event.commandId()) {
 
     case ID_OK: {  // Ok button pressed

    dismiss(ID_OK);
       result = true;
       break;
     }
     default: {

       dismiss(0);
       result = true;
       break;
  }

   }

   return result;

}

//*************************************************************************
// Class DrawingArea: method definitions                                  *
//*************************************************************************

/*
 * Function: DrawingArea::DrawingArea
 *
 * Parameters:
 *   windowId: the window's id
 *   parent  : a pointer to the window's parent
 *   owner   : a pointer to the window's owner
 *   initial : the window's intial sizing rectangle
 *
 * Return value: NONE
 *
 * Purpose: constructor for DrawingArea
 *
*/

DrawingArea::DrawingArea( unsigned long windowId, IWindow* parent,
                          IWindow* owner, const IRectangle& initial )
  : dState( notDrawing ),
    currentObj( attribStyle ),
    clipping(false),
    drawingBundle(IBaseColor(IBaseColor::kBlack), IAttributeState::kFrame),
    currentBundle(IBaseColor(IBaseColor::kGreen),IBaseColor(IBaseColor::kBlue), IAttributeState::kFillAndFrame)
    , myDisplayPort(0)
    , paintedLastResize(false)
{

  ICanvas::initialize( windowId, parent, owner, initial, 
        ICanvas::convertToGUIStyle(ICanvas::defaultStyle()), 0);
  // start up the event handlers
  IMouseHandler::handleEventsFor(this);
  IPaintHandler::handleEventsFor(this);
  IResizeHandler::handleEventsFor(this);

#ifndef IC_MOTIF
  // Load the mouse pointers
  IResourceLibrary reslib;

  for(unsigned long i = 0; i < kNumberOfPointers; i++) {

    ptrArray[i] = reslib.loadPointer( i+POINTER_OFFSET );

  }
#endif

  moveGraphic = NULL;
  parentPort = NULL;
  clickCount = 0;

  fGraphicGroup = new IGraphicGroup();

  clickCount = 0;

}

/*
 * Function: DrawingArea::~DrawingArea
 *
 * Parameters: NONE
 *
 * Return value: NONE
 *
 * Purpose: destructor for DrawingArea
 *
*/

DrawingArea::~DrawingArea( )
{

  // shut down the event handlers
  IMouseHandler::stopHandlingEventsFor(this);
  IPaintHandler::stopHandlingEventsFor(this);

  // clean up the pointers
  if(fGraphicGroup) delete fGraphicGroup;
  if(currentGraphic) delete currentGraphic;
  if(myDisplayPort) delete myDisplayPort;

}

/*
 * Function: DrawingArea::SetInfoText
 *
 * Parameters:
 *   text: the text to be displayed in the information area
 *
 * Return value: NONE
 *
 * Purpose: calls MainWindow to set the text in the information area
 *
*/

void DrawingArea::SetInfoText(IString text)
{
  ((MainWindow*)parent())->SetInfoText(text);

}

/*
 * Function: DrawingArea::SetInfoText
 *
 * Parameters:
 *   id: the resource id of the text to be displayed in the information area
 *
 * Return value: NONE
 *
 * Purpose: calls MainWindow to set the text in the information area
 *
*/

void DrawingArea::SetInfoText(unsigned long id)
{
  ((MainWindow*)parent())->SetInfoText(id);

}

//*************************************************************************
// Class MainWindow: method definitions                                   *
//*************************************************************************

/*
 * Function: MainWindow::MainWindow
 *
 * Parameters:
 *   windowId: the window's id
 *
 * Return value: NONE
 *
 * Purpose: constructor for MainWindow
 *
*/

MainWindow::MainWindow(unsigned long windowId)
  : IFrameWindow (                      //Call IFrameWindow constructor
    IFrameWindow::defaultStyle()        //  Use default plus
    | IFrameWindow::animated,           //  Set to show with "animation"
    windowId),                          //  Main Window ID
    drawingArea( WND_DRAW, this, this ),
    toolBar1( WND_TOOLBAR1,this, IToolBar::aboveClient),
    menuBar( WND_MAIN, this),
    infoText( WND_TEXT, this, this, IRectangle(), IStaticText::defaultStyle()
                                                | IStaticText::top
                                                | IStaticText::left
                                                | IStaticText::wordBreak ),
    lastDrawOperationId(ID_FILLANDFRAME),
    lastPenWidthId(ID_PENWIDTH_1),
    lastPenTypeId(ID_PENTYPE_SOLID)
{
   ICoordinateSystem::setApplicationOrientation(ICoordinateSystem::originUpperLeft);

  // start up the event handlers
  ICommandHandler::handleEventsFor(this);
  IResizeHandler::handleEventsFor(this);

  setClient(&drawingArea);


  // Flow Toolbar
  toolBar1.alignDecksByGroup();

  // initialize the tool bar button array
  for(unsigned long i = 0; i < kNumberOfButtons; i++) {

        try {
    buttonArray[i] = new IToolBarButton(i+BUTTON_OFFSET, &toolBar1, &toolBar1);
    buttonArray[i]->setStandardBitmapSize(ISize(22,19)); // used as an offset here
    buttonArray[i]->setBitmap( i+BUTTON_OFFSET );
    toolBar1.addAsLast(buttonArray[i]);
        }
        catch (IException& e)
        {
                cout << "Caught Exception: " << e.name() << ": " << e.text() << endl;
                buttonArray[i] = new IToolBarButton(i+BUTTON_OFFSET, &toolBar1, &toolBar1);
                buttonArray[i]->setStandardBitmapSize(ISize(22,19));
                buttonArray[i]->setBitmap(i+BUTTON_OFFSET);
                toolBar1.addAsLast(buttonArray[i]);
        }

  }

  groupButtIndex = kNumberOfButtons;
  buttonArray[0]->latch();
  lastButton = buttonArray[0];

  // setup the information area
  addExtension( &infoText,
    IFrameWindow::belowClient,
    (unsigned long)(2 * 24),
    IFrameWindow::thickLine );

  // check the default menu selections
  menuBar.checkItem(lastDrawOperationId);
  menuBar.checkItem(lastPenWidthId);
  menuBar.checkItem(lastPenTypeId);
  menuBar.checkItem(ID_SC_FRAME_TMODE);
  menuBar.checkItem(ID_SC_FILL_TMODE);
  menuBar.checkItem(ID_PATTERN_SOLID);
  menuBar.checkItem(ID_FPATTERN_SOLID);

  setFocus();
  maximize();
  show();

  // initialize the color table indices
  fillX = bframeX = bfillX = 0;         // set default color settings
  frameX = 3;
  frameY = bframeY = bfillY = 7;
  fillY = 4;
  canvasX = 7; canvasY = 0;

  drawingArea.Init();

  refresh();

  // allocate the color table
  InitPallet();
  
}

/*
 * Function: MainWindow::~MainWindow
 *
 * Parameters: NONE
 *
 * Return value: NONE
 *
 * Purpose: destructor for MainWindow
 *
*/

MainWindow::~MainWindow()
{

  // delete the button array
  for(unsigned long i = 0; i < kNumberOfButtons; i++) {

    delete buttonArray[i];

  }

  // delete the color table
  ClearPallet();

}

/*
 * Function: MainWindow::SetInfoText
 *
 * Parameters:
 *   text: the text to be displayed in the information area
 *
 * Return value: NONE
 *
 * Purpose: sets the text in the information area
 *
*/

void MainWindow::SetInfoText(IString text)
{
  infoText.setText(text);

}

/*
 * Function: MainWindow::SetInfoText
 *
 * Parameters:
 *   id: the resource id of the text to be displayed in the information area
 *
 * Return value: NONE
 *
 * Purpose: sets the text in the information area
 *
*/

void MainWindow::SetInfoText(unsigned long id)
{
  infoText.setText(id);

}

/*
 * Function: MainWindow::InitPallet
 *
 * Parameters: NONE
 *
 * Return value: NONE
 *
 * Purpose: initializes the global color pallet
 *
*/

void MainWindow::InitPallet()
{
  // set up the table - no pattern here!
  IBaseColor table[8][8] = {
    {IBaseColor(170,255,0), IBaseColor(128,128,0),
    IBaseColor(170,85,0),IBaseColor(128,0,0),IBaseColor(0,255,0),
    IBaseColor(0,146,0),IBaseColor(0,85,0),IBaseColor(0,0,0)},

    {IBaseColor(170,1,85),IBaseColor(170,170,85),
    IBaseColor(170,85,85),IBaseColor(170,0,85),
    IBaseColor(0,255,85),IBaseColor(0,170,85),IBaseColor(0,85,85),
    IBaseColor(0,0,85)},

    {IBaseColor(170,1,170),
    IBaseColor(204,204,204),IBaseColor(170,85,170),
    IBaseColor(128,128,128),IBaseColor(0,255,170),
    IBaseColor(0,146,170),IBaseColor(0,85,170),
    IBaseColor(0,0,170)},

    {IBaseColor(170,255,255),
    IBaseColor(170,170,255),IBaseColor(170,85,255),
    IBaseColor(170,0,255),IBaseColor(0,255,255),
    IBaseColor(0,170,255),IBaseColor(0,85,255),
    IBaseColor(0,0,255)},

    {IBaseColor(255,255,0),
    IBaseColor(255,170,0),IBaseColor(255,85,0),
    IBaseColor(255,0,0),IBaseColor(85,255,0),
    IBaseColor(85,170,0),IBaseColor(85,85,0),
    IBaseColor(85,0,0)},

    {IBaseColor(255,255,85),
    IBaseColor(255,170,85),IBaseColor(255,85,85),
    IBaseColor(255,0,85),IBaseColor(85,255,85),
    IBaseColor(85,170,85),IBaseColor(131,131,131),
    IBaseColor(85,0,85)},

    {IBaseColor(255,255,170),
    IBaseColor(255,170,170),IBaseColor(255,85,170),
    IBaseColor(255,0,170),IBaseColor(85,255,170),
    IBaseColor(85,170,170),IBaseColor(85,85,170),
    IBaseColor(85,0,170)},

    {IBaseColor(255,255,255),
    IBaseColor(255,170,255),IBaseColor(255,85,255),
    IBaseColor(255,0,255),IBaseColor(85,255,255),
    IBaseColor(85,170,255),IBaseColor(85,85,255),
    IBaseColor(85,0,255)}
  };

  // initialize the global table
  for(int i = 0; i < PALLETCANVAS_SQUARE; i++) {

    for(int j = 0; j < PALLETCANVAS_SQUARE; j++) {

      colorTable[i][j] = new IBaseColor(table[i][j]);

    }

  }

}

/*
 * Function: MainWindow::ClearPallet
 *
 * Parameters: NONE
 *
 * Return value: NONE
 *
 * Purpose: clears the global color pallet
 *
*/

void MainWindow::ClearPallet()
{
  for(int i = 0; i < PALLETCANVAS_SQUARE; i++) {

    for(int j = 0; j < PALLETCANVAS_SQUARE; j++) {

      delete colorTable[i][j];

    }

  }

}

/*
 * Function: MainWindow::command
 *
 * Parameters:
 *   event: contains the command id of the event to be handled
 *
 * Return value: returns true when the event is processed
 *
 * Purpose: handles selections from the menu bar, tool bar, and pop-up menus
 *
*/

bool MainWindow::command( ICommandEvent& event )
{
  bool fProcessed = false;

  char title[20];

  switch (event.commandId()) {

    // handle the toolbar events
    case PALLET_NORM: {

      currentPointer = POINTER_NONE;

      if(lastButton != buttonArray[PALLET_NORM - BUTTON_OFFSET]) lastButton->unlatch();

      lastButton = buttonArray[PALLET_NORM - BUTTON_OFFSET];

      drawingArea.SetDrawObject((DrawingArea::DrawObject)event.commandId());
      SetInfoText(event.commandId()+LONG_OFFSET);

      fProcessed = true;
      break;

    }

    case PALLET_LINE: {

      currentPointer = POINTER_LINE;

      if(lastButton != buttonArray[PALLET_LINE - BUTTON_OFFSET]) lastButton->unlatch();

      lastButton = buttonArray[PALLET_LINE - BUTTON_OFFSET];

      drawingArea.SetDrawObject((DrawingArea::DrawObject)event.commandId());
      SetInfoText(event.commandId()+LONG_OFFSET);

      fProcessed = true;
      break;

    }

    case PALLET_DRAW: {

      currentPointer = POINTER_DRAW;

      if(lastButton != buttonArray[PALLET_DRAW - BUTTON_OFFSET]) lastButton->unlatch();

      lastButton=  buttonArray[PALLET_DRAW - BUTTON_OFFSET];

      drawingArea.SetDrawObject((DrawingArea::DrawObject)event.commandId());
      SetInfoText(event.commandId()+LONG_OFFSET);

      fProcessed = true;
      break;

    }

    case PALLET_RECTANGLE: {

      currentPointer = POINTER_RECTANGLE;

      if(lastButton != buttonArray[PALLET_RECTANGLE - BUTTON_OFFSET]) lastButton->unlatch();

      lastButton = buttonArray[PALLET_RECTANGLE - BUTTON_OFFSET];

      drawingArea.SetDrawObject((DrawingArea::DrawObject)event.commandId());
      SetInfoText(event.commandId()+LONG_OFFSET);

      fProcessed = true;
      break;

    }

    case PALLET_ELLIPSE: {

      currentPointer = POINTER_ELLIPSE;

      if(lastButton != buttonArray[PALLET_ELLIPSE - BUTTON_OFFSET]) lastButton->unlatch();

      lastButton = buttonArray[PALLET_ELLIPSE - BUTTON_OFFSET];

      drawingArea.SetDrawObject((DrawingArea::DrawObject)event.commandId());
      SetInfoText(event.commandId()+LONG_OFFSET);

      fProcessed = true;
      break;

    }

    case PALLET_POLYLINE: {

      currentPointer = POINTER_POLYLINE;

      if(lastButton != buttonArray[PALLET_POLYLINE - BUTTON_OFFSET]) lastButton->unlatch();

      lastButton = buttonArray[PALLET_POLYLINE - BUTTON_OFFSET];

      drawingArea.SetDrawObject((DrawingArea::DrawObject)event.commandId());
      SetInfoText(event.commandId()+LONG_OFFSET);

      fProcessed = true;
      break;

    }

    case PALLET_POLYGON: {

      currentPointer = POINTER_POLYGON;

      if(lastButton != buttonArray[PALLET_POLYGON - BUTTON_OFFSET]) lastButton->unlatch();

      lastButton = buttonArray[PALLET_POLYGON - BUTTON_OFFSET];

      drawingArea.SetDrawObject((DrawingArea::DrawObject)event.commandId());
      SetInfoText(event.commandId()+LONG_OFFSET);

      fProcessed = true;
      break;

    }

    case PALLET_CURVE: {

      currentPointer = POINTER_NONE;

      buttonArray[PALLET_CURVE - BUTTON_OFFSET]->unlatch();
      lastButton->latch();

      IPopUpMenu *curvePopUp = new IPopUpMenu(this,ID_POPUP_MENU);
      curvePopUp->addText(PALLET_ARC, "3 Point Arc");
      curvePopUp->addText(PALLET_CBEZIER, "Bezier Curve");
      curvePopUp->addText(PALLET_ACURVE, "Abstract Curve");
#ifndef IC_MOTIF
      (*curvePopUp).show(buttonArray[PALLET_CURVE - BUTTON_OFFSET]->position());
#else
      (*curvePopUp).show(IPoint(0,0));
#endif
      (*curvePopUp).setAutoDeleteObject();

      fProcessed = true;
      break;

    }

    case PALLET_LOOP: {

      currentPointer = POINTER_NONE;

      buttonArray[PALLET_LOOP - BUTTON_OFFSET]->unlatch();
      lastButton->latch();

      IPopUpMenu *loopPopUp = new IPopUpMenu(this,ID_POPUP_MENU);
      loopPopUp->addText(PALLET_CHORD, "Chord");
      loopPopUp->addText(PALLET_PIE, "Pie");
      loopPopUp->addText(PALLET_LBEZIER, "Bezier Loop");
      loopPopUp->addText(PALLET_ALOOP, "Abstract Loop");
#ifndef IC_MOTIF
      (*loopPopUp).show(buttonArray[PALLET_LOOP - BUTTON_OFFSET]->position());
#else
      (*loopPopUp).show(IPoint(0,0));
#endif
      (*loopPopUp).setAutoDeleteObject();

      fProcessed = true;
      break;

    }

    case PALLET_AREA: {

      currentPointer = POINTER_NONE;

      buttonArray[PALLET_AREA - BUTTON_OFFSET]->unlatch();
      lastButton->latch();

      IPopUpMenu *areaPopUp = new IPopUpMenu(this,ID_POPUP_MENU);
      areaPopUp->addText(PALLET_ADD, "Add");
      areaPopUp->addText(PALLET_SUBTRACT, "Subtract");
      areaPopUp->addText(PALLET_MULTIPLY, "Intersect");
      areaPopUp->addText(PALLET_XOR, "Exclusive Or");
#ifndef IC_MOTIF
      (*areaPopUp).show(buttonArray[PALLET_AREA - BUTTON_OFFSET]->position());
#else
      (*areaPopUp).show(IPoint(0,0));
#endif
      (*areaPopUp).setAutoDeleteObject();

      fProcessed = true;
      break;

    }

    case PALLET_TEXT: {

      currentPointer = POINTER_TEXT;

      if(lastButton != buttonArray[PALLET_TEXT - BUTTON_OFFSET]) lastButton->unlatch();

      lastButton = buttonArray[PALLET_TEXT - BUTTON_OFFSET];

      drawingArea.SetDrawObject((DrawingArea::DrawObject)event.commandId());
      SetInfoText(event.commandId()+LONG_OFFSET);

      ITextDialog textDialog("Set Graphic Text", this);

      // bring up the dialog and get the text when the user has finished
      textDialog.showModally();
      if (textDialog.result() == ID_OK)
        drawingArea.SetGraphicText(IText(textDialog.getText()));
      else
        drawingArea.SetGraphicText(IText(""));

      fProcessed = true;
      break;

    }

    case PALLET_BITMAP: {

      currentPointer = POINTER_BITMAP;

      if(lastButton != buttonArray[PALLET_BITMAP - BUTTON_OFFSET]) lastButton->unlatch();

      lastButton = buttonArray[PALLET_BITMAP - BUTTON_OFFSET];

      drawingArea.SetDrawObject((DrawingArea::DrawObject)event.commandId());

      fProcessed = true;
      break;

    }


    case PALLET_ROTATE: {

      currentPointer = POINTER_ROTATE;

      if(lastButton != buttonArray[PALLET_ROTATE - BUTTON_OFFSET]) lastButton->unlatch();

      lastButton = buttonArray[PALLET_ROTATE - BUTTON_OFFSET];

      drawingArea.SetDrawObject((DrawingArea::DrawObject)event.commandId());
      SetInfoText(event.commandId()+LONG_OFFSET);

      fProcessed = true;
      break;

    }

    case PALLET_SCALE: {

      currentPointer = POINTER_SCALE;

      if(lastButton != buttonArray[PALLET_SCALE - BUTTON_OFFSET]) lastButton->unlatch();

      lastButton = buttonArray[PALLET_SCALE - BUTTON_OFFSET];

      drawingArea.SetDrawObject((DrawingArea::DrawObject)event.commandId());
      SetInfoText(event.commandId()+LONG_OFFSET);

      fProcessed = true;
      break;
    }

    case PALLET_CLIP: {

      currentPointer = POINTER_CLIP;

      if(lastButton != buttonArray[PALLET_CLIP - BUTTON_OFFSET]) lastButton->unlatch();

      lastButton = buttonArray[PALLET_CLIP - BUTTON_OFFSET];

      drawingArea.SetDrawObject((DrawingArea::DrawObject)event.commandId());
      SetInfoText(event.commandId()+LONG_OFFSET);

      fProcessed = true;
      break;

    }

    case PALLET_STYLE: {

      currentPointer = POINTER_NONE;

      if(lastButton != buttonArray[PALLET_STYLE - BUTTON_OFFSET]) lastButton->unlatch();

      lastButton = buttonArray[PALLET_STYLE - BUTTON_OFFSET];

      drawingArea.SetDrawObject((DrawingArea::DrawObject)event.commandId());
      SetInfoText(event.commandId()+LONG_OFFSET);

      fProcessed = true;
      break;

    }

    // handle the curve popup menu selections
    case PALLET_ARC: {

      currentPointer = POINTER_ARC;

      if(lastButton != buttonArray[PALLET_CURVE - BUTTON_OFFSET]) lastButton->unlatch();

      lastButton = buttonArray[PALLET_CURVE - BUTTON_OFFSET];
      lastButton->latch();

      drawingArea.SetDrawObject((DrawingArea::DrawObject)event.commandId());
      SetInfoText(event.commandId()+LONG_OFFSET);

      fProcessed = true;
      break;

    }

    case PALLET_CBEZIER: {

      currentPointer = POINTER_NONE;

      if(lastButton != buttonArray[PALLET_CURVE - BUTTON_OFFSET]) lastButton->unlatch();

      lastButton = buttonArray[PALLET_CURVE - BUTTON_OFFSET];
      lastButton->latch();

      drawingArea.SetDrawObject((DrawingArea::DrawObject)event.commandId());
      SetInfoText(event.commandId()+LONG_OFFSET);

      fProcessed = true;
      break;

    }

    case PALLET_ACURVE: {

      currentPointer = POINTER_NONE;

      if(lastButton != buttonArray[PALLET_CURVE - BUTTON_OFFSET]) lastButton->unlatch();

      lastButton = buttonArray[PALLET_CURVE - BUTTON_OFFSET];
      lastButton->latch();

      drawingArea.SetDrawObject((DrawingArea::DrawObject)event.commandId());
      SetInfoText(event.commandId()+LONG_OFFSET);

      fProcessed = true;
      break;

    }

    // handle the loop popup menu selections
    case PALLET_ALOOP: {

      currentPointer = POINTER_NONE;

      if(lastButton != buttonArray[PALLET_LOOP - BUTTON_OFFSET]) lastButton->unlatch();

      lastButton = buttonArray[PALLET_LOOP - BUTTON_OFFSET];
      lastButton->latch();

      drawingArea.SetDrawObject((DrawingArea::DrawObject)event.commandId());
      SetInfoText(event.commandId()+LONG_OFFSET);

      fProcessed = true;
      break;

    }

    case PALLET_LBEZIER: {

      currentPointer = POINTER_NONE;

      if(lastButton != buttonArray[PALLET_LOOP - BUTTON_OFFSET]) lastButton->unlatch();

      lastButton = buttonArray[PALLET_LOOP - BUTTON_OFFSET];
      lastButton->latch();

      drawingArea.SetDrawObject((DrawingArea::DrawObject)event.commandId());
      SetInfoText(event.commandId()+LONG_OFFSET);

      fProcessed = true;
      break;

    }

    case PALLET_CHORD: {

      currentPointer = POINTER_CHORD;

      if(lastButton != buttonArray[PALLET_LOOP - BUTTON_OFFSET]) lastButton->unlatch();

      lastButton = buttonArray[PALLET_LOOP - BUTTON_OFFSET];
      lastButton->latch();

      drawingArea.SetDrawObject((DrawingArea::DrawObject)event.commandId());
      SetInfoText(event.commandId()+LONG_OFFSET);

      fProcessed = true;
      break;

    }

    case PALLET_PIE: {

      currentPointer = POINTER_PIE;

      if(lastButton != buttonArray[PALLET_LOOP - BUTTON_OFFSET]) lastButton->unlatch();

      lastButton = buttonArray[PALLET_LOOP - BUTTON_OFFSET];
      lastButton->latch();

      drawingArea.SetDrawObject((DrawingArea::DrawObject)event.commandId());
      SetInfoText(event.commandId()+LONG_OFFSET);

      fProcessed = true;
      break;

    }

    // handle the area popup menu selections
    case PALLET_ADD: {

      currentPointer = POINTER_NONE;

      if(lastButton != buttonArray[PALLET_AREA - BUTTON_OFFSET]) lastButton->unlatch();

      lastButton = buttonArray[PALLET_AREA - BUTTON_OFFSET];
      lastButton->latch();

      drawingArea.SetDrawObject((DrawingArea::DrawObject)event.commandId());
      SetInfoText(event.commandId()+LONG_OFFSET);

      fProcessed = true;
      break;

    }

    case PALLET_SUBTRACT: {

      currentPointer = POINTER_NONE;

      if(lastButton != buttonArray[PALLET_AREA - BUTTON_OFFSET]) lastButton->unlatch();

      lastButton = buttonArray[PALLET_AREA - BUTTON_OFFSET];
      lastButton->latch();

      drawingArea.SetDrawObject((DrawingArea::DrawObject)event.commandId());
      SetInfoText(event.commandId()+LONG_OFFSET);

      fProcessed = true;
      break;

    }

    case PALLET_MULTIPLY: {

      currentPointer = POINTER_NONE;

      if(lastButton != buttonArray[PALLET_AREA - BUTTON_OFFSET]) lastButton->unlatch();

      lastButton = buttonArray[PALLET_AREA - BUTTON_OFFSET];
      lastButton->latch();

      drawingArea.SetDrawObject((DrawingArea::DrawObject)event.commandId());
      SetInfoText(event.commandId()+LONG_OFFSET);

      fProcessed = true;
      break;

    }

    case PALLET_XOR: {

      currentPointer = POINTER_NONE;

      if(lastButton != buttonArray[PALLET_AREA - BUTTON_OFFSET]) lastButton->unlatch();

      lastButton = buttonArray[PALLET_AREA - BUTTON_OFFSET];
      lastButton->latch();

      drawingArea.SetDrawObject((DrawingArea::DrawObject)event.commandId());
      SetInfoText(event.commandId()+LONG_OFFSET);

      fProcessed = true;
      break;

    }

    // handle pen width selections
    case ID_PENWIDTH_1:
    case ID_PENWIDTH_2:
    case ID_PENWIDTH_3:
    case ID_PENWIDTH_4:
    case ID_PENWIDTH_5:
    case ID_PENWIDTH_6:
    case ID_PENWIDTH_7:
    case ID_PENWIDTH_8:
    case ID_PENWIDTH_9:
    case ID_PENWIDTH_10: {

      menuBar.uncheckItem(lastPenWidthId)
               .checkItem(lastPenWidthId = event.commandId());

      drawingArea.SetPenWidth(event.commandId() - ID_CORRECTION);

      fProcessed = true;
      break;

    }

    // handle pen color selection
    case ID_COLORS: {

      IPalletDialog colorDialog("Set Pen Color",frameX,frameY, this);
      colorDialog.showModally();
      if (colorDialog.result() == ID_OK)
        drawingArea.SetPenColor(colorDialog.color());
      fProcessed = true;
      break;

    }

    // handle fill color selection
    case ID_FLCOLORS: {

      IPalletDialog colorDialog("Set Fill Color",fillX,fillY,this);
      colorDialog.showModally();
      if (colorDialog.result() == ID_OK)
        drawingArea.SetFillColor(colorDialog.color());

      fProcessed = true;
      break;

    }

    // handle fill color selection
    case ID_CCOLORS: {

      IPalletDialog colorDialog("Set Canvas Color",canvasX,canvasY,this);

      fProcessed = true;
      break;

    }

    // handle pen style selections
    case ID_PENTYPE_HAIRLINE:
    case ID_PENTYPE_SOLID :
    case ID_PENTYPE_INVISIBLE :
    case ID_PENTYPE_DASHDOT :
    case ID_PENTYPE_SHORTDASH :
    case ID_PENTYPE_DOT :
    case ID_PENTYPE_DASHDOUBLEDOT: {

      menuBar.uncheckItem(lastPenTypeId);
      menuBar.checkItem(lastPenTypeId = event.commandId());

      drawingArea.setPenType(event.commandId());

      fProcessed = true;
      break;

    }

    // handle drawing operation selections
    case ID_FILL: {

      menuBar.uncheckItem(lastDrawOperationId)
             .checkItem(lastDrawOperationId = event.commandId());

      drawingArea.SetDrawingOp(IAttributeState::kFill);

      fProcessed = true;
      break;

    }

    case ID_FRAME: {

      menuBar.uncheckItem(lastDrawOperationId)
             .checkItem(lastDrawOperationId = event.commandId());

      drawingArea.SetDrawingOp(IAttributeState::kFrame);

      fProcessed = true;
      break;

    }

    case ID_FILLANDFRAME: {

      menuBar.uncheckItem(lastDrawOperationId)
             .checkItem(lastDrawOperationId = event.commandId());

      drawingArea.SetDrawingOp(IAttributeState::kFillAndFrame);

      fProcessed = true;
      break;

    }

    // handle clear background selection
    case ID_CLEAR: {

      drawingArea.Clear();

      fProcessed = true;
      break;

    }

    // handle reset color pallete selection
    case ID_RESET: {

      ClearPallet();
      InitPallet();

      fProcessed = true;
      break;

    }

    // handle frame transfer mode selections
    case ID_SC_FRAME_TMODE:
    case ID_IS_FRAME_TMODE:
    case ID_DC_FRAME_TMODE:
    case ID_ID_FRAME_TMODE:
    case ID_SORD_FRAME_TMODE:
    case ID_SANDD_FRAME_TMODE:
    case ID_SXORD_FRAME_TMODE:
    case ID_ISANDD_FRAME_TMODE:
    case ID_ISORD_FRAME_TMODE:
    case ID_SANDID_FRAME_TMODE:
    case ID_SORID_FRAME_TMODE:
    case ID_IRSANDD_FRAME_TMODE:
    case ID_IRSORD_FRAME_TMODE:
    case ID_IRSXORD_FRAME_TMODE:
    case ID_ONE_FRAME_TMODE:
    case ID_ZERO_FRAME_TMODE: {

      menuBar.uncheckItem(frameTransferMode)
             .checkItem(event.commandId());

      drawingArea.SetFrameTransferMode(event.commandId());

      fProcessed = true;
      break;

    }

    // handle fill transfer mode selections
    case ID_SC_FILL_TMODE:
    case ID_IS_FILL_TMODE:
    case ID_DC_FILL_TMODE:
    case ID_ID_FILL_TMODE:
    case ID_SORD_FILL_TMODE:
    case ID_SANDD_FILL_TMODE:
    case ID_SXORD_FILL_TMODE:
    case ID_ISANDD_FILL_TMODE:
    case ID_ISORD_FILL_TMODE:
    case ID_SANDID_FILL_TMODE:
    case ID_SORID_FILL_TMODE:
    case ID_IRSANDD_FILL_TMODE:
    case ID_IRSORD_FILL_TMODE:
    case ID_IRSXORD_FILL_TMODE:
    case ID_ONE_FILL_TMODE:
    case ID_ZERO_FILL_TMODE: {

      menuBar.uncheckItem(fillTransferMode)
             .checkItem(event.commandId());

      drawingArea.SetFillTransferMode(event.commandId());

      fProcessed = true;
      break;

    }

    // handle fill pattern selections
    case ID_PATTERN_SOLID:
    case ID_PATTERN_BDIAGONAL:
    case ID_PATTERN_FDIAGONAL:
    case ID_PATTERN_CROSS:
    case ID_PATTERN_DIAGONALCROSS:
    case ID_PATTERN_HORIZONTAL:
    case ID_PATTERN_VERTICAL:
    case ID_PATTERN_EAGLE:
    case ID_PATTERN_TAJMAHAL: {

      menuBar.uncheckItem(framePattern)
             .checkItem(event.commandId());

      drawingArea.SetFramePattern(event.commandId());
      fProcessed = true;

      break;

    }

    // handle fill pattern selections
    case ID_FPATTERN_SOLID:
    case ID_FPATTERN_BDIAGONAL:
    case ID_FPATTERN_FDIAGONAL:
    case ID_FPATTERN_CROSS:
    case ID_FPATTERN_DIAGONALCROSS:
    case ID_FPATTERN_HORIZONTAL:
    case ID_FPATTERN_VERTICAL:
    case ID_FPATTERN_EAGLE:
    case ID_FPATTERN_TAJMAHAL: {

      menuBar.uncheckItem(fillPattern)
             .checkItem(event.commandId());

      drawingArea.SetFillPattern(event.commandId());

      fProcessed = true;
      break;

    }

    case MI_PREVIEWER:
    case MI_DIALOG:
        {
#ifndef FVT_NOPRINT
                SetInfoText("Handling Print");

                // Create a simple butler (good old Ned) and use a simple page iterator
                IPrintButler butler;
                IStandardPageDescription page(IString("US Letter"), IPageDescription::kUSLetter);
                IGenericClientJobDescription *clientJob = (IGenericClientJobDescription*)
                butler.printJobDescription()->clientJobDescription();
                clientJob->setFileName("c:\\temp\\ptfwin.txt");
                IGraphicGroup *group = drawingArea.GetGraphicGroup();

                try {
                        switch (event.commandId())
                        {
                                case MI_PREVIEWER:
                                        butler.printWithPreview(*this, page, *group);
                                        break;
                                case MI_DIALOG:
                                        butler.printWithDialog(*this, page, *group);
                                        break;
                        } // end switch on the print request
                }
                catch (IException& e)
                {
                        IText error("Caught Exception: ");
                        error.append(e.name());
                        error.append(": ");
                        error.append(e.text());
                        SetInfoText(error);
                }
#endif
                fProcessed = true;
                break;
        }

    break;

  } /* endswitch */

  return fProcessed;

}

/*
 * Function: MainWindow::windowResize
 *
 * Parameters:
 *   event: describes the type of resize event to be processed
 *
 * Return value: returns true when the event it processed - always true here
 *
 * Purpose: Handles the positioning of the buttons of the toolbar as the
 *          window size changes
 *
*/

bool MainWindow::windowResize(IResizeEvent& event)
{
  // if the window size hasn't changed there is nothing to do
  if(event.newSize() == event.oldSize()) return true;

  // if the width of the button is zero, do nothing
  if(buttonArray[0]->size().width() == 0) return true;

  // calculate the number of buttons that can fit in one row
  int newInd = event.newSize().width()/buttonArray[0]->size().width();

  // do some range checking/adjustment
  if(newInd > kNumberOfButtons) newInd = kNumberOfButtons;

  // if the same amount of buttons can fit there is nothing to do
  if((newInd == groupButtIndex) || (newInd == 0)) return true;

  // remove the buttons from the toolbar
  for(unsigned long i = 0; i < kNumberOfButtons; i++) {

    toolBar1.remove( buttonArray[i] );

  }

  // add the buttons in the new orientation
  for(unsigned long j = kNumberOfButtons-1; j > 0; j--) {

    if(!((j+1)%newInd)) {  // if we are at a break point...

      toolBar1.addAsFirst( buttonArray[j], true ); // start another row

    }

    else { // else add to the same row

      toolBar1.addAsFirst( buttonArray[j] );

    }

  }

  toolBar1.addAsFirst( buttonArray[0] );
  groupButtIndex = newInd;
  
  return true;

}

