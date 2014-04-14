/******************************************************************************
* .FILE:         mltcd.cpp                                                    *
*                                                                             *
* .DESCRIPTION:  Multimedia Stereo Sample:             Class Implementation   *
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
#include <ireslib.hpp>
#include "mmstereo.hpp"
#include "mltcd.hpp"

/*------------------------------------------------------------------------------
| CD::CD                                                                       |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
CD::CD( IMMAudioCD*       cd,
        unsigned long     windowid,
        IWindow*          parent,
        IWindow*          owner)
   : IMMPlayerPanel(windowid,parent,owner,IMMDevice::audioCD),
     readout     (READOUTID, this,this),
     discReadout (DISCREADOUTID, this,this),
     name        (CDNAMEID, this, this),
     pCDPlayer(cd),
     observer(0),
     handler(0)
{
   IResourceLibrary reslib;
   setPlayableDevice(pCDPlayer);

   eject = new IAnimatedButton(EJECTID,this,this,IRectangle(),
                     ICustomButton::autoLatch |
                     IWindow::visible | IAnimatedButton::animateWhenLatched);
   trackF= new IAnimatedButton(TRACKFID,this,this,IRectangle(),
                     IWindow::visible | IAnimatedButton::animateWhenLatched);
   trackB= new IAnimatedButton(TRACKBID,this,this,IRectangle(),
                     IWindow::visible | IAnimatedButton::animateWhenLatched);
   scanF = new IAnimatedButton(SCANFID,this,this,IRectangle(),
                     ICustomButton::autoLatch |
                     ICustomButton::latchable |
                     IWindow::visible | IAnimatedButton::animateWhenLatched);
   scanB = new IAnimatedButton(SCANBID,this,this,IRectangle(),
                     ICustomButton::autoLatch |
                     ICustomButton::latchable |
                     IWindow::visible | IAnimatedButton::animateWhenLatched);

   //Add the additional buttons to the player panel.
   addToCell(trackB   ,     7, 1, 1, 1);
   addToCell(trackF   ,     8, 1, 1, 1);
   addToCell(scanB    ,    10, 1, 1, 1);
   addToCell(scanF    ,    11, 1, 1, 1);
   addToCell(&readout ,    13, 1, 1, 2);
   addToCell(&discReadout ,13, 3, 1, 1);
   addToCell(eject    ,    15, 1, 1, 1);
   addToCell(&name    ,     2, 3, 12, 1);
   setRowHeight(4,4);

   //Put the bitmaps on the buttons.
   trackB->setBitmaps(IAnimatedButton::trackReverse);
   trackF->setBitmaps(IAnimatedButton::trackAdvance);
   scanB->setBitmaps(IAnimatedButton::scanBackward);
   scanF->setBitmaps(IAnimatedButton::scanForward);
   eject->setBitmaps(IAnimatedButton::eject);


   //Set up the title
   name.setText(TITLE_CD_PLAYER);
   name.setForegroundColor(IColor(IColor::kRed));

   //Set up the display
   readout.setForegroundColor(IColor(0,160,0));
   readout.setBackgroundColor(IColor(IColor::kBlack));
   readout.setText(reslib.loadString(STR_INIT_DISP));
   readout.setLimit(24);

   //Set up the disc and track display
   discReadout.setForegroundColor(IColor(0,160,0));
   discReadout.setBackgroundColor(IColor(IColor::kBlack));
   discReadout.setLimit(24);
   discReadout.setText(reslib.loadString(STR_NO_TITLE));

   if (pCDPlayer)
   {
      handler  = new CDHandler();
      handler->handleEventsFor(this);
      observer = new CDObserver(*this);
      observer->handleNotificationsFor(*pCDPlayer);
      if (!pCDPlayer->isMediaPresent())
      {
         disable();
         eject->latch();
         discReadout.setText(reslib.loadString(STR_INSERT));
      }
   }
   else
     discReadout.setText(reslib.loadString(STR_NO_DEVICE));

}


/*------------------------------------------------------------------------------
| CD::~CD                                                                      |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
CD::~CD()
{
  if (observer)
     observer->stopHandlingNotificationsFor(*pCDPlayer);
  if (handler)
     handler->stopHandlingEventsFor(this);
}

/*------------------------------------------------------------------------------
| CD::scanForwardButton                                                        |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
IAnimatedButton* CD::scanForwardButton () const
{
  return scanF;
}

/*------------------------------------------------------------------------------
| CD::scanBackwardButton                                                       |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
IAnimatedButton* CD::scanBackwardButton () const
{
  return scanB;
}

/*------------------------------------------------------------------------------
| CD::ejectButton                                                              |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
IAnimatedButton* CD::ejectButton () const
{
  return eject;
}

/*------------------------------------------------------------------------------
| CD::CDPlayer                                                                 |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
IMMAudioCD* CD::cdPlayer () const
{
  return pCDPlayer;
}

/*------------------------------------------------------------------------------
| CDHandler::CDHandler                                                         |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
CDHandler::CDHandler()
          : CDHandler::Inherited()
{}

/*------------------------------------------------------------------------------
| CDHandler::command                                                           |
|                                                                              |
------------------------------------------------------------------------------*/
bool CDHandler::command(ICommandEvent& event)
{
  bool handled = false;
  CD* panel = 0;

  switch (event.commandId())
  {
    case EJECTID:
         panel = (CD*) (event.controlWindow());
         if (panel->cdPlayer())
         {
            if (panel->cdPlayer()->isMediaPresent())
               panel->cdPlayer()->openDoor();
         }
         handled=true;
         break;
    case TRACKBID:
         panel = (CD*) (event.controlWindow());
         panel->cdPlayer()->trackBackward();
         handled=true;
         break;
    case TRACKFID:
         panel = (CD*) (event.controlWindow());
         panel->cdPlayer()->trackForward();
         handled=true;
         break;
    case SCANFID:
         panel = (CD*) (event.controlWindow());
         if (panel->scanForwardButton()->isLatched())
            panel->cdPlayer()->startScanningForward();
         handled=true;
         break;
    case SCANBID:
         panel = (CD*) (event.controlWindow());
         if (panel->scanBackwardButton()->isLatched())
            panel->cdPlayer()->startScanningBackward();
         handled=true;
         break;
    default:
         handled = Inherited::command(event);
         break;
  } /* endswitch */
  return handled;
}

/*------------------------------------------------------------------------------
| CDHandler::rewind                                                            |
|                                                                              |
------------------------------------------------------------------------------*/
bool CDHandler::rewind(const IMMPlayerPanel& panel)
{
  IResourceLibrary reslib;
  IMMAudioCD* device = (IMMAudioCD*)(panel.playableDevice());
  CD* cdpanel = (CD*)(&panel);
  bool ret = Inherited::rewind(panel);
  IMMAudioCDContents contents = device->contents();
  IMMTrackMinSecFrameTime time(contents,device->position());
  cdpanel->readout.setText(IString(reslib.loadString(STR_TRACK)) +
                  IString(time.track()).rightJustify(2,'0') +
                  IString(reslib.loadString(STR_PAD)) +
                  IString(time.minutes()).rightJustify(2,'0') +
                  IString(reslib.loadString(STR_COLON)) +
                  IString(time.seconds()).rightJustify(2,'0'));
  return ret;
}

/*------------------------------------------------------------------------------
| CDHandler::fastForward                                                       |
|                                                                              |
------------------------------------------------------------------------------*/
bool CDHandler::fastForward(const IMMPlayerPanel& panel)
{
  IResourceLibrary reslib;
  IMMAudioCD* device = (IMMAudioCD*)(panel.playableDevice());
  CD* cdpanel = (CD*)(&panel);
  bool ret = Inherited::fastForward(panel);
  IMMAudioCDContents contents = device->contents();
  IMMTrackMinSecFrameTime time(contents,device->position());
  cdpanel->readout.setText(IString(reslib.loadString(STR_TRACK)) +
                  IString(time.track()).rightJustify(2,'0') +
                  IString(reslib.loadString(STR_PAD)) +
                  IString(time.minutes()).rightJustify(2,'0') +
                  IString(reslib.loadString(STR_COLON)) +
                  IString(time.seconds()).rightJustify(2,'0'));
  return ret;
}

/*------------------------------------------------------------------------------
| CDObserver::CDObserver                                                       |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
CDObserver::CDObserver(CD& cdPanel)
          : CDObserver::Inherited(),
          panel(cdPanel)
{}

/*-------------------------------------------------------------------------------
| CDObserver::dispatchNotificationEvent                                        |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
CDObserver& CDObserver::dispatchNotificationEvent(const INotificationEvent& event)
{
   IResourceLibrary reslib;
   if (event.notificationId() == IMMAudioCD::positionTimerId)
   {
      IMMTrackMinSecFrameTime* time = (IMMTrackMinSecFrameTime*)(event.eventData().asUnsignedLong());
      panel.readout.setText(IString(reslib.loadString(STR_TRACK)) +
                      IString(time->track()).rightJustify(2,'0') +
                      IString(reslib.loadString(STR_PAD)) +
                      IString(time->hours()).rightJustify(2,'0') +
                      IString(reslib.loadString(STR_COLON)) +
                      IString(time->minutes()).rightJustify(2,'0') +
                      IString(reslib.loadString(STR_COLON)) +
                      IString(time->seconds()).rightJustify(2,'0'));
      if (!panel.playButton()->isLatched())
         panel.playButton()->latch();
   } /* endif */
   else if (event.notificationId() == IMMAudioCD::trackStartedId)
   {
      IMMTrackMinSecFrameTime* time = (IMMTrackMinSecFrameTime*)(event.eventData().asUnsignedLong());
      panel.readout.setText(IString(reslib.loadString(STR_TRACK)) +
                      IString(time->track()).rightJustify(2,'0') +
                      IString(reslib.loadString(STR_PAD)) +
                      IString(time->hours()).rightJustify(2,'0') +
                      IString(reslib.loadString(STR_COLON)) +
                      IString(time->minutes()).rightJustify(2,'0') +
                      IString(reslib.loadString(STR_COLON)) +
                      IString(time->seconds()).rightJustify(2,'0'));
      IString discName( panel.cdPlayer()->discTitle() );
      IString trackName( panel.cdPlayer()->trackTitle(time->track()) );
      if ( discName == "" )
        discName = reslib.loadString( STR_NO_DISC_TITLE );
      if ( trackName == "" )
        trackName = reslib.loadString( STR_NO_TRACK_TITLE );
      panel.discReadout.setText(discName + reslib.loadString(STR_COLON) +
                                trackName);
      if (!panel.playButton()->isLatched())
         if (panel.cdPlayer()->mode()==IMMDevice::playing)
         {
            panel.playButton()->latch();
         }
   } /* endif */
   else if (event.notificationId() == IMMDevice::commandNotifyId)
   {
      IMMNotifyEvent* notifyEvent = (IMMNotifyEvent*)(event.eventData().asUnsignedLong());
      if (notifyEvent->command() == IMMNotifyEvent::play)
         panel.playButton()->unlatch();
   } /* endif */
   else if (event.notificationId() == IMMRemovableMedia::mediaLoadedId)
   {
      if (event.eventData().asUnsignedLong())
      {
         panel.enable();
         panel.ejectButton()->unlatch();
      } else {
         panel.disable();
         panel.ejectButton()->latch();
         panel.discReadout.setText(IString(reslib.loadString(STR_INSERT)));
      }
   } /* endif */
   return *this;
}
