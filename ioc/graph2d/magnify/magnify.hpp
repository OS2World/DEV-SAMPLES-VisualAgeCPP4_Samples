// Revision: 17 1.4.1.2 samples/graph2d/magnify/magnify.hpp, ocsamples-L1, ioc.v400, 981111 
/******************************************************************************
* .FILE:         magnify.hpp                                                  *
*                                                                             *
* .DESCRIPTION:  Magnify Sample Program:  Class Header                        *
*                                                                             *
* .CLASSES:      MagnifyWindow                                                *
*                MagnifyHandler                                               *
*                                                                             *
* .NOTE: WE RECOMMEND USING A FIXED SPACE FONT TO LOOK AT THE SOURCE          *
*                                                                             *
******************************************************************************/
/*
-------------------------------------------------------------------------------
Copyright (c) IBM Corporation 1992, 1997.
All Rights Reserved.

Permission is granted to copy, use, modify, and merge this software into your
applications and to permit others to do any of the foregoing. You must include
this permission and copyright notice in all copies and modified versions of
this software. THIS SOFTWARE IS PROVIDED IN ITS 'AS IS' CONDITION. TALIGENT
AND IBM DISCLAIM ANY LIABILITY OF ANY KIND FOR DAMAGES WHATSOEVER RESULTING
FROM THE USE OF THIS SOFTWARE.
-------------------------------------------------------------------------------
*/
#ifndef _MAGNIFY_HPP
#define _MAGNIFY_HPP

#include <iapp.hpp>
#include <ibmpctl.hpp>
#include <icmdhdr.hpp>
#include <iframe.hpp>
#include <iimage.hpp>
#include <ipushbut.hpp>
#include <isetcv.hpp>
#include <ispinnum.hpp>
#include <istattxt.hpp>
#include <itimer.hpp>
#include <ititle.hpp>

#include "magnify.h"

class MagnifyHandler : public ICommandHandler
{
/*----------------------------------------------------------------------------|
| command - An overloaded function that handles command events                |
-----------------------------------------------------------------------------*/
protected:
  bool command (ICommandEvent& event);
};

class MagnifyWindow : public IFrameWindow
{
public:
/*------------------------------- Constructor --------------------------------|
| Constructs the object with:                                                 |
| 1) No parameters                                                            |
-----------------------------------------------------------------------------*/
  MagnifyWindow      ();
virtual
  ~MagnifyWindow     ();

/*----------------------------------------------------------------------------|
| timerFunction - A function that is called after the timer expiring          |
-----------------------------------------------------------------------------*/
  void timerFunction ();

/*----------------------------------------------------------------------------|
| saveFile - Function to save the captured image to a file.                   |
-----------------------------------------------------------------------------*/
  bool
    saveFile();

/*----------------------------------------------------------------------------|
| magnify  - Function to start/stop capturing the screen under the cursor.    |
-----------------------------------------------------------------------------*/
  void
    magnify();


private:
  IBitmapControl
    bitmapControl;
  ISetCanvas
    canvas;
  IStaticText
    xText;
  INumericSpinButton
    xSpin;
  IStaticText
    yText;
  INumericSpinButton
    ySpin;
  MagnifyHandler
    handler;
  IImage
   *bitmap;
  ITitle
    title;

  IPushButton
    button;
  ITimer
    timer;
  IPushButton
    savebut;

};

#endif // _MAGNIFY_HPP
