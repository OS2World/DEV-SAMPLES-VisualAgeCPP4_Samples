/******************************************************************************
* .FILE:         mltamp.hpp                                                   *
*                                                                             *
* .DESCRIPTION:  Multimedia Stereo Sample:             Class Definitions      *
*                                                                             *
* .CLASSES:      Amp                                                          *
*                AmpHandler                                                   *
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
#ifndef _MLTAMP_
#define _MLTAMP_
#include <imcelcv.hpp>
#include <immamix.hpp>
#include <icslider.hpp>
#include <isldahdr.hpp>
#include <ictlevt.hpp>
#include <istattxt.hpp>
#include "mltamp.h"

class AmpHandler    : public ISliderArmHandler {
typedef ISliderArmHandler
  Inherited;
//**************************************************************************
// Class:   AmpHandler                                                     *
//                                                                         *
// Purpose: Provide a Handler for processing the sliders on the Amp.       *
//          It is a subclass of ISliderArmHandler                          *
//                                                                         *
//**************************************************************************
public:

  AmpHandler ();

virtual bool
  moving     (IControlEvent& evt);
};


class Amp    : public IMultiCellCanvas {
//**************************************************************************
// Class:   Amp                                                            *
//                                                                         *
// Purpose: Provide a Amp for use by all of the devices.                   *
//          It is a subclass of IMultiCell                                 *
//                                                                         *
//**************************************************************************
public:

  Amp(IMMAmpMixer*      pAmp1,
      IMMAmpMixer*      pAmp2,
      IMMAmpMixer*      pAmp3,
      unsigned long     windowid,
      IWindow*          parent,
      IWindow*          owner);

ICircularSlider
  slVolume,
  slBalance,
  slBass,
  slTreble,
  slPitch,
  slGain;


IMMAmpMixer
  *pAmpMixer1,
  *pAmpMixer2,
  *pAmpMixer3;

AmpHandler
  ampHandler;

IStaticText
  name;
};
#endif
