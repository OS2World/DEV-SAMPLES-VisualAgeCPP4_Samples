/******************************************************************************
* .FILE:         avport.hpp                                                   *
*                                                                             *
* .DESCRIPTION:  Canvas Classes Example 4 - ViewPort (Class Headers)          *
*                                                                             *
* .CLASSES:      AViewPort                                                    *
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
#ifndef AVPORT_HPP
#define AVPORT_HPP

#include <iframe.hpp>                   // IFrameWindow
#include <ivport.hpp>                   // IViewPort
#include <ibmpctl.hpp>                  // IBitmapControl

/**************************************************************************
* Class AViewPort - Main window for C++ ViewPort sample application       *
**************************************************************************/

class AViewPort : public IFrameWindow
{
  public:
/*--------------------------------- Constructor --------------------------*
| Constructs the object with:                                             |
| 1) the window id                                                        |
-------------------------------------------------------------------------*/
    AViewPort(unsigned long windowId);

  private:
    IViewPort
      clientViewPort;
    IBitmapControl
      bitmap;
};

#endif
