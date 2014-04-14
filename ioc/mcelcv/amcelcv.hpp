/******************************************************************************
* .FILE:         amcelcv.hpp                                                  *
*                                                                             *
* .DESCRIPTION:  Canvas Classes Example 3 - Multi Cell Canvas : Class Header  *
*                                                                             *
* .CLASSES:      APushButtonHandler                                           *
*                AMultiCellCanvas                                             *
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
#ifndef AMCELCV_HPP
#define AMCELCV_HPP

#include <iframe.hpp>
#include <istattxt.hpp>
#include <ipushbut.hpp>
#include <iradiobt.hpp>
#include <icheckbx.hpp>
#include <imcelcv.hpp>
#include <icmdhdr.hpp>

class AMultiCellCanvas;

/******************************************************************************
* Class APushButtonHandler - Push button handler                              *
******************************************************************************/
class APushButtonHandler : public ICommandHandler
{
  public:
    APushButtonHandler() : window(0) {;}

    inline APushButtonHandler
     &setOwnerWindow(AMultiCellCanvas *pmcellcv) { window = pmcellcv; return *this; };
  protected:
    virtual bool
      command( ICommandEvent& evt );
  private:
    AMultiCellCanvas
     *window;
};

/*******************************************************************************
* Class AMultiCellCanvas - main window for multicell canvas sample application *
*******************************************************************************/
class AMultiCellCanvas : public IFrameWindow
{
  public:
    AMultiCellCanvas(unsigned long windowId);

  AMultiCellCanvas&
    displayButtonStatus();

  private:
    IMultiCellCanvas
      clientCanvas;
    IStaticText
      status,
      title1,
      title2;
    ICheckBox
      check1,
      check2;
    IRadioButton
      radio1,
      radio2;
    IPushButton
      pushButton;
    APushButtonHandler
      pushButtonHandler;
};

#endif
