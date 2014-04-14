#ifndef DAREA_HPP
#define DAREA_HPP
/******************************************************************************
* .FILE:        darea.hpp                                                     *
*                                                                             *
* .DESCRIPTION: Header file for the class, DrawingArea                        *
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

#include <iframe.hpp>           //Include IFrameWindow Class Header
#include <isizehdr.hpp>
#include <icmdhdr.hpp>
#include <igrafctx.hpp>
#include <igbundle.hpp>
#include <idrawcv.hpp>
#include <imndihdr.hpp>
#include <imndievt.hpp>
#include <ireslib.hpp>
#include <imoushdr.hpp>
#include <imousevt.hpp>
#include <ifont.hpp>
#include <istring.hpp>
#include <igrect.hpp>
#include <iflyhhdr.hpp>
#include "darea.h"

//**************************************************************************
// Class:   DrawingArea                                                    *
//                                                                         *
// Purpose: Subclass of IDrawingCanvas.  Class contains the handlers       *
//          necessary for interactive drawing of the graphic objects.      *
//                                                                         *
//**************************************************************************
class DrawingArea : public IDrawingCanvas,
                    public IMouseHandler
{
public:
  DrawingArea  ( unsigned long id,
                 IWindow* parent,
                 IWindow* owner,
                 const IRectangle& rect = IRectangle() );
virtual
  ~DrawingArea ( );

enum DrawState {
  drawing,
  waitingForInput,
  notDrawing
  };

DrawingArea
  &setDrawState        ( const DrawState newState = drawing );
DrawState
  drawState            ( ) const { return dState; }

DrawingArea
  &setBitmapFileName   ( const IString& bitmapFile )
                         { currentBitmap = bitmapFile;
                           return *this; }
IString
  bitmapFileName       ( ) const
                         { return currentBitmap; }

enum DrawObject {
  move = POINTER_MOVE,
  line,
  freehand,
  rectangle,
  ellipse,
  polyline,
  polygon,
  arc,
  pie,
  chord,
  text,
  bitmap,
  stylecan,
  eraser
  };

virtual DrawingArea
  &setDrawObject       ( const DrawObject drawObject )
                         { currentObj = drawObject;
                           if (flyOverHandler)
                             flyOverHandler->setHelpText( handle(),
                                                          IResourceId(FLYOVERTEXT_BLANK),
                                                          IResourceId(currentObj+LONG_OFFSET));
                           return *this; }
virtual DrawObject
  drawObject           ( ) const {return currentObj;}

virtual IGraphicBundle
  &graphicBundle       ( ) { return currentBundle; }

virtual DrawingArea
  &setCurrentFont      ( const IFont& font );
virtual IFont
  currentFont          ( ) const;

virtual void
   setColor            ( const IColor* color )
                         { graphicBundle().setFillColor(*color); }

virtual void
   setFlyOverHandler   ( IFlyOverHelpHandler* handler)
                         { flyOverHandler = handler;
                           if (flyOverHandler)
                             flyOverHandler->setHelpText( handle(),
                                                          IResourceId(FLYOVERTEXT_BLANK),
                                                          IResourceId(currentObj+LONG_OFFSET));
                         }

virtual void
   setPenColor         ( const IColor* color )
                         { graphicBundle().setPenColor(*color); }
virtual void
   setWidth            ( unsigned long width )
                         { graphicBundle().setPenWidth(width); }

virtual void
   setDrawStyle        ( short value = 0 )
        { switch(value)
          {
            case -1:    // frame
              graphicBundle().setDrawOperation(IGraphicBundle::frame);
              break;
            case 0:     // frame & fill
              graphicBundle().setDrawOperation(IGraphicBundle::fillAndFrame);
              break;
            case 1:     // fill
              graphicBundle().setDrawOperation(IGraphicBundle::fill);
              break;
          }
        }

protected:

virtual Boolean
  mouseMoved           ( IMouseEvent&        event ),
  mouseClicked         ( IMouseClickEvent&   event ),
  mousePointerChange   ( IMousePointerEvent& event );

virtual DrawingArea
  &button1Down         ( const IPoint&       point ),
  &button1Up           ( const IPoint&       point ),
  &button1DoubleClick  ( const IPoint&       point ),
  &button2Down         ( const IPoint&       point ),
  &button2Up           ( const IPoint&       point );

private:
  IGraphicContext    gc;
  IFont              currentfont;
  IGraphicBundle     currentBundle;
  IString            currentBitmap;
  DrawState          dState;
  DrawObject         currentObj;
  IGraphic*          iGraphic;
  IGraphic*          moveGraphic;
  IGRectangle        moveRect;
  IPoint             startingPt;
  IPoint             previousPt;
  IPoint             tempPt;
  unsigned long      pointCount;
  IPointerHandle     ptrCurrent;
  IPointerHandle     ptrLine;
  IPointerHandle     ptrFreehand;
  IPointerHandle     ptrRectangle;
  IPointerHandle     ptrEllipse;
  IPointerHandle     ptrPolyline;
  IPointerHandle     ptrPolygon;
  IPointerHandle     ptrArc;
  IPointerHandle     ptrPie;
  IPointerHandle     ptrChord;
  IPointerHandle     ptrText;
  IPointerHandle     ptrBitmap;
  IPointerHandle     ptrStyleCan;
  IPointerHandle     ptrEraser;
  IFlyOverHelpHandler*  flyOverHandler;
};

#endif

