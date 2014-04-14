/******************************************************************************
* .FILE:         mltvid.cpp                                                   *
*                                                                             *
* .DESCRIPTION:  Multimedia Stereo Sample:             Class Implementation   *
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
#include <ireslib.hpp>
#include "mmstereo.hpp"
#include "mltvid.hpp"

/*------------------------------------------------------------------------------
| VIDEO::VIDEO                                                                   |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
VIDEO::VIDEO( IMMDigitalVideo*  aVideoPlayer,
              unsigned long     windowid,
              IWindow*          parent,
              IWindow*          owner)
     : IMMPlayerPanel(windowid,parent,owner,IMMDevice::digitalVideo),
       readout       (VIDEOREADOUTID, this,this),
       name          (VIDEONAMEID, this, this),
       pVideoPlayer  (aVideoPlayer),
       observer      (0),
       handler       (0)
{
   setPlayableDevice(pVideoPlayer);

   loadit= new IAnimatedButton(VIDEOLOADID,this,this,IRectangle(),
                    IWindow::visible | IAnimatedButton::animateWhenLatched);
   //Add the additional buttons to the player panel.
   addToCell(&readout ,     9, 1, 1, 2);
   addToCell(loadit   ,    11, 1, 1, 2);
   addToCell(&name    ,     2, 3, 8, 1);
   playButton()->disable();
   rewindButton()->disable();
   fastForwardButton()->disable();
   stepForwardButton()->disable();
   stepBackwardButton()->disable();

   //Put the bitmaps on the button.
   loadit->setBitmaps(IAnimatedButton::eject);

   //Put text on the button.
   loadit->setText(STR_LOAD_VID);

   //Set up the title
   name.setText(TITLE_VID_PLAYER);
   name.setForegroundColor(IColor(IColor::kRed));

   //Set up the display
   readout.setForegroundColor(IColor(0,160,0));
   readout.setBackgroundColor(IColor(IColor::kBlack));
   readout.setText(STR_DEF_TIME);
   readout.setLimit(22);

   if (pVideoPlayer)
   {
      handler  = new VideoHandler();
      handler->handleEventsFor(this);
      observer = new VideoObserver(*this);
      observer->handleNotificationsFor(*pVideoPlayer);
   }
}


/*------------------------------------------------------------------------------
| VIDEO::~VIDEO                                                                      |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
VIDEO::~VIDEO()
{
  if (observer)
     observer->stopHandlingNotificationsFor(*pVideoPlayer);
  if (handler)
     handler->stopHandlingEventsFor(this);
}


/*------------------------------------------------------------------------------
| VIDEO::videoPlayer                                                             |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
IMMDigitalVideo* VIDEO::videoPlayer () const
{
  return pVideoPlayer;
}


/*------------------------------------------------------------------------------
| VideoHandler::VideoHandler                                                     |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
VideoHandler::VideoHandler()
          : VideoHandler::Inherited()
{}

/*------------------------------------------------------------------------------
| VideoHandler::command                                                         |
|                                                                              |
------------------------------------------------------------------------------*/
bool VideoHandler::command(ICommandEvent& event)
{
  bool handled = false;
  VIDEO* panel = 0;
  IResourceLibrary reslib;

  switch (event.commandId())
  {
    case VIDEOLOADID:
         {
         panel = (VIDEO*) (event.controlWindow());
         IFileDialog::Settings fdSettings;
         fdSettings.setTitle(STR_LOAD_VID_FILE);
         fdSettings.setFileName(reslib.loadString(STR_AVI_EXT));
         IFileDialog fd(panel->desktopWindow(),panel,fdSettings);
         if (fd.pressedOK())
         {
            panel->videoPlayer()->loadOnThread(fd.fileName());
            stop(*panel);
            panel->videoPlayer()->startPositionTracking(IMMTime(3000));
            panel->playButton()->enable();
            panel->rewindButton()->enable();
            panel->fastForwardButton()->enable();
            panel->stepForwardButton()->enable();
            panel->stepBackwardButton()->enable();
         }
         }
         handled=true;
         break;
    default:
         handled = Inherited::command(event);
         break;
  } /* endswitch */
  return handled;
}


/*------------------------------------------------------------------------------
| VideoObserver::VideoObserver                                                   |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
VideoObserver::VideoObserver(VIDEO& videoPanel)
          : VideoObserver::Inherited(),
          panel(videoPanel)
{}

/*------------------------------------------------------------------------------
| VideoObserver::dispatchNotificationEvent                                      |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
VideoObserver& VideoObserver::dispatchNotificationEvent(const INotificationEvent& event)
{
   IResourceLibrary reslib;
   if (event.notificationId() == IMMDevice::positionChangeId)
   {
      IMMPositionChangeEvent* positionEvent = (IMMPositionChangeEvent*)(event.eventData().asUnsignedLong());

      IMMTime time(positionEvent->position());
      panel.readout.setText(
                      IString(time.hours()).rightJustify(2,'0') +
                      reslib.loadString(STR_COLON) +
                      IString(time.minutes()).rightJustify(2,'0') +
                      reslib.loadString(STR_COLON) +
                      IString(time.seconds()).rightJustify(2,'0'));
      if (!panel.playButton()->isLatched())
         if (panel.videoPlayer()->mode()==IMMDevice::playing)
            panel.playButton()->latch();
   } /* endif */
   if (event.notificationId() == IMMDevice::commandNotifyId)
   {
      IMMNotifyEvent* notifyEvent = (IMMNotifyEvent*)(event.eventData().asUnsignedLong());
      if (notifyEvent->command() == IMMNotifyEvent::play)
         panel.playButton()->unlatch();
   } /* endif */
   return *this;
}
