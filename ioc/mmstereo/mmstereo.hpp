/******************************************************************************
* .FILE:         mmstereo.hpp                                                 *
*                                                                             *
* .DESCRIPTION:  Multimedia Stereo Sample:             Class Definition       *
*                                                                             *
* .CLASSES:      MainWindow                                                   *
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
#ifndef _MMSTEREO_
#define _MMSTEREO_
#include <icolor.hpp>
#include <iframe.hpp>
#include <immcdda.hpp>
#include <immwave.hpp>
#include <immdigvd.hpp>
#include <immsequ.hpp>
#include <isetcv.hpp>
#include <ititle.hpp>
#include <iradiobt.hpp>
#include <iselhdr.hpp>
#include "mmstereo.h"
#include "mltamp.hpp"
#include "mltcd.hpp"
#include "mltwave.hpp"
#include "mltvid.hpp"
#include "ifont.hpp"


class MainWindow : public IFrameWindow, public ISelectHandler
{
//**************************************************************************
// Class:   MainWindow                                                     *
//                                                                         *
// Purpose: Main Window for C++ MltMedia sample application.               *
//          It is a subclass of IFrameWindow                               *
//                                                                         *
//**************************************************************************
public:                               //Define the Public Information

  MainWindow( unsigned long windowId);

  ~MainWindow();

  bool selected(IControlEvent& event);
  MainWindow& enableComponent( IMultiCellCanvas& component, bool enable );

private:
ITitle title;

ISetCanvas
  clientCanvas,
  selectorCanvas;

IRadioButton
  selectCD,
  selectWave,
  selectVideo;

IMMAudioCD
  *cdPlayer;

IMMWaveAudio
  *wavPlayer;

IMMDigitalVideo
  *vidPlayer;

IMMAmpMixer
  *ampMixer1,
  *ampMixer2,
  *ampMixer3;

Amp*
  amp;

CD*
  cd ;

WAVE*
  wave;

VIDEO*
  video;
};
#endif
