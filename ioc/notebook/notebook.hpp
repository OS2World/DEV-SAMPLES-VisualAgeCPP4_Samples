/******************************************************************************
* .FILE:         notebook.hpp                                                 *
*                                                                             *
* .DESCRIPTION:  Notebook Sample Program:  Class Header                       *
*                                                                             *
* .CLASSES:      ABitmapNotebook                                              *
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
#ifndef NOTEBOOK_HPP
#define NOTEBOOK_HPP

#include <iframe.hpp>
#include <inotebk.hpp>
#include <ivport.hpp>
#include <ibmpctl.hpp>

#include "notebook.h"

/**************************************************************************
* Class ABitmapNotebook -- Main window that displays a notebook containg  *
*   four bitmaps.                                                         *
**************************************************************************/
class ABitmapNotebook : public IFrameWindow
{
  public:
/*---------------------------- Constructor -------------------------------|
| Construct the object with:                                              |
| 1) the window id                                                        |
-------------------------------------------------------------------------*/
    ABitmapNotebook(unsigned long windowId);

/*----------------------------- Destructor -------------------------------|
| Destruct the object with:                                               |
| 1) the window id                                                        |
-------------------------------------------------------------------------*/
    virtual
     ~ABitmapNotebook() { };

  private:
    IResourceLibrary
      reslib;
    ISize
      tabSize;
    IBitmapHandle
      tab1,
      tab2,
      tab3,
      tab4;
    INotebook
      notebook;
    IViewPort
      viewport1,
      viewport2,
      viewport3,
      viewport4;
    IBitmapControl
      bitmap1,
      bitmap2,
      bitmap3,
      bitmap4;
};

#endif
