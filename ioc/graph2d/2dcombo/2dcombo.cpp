// Revision: 84  1.10.1.5  samples/graph2d/2dcombo/2dcombo.cpp, ocsamples-L1, ioc.v400, 981111  
/******************************************************************************/
/* 2DCOMBO SAMPLE PROGRAM -- Version 1: Class Implementation (2DCOMBO.CPP)    */
/******************************************************************************/

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

#include "2dcombo.h"
#include "2dcombo.hpp"

#include <igraph2d.hpp>
#include <igrport.hpp>
#include <iexgrprt.hpp>
#include <ibcolor.hpp>
#include <igloop2d.hpp>
#include <iimage.hpp>
#include <icolor.hpp>
#include <igraftxt.hpp>
#include <istyles.hpp>
#include <istylset.hpp>

#include <math.h>
#include <ifont.hpp>

//*************************************************************************
// Helper functions for constructing the bar chart                        *
//*************************************************************************

/*
 * function: GetBar
 *
 * Parameters:
 *   rect : indicates the height, and width of the bar
 *   color: indicates the color of the bar
 *
 * Return value: returns the bar (3D) in the form of a graphic group
 *
 * Purpose: constructs a 3D bar from the specified rectangle and color
 *
*/

IGraphicGroup *GetBar(IGRect2D rect, IBaseColor color)
{

  // initialize the empty bar
  IGraphicGroup *bar = new IGraphicGroup();

  // 135 degrees = 2.3562 Radians
  IGPoint2D translator(rect.width()*cos(2.3562), (-1)*rect.width()*sin(2.3562));

  // construct the main rectangle
  IGPolygon2D* rectPanel = new IGPolygon2D(rect);

  // construct the left panel
  IGPolygon2D* leftPanel = new IGPolygon2D(4);
  leftPanel->setPoint(0, rect.bottomLeft());
  leftPanel->setPoint(1, rect.topLeft());
  leftPanel->setPoint(2, rect.topLeft()+translator);
  leftPanel->setPoint(3, rect.bottomLeft()+translator);

  // construct the top panel
  IGPolygon2D* topPanel = new IGPolygon2D(4);
  topPanel->setPoint(0, rect.topLeft());
  topPanel->setPoint(1, rect.topLeft()+translator);
  topPanel->setPoint(2, rect.topRight()+translator);
  topPanel->setPoint(3, rect.topRight());

  // compute the colors for the left and top panels

  // using the GIntensity group of member function just to test them...boy, they are clumsy to use!
  GIntensity intensity;
  IBaseColor leftColor;
  color.redMix(intensity); intensity *= 0.7; leftColor.setRed(intensity);
  color.greenMix(intensity); intensity *= 0.7; leftColor.setGreen(intensity);
  color.blueMix(intensity); intensity *= 0.7; leftColor.setBlue(intensity);

  IBaseColor topColor;
  color.redMix(intensity); intensity *= 0.85; topColor.setRed(intensity);
  color.greenMix(intensity); intensity *= 0.85; topColor.setGreen(intensity);
  color.blueMix(intensity); intensity *= 0.85; topColor.setBlue(intensity);

  IBaseColor frameColor;        // default black color

  // construct the bar by adding the panels to the graphic group
  bar->adoptFirst(new IPolygon(rectPanel, new IGrafBundle(color,frameColor)));
  bar->adoptLast(new IPolygon(leftPanel, new IGrafBundle(leftColor,frameColor)));
  bar->adoptLast(new IPolygon(topPanel, new IGrafBundle(topColor,frameColor)));
  return bar;

}

/*
 * function: GetBase
 *
 * Parameters:
 *   left  : the line indicating the left side of the base
 *   bottom: the line indicating the bottom side of the base
 *   width : indicates the width of the bars used for the bar chart
 *
 * Return value: returns the base (3D) of the bar chart in graphic group form
 *
 * Purpose: constructs a 3D base for use with a bar chart
 *
*/

IGraphicGroup *GetBase(IGLine2D left, IGLine2D bottom, GCoordinate width)
{

  // initialize an empty base
  IGraphicGroup *base = new IGraphicGroup();

  // 135 degrees = 2.3562 Radians
  IGPoint2D translator(width*cos(2.3562), (-1)*width*sin(2.3562));

  // construct the bottom panel
  IGPolygon2D baseBottom;
  baseBottom.append(left.startPoint());
  baseBottom.append(left.endPoint());
  baseBottom.append(left.endPoint()+translator);
  baseBottom.append(left.startPoint()+translator);

  // construct the left panel
  IGPolygon2D baseLeft;
  baseLeft.append(bottom.startPoint());
  baseLeft.append(bottom.endPoint());
  baseLeft.append(bottom.endPoint()+translator);
  baseLeft.append(bottom.startPoint()+translator);

  IBaseColor black;
  // construct the base by adding the panels to the graphic group
  IGPolygon2D* fPoly = new IGPolygon2D(baseBottom);
  base->adoptFirst(new IPolygon(fPoly, new IGrafBundle(IBaseColor(128),black)));

  fPoly = new IGPolygon2D(baseLeft);
  base->adoptFirst(new IPolygon(fPoly, new IGrafBundle(IBaseColor(77),black)));

  return base;
}

//*************************************************************************
// Class MainWindow: method definitions                                   *
//*************************************************************************

/*
 * function: MainWindow::MainWindow
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
    | IFrameWindow::animated,           //  set to show with "animation"
    windowId),                          //  Main Window ID
    drawingArea( WND_DRAW, this, this ),
    menuBar( WND_MAIN, this)
{

  // start up the event handlers
  ICommandHandler::handleEventsFor(this);
#ifdef IC_WIN
        IPaintHandler::handleEventsFor(this);
#else
        IPaintHandler::handleEventsFor(&drawingArea);
#endif

  // specify upper left coordinate system
  ICoordinateSystem::setApplicationOrientation(ICoordinateSystem::originUpperLeft);

  // set the defaults
  drawSetting = ID_AREA;
  menuBar.checkItem(drawSetting);
  menuBar.checkItem(ID_UPPER);

  setClient(&drawingArea);

  setFocus();
  show();
}

/*
 * function: MainWindow::~MainWindow
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

  // shut down the event handlers
  ICommandHandler::stopHandlingEventsFor(this);
  IPaintHandler::stopHandlingEventsFor(this);

}

/*
 * function: MainWindow::command
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

  switch (event.commandId()) {

    // sample selections
    case ID_AREA:
    case ID_LOOP:
    case ID_BEZIER:
    case ID_CONIC:
    case ID_NURB:
    case ID_TRANSFERMODE:
    case ID_IMAGE:
    case ID_BARCHART:
    case ID_PIECHART:
    case ID_TEXT:
    case ID_PATTERN:
    {

      // update the checked menu item
      menuBar.uncheckItem(drawSetting)
             .checkItem(drawSetting = event.commandId());

      fProcessed = true;

      // update the display
#ifndef IC_MOTIF
                refresh();
#else
                drawingArea.refresh();
#endif

      break;

    }

    case ID_UPPER: {

      ICoordinateSystem::setApplicationOrientation(ICoordinateSystem::originUpperLeft);
      menuBar.uncheckItem(ID_LOWER)
             .checkItem(ID_UPPER);
#ifndef IC_MOTIF
                refresh();
#else
                drawingArea.refresh();
#endif
      break;

    }

    case ID_LOWER: {

      ICoordinateSystem::setApplicationOrientation(ICoordinateSystem::originLowerLeft);
      menuBar.uncheckItem(ID_UPPER)
             .checkItem(ID_LOWER);
#ifndef IC_MOTIF
                refresh();
#else
                drawingArea.refresh();
#endif
      break;

    }

  }

  return fProcessed;

}

/*
 * function: MainWindow::paintWindow
 *
 * Parameters:
 *   event: identifies the type of paint event to be processed
 *
 * Return value: returns true when the event is processed
 *
 * Purpose: handles the rendering of graphics to the screen, and handles
 *          repaint updates
 *
*/

bool MainWindow::paintWindow( IPaintEvent& event )
{

  bool fProcessed = false;
  // clear the drawing area
#ifdef IC_WIN
        drawingArea.refresh(IWindow::paintAllImmediate);
#else
        event.clearBackground( IColor::white );
#endif

  IManagedPresSpaceHandle presSpace(&drawingArea);
  IExtendedRootGrafPort *myDisplayPort= new IExtendedRootGrafPort(presSpace);

  switch (drawSetting) {

    // handle pen width selections
    case ID_AREA: {  // handle area sample

      // construct a green (fill color) and blue (frame color) bundle
      IFillAndFrameBundle bundle(IBaseColor(  0,255,  0),IBaseColor(  0,  0,255));

      // construct the four areas to be shown with there respective operations
      IGArea area1(IGArea(IGRect2D(10,10,110,110)) + IGArea(IGRect2D(60,60,160,160)));
      IGArea area2(IGArea(IGRect2D(310,10,410,110)) - IGArea(IGRect2D(360,60,460,160)));
      IGArea area3(IGArea(IGRect2D(10,210,110,310)) * IGArea(IGRect2D(60,260,160,360)));
      IGArea area4(IGArea(IGRect2D(310,210,410,310)) ^ IGArea(IGRect2D(360,260,460,360)));

      // render the areas to the display
      myDisplayPort->draw(area1, bundle);
      myDisplayPort->draw(area2, bundle);
      myDisplayPort->draw(area3, bundle);
      myDisplayPort->draw(area4, bundle);
      break;

    }

    case ID_LOOP: {  // handle loop sample

      // construct a pie  Shah
      IGLoop2D loop1(IGPie2D(IGEllipse2D(IGRect2D(10,10,210,210)),180,45));

      // construct a chord
      IGLoop2D loop2(IGArcThrough3Points(IGPoint2D(350,10),IGPoint2D(450,110),IGPoint2D(250,110)));

      // construct a bezier loop
      IGLoop2D loop3(IGCurve2D(IGPoint2D(10,400),IGPoint2D(10,250),IGPoint2D(210,400),IGPoint2D(210,250)));

      // construct a nurb loop
      IGRPoint2DArray aLoopArray(4);
      aLoopArray.setPoint(0,IGRPoint2D(250,250,1));
      aLoopArray.setPoint(1,IGRPoint2D(270,450,1));
      aLoopArray.setPoint(2,IGRPoint2D(400,300,1));
      aLoopArray.setPoint(3,IGRPoint2D(295,275,1));
      IGLoop2D loop4(4, aLoopArray);

      // construct a blue (fill) and green (frame) bundle
      IBaseColor color1(  0, 255,   0);
      IBaseColor color2(  0,   0, 255);
      IFillAndFrameBundle bundle(color1, color2);
          //To use the differenct pen styles instead of the default one, one need to do the following
          //instead of instantiating a IFillAndFrameBundle as above:
      //IGrafBundle bundle(color1, color2);
          // select one of these pen styles:
          //bundle.setFramePen(IPen(IPen::kDashed));
          //bundle.setFramePen(IPen(IPen::kDot));
          //bundle.setFramePen(IPen(IPen::kDashDot));
          //bundle.setFramePen(IPen(IPen::kDashDotDot, 5));
          //bundle.setFramePen(IPen(IPen::kInvisible));

      // render the loops to the display
      myDisplayPort->draw(loop1,bundle);
      myDisplayPort->draw(loop2,bundle);

      // construct a green (fill color) and blue (frame color) bundle
      IFillAndFrameBundle another(color2, color1);
          //To use the differenct patterns instead of the default one, one need to do the following
          //instead of instantiating a IFillAndFrameBundle as above:
      //IGrafBundle another(color2, color1);
          //another.setFramePen(IPen(IPen::kDashDotDot, 20));
          //another.setFramePaint(IPaint(color1, IMaskPattern::kDiagonalCross));
          // select one of these patterns:
          //another.setFillPaint(IPaint(color2, IMaskPattern::kDiagonalDown));
          //another.setFillPaint(IPaint(color2, IMaskPattern::kCross));
          //another.setFillPaint(IPaint(color2, IMaskPattern::kDiagonalCross));
          //another.setFillPaint(IPaint(color2, IMaskPattern::kDiagonalUp));
          //another.setFillPaint(IPaint(color2, IMaskPattern::kHorizontal));
          //another.setFillPaint(IPaint(color2, IMaskPattern::kVertical));

      myDisplayPort->draw(loop3,another);
      myDisplayPort->draw(loop4,another);

          IGrafMatrix xlate(IGPoint2D(10, 0));
          ILinkedGrafPort xport(myDisplayPort, kModelMatrix, &xlate);
      xport.draw(loop4, bundle);

      break;

    }

    case ID_BEZIER: {  // handle bezier sample

      // construct four different types of bezier curves
      IGCurve2D curve1(IGPoint2D(50,200),IGPoint2D(-50,0),IGPoint2D(350,0),IGPoint2D(250,200));
      IGCurve2D curve2(IGPoint2D(300,200),IGPoint2D(600,0),IGPoint2D(200,0),IGPoint2D(500,200));
      IGCurve2D curve3(IGPoint2D(50,350),IGPoint2D(100,250),IGPoint2D(200,450),IGPoint2D(250,350));
      IGCurve2D curve4(IGPoint2D(300,350),IGPoint2D(450,450),IGPoint2D(350,250),IGPoint2D(500,350));

      // render them to the display using the default bundle
      myDisplayPort->draw(curve1);
      myDisplayPort->draw(curve2);
      myDisplayPort->draw(curve3);
      myDisplayPort->draw(curve4);

      break;

    }

    case ID_CONIC: {  // handle conics sample

      unsigned long n = 0;

      // construct and show a 3 point arc
      IGPoint2D p0(10,25);
      IGPoint2D p1(50,30);
      IGPoint2D p2(100,75);
      IGCurve2D curve1 = IGArcThrough3Points(p0, p1, p2);
      myDisplayPort->draw(curve1);

      // construct and show a conic end center end with direction set to false
      // (false is the default)
      p0 = IGPoint2D(210,25);
      p1 = IGPoint2D(250,30);
      p2 = IGPoint2D(300,75);
      IGCurve2D curve2 = IGConicEndCenterEnd(p0, p1, p2);
      myDisplayPort->draw(curve2);

      // construct and show a conic end center end with direction set to true
      // (same curve as previous one, only draws the other part of the conic)
      p0 = IGPoint2D(410,65);
      p1 = IGPoint2D(450,70);
      p2 = IGPoint2D(500,115);
      IGCurve2D curve3 = IGConicEndCenterEnd(p0, p1, p2, true);
      myDisplayPort->draw(curve3);

      // construct and draw a hermite spline
      p0 = IGPoint2D(10,125);
      p1 = IGPoint2D(50,130);
      p2 = IGPoint2D(100,175);
      IGPoint2D p3(125,250);
      IGPoint2DArray aPointArray(4);
      aPointArray.setPoint(0, p0);
      aPointArray.setPoint(1, p1);
      aPointArray.setPoint(2, p2);
      aPointArray.setPoint(3, p3);
      IGCurve2D curve4 = IGHermiteSpline(aPointArray);
      myDisplayPort->draw(curve4);

      // construct and draw a cardinal spline (tension 0)
      p0 = IGPoint2D(210,125);
      p1 = IGPoint2D(250,130);
      p2 = IGPoint2D(300,175);
      p3 = IGPoint2D(325,250);
      aPointArray.setPoint(0, p0);
      aPointArray.setPoint(1, p1);
      aPointArray.setPoint(2, p2);
      aPointArray.setPoint(3, p3);
      IGCurve2D curve5 = IGCardinalSpline(aPointArray,1.0);
      myDisplayPort->draw(curve5);

      // construct and draw a cardinal spline (tension 1)
      p0 = IGPoint2D(410,125);
      p1 = IGPoint2D(450,130);
      p2 = IGPoint2D(500,175);
      p3 = IGPoint2D(525,250);
      aPointArray.setPoint(0, p0);
      aPointArray.setPoint(1, p1);
      aPointArray.setPoint(2, p2);
      aPointArray.setPoint(3, p3);
      IGCurve2D curve6 = IGCardinalSpline(aPointArray,0.0);
      myDisplayPort->draw(curve6);

      // construct and draw a tension spline (tension 1, basis 1)
      p0 = IGPoint2D(10,225);
      p1 = IGPoint2D(50,230);
      p2 = IGPoint2D(100,275);
      p3 = IGPoint2D(125,350);
      aPointArray.setPoint(0, p0);
      aPointArray.setPoint(1, p1);
      aPointArray.setPoint(2, p2);
      aPointArray.setPoint(3, p3);
      IGCurve2D curve7 = IGTensionSpline(aPointArray,1.0,1.0);
      myDisplayPort->draw(curve7);

      // construct and draw a tension spline (tension 0, basis 1)
      p0 = IGPoint2D(110,225);
      p1 = IGPoint2D(160,230);
      p2 = IGPoint2D(200,275);
      p3 = IGPoint2D(225,350);
      aPointArray.setPoint(0, p0);
      aPointArray.setPoint(1, p1);
      aPointArray.setPoint(2, p2);
      aPointArray.setPoint(3, p3);
      IGCurve2D curve8 = IGTensionSpline(aPointArray,0.0,1.0);
      myDisplayPort->draw(curve8);

      // construct and draw a tension spline (tension 1, basis 0)
      p0 = IGPoint2D(235,225);
      p1 = IGPoint2D(275,230);
      p2 = IGPoint2D(325,275);
      p3 = IGPoint2D(350,350);
      aPointArray.setPoint(0, p0);
      aPointArray.setPoint(1, p1);
      aPointArray.setPoint(2, p2);
      aPointArray.setPoint(3, p3);
      IGCurve2D curve9 = IGTensionSpline(aPointArray,1.0,0.0);
      myDisplayPort->draw(curve9);

      // construct and draw a tension spline (tension 0, basis 0)
      p0 = IGPoint2D(360,225);
      p1 = IGPoint2D(400,230);
      p2 = IGPoint2D(450,275);
      p3 = IGPoint2D(475,350);
      aPointArray.setPoint(0, p0);
      aPointArray.setPoint(1, p1);
      aPointArray.setPoint(2, p2);
      aPointArray.setPoint(3, p3);
      IGCurve2D curve10 = IGTensionSpline(aPointArray,0.0,0.0);
      myDisplayPort->draw(curve10);

      break;
    }

    case ID_NURB: {  // handle nurb sample

      // construct the control points
      IGRPoint2DArray aCurveArray(7);
      aCurveArray.setPoint(0,IGRPoint2D(175,125,1));
      aCurveArray.setPoint(1,IGRPoint2D(195,200,1));
      aCurveArray.setPoint(2,IGRPoint2D(245,175,1));
      aCurveArray.setPoint(3,IGRPoint2D(220,150,1));
      aCurveArray.setPoint(4,IGRPoint2D(250,150,1));
      aCurveArray.setPoint(5,IGRPoint2D(275,100,1));
      aCurveArray.setPoint(6,IGRPoint2D(260,50,1));

      // construct the knot vector
      static const GCoordinate knotArray[10] = { 0,0,0,1,1,2,2,3,3,3 };
      IRawArray<GParametric> knots(10);
      for(long p = 0; p < 10; p++)
        knots.setValue(p,knotArray[p]);

      // construct and render the nurb
      IGCurve2D nurb(3, aCurveArray, knots);
      myDisplayPort->draw(nurb);

      break;
    }

    case ID_TRANSFERMODE: {  // handle transfer mode sample

      // construct to different color paints
      IPaint paint1(IBaseColor(  0,  0,255));
      IPaint paint2(IBaseColor(  0,255,  0));

      // construct to fill bundles from the above paints
      IGrafBundle bundle1(paint1, IAttributeState::kFill);
      IGrafBundle bundle2(paint2, IAttributeState::kFill);

      // draw two overlapping rectangles in source copy mode
      bundle1.setFillTransferMode(IColorTransferMode(IColorTransferMode::kSourceCopy));
      bundle2.setFillTransferMode(IColorTransferMode(IColorTransferMode::kSourceCopy));

      myDisplayPort->draw(IGRect2D(10,10,110,110),bundle1);
      myDisplayPort->draw(IGRect2D(60,60,160,160),bundle2);

      // draw two overlapping rectangles in AND mode
      bundle1.setFillTransferMode(IColorTransferMode(IColorTransferMode::kAND));
      bundle2.setFillTransferMode(IColorTransferMode(IColorTransferMode::kAND));

      myDisplayPort->draw(IGRect2D(310,10,410,110),bundle1);
      myDisplayPort->draw(IGRect2D(360,60,460,160),bundle2);

      // draw two overlapping rectangles in XOR mode
      bundle1.setFillTransferMode(IColorTransferMode(IColorTransferMode::kXOR));
      bundle2.setFillTransferMode(IColorTransferMode(IColorTransferMode::kXOR));

      myDisplayPort->draw(IGRect2D(10,210,110,310),bundle1);
      myDisplayPort->draw(IGRect2D(60,260,160,360),bundle2);

      // draw two overlapping rectangles in Inverted XOR mode
      bundle1.setFillTransferMode(IColorTransferMode(IColorTransferMode::kInvertedXOR));
      bundle2.setFillTransferMode(IColorTransferMode(IColorTransferMode::kInvertedXOR));

      myDisplayPort->draw(IGRect2D(310,210,410,310),bundle1);
      myDisplayPort->draw(IGRect2D(360,260,460,360),bundle2);

      break;
    }

    case ID_IMAGE:
    {
           // added test for constructing image from file...
           // IImage perFile(IString("winlogo.bmp"), true, IImage::kNoDither);
           // perFile.translateBy(IGPoint2D(20, 20));
           // perFile.draw(*myDisplayPort);

       // handle image sample
       IImage firstTime(64L,64L,IGImage::k256Color8Bit);
       IGrafPort* theImagePort = firstTime.grafPort();

       // construct to different color paints
       IPaint paint1(IBaseColor(0,0,0));
       IPaint paint2(IBaseColor(255, 255, 255));
       IPaint paint3(IBaseColor(255, 0, 0));

       // construct to fill bundles from the above paints
       IGrafBundle bundle1(paint1,IAttributeState::kFill);
       IGrafBundle bundle2(paint2,IAttributeState::kFill);
       IGrafBundle bundle3(paint3,IAttributeState::kFill);

       theImagePort->draw(IGRect2D(0,0,64,64),bundle1);
       theImagePort->draw(IGRect2D(8,8,56,56),bundle2);
       theImagePort->draw(IGEllipse2D(IGRect2D(8,8,56,56)),bundle3);
       theImagePort->draw(IGEllipse2D(IGRect2D(16,16,48,48)),bundle2);

       ILine diagline(
                        new IGLine2D(IGPoint2D(16, 16), IGPoint2D(48, 48)),
                        new IGrafBundle(paint1,IAttributeState::kFrame));

       diagline.draw(*theImagePort);
       firstTime.draw(*myDisplayPort);

           IGrafBundle* bundle = diagline.orphanBundle();
           bundle->setFrameColor(IBaseColor::kYellow);
           bundle->setFramePen(IPen(IPen::kSolid, 3.0));
           bundle->setFrameEndCap(ICap::kRound);
           diagline.adoptBundle(bundle);
       diagline.transformBy(IGrafMatrix(IGPoint2D(1, -1), IGPoint2D(32, 32)));
       diagline.draw(*theImagePort);
       firstTime.translateBy(IGPoint2D(128,128));
       firstTime.draw(*myDisplayPort);

       IImage secondTime(firstTime);
       secondTime.scaleBy(IGPoint2D(1.5,1.5));
       secondTime.draw(*myDisplayPort);

       break;
    }

    case ID_PATTERN:
        {
       // construct the same image as image demo... but half the size...
       IImage firstTime(32L,32L,IGImage::k256Color8Bit);
       IGrafPort* theImagePort = firstTime.grafPort();

       // construct to fill bundles from the above paints
       IGrafBundle bundle1(IBaseColor::kBlack,IAttributeState::kFill);
       IGrafBundle bundle2(IBaseColor(255, 255, 255),IAttributeState::kFill);
       IGrafBundle bundle3(IBaseColor(255, 0, 0),IAttributeState::kFill);

       theImagePort->draw(IGRect2D(0,0,32,32),bundle1);
       theImagePort->draw(IGRect2D(3,3,29,29),bundle2);
       theImagePort->draw(IGEllipse2D(IGRect2D(3,3,29,29)),bundle3);
       theImagePort->draw(IGEllipse2D(IGRect2D(8,8,24,24)),bundle2);

       ILine diagline(
                        new IGLine2D(IGPoint2D(8, 8), IGPoint2D(24, 24)),
                        new IGrafBundle(IBaseColor::kBlack, IAttributeState::kFrame));

       diagline.draw(*theImagePort);

           IGrafBundle* bundle = diagline.orphanBundle();
           bundle->setFrameColor(IBaseColor::kYellow);
           bundle->setFramePen(IPen(IPen::kSolid, 3.0));
           bundle->setFrameEndCap(ICap::kRound);
           diagline.adoptBundle(bundle);
       diagline.transformBy(IGrafMatrix(IGPoint2D(1, -1), IGPoint2D(16, 16)));
       diagline.draw(*theImagePort);
       //firstTime.translateBy(IGPoint2D(128,128));

           // try the image pattern paint...
           IPaint imagePaint(*firstTime.image(), IGPoint2D::origin());
       IGrafBundle bundlei(IBaseColor::kBlack, IBaseColor::kDarkRed);
           bundlei.setFillPaint(imagePaint);

           // now do the same things as loops demo...
           IGLoop2D loop1(IGPie2D(IGEllipse2D(IGRect2D(10,10,210,210)),180,45));

           IGLoop2D loop2(IGArcThrough3Points(IGPoint2D(350,10),IGPoint2D(450,110),IGPoint2D(250,110)));

           IGLoop2D loop3(IGCurve2D(IGPoint2D(10,400),IGPoint2D(10,250),IGPoint2D(210,400),IGPoint2D(210,250)));

           IGRPoint2DArray aLoopArray(4);
           aLoopArray.setPoint(0,IGRPoint2D(250,250,1));
           aLoopArray.setPoint(1,IGRPoint2D(270,450,1));
           aLoopArray.setPoint(2,IGRPoint2D(400,300,1));
           aLoopArray.setPoint(3,IGRPoint2D(295,275,1));
           IGLoop2D loop4(4, aLoopArray);

           // render the loops to the display
           myDisplayPort->draw(loop1,bundlei);
           myDisplayPort->draw(loop2,bundlei);
           myDisplayPort->draw(loop3,bundlei);
           myDisplayPort->draw(loop4,bundlei);
           
           myDisplayPort->draw(IGRect2D(0,0,0,0),bundle2);

       break;
        }

    case ID_BARCHART: {  // handle bar chart sample

      // create and draw the base
      GetBase(IGLine2D(IGPoint2D(70,100),IGPoint2D(70,400)),
              IGLine2D(IGPoint2D(70,400),IGPoint2D(350,400)), 20)->draw(*myDisplayPort);

      // create and draw the 5 bars of the chart
      GetBar(IGRect2D(100,200,120,400),IBaseColor(  0,  0,255))->draw(*myDisplayPort);
      GetBar(IGRect2D(150,360,170,400),IBaseColor(  0,255,  0))->draw(*myDisplayPort);
      GetBar(IGRect2D(200,225,220,400),IBaseColor(  0,255,255))->draw(*myDisplayPort);
      GetBar(IGRect2D(250,120,270,400),IBaseColor(255,  0,  0))->draw(*myDisplayPort);
      GetBar(IGRect2D(300,100,320,400),IBaseColor(255,  0,255))->draw(*myDisplayPort);

      // use the default font (system)
          ITextStyleSet styles;
      IFont font;
      styles.add(ITextTypefaceStyle(font.name()));
      styles.add(ITextPointSizeStyle(font.pointSize()));

      // create the base text
      IText year("1991");
          year.addStyles(styles);
      IGraphicText y1991(year, IGraphicText::kSingleLine);
      y1991.setLocation(IGPoint2D(95,420));
      y1991.draw(*myDisplayPort);

          year.replace(3, 1, 1, UniChar('2'));  // 2 for 1992
          year.addStyles(styles);
      IGraphicText y1992(year, IGraphicText::kSingleLine);
      y1992.setLocation(IGPoint2D(145,420));
      y1992.draw(*myDisplayPort);

          year.replace(3, 1, 1, UniChar('3'));  // 3 for 1993
          year.addStyles(styles);
      IGraphicText y1993(year, IGraphicText::kSingleLine);
      y1993.setLocation(IGPoint2D(195,420));
      y1993.draw(*myDisplayPort);

          year.replace(3, 1, 1, UniChar('4'));  // 4 for 1994
          year.addStyles(styles);
      IGraphicText y1994(year, IGraphicText::kSingleLine);
      y1994.setLocation(IGPoint2D(245,420));
      y1994.draw(*myDisplayPort);

          year.replace(3, 1, 1, UniChar('5'));  // 5 for 1995
          year.addStyles(styles);
      IGraphicText y1995(year, IGraphicText::kSingleLine);
      y1995.setLocation(IGPoint2D(295,420));
      y1995.draw(*myDisplayPort);

      IText value("100");
          value.addStyles(styles);
      IGraphicText l100(value, IGraphicText::kSingleLine);
      l100.setLocation(IGPoint2D(20,300));
      l100.draw(*myDisplayPort);

          value.replace(0, 1, 1, UniChar('2'));
          value.addStyles(styles);
      IGraphicText l200(value, IGraphicText::kSingleLine);
      l200.setLocation(IGPoint2D(20,200));
      l200.draw(*myDisplayPort);

          value.replace(0, 1, 1, UniChar('3'));
          value.addStyles(styles);
      IGraphicText l300(value, IGraphicText::kSingleLine);
      l300.setLocation(IGPoint2D(20,100));
      l300.draw(*myDisplayPort);

      break;
    }

    case ID_PIECHART: {  // handle pie chart sample

      // construct an attribute bundle for the 5 pieces
      IBaseColor black;

      IGrafBundle *piece1Bundle = new IGrafBundle(IBaseColor(  0,  0,255),black);
      IGrafBundle *piece2Bundle = new IGrafBundle(IBaseColor(  0,255,  0),black);
      IGrafBundle *piece3Bundle = new IGrafBundle(IBaseColor(  0,255,255),black);
      IGrafBundle *piece4Bundle = new IGrafBundle(IBaseColor(255,  0,  0),black);
      IGrafBundle *piece5Bundle = new IGrafBundle(IBaseColor(255,  0,255),black);

      // the defining ellipse of the entire pie
      IGEllipse2D pieEllipse(IGRect2D(100,100,400,400));

      // construct 5 pieces of the ellipse, by indicating the sweep
      // angles

      ILoop piece1( new
                    IGLoop2D(IGPie2D(pieEllipse,225,0)),piece1Bundle);
      ILoop piece2( new
                    IGLoop2D(IGPie2D(pieEllipse,125,225)),piece2Bundle);
      ILoop piece3(new
                   IGLoop2D(IGPie2D(pieEllipse,55,125)),piece3Bundle);
      ILoop piece4(new
                   IGLoop2D(IGPie2D(pieEllipse,20,55)),piece4Bundle);
      ILoop piece5(new
                   IGLoop2D(IGPie2D(pieEllipse,0,20)),piece5Bundle);

      // render the pie to the display
      piece1.draw(*myDisplayPort);
      piece2.draw(*myDisplayPort);
      piece3.draw(*myDisplayPort);
      piece4.draw(*myDisplayPort);
      piece5.draw(*myDisplayPort);

      break;
    }

    case ID_TEXT: {  // handle text sample

      IFont currentfont;

      IText theText("0123456789");
      theText.addStyles(ITextColorStyle(128, 0, 128 /*kDarkPink*/),2,5);
      theText.addStyles(ITextTypefaceStyle(currentfont.name()),2,5);

      theText.addStyles(ITextPointSizeStyle(currentfont.pointSize()),2,5);
      theText.addStyles(ITextBoldfaceStyle(currentfont.isBold()),2,5);
      theText.addStyles(ITextItalicStyle(currentfont.isItalic()),2,5);
      theText.addStyles(ITextUnderlineStyle(currentfont.isUnderscore()),2,5);
      theText.addStyles(ITextStrikethroughStyle(currentfont.isStrikeout()),2,5);

      theText.addStyles(ITextPointSizeStyle(18),0,1);
      theText.addStyles(ITextBoldfaceStyle(true),6,3);

      theText.addStyles(ITextItalicStyle(true),1,1);
      theText.addStyles(ITextUnderlineStyle(true),4,6);
      theText.addStyles(ITextStrikethroughStyle(true),8,2);

      IGraphicText graphicText(theText, IGraphicText::kSingleLine);
      graphicText.setLocation(IGPoint2D(50,30));
      graphicText.draw(*myDisplayPort);

          IGPoint2D orig(50,50);
          double deg = 90.;
          IGrafMatrix aMatrix(deg, orig);
          ILinkedGrafPort myLinkedPort(myDisplayPort, kViewMatrix, &aMatrix);
          IText aText("abcdef");
          aText.addStyles(ITextTypefaceStyle("Arial"));
      aText.addStyles(ITextColorStyle(128, 0, 128 /*kDarkPink*/),2,4);
          IGraphicText gText(aText, IGraphicText::kSingleLine);
          gText.setLocation(orig);
          gText.draw(myLinkedPort);

      break;
    }

  }  // end switch

  delete myDisplayPort;

  return true;

}

//*************************************************************************
// Program entry point                                                    *
//*************************************************************************

int main()                              //Main procedure with no parameters
{

  MainWindow  mainWindow(WND_MAIN);     //Create our main window on the desktop

  IApplication::current().run();        //Get the current application and
                                        // run it
} /* end main */
