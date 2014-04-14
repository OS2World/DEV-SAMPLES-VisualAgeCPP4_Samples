/******************************************************************************
* .FILE:         asetcv.hpp                                                   *
*                                                                             *
* .DESCRIPTION:  Set Canvas Example:  Class Headers                           *
*                                                                             *
* .CLASSES:      AButtonHandler                                               *
*                ASetCanvas                                                   *
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
#ifndef ASETCV_HPP
#define ASETCV_HPP

#define MAX_BUTTONS  7

#include <iframe.hpp>                   // IFrameWindow
#include <iradiobt.hpp>                 // IRadioButton
#include <ipushbut.hpp>                 // IPushButton
#include <isetcv.hpp>                   // ISetCanvas
#include <isplitcv.hpp>                 // ISplitCanvas

/******************************************************************************
* Class AButtons -- Collection of radio and push buttons                      *
******************************************************************************/
class AButtons
{
  public:
/*------------------------------- Styles -------------------------------------|
| Styles for creating the radio button group:                                 |
|   vertical - The first radio button has text indicating a vertical group    |
|   horizontal - The first radio button has text indicating a horizontal group|
-----------------------------------------------------------------------------*/
    enum MyCanvasType
    {
      vertical,
      horizontal
    };

/*------------------------------ Constructor ---------------------------------|
| Constructs the radio and push button objects with:                          |
| 1) the ID for the first button, the parent/owner canvas, and                |
|    number of buttons                                                        |
-----------------------------------------------------------------------------*/
    AButtons( unsigned long windowId,
              ISetCanvas * parentOwner,
              unsigned long numberOfButtons,
              MyCanvasType canvasType );

/*------------------------------- Destructor ---------------------------------|
| Destructs the object with:                                                  |
| 1) No Parameters                                                            |
-----------------------------------------------------------------------------*/
    ~AButtons();

  private:
    IButton
     *button[ MAX_BUTTONS ];
    unsigned long
      numberOfButtons;
};

/******************************************************************************
* Class ASetCanvas -- Main window for set canvas sample                       *
******************************************************************************/
class ASetCanvas : public IFrameWindow
{
  public:
/*------------------------------ Constructor ---------------------------------|
| Constructs the object with:                                                 |
| 1) the window id                                                            |
-----------------------------------------------------------------------------*/
    ASetCanvas(unsigned long windowId);

/*------------------------------- Destructor ---------------------------------|
| Destructs the object with:                                                  |
| 1) No Parameters                                                            |
-----------------------------------------------------------------------------*/
   ~ASetCanvas();

  private:
    ISplitCanvas
      horzCanvas1,
      vertCanvas1,
      vertCanvas2,
      vertCanvas3;
    ISetCanvas
      setCanvas1,
      setCanvas2,
      setCanvas3,
      setCanvas4,
      setCanvas5,
      setCanvas6;
    AButtons
     vRadioGroup1,
     vRadioGroup2,
     vRadioGroup3,
     hRadioGroup1,
     hRadioGroup2,
     hRadioGroup3;
};

#endif
