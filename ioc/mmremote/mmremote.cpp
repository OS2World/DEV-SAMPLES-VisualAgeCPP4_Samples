/******************************************************************************
* .FILE:         mmremote.cpp                                                 *
*                                                                             *
* .DESCRIPTION:  Multimedia Remote-Control Sample:     Class Implementation   *
*                                                                             *
* .CLASSES:      KeyPad                                                       *
*                MainWindow                                                   *
*                MainHandler                                                  *
*                MainObserver                                                 *
*                                                                             *
* .COPYRIGHT:                                                                 *
*    IBM Open Class Library                                                   *
*    Licensed Material - Program-Property of IBM                              *
*    (C) Copyright IBM Corp. 1992, 1995 - All Rights Reserved                 *
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
#include <iapp.hpp>
#include <ifont.hpp>
#include <immttime.hpp>
#include <inotifev.hpp>
#include <imsgbox.hpp>
#include <icoordsy.hpp>
#include "mmremote.hpp"

//*************************************************************************
// main  - Application entry point                                        *
//*************************************************************************

int main()
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::kOriginLowerLeft );
  MainWindow  mainWindow(WINDOWID);
  IApplication::current().run();
  return 0;
}

//******************************************************************************
// KeyPad::KeyPad                                                              *
//   Defines the keypad 0-9 for entering tracks for the CD player or special   *
//   functions for the video player.                                           *
//******************************************************************************

KeyPad::KeyPad(unsigned long windowid,
               IWindow*          parent,
               IWindow*          owner)
      : IMultiCellCanvas(windowid,parent,owner),
        one             (ONEID   ,this  ,owner),
        two             (TWOID   ,this  ,owner),
        three           (THREEID ,this  ,owner),
        four            (FOURID  ,this  ,owner),
        five            (FIVEID  ,this  ,owner),
        six             (SIXID   ,this  ,owner),
        seven           (SEVENID ,this  ,owner),
        eight           (EIGHTID ,this  ,owner),
        nine            (NINEID  ,this  ,owner),
        zero            (ZEROID  ,this  ,owner)
{
   IResourceLibrary reslib;
   one.setText  (reslib.loadString(STR_ONE));
   two.setText  (reslib.loadString(STR_TWO));
   three.setText(reslib.loadString(STR_THREE));
   four.setText (reslib.loadString(STR_FOUR));
   five.setText (reslib.loadString(STR_FIVE));
   six.setText  (reslib.loadString(STR_SIX));
   seven.setText(reslib.loadString(STR_SEVEN));
   eight.setText(reslib.loadString(STR_EIGHT));
   nine.setText (reslib.loadString(STR_NINE));
   zero.setText (reslib.loadString(STR_ZERO));

//*****************************************************************************
//  Lay out the keypad multicell canvas - 3 columns, 4 rows, no margins       *
//*****************************************************************************

   addToCell(&one,           1, 1, 1, 1);
   addToCell(&two,           2, 1, 1, 1);
   addToCell(&three,         3, 1, 1, 1);
   addToCell(&four,          1, 2, 1, 1);
   addToCell(&five,          2, 2, 1, 1);
   addToCell(&six,           3, 2, 1, 1);
   addToCell(&seven,         1, 3, 1, 1);
   addToCell(&eight,         2, 3, 1, 1);
   addToCell(&nine,          3, 3, 1, 1);
   addToCell(&zero,          2, 4, 1, 1);
}
//*******************************************************************************
// MainWindow::~MainWindow                                                      *
//   Destruct the remote control main window                                    *
//                                                                              *
//*******************************************************************************

MainWindow::~MainWindow()
{
   if (cdPlayer)
      delete cdPlayer;
   if (digPlayer)
      delete digPlayer;
   if (midPlayer)
      delete midPlayer;
   if (wavPlayer)
      delete wavPlayer;
   if (handler)
      delete handler;
   if (observer)
      delete observer;
}

//*******************************************************************************
// MainWindow::MainWindow                                                       *
//   Construct the remote control main window                                   *
//                                                                              *
//*******************************************************************************

MainWindow::MainWindow( unsigned long windowId)
          : IFrameWindow(windowId),
            title(this),
            newTrackDigit1(0),
            newTrackDigit2(0),
            flyText(FLYTEXTID, this),
            flyHelpHandler(&flyText, 100, 5),


//*****************************************************************************
// remoteCanvas is the main canvas.  devices, controls, volkey, volume, and   *
// pad are canvases it contains                                               *
//*****************************************************************************

            remoteCanvas(REMOTECANVASID ,this,this),
            devices     (DEVID   ,&remoteCanvas,this),
            controls    (CTLID   ,&remoteCanvas,this),
            volkey      (VKID    ,&remoteCanvas,this),
            volume      (VOLUMEID,&volkey,this),
            pad         (PADID   ,&volkey,this),

//*****************************************************************************
//  These are the control buttons for the remote control                      *
//*****************************************************************************

            powerbtn        (POWERID ,&remoteCanvas,this,IRectangle(),
                            IWindow::visible | IAnimatedButton::animateWhenLatched),
            volupbtn        (VOLUPID ,&volume,this,IRectangle(),
                            IControl::group |
                            IWindow::visible | IAnimatedButton::animateWhenLatched),
            voldnbtn        (VOLDNID ,&volume,this,IRectangle(),
                            IWindow::visible | IAnimatedButton::animateWhenLatched),
            playbtn         (PLAYID  ,&controls,this,IRectangle(),
                            ICustomButton::latchable |
                            ICustomButton::autoLatch |
                            IControl::group |
                            IWindow::visible | IAnimatedButton::animateWhenLatched),
            stopbtn         (STOPID  ,&controls,this,IRectangle(),
                            IWindow::visible | IAnimatedButton::animateWhenLatched),
            rewbtn          (REWID   ,&controls,this,IRectangle(),
                            IWindow::visible | IAnimatedButton::animateWhenLatched),
            ffbtn           (FFID    ,&controls,this,IRectangle(),
                            IWindow::visible | IAnimatedButton::animateWhenLatched),
            pausebtn        (PAUSEID ,&controls,this,IRectangle(),
                            ICustomButton::latchable |
                            ICustomButton::autoLatch |
                            IWindow::visible | IAnimatedButton::animateWhenLatched),
            stepOrTrackFBtn (STEPTRACKFID ,&controls,this,IRectangle(),
                            IWindow::visible | IAnimatedButton::animateWhenLatched),
            stepOrTrackBBtn (STEPTRACKBID ,&controls,this,IRectangle(),
                            IWindow::visible | IAnimatedButton::animateWhenLatched),

//*****************************************************************************
//  These are the device selection buttons for video, midi, CD, and wave      *
//  players                                                                   *
//*****************************************************************************

            videobtn        (VIDEOID ,&devices,this,IRectangle(),
                            IControl::group |
                            ICustomButton::autoLatch |
                            IWindow::visible | IAnimatedButton::animateWhenLatched),
            midibtn         (MIDIID  ,&devices,this,IRectangle(),
                            ICustomButton::autoLatch |
                            IWindow::visible | IAnimatedButton::animateWhenLatched),
            cdbtn           (CDID    ,&devices,this,IRectangle(),
                            ICustomButton::autoLatch |
                            IWindow::visible | IAnimatedButton::animateWhenLatched),
            wavebtn         (WAVEID  ,&devices,this,IRectangle(),
                            ICustomButton::autoLatch |
                            IWindow::visible | IAnimatedButton::animateWhenLatched),

//*****************************************************************************
//  This is the status line for the playing device                            *
//*****************************************************************************

            readout     (READOUTID, &remoteCanvas,this),

//*****************************************************************************
//  Set the pointers for the devices to be zero.                              *
//*****************************************************************************
            player   (0),
            cdPlayer (0),
            digPlayer(0),
            midPlayer(0),
            wavPlayer(0),
            handler  (0),

//*****************************************************************************
//  Initialize the observer to this window.                                   *
//*****************************************************************************
            observer ( new MainObserver( *this ) )

//*****************************************************************************
//  Open the CD player.  If not ready, post message and allow retry or cancel.*
//  Then point the player to the default device - CD and set the device ID.   *
//*****************************************************************************

{
   IResourceLibrary reslib;
   title.setTitleText(WINDOWID);
   try
   {
      //***********************************************************************
      //  Construct the CD player. The default arguments cause the audio CD   *
      //  device to be opened so we don't need to make an additional open()   *
      //  call later.  Also, it uses the system profile for storing and       *
      //  retrieving information(track titles, disc titles, playback order of *
      //  the tracks).  If we get an error opening the audio CD device then   *
      //  the remote will not control the audio cd player.                    *
      //***********************************************************************
      cdPlayer = new IMMAudioCD();
      while (!cdPlayer->isMediaPresent())
      {
         IMessageBox::Response response = IMessageBox::cancel;
         IMessageBox msgBox(this);
         response = msgBox.show(reslib.loadString(STR_NOAUDCD),
                     IMessageBox::retryCancelButton  |
                     IMessageBox::errorIcon          |
                     IMessageBox::moveable );
         if (response == IMessageBox::cancel)
         {
            msgBox.show(reslib.loadString(STR_CDDIS),
                        IMessageBox::okButton  |
                        IMessageBox::errorIcon |
                        IMessageBox::moveable );
            cdbtn.disable();
            delete cdPlayer;
            cdPlayer = 0;
            break;
         }
      }
   }
   catch (IException& exc)
   {
      IMessageBox msgBox(this);
      msgBox.show(reslib.loadString(STR_NOCD),
                  IMessageBox::okButton  |
                  IMessageBox::errorIcon |
                  IMessageBox::moveable );
      cdbtn.disable();
   }

   if (cdPlayer)
   {
      player = cdPlayer;
      playerDevice = CDID;
      cdPlayer->enableNotification() ;
      try
      {
         //********************************************************************
         //  Allow CD sound to be played without a connector cable            *
         //********************************************************************
         cdPlayer->enableConnector(IMMDevice::cdStream);
      }
      catch (IException& exc)
      {
         IMessageBox msgBox(this);
         msgBox.show(reslib.loadString(STR_NOTRANS),
                     IMessageBox::okButton  |
                     IMessageBox::errorIcon |
                     IMessageBox::moveable );
      }
   } /* endif */

   try
   {
      wavPlayer = new IMMWaveAudio();
      if (wavPlayer)
      {
         player       = wavPlayer;
         playerDevice = WAVEID;
         wavPlayer->enableNotification();
      } /* endif */
   }
   catch (IException& exc)
   {
      IMessageBox msgBox(this);
      msgBox.show(reslib.loadString(STR_NOWAVE),
                  IMessageBox::okButton  |
                  IMessageBox::errorIcon |
                  IMessageBox::moveable );
      wavebtn.disable();
   }
   try
   {
      digPlayer = new IMMDigitalVideo();
      if (digPlayer)
      {
         player       = digPlayer;
         playerDevice = VIDEOID;
         digPlayer->enableNotification();
      } /* endif */
   }
   catch (IException& exc)
   {
      IMessageBox msgBox(this);
      msgBox.show(reslib.loadString(STR_NOVID),
                  IMessageBox::okButton  |
                  IMessageBox::errorIcon |
                  IMessageBox::moveable );
      videobtn.disable();
   }
   try
   {
      midPlayer = new IMMSequencer();
      if (midPlayer)
      {
         player       = midPlayer;
         playerDevice = MIDIID;
         midPlayer->enableNotification();
      } /* endif */
   }
   catch (IException& exc)
   {
      IMessageBox msgBox(this);
      msgBox.show(reslib.loadString(STR_NOMIDI),
                  IMessageBox::okButton  |
                  IMessageBox::errorIcon |
                  IMessageBox::moveable );
      midibtn.disable();
   }

//*****************************************************************************
//  Put the bitmaps on the buttons                                            *
//*****************************************************************************

   powerbtn.setBitmaps(BMPPOWER,1);
   volupbtn.setBitmaps(IAnimatedButton::volumeUp);
   voldnbtn.setBitmaps(IAnimatedButton::volumeDown);
   rewbtn.setBitmaps  (IAnimatedButton::rewind);
   ffbtn.setBitmaps   (IAnimatedButton::fastForward);
   pausebtn.setBitmaps(IAnimatedButton::pause);
   stopbtn.setBitmaps (IAnimatedButton::stop);
   playbtn.setBitmaps (IAnimatedButton::play);
   stepOrTrackBBtn.setBitmaps(IAnimatedButton::trackReverse);
   stepOrTrackFBtn.setBitmaps(IAnimatedButton::trackAdvance);
   videobtn.setBitmaps(BMPVIDEO,1);
   midibtn.setBitmaps (BMPMIDI ,1);
   cdbtn.setBitmaps   (BMPCD   ,1);
   wavebtn.setBitmaps (BMPWAVE ,1);

//*****************************************************************************
//  Set the text for each of the buttons.  The \n causes the following word   *
//  to be on a new line                                                       *
//*****************************************************************************

   powerbtn.setText(reslib.loadString(STR_POWER));
   volupbtn.setText(reslib.loadString(STR_VOLUMEUP));
   voldnbtn.setText(reslib.loadString(STR_VOLUMEDOWN));
   videobtn.setText(reslib.loadString(STR_VIDEO));
   midibtn.setText (reslib.loadString(STR_MIDI));
   cdbtn.setText   (reslib.loadString(STR_CD));
   wavebtn.setText (reslib.loadString(STR_WAVE));
//*****************************************************************************
//  Build the main canvas.  Columns 1 and 3 and rows 1 and 11 are margins     *
//*****************************************************************************

   remoteCanvas.addToCell(&powerbtn,      2, 2, 1, 1);
   remoteCanvas.addToCell(&devices,       2, 4, 1, 1);
   remoteCanvas.addToCell(&volkey,        2, 6, 1, 1);
   remoteCanvas.addToCell(&controls,      2, 8, 1, 1);
   remoteCanvas.addToCell(&readout,       2, 10, 1,1);
   remoteCanvas.setColumnWidth(1, MARGIN, true);
   remoteCanvas.setColumnWidth(3, MARGIN, true);
   remoteCanvas.setRowHeight  (1, MARGIN, true);
   remoteCanvas.setRowHeight  (11, MARGIN, true);

//*****************************************************************************
//  Calculate size for control buttons to keep them all the same.             *
//*****************************************************************************

   ISize bigbtn;
   bigbtn = bigbtn.maximum(playbtn.minimumSize());
   bigbtn = bigbtn.maximum(stopbtn.minimumSize());
   bigbtn = bigbtn.maximum(rewbtn.minimumSize());
   bigbtn = bigbtn.maximum(ffbtn.minimumSize());
   bigbtn = bigbtn.maximum(pausebtn.minimumSize());
   bigbtn = bigbtn.maximum(stepOrTrackBBtn.minimumSize());
   bigbtn = bigbtn.maximum(stepOrTrackFBtn.minimumSize());
   if (bigbtn.width() > bigbtn.height())
      bigbtn.setHeight(bigbtn.width());
   else bigbtn.setWidth(bigbtn.height());
   playbtn.setMinimumSize( bigbtn );
   stopbtn.setMinimumSize( bigbtn );
   rewbtn.setMinimumSize( bigbtn );
   ffbtn.setMinimumSize( bigbtn );
   pausebtn.setMinimumSize( bigbtn );
   stepOrTrackBBtn.setMinimumSize( bigbtn );
   stepOrTrackFBtn.setMinimumSize( bigbtn );

//*****************************************************************************
//  Build the controls canvas.  Columns 1 and 5 and rows 1 and 5 are margins  *
//*****************************************************************************

   controls.addToCell(&playbtn,         3, 2, 1, 1);
   controls.addToCell(&stopbtn,         3, 3, 1, 1);
   controls.addToCell(&rewbtn,          2, 2, 1, 1);
   controls.addToCell(&ffbtn,           4, 2, 1, 1);
   controls.addToCell(&pausebtn,        3, 4, 1, 1);
   controls.addToCell(&stepOrTrackBBtn, 2, 3, 1, 1);
   controls.addToCell(&stepOrTrackFBtn, 4, 3, 1, 1);
   controls.setColumnWidth(1, MARGIN, true);
   controls.setColumnWidth(5, MARGIN, true);
   controls.setRowHeight  (1, MARGIN, true);
   controls.setRowHeight  (5, MARGIN, true);

//*****************************************************************************
//  Calculate size for device buttons to keep them all the same.              *
//*****************************************************************************

   ISize biggest;
   biggest = biggest.maximum(videobtn.minimumSize());
   biggest = biggest.maximum(midibtn.minimumSize());
   biggest = biggest.maximum(cdbtn.minimumSize());
   biggest = biggest.maximum(wavebtn.minimumSize());
   videobtn.setMinimumSize( biggest );
   midibtn.setMinimumSize( biggest );
   cdbtn.setMinimumSize( biggest );
   wavebtn.setMinimumSize( biggest );

//*****************************************************************************
//  Build the devices canvas.  Columns 2, 4, and 6 are separators             *
//*****************************************************************************

   devices.addToCell(&videobtn,     1, 1, 1, 1);
   devices.addToCell(&midibtn,      3, 1, 1, 1);
   devices.addToCell(&cdbtn,        5, 1, 1, 1);
   devices.addToCell(&wavebtn,      7, 1, 1, 1);
   devices.setColumnWidth( 1, IMultiCellCanvas::defaultCell().width(), true);
   devices.setColumnWidth( 2, MARGIN);
   devices.setColumnWidth( 3, IMultiCellCanvas::defaultCell().width(), true);
   devices.setColumnWidth( 4, MARGIN);
   devices.setColumnWidth( 5, IMultiCellCanvas::defaultCell().width(), true);
   devices.setColumnWidth( 6, MARGIN);
   devices.setColumnWidth( 7, IMultiCellCanvas::defaultCell().width(), true);

//*****************************************************************************
//  Build the canvas containing the volume buttons                            *
//*****************************************************************************

   volume.addToCell(&volupbtn,      1, 1, 1, 1);
   volume.addToCell(&voldnbtn,      1, 2, 1, 1);

//*****************************************************************************
//  Build the canvas containing the keypad and volume buttons canvases        *
//*****************************************************************************

   volkey.addToCell(&pad,           1, 1, 1, 1);
   volkey.addToCell(&volume,        3, 1, 1, 1);
   volkey.setColumnWidth( 2, MARGIN, true);

//*****************************************************************************
//  Set the background color for all canvases to black                        *
//*****************************************************************************

   remoteCanvas.setBackgroundColor(IColor(IColor::kBlack));
   pad.setBackgroundColor(IColor(IColor::kBlack));
   devices.setBackgroundColor(IColor(IColor::kBlack));
   controls.setBackgroundColor(IColor(IColor::kBlack));
   volume.setBackgroundColor(IColor(IColor::kBlack));
   volkey.setBackgroundColor(IColor(IColor::kBlack));

//*****************************************************************************
//  Set up the readout for the player status line                             *
//*****************************************************************************

   readout.setForegroundColor(IColor(0,160,0));
   readout.setBackgroundColor(IColor(IColor::kBlack));
   readout.setText(IString(reslib.loadString(STR_TRACK)) + IString(newTrackDigit1) +
                   IString(newTrackDigit2) + IString(reslib.loadString(STR_PAD)) +
                   IString(reslib.loadString(STR_TIME_00)));
   ISize charSize = readout.characterSize();
   readout.setMinimumSize(ISize( charSize.width()*30, charSize.height()));

//*****************************************************************************
// Have the command handler handle events for this window                     *
//*****************************************************************************

   handler  = new MainHandler();
   handler->handleEventsFor(this);

   if (cdPlayer)
   {
      observer->handleNotificationsFor(*cdPlayer);
   }
   if (wavPlayer)
   {
      observer->handleNotificationsFor(*wavPlayer);
   }
   if (digPlayer)
   {
      observer->handleNotificationsFor(*digPlayer);
   }
   if (midPlayer)
   {
      observer->handleNotificationsFor(*midPlayer);
   }

//*****************************************************************************
//  Latch the button for the default device.  Until play is                   *
//  pressed, disable the stop and pause buttons. By doing this latching after *
//  the command handler is added, we can let the command handler do all of the*
//  setup(enable, disable, and latch) for the buttons.                        *
//*****************************************************************************

   switch (playerDevice)
   {
     case VIDEOID:
          videobtn.click();
          videobtn.latch();
          break;
     case MIDIID:
          midibtn.click();
          midibtn.latch();
          break;
     case CDID:
          cdbtn.click();
          cdbtn.latch();
          break;
     case WAVEID:
          wavebtn.click();
          wavebtn.latch();
          break;
     default:
          remoteCanvas.disable();
          break;
   } /* endswitch */


//*****************************************************************************
//  Set up the fly over help handler                                          *
//*****************************************************************************

   flyHelpHandler.handleEventsFor(this);

//*****************************************************************************
//  Size the window to it's minimum size, give it focus and show it           *
//*****************************************************************************

   setIcon(WINDOWID);
   setClient(&remoteCanvas);
   ISize size = remoteCanvas.minimumSize();
   moveSizeToClient(IRectangle(MARGIN*3,
                               MARGIN*3,
                               MARGIN*3+size.width(),
                               MARGIN*3+size.height()));
   setFocus();
   show();
}

//*****************************************************************************
//  newDigit routine manages digital input for CD player.                     *
//*****************************************************************************

MainWindow& MainWindow::newDigit(int digit)
{
  IResourceLibrary reslib;
  if (newTrackDigit2 ==-1)
  {
     newTrackDigit2 = digit;
     readout.setText(IString(reslib.loadString(STR_TRACK)) + IString(newTrackDigit1) +
                     IString(newTrackDigit2) + IString(reslib.loadString(STR_PAD)) +
                     IString(reslib.loadString(STR_TIME_00)));
     if (newTrackDigit1*10 + newTrackDigit2 > cdPlayer->numberOfTracks())
     {
        IMessageBox msgBox(this);
        msgBox.show(IString(newTrackDigit1*10+newTrackDigit2) +
                    IString(reslib.loadString(STR_INVALID_TRACK)) + IString(cdPlayer->numberOfTracks()) + IString(reslib.loadString(STR_TRACKS)),
                    IMessageBox::okButton  |
                    IMessageBox::errorIcon |
                    IMessageBox::moveable );
     } else
     {
        cdPlayer->goToEntry(newTrackDigit1*10 + newTrackDigit2);
     } /* endif */
  }
  else
  {
    newTrackDigit1 = digit;
    newTrackDigit2 = -1;
    readout.setText(IString(reslib.loadString(STR_TRACK)) + IString(newTrackDigit1) +
                    IString(reslib.loadString(STR_PAD)) + IString(reslib.loadString(STR_TIME_00)));
  }
  return *this;
}

//*******************************************************************************
// MainHandler::MainHandler                                                      *
//                                                                              *
// Constructs the handler.                                                      *
//*******************************************************************************
MainHandler::MainHandler()
           : MainHandler::Inherited()
{}

//*******************************************************************************
// MainHandler::command                                                          *
//                                                                              *
// Does the processing for the button presses.                                  *
//*******************************************************************************

bool MainHandler::command( ICommandEvent& event )
{
  IResourceLibrary reslib;
  bool rv = false;
  MainWindow* panel = (MainWindow*) (event.controlWindow());
  switch ( event.commandId() )
  {

//*****************************************************************************
//  The power button is used to start a new device.  It loads the file to be  *
//  played and sets up the device and buttons                                 *
//*****************************************************************************
  case POWERID:
       {
          IFileDialog::Settings fdSettings;
          fdSettings.setTitle(STR_LOAD_DEVICE);
          switch (panel->playerDevice)
          {
//*****************************************************************************
//  Load a video file, using the file dialog.  Enable the control buttons     *
//  and keypad, and set the status line text.  Start position tracking for    *
//  timer.                                                                    *
//*****************************************************************************

             case VIDEOID:
                  {
                  fdSettings.setFileName(reslib.loadString(STR_AVI));
                  IFileDialog fd(panel->desktopWindow(),panel,fdSettings);
                  if (fd.pressedOK())
                  {
                     panel->digPlayer->loadOnThread(fd.fileName());
                     panel->digPlayer->startPositionTracking(IMMTime(3000));
                     panel->stepOrTrackBBtn.enable();
                     panel->stepOrTrackFBtn.enable();
                     panel->readout.setText(IString(reslib.loadString(STR_TIME_00)));
                     if (!panel->playbtn.isEnabled())
                     {
                        panel->playbtn.enable();
                        panel->stopbtn.enable();
                        panel->rewbtn.enable();
                        panel->ffbtn.enable();
                        panel->pausebtn.enable();
                        panel->pad.enable();
                     }
                  }
                  }
                  break;

//*****************************************************************************
//  Load a midi file, using the file dialog.  Enable the control buttons      *
//  and set the status line text.  Start position tracking for timer.         *
//*****************************************************************************

             case MIDIID:
                  {
                  fdSettings.setFileName(reslib.loadString(STR_MID_EXT));
                  IFileDialog fd(panel->desktopWindow(),panel,fdSettings);
                  if (fd.pressedOK())
                  {
                     panel->midPlayer->loadOnThread(fd.fileName());
                     panel->midPlayer->startPositionTracking(IMMTime(3000));
                     panel->readout.setText(IString(reslib.loadString(STR_TIME_00)));
                     if (!panel->playbtn.isEnabled())
                     {
                        panel->playbtn.enable();
                        panel->stopbtn.enable();
                        panel->rewbtn.enable();
                        panel->ffbtn.enable();
                        panel->pausebtn.enable();
                     }
                  }
                  }
                  break;

//*****************************************************************************
//  Load a wave file using the file dialog. Enable the control buttons and    *
//  set the status line text.  Start position tracking for timer.             *
//*****************************************************************************

             case WAVEID:
                  {
                  fdSettings.setFileName(reslib.loadString(STR_WAV_EXT));
                  IFileDialog fd(panel->desktopWindow(),panel,fdSettings);
                  if (fd.pressedOK())
                  {
                     panel->wavPlayer->loadOnThread(fd.fileName());
                     panel->wavPlayer->startPositionTracking(IMMTime(3000));
                     panel->readout.setText(IString(reslib.loadString(STR_TIME_00)));
                     if (!panel->playbtn.isEnabled())
                     {
                        panel->playbtn.enable();
                        panel->stopbtn.enable();
                        panel->rewbtn.enable();
                        panel->ffbtn.enable();
                        panel->pausebtn.enable();
                     }
                  }
                  }
                  break;
          }
          panel->powerbtn.setText(reslib.loadString(STR_POWER));
          rv=true;
       }
       break;

//*****************************************************************************
//  If CD button is pressed, set up the bitmaps on the buttons and the        *
//  status line.                                                              *
//*****************************************************************************

  case CDID:
       panel->player->stop();
       panel->pausebtn.unlatch();
       panel->playbtn.unlatch();
       panel->stopbtn.disable();
       panel->pausebtn.disable();
       panel->player=panel->cdPlayer;
       if (panel->playerDevice!=CDID)
       {
         panel->stepOrTrackBBtn.setBitmaps(IAnimatedButton::trackReverse);
         panel->stepOrTrackFBtn.setBitmaps(IAnimatedButton::trackAdvance);
         panel->stepOrTrackBBtn.enable();
         panel->stepOrTrackFBtn.enable();
         panel->readout.setText(IString(reslib.loadString(STR_TRACK)) + IString(panel->newTrackDigit1) +
                   IString(panel->newTrackDigit2) + IString(reslib.loadString(STR_PAD)) +
                   IString(reslib.loadString(STR_TIME_00)));
         panel->flyHelpHandler.setFlyTextStringTableOffset(0);
       }
       panel->playerDevice=CDID;
       if (!panel->playbtn.isEnabled())
       {
          panel->playbtn.enable();
          panel->stopbtn.enable();
          panel->rewbtn.enable();
          panel->ffbtn.enable();
          panel->pausebtn.enable();
       }
       panel->pad.enable();
       rv=true;
       break;

//*****************************************************************************
// If video is pressed, disable the buttons until a file is loaded            *
//*****************************************************************************

  case VIDEOID:
       panel->player->stop();
       panel->player=panel->digPlayer;
       if (panel->playerDevice!=VIDEOID)
       {
          panel->stepOrTrackBBtn.setBitmaps(IAnimatedButton::stepBackward);
          panel->stepOrTrackFBtn.setBitmaps(IAnimatedButton::stepForward );
          panel->flyHelpHandler.setFlyTextStringTableOffset(VIDEO);
       }
       if (panel->playbtn.isLatched())
          panel->playbtn.unlatch();
       panel->playerDevice=VIDEOID;
       panel->pausebtn.unlatch();
       panel->playbtn.disable();
       panel->stopbtn.disable();
       panel->rewbtn.disable();
       panel->ffbtn.disable();
       panel->pausebtn.disable();
       panel->stepOrTrackBBtn.disable();
       panel->stepOrTrackFBtn.disable();
       panel->pad.disable();
       panel->powerbtn.setText(reslib.loadString(STR_LOAD_FILE) );
       rv=true;
       break;

//*****************************************************************************
//  If midi device is selected, disable buttons until a file is loaded        *
//*****************************************************************************

  case MIDIID:
       panel->player->stop();
       panel->player=panel->midPlayer;
       panel->playerDevice=MIDIID;
       if (panel->playbtn.isLatched())
          panel->playbtn.unlatch();
       panel->stepOrTrackBBtn.disable();
       panel->stepOrTrackFBtn.disable();
       panel->playbtn.disable();
       panel->stopbtn.disable();
       panel->rewbtn.disable();
       panel->ffbtn.disable();
       panel->pausebtn.unlatch();
       panel->pausebtn.disable();
       panel->pad.disable();
       panel->powerbtn.setText(reslib.loadString(STR_LOAD_FILE) );
       panel->flyHelpHandler.setFlyTextStringTableOffset(MIDI);
       rv=true;
       break;
//*****************************************************************************
//  If wave device is selected, disable buttons until a file is loaded        *
//*****************************************************************************

  case WAVEID:
       panel->player->stop();
       panel->player=panel->wavPlayer;
       panel->playerDevice=WAVEID;
       if (panel->playbtn.isLatched())
          panel->playbtn.unlatch();
       panel->stepOrTrackBBtn.disable();
       panel->stepOrTrackFBtn.disable();
       panel->playbtn.disable();
       panel->stopbtn.disable();
       panel->rewbtn.disable();
       panel->ffbtn.disable();
       panel->pausebtn.unlatch();
       panel->pausebtn.disable();
       panel->pad.disable();
       panel->powerbtn.setText(reslib.loadString(STR_LOAD_FILE));
       panel->flyHelpHandler.setFlyTextStringTableOffset(WAVE);
       rv=true;
       break;

//*****************************************************************************
// Step backward button.  For CD, back up to previous track                   *
//*****************************************************************************

  case STEPTRACKBID:
       if (panel->playerDevice==CDID)
          panel->cdPlayer->trackBackward();
       else
       {
          IMMTime::Format format = panel->player->timeFormat();
          panel->player->setTimeFormat(IMMTime::mmTime);
          if (panel->player->position())
          {
             panel->player->setTimeFormat(format);
             panel->player->stepFrame(1,false);
          }
          else
             panel->player->setTimeFormat(format);
       }
       break;

//*****************************************************************************
//  Step forward button.  For CD, advance to next track                       *
//*****************************************************************************

  case STEPTRACKFID:
       if (panel->playerDevice==CDID)
          panel->cdPlayer->trackForward();
       else
       {
          IMMTime::Format format = panel->player->timeFormat();
          panel->player->setTimeFormat(IMMTime::mmTime);
          if (panel->player->position() < panel->player->length())
          {
             panel->player->setTimeFormat(format);
             panel->player->stepFrame();
          }
          else
             panel->player->setTimeFormat(format);
       }
       break;

//*****************************************************************************
// If play is pressed, first check to see if already playing.  If not, enable *
// pause and stop buttons and play.  If it is, relatch the play button        *
//*****************************************************************************

  case PLAYID:
       if (panel->player->mode() != IMMDevice::playing)
       {
          panel->stopbtn.enable();
          panel->pausebtn.enable();
          panel->pausebtn.unlatch();
          panel->player->play();
          panel->playHours=0;
          panel->playMins=0;
          panel->playSecs=0;
        }
       else panel->playbtn.latch();
       rv=true;
       break;

//*****************************************************************************
//  If Stop is pressed, stop the player and reset to the beginning.  Disable  *
//  stop and pause buttons                                                    *
//*****************************************************************************

  case STOPID:
       panel->player->stop();
       panel->player->seekToStart();
       panel->pausebtn.unlatch();
       panel->playbtn.unlatch();
       panel->stopbtn.disable();
       panel->pausebtn.disable();
       rv=true;
       break;

//*****************************************************************************
//  For rewind, reset to beginning of file, unlatch the play button and       *
//  diable stop and pause                                                     *
//*****************************************************************************

  case REWID:
       if (panel->playerDevice == CDID) {
          panel->cdPlayer->startScanningBackward() ;
          panel->stopbtn.enable();
       }
       else {
          panel->player->seekToStart();
          panel->playbtn.unlatch();
          panel->pausebtn.unlatch();
          panel->stopbtn.disable();
          panel->pausebtn.disable();
       }
       rv=true;
       break;

//*****************************************************************************
//  For fast forward, advance to end of file                                  *
//*****************************************************************************

  case FFID:
       if (panel->playerDevice == CDID) {
          panel->cdPlayer->startScanningForward() ;
          panel->stopbtn.enable();
       }
       else {
          panel->player->seekToEnd();
          panel->pausebtn.unlatch();
          panel->playbtn.unlatch();
          panel->stopbtn.disable();
          panel->pausebtn.disable();
       }
       rv=true;
       break;

//*****************************************************************************
//  If pause, check pause state.  If paused, resume play, otherwise pause     *
//*****************************************************************************

    case PAUSEID:
       if ( panel->player->mode() != IMMDevice::playing )
       {
          panel->player->play();
          panel->playbtn.latch();
       }
       else
         panel->player->pause();

       rv=true;
       break;

//*****************************************************************************
//  Turn down volume 5%                                                       *
//*****************************************************************************

  case VOLDNID:
       panel->player->setVolume(panel->player->volume()-5);
       rv=true;
       break;

//*****************************************************************************
//  Turn up volume 5%                                                         *
//*****************************************************************************

  case VOLUPID:
       panel->player->setVolume(panel->player->volume()+5);
       rv=true;
       break;

//*****************************************************************************
// For one on keypad, enter digit 1 for CD, or play slow motion for video     *
//*****************************************************************************

  case ONEID:
       switch (panel->playerDevice){
       case CDID:
          panel->newDigit(1);
          rv=true;
          break;
       case VIDEOID:
          panel->digPlayer->playSlow();
          rv=true;
          break;
       }
       break;

//*****************************************************************************
//  For two on keypad, enter digit 2 for CD, or play fast speed for video     *
//*****************************************************************************

  case TWOID:
       switch (panel->playerDevice) {
       case CDID:
          panel->newDigit(2);
          rv=true;
          break;
       case VIDEOID:
          panel->digPlayer->playFast();
          rv=true;
          break;
       }
       break;

//*****************************************************************************
//  For three on keypad, enter digit 3 for CD, play in scan mode for video    *
//*****************************************************************************

  case THREEID:
       switch (panel->playerDevice){
       case CDID:
          panel->newDigit(3);
          rv=true;
          break;
       case VIDEOID:
          panel->digPlayer->playScan();
          rv=true;
          break;
       }
       break;

//*****************************************************************************
//  For digits 4-9, enter digit for CD track                                  *
//*****************************************************************************

  case FOURID:
       if (panel->playerDevice==CDID)
          panel->newDigit(4);
       rv=true;
       break;
  case FIVEID:
       if (panel->playerDevice==CDID)
          panel->newDigit(5);
       rv=true;
       break;
  case SIXID:
       if (panel->playerDevice==CDID)
          panel->newDigit(6);
       rv=true;
       break;
  case SEVENID:
       if (panel->playerDevice==CDID)
          panel->newDigit(7);
       rv=true;
       break;
  case EIGHTID:
       if (panel->playerDevice==CDID)
          panel->newDigit(8);
       rv=true;
       break;
  case NINEID:
       if (panel->playerDevice==CDID)
          panel->newDigit(9);
       rv=true;
       break;

//*****************************************************************************
//  For zero on keypad, enter 0 for CD, or resume normal play for video       *
//*****************************************************************************

  case ZEROID:
       switch (panel->playerDevice) {
       case CDID:
          if (panel->playerDevice==CDID && !(panel->newTrackDigit1==0 && panel->newTrackDigit2==-1))
          panel->newDigit(0);
          rv=true;
          break;
       case VIDEOID:
          panel->digPlayer->play();
          rv=true;
          break;
       }
       break;
  }
  return rv;
}

//*******************************************************************************
// MainObserver::MainObserver                                                     *
//                                                                              *
// Constructs the observer.                                                     *
//*******************************************************************************
MainObserver::MainObserver(MainWindow& mainPanel)
            : MainObserver::Inherited(),
              panel(mainPanel)
{}

//*****************************************************************************
//  Set up observer to track time and update status line for CD player        *
//*****************************************************************************

MainObserver& MainObserver::dispatchNotificationEvent(const INotificationEvent& event)
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
   }
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
      if ((panel.cdPlayer->mode()==IMMDevice::playing) &&
          !(panel.playbtn.isLatched()))
         panel.playbtn.latch();
   } /* endif */
   else if (event.notificationId() == IMMDevice::positionChangeId)
   {
      IMMPositionChangeEvent* positionEvent = (IMMPositionChangeEvent*)(event.eventData().asUnsignedLong());
      IMMTime time(positionEvent->position());

      if ((panel.player)->deviceId() == (positionEvent->device())->deviceId() )
      {
         panel.readout.setText(
                         IString(time.hours()).rightJustify(2,'0') +
                         IString(reslib.loadString(STR_COLON)) +
                         IString(time.minutes()).rightJustify(2,'0') +
                         IString(reslib.loadString(STR_COLON)) +
                         IString(time.seconds()).rightJustify(2,'0'));
      }

   }
   else if (event.notificationId() == IMMDevice::commandNotifyId)
   {
      IMMNotifyEvent* notifyEvent = (IMMNotifyEvent*)(event.eventData().asUnsignedLong());
      if (notifyEvent->command() == IMMNotifyEvent::play)
      {
         panel.playbtn.unlatch();
         if (panel.playerDevice == CDID &&
             panel.cdPlayer->mode() == IMMDevice::playing)
         {
            panel.playbtn.latch();
         }
      }
   }

   return *this;
}
