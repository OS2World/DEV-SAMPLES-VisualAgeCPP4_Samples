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
#include <math.h>
#include <iiconctl.hpp>
#include <imsgbox.hpp>

#include <iostream.h>

// program globals
unsigned long       currentPointer        = POINTER_NONE;
unsigned long       currentPenType        = ID_PENTYPE_SOLID;
unsigned long       fillTransferMode      = ID_SC_FILL_TMODE;
unsigned long       frameTransferMode     = ID_SC_FRAME_TMODE;
unsigned long       fillPattern           = ID_FPATTERN_SOLID;
unsigned long       framePattern          = ID_PATTERN_SOLID;
unsigned long       BUTTON_OFFSET         = PALLET_STYLE;
unsigned long       POINTER_OFFSET        = POINTER_LINE;

// some forward declarations
GParametric angleFromPoints(const IGPoint2D& center, const IGPoint2D& drop);
GCoordinate distanceBetweenPoints(const IGPoint2D& p1, const IGPoint2D& p2);

//*************************************************************************
// Class DrawingArea: method definitions                                  *
//*************************************************************************

IRectangle& DrawingArea::convertGraphicToView( IRectangle& graphicRect )
{

    if( ICoordinateSystem::isConversionNeeded() )
    {
        IRectangle myRect( rect() );
        myRect.moveTo( IPoint(0,0) );
        graphicRect = IRectangle( graphicRect.minX(), myRect.maxY() - graphicRect.minY(), 
                                              graphicRect.maxX(), myRect.maxY() - graphicRect.maxY());
    }                                              

    return graphicRect;
}
   

IMGraphic* DrawingArea::getTopGraphicUnderPoint(const IGPoint2D& point, IGraphicGroup* group)
{
     IGraphicIterator* iterator = group->createIterator();
     IMGraphic* retGraphic = NULL;
     retGraphic = iterator->last();
     for(long i = 0; i < group->count(); i++) {
       if(retGraphic) {
         if(retGraphic->geometricBounds().contains(point)) return retGraphic;
       }
       retGraphic = iterator->previous();
     }
     return NULL;
}

/*
 * Function: DrawingArea::SetDrawState
 *
 * Parameters:
 *    newState: indicates whether the mouse should be captured or released
 *
 * Return value: return the drawing area for which the call was made
 *
 * Purpose: to capture or release the mouse pointer
 *
*/

DrawingArea& DrawingArea::SetDrawState( const DrawingArea::DrawingState newState )
{

  dState = newState;

  if (dState == drawing)  // if we want to draw...
  {

    if (!hasPointerCaptured()) {  // if the pointer is not captured...

      // capture the mouse pointer
      capturePointer();

    }

  }

  else if (dState == notDrawing) {  // if we want to stop drawing...

    // release the mouse pointer
    capturePointer(false);

  }

  return *this;

}

/*
 * Function: DrawingArea::Init
 *
 * Parameters: NONE
 *
 * Return value: NONE
 *
 * Parameters: Initializes the rendering tools for the drawing area
 *
*/

void DrawingArea::Init()
{
  // create the rendering devices
  managedPresSpacePtr = new IManagedPresSpaceHandle(this);
  myDisplayPort = new IBaseRootGrafPort(*managedPresSpacePtr);
  currentGraphic = NULL;

  // create the drawing bundle (outline shape as its being constructed.)
  drawingBundle.setFramePaint(IPaint(IBaseColor(IBaseColor::kWhite)));
  drawingBundle.setDrawingOperation(IAttributeState::kFrame);
  drawingBundle.setFrameTransferMode(IColorTransferMode::kXOR);
  drawingBundle.setFramePen(IPen(IPen::kHairline));
  drawingBundle.setFrameEndCap(ICap(ICap::kSquare));

  // set some default attributes
  currentBundle.setFillPaint(IPaint(IBaseColor(IBaseColor::kGreen)));
  currentBundle.setFramePaint(IPaint(IBaseColor(IBaseColor::kBlue)));
  currentBundle.setDrawingOperation(IAttributeState::kFillAndFrame);
  currentBundle.setFillTransferMode(IColorTransferMode::kSourceCopy);
  currentBundle.setFrameTransferMode(IColorTransferMode::kSourceCopy);
  currentBundle.setFramePen(IPen(IPen::kSolid));
  currentBundle.setFrameEndCap(ICap(ICap::kSquare));

}

/*
 * Function: DrawingArea::Clear
 *
 * Parameters: NONE
 *
 * Return value: NONE
 *
 * Purpose: removes all the previously drawn graphics and refreshes the window
 *
*/

void DrawingArea::Clear()
{
  // delete the graphics
  delete fGraphicGroup;
  fGraphicGroup = new IGraphicGroup();

  // update the window
  refresh();

}

/*
 * Function: DrawingArea::ResetDrawingDevices
 *
 * Parameters: NONE
 *
 * Return value: NONE
 *
 * Purpose: reconstructs the rendering devices (for window resizing)
 *
*/

void DrawingArea::ResetDrawingDevices()
{
  // delete the old rendering devices
  delete myDisplayPort;
  delete parentPort;

  // create new rendering devices

  if(!clipping) {

    parentPort = NULL;
    myDisplayPort = new IBaseRootGrafPort(*managedPresSpacePtr);

  }
  else {

    parentPort = new IBaseRootGrafPort(*managedPresSpacePtr);
    myDisplayPort = new ILinkedGrafPort(parentPort, clipArea);

  }

}

/*
 * Function: DrawingArea::Draw
 *
 * Parameters:
 *   invalidRect: specifies the portion of the window where update is needed
 *
 * Return value: NONE
 *
 * Purpose: repaints the portion of the window that needs updating
 *
*/

void DrawingArea::Draw(IRectangle invalidRect)
{
  IGPoint2D r1, r2;
  IPoint pts[2];
  paintedLastResize = true;
  
  // get the rectangle in world space
  pts[0].setX(invalidRect.left());
  pts[0].setY(invalidRect.bottom());
  pts[1].setX(invalidRect.right());
  pts[1].setY(invalidRect.top());

  r1 = myDisplayPort->invertedDeviceTransform().transformPoint(IGPoint2D(pts[0]));
  r2 = myDisplayPort->invertedDeviceTransform().transformPoint(IGPoint2D(pts[1]));

#ifdef IC_PM
  r1 += IGPoint2D(-1,2);        // one pixel correction for IRect -> IGRect2D, one pixel for truncation due to scaling
  r2 += IGPoint2D(2,-1);   // one pixel correction for IRect -> IGRect2D, one pixel for truncation due to scaling
  IGRect2D eraseRect(r1, r2);
  IGRect2D clipRect(r1, r2);
#else
  // The Pixel correction that I needed to do for NT was different than what
  // was necessary for OS2.  And even odder, was that the eraseRect is different
  // from the cliprect.  But it seems to work.
  r1 += IGPoint2D(-1,-1);
  IGRect2D eraseRect(r1, r2);
  r2 += IGPoint2D(1,1);
  IGRect2D clipRect(r1, r2);
#endif

  clipRect.orderPoints();
  eraseRect.orderPoints();

  // don't clip the background to a graphic!
  if(!clipping)
    myDisplayPort->draw(eraseRect,IFillBundle(IBaseColor(IBaseColor::kWhite)));
  else
    parentPort->draw(eraseRect,IFillBundle(IBaseColor(IBaseColor::kWhite)));

  // create the clip port
  ILinkedGrafPort clipPort(myDisplayPort,new IGArea(clipRect));

  // do the update
  if(fGraphicGroup) {

    fGraphicGroup->draw(clipPort);

  }
}

/*
 * Function: DrawingArea::SetFrameTransferMode
 *
 * Parameters:
 *   mode: specifies the transfer mode to be set
 *
 * Return value: NONE
 *
 * Purpose: set the transfer mode of the current frame paint
 *
*/

void DrawingArea::SetFrameTransferMode(unsigned long mode)
{
  frameTransferMode = mode;

  // select the transfer mode to the frame paint
  switch(mode) {

    case ID_IS_FRAME_TMODE:  // invert source
    {

      currentBundle.setFrameTransferMode(IColorTransferMode::kInvertSource);
      break;

    }

    case ID_DC_FRAME_TMODE:  // destination copy
    {

      currentBundle.setFrameTransferMode(IColorTransferMode::kDestinationCopy);
      break;

    }

    case ID_ID_FRAME_TMODE:  // invert destination
    {

      currentBundle.setFrameTransferMode(IColorTransferMode::kInvertDestination);
      break;

    }

    case ID_SORD_FRAME_TMODE:  // or
    {

      currentBundle.setFrameTransferMode(IColorTransferMode::kOR);
      break;

    }

    case ID_SANDD_FRAME_TMODE:  // and
    {

      currentBundle.setFrameTransferMode(IColorTransferMode::kAND);
      break;

    }

    case ID_SXORD_FRAME_TMODE:  // Xor
    {

      currentBundle.setFrameTransferMode(IColorTransferMode::kXOR);
      break;

    }

    case ID_ISANDD_FRAME_TMODE:  // invert source and
    {

      currentBundle.setFrameTransferMode(IColorTransferMode::kInvertedSourceAND);
      break;

    }

    case ID_ISORD_FRAME_TMODE:  // invert source or
    {

      currentBundle.setFrameTransferMode(IColorTransferMode::kInvertedSourceOR);
      break;

    }

    case ID_SANDID_FRAME_TMODE:  // invert destination and
    {

      currentBundle.setFrameTransferMode(IColorTransferMode::kInvertedDestinationAND);
      break;

    }

    case ID_SORID_FRAME_TMODE:  // invert destination or
    {

      currentBundle.setFrameTransferMode(IColorTransferMode::kInvertedDestinationOR);
      break;

    }

    case ID_IRSANDD_FRAME_TMODE:  // invert and
    {

      currentBundle.setFrameTransferMode(IColorTransferMode::kInvertedAND);
      break;

    }

    case ID_IRSORD_FRAME_TMODE:  // invert or
    {

      currentBundle.setFrameTransferMode(IColorTransferMode::kInvertedOR);
      break;

    }

    case ID_IRSXORD_FRAME_TMODE:  // invert Xor
    {

      currentBundle.setFrameTransferMode(IColorTransferMode::kInvertedXOR);
      break;

    }

    case ID_ONE_FRAME_TMODE:  // all ones (white)
    {

      currentBundle.setFrameTransferMode(IColorTransferMode::kONES);
      break;

    }

    case ID_ZERO_FRAME_TMODE:  // all zeros (black)
    {

      currentBundle.setFrameTransferMode(IColorTransferMode::kZEROS);
      break;

    }

    default:  // source copy
    {

      currentBundle.setFrameTransferMode(IColorTransferMode::kSourceCopy);

    }

  }

}

/*
 * Function: DrawingArea::SetFillTransferMode
 *
 * Parameters:
 *   mode: specifies the transfer mode to be set
 *
 * Return value: NONE
 *
 * Purpose: set the transfer mode of the current fill paint
 *
*/

void DrawingArea::SetFillTransferMode(unsigned long mode)
{
  fillTransferMode = mode;

  // select the transfer mode to the fill paint
  switch(mode) {

    case ID_IS_FILL_TMODE:  // invert source
    {

      currentBundle.setFillTransferMode(IColorTransferMode::kInvertSource);
      break;

    }

    case ID_DC_FILL_TMODE:  // destination copy
    {

      currentBundle.setFillTransferMode(IColorTransferMode::kDestinationCopy);
      break;

    }

    case ID_ID_FILL_TMODE:  // invert destination copy
    {

      currentBundle.setFillTransferMode(IColorTransferMode::kInvertDestination);
      break;

    }

    case ID_SORD_FILL_TMODE:  // or
    {

      currentBundle.setFillTransferMode(IColorTransferMode::kOR);
      break;

    }

    case ID_SANDD_FILL_TMODE:  // and
    {

      currentBundle.setFillTransferMode(IColorTransferMode::kAND);
      break;

    }

    case ID_SXORD_FILL_TMODE:  // Xor
    {

      currentBundle.setFillTransferMode(IColorTransferMode::kXOR);
      break;

    }

    case ID_ISANDD_FILL_TMODE:  // inverted source and
    {

      currentBundle.setFillTransferMode(IColorTransferMode::kInvertedSourceAND);
      break;

    }

    case ID_ISORD_FILL_TMODE:  // inverted source or
    {

      currentBundle.setFillTransferMode(IColorTransferMode::kInvertedSourceOR);
      break;

    }

    case ID_SANDID_FILL_TMODE: // invert destination and
    {

      currentBundle.setFillTransferMode(IColorTransferMode::kInvertedDestinationAND);
      break;

    }

    case ID_SORID_FILL_TMODE: // invert destination or
    {

      currentBundle.setFillTransferMode(IColorTransferMode::kInvertedDestinationOR);
      break;

    }

    case ID_IRSANDD_FILL_TMODE:  // inverted and
    {

      currentBundle.setFillTransferMode(IColorTransferMode::kInvertedAND);
      break;

    }

    case ID_IRSORD_FILL_TMODE:  // inverted or
    {

      currentBundle.setFillTransferMode(IColorTransferMode::kInvertedOR);
      break;

    }

    case ID_IRSXORD_FILL_TMODE:  // inverted Xor
    {

      currentBundle.setFillTransferMode(IColorTransferMode::kInvertedXOR);
      break;

    }

    case ID_ONE_FILL_TMODE:  // all ones (white)
    {

      currentBundle.setFillTransferMode(IColorTransferMode::kONES);
      break;

    }

    case ID_ZERO_FILL_TMODE:  // all zeros (black)
    {

      currentBundle.setFillTransferMode(IColorTransferMode::kZEROS);
      break;

    }

    default:  // source copy
    {

      currentBundle.setFillTransferMode(IColorTransferMode::kSourceCopy);
      break;

    }

  }

}

/*
 * Function: DrawingArea::SetFramePattern
 *
 * Parameters:
 *   mode: identifies the pattern to be set
 *
 * Return value: NONE
 *
 * Purpose: set the pattern of the current frame paint
 *
*/

void DrawingArea::SetFramePattern(unsigned long mode)
{
  framePattern = mode;

  const IPaint *paint = currentBundle.framePaint();
  const IBaseColor *color = paint->color();

  // select the pattern to the frame paint
  switch(mode) {

    case ID_PATTERN_BDIAGONAL:  // backward diagonal
    {

      currentBundle.setFramePaint(IPaint(*color, IMaskPattern::diagonalDown()));
      break;

    }

    case ID_PATTERN_FDIAGONAL:  // forward diagonal
    {

      currentBundle.setFramePaint(IPaint(*color, IMaskPattern::diagonalUp()));
      break;

    }

    case ID_PATTERN_CROSS:  // cross
    {

      currentBundle.setFramePaint(IPaint(*color, IMaskPattern::cross()));
      break;

    }

    case ID_PATTERN_DIAGONALCROSS:  // diagonal cross
    {

      currentBundle.setFramePaint(IPaint(*color, IMaskPattern::diagonalCross()));
      break;

    }

    case ID_PATTERN_HORIZONTAL:  // horizontal
    {

      currentBundle.setFramePaint(IPaint(*color, IMaskPattern::horizontal()));
      break;

    }

    case ID_PATTERN_VERTICAL:  // vertical
    {

      currentBundle.setFramePaint(IPaint(*color, IMaskPattern::vertical()));
      break;

    }

    case ID_PATTERN_EAGLE:  // image eagle pattern
    {
        try {
                IGImage anImage(IGImagePixelAccessor::loadFromFile("eagle.bmp"));
                IPaint paint(anImage);
                paint.setPatternPhase(IGPoint2D::origin());
                paint.setImagePattern(anImage);
                currentBundle.setFramePaint(paint);
        } catch(...)
        {
            // warn the user of their mistake with a message box
            IMessageBox warning(this);
            IString title("File Not Found");
            warning.setTitle(title);
            IString msg("Bitmap file not found in this directory.");
            warning.show(msg,IMessageBox::okButton);
        }

      break;

    }

    case ID_PATTERN_TAJMAHAL:  // image tajmahal pattern
    {

        try {
                IGImage anImage(IGImagePixelAccessor::loadFromFile("tajmahal.bmp"));
                IPaint paint(anImage);
                paint.setPatternPhase(IGPoint2D::origin());
                paint.setImagePattern(anImage);
                currentBundle.setFramePaint(paint);
        } catch(...)
        {
            // warn the user of their mistake with a message box
            IMessageBox warning(this);
            IString title("File Not Found");
            warning.setTitle(title);
            IString msg("Bitmap file not found in this directory.");
            warning.show(msg,IMessageBox::okButton);
        }

      break;

    }

    default:  // solid
    {

      currentBundle.setFramePaint(IPaint(*color, IMaskPattern::solid()));
      break;

    }

  }

}

/*
 * Function: DrawingArea::SetFillPattern
 *
 * Parameters:
 *   mode: identifies the pattern to be set
 *
 * Return value: NONE
 *
 * Purpose: set the pattern of the current fill paint
 *
*/

void DrawingArea::SetFillPattern(unsigned long mode)
{
  fillPattern = mode;

  const IPaint *paint = currentBundle.fillPaint();
  const IBaseColor *color = paint->color();

  // select the pattern to the fill paint
  switch(mode) {

    case ID_FPATTERN_BDIAGONAL:  // backward diagonal
    {

      currentBundle.setFillPaint(IPaint(*color, IMaskPattern::diagonalDown()));
      break;

    }

    case ID_FPATTERN_FDIAGONAL:  // forward diagonal
    {

      currentBundle.setFillPaint(IPaint(*color, IMaskPattern::diagonalUp()));
      break;

    }

    case ID_FPATTERN_CROSS:  // cross
    {

      currentBundle.setFillPaint(IPaint(*color, IMaskPattern::cross()));
      break;

    }

    case ID_FPATTERN_DIAGONALCROSS:  // diagonal cross
    {

      currentBundle.setFillPaint(IPaint(*color, IMaskPattern::diagonalCross()));
      break;

    }

    case ID_FPATTERN_HORIZONTAL:  // horizontal
    {

      currentBundle.setFillPaint(IPaint(*color, IMaskPattern::horizontal()));
      break;

    }

    case ID_FPATTERN_VERTICAL:  // vertical
    {

      currentBundle.setFillPaint(IPaint(*color, IMaskPattern::vertical()));
      break;

    }

    case ID_FPATTERN_EAGLE:  // image eagle pattern
    {

        try {
                IGImage anImage(IGImagePixelAccessor::loadFromFile("eagle.bmp"));
                IPaint paint(anImage);
                paint.setPatternPhase(IGPoint2D::origin());
                paint.setImagePattern(anImage);
                currentBundle.setFillPaint(paint);
        } catch(...)
        {
            // warn the user of their mistake with a message box
            IMessageBox warning(this);
            IString title("File Not Found");
            warning.setTitle(title);
            IString msg("Bitmap file not found in this directory.");
            warning.show(msg,IMessageBox::okButton);
        }

      break;

    }

    case ID_FPATTERN_TAJMAHAL:  // image tajmahal pattern
    {

        try {
                IGImage anImage(IGImagePixelAccessor::loadFromFile("tajmahal.bmp"));
                IPaint paint(anImage);
                paint.setPatternPhase(IGPoint2D::origin());
                paint.setImagePattern(anImage);
                currentBundle.setFillPaint(paint);
        } catch(...)
        {
            // warn the user of their mistake with a message box
            IMessageBox warning(this);
            IString title("File Not Found");
            warning.setTitle(title);
            IString msg("Bitmap file not found in this directory.");
            warning.show(msg,IMessageBox::okButton);
        }

      break;

    }

    default:  // solid
    {

      currentBundle.setFillPaint(IPaint(*color, IMaskPattern::solid()));
      break;

    }

  }

}

/*
 * Function: DrawingArea::SetPenColor
 *
 * Parameters:
 *   color: the new color to be set
 *
 * Return value: NONE
 *
 * Purpose: sets the currently selected pen color
 *
*/

void DrawingArea::SetPenColor(IBaseColor color)
{

  currentBundle.setFrameColor(color);

}

/*
 * Function: DrawingArea::SetFillColor
 *
 * Parameters:
 *   color: the new color to be set
 *
 * Return value: NONE
 *
 * Purpose: sets the currently selected fill color
 *
*/

void DrawingArea::SetFillColor(IBaseColor color)
{

  currentBundle.setFillColor(color);

}

/*
 * Function: DrawingArea::SetDrawingOp
 *
 * Parameters:
 *   op: indicates the drawing operation to be set
 *
 * Return value: NONE
 *
 * Purpose: sets the current drawing operation (fill, frame, or fill and frame)
 *
*/

void DrawingArea::SetDrawingOp(IAttributeState::EDrawOperation op)
{

  currentBundle.setDrawingOperation(op);

}

/*
 * Function: DrawingArea::CreatePen
 *
 * Parameters: NONE
 *
 * Return value: returns a newly created pen, reflecting the current
 *               pen attributes
 *
 * Purpose: creates a pen usising the currently selected pen attributes
 *
*/

void DrawingArea::setPenType(int currentPenType)
{
  const IPen *pen = currentBundle.framePen();
  IPen newPen(*pen);

  // create the appropriate pen
  switch(currentPenType) {

    // the solid pens
    case ID_PENTYPE_SOLID:  // solid
    {

      newPen.setPenType(IPen::kSolid);
      break;

    }

    case ID_PENTYPE_INVISIBLE:  // invisible
    {

      newPen.setPenType(IPen::kInvisible);
      break;

    }

    case ID_PENTYPE_DASHDOUBLEDOT:  // dash-double-dot
    {
      newPen.setPenType(IPen::kDashDotDot);
      break;

    }

    case ID_PENTYPE_DASHDOT:  // dash-dot
    {

      newPen.setPenType(IPen::kDashDot);
      break;

    }

    case ID_PENTYPE_SHORTDASH:  // short dash
    {
      newPen.setPenType(IPen::kDashed);
      break;

    }

    case ID_PENTYPE_DOT:  // dotted
    {

      newPen.setPenType(IPen::kDot);
      break;

    }

    // the hairline pens
    case ID_PENTYPE_HAIRLINE:  // dotted
    {

      newPen.setPenType(IPen::kHairline);
      break;

    }

  }

  currentBundle.setFramePen(newPen);

}


void DrawingArea::SetPenWidth(int width)
{
  const IPen *pen = currentBundle.framePen();
  IPen newPen(*pen);
  newPen.setPenWidth(width);
  currentBundle.setFramePen(newPen);
}

/*
 * Function: DrawingArea::paintWindow
 *
 * Parameters:
 *   evt: describes the type of paint event to be processed
 *
 * Return value: returns true when the event is processed - always true here
 *
 * Purpose: handles paint events for DrawingArea window
 *
*/

bool DrawingArea::paintWindow(IPaintEvent& evt)
{
#ifdef IC_PM
// correct the matrix so drawing is done on the canvas

  if( myDisplayPort )
      myDisplayPort->draw(IGRect2D(0,0,0,0));
#endif  //  IC_PM

  ResetDrawingDevices();
  Draw(evt.rect());

  return true;

}

/*
 * Function: DrawingArea::mouseClicked
 *
 * Parameters:
 *   event: indicates the type of mouse click to be processed
 *
 * Return value: returns true if the event is processed
 *
 * Purpose: Handles mouse clicks occuring inside the drawing area
 *
*/

bool DrawingArea::mouseClicked( IMouseClickEvent& event )
{
  bool bRc = false;

  if ( event.mouseButton() == IMouseClickEvent::button1 &&
       event.mouseAction() == IMouseClickEvent::down ) {

    button1Down(event.mousePosition());
    bRc = false;

  }
  else if ( event.mouseButton() == IMouseClickEvent::button1 &&
            event.mouseAction() == IMouseClickEvent::up ) {

    button1Up(event.mousePosition());
    bRc = true;

  }
  else if ( event.mouseButton() == IMouseClickEvent::button1 &&
            event.mouseAction() == IMouseClickEvent::doubleClick ) {

    button1DoubleClick(event.mousePosition());
    bRc = true;

  }
  else if ( (event.mouseButton() == IMouseClickEvent::button2 || 
             event.mouseButton() == IMouseClickEvent::button3) &&
             event.mouseAction() == IMouseClickEvent::down ) {

    button2or3Down(event.mousePosition());

  }
  else if ( (event.mouseButton() == IMouseClickEvent::button2 ||
             event.mouseButton() == IMouseClickEvent::button3) &&
             event.mouseAction() == IMouseClickEvent::doubleClick ) {

    button2or3DoubleClick(event.mousePosition());

  }

  return bRc;

}

#ifndef IC_MOTIF
/*
 * Function: DrawingArea::mousePointerChange
 *
 * Parameters:
 *   event: gives detail on the type of mouse pointer event to be processed
 *
 * Return value: returns true if the event is processed
 *
 * Purpose: changes the mouse pointer to reflect the current drawing state
 *
*/

bool DrawingArea::mousePointerChange( IMousePointerEvent& event )
{

  // check for default mouse pointers
  if(currentPointer == POINTER_NONE) return false;

  // set a custom pointer
  event.setMousePointer( ptrArray[currentPointer - POINTER_OFFSET] );  // PALLET_LINE is the first pointer id (used as offset)

  return true;

}
#endif

/*
 * Function: DrawingArea::mouseMoved
 *
 * Parameters:
 *   event: contains the mouse position
 *
 * Return value: returns true if the event is processed
 *
 * Purpose: handles a the mouse moved event - used for defining/moving graphics
 *
*/

bool DrawingArea::mouseMoved( IMouseEvent& event )
{

  // get the point from the mouse pointer.
  IPoint point(event.mousePosition());

  if(hasPointerCaptured()) {  // if the mouse has been captured...

    // adjust its position if it is outside the window
    IRectangle windowRect(this->rect());
    windowRect.moveTo(IPoint(0,0));

    if(!windowRect.contains(point)) {

      if((short)point.x() < (short)windowRect.left())
        point.setX(windowRect.left());

      else if((short)point.x() > (short)windowRect.right())
        point.setX(windowRect.right());

      else if((short)point.y() < (short)windowRect.bottom())
        point.setY(windowRect.bottom());

      else if((short)point.y() > (short)windowRect.top())
        point.setY(windowRect.top());

      IPoint mapPt(IWindow::mapPoint(point, this->handle(),
                                     IWindow::desktopWindow()->handle()));
      IWindow::movePointerTo(mapPt);

    }

  }

  if(!moveGraphic) {  // if we are not moving a graphic...

    if ( GetDrawState() == drawing ) {  // if we are in the process of drawing

      switch (currentObj) {

        case line: {  // handle line event

          // erase the old line with Xor
          currentGraphic->draw(*myDisplayPort);
          previousPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

          // change the end point and draw the new line
          IGLine2D* aLine = ((ILine*)(currentGraphic))->orphanGeometry();
          aLine->setEndPoint(previousPoint);
          ((ILine*)(currentGraphic))->adoptGeometry(aLine);
          currentGraphic->draw(*myDisplayPort);

          break;

        }

        case freeHand: {  // handle free hand event

          // add the new point to the polyline
                  previousPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

          IGPolyline2D* poly = tempPolyline->orphanGeometry();
          poly->append(previousPoint);
          tempPolyline->adoptGeometry(poly);

          // draw the new point
          IGLine2D* aLine = ((ILine*)(currentGraphic))->orphanGeometry();
          aLine->setEndPoint(previousPoint);
          ((ILine*)(currentGraphic))->adoptGeometry(aLine);
          currentGraphic->draw(*myDisplayPort);
          aLine = ((ILine*)(currentGraphic))->orphanGeometry();
          aLine->setStartPoint(previousPoint);
          ((ILine*)(currentGraphic))->adoptGeometry(aLine);

          break;

        }

        case rectangle: {  // handle rectangle

          // get the mouse position in world space
          previousPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

          if(currentGraphic) {  // if there is a old rectangle...

            // erase the old rectangle using Xor
            currentGraphic->draw(*myDisplayPort);
            // delete the old rectangle
            delete currentGraphic;
            currentGraphic = NULL;

          }

          // construct the new rectangle and draw it
          IGRect2D theRect(startingPoint,previousPoint);
          IGPoint2DArray pointArray(5);
          pointArray[0] = theRect.topLeft();
          pointArray[1] = theRect.topRight();
          pointArray[2] = theRect.bottomRight();
          pointArray[3] = theRect.bottomLeft();
          pointArray[4] = theRect.topLeft();
          currentGraphic = new IPolygon(new IGPolygon2D(pointArray), new IGrafBundle(drawingBundle));
          currentGraphic->draw(*myDisplayPort);

          break;

        }

        case ellipse: {  // handle ellipse event

          // get the mouse position in world space
                  previousPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

          if(currentGraphic) {  // if there is a old ellipse...

            // erase the old ellipse using Xor
            currentGraphic->draw(*myDisplayPort);

            // delete the old ellipse
            delete currentGraphic;
            currentGraphic = NULL;

          }

          IGPoint2D p1,p2;
          p1 = startingPoint;
          p2 = previousPoint;

          // get the top left and bottom right corners
          if(startingPoint.fX > previousPoint.fX) p1.fX = previousPoint.fX;

          if(startingPoint.fY > previousPoint.fY) p1.fY = previousPoint.fY;

          if(previousPoint.fX < startingPoint.fX) p2.fX = startingPoint.fX;

          if(previousPoint.fY < startingPoint.fY) p2.fY = startingPoint.fY;

          // construct the new ellipse and draw it
          currentGraphic = new IEllipse(new IGEllipse2D(IGRect2D(p1,p2)), new IGrafBundle(drawingBundle));
          currentGraphic->draw(*myDisplayPort);

          break;

        }

        case aloop: {  // handle abstract loop event

          // get the mouse position in world space
                  previousPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

          if(currentGraphic) {  // if there is a old loop...

            // erase the old loop using Xor
            currentGraphic->draw(*myDisplayPort);

            // delete the old loop
            delete currentGraphic;
            currentGraphic = NULL;

          }

          // set the new point, construct the new loop, and draw
          pointArray.setPoint(pointArray.numberOfPoints()-1,IGRPoint2D(previousPoint.fX,previousPoint.fY,1));
                  long order = pointArray.numberOfPoints();
                  if (order < 2) order = 2;
                  if (order > 9) order = 9;
                  cout << "order = " << order << endl;
          currentGraphic = new ILoop(new IGLoop2D(order, pointArray),new IGrafBundle(drawingBundle));
          currentGraphic->draw(*myDisplayPort);

          break;

        }

        case acurve: {  // handle abstract curve event

          // get the mouse position in world space
                  previousPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

          if(currentGraphic) {  // if there is a old curve...

            // erase the curve using Xor
            currentGraphic->draw(*myDisplayPort);

            // delete the curve
            delete currentGraphic;
            currentGraphic = NULL;

          }

          // set the new point, reconstruct the new curve, and draw
          pointArray.setPoint(pointArray.numberOfPoints()-1,IGRPoint2D(previousPoint.fX,previousPoint.fY,1));
                  long order = pointArray.numberOfPoints();
                  if (order < 2) order = 2;
                  if (order > 8) order = 8;
                  cout << "order = " << order << endl;
          currentGraphic = new ICurve(new IGCurve2D(order, pointArray),new IGrafBundle(drawingBundle));
          currentGraphic->draw(*myDisplayPort);

          break;

        }

        case polyline:
        case polygon: {  // handle polyline and polygon events

          // erase the old line (segment) using Xor
          currentGraphic->draw(*myDisplayPort);
                  previousPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

          // define the new segment and draw
          IGLine2D* aLine = ((ILine*)(currentGraphic))->orphanGeometry();
          aLine->setEndPoint(previousPoint);
          ((ILine*)(currentGraphic))->adoptGeometry(aLine);
          currentGraphic->draw(*myDisplayPort);

          break;

        }

        case arc: {  // handle arc event

          if(clickCount == 1) {  // if defining the second point...

            // erase the old line using Xor
            currentGraphic->draw(*myDisplayPort);

            // get the mouse position in world space
                  previousPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

            // define the new line and draw
            IGLine2D* aLine = ((ILine*)(currentGraphic))->orphanGeometry();
            aLine->setEndPoint(previousPoint);
            ((ILine*)(currentGraphic))->adoptGeometry(aLine);
            currentGraphic->draw(*myDisplayPort);

          }

          else if(clickCount == 2) {  // else if defining the last point...

            // erase the old arc using Xor
            currentGraphic->draw(*myDisplayPort);

            // get the mouse position in world space
                  previousPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

            // delete the old arc
            delete currentGraphic;

            // reconstruct the arc with the new point, and draw
            currentGraphic = new ICurve(new IGArcThrough3Points(c1,previousPoint,c3), new IGrafBundle(drawingBundle));
            currentGraphic->draw(*myDisplayPort);

          }

          break;

        }

        case chord: {  // handle chord event

          if(clickCount == 1) {  // if defining the second point...

            // erase the old line using Xor
            currentGraphic->draw(*myDisplayPort);

            // get the mouse position in world space
                  previousPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

            // redefine the line and draw
            IGLine2D* aLine = ((ILine*)(currentGraphic))->orphanGeometry();
            aLine->setEndPoint(previousPoint);
            ((ILine*)(currentGraphic))->adoptGeometry(aLine);
            currentGraphic->draw(*myDisplayPort);

          }

          else if(clickCount == 2) {  // else if defining the last point...

            // erase the old chord
            currentGraphic->draw(*myDisplayPort);

            // get the mouse position in world space
                  previousPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

            // delete the old chord
            delete currentGraphic;

            // reconstruct the chord with the new point, and draw
            currentGraphic = new ILoop(new IGLoop2D(IGCurve2D(IGArcThrough3Points(c1,c2,previousPoint))),new IGrafBundle(drawingBundle));
            currentGraphic->draw(*myDisplayPort);

          }

          break;

        }

        case pie: {  // handle pie event

          if(clickCount == 1) {  // if defining the second point...

            // erase the old line with Xor
            currentGraphic->draw(*myDisplayPort);

            // get the mouse position in world space
                  previousPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

            // redifine the line and draw
            IGLine2D* aLine = ((ILine*)(currentGraphic))->orphanGeometry();
            aLine->setEndPoint(previousPoint);
            ((ILine*)(currentGraphic))->adoptGeometry(aLine);
            currentGraphic->draw(*myDisplayPort);

          }

          else if(clickCount == 2) {  // else if defining the last point...

            // erase the old pie
            currentGraphic->draw(*myDisplayPort);

            // get the pie's radius
            GCoordinate radius = distanceBetweenPoints(c1,c2);

            // get the mouse position in world space
                  previousPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

            // delete the old pie
            delete currentGraphic;

            // reconstruct the pie, using the new point to define the angle
            currentGraphic = new ILoop(new IGLoop2D(IGPie2D(IGRect2D(c1.fX-radius, c1.fY-radius,c1.fX+radius,c1.fY+radius),
                                       angleFromPoints(c1,c2),angleFromPoints(c1,previousPoint))),new IGrafBundle(drawingBundle));

            // draw!
            currentGraphic->draw(*myDisplayPort);

          }

          break;

        }

        case cbezier: {  // handle bezier curve event

          if(clickCount == 1) {  // if defining the second point...

            // erase the old line using Xor
            currentGraphic->draw(*myDisplayPort);

            // get the mouse position in world space
                  previousPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

            // redifene the line and draw
            IGLine2D* aLine = ((ILine*)(currentGraphic))->orphanGeometry();
            aLine->setEndPoint(previousPoint);
            ((ILine*)(currentGraphic))->adoptGeometry(aLine);
            currentGraphic->draw(*myDisplayPort);

          }

          else if(clickCount == 2) {  // else if defining the third point...

            // erase the old curve using Xor
            currentGraphic->draw(*myDisplayPort);

            // get the mouse position in world space
                  previousPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

            // delete the old curve
            delete currentGraphic;

            // reconstruct the curve using the new point as both the second and
            // third control points
            currentGraphic = new ICurve(new IGCurve2D(c1,previousPoint,previousPoint,c4), new IGrafBundle(drawingBundle));

            // draw!
            currentGraphic->draw(*myDisplayPort);

          }

          else if(clickCount == 3) {  // else if defining the last point...

            // erase the old curve using Xor
            currentGraphic->draw(*myDisplayPort);

            // get the mouse position in word space
                  previousPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

            // delete the old curve
            delete currentGraphic;

            // reconstruct the curve using the new point, and draw
            currentGraphic = new ICurve(new IGCurve2D(c1,c2,previousPoint,c4), new IGrafBundle(drawingBundle));
            currentGraphic->draw(*myDisplayPort);

          }

          break;

        }

        case lbezier: {  // handle bezier loop event

          if(clickCount == 1) {  // if defining the second point...

            // erase the old line using Xor
            currentGraphic->draw(*myDisplayPort);

            // get the mouse position in world space
                  previousPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

            // redefine the line and draw
            IGLine2D* aLine = ((ILine*)(currentGraphic))->orphanGeometry();
            aLine->setEndPoint(previousPoint);
            ((ILine*)(currentGraphic))->adoptGeometry(aLine);
            currentGraphic->draw(*myDisplayPort);

          }

          else if(clickCount == 2) {  // else if defining the third point...

            // erase the old loop using Xor
            currentGraphic->draw(*myDisplayPort);

            // get the mouse position in world space
                  previousPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

            // delete the old loop
            delete currentGraphic;

            // reconstruct the curve using the new point as both the second and
            // third control points
            currentGraphic = new ILoop(new IGLoop2D(IGCurve2D(c1,previousPoint,previousPoint,c4)), new IGrafBundle(drawingBundle));

            // draw!
            currentGraphic->draw(*myDisplayPort);

          }

          else if(clickCount == 3) {  // else if defining the last point...

            // erase the old loop using Xor
            currentGraphic->draw(*myDisplayPort);

            // get the mouse position in world space
                  previousPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

            // delete the old loop
            delete currentGraphic;

            // reconstruct the loop using the new point, and draw
            currentGraphic = new ILoop(new IGLoop2D(IGCurve2D(c1,c2,previousPoint,c4)), new IGrafBundle(drawingBundle));
            currentGraphic->draw(*myDisplayPort);

          }

          break;

        }

      } // end switch

    }

  }

  else {  // else were moving a graphic...

    // get the mouse position in world space
    IGPoint2D currentPoint;
        currentPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

    // erase the old rectangle using Xor
    currentGraphic->draw(*myDisplayPort);

    // translate the rectangle to reflect the change in mouse position
    currentGraphic->translateBy(currentPoint - previousPoint);

    // update the previous positon
    previousPoint = currentPoint;

    // draw the rectangle in the new position
    currentGraphic->draw(*myDisplayPort);

  }

  return false;

}

/*
 * Function: DrawingArea::button1Down
 *
 * Parameters:
 *   point: the position of the mouse pointer when the event occured
 *
 * Return value: returns the drawing area in which the event occured
 *
 * Purpose: handles the button 1 down mouse event
 *
*/

DrawingArea& DrawingArea::button1Down( const IPoint& point )
{
  // get the mouse position in world space
        startingPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));
  previousPoint = startingPoint;

  // process the event based on the current draw object
  switch (currentObj) {

    case pointer: {  // handle move event

      moveGraphic = getTopGraphicUnderPoint(startingPoint, fGraphicGroup);

      if(moveGraphic) {  // if a graphic was selected...

        // set the current graphic to be the moveGraphic's bounding rectangle
        // again
        IGRect2D theRect(moveGraphic->geometricBounds());
        IGPoint2DArray pointArray(5);
        pointArray[0] = theRect.topLeft();
        pointArray[1] = theRect.topRight();
        pointArray[2] = theRect.bottomRight();
        pointArray[3] = theRect.bottomLeft();
        pointArray[4] = theRect.topLeft();
        currentGraphic = new IPolygon(new IGPolygon2D(pointArray), new IGrafBundle(drawingBundle));
        currentGraphic->draw(*myDisplayPort);

        // set the instuctions in the information area and capture the mouse
        SetInfoText("Drag bounding rectangle to new position and release the mouse button.");
        capturePointer();

      }

      break;

    }

    case clip: {  // handle clipping event
      IMGraphic* clipGraphic = getTopGraphicUnderPoint(startingPoint,fGraphicGroup);

      if(clipGraphic)
      {  // if a graphic was selected...

        // get the graphic's area
        clipArea = NULL;
        clipArea = GraphicToArea(clipGraphic);

        if(clipArea)
        {  // if the graphic has area...

          // turn clipping on and clip to the selected graphic
          clipping = true;
          clipGraphic->draw(*myDisplayPort);
          ResetDrawingDevices();
          refresh();

        }

      }
      break;

    }

    case attribStyle: {  // handle apply attributes event

      currentGraphic = getTopGraphicUnderPoint(startingPoint,fGraphicGroup);

      if(currentGraphic) {  // if a graphic was selected...
        // invalidate old box
        IRectangle oldRect( myDisplayPort->matrix(kViewMatrix)->
                    transformBounds(currentGraphic->geometricBounds()));

        // replace the graphic's old attributes with the currently selected ones
        currentGraphic->adoptBundle(new IGrafBundle(currentBundle));

#ifdef IC_PM
        refresh();
#else
        refresh( convertGraphicToView(oldRect).expandBy( IPair(2,2)), false );
        IRectangle rect( myDisplayPort->matrix(kViewMatrix)->
                    transformBounds(currentGraphic->geometricBounds()));
        refresh( convertGraphicToView(rect).expandBy( IPair(2,2)), true );
#endif
        currentGraphic = NULL;

      }

      break;

    }

    case rotate: {  // handle rotate event

      currentGraphic = getTopGraphicUnderPoint(startingPoint,fGraphicGroup);

      if(currentGraphic) {  // if a graphic was selected...

        // invalidate the old bounding rect first
        IRectangle oldRect( myDisplayPort->matrix(kViewMatrix)->
                        transformBounds(currentGraphic->geometricBounds()));

        // rotate the graphic -10 degrees (counter clockwise) about its center
        currentGraphic->rotateBy(-10, currentGraphic->geometricBounds().center());
        
        // refresh the affected part of the canvas
#ifdef IC_PM
        refresh();
#else
        refresh( convertGraphicToView(oldRect).expandBy( IPair(2,2)), false );
        IRectangle rect( myDisplayPort->matrix(kViewMatrix)->
                    transformBounds(currentGraphic->geometricBounds()));
        refresh( convertGraphicToView(rect).expandBy( IPair(2,2)), true );
#endif
        currentGraphic = NULL;

      }

      break;

    }

    case scale: {  // handle scale event

      currentGraphic = getTopGraphicUnderPoint(startingPoint,fGraphicGroup);

      if(currentGraphic) {  // if a graphic was selected...
                            // if graphic is smaller than desktop, then scale
        if((IWindow::desktopWindow()->size().width()  > currentGraphic->geometricBounds().size().fX) &&
           (IWindow::desktopWindow()->size().height() > currentGraphic->geometricBounds().size().fY)) {
        // increase the graphics size by 10%
        currentGraphic->scaleBy(IGPoint2D(1.1,1.1), currentGraphic->geometricBounds().center());

        // only have to refresh new box because it's bigger than the old one
        IRectangle rect( myDisplayPort->matrix(kViewMatrix)->
                        transformBounds(currentGraphic->geometricBounds()));
#ifdef IC_PM
        refresh();
#else
        refresh( convertGraphicToView(rect).expandBy( IPair(2,2)), true );
#endif
        currentGraphic = NULL;
        }
      }

      break;

    }

    case line: {  // handle line event

      if(currentGraphic) {  // if there is a old graphic...

        // delete the old graphic
        delete currentGraphic;
        currentGraphic = NULL;

      }

      // set the current graphic to a line (with no size at the moment)
      IGLine2D* myLine = new IGLine2D(startingPoint,previousPoint);
      ILine *lne = new ILine(myLine, new IGrafBundle(drawingBundle));
      currentGraphic = lne;

      // set some instructions in the information area
      SetInfoText("Drag to define line. Release to finish");

      // capture the mouse
      SetDrawState();

      break;

    }

    case freeHand: {  // handle free hand or sketch event

      if(currentGraphic) {  // if there is a old graphic...

        // delete the old graphic
        delete currentGraphic;
        currentGraphic = NULL;

      }

      // draw the sketch line by line
      IGLine2D *myLine = new IGLine2D(startingPoint,previousPoint);
      ILine *lne = new ILine(myLine, new IGrafBundle(currentBundle));
      currentGraphic = lne;

      // construct the sketch with a polyline
      tempPolyline = new IPolyline;

      IGPolyline2D* poly = new IGPolyline2D;
      poly->append(previousPoint);
      tempPolyline->adoptGeometry(poly);

      // capture the mouse
      SetDrawState();

      break;

    }

    case rectangle: {  // handle rectangle event

      if(currentGraphic) {  // if there is a old graphic...

        // delete the old graphic
        delete currentGraphic;
        currentGraphic = NULL;

      }

      // the rectangle is empty now

      // set the instructions in the informaiton area
      SetInfoText("Drag to define rectangle. Release to finish.");

      // capture the mouse
      SetDrawState();

      break;

    }

    case ellipse: {  // handle ellipse event

      if(currentGraphic) {  // if there is a old graphic...

        // delete the old graphic
        delete currentGraphic;
        currentGraphic = NULL;

      }

      // the ellipse is empty now

      // set the instructions in the information area
      SetInfoText("Drag to define ellipse. Release to finish.");

      // capture the mouse
      SetDrawState();

      break;

    }

    case polyline: {  // handle polyline event

      if (GetDrawState() == notDrawing) {  // if this is a new polyline...

        if(currentGraphic) {  // if there is a old graphic...

          // delete the old graphic
          delete currentGraphic;
          currentGraphic = NULL;

        }

        // draw the polyline segment by segment
        IGLine2D *myLine = new IGLine2D(startingPoint,previousPoint);
        ILine *lne = new ILine(myLine, new IGrafBundle(drawingBundle));
        currentGraphic = lne;

        // construct the polyline point by point
        tempPolyline = new IPolyline;

        IGPolyline2D* poly = new IGPolyline2D;
        poly->append(previousPoint);
        tempPolyline->adoptGeometry(poly);

        // set the instructions in the information area
        SetInfoText("Drag to define next point.  Double click to finish");

        // capture the mouse
        SetDrawState();

      }

      break;

    }

    case polygon: {  // handle polygon event

      if (GetDrawState() == notDrawing) {  // if this is a new polygon...

        if(currentGraphic) {  // if there is a old graphic...

          // delete the old graphic
          delete currentGraphic;
          currentGraphic = NULL;

        }

        // draw the polygon segment by segment
        IGLine2D *myLine = new IGLine2D(startingPoint,previousPoint);
        ILine *lne = new ILine(myLine, new IGrafBundle(drawingBundle));
        currentGraphic = lne;

        // construct a polyline to be used to erase the frame
        tempPolyline = new IPolyline;

        // construct the polygon point by point
        tempPolygon = new IPolygon;

        // add the initial point
        IGPolyline2D* poly = new IGPolyline2D;
        poly->append(previousPoint);
        tempPolyline->adoptGeometry(poly);

        IGPolygon2D* polyg = new IGPolygon2D;
        polyg->append(startingPoint);
        tempPolygon->adoptGeometry(polyg);


        // set the instructions in the information area
        SetInfoText("Drag to define next point.  Double click to finish");

        // capture the mouse
        SetDrawState();

      }

      break;

    }

    case acurve: {  // handle abstract curve event

      if (GetDrawState() == notDrawing) {  // if this is a new curve...

        if(currentGraphic) {  // if these is a old graphic...

          // delete the old graphic
          delete currentGraphic;
          currentGraphic = NULL;

        }

        // initialize a point array and store the first control point
                pointArray.setGrowIncrement(100);
        pointArray.resize(0);
        pointArray.append(IGRPoint2D(startingPoint.fX,startingPoint.fY,1));
        pointArray.resize(pointArray.numberOfPoints()+1);

        // capture the mouse
        SetDrawState();

        // set some instructions in the information area
        SetInfoText("Drag to define next point.  Double click to finish");

      }

      break;

    }

    case aloop: {  // handle abstract loop event

      if (GetDrawState() == notDrawing) {  // if this is a new loop...

        if(currentGraphic) {  // if there is a old graphic...

          // delete the old graphic
          delete currentGraphic;
          currentGraphic = NULL;

        }

        // initialize a point array and store the first control point
                pointArray.setGrowIncrement(100);
        pointArray.resize(0);
        pointArray.append(IGRPoint2D(startingPoint.fX,startingPoint.fY,1));
        pointArray.resize(pointArray.numberOfPoints()+1);

        // capture the mouse
        SetDrawState();

        // set some instructions in the information area
        SetInfoText("Drag to define next point.  Double click to finish");

      }

      break;

    }

    case arc: {  // handle arc event

      if(clickCount == 0) {  // if this is a new arc...

        if(currentGraphic) {  // if there is a old graphic...

          // delete the old graphic
          delete currentGraphic;
          currentGraphic = NULL;

        }

        // start with a line
        IGLine2D *myLine = new IGLine2D(startingPoint,previousPoint);
        ILine *lne = new ILine(myLine, new IGrafBundle(drawingBundle));
        currentGraphic = lne;

        // capture the mouse
        SetDrawState();

        // set the initial point and update the click counter
        c1 = startingPoint;
        clickCount++;

        // set some instructions in the information area
        SetInfoText("Drag to define next point. Release when finished.");

      }

      break;

    }

    case chord: {  // handle chord event

      if(clickCount == 0) {  // if this is a new chord...

        if(currentGraphic) {  // if there is a old graphic...

          // delete the old graphic
          delete currentGraphic;
          currentGraphic = NULL;

        }

        // start with a line
        IGLine2D *myLine =  new IGLine2D(startingPoint,previousPoint);
        ILine *lne = new ILine(myLine, new IGrafBundle(drawingBundle));
        currentGraphic = lne;

        // capture the mouse
        SetDrawState();

        // set the initial point and update the click counter
        c1 = startingPoint;
        clickCount++;

        // set some instructions in the information area
        SetInfoText("Drag to define next point. Release when finished.");

      }

      break;

    }

    case pie: {  // handle pie event

      if(clickCount == 0) {  // if this is a new pie...

        if(currentGraphic) {  // if there is a old graphic...

          // delete the old graphic
          delete currentGraphic;
          currentGraphic = NULL;

        }

        // start with a line
        IGLine2D *myLine = new IGLine2D(startingPoint,previousPoint);
        ILine *lne = new ILine(myLine, new IGrafBundle(drawingBundle));
        currentGraphic = lne;

        // capture the mouse
        SetDrawState();

        // set the initial point and update the click counter
        c1 = startingPoint;
        clickCount++;

        // set some instructions in the information area
        SetInfoText("Drag to define radius, and initial angle. Release when finished.");

      }

      break;

    }

    case cbezier: {  // handle bezier curve event

      if(clickCount == 0) {  // if this is a new bezier curve...

        if(currentGraphic) {  // if there is a old graphic...

          // delete the old graphic
          delete currentGraphic;
          currentGraphic = NULL;

        }

        // start with a line
        IGLine2D *myLine = new IGLine2D(startingPoint,previousPoint);
        ILine *lne = new ILine(myLine, new IGrafBundle(drawingBundle));
        currentGraphic = lne;

        // capture the mouse
        SetDrawState();

        // set the initial point and update the click counter
        c1 = startingPoint;
        clickCount++;

        // set some instructions in the information area
        SetInfoText("Drag to define end point. Release when finished.");

      }

      break;

    }

    case lbezier: {  // handle bezier loop event

      if(clickCount == 0) {  // if this is a new bezier loop...

        if(currentGraphic) {  // if there is a old graphic...

          // delete the old graphic
          delete currentGraphic;
          currentGraphic = NULL;

        }

        // start with a line
        IGLine2D *myLine = new IGLine2D(startingPoint,previousPoint);
        ILine *lne = new ILine(myLine, new IGrafBundle(drawingBundle));
        currentGraphic = lne;

        // capture the mouse
        SetDrawState();

        // set the initial point and update the click counter
        c1 = startingPoint;
        clickCount++;

        // set some instructions in the information area
        SetInfoText("Drag to define end point. Release when finished.");

      }

      break;

    }

    case add: {  // handle area add event
      if(clickCount == 0) {  // if this is a new area being created...

        if(currentGraphic) {  // if there is a old graphic...

          // delete the old graphic
          delete currentGraphic;
          currentGraphic = NULL;

        }

        currentGraphic = getTopGraphicUnderPoint(startingPoint,fGraphicGroup);

        if(currentGraphic) {  // if a graphic is selected...

          // update the click counter
          clickCount++;

          // set some instructions in the information area
          SetInfoText("Click on second area graphic for addition.");

        }

      }

      else if(clickCount == 1) {  // if a initial graphic has been selected...

        IMGraphic* addGraphic = getTopGraphicUnderPoint(startingPoint,fGraphicGroup);

        if(addGraphic && (addGraphic != currentGraphic)) {  // if a different graphic is
                                                            // selected...
          // create the areas
         const IGArea* a1 = GraphicToArea(currentGraphic);
         const IGArea* a2 = GraphicToArea(addGraphic);

          if(a1 && a2) {  // if the areas are both valid...

            // remove the graphics from the graphic group
            delete fGraphicGroup->orphan(*currentGraphic);
            delete fGraphicGroup->orphan(*addGraphic);

            // construct an area graphic from addition
            currentGraphic = new IArea(new IGArea(*a1+*a2),new IGrafBundle(currentBundle));

            // add the new graphic to the group
            fGraphicGroup->adoptLast(currentGraphic);

            IRectangle rect( myDisplayPort->matrix(kViewMatrix)->
                        transformBounds(currentGraphic->geometricBounds()));
#ifdef IC_PM
            refresh();
#else
            refresh( convertGraphicToView(rect).expandBy( IPair(2,2)), true );
#endif
          }

          else {  // else an invalid graphic was selected...

            // warn the user of their error with a message box
            IMessageBox warning(this);
            IString title("Invalid Operation");
            warning.setTitle(title);
            IString msg("Cannot add non-area graphic to area graphic.");
            warning.show(msg,IMessageBox::okButton);

          }

        }

        currentGraphic = NULL;

        // set some instructions in the information area
        SetInfoText(PALLET_ADD+LONG_OFFSET);

        // reset the click counter
        clickCount = 0;

      }
      break;

    }

    case subtract: {  // handle area subtract event
      if(clickCount == 0) {  // if this is a new area being created...

        if(currentGraphic) {  // if there is a old graphic...

          // delete the old graphic
          delete currentGraphic;
          currentGraphic = NULL;

        }

        currentGraphic = getTopGraphicUnderPoint(startingPoint,fGraphicGroup);

        if(currentGraphic) {  // if a graphic was selected...

          // update the click counter
          clickCount++;

          // set some instructions in the information area
          SetInfoText("Click on second area graphic for subtraction.");

        }

      }

      else if(clickCount == 1) {  // if an initial graphic has been selected...

        IMGraphic* addGraphic = getTopGraphicUnderPoint(startingPoint,fGraphicGroup);

        if(addGraphic && (addGraphic != currentGraphic)) {  // if another different graphic
                                                            // is selected...
          // create the areas
         const IGArea* a1 = GraphicToArea(currentGraphic);
         const IGArea* a2 = GraphicToArea(addGraphic);

          if(a1 && a2) {  // if the areas area both valid...

            // remove the graphics from the group
            delete fGraphicGroup->orphan(*currentGraphic);
            delete fGraphicGroup->orphan(*addGraphic);

            // create a new area graphics from subtraction
            currentGraphic = new IArea(new IGArea(*a1-*a2),new IGrafBundle(currentBundle));

            // replace the graphics with the area graphic
            fGraphicGroup->adoptLast(currentGraphic);

            IRectangle rect( myDisplayPort->matrix(kViewMatrix)->
                        transformBounds(currentGraphic->geometricBounds()));
#ifdef IC_PM
            refresh();
#else
            refresh( convertGraphicToView(rect).expandBy( IPair(2,2)), true );
#endif
          }

          else {  // else an invalid graphic was selected...

            // warn the user of their error with a message box
            IMessageBox warning(this);
            IString title("Invalid Operation");
            warning.setTitle(title);
            IString msg("Cannot subtract non-area graphic from area graphic.");
            warning.show(msg,IMessageBox::okButton);

          }

        }

        currentGraphic = NULL;

        // set some instructions in the information area
        SetInfoText(PALLET_SUBTRACT+LONG_OFFSET);

        // reset the click counter
        clickCount = 0;

      }
      break;

    }

    case multiply: {  // handle area multiply event
      if(clickCount == 0) {  // if a new area is being created...

        if(currentGraphic) {  // if there is a old graphic...

          // delete the old graphic
          delete currentGraphic;
          currentGraphic = NULL;

        }

        currentGraphic = getTopGraphicUnderPoint(startingPoint,fGraphicGroup);

        if(currentGraphic) {  // if a graphic is selected...

          // update the click counter
          clickCount++;

          // set some instructions in the information area
          SetInfoText("Click on second area graphic for intersection.");

        }

      }

      else if(clickCount == 1) {  // if an initial graphic has been selected...

        IMGraphic* addGraphic = getTopGraphicUnderPoint(startingPoint,fGraphicGroup);

        if(addGraphic && (addGraphic != currentGraphic)) {  // if another different graphic
                                                            // is selected...
          // create the areas
         const IGArea* a1 = GraphicToArea(currentGraphic);
         const IGArea* a2 = GraphicToArea(addGraphic);

          if(a1 && a2) {  // if the areas are valid...

            // remove the graphics from the group
            delete fGraphicGroup->orphan(*currentGraphic);
            delete fGraphicGroup->orphan(*addGraphic);

            // create an area graphic through intersection
            currentGraphic = new IArea(new IGArea((*a1)*(*a2)),new IGrafBundle(currentBundle));

            // replace the graphics with the area graphic
            fGraphicGroup->adoptLast(currentGraphic);

            IRectangle rect( myDisplayPort->matrix(kViewMatrix)->
                        transformBounds(currentGraphic->geometricBounds()));
#ifdef IC_PM
            refresh();
#else
            refresh( convertGraphicToView(rect).expandBy( IPair(2,2)), true );
#endif
          }

          else {  // else an invalid graphic was selected...

            // warn the user of their error with a message box
            IMessageBox warning(this);
            IString title("Invalid Operation");
            warning.setTitle(title);
            IString msg("Cannot intersect non-area graphic with area graphic.");
            warning.show(msg,IMessageBox::okButton);

          }

        }

        currentGraphic = NULL;

        // set some instructions in the information area
        SetInfoText(PALLET_MULTIPLY+LONG_OFFSET);

        // reset the click counter
        clickCount = 0;

      }
      break;

    }

    case Xor: {  // handle area Xor event
      if(clickCount == 0) {  // if this is a new area being created...

        if(currentGraphic) {  // if there is a old graphic...

          // delete the old graphic
          delete currentGraphic;
          currentGraphic = NULL;

        }

        currentGraphic = getTopGraphicUnderPoint(startingPoint,fGraphicGroup);

        if(currentGraphic) {  // if a graphic is selected...

          // update the click counter
          clickCount++;

          // set some instructions in the information area
          SetInfoText("Click on second area graphic for Xoring.");

        }

      }

      else if(clickCount == 1) {  // if an initial graphic has been selected...

        IMGraphic* addGraphic = getTopGraphicUnderPoint(startingPoint,fGraphicGroup);

        if(addGraphic && (addGraphic != currentGraphic)) {  // if another differnt graphic
                                                            // is selected...
          // contruct the areas
         const IGArea* a1 = GraphicToArea(currentGraphic);
         const IGArea* a2 = GraphicToArea(addGraphic);

          if(a1 && a2) {  // if the areas are valid...

            // remove the graphics from the graphic group
            delete fGraphicGroup->orphan(*currentGraphic);
            delete fGraphicGroup->orphan(*addGraphic);

            // create an area graphic through Xor
            currentGraphic = new IArea(new IGArea(*a1^*a2),new IGrafBundle(currentBundle));

            // replace the graphics with the area graphic
            fGraphicGroup->adoptLast(currentGraphic);

            IRectangle rect( myDisplayPort->matrix(kViewMatrix)->
                        transformBounds(currentGraphic->geometricBounds()));
#ifdef IC_PM
            refresh();
#else
            refresh( convertGraphicToView(rect).expandBy( IPair(2,2)), true );
#endif
          }

          else {  // else an invalid graphic was selected...

            // warn the user of their mistake with a message box
            IMessageBox warning(this);
            IString title("Invalid Operation");
            warning.setTitle(title);
            IString msg("Cannot Xor non-area graphic with area graphic.");
            warning.show(msg,IMessageBox::okButton);

          }

        }

        currentGraphic = NULL;

        // set some instructions in the information area
        SetInfoText(PALLET_XOR+LONG_OFFSET);

        // reset the click counter
        clickCount = 0;

      }
      break;

    }

    case text: {  // handle text event

        if(currentGraphic) {  // if there is a old graphic...

          // delete the old graphic
          delete currentGraphic;
          currentGraphic = NULL;

        }

      // create a new text graphic and draw it
          int start = 0;
          int end = 0;
          for (int i = 0; i * 100 < graphicText.length(); i++)
          {
                start = i;
                if (graphicText.length() - start > 100)
                        end = 100;
                else
                        end = graphicText.length() - start;
                IText substring(graphicText.substr(start, end));
                IGraphicText *graftext = new IGraphicText(substring, IGraphicText::kSingleLine);
                graftext->setLocation(IGPoint2D(startingPoint.fX, startingPoint.fY + 10 * i));
                fGraphicGroup->adoptLast(graftext);
                graftext->draw(*myDisplayPort);
          }


      break;

    }

    case bitmap: {  // handle bitmap event

        try {
                IImage *myimage = new IImage(IGImagePixelAccessor::loadFromFile("eagle.bmp"));
                myimage->translateBy(startingPoint);
                fGraphicGroup->adoptLast(myimage);
                myimage->draw(*myDisplayPort);
                currentGraphic = NULL;
        } catch(...)
        {
            // warn the user of their mistake with a message box
            IMessageBox warning(this);
            IString title("File Not Found");
            warning.setTitle(title);
            IString msg("Bitmap file not found in this directory.");
            warning.show(msg,IMessageBox::okButton);
        }


      break;

    }

  }  // end switch

  return *this;
}

/*
 * Function: DrawingArea::button1Up
 *
 * Parameters:
 *   point: the position of the mouse pointer when the event occured
 *
 * Return value: returns the drawing area in which the event occured
 *
 * Purpose: handles the button 1 up mouse event
 *
*/

DrawingArea& DrawingArea::button1Up( const IPoint& point )
{
  if(!moveGraphic) {  // if we are not moving a graphic...

    if ( GetDrawState() == drawing ) {  // if we are in the process of drawing...

      switch (currentObj) {

        case line: {  // handle line event

          // erase the old line using Xor
          currentGraphic->draw(*myDisplayPort);

          // replace the bundle to reflect the currently selected attributes
          currentGraphic->adoptBundle(new IGrafBundle(currentBundle));

          // add the line to the graphic group
          fGraphicGroup->adoptLast(currentGraphic);

          // draw the new line then reset it's pointer
          currentGraphic->draw(*myDisplayPort);
          currentGraphic = NULL;

          // reset the instructions in the information area
          SetInfoText(PALLET_LINE+LONG_OFFSET);

          // release the capture on the mouse
          SetDrawState(notDrawing);

          break;
        }

        case freeHand: {  // handle free hand event

          // erase the old sketch
          IGrafBundle* bundle = currentGraphic->orphanBundle();
          currentGraphic = tempPolyline;
          currentGraphic->adoptBundle(bundle);

          // add the graphic to the graphic group
          fGraphicGroup->adoptLast(currentGraphic);

          // reset the graphic's pointer
          currentGraphic = NULL;

          // release the capture on the mouse
          SetDrawState(notDrawing);

          break;

        }

        case rectangle:
        case ellipse: {  // handle rectangle and ellipse events

          if(currentGraphic) {  // if there is a old graphic...

            // erase the old graphic using Xor
            currentGraphic->draw(*myDisplayPort);

            // replace its bundle to reflect the currently selected attributes
            currentGraphic->adoptBundle(new IGrafBundle(currentBundle));

            // add it to the graphic group
            fGraphicGroup->adoptLast(currentGraphic);

            // draw the graphic with its new attributes
            currentGraphic->draw(*myDisplayPort);
            currentGraphic = NULL;

          }

          // release the capture on the mouse
          SetDrawState(notDrawing);

          // reset the instructions in the information area
          if(currentObj == rectangle)
            SetInfoText(PALLET_RECTANGLE+LONG_OFFSET);

          else
            SetInfoText(PALLET_ELLIPSE+LONG_OFFSET);

          break;
        }

        case polyline: {  // handle polyline event

          // erase the old line segment
          currentGraphic->draw(*myDisplayPort);

          // get the mouse position in world space
                        startingPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

          // set the line to the start of the new segment
          IGLine2D* aLine = ((ILine*)(currentGraphic))->orphanGeometry();
          aLine->setStartPoint(previousPoint);
          ((ILine*)(currentGraphic))->adoptGeometry(aLine);

          // add the point to the polyline
          IGPolyline2D* poly = tempPolyline->orphanGeometry();
          poly->append(previousPoint);
          tempPolyline->adoptGeometry(poly);

          // draw the defined section of the polyline
          tempPolyline->draw(*myDisplayPort);

          break;

        }
        case polygon: {  // handle polygon event

          // erase the old line segment
          currentGraphic->draw(*myDisplayPort);


          // get the mouse position in world space
                        startingPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

          // set the line to the start of a new segment
          IGLine2D* aLine = ((ILine*)(currentGraphic))->orphanGeometry();
          aLine->setStartPoint(previousPoint);
          ((ILine*)(currentGraphic))->adoptGeometry(aLine);

          // update the frame and the polygon
          IGPolyline2D* poly = tempPolyline->orphanGeometry();
          poly->append(previousPoint);
          tempPolyline->adoptGeometry(poly);

          IGPolygon2D* polyg = tempPolygon->orphanGeometry();
          polyg->append(previousPoint);
          tempPolygon->adoptGeometry(polyg);

          // draw the defined section of the polygon
          tempPolyline->draw(*myDisplayPort);

          break;

        }

        case acurve: {  // handle abstract curve event

          // get the mouse position in world space
                        startingPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

          // add the new point to the control point array
          pointArray.resize(pointArray.numberOfPoints()-1);  // chop off last point
          pointArray.append(IGRPoint2D(startingPoint.fX,startingPoint.fY,1));
          pointArray.resize(pointArray.numberOfPoints()+1);  // add new empty point

          break;

        }

        case aloop: {  // handle abstract loop event

          // get the mouse position in world space
                        startingPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

          // add the new point to the control point array
          pointArray.resize(pointArray.numberOfPoints()-1);  // chop off last point
          pointArray.append(IGRPoint2D(startingPoint.fX,startingPoint.fY,1));
          pointArray.resize(pointArray.numberOfPoints()+1);  // add new empty point

          break;

        }

        case arc: {  // handle arc event

          if(clickCount == 1) {  // if defining the second point...

            // get the mouse position in world space
            // and make it a control point
                        c3 = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

            // change the instructions in the information area
            SetInfoText("Drag to define arc.  Double click to finish");

            // update the click counter
            clickCount++;

          }

          break;

        }

        case chord: {  // handle chord event

          if(clickCount == 1) {  // if defining the second point...

            // get the mouse position in world space
            // and make it a control point
                        c2 = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

            // change the instructions in the information area
            SetInfoText("Drag to define chord.  Double click to finish");

            // update the click counter
            clickCount++;

          }

          break;

        }

        case pie: {  // handle pie event

          if(clickCount == 1) {  // if defining the second point...

            // get the mouse position in world space
            // and make it a control point
                        c2 = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

            // change the instructions in the information area
            SetInfoText("Drag to define pie.  Double click to finish");

            // update the click counter
            clickCount++;

          }

          break;

        }

        case cbezier: {  // handle bezier curve event

          if(clickCount == 1) {  // if defining the second point...

            // get the mouse position in world space
            // and make it a control point
                        c4 = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

            // change the instructions in the information area
            SetInfoText("Drag to define first control point. Release when finished.");

            // update the click counter
            clickCount++;

          }

          else if(clickCount == 2) {  // else if defining the third point...

            // get the mouse position in world space
            // and make it a control point
                        c2 = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

            // change the instructions in the information area
            SetInfoText("Drag to define second control point. Release when finished.");

            // update the click counter
            clickCount++;

          }

          else if(clickCount == 3) {  // else if defining the last point...

            // get the mouse position in world space
            // and make it a control point
                        c3 = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

            // erase the old curve using Xor
            currentGraphic->draw(*myDisplayPort);

            // delete the old curve
            delete currentGraphic;

            // reconstruct the curve with the new point, and attributes and draw
            currentGraphic = new ICurve(new IGCurve2D(c1,c2,c3,c4),new IGrafBundle(currentBundle));
            currentGraphic->draw(*myDisplayPort);

            // add the curve to the graphic group, and reset it's pointer
            fGraphicGroup->adoptLast(currentGraphic);
            currentGraphic = NULL;

            // release the capture on the mouse
            SetDrawState(notDrawing);

            // reset the instructions in the information area
            SetInfoText(PALLET_CBEZIER+LONG_OFFSET);

            // reset the click counter
            clickCount = 0;

          }

          break;

        }

        case lbezier: {  // handle bezier loop event

          if(clickCount == 1) {  // if defining the second point...

            // get the mouse position in world space
            // and make it a control point
                        c4 = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

            // change the instructions in the information area
            SetInfoText("Drag to define first control point. Release when finished.");

            // update the click counter
            clickCount++;

          }

          else if(clickCount == 2) {  // else if defining the third point...

            // get the mouse position in world space
            // and make it a control point
                        c2 = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

            // change the instructions in the information area
            SetInfoText("Drag to define second control point. Release when finished.");

            // update the click counter
            clickCount++;

          }

          else if(clickCount == 3) {  // else if defining the last point...

            // get the mouse position in world space
            // and make it a control point
                        c3 = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

            // erase the old curve using Xor
            currentGraphic->draw(*myDisplayPort);

            // delete the old curve
            delete currentGraphic;

            // reconstruct the curve with the new point, and attributes and draw
            currentGraphic = new ILoop(new IGLoop2D(IGCurve2D(c1,c2,c3,c4)),new IGrafBundle(currentBundle));
            currentGraphic->draw(*myDisplayPort);

            // add the curve to the graphic group, and reset it's pointer
            fGraphicGroup->adoptLast(currentGraphic);
            currentGraphic = NULL;

            // release the capture on the mouse
            SetDrawState(notDrawing);

            // reset the instructions in the information area
            SetInfoText(PALLET_LBEZIER+LONG_OFFSET);

            // reset the click counter
            clickCount = 0;

          }

          break;

        }

      }  // end switch

    }

  }

  else {  // else we are moving a graphic...

    // get the mouse position in world space
    IGPoint2D currentPoint;
        currentPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

    // invalidate old location        
    IRectangle oldRect( myDisplayPort->matrix(kViewMatrix)->
                transformBounds(moveGraphic->geometricBounds()));

    // move the graphic to its new position
    moveGraphic->translateBy(currentPoint - startingPoint);

    // repaint the drawing area
#ifdef IC_PM
    refresh();
#else
    refresh( convertGraphicToView(oldRect).expandBy( IPair(2,2)), true );
    IRectangle rect( myDisplayPort->matrix(kViewMatrix)->
                transformBounds(currentGraphic->geometricBounds()));
    refresh( convertGraphicToView(rect).expandBy( IPair(2,2)), true );
    myDisplayPort->draw(IGRect2D(0,0,0,0));
#endif
    // reset the move graphic's pointer
    moveGraphic = NULL;

    // reset the instructions in the information area
    SetInfoText(PALLET_NORM+LONG_OFFSET);

    // release the capture on the mouse
    capturePointer(false);

  }

  return *this;

}

/*
 * Function: DrawingArea::button1DoubleClick
 *
 * Parameters:
 *   point: the position of the mouse pointer when the event occured
 *
 * Return value: returns the drawing area in which the event occured
 *
 * Purpose: handles the button 1 double click mouse event
 *
*/

DrawingArea& DrawingArea::button1DoubleClick( const IPoint& point )
{
  if (GetDrawState() == drawing ) {  // if we are in the process of drawing

    switch (currentObj) {

      case polyline: {  // handle polyline event

        // delete the last line segment
        delete currentGraphic;

        // set the graphic to the polyline
        currentGraphic = tempPolyline;

        // erase the old polyline
        tempPolyline->adoptBundle(new IGrafBundle(drawingBundle));
        tempPolyline->draw(*myDisplayPort);

        // adopt the currently selected attributes into the polyline, and draw
        currentGraphic->adoptBundle(new IGrafBundle(currentBundle));
        currentGraphic->draw(*myDisplayPort);

        // add the polyline to the graphic group and reset it's pointer
        fGraphicGroup->adoptLast(currentGraphic);
        currentGraphic = NULL;

        // reset the instructions in the information area
        SetInfoText(PALLET_POLYLINE+LONG_OFFSET);

        // release the capture on the mouse pointer
        SetDrawState(notDrawing);

        break;

      }

      case polygon: {  // handle polygon event

        // delete the last line segment
        delete currentGraphic;

        // set the graphic to the polygon
        currentGraphic = tempPolygon;

        // erase the polygon's frame
        tempPolyline->draw(*myDisplayPort);

        // adopt the currently selected attributes into the polygon, and draw
        currentGraphic->adoptBundle(new IGrafBundle(currentBundle));
        currentGraphic->draw(*myDisplayPort);

        // add the polygon to the graphic group and reset it's pointer
        fGraphicGroup->adoptLast(currentGraphic);
        currentGraphic = NULL;

        // reset the instructions in the information area
        SetInfoText(PALLET_POLYGON+LONG_OFFSET);

        // release the capture on the mouse
        SetDrawState(notDrawing);

        break;

      }

      case acurve: {  // handle abstract curve event

        // erase the old curve using Xor
        currentGraphic->draw(*myDisplayPort);

        // replace the attributes with the currently selected ones
        currentGraphic->adoptBundle(new IGrafBundle(currentBundle));

        // add the curve to the graphic group and draw
        fGraphicGroup->adoptLast(currentGraphic);
        currentGraphic->draw(*myDisplayPort);

        // reset the graphic's pointer
        currentGraphic = NULL;

        // reset the instructions in the information area
        SetInfoText(PALLET_ACURVE+LONG_OFFSET);

        // release the capture on the mouse
        SetDrawState(notDrawing);

        break;

      }

      case aloop: {  // handle abstract loop event

        // erase the old loop using Xor
        currentGraphic->draw(*myDisplayPort);

        // replace the attributes with the currently selected ones
        currentGraphic->adoptBundle(new IGrafBundle(currentBundle));

        // add the loop to the graphic goup and draw
        fGraphicGroup->adoptLast(currentGraphic);
        currentGraphic->draw(*myDisplayPort);

        // reset the graphic's pointer
        currentGraphic = NULL;

        // reset the instructions in the information area
        SetInfoText(PALLET_ALOOP+LONG_OFFSET);

        // release the capture on the mouse pointer
        SetDrawState(notDrawing);

        break;

      }

      case arc: {  // handle arc event

        // erase the old arc using Xor
        currentGraphic->draw(*myDisplayPort);

        // delete the old arc
        delete currentGraphic;

        // get the mouse position in world space
        // and make it a control point
                c2 = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

        // redefine the arc using the new control point, and draw
        currentGraphic = new ICurve(new IGArcThrough3Points(c1,c2,c3),new IGrafBundle(currentBundle));
        currentGraphic->draw(*myDisplayPort);

        // add the arc to the graphic group and reset it's pointer
        fGraphicGroup->adoptLast(currentGraphic);
        currentGraphic = NULL;

        // reset the instructions in the infromation area
        SetInfoText(PALLET_ARC+LONG_OFFSET);

        // release the capture on the mouse pointer
        SetDrawState(notDrawing);

        // reset the click counter
        clickCount = 0;

        break;

      }

      case chord: {  // handle chord event

        // erase the old chord using Xor
        currentGraphic->draw(*myDisplayPort);

        // delete the old chord
        delete currentGraphic;

        // get the mouse position in world space
        // and make it a control point
                c3 = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

        // redefine the chord using the new control point, and draw
        currentGraphic = new ILoop(new IGLoop2D(IGCurve2D(IGArcThrough3Points(c1,c2,c3))),new IGrafBundle(currentBundle));
        currentGraphic->draw(*myDisplayPort);

        // add the chord to the graphic group, and reset it's pointer
        fGraphicGroup->adoptLast(currentGraphic);
        currentGraphic = NULL;

        // reset the instructions in the information area
        SetInfoText(PALLET_CHORD+LONG_OFFSET);

        // release the capture on the mouse
        SetDrawState(notDrawing);

        // reset the click counter
        clickCount = 0;

        break;

      }

      case pie: {  // handle pie event

        // erase the old pie using Xor
        currentGraphic->draw(*myDisplayPort);

        // delete the old pie
        delete currentGraphic;

        // get the mouse position in world space
        // and make it a control point
                c3 = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

        // calculate the pie's radius
        GCoordinate radius = distanceBetweenPoints(c1,c2);

        // redefine the pie using the new control point to define the angle
        currentGraphic = new ILoop(new IGLoop2D(IGPie2D(IGRect2D(c1.fX-radius, c1.fY-radius,c1.fX+radius,c1.fY+radius),angleFromPoints(c1,c2),angleFromPoints(c1,c3))), new IGrafBundle(currentBundle));

        // draw the new pie
        currentGraphic->draw(*myDisplayPort);

        // add it to the graphic group and reset it's pointer
        fGraphicGroup->adoptLast(currentGraphic);
        currentGraphic = NULL;

        // reset the instructions in the information area
        SetInfoText(PALLET_PIE+LONG_OFFSET);

        // release the capture on the mouse
        SetDrawState(notDrawing);

        // reset the click counter
        clickCount = 0;

        break;

      }

    } // end switch

  }

  else if(currentObj == rotate) {  // else if we are rotating a graphic...

    // get the mouse position in world space...
        startingPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

    currentGraphic = getTopGraphicUnderPoint(startingPoint,fGraphicGroup);

    if(currentGraphic) {  // if a graphic is selected...
      // invalidate old box
      IRectangle oldRect( myDisplayPort->matrix(kViewMatrix)->
                  transformBounds(currentGraphic->geometricBounds()));

      // rotate the graphic -10 degrees (counter clockwise) about it's center
      currentGraphic->rotateBy(-10, currentGraphic->geometricBounds().center());

      // repaint the drawing area
#ifdef IC_PM
      refresh();
#else
      refresh( convertGraphicToView(oldRect).expandBy( IPair(2,2)), false );
      IRectangle rect( myDisplayPort->matrix(kViewMatrix)->
                  transformBounds(currentGraphic->geometricBounds()));
      refresh( convertGraphicToView(rect).expandBy( IPair(2,2)), true );
#endif
      // reset the graphics pointer
      currentGraphic = NULL;

    }

  }

  return *this;

}

/*
 * Function: DrawingArea::button2or3DoubleClick
 *
 * Parameters:
 *   point: the position of the mouse pointer when the event occured
 *
 * Return value: returns the drawing area in which the event occured
 *
 * Purpose: handles the button 2(or 3 in Motif) double click mouse event
 *
*/

DrawingArea& DrawingArea::button2or3DoubleClick( const IPoint& point )
{

  if(currentObj == rotate) {  // if we are rotating a graphic...

    // get the mouse position in world space
        startingPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));

    currentGraphic = getTopGraphicUnderPoint(startingPoint,fGraphicGroup);

    if(currentGraphic) {  // if a graphic is selected...
      // invalidate old box
      IRectangle oldRect( myDisplayPort->matrix(kViewMatrix)->
                  transformBounds(currentGraphic->geometricBounds()));

      // rotate the graphic by 10 degrees (clockwise) about it's center
      currentGraphic->rotateBy(10, currentGraphic->geometricBounds().center());

      // repaint the drawing area
#ifdef IC_PM
      refresh();
#else
      refresh( convertGraphicToView(oldRect).expandBy( IPair(2,2)), false );
      IRectangle rect( myDisplayPort->matrix(kViewMatrix)->
                  transformBounds(currentGraphic->geometricBounds()));
      refresh( convertGraphicToView(rect).expandBy( IPair(2,2)), true );
#endif
      // reset the graphics pointer
      currentGraphic = NULL;

    }

  }

  return *this;

}

/*
 * Function: DrawingArea::button2or3Down
 *
 * Parameters:
 *   point: the position of the mouse pointer when the event occured
 *
 * Return value: returns the drawing area in which the event occured
 *
 * Purpose: handles the button 2(or 3 in Motif) down mouse event
 *
*/

DrawingArea& DrawingArea::button2or3Down( const IPoint& point)
{
  // get the mouse position in world space
        startingPoint = myDisplayPort->pixelToPointSize().transformPoint(IGPoint2D(point));
  previousPoint = startingPoint;

  // process the event based on the current draw object
  switch (currentObj) {

    case clip: {  // handle clipping event
      if(clipping) {  // if clipping was on...

        // turn clipping off
        clipping = false;
        ResetDrawingDevices();
        refresh();

      }
      break;

    }

    case scale: {  // handle scale event

      currentGraphic = getTopGraphicUnderPoint(startingPoint,fGraphicGroup);

      if(currentGraphic) {  // if a graphic was selected...
        // invalidate old box
        IRectangle oldRect( myDisplayPort->matrix(kViewMatrix)->
                    transformBounds(currentGraphic->geometricBounds()));

        // decrease the graphics size by 10%
        currentGraphic->scaleBy(IGPoint2D(0.9,0.9), currentGraphic->geometricBounds().center());

#ifdef IC_PM
        refresh();
#else
        refresh( convertGraphicToView(oldRect).expandBy( IPair(2,2)), false );
        IRectangle rect( myDisplayPort->matrix(kViewMatrix)->
                    transformBounds(currentGraphic->geometricBounds()));
        refresh( convertGraphicToView(rect).expandBy( IPair(2,2)), true );
#endif
        currentGraphic = NULL;

      }

      break;

    }

    case rotate: {  // handle rotate event

      currentGraphic = getTopGraphicUnderPoint(startingPoint,fGraphicGroup);

      if(currentGraphic) {  // if a graphic was selected...
        // invalidate the old box
        IRectangle oldRect( myDisplayPort->matrix(kViewMatrix)->
                    transformBounds(currentGraphic->geometricBounds()));

        // rotate the graphic by 10 degrees (clockwise) about its center
        currentGraphic->rotateBy(10, currentGraphic->geometricBounds().center());

#ifdef IC_PM
        refresh();
#else
        refresh( convertGraphicToView(oldRect).expandBy( IPair(2,2)), false );
        IRectangle rect( myDisplayPort->matrix(kViewMatrix)->
                    transformBounds(currentGraphic->geometricBounds()));
        refresh( convertGraphicToView(rect).expandBy( IPair(2,2)), true );
        currentGraphic = NULL;
#endif

      }

      break;

    }

  }  // end switch

  return *this;
}

//*************************************************************************
// helper functions for defining pie                                      *
//*************************************************************************

/*
 * Funciton: angleFromPoints
 *
 * Parameters:
 *   center: the center or reference point for calculating the angle
 *   drop  : the point describing the angle
 *
 * Return value: returns the angle a
 *
 *                                * drop
 *                               /
 *                              / ) a
 *                     center  *------
 *
 * Purpose: calculates the angle between center and drop using center as
 *          the reference point
 *
*/

GParametric angleFromPoints(const IGPoint2D& center, const IGPoint2D& drop)
{

  IGPoint2D temp;
  GParametric angle;

  temp = drop - center;
  angle = atan2(temp.fY, temp.fX);
  angle *= 57.295779;

  if(angle < 0.0) angle += 360.0;

  return angle;

}

/*
 * Function: distanceBetweenPoints
 *
 * Paramtertes:
 *   p1: the first reference point
 *   p2: the second reference point
 *
 * Return value: the distance between points p1 and p2
 *
 * Purpose: calculates the distance between points p1 and p2
 *
*/

GCoordinate distanceBetweenPoints(const IGPoint2D& p1, const IGPoint2D& p2)
{

  return sqrt((p1.fX-p2.fX)*(p1.fX-p2.fX) + (p1.fY-p2.fY)*(p1.fY-p2.fY));

}

//*************************************************************************
// main  - Application entry point                                        *
//*************************************************************************

int main()                             //Main procedure with no parameters
{
  IToolBarButton::setDefaultStyle( IToolBarButton::defaultStyle() |
                                   IToolBarButton::autoLatch      |
                                   IToolBarButton::useIdForText   |
                                   IWindow::visible );

  IToolBar::setDefaultStyle(IToolBar::classDefaultStyle
                            | IToolBar::buttonBitmapAndTextVisible
                            | IToolBar::noDragDrop );

  MainWindow  mainWindow(WND_MAIN);     //Create our main window on the desktop

  try {

    IApplication::current().run();        //Get the current application and
                                        // run it
  }

  catch(IException& exc) {

  }

} /* end main */


IGArea *
DrawingArea::GraphicToArea(IMGraphic *mgraphic)
{
        IGArea *Area = NULL;
#ifdef IC_WIN
        IArea *a = NULL;
        IEllipse *e = NULL;
        IPolygon *p = NULL;
        ILoop *l = NULL;

        if (a = dynamic_cast<IArea*>(mgraphic))
        {
                Area = new IGArea(*(a->geometry()));
                return Area;
        }
        if (e = dynamic_cast<IEllipse*>(mgraphic))
        {
                Area = new IGArea(*(e->geometry()));
                return Area;
        }
        if (p = dynamic_cast<IPolygon*>(mgraphic))
        {
                Area = new IGArea(*(p->geometry()));
                return Area;
        }
        if (l = dynamic_cast<ILoop*>(mgraphic))
        {
                Area = new IGArea(*(l->geometry()));
                return Area;
        }
#endif

        Area = new IGArea(mgraphic->geometricBounds());
        return Area;
}

/*
 * Function: DrawingArea::windowResize
 *
 * Parameters:
 *   p1: the resize event
 *
 * Return value: boolean condition whether to continue processing
 *
 * Purpose: force a minimum repaint on size events.  In a size event where
 * 	    both horizontal and vertical size is larger than the previous window size a single paint 
 *          event is sent with a invalid rect equal to the minimum rectangle containing both horz. and 
 *          vert. invalid rects.  This function breaks that event in to two paint events to minimize the 
 *          repainted area.  This also minimizes painting when the toolbar is resized and redrawn.
 *
*/


bool DrawingArea::windowResize(IResizeEvent& event)
{
    bool result = false;

#ifdef IC_MOTIFWIN
    static IRectangle oldWinRect;
    IRectangle winRect( rect() );
    
    IRectangle toolBarRect(((MainWindow*)parent())->toolbar().rect());

    if( toolBarRect.maxY() > winRect.minY() )
    {
        paintedLastResize = false;
    }
    
    // normalize winRect
    winRect.moveTo( IPoint(0,0) );
    IRectangle validRect( convertGraphicToView(winRect) );
    validRect.expandBy( IPair(100,100) );
                    
    if( oldWinRect != IRectangle() )
    {
        long newWidth = winRect.maxX() - winRect.minX();
        long oldWidth = oldWinRect.maxX() - oldWinRect.minX();
        long newHeight = winRect.maxY() - winRect.minY();
        long oldHeight = oldWinRect.maxY() - oldWinRect.minY();

        if( myDisplayPort && ( newWidth > oldWidth ))
        {
            if( !paintedLastResize && myDisplayPort )
            {
                refresh( convertGraphicToView(validRect), true );
            }
            paintedLastResize = false;

            // construct the horizontal and vertical invalid rects
            IRectangle vertRect, hortRect;

            IPoint hortTL( 0, oldWinRect.maxY() );
            IPoint hortBR( winRect.maxX(), winRect.maxY() );
            IPoint vertTL( oldWinRect.maxX(), winRect.minY() );
            IPoint vertBR( winRect.maxX(), hortTL.y() );
            
            IRectangle vert( vertTL, vertBR );
            IRectangle hort( hortTL, hortBR );

            if( hortTL.y() < hortBR.y() )
            {
                validateRect( validRect );
                refresh( immediate );
                refresh( convertGraphicToView(hort), true );
            }
            
            validateRect( validRect );
            refresh( immediate );
            refresh( convertGraphicToView(vert), true );

            result = true;
        }
    }
    
    oldWinRect = winRect;
#endif  //  IC_MOTIFWIN

    return result;
}

