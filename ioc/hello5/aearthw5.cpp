/******************************************************************************
* .FILE:         aearthw5.cpp                                                 *
*                                                                             *
* .DESCRIPTION:  Hello World Sample Program Version 5: Class Implementation   *
*                                                                             *
* .CLASSES:      AEarthWindow                                                 *
*                AEarthWindowResizeHandler                                    *
*                Star                                                         *
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
#include "aearthw5.hpp"

/**************************************************************************
* Class Star::Star - Constructors for drawing a star                      *
**************************************************************************/
Star::Star(const IGPoint2D &pt)
   : IGLine2D(pt,IGPoint2D(pt.fX+1, pt.fY+1))
{
}

Star::Star()
{
}

/**************************************************************************
* Class Star::setPoint - Sets the point where a star is located           *
**************************************************************************/
Star
 &Star::setPoint(const IGPoint2D &pt)
{
  setStartPoint(pt);
  setEndPoint(IPoint(pt.fX+1, pt.fY+1));
  return *this;
}

/**************************************************************************
* AEarthWindow :: AEarthWindow - Constructor for the Earth window         *
**************************************************************************/
AEarthWindow :: AEarthWindow(unsigned long windowId,
                             IWindow * parowWindow,
                             const IRectangle& rect)
               :IDrawingCanvas(windowId, parowWindow, parowWindow, rect)
                ,earthWindowResizeHandler(this)
                ,spaceColor(IBaseColor::kBlack)
                ,globeColor(IBaseColor::kCyan)
                ,starColor(IBaseColor::kWhite)
                ,spaceDimensions(4) // sets numPoints in the polygon to 4
{

/*------------------------------------------------------------------------|
|  Set the colors for the planets, atmosphere, space, and stars.          |
-------------------------------------------------------------------------*/
  arcBundle[0].setFillColor(globeColor);
  arcBundle[0].setFrameColor(globeColor);
  arcBundle[0].setDrawingOperation(IAttributeState::kFillAndFrame);

  arcBundle[1].setFillColor(IBaseColor::kDarkCyan);
  arcBundle[1].setFrameColor(IBaseColor::kDarkCyan);
  arcBundle[1].setDrawingOperation(IAttributeState::kFillAndFrame);

  arcBundle[2].setFillColor(IBaseColor::kDarkBlue);
  arcBundle[2].setFrameColor(IBaseColor::kDarkBlue);
  arcBundle[2].setDrawingOperation(IAttributeState::kFillAndFrame);

  arcBundle[3].setFillColor(IBaseColor::kBlue);
  arcBundle[3].setFrameColor(IBaseColor::kBlue);
  arcBundle[3].setDrawingOperation(IAttributeState::kFillAndFrame);

  spaceBundle.setFillColor(spaceColor);
  spaceBundle.setFrameColor(spaceColor);
  spaceBundle.setDrawingOperation(IAttributeState::kFillAndFrame);

  starBundle.setFrameColor(starColor);
  starBundle.setDrawingOperation(IAttributeState::kFillAndFrame);

/*------------------------------------------------------------------------|
|   The ResizeHandler is attached to the AEarthWindow object to begin     |
|   handling resize events.  Each time the IDrawingCanvas window needs to |
|   be resized, AEarthWindowResizeHandler::resizeWindow function will be  |
|   called.  The coordinates of the world are computed and the first      |
|   painting occurs because of IWindow::show.                             |
-------------------------------------------------------------------------*/
  earthWindowResizeHandler.handleEventsFor(this);
  setGraphicGroup(&theGroup);
  show();
} /* end AEarthWindow :: AEarthWindow(...) */

/**************************************************************************
* AEarthWindow :: ~AEarthWindow - Destructor for Earth window             *
**************************************************************************/
AEarthWindow :: ~AEarthWindow()
{
/*------------------------------------------------------------------------|
| Tell earthWindowResizeHandler to stop handling events for AEarthWindow. |
-------------------------------------------------------------------------*/
  int i;
  earthWindowResizeHandler.stopHandlingEventsFor(this);

  for (i = 0; i < stars; i++)
     {
        starLines[i].orphanGeometry();
        starLines[i].orphanBundle();
     }

  for (i = 0; i <= atmosphereLayers; i++)
     {
        earthArc[i].orphanGeometry();
        earthArc[i].orphanBundle();
     }

  space.orphanGeometry();
  space.orphanBundle();

  IGraphicGroupIterator emptyCheck(&theGroup);
  while (emptyCheck.first())
     theGroup.orphanFirst();

} /* end AEarthWindow :: ~AEarthWindow() */


/**************************************************************************
* AEarthWindow :: paintWorld - paint a view of Earth from space           *
**************************************************************************/
bool AEarthWindow :: computeWorld()
{
  const float
    xRadiusFactor[4] = {1.45, 1.55, 1.60, 1.65},
    yRadiusFactor[4] = {(0.7 - 1.0/8), (0.7 - 1.0/16),
                        (0.7 - 1.0/32), (0.7 - 1.0/64)};
  const IRectangle
    psRect(rect());

/*------------------------------------------------------------------------|
| Construct the IGRect2D space to form the background of the scene.       |
-------------------------------------------------------------------------*/

  IGPoint2D
     bottomLeftPoint(0, 0),
     bottomRightPoint(psRect.width(), 0),
     topLeftPoint(0, psRect.height()),
     topRightPoint(psRect.width(), psRect.height());

  spaceDimensions.setPoint(0, bottomLeftPoint);
  spaceDimensions.setPoint(1, bottomRightPoint);
  spaceDimensions.setPoint(2, topRightPoint);
  spaceDimensions.setPoint(3, topLeftPoint);

/*------------------------------------------------------------------------|
| Compute the dimensions for the earthArcs.                               |
-------------------------------------------------------------------------*/

  IGPoint2D centerPoint(psRect.width() / 2, -psRect.height() * 0.2);
  int xRad, yRad;
  for(int i=0;i<=atmosphereLayers;i++)
     {
        yRad = yRadiusFactor[i] * psRect.height();
        xRad = xRadiusFactor[i] * yRad;
        IGRect2D arcBoundsRect(0, 2 * yRad, 2 * xRad, 0);
        arcDimensions[i].setBounds(arcBoundsRect);
        arcDimensions[i].setCenter(centerPoint);
     }


/*------------------------------------------------------------------------|
| Call computeStars() to compuet the dimensions for the stars.            |
| Then call paintWorld() that uses all these dimensions to create the     |
| objects to be painted.                                                  |
-------------------------------------------------------------------------*/
  computeStars();
  paintWorld();
  refresh();
  return true;

} /* end AEarthWindow :: paintWorld(..) */

bool AEarthWindow::paintWorld() {

/*------------------------------------------------------------------------|
| Clear out theGroup.                                                     |
-------------------------------------------------------------------------*/
  IGraphicGroupIterator emptyCheck(&theGroup);
  while (emptyCheck.first())
     theGroup.orphanFirst();

/*------------------------------------------------------------------------|
| Add the drawable objects to theGroup.                                   |
-------------------------------------------------------------------------*/
  space.orphanGeometry();
  space.adoptGeometry(&spaceDimensions);
  space.orphanBundle();
  space.adoptBundle(&spaceBundle);
  theGroup.adoptLast(&space);

  for (int i=atmosphereLayers; i>=0; i--)
     {
        earthArc[i].orphanGeometry();
        earthArc[i].adoptGeometry(&arcDimensions[i]);
        earthArc[i].orphanBundle();
        earthArc[i].adoptBundle(&arcBundle[i]);
        theGroup.adoptLast(&earthArc[i]);
     }

  for (int k=0; k<stars ;k++ )
     {
        starList[k].setPoint(star[k]);
        starLines[k].orphanGeometry();
        starLines[k].adoptGeometry(&starList[k]);
        starLines[k].orphanBundle();
        starLines[k].adoptBundle(&starBundle);
        theGroup.adoptLast(&starLines[k]);
     }
  return true;
}

/**************************************************************************
* AEarthWindow :: paintStars - paint the stars in the Earth window        *
**************************************************************************/
bool AEarthWindow :: computeStars()
{
  bool starsPainted = false;

/*------------------- Get Presentation Space Objects ---------------------|
| Get the presentation space handle (called "graphics context" in AIX)    |
|   and the rectangle of the area that needs to be painted.               |
|------------------------------------------------------------------------*/
  const IRectangle
    psRect(rect());

/*------------------- Construct Stars from IPoints -----------------------|
| Construct a star array where each star is a point within the            |
|   presentation space rectangle.  Each point is computed as a fraction   |
|   of the psRect size offset from the origin of the psRect.              |
|------------------------------------------------------------------------*/
  const IPair
    psOrigin(psRect.bottomLeft()),
    psSize(psRect.size());
  int
    i, j;

  star[0] = IGPoint2D(psOrigin+psSize.scaledBy(0.98,0.43));
  star[1] = IGPoint2D(psOrigin+psSize.scaledBy(0.70,0.69));
  star[2] = IGPoint2D(psOrigin+psSize.scaledBy(0.20,0.50));
  star[3] = IGPoint2D(psOrigin+psSize.scaledBy(0.80,0.63));
  star[4] = IGPoint2D(psOrigin+psSize.scaledBy(0.05,0.41));
  star[5] = IGPoint2D(psOrigin+psSize.scaledBy(0.50,0.69));
  star[6] = IGPoint2D(psOrigin+psSize.scaledBy(0.60,0.94));
  star[7] = IGPoint2D(psOrigin+psSize.scaledBy(0.10,0.87));
  star[8] = IGPoint2D(psOrigin+psSize.scaledBy(0.40,0.81));
  star[9] = IGPoint2D(psOrigin+psSize.scaledBy(0.25,0.69));
  star[10]= IGPoint2D(psOrigin+psSize.scaledBy(0.75,0.63));
  star[11]= IGPoint2D(psOrigin+psSize.scaledBy(0.30,0.87));
  star[12]= IGPoint2D(psOrigin+psSize.scaledBy(0.95,0.87));


/*------------------------------------------------------------------------|
| Draw the stars by setting the starBundle to white and by setting the    |
| position of that the star will be drawn at.  On the first call to this  |
| function, each star will instantiated while setting the location and    |
| the graphic bundle will be set to starBundle.                           |
|------------------------------------------------------------------------*/

  starsPainted = true;
  return (starsPainted);
} /* end AEarthWindow :: paintStars(...) */

/******************************************************************************
* Class AEarthWindowResizeHandler :: AEarthWindowResizeHandler - Constructor  *
*                                                                             *
* Define yourself as an IResizeHandler                                        *
* Store a pointer to the picture                                              *
******************************************************************************/
AEarthWindowResizeHandler::AEarthWindowResizeHandler( AEarthWindow * aew )
      :IResizeHandler()
     , earthWindow ( aew )
{
}


/******************************************************************************
* Class AEarthWindowResizeHandler :: ~AEarthWindowResizeHandler - Destructor  *
******************************************************************************/
AEarthWindowResizeHandler::~AEarthWindowResizeHandler( )
{
}


/******************************************************************************
* Class AEarthWindowResizeHandler :: windowResize() - Called when a resize    *
*   event occurs for the picture.                                             *
******************************************************************************/
bool AEarthWindowResizeHandler::windowResize( IResizeEvent& event )
{
/*-----------------------------------------------------------------------------
| Call our own resizing function and repaint the drawing canvas.              |
-----------------------------------------------------------------------------*/
  earthWindow->computeWorld();
  return true;
}

