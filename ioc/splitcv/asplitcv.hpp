/******************************************************************************
* .FILE:         asplitcv.hpp                                                 *
*                                                                             *
* .DESCRIPTION:  Split Canvas Example                                         *
*                                                                             *
* .CLASSES       ASplitCanvas                                                 *
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
#ifndef ASPLITCV_HPP
#define ASPLITCV_HPP

#include <iframe.hpp>                   // IFrameWindow
#include <istattxt.hpp>                 // IStaticText
#include <isplitcv.hpp>                 // ISplitCanvas

/******************************************************************************
* Class ASplitCanvas - main window for the sample application                 *
******************************************************************************/
class ASplitCanvas : public IFrameWindow
{
  public:
/*------------------------------- Constructor --------------------------------|
| Constructs the object with:                                                 |
| 1) the window id                                                            |
--------------------------------- Constructor -------------------------------*/
    ASplitCanvas(unsigned long windowId);

  private:
    ISplitCanvas
      horzCanvas,
      vertCanvas;
    IStaticText
      lText,
      rText,
      bText;
};
#endif
