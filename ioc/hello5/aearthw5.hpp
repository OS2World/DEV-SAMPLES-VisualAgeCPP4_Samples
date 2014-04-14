/******************************************************************************
* .FILE:         aearthw5.hpp                                                 *
*                                                                             *
* .DESCRIPTION:  Hello World Sample Program Version 5:  AEarthWindow Header   *
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
#ifndef _AEARTHW5_
#define _AEARTHW5_

#include <idrawcv.hpp>
#include <isizehdr.hpp>
#include <igarea2d.hpp>
#include <igbase2d.hpp>
#include <ibundles.hpp>
#include <igbase2d.hpp>
#include <iexgrprt.hpp>
#include <igraph2d.hpp>


const int                       //Number of stars in the sky
  stars=13;
const int                       //Number of layers in the atmosphere
  atmosphereLayers=3;

class AEarthWindow;

/**************************************************************************
* Class Star -- Draws a star at a specified location                      *
**************************************************************************/

class Star:public IGLine2D
{
  public:
/*--------------------------- Constructor --------------------------------|
| Constructs the object with:                                             |
| 1) the point to put the star                                            |
| 2) default constructor                                                  |
-------------------------------------------------------------------------*/
    Star(const IGPoint2D &pt) ;
    Star() ;
/*------------------------------------------------------------------------|
|  setPoint -- This function sets a new location to draw the star at      |
-------------------------------------------------------------------------*/
    Star
     &setPoint(const IGPoint2D &pt);
};


/**************************************************************************
* Class AEarthWindowResizeHandler -- A handler that computes the new      *
* window dimensions when the window is resized and paints the window      *
* whenevernecessary.                                                      *
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
    virtual ~AEarthWindowResizeHandler();

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
|   computeWorld - compute the coordinates of the earth                   |
|   computeStars - compute the coordinates of the stars                   |
|   paintWorld - Clear the background, draw the Earth and a variable      |
|           number of atmosphere layers, and draw the stars.              |
|------------------------------------------------------------------------*/
    bool
      paintWorld();
    bool
      computeWorld();
    bool
      computeStars();

  private:
    AEarthWindowResizeHandler
      earthWindowResizeHandler;

    IGraphicGroup theGroup;

    IGEllipse2D arcDimensions[4];
    IEllipse earthArc[4];

    IGPolygon2D spaceDimensions;
    IPolygon space;

    IGPoint2D star[stars];
    Star starList[stars];
    ILine starLines[stars];

    IGrafBundle arcBundle[4], spaceBundle;
    IGrafBundle starBundle;

    IBaseColor
      spaceColor,
      globeColor,
      starColor;

/*------------------------------ Operators -------------------------------|
| Operators defined for this class:                                       |
|  =  -- Assignment operator                                              |
-------------------------------------------------------------------------*/
    AEarthWindow
     &operator=(const AEarthWindow&);    //Default assignment operator

};
#endif
