/******************************************************************************
* .FILE:         mltcd.hpp                                                    *
*                                                                             *
* .DESCRIPTION:  Multimedia Stereo Sample:             Class Definition       *
*                                                                             *
* .CLASSES:      CD                                                           *
*                CDHandler                                                    *
*                CDObserver                                                   *
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
#ifndef _MLTCD_
#define _MLTCD_
#include <immcdda.hpp>
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
#include "mltcd.h"

class CDHandler;
class CDObserver;

class CD  : public IMMPlayerPanel {
//**************************************************************************
// Class:   CD                                                             *
//                                                                         *
// Purpose: Provide a CD player.                                           *
//          It is a subclass of IMMPlayerPanel                             *
//                                                                         *
//**************************************************************************
  public:

    CD( IMMAudioCD*       cd,
        unsigned long     windowid,
        IWindow*          parent,
        IWindow*          owner);

    ~CD();

    IAnimatedButton
     *ejectButton              () const,
     *scanForwardButton        () const,
     *scanBackwardButton       () const;
    void
      playTimeEvent();


/*-------------------------------- Device ------------------------------------*/
    IMMAudioCD*
      cdPlayer() const;

    IStaticText
      name,
      discReadout,
      readout;

  private:
    IMMAudioCD
      *pCDPlayer;

    IAnimatedButton
      *trackF,
      *trackB,
      *scanF,
      *scanB,
      *eject;

    CDHandler
      *handler;

    CDObserver
      *observer;

};

class CDHandler : public IMMPlayerPanelHandler {
typedef IMMPlayerPanelHandler
  Inherited;
//**************************************************************************
// Class:   CDHandler                                                      *
//                                                                         *
// Purpose: Provide a Handler for processing the track and scan buttons    *
//                                                                         *
//**************************************************************************
  public:

    CDHandler ();

/*---------------------------- Event Dispatching -----------------------------*/
    virtual bool
      command (ICommandEvent& event);

/*----------------------------- Event Processing -----------------------------*/
    virtual bool
      rewind      (const IMMPlayerPanel& panel),
      fastForward (const IMMPlayerPanel& panel);

};

class CDObserver : public IObserver {
typedef IObserver
  Inherited;
//**************************************************************************
// Class:   CDObserver                                                     *
//                                                                         *
// Purpose: Provide an Observer for processing the play notifications.     *
//                                                                         *
//**************************************************************************
  public:

    CDObserver (CD& cdPanel);

    virtual CDObserver
      &dispatchNotificationEvent(const INotificationEvent&);

  private:
    CD
      &panel;

};
#endif
