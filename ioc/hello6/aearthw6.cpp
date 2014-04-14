/******************************************************************************
* .FILE:         aearthw6.cpp                                                 *
*                                                                             *
* .DESCRIPTION:  Hello World Sample Program Version 6: Class Implementation   *
*                                                                             *
* .CLASSES:      AEarthWindow                                                 *
*                AEarthWindowResizeHandler                                    *
*                ATwinkleTimeHandler                                          *
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
#include <stdlib.h>
#include "aearthw6.hpp"

/**************************************************************************
* Class Star::Star--Constructor for drawing a star                        *
**************************************************************************/
Star::Star(const IGPoint2D &pt)
  : dimStarDimensions(pt, IGPoint2D(pt.fX+1, pt.fY+1))
  , brightStarDimensions(IGRect2D(IRectangle(2,2)))
{
  intensity=bright;

  dimStarBundle.setFrameColor(IBaseColor::kWhite);
  dimStarBundle.setDrawingOperation(IAttributeState::kFillAndFrame);
  dimStar.adoptGeometry(&dimStarDimensions);
  dimStar.adoptBundle(&dimStarBundle);

  brightStarDimensions.setCenter(pt);
  brightStarBundle.setFillColor(IBaseColor::kWhite);
  brightStarBundle.setFrameColor(IBaseColor::kWhite);
  brightStarBundle.setDrawingOperation(IAttributeState::kFillAndFrame);
  brightStar.adoptGeometry(&brightStarDimensions);
  brightStar.adoptBundle(&brightStarBundle);
}

/**************************************************************************
* Class Star::~Star--Destructor for drawing a star                        *
**************************************************************************/
Star::~Star()
{
   dimStar.orphanGeometry();
   dimStar.orphanBundle();
   brightStar.orphanGeometry();
   brightStar.orphanBundle();
}

/**************************************************************************
* Class Star::setPoint--Sets the point where a star is located            *
**************************************************************************/
Star
 &Star::setPoint(const IGPoint2D &pt)
{
  dimStarDimensions.setEndPoint(IGPoint2D(pt.fX+1, pt.fY+1));
  dimStarDimensions.setStartPoint(pt);
  brightStarDimensions.setCenter(pt);
  return *this;
}
/**************************************************************************
* Class Star::setIntensity - Sets the intensity of the star               *
**************************************************************************/
Star
 &Star::setIntensity(const Intensity it)
{
  intensity=it;
  return *this;
}
/**************************************************************************
* Class Star::getIMGraphic - Returns the IMGraphic for the star           *
**************************************************************************/
IMGraphic
 &Star::getIMGraphic()
{
  if (intensity == bright)
    return brightStar;
  else
    return dimStar;
}
/**************************************************************************
* Class Star::flicker - randomly sets the star from bright to dim         *
**************************************************************************/
Star
 &Star::flicker()
{
  if (rand()%2)
    intensity=bright;
  else
    intensity=dim;
  return *this;
}

/**************************************************************************
* AEarthWindow :: AEarthWindow - Constructor for the Earth window         *
**************************************************************************/
AEarthWindow :: AEarthWindow(unsigned long windowId,
                             IWindow * parowWindow,
                             const IRectangle& rect)
               :IDrawingCanvas(windowId, parowWindow, parowWindow, rect)
                ,spaceColor(IBaseColor::kBlack)
                ,globeColor(IBaseColor::kCyan)
                ,starColor(IBaseColor::kWhite)
                ,earthWindowResizeHandler(this)
                ,twinkling(false)
                ,starIntensity(bright)
                ,atmosphereLayers(3)
                ,spaceDimensions(4)
{
/*------------------------------------------------------------------------|
|  Set the bundles for the planets, atmosphere, and space.                |
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

/*------------------------------------------------------------------------|
|   The ResizeHandler is attached to the AEarthWindow object to begin     |
|   handling resize events.  Each time the IDrawingCanvas window needs to |
|   be resized, AEarthWindowResizeHandler::resizeWindow function will be  |
|   called.  The first painting occurs because of IWindow::show.          |
-------------------------------------------------------------------------*/

  earthWindowResizeHandler.handleEventsFor(this);
  setGraphicGroup(&theGroup);
  twinkleTimer.setInterval(500);
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
  earthWindowResizeHandler.stopHandlingEventsFor(this);

/*------------------------------------------------------------------------|
| Tell the timer to stop twinkling.                                       |
-------------------------------------------------------------------------*/
  if (twinkleTimer.isStarted())
     twinkleTimer.stop();

/*------------------------------------------------------------------------|
| Orphan all geometry, bundles, and other objects that were previously    |
| adopted.                                                                |
-------------------------------------------------------------------------*/
  space.orphanGeometry();
  space.orphanBundle();
  for (int i = 0; i <= 3; i++)
    {
      earthArc[i].orphanGeometry();
      earthArc[i].orphanBundle();
    }

  IGraphicGroupIterator emptyCheck(&theGroup);
  while (emptyCheck.first())
     theGroup.orphanFirst();
  IGraphicGroupIterator aEmptyCheck(&atmosphereGraphicGroup);
  while (aEmptyCheck.first())
     atmosphereGraphicGroup.orphanFirst();

} /* end AEarthWindow :: ~AEarthWindow() */


/**************************************************************************
* AEarthWindow :: paintWorld - paint a view of Earth from space           *
**************************************************************************/
bool
  AEarthWindow :: paintWorld()
{
  bool
    worldPainted = false;
  const float
    xRadiusFactor[4] = {1.45, 1.55, 1.60, 1.65},
    yRadiusFactor[4] = {(0.7 - 1.0/8), (0.7 - 1.0/16),
                        (0.7 - 1.0/32), (0.7 - 1.0/64)};
  const IRectangle
    psRect(rect());

/*------------------------------------------------------------------------|
| Construct the IGRect2D spaceDimensions to form the background of the    |
| scene.                                                                  |
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
  for(int i=atmosphereLayers;i>=0;i--)
     {
        yRad = yRadiusFactor[i] * psRect.height();
        xRad = xRadiusFactor[i] * yRad;
        IGRect2D arcBoundsRect(0, 2 * yRad, 2 * xRad, 0);
        arcDimensions[i].setBounds(arcBoundsRect);
        arcDimensions[i].setCenter(centerPoint);
     }


/*------------------------------------------------------------------------|
| Call computeStars() to compute the dimensions for the stars.            |
| Then call addObjectsToGroup() that uses all these dimensions to add     |
| all the objects to be painted to the IGraphicGroup.                     |
-------------------------------------------------------------------------*/
  computeStars();
  worldPainted = addObjectsToGroup();
  refresh();
  return worldPainted;

} /* end AEarthWindow :: paintWorld(..) */

/**************************************************************************
* AEarthWindow::addObjectsToGroup - Adds all the objects to be painted to *
* the IGraphicGroup.                                                      *
**************************************************************************/
bool AEarthWindow::addObjectsToGroup() {

/*------------------------------------------------------------------------|
| Clear out theGroup.                                                     |
-------------------------------------------------------------------------*/
  IGraphicGroupIterator emptyCheck(&theGroup);
  while (emptyCheck.first())
     theGroup.orphanFirst();
  IGraphicGroupIterator aEmptyCheck(&atmosphereGraphicGroup);
  while (aEmptyCheck.first())
     atmosphereGraphicGroup.orphanFirst();

/*------------------------------------------------------------------------|
| Add the drawable objects to theGroup.                                   |
-------------------------------------------------------------------------*/
  space.orphanGeometry();
  space.adoptGeometry(&spaceDimensions);
  space.orphanBundle();
  space.adoptBundle(&spaceBundle);
  theGroup.adoptLast(&space);

  for (int i=0; i<=3; i++)
     {
        earthArc[i].orphanGeometry();
        earthArc[i].adoptGeometry(&arcDimensions[i]);
        earthArc[i].orphanBundle();
        earthArc[i].adoptBundle(&arcBundle[i]);
     }
  for (int j = atmosphereLayers; j >= 0; j--)
//     atmosphereGraphicGroup.adoptLast(&earthArc[3 - j]);
     atmosphereGraphicGroup.adoptLast(&earthArc[j]);

  theGroup.adoptLast(&atmosphereGraphicGroup);

  for (int k=0; k<13 ;k++ )
     {
        starList[k].setPoint(star[k]);
        theGroup.adoptLast(&starList[k].getIMGraphic());
     }
  return true;
} /* end AEarthWindow :: addObjectsToGroup(..) */

/**************************************************************************
* AEarthWindow :: computeStars - compute the coordinates of the stars     *
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

  starsPainted = true;
  return (starsPainted);
} /* end AEarthWindow :: computeStars(...) */


/**************************************************************************
* Class AEarthWindow:: twinkleStars - Make the stars twinkle and refresh  *
**************************************************************************/
bool
  AEarthWindow::twinkleStars()
{
  if (twinkling)
  {
/*------------------------------------------------------------------------|
| If the stars are twinkling, then call the flicker function for each     |
| and redraw them on the IDrawingCanvas.                                  |
-------------------------------------------------------------------------*/
    for (int i=0;i<13 ;i++ )
      starList[i].flicker();
    paintWorld();
  }
  return true;
}

/******************************************************************************
* Class AEarthWIndowResizeHandler :: AEarthWindowResizeHandler - Constructor  *
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


/**************************************************************************
* Class AEarthWindowResizeHandler :: windowResize() - Called when a       *
*   resize event occurs for the drawing canvas.                           *
**************************************************************************/
bool AEarthWindowResizeHandler::windowResize( IResizeEvent& event )
{
/*-------------------------------------------------------------------------
| Call our own resizing function and repaint the drawing canvas.          |
-------------------------------------------------------------------------*/
   earthWindow->paintWorld();
   return false;
}


/**************************************************************************
* Class AEarthWindow :: enableBright - Set the star intensity to bright   *
*   or dim.                                                               *
**************************************************************************/
AEarthWindow
  &AEarthWindow :: enableBright(bool makingBright)
{
  int i;

  if (makingBright && starIntensity != bright)
  {
    starIntensity = bright;
    for (i = 0; i < 13; i++)
      starList[i].setIntensity(bright);
    paintWorld();
  }
  else if (!makingBright && starIntensity != dim)
  {
    starIntensity = dim;
     for (i = 0; i < 13; i++)
       starList[i].setIntensity(dim);
     paintWorld();
  }
  return (*this);
} /* end AEarthWindow :: enableBright */


/**************************************************************************
* Class AEarthWindow :: disableBright - Set the star intensity to dim.    *
**************************************************************************/
AEarthWindow
  &AEarthWindow :: disableBright()
{
  return (enableBright(false));
} /* end AEarthWindow :: disableBright */


/**************************************************************************
* AEarthWindow :: isBright                                                *
*   Return true if starIntensity is bright, else return false.            *
**************************************************************************/
const bool
  AEarthWindow :: isBright()
{
  return (starIntensity==bright);
} /* end AEarthWindow :: isBright */


/**************************************************************************
* Class AEarthWindow :: setLayers - Set the atmosphere layers from 0 to 3.*
**************************************************************************/
AEarthWindow
  &AEarthWindow :: setLayers(const unsigned long layers)
{
  if(layers>3)
    atmosphereLayers=3;
  else
    atmosphereLayers=layers;
  paintWorld();
  return (*this);
} /* end AEarthWindow :: setLayers */


/**************************************************************************
* Class AEarthWindow :: layers - Return the current number of layers      *
*   of atmosphere.                                                        *
**************************************************************************/
const unsigned long
  AEarthWindow :: layers()
{
  return (atmosphereLayers);
} /* end AEarthWindow :: layers */


/**************************************************************************
* Class AEarthWindow :: enableTwinkle - Make the stars twinkle.           *
**************************************************************************/
AEarthWindow
  &AEarthWindow :: enableTwinkle(bool turningOn)
{
  if (turningOn && !twinkling)
  {
    twinkling=true;
    twinkleTimer.start(new ATwinkleTimeHandler(this));
    twinkleStars();
  }
  else if (!turningOn && twinkling)
  {
    twinkling=false;
    twinkleTimer.stop();
    addObjectsToGroup();
  }
  return (*this);
} /* end AEarthWindow :: enableTwinkle (...) */


/**************************************************************************
* Class AEarthWindow :: disableTwinkle - Make the stars stop twinkling.   *
**************************************************************************/
AEarthWindow
  &AEarthWindow :: disableTwinkle()
{
  return (enableTwinkle(false));
} /* end AEarthWindow :: disableTwinkle() */


/**************************************************************************
* Class AEarthWindow :: isTwinkling -Are the stars twinkling?             *
**************************************************************************/
const bool
  AEarthWindow :: isTwinkling()
{
  return (twinkling);
} /* end AEarthWindow :: isTwinkling() */


/**************************************************************************
* AEarthWindow :: setEarthColor - Set the color used for drawing the      *
*   inner arc that represents Earth.                                      *
**************************************************************************/
AEarthWindow
  &AEarthWindow :: setEarthColor(const IColor &hue)
{
  globeColor = hue;
  arcBundle[0].setFillColor(hue);
  arcBundle[0].setFrameColor(hue);
  arcBundle[0].setDrawingOperation(IAttributeState::kFillAndFrame);
  paintWorld();
  return (*this);
} /* end AEarthWindow :: setEarthColor(...) */


/**************************************************************************
* Class AEarthWindow :: earthColor - Return the current color being used  *
*   to draw the Earth.                                                    *
**************************************************************************/
const IColor
  &AEarthWindow :: earthColor()
{
  return globeColor;
} /* end AEarthWindow :: earthColor() */


/**************************************************************************
* Class ATwinkleTimeHandler :: tick - Process ATimeHandler ticks by       *
*   calling the AEarthWindow function for twinkling the stars.            *
**************************************************************************/
void ATwinkleTimeHandler::timerExpired(unsigned long timeid)
{
  aew->twinkleStars();
}

