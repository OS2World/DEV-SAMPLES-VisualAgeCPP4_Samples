/******************************************************************************
* .FILE:        darea.cpp                                                     *
*                                                                             *
* .DESCRIPTION: Implementation for the class, DrawingArea                     *
*                                                                             *
* .CLASSES:     DrawingArea                                                   *
*                                                                             *
* .COPYRIGHT:                                                                 *
*    Licensed Material - Program-Property of IBM                              *
*    (C) Copyright IBM Corp. 1992, 1996 - All Rights Reserved                 *
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

#ifndef _IBASE_                         //Make sure ibase.hpp is included
  #include <ibase.hpp>                  //  since that is where IC_<environ>
#endif                                  //  is defined.
#include "darea.hpp"
#include <igline.hpp>
#include <igpyline.hpp>
#include <igelipse.hpp>
#include <igarc.hpp>
#include <igpie.hpp>
#include <igstring.hpp>
#include <igbitmap.hpp>
#include <icolor.hpp>
#include <iglist.hpp>
#include <math.h>

/*------------------------------------------------------------------------------
| angleFromPoints                                                              |
|                                                                              |
| Given two points determine the angle between the horizontal line through     |
| the first point and the line from the first point to the second point.       |
------------------------------------------------------------------------------*/
double angleFromPoints( const IPoint& center, const IPoint& drop )
{
  IPoint temp;
  double angle;

  temp  = drop - center;
  angle = atan2((double)temp.y(), (double)temp.x());
  angle *= 57.295779;

  if ( angle < 0.0 )
    angle += 360.0;

  return angle;
}

/*------------------------------------------------------------------------------
| DrawingArea::DrawingArea                                                     |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
DrawingArea::DrawingArea( unsigned long id, IWindow* parent,
                          IWindow* owner, const IRectangle& rect )
  : IDrawingCanvas( id, parent, owner, rect ),
    gc(handle()),
    currentfont(),
    currentBundle(),
    currentBitmap(),
    dState( notDrawing ),
    currentObj( move ),
    iGraphic(0),
    moveGraphic(0),
    moveRect(IRectangle()),
    startingPt(), previousPt(), tempPt(),
    pointCount(0),
    flyOverHandler(0)
{
  currentBundle.setPenColor(IGraphicContext::defaultPenColor())
               .setFillColor(IGraphicContext::defaultFillColor())
               .setMixMode(IGraphicContext::defaultMixMode())
               .setPenJoiningStyle(IGraphicBundle::miter)
               .setDrawOperation( IGraphicBundle::fillAndFrame );

gc.setMixMode( IGraphicBundle::xor ).setPenColor( IColor::white )
    .setFillColor( IColor::white )
    .setDrawOperation( IGraphicBundle::frame )
    .setHitApertureSize( ISize(2,2) );
  setGraphicContext( &gc );

  setGraphicList( new IGList() );

  // Load the pointers.

//  IResourceLibrary reslib;
  IDynamicLinkLibrary reslib("CPPWV53R");
  ptrLine      = reslib.loadPointer( POINTER_LINE );
  ptrFreehand  = reslib.loadPointer( POINTER_FREEHAND );
  ptrRectangle = reslib.loadPointer( POINTER_RECTANGLE );
  ptrEllipse   = reslib.loadPointer( POINTER_ELLIPSE );
  ptrPolyline  = reslib.loadPointer( POINTER_POLYLINE );
  ptrPolygon   = reslib.loadPointer( POINTER_POLYGON );
  ptrArc       = reslib.loadPointer( POINTER_ARC );
  ptrPie       = reslib.loadPointer( POINTER_PIE );
  ptrChord     = reslib.loadPointer( POINTER_CHORD );
  ptrText      = reslib.loadPointer( POINTER_TEXT );
  ptrBitmap    = reslib.loadPointer( POINTER_BITMAP );
  ptrStyleCan  = reslib.loadPointer( POINTER_STYLECAN );
  ptrEraser    = reslib.loadPointer( POINTER_ERASER );

  ((IMouseHandler*)this)->handleEventsFor(this);
}

/*------------------------------------------------------------------------------
| DrawingArea::DrawingArea                                                     |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
DrawingArea::~DrawingArea( )
{
  // Delete all the graphic objects in the drawing canvas.
  IGList::Cursor graphicsCursor( *graphicList() );
  for ( graphicsCursor.setToFirst();
        graphicsCursor.isValid();
        graphicsCursor.setToNext() )
  {
    IGraphic* graphic(&(graphicList()->graphicAt(graphicsCursor)));
    delete graphic;
  } /* endfor */
  delete graphicList();
}

/*------------------------------------------------------------------------------
| DrawingArea::changeMousePointer                                              |
|                                                                              |
| Change the cursor to reflect the object being drawn.                         |
------------------------------------------------------------------------------*/
Boolean DrawingArea::mousePointerChange( IMousePointerEvent& event )
{
  Boolean fReturn(true);

//  if (event.windowId() != 32776)
//    return(false);
//  if (infoArea)
//  {
//    infoArea->setText("Set the text!");
//  }

  switch (drawObject())
  {
    case POINTER_MOVE:
      return fReturn = false;
    break;
    case POINTER_LINE:
      event.setMousePointer( ptrLine );
    break;
    case POINTER_FREEHAND:
      event.setMousePointer( ptrFreehand );
    break;
    case POINTER_RECTANGLE:
      event.setMousePointer( ptrRectangle );
    break;
    case POINTER_ELLIPSE:
      event.setMousePointer( ptrEllipse );
    break;
    case POINTER_POLYLINE:
      event.setMousePointer( ptrPolyline );
    break;
    case POINTER_POLYGON:
      event.setMousePointer( ptrPolygon );
    break;
    case POINTER_ARC:
      event.setMousePointer( ptrArc );
    break;
    case POINTER_PIE:
      event.setMousePointer( ptrPie );
    break;
    case POINTER_CHORD:
      event.setMousePointer( ptrChord );
    break;
    case POINTER_TEXT:
      event.setMousePointer( ptrText );
    break;
    case POINTER_BITMAP:
      event.setMousePointer( ptrBitmap );
    break;
    case POINTER_STYLECAN:
      event.setMousePointer( ptrStyleCan );
    break;
    case POINTER_ERASER:
      event.setMousePointer( ptrEraser );
    break;
    default:
      fReturn = false;
    break;
  } // end switch

  return fReturn;
}

/*------------------------------------------------------------------------------
| DrawingArea::mouseClicked                                                    |
|                                                                              |
| Translate the mouse clicked events.                                          |
------------------------------------------------------------------------------*/
Boolean DrawingArea::mouseClicked( IMouseClickEvent& event )
{
  Boolean bRc = false;
  if ( event.mouseButton() == IMouseClickEvent::button1 &&
       event.mouseAction() == IMouseClickEvent::down )
  {
    button1Down(event.mousePosition());
    bRc = false;
  }
  else if ( event.mouseButton() == IMouseClickEvent::button1 &&
            event.mouseAction() == IMouseClickEvent::up )
  {
    button1Up(event.mousePosition());
    bRc = true;
  }
  else if ( event.mouseButton() == IMouseClickEvent::button1 &&
            event.mouseAction() == IMouseClickEvent::doubleClick )
  {
    button1DoubleClick(event.mousePosition());
    bRc = true;
  }
  else if ( event.mouseButton() == IMouseClickEvent::button2 &&
            event.mouseAction() == IMouseClickEvent::down )
  {
    button2Down(event.mousePosition());
  }
  else if ( event.mouseButton() == IMouseClickEvent::button2 &&
            event.mouseAction() == IMouseClickEvent::up )
  {
    button2Up(event.mousePosition());
  }

  return bRc;
}


/*------------------------------------------------------------------------------
| DrawingArea::button1Down                                                     |
|                                                                              |
| Handle button 1 down messages.  This event indicates a new graphic object is |
| to be created of additional data points to add to an existing graphic object.|
------------------------------------------------------------------------------*/
DrawingArea& DrawingArea::button1Down( const IPoint& point )
{
  switch (currentObj)
  {
    case move: // Button 1 drag
      if (drawState() == notDrawing)
      {
        moveGraphic = graphicList()->topGraphicUnderPoint( point, gc );
        if ( moveGraphic )
        {
          moveRect.setEnclosingRect(moveGraphic->boundingRect( gc ));
          previousPt = point;
          startingPt = point;
          capturePointer();
        }
      }
    break;
    case eraser:
      {
        // Delete the object under the pointer
        moveGraphic = graphicList()->topGraphicUnderPoint( point, gc );
        if ( moveGraphic )
        {
          moveRect.setEnclosingRect(moveGraphic->boundingRect( gc ));
          IGList::Cursor cursor( *graphicList(), gc, point );
          for (cursor.setToFirst(); cursor.isValid(); cursor.setToNext())
          {
             IGraphic* graphic(&(graphicList()->graphicAt(cursor)));
             if (graphic == moveGraphic)
             {
               graphicList()->removeAt(cursor);
               delete graphic;
               this->refresh( moveRect.boundingRect(gc).expandBy(2) );
               moveRect.resetTransformMatrix();
               moveGraphic = 0;
               break;
             }
          }
        }
      }
    break;
    case stylecan:
    {
      // Change all objects to the current pen and fill color.
      IRectangle tempRect;
      moveGraphic = graphicList()->topGraphicUnderPoint( point, gc );
      if( moveGraphic )
      {
        tempRect = moveGraphic->boundingRect( gc );
        moveGraphic->setGraphicBundle( currentBundle );
        moveGraphic->drawOn( gc );
        tempRect |= moveGraphic->boundingRect( gc );
        this->refresh( tempRect.expandBy(2) );
        moveGraphic = 0;
      }
    }
    break;
    case line:
      startingPt = point;
      previousPt = point;
      iGraphic = new IGLine( startingPt, previousPt );
      setDrawState();
    break;
    case freehand:
      iGraphic = new IGPolygon(IPointArray());
      ((IGPolygon*)iGraphic)->addPoint( point );
      setDrawState();
    break;
    case rectangle:
      startingPt = point;
      previousPt = point;
      iGraphic = new IGRectangle(IRectangle(startingPt, previousPt));
      setDrawState();
    break;
    case ellipse:
      startingPt = point;
      previousPt = point;
      iGraphic = new IGEllipse( startingPt, 0L );
      setDrawState();
    break;
    case polyline:
    case polygon:
      if (drawState() == notDrawing)
      {
        startingPt = point;
        previousPt = point;
        if (currentObj == polyline)
          iGraphic = new IGPolyline(IPointArray());
        else
          iGraphic = new IGPolygon(IPointArray());

        ((IGPolyline*)iGraphic)->addPoint( startingPt );
        ((IGPolyline*)iGraphic)->addPoint( previousPt );
        setDrawState();
      }
      else
      {
        ((IGPolyline*)iGraphic)->IGPolyline::drawOn( gc );
        ((IGPolyline*)iGraphic)->addPoint( point );
        ((IGPolyline*)iGraphic)->IGPolyline::drawOn( gc );
      }
    break;
    case arc:
      pointCount++;
      if (drawState() == notDrawing)
      {
        iGraphic = new IG3PointArc( point, IPoint(0,0), IPoint(0,0) );
        startingPt = point;
        previousPt = point;
      }
      else if ( pointCount == 2 )
      {
        previousPt = point;
        IGLine tempLine( ((IG3PointArc*)iGraphic)->startingPoint(), point );
        tempLine.drawOn( gc );
      }
      else if ( pointCount == 3 )
      {
        IGLine tempLine( ((IG3PointArc*)iGraphic)->startingPoint(), previousPt );
        tempLine.drawOn( gc );
        previousPt = point;
        ((IG3PointArc*)iGraphic)->setEndingPoint( point );
        iGraphic->drawOn( gc );
      }
      setDrawState();
    break;
    case pie:
    case chord:
      pointCount++;
      if (drawState() == notDrawing)
      {
        if (currentObj == pie)
          iGraphic = new IGPie( IRectangle(), 0, 0);
        else
          iGraphic = new IGChord( IRectangle(), 0, 0);

        ((IGPie*)iGraphic)->setEnclosingRect(
                             ((IGPie*)iGraphic)->enclosingRect().centerAt( point ));
        startingPt = point;
        previousPt = point;
      }
      else if ( pointCount == 2 )
      {
        previousPt = point;
        IGLine tempLine( ((IGPie*)iGraphic)->enclosingRect().center(), point );
        tempLine.drawOn( gc );
      }
      else if ( pointCount == 3 )
      {
        IGLine tempLine( ((IGPie*)iGraphic)->enclosingRect().center(), previousPt );
        tempLine.drawOn( gc );
        previousPt = point;
        double sweep(angleFromPoints( ((IGPie*)iGraphic)->enclosingRect().center(), point ));
        if ( sweep < ((IGPie*)iGraphic)->startAngle() )
          ((IGPie*)iGraphic)->setSweepAngle( 360.0 -
                                ( ((IGPie*)iGraphic)->startAngle() - sweep ));
        else
          ((IGPie*)iGraphic)->setSweepAngle( sweep -
                                            ((IGPie*)iGraphic)->startAngle());
        iGraphic->drawOn( gc );
      }
      setDrawState();
    break;
    case text:
      setDrawState();
    break;
    case bitmap:
      setDrawState();
    break;
  } /* endswitch */
  return *this;
}

/*------------------------------------------------------------------------------
| DrawingArea::button1Up                                                       |
|                                                                              |
| Handle button 1 up events.  This indicates a data points final location.     |
------------------------------------------------------------------------------*/
DrawingArea& DrawingArea::button1Up( const IPoint& point )
{
  if ( drawState() == drawing )
  {
    switch (currentObj)
    {
      case move:
      break;
      case eraser:
      break;
      case stylecan:
      break;
      case line:
        ((IGLine*)iGraphic)->setEndingPoint( point );
        iGraphic->setGraphicBundle( currentBundle );
        iGraphic->drawOn( gc );
        setDrawState( notDrawing );
        graphicList()->addAsLast( *iGraphic );
      break;
      case freehand:
        ((IGPolygon*)iGraphic)->addPoint( point );
        iGraphic->setGraphicBundle( currentBundle );
        iGraphic->drawOn( gc );
        setDrawState( notDrawing );
        graphicList()->addAsLast( *iGraphic );
      break;
      case rectangle:
      {
        IRectangle rc(((IGRectangle*)iGraphic)->enclosingRect());
        rc.sizeTo( rc.size() + point - previousPt );
        ((IGRectangle*)iGraphic)->setEnclosingRect( rc );
        iGraphic->setGraphicBundle( currentBundle );
        iGraphic->drawOn( gc );
        setDrawState( notDrawing );
        graphicList()->addAsLast( *iGraphic );
      }
      break;
      case ellipse:
      {
        IRectangle rc(((IGEllipse*)iGraphic)->enclosingRect());
        rc.sizeTo( rc.size() + point - previousPt );
        ((IGEllipse*)iGraphic)->setEnclosingRect( rc );

        iGraphic->setGraphicBundle( currentBundle );
        iGraphic->drawOn( gc );
        setDrawState( notDrawing );
        graphicList()->addAsLast( *iGraphic );
      }
      break;
      case polyline:
      case polygon:
        previousPt = point;
        ((IGPolyline*)iGraphic)->setPoint(
                         ((IGPolyline*)iGraphic)->numberOfPoints()-1, point );
        setDrawState( waitingForInput );
      break;
      case arc:
      if ( pointCount == 2 )
      {
        ((IG3PointArc*)iGraphic)->setIntermediatePoint( point );
        gc.setMixMode( IGraphicBundle::xor ).setPenColor( IColor::white );
        IGLine tempLine( ((IG3PointArc*)iGraphic)->startingPoint(), previousPt );
        tempLine.drawOn( gc );
        tempLine.setEndingPoint( point );
        tempLine.drawOn( gc );
        setDrawState( waitingForInput );
      }
      else if ( pointCount == 3 )
      {
        gc.setMixMode( IGraphicBundle::xor ).setPenColor( IColor::white );
        iGraphic->drawOn( gc );
        ((IG3PointArc*)iGraphic)->setEndingPoint( point );
        iGraphic->setGraphicBundle( currentBundle );
        iGraphic->drawOn( gc );
        setDrawState( notDrawing );
        graphicList()->addAsLast( *iGraphic );
        pointCount = 0;
      }
      break;
      case pie:
      case chord:
      if ( pointCount == 2 )
      {
        gc.setMixMode( IGraphicBundle::xor ).setPenColor( IColor::white );
        setDrawState( waitingForInput );
        IPoint centerPt(((IGPie*)iGraphic)->enclosingRect().center());

        ((IGPie*)iGraphic)->setStartAngle( angleFromPoints( centerPt, point ));

        unsigned a(abs(centerPt.x()) - abs(point.x()));
        unsigned b(abs(centerPt.y()) - abs(point.y()));

        unsigned long radius((unsigned long)sqrtl(a*a + b*b));

        ((IGPie*)iGraphic)->setEnclosingRect(
           ((IGPie*)iGraphic)->enclosingRect().expandBy(radius));
      }
      else if ( pointCount == 3 )
      {
        gc.setMixMode( IGraphicBundle::xor ).setPenColor( IColor::white );
        iGraphic->drawOn( gc );

        double sweep(angleFromPoints(
                              ((IGPie*)iGraphic)->enclosingRect().center(), point ));

        if ( sweep < ((IGPie*)iGraphic)->startAngle() )
          ((IGPie*)iGraphic)->setSweepAngle( 360.0 -
                                ( ((IGPie*)iGraphic)->startAngle() - sweep ));
        else
          ((IGPie*)iGraphic)->setSweepAngle( sweep -
                                            ((IGPie*)iGraphic)->startAngle());

        iGraphic->setGraphicBundle( currentBundle );
        iGraphic->drawOn( gc );
        setDrawState( notDrawing );
        graphicList()->addAsLast( *iGraphic );
        pointCount = 0;
      }
      break;
      case text:
      {
        IString input;

        IDynamicLinkLibrary reslib("CPPWV53R");

        if (point.x() % 2)
          input = reslib.loadString( STRING_SAMPLE1 );
        else if ((point.y() % 5)==1)
          input = reslib.loadString( STRING_SAMPLE3 );
        else if ((point.y() % 5)==3)
          input = reslib.loadString( STRING_SAMPLE4 );
        else
          input = reslib.loadString( STRING_SAMPLE2 );

        IGString* text = new IGString( input.x2c(), point, currentFont());
//      IGString* text = new IGString( "Doodle", point, currentFont());
        text->rotateBy( 10.0, point );
        text->setGraphicBundle( currentBundle );
        text->drawOn( gc );
        setDrawState( notDrawing );
        graphicList()->addAsLast( *text );
      }
      break;
      case bitmap:
      {
        IGBitmap *bmp;
//      if (bitmapFileName().length() > 0)
//      {
//        bmp = new IGBitmap(bitmapFileName());
//      }

        // Select a bitmap to load
        IDynamicLinkLibrary reslib("CPPWV53R");

        if (point.x() % 2)
          bmp = new IGBitmap(reslib.loadBitmap( BITMAP_SAMPLE1 ));
        else if ((point.y() % 5)==1)
          bmp = new IGBitmap(reslib.loadBitmap( BITMAP_SAMPLE3 ));
        else if ((point.y() % 5)==3)
          bmp = new IGBitmap(reslib.loadBitmap( BITMAP_SAMPLE4 ));
        else
          bmp = new IGBitmap(reslib.loadBitmap( BITMAP_SAMPLE2 ));

        bmp->moveTo( point );
        bmp->drawOn( gc );
        setDrawState( notDrawing );
        graphicList()->addAsLast( *bmp );
      }
      break;
    } /* endswitch */
  } /* endif */
  else  // not drawing
  {
    switch (currentObj)
    {
      case move:
        if (moveGraphic && capturePointer)
        {
          moveRect.translateBy( point - previousPt );
          moveRect.drawOn( gc );
          moveRect.resetTransformMatrix();
          this->refresh( moveRect.boundingRect(gc).expandBy(2) );
          moveGraphic->translateBy( point - startingPt );
          moveGraphic->drawOn( gc );
          moveGraphic = 0;
          capturePointer(false);
        }
      break;
    }
  }
  return *this;
}

/*------------------------------------------------------------------------------
| DrawingArea::button1DoubleClick                                              |
|                                                                              |
| Handle button 1 up double click events.  In the case of polyline and polygon |
| a double click indicates the user has finished adding data points to the     |
| object.                                                                      |
------------------------------------------------------------------------------*/
DrawingArea& DrawingArea::button1DoubleClick( const IPoint& point )
{
  if (drawState() == waitingForInput )
  {
    switch (currentObj)
    {
      case polyline:
      {
        iGraphic->drawOn( gc );
        iGraphic->setGraphicBundle( currentBundle );
        iGraphic->drawOn( gc );
        setDrawState( notDrawing );
        graphicList()->addAsLast( *iGraphic );
      }
      break;
      case polygon:
      {
        ((IGPolyline*)iGraphic)->IGPolyline::drawOn( gc );
        iGraphic->setGraphicBundle( currentBundle );
        iGraphic->drawOn( gc );
        setDrawState( notDrawing );
        graphicList()->addAsLast( *iGraphic );
      }
      break;
    }
  }
  return *this;
}

/*------------------------------------------------------------------------------
| DrawingArea::button2Down                                                     |
|                                                                              |
| Determine the object under the mouse and start moving.                       |
------------------------------------------------------------------------------*/
DrawingArea& DrawingArea::button2Down( const IPoint& point )
{
  if (drawState() == notDrawing)
  {
    moveGraphic = graphicList()->topGraphicUnderPoint( point, gc );
    if ( moveGraphic )
    {
      moveRect.setEnclosingRect(moveGraphic->boundingRect( gc ));
      previousPt = point;
      startingPt = point;
      capturePointer();
    }
  }
  return *this;
}

/*------------------------------------------------------------------------------
| DrawingArea::button2Up                                                       |
|                                                                              |
------------------------------------------------------------------------------*/
DrawingArea& DrawingArea::button2Up( const IPoint& point )
{
  if (moveGraphic)
  {
    moveRect.translateBy( point - previousPt );
    moveRect.drawOn( gc );
    moveRect.resetTransformMatrix();
    this->refresh( moveRect.boundingRect(gc).expandBy(2) );
    moveGraphic->translateBy( point - startingPt );
    moveGraphic->drawOn( gc );
    moveGraphic = 0;
    capturePointer(false);
  }
  return *this;
}

/*------------------------------------------------------------------------------
| DrawingArea::mouseMoved                                                      |
|                                                                              |
| Handle button 1 down mouse move events.  This allows data points to be       |
| moved while the object is drawn with a rubber band effect.                   |
------------------------------------------------------------------------------*/
Boolean DrawingArea::mouseMoved( IMouseEvent& event )
{
  IPoint point(event.mousePosition());
  if ( hasPointerCaptured() )
  {
    IRectangle windowRect(this->rect());
    windowRect.moveTo(IPoint(0,0));
    if (!windowRect.contains(point))
    {
      if ((short)point.x() < (short)windowRect.left())
        point.setX(windowRect.left());
      else if ((short)point.x() > (short)windowRect.right())
        point.setX(windowRect.right());
      else if ((short)point.y() < (short)windowRect.bottom())
        point.setY(windowRect.bottom());
      else if ((short)point.y() > (short)windowRect.top())
        point.setY(windowRect.top());

      IPoint mapPt( IWindow::mapPoint( point,
                                       this->handle(),
                                       IWindow::desktopWindow()->handle()));

      IWindow::movePointerTo( mapPt );
    }
  }

  // If we're not moving an object
  if (!moveGraphic)
  {
    if (( drawState() == drawing ) || ( drawState() == waitingForInput ))
    {
      switch (currentObj)
      {
        case move:
        break;
        case eraser:
        break;
        case stylecan:
        break;
        case line:
          ((IGLine*)iGraphic)->drawOn( gc );
          ((IGLine*)iGraphic)->setEndingPoint( point );
          ((IGLine*)iGraphic)->drawOn( gc );
        break;
        case freehand:
          ((IGPolygon*)iGraphic)->addPoint( point );
          ((IGPolyline*)iGraphic)->IGPolyline::drawOn( gc );
        break;
        case rectangle:
        {
          IRectangle rc(((IGRectangle*)iGraphic)->enclosingRect());
          iGraphic->drawOn( gc );
          rc.sizeTo( rc.size() + point - previousPt );
          ((IGRectangle*)iGraphic)->setEnclosingRect( rc );
          iGraphic->drawOn( gc );
          previousPt = point;
        }
        break;
        case ellipse:
        {
          iGraphic->drawOn( gc );
          IRectangle rc(((IGEllipse*)iGraphic)->enclosingRect());
          rc.sizeTo( rc.size() + point - previousPt );
          ((IGEllipse*)iGraphic)->setEnclosingRect( rc );
          iGraphic->drawOn( gc );
          previousPt = point;
        }
        break;
        case polyline:
        case polygon:
          ((IGPolyline*)iGraphic)->IGPolyline::drawOn( gc );
          ((IGPolyline*)iGraphic)->setPoint(
                           ((IGPolyline*)iGraphic)->numberOfPoints()-1, point );
          ((IGPolyline*)iGraphic)->IGPolyline::drawOn( gc );
        break;
        case arc:
          if (drawState() != waitingForInput)
          {
            if ( pointCount == 2 )
            {
              IGLine tempLine( ((IG3PointArc*)iGraphic)->startingPoint(), previousPt );
              tempLine.drawOn( gc );
              tempLine.setEndingPoint( point );
              tempLine.drawOn( gc );
              previousPt = point;
            } else if ( pointCount == 3 ) {
              iGraphic->drawOn( gc );
              ((IG3PointArc*)iGraphic)->setEndingPoint( point );
              iGraphic->drawOn( gc );
            }
          } /* endif */
        break;
        case pie:
        case chord:
          if (drawState() != waitingForInput)
          {
            if ( pointCount == 2 )
            {
              IGLine tempLine( ((IGPie*)iGraphic)->enclosingRect().center(), previousPt );
              tempLine.drawOn( gc );
              tempLine.setEndingPoint( point );
              tempLine.drawOn( gc );
              previousPt = point;
            } else if ( pointCount == 3 ) {
              iGraphic->drawOn( gc );
              double sweep(angleFromPoints( ((IGPie*)iGraphic)->enclosingRect().center(), point ));
              if ( sweep < ((IGPie*)iGraphic)->startAngle() )
                ((IGPie*)iGraphic)->setSweepAngle( 360.0 -
                                    ( ((IGPie*)iGraphic)->startAngle() - sweep ));
              else
                ((IGPie*)iGraphic)->setSweepAngle( sweep -
                                                ((IGPie*)iGraphic)->startAngle());
              iGraphic->drawOn( gc );
            }
          } /* endif */
        break;
      } /* endswitch */
    }
  }
  else  // We are moving a graphic
  {
    moveRect.drawOn( gc );
    moveRect.translateBy( point - previousPt );
    moveRect.drawOn( gc );
    previousPt = point;
  }
  return false;
}

/*------------------------------------------------------------------------------
| DrawingArea::setDrawState                                                    |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
DrawingArea& DrawingArea::setDrawState( const DrawState newState )
{
  dState = newState;
  if (dState == drawing)
  {
    if (!hasPointerCaptured())
      capturePointer();
  }
  else if (dState == notDrawing)
    capturePointer(false);
  return *this;
}

/*------------------------------------------------------------------------------
| DrawingArea::setFont                                                         |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
DrawingArea& DrawingArea::setCurrentFont( const IFont& font )
{
  currentfont = font;
  return *this;
}

/*------------------------------------------------------------------------------
| DrawingArea::font                                                            |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
IFont DrawingArea::currentFont( ) const
{
  return currentfont;
}

