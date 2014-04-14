/******************************************************************************
* .FILE:         mmremote.hpp                                                 *
*                                                                             *
* .DESCRIPTION:  Multimedia Remote-Control Sample:     Class Definition       *
*                                                                             *
* .CLASSES:      KeyPad                                                       *
*                MainWindow                                                   *
*                MainHandler                                                  *
*                MainObserver                                                 *
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
#ifndef _MMREMOTE_
#define _MMREMOTE_
#include <icolor.hpp>
#include <ianimbut.hpp>
#include <iframe.hpp>
#include <icmdhdr.hpp>
#include <immcdda.hpp>
#include <immwave.hpp>
#include <immdigvd.hpp>
#include <immsequ.hpp>
#include <immtime.hpp>
#include <isetcv.hpp>
#include <imcelcv.hpp>
#include <ipushbut.hpp>
#include <ifiledlg.hpp>
#include <istattxt.hpp>
#include <iobservr.hpp>
#include <iflytext.hpp>
#include <iflyhhdr.hpp>
#include <ititle.hpp>
#include <itimer.hpp>
#include "mmremote.h"

class MainHandler;
class MainObserver;

//**************************************************************************
// Class:   Keypad                                                         *
//                                                                         *
// Purpose: Provide a keypad for use by the cd and video players.          *
//          It is a subclass of IMultiCell                                 *
//                                                                         *
//**************************************************************************
class KeyPad : public IMultiCellCanvas
{
public:

  KeyPad(unsigned long     windowid,
         IWindow*          parent,
         IWindow*          owner);

IPushButton
  one,
  two,
  three,
  four,
  five,
  six,
  seven,
  eight,
  nine,
  zero;

};

//**************************************************************************
// Class:   MainWindow                                                     *
//                                                                         *
// Purpose: Main Window for C++ mmremote sample application.               *
//          It is a subclass of IFrameWindow                               *
//                                                                         *
//**************************************************************************
class MainWindow : public IFrameWindow
{
public:                               //Define the Public Information

  MainWindow  ( unsigned long windowId);
virtual
  ~MainWindow ( );

MainWindow
  &newDigit(int digit);

void
  playTimeEvent();

ITitle
  title;

IMultiCellCanvas
  remoteCanvas,
  devices,
  controls,
  volkey,
  volume;

IAnimatedButton
  powerbtn,
  volupbtn,
  voldnbtn,
  playbtn ,
  stopbtn ,
  rewbtn  ,
  ffbtn   ,
  pausebtn,
  stepOrTrackFBtn,
  stepOrTrackBBtn,
  videobtn,
  midibtn,
  cdbtn,
  wavebtn;

IFlyText
  flyText;

IFlyOverHelpHandler
  flyHelpHandler;

IMMPlayableDevice
  *player;

IMMAudioCD
  *cdPlayer;

IMMDigitalVideo
  *digPlayer;

IMMSequencer
  *midPlayer;

IMMWaveAudio
  *wavPlayer;

unsigned long
  playerDevice;

KeyPad
  pad;

IStaticText
  readout;

ITimer
  playTimer;

int
  newTrackDigit1,
  newTrackDigit2;

MainHandler
  *handler;

MainObserver
  *observer;

unsigned long
  playHours,
  playMins,
  playSecs;

private:
};

class MainHandler : public ICommandHandler {
typedef ICommandHandler
  Inherited;
//**************************************************************************
// Class:   MainHandler                                                    *
//                                                                         *
// Purpose: Provide a Handler for processing the buttons.                  *
//                                                                         *
//**************************************************************************
public:

  MainHandler ();

/*---------------------------- Event Dispatching -----------------------------*/
virtual bool
  command (ICommandEvent& event);

};

class MainObserver : public IObserver {
typedef IObserver
  Inherited;
//**************************************************************************
// Class:   MainObserver                                                   *
//                                                                         *
// Purpose: Provide an Observer for processing the play notifications.     *
//                                                                         *
//**************************************************************************
public:

  MainObserver (MainWindow& mainPanel);

virtual MainObserver
  &dispatchNotificationEvent(const INotificationEvent&);

private:
MainWindow
  &panel;

};
#endif
