/******************************************************************************
* .FILE:         mltwave.cpp                                                  *
*                                                                             *
* .DESCRIPTION:  Multimedia Stereo Sample:             Class Implementation   *
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
#include <ireslib.hpp>
#include "mmstereo.hpp"
#include "mltwave.hpp"

/*------------------------------------------------------------------------------
| WAVE::WAVE                                                                   |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
WAVE::WAVE( IMMWaveAudio*     aWavePlayer,
            unsigned long     windowid,
            IWindow*          parent,
            IWindow*          owner)
   : IMMPlayerPanel(windowid,parent,owner,IMMDevice::waveAudio),
     readout     (WAVEREADOUTID, this,this),
     name        (WAVENAMEID, this, this),
     loadit      (LOADID,this,this,IRectangle(),
                  IWindow::visible | IAnimatedButton::animateWhenLatched),
     saveButton  (SAVEID,this,this),
     lineIn      (WAVELINEINID,this,this),
     microphone  (WAVEMICROPHONEID,this,this),
     pWavePlayer(aWavePlayer),
     observer(0),
     handler(0)
{

   IResourceLibrary reslib;
   setPlayableDevice(pWavePlayer);

   rec = new IAnimatedButton(RECID,this,this,IRectangle(),
                             ICustomButton::autoLatch |
                             ICustomButton::latchable |
                             IWindow::visible | IAnimatedButton::animateWhenLatched);
   saveButton.setText(reslib.loadString(STR_SAVE));
   lineIn.enableAutoSelect();
   lineIn.setText(STR_LINE_IN);
   microphone.enableAutoSelect();
   microphone.setText(STR_MIC);
   microphone.select();

   //Add the additional buttons to the player panel.
   addToCell(rec      ,     7, 1, 1, 2);
   addToCell(&lineIn   ,    8, 1, 1, 1);
   addToCell(&microphone,   8, 2, 1, 1);
   addToCell(&saveButton,   9, 1, 1, 1);
   addToCell(&readout ,    11, 1, 1, 2);
   addToCell(&loadit  ,    13, 1, 1, 2);
   addToCell(&name    ,     2, 3, 11, 1);
   rec->disable();
   playButton()->disable();
   saveButton.disable();
   rewindButton()->disable();
   fastForwardButton()->disable();

   //Put the bitmaps on the buttons.
   rec->setBitmaps(IAnimatedButton::record);
   loadit.setBitmaps(IAnimatedButton::eject);

   //Put text on the buttons.
   rec->setText(STR_RECORD);
   loadit.setText(STR_LOAD);

   //Set up the title
   name.setText(TITLE_WAV_PLAYER);
   name.setForegroundColor(IColor(IColor::kRed));

   //Set up the display
   readout.setForegroundColor(IColor(0,160,0));
   readout.setBackgroundColor(IColor(IColor::kBlack));
   readout.setText(reslib.loadString(STR_LTIME_DEF));
   readout.setLimit(22);

   if (pWavePlayer)
   {
      handler  = new WaveHandler();
      handler->handleEventsFor(this);
      observer = new WaveObserver(*this);
      observer->handleNotificationsFor(*pWavePlayer);
   }
}


/*------------------------------------------------------------------------------
| WAVE::~WAVE                                                                      |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
WAVE::~WAVE()
{
  if (observer)
     observer->stopHandlingNotificationsFor(*pWavePlayer);
  if (handler)
     handler->stopHandlingEventsFor(this);
}

/*------------------------------------------------------------------------------
| WAVE::recordButton                                                           |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
IAnimatedButton* WAVE::recordButton () const
{
  return rec;
}

/*------------------------------------------------------------------------------
| WAVE::wavePlayer                                                             |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
IMMWaveAudio* WAVE::wavePlayer () const
{
  return pWavePlayer;
}


/*------------------------------------------------------------------------------
| WaveHandler::WaveHandler                                                     |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
WaveHandler::WaveHandler()
          : WaveHandler::Inherited()
{}

/*------------------------------------------------------------------------------
| WaveHandler::command                                                         |
|                                                                              |
------------------------------------------------------------------------------*/
bool WaveHandler::command(ICommandEvent& event)
{
  bool handled = false;
  WAVE* panel = 0;
  IResourceLibrary reslib;
  switch (event.commandId())
  {
    case LOADID:
         {
         panel = (WAVE*) (event.controlWindow());
         IFileDialog::Settings fdSettings;
         fdSettings.setTitle(STR_LOAD_NEW);
         fdSettings.setFileName(reslib.loadString(STR_WAV_EXT));
         IFileDialog fd(panel->desktopWindow(),panel,fdSettings);
         if (fd.pressedOK())
         {
            panel->wavePlayer()->loadOnThread(fd.fileName());
            stop(*panel);
            panel->wavePlayer()->startPositionTracking(IMMTime(3000));
            panel->recordButton()->enable();
            panel->playButton()->enable();
            panel->rewindButton()->enable();
            panel->fastForwardButton()->enable();
            panel->saveButton.enable();
         }
         }
         handled=true;
         break;
    case SAVEID:
         panel = (WAVE*) (event.controlWindow());
         stop(*panel);
         panel->wavePlayer()->save();
         handled=true;
         break;
    case RECID:
         panel = (WAVE*) (event.controlWindow());
         panel->stopButton()->enable();
         panel->pauseButton()->disable();
         panel->playButton()->disable();
         panel->rewindButton()->disable();
         panel->fastForwardButton()->disable();
         if (panel->lineIn.isSelected())
            panel->wavePlayer()->enableConnector(IMMDevice::lineIn);
         else
            panel->wavePlayer()->enableConnector(IMMDevice::microphones);
         panel->wavePlayer()->acquire(IMMDevice::isolatedExclusive);
         panel->wavePlayer()->record();
         handled = true;
         break;
    default:
         handled = Inherited::command(event);
         break;
  } /* endswitch */
  return handled;
}

/*------------------------------------------------------------------------------
| WaveHandler::stop                                                            |
|                                                                              |
------------------------------------------------------------------------------*/
bool WaveHandler::stop(const IMMPlayerPanel& panel)
{
  panel.playButton()->enable();
  panel.rewindButton()->enable();
  panel.fastForwardButton()->enable();
  bool retval = Inherited::stop(panel);
  panel.playableDevice()->release();
  return retval;
}

/*------------------------------------------------------------------------------
| WaveObserver::WaveObserver                                                   |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
WaveObserver::WaveObserver(WAVE& wavePanel)
          : WaveObserver::Inherited(),
          panel(wavePanel)
{}

/*------------------------------------------------------------------------------
| WaveObserver::dispatchNotificationEvent                                      |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
WaveObserver& WaveObserver::dispatchNotificationEvent(const INotificationEvent& event)
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
         if (panel.wavePlayer()->mode()==IMMDevice::playing)
            panel.playButton()->latch();
   } /* endif */
   if (event.notificationId() == IMMDevice::commandNotifyId)
   {
      IMMNotifyEvent* notifyEvent = (IMMNotifyEvent*)(event.eventData().asUnsignedLong());
      if (notifyEvent->command() == IMMNotifyEvent::play)
         panel.playButton()->unlatch();
      if (notifyEvent->command() == IMMNotifyEvent::record)
         panel.recordButton()->unlatch();
   } /* endif */
   return *this;
}
