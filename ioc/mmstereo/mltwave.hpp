/******************************************************************************
* .FILE:         mltwave.hpp                                                  *
*                                                                             *
* .DESCRIPTION:  Multimedia Stereo Sample:             Class Definition       *
*                                                                             *
* .CLASSES:      WAVE                                                         *
*                WaveHandler                                                  *
*                WaveObserver                                                 *
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
#ifndef _MLTWAVE_
#define _MLTWAVE_
#include <imcelcv.hpp>
#include <immwave.hpp>
#include <ifont.hpp>
#include <immttime.hpp>
#include <inotifev.hpp>
#include <icolor.hpp>
#include <ianimbut.hpp>
#include <icmdhdr.hpp>
#include <istattxt.hpp>
#include <iobservr.hpp>
#include <immplypn.hpp>
#include <immplyhd.hpp>
#include <ifiledlg.hpp>
#include <iradiobt.hpp>
#include <ipushbut.hpp>
#include "mltwave.h"

class WaveHandler;
class WaveObserver;

class WAVE  : public IMMPlayerPanel {
//**************************************************************************
// Class:   WAVE                                                           *
//                                                                         *
// Purpose: Provide a Wave player.                                         *
//          It is a subclass of IMMPlayerPanel                             *
//                                                                         *
//**************************************************************************
public:

  WAVE( IMMWaveAudio*     wave,
        unsigned long     windowid,
        IWindow*          parent,
        IWindow*          owner);

  ~WAVE();

IAnimatedButton
  *recordButton       () const;

/*-------------------------------- Device ------------------------------------*/
IMMWaveAudio*
  wavePlayer          () const;

IStaticText
  name,
  readout;

IRadioButton
  lineIn,
  microphone;

IPushButton
  saveButton;

private:
IMMWaveAudio
  *pWavePlayer;

IAnimatedButton
  loadit,
  *rec;

WaveHandler
  *handler;

WaveObserver
  *observer;

};

class WaveHandler : public IMMPlayerPanelHandler {
typedef IMMPlayerPanelHandler
  Inherited;
//**************************************************************************
// Class:   WaveHandler                                                    *
//                                                                         *
// Purpose: Provide a Handler for processing the load and record buttons   *
//                                                                         *
//**************************************************************************
public:

  WaveHandler ();

/*---------------------------- Event Dispatching -----------------------------*/
virtual bool
  command (ICommandEvent& event);

/*----------------------------- Event Processing -----------------------------*/
virtual bool
  stop               (const IMMPlayerPanel& panel);

};

class WaveObserver : public IObserver {
typedef IObserver
  Inherited;
//**************************************************************************
// Class:   WaveObserver                                                   *
//                                                                         *
// Purpose: Provide an Observer for processing the play notifications.     *
//                                                                         *
//**************************************************************************
public:

  WaveObserver (WAVE& wavePanel);

virtual WaveObserver
  &dispatchNotificationEvent(const INotificationEvent&);

private:
WAVE
  &panel;

};
#endif
