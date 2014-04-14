/******************************************************************************
* .FILE:         mltvid.hpp                                                   *
*                                                                             *
* .DESCRIPTION:  Multimedia Stereo Sample:             Class Definition       *
*                                                                             *
* .CLASSES:      VIDEO                                                        *
*                VideoHandler                                                 *
*                VideoObserver                                                *
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
#ifndef _MLTVID_
#define _MLTVID_
#include <immdigvd.hpp>
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
#include "mltvid.h"

class VideoHandler;
class VideoObserver;

class VIDEO  : public IMMPlayerPanel {
//**************************************************************************
// Class:   VIDEO                                                          *
//                                                                         *
// Purpose: Provide a Video player.                                        *
//          It is a subclass of IMMPlayerPanel                             *
//                                                                         *
//**************************************************************************
public:

  VIDEO( IMMDigitalVideo*  pVideo,
         unsigned long     windowid,
         IWindow*          parent,
         IWindow*          owner);

  ~VIDEO();

/*-------------------------------- Device ------------------------------------*/
IMMDigitalVideo*
  videoPlayer          () const;

IStaticText
  name,
  readout;

private:
IMMDigitalVideo
  *pVideoPlayer;

IAnimatedButton
  *loadit;

VideoHandler
  *handler;

VideoObserver
  *observer;

};

class VideoHandler : public IMMPlayerPanelHandler {
typedef IMMPlayerPanelHandler
  Inherited;
//**************************************************************************
// Class:   VideoHandler                                                   *
//                                                                         *
// Purpose: Provide a Handler for processing the load button.              *
//                                                                         *
//**************************************************************************
public:

  VideoHandler ();

/*---------------------------- Event Dispatching -----------------------------*/
virtual bool
  command (ICommandEvent& event);

};

class VideoObserver : public IObserver {
typedef IObserver
  Inherited;
//**************************************************************************
// Class:   VideoObserver                                                  *
//                                                                         *
// Purpose: Provide an Observer for processing the play notifications.     *
//                                                                         *
//**************************************************************************
public:

  VideoObserver (VIDEO& videoPanel);

virtual VideoObserver
  &dispatchNotificationEvent(const INotificationEvent&);

private:
VIDEO
  &panel;

};
#endif
