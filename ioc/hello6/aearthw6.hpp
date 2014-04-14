/******************************************************************************
* .FILE:         aearthw6.hpp                                                 *
*                                                                             *
* .DESCRIPTION:  Hello World Sample Program Version 6:  AEarthWindow Header   *
*                                                                             *
* .CLASSES:      AEarthWindow                                                 *
*                ATwinkleTimeHandler                                          *
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
******************************************************************************/
#ifndef _AEARTHW6_
#define _AEARTHW6_

#include <idrawcv.hpp>
#include <isizehdr.hpp>
#include <itimer.hpp>
#include <igraph2d.hpp>
#include <igbase2d.hpp>
#include <igarea2d.hpp>
#include <ibundles.hpp>

class AEarthWindow;

/**************************************************************************
* Class ATwinkleTimeHandler - Time Handler class the processes time ticks *
*   for AEarthWindow.                                                     *
**************************************************************************/
class ATwinkleTimeHandler : public ITimerFn
{
  public:
/*---------------------------- Constructor -------------------------------|
| Constructs the object with                                              |
| 1) A pointer to the earth window                                        |
-------------------------------------------------------------------------*/
    ATwinkleTimeHandler (AEarthWindow *a) : aew(a) {}

/*------------------------ Overridden Functions---------------------------|
| timerExpired function is called each time the ITimer expires.           |
-------------------------------------------------------------------------*/
    virtual void
      timerExpired (unsigned long);

  private:
    AEarthWindow
     *aew;
};

/*------------------------------------------------------------------------|
| An enumerated type that determines how the star will be drawn.          |
-------------------------------------------------------------------------*/
    enum Intensity
    {
      dim, twinkle, bright
    };


/**************************************************************************
* Class Star -- Draws a star at a specified location                      *
**************************************************************************/

class Star
{
  public:
/*--------------------------- Constructor --------------------------------|
| Constructs the object with:                                             |
| 1) the point to put the star                                            |
| 2) the point and intensity of the star                                  |
-------------------------------------------------------------------------*/
    Star(const IGPoint2D &pt = IGPoint2D(0, 0)) ;
    Star(const IGPoint2D &pt,Intensity &it) ;
/*--------------------------- Destructor ---------------------------------|
| Destructs the object with:                                              |
| 1) no parameters                                                        |
-------------------------------------------------------------------------*/
   ~Star();
/*------------------------------------------------------------------------|
|  setPoint -- This function sets a new location to draw the star at      |
|  setIntensity--This function sets the intensity of the star             |
|  flicker--This function randomly causes the star to change intensity    |
|  getIMGraphic--This function return the IMGraphic for the star          |
-------------------------------------------------------------------------*/
  Star
   &setPoint(const IGPoint2D &pt),
   &setIntensity(const Intensity it),
   &flicker(); // GetIMGraphic??
  IMGraphic
    &getIMGraphic();

  private:
    Intensity
      intensity;
    IGLine2D
      dimStarDimensions;
    ILine
      dimStar;
    IGEllipse2D
      brightStarDimensions;
    IEllipse
      brightStar;
    IGrafBundle
      brightStarBundle,
      dimStarBundle;
};


/**************************************************************************
* Class AEarthWindowResizeHandler -- A handler to resize the picture      *
*    according to the new dimensions of the IDrawingCanvas window.        *
**************************************************************************/
class AEarthWindowResizeHandler: public IResizeHandler
{
  public:
/*--------------------------- Constructor --------------------------------|
| Constructs the object with:                                             |
| 1) a pointer to the EarthWindow                                         |
-------------------------------------------------------------------------*/
    AEarthWindowResizeHandler (AEarthWindow *aew);

/*--------------------------- Destructor ---------------------------------|
| Destructs the object with:                                              |
| 1) no parameters                                                        |
-------------------------------------------------------------------------*/
    virtual
     ~AEarthWindowResizeHandler();

  protected:
/*-------------------- Override windowResize Function --------------------|
| The windowResize() function is called to handle resizing of             |
| the IDrawingCanvas text window containing the graphics of Earth.        |
|------------------------------------------------------------------------*/
    virtual bool
      windowResize(IResizeEvent & evnt);

  private:
    AEarthWindow
     *earthWindow;
};

/**************************************************************************
* Class AEarthWindow -- Earth window for the C++ Hello World sample       *
*    application.                                                         *
**************************************************************************/
class AEarthWindow : public IDrawingCanvas
{
  public:
/*--------------------------- Constructor --------------------------------|
| Constructs the object with:                                             |
| 1) the window id, the parent window, and the size of the window         |
-------------------------------------------------------------------------*/
    AEarthWindow(unsigned long windowId,
                IWindow * parentownerWindow,
                const IRectangle& rect=IRectangle());

/*--------------------------- Destructor ---------------------------------|
| Destructs the object with:                                              |
| 1) no parameters                                                        |
-------------------------------------------------------------------------*/
    virtual
     ~AEarthWindow();

/*------------------ Paint the Earth and Stars Functions -----------------|
| These functions are called to draw the Earth and stars in a static      |
| text window.                                                            |
|   paintWorld - Clear the background, draw the Earth and a variable      |
|           number of atmosphere layers, call paintStars to draw the      |
|           stars, and call addObjectsToGroup to add the graphical        |
|           objects to IGraphicGroup theGroup.                            |
|   computeStars - Compute the coordinates of the stars.                  |
|   addObjectsToGroup - Adds graphical objects to theGroup.               |
|   twinkleStars - Causes the stars to randomly swith from bright to dim  |
|------------------------------------------------------------------------*/
    bool
      paintWorld(),
      computeStars(),
      addObjectsToGroup(),
      twinkleStars();
/*------------------ Earth Window Settings Functions ---------------------|
| These functions are used to change the Earth window settings.           |
|   enableBright - Change starIntensity to bright.                        |
|   disableBright - Change starIntensity to dim.                          |
|   setLayers - Change the number of atmosphere layers drawn atop the     |
|           Earth arc.  Valid values are 0, 1, 2, 3.                      |
|   enableTwinkle - Set twinkling to true.                                |
|   disableTwinkle - Set twinkling to false.                              |
|   setEarthColor - Change the color used to draw the Earth arc.          |
|                                                                         |
| These functions are used to query the Earth window settings.            |
|   isTwinkling - Return true if the stars are set to twinkle.            |
|   isBright - Return true if the stars are to be drawn with five points  |
|           when they are not twinkling.                                  |
|   earthColor - Return the current color used to draw the Earth arc.     |
|   layers - Return the number of arcs drawn above the Earth arc.         |
|------------------------------------------------------------------------*/
    virtual AEarthWindow
     &enableBright(bool makingBright=true),
     &disableBright(),
     &setLayers(const unsigned long atmosphereLayers),
     &enableTwinkle(bool turningOn=true),
     &disableTwinkle(),
     &setEarthColor(const IColor &hue);
    const bool
      isTwinkling(),
      isBright();
    const IColor
     &earthColor();
    const unsigned long
      layers();

  private:
    int
      atmosphereLayers;
    AEarthWindowResizeHandler
      earthWindowResizeHandler;
    IColor
      spaceColor,
      globeColor,
      starColor;

    IGPoint2D
      star[13];
    Star
      starList[13];

    IGEllipse2D
      arcDimensions[4];
    IEllipse
      earthArc[4];

    IGrafBundle arcBundle[4], spaceBundle;

    IGPolygon2D
      spaceDimensions;
    IPolygon
      space;
    IGraphicGroup
      theGroup,
      atmosphereGraphicGroup;
    bool
      twinkling;
    Intensity
      starIntensity;
    ITimer
       twinkleTimer;
/*------------------------------ Operators -------------------------------|
| Operators defined for this class:                                       |
|  =  -- Assignment operator                                              |
-------------------------------------------------------------------------*/
    AEarthWindow
     &operator=(const AEarthWindow&);    //Default assignment operator

};
#endif
