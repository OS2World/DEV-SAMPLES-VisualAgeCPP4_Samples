/******************************************************************************
* .FILE:         mmstereo.cpp                                                 *
*                                                                             *
* .DESCRIPTION:  Multimedia Stereo Sample:             Class Implementation   *
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
#include <iapp.hpp>
#include <icoordsy.hpp>
#include "mmstereo.hpp"

//*************************************************************************
// main  - Application entry point                                        *
//*************************************************************************
int main()                             //Main procedure with no parameters
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::kOriginLowerLeft );

  MainWindow  mainWindow(WINDOWID);     //Create our main window on the desktop

  IApplication::current().run();        //Get the current application and
                                        // run it
  return 0;
} /* end main */


/*------------------------------------------------------------------------------
| MainWindow::MainWindow                                                       |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
MainWindow::MainWindow( unsigned long windowId)
            //Call IFrameWindow constructor
          : IFrameWindow(windowId,
            IFrameWindow::defaultStyle()
            | IFrameWindow::minimizedIcon),
            title(this),
            clientCanvas(CLIENTCANVASID,this,this),
	  selectorCanvas( IDC_SELECTOR, &clientCanvas, &clientCanvas ),
            cdPlayer(0),
            wavPlayer(0),
            vidPlayer(0),
            selectCD( IDB_CD, &selectorCanvas, &selectorCanvas ),  
            selectWave( IDB_WAVE, &selectorCanvas, &selectorCanvas ),  
            selectVideo( IDB_VIDEO, &selectorCanvas, &selectorCanvas )
{
   title.setTitleText(WINDOWID);
   selectCD.setText(TITLE_CD_PLAYER);
   selectWave.setText(TITLE_WAV_PLAYER);
   selectVideo.setText(TITLE_VID_PLAYER);
   
   selectorCanvas.setDeckOrientation(ISetCanvas::vertical)
	.setBackgroundColor( IColor( IColor::kPaleGray ) );

   handleEventsFor( &selectorCanvas );

   //Create the audio cd device, but if we get an exception then
   //we will still display the cd player, but it will be disabled
   try
   {
      cdPlayer = new IMMAudioCD();
   }
   catch (...)
   {
        cdPlayer  = 0;
        ampMixer1 = 0;
   }
   if (cdPlayer)
   {
      try
      {
         //Enable Digital transfer from the cd
         cdPlayer->enableConnector(IMMDevice::cdStream);
         ampMixer1 = new IMMAmpMixer(cdPlayer->connectedDeviceId(IMMDevice::cdStream));
         ampMixer1->enableMonitoring();
         ampMixer1->setCloseOnDestroy(false);
      }
      catch (...)
      {
         ampMixer1 = 0;
      }
   } /* endif */
   cd       = new CD   (cdPlayer , CD_ID   ,  &clientCanvas, &clientCanvas);
   if (!cdPlayer)
   {
      ((IMultiCellCanvas*)cd)->disable();
      selectCD.disable();
   }
   else
   {
         cdPlayer->enableNotification();
   }

   // Color is inherited from the parent.  The parent is clientCanvas and
   // its color is black.  We want to player panel to be gray.
   cd->setBackgroundColor( IColor( IColor::kPaleGray ) );

   //Create the wave audio device, but if we get an exception then
   //we will still display the wave player, but it will be disabled
   try
   {
      wavPlayer = new IMMWaveAudio();
      ampMixer2 = new IMMAmpMixer(wavPlayer->connectedDeviceId(IMMDevice::waveStream));
//      ampMixer2->enableMonitoring();
      ampMixer2->setCloseOnDestroy(false);
   }
   catch (...)
   {
      wavPlayer = 0;
      ampMixer2 = 0;
   }
   wave     = new WAVE (wavPlayer, WAVE_ID ,  &clientCanvas, &clientCanvas);
   if (wavPlayer)
      wavPlayer->enableNotification();
   else
   {
      ((IMultiCellCanvas*)wave)->disable();
      selectWave.disable();
   }


   // Color is inherited from the parent.  The parent is clientCanvas and
   // its color is black.  We want to player panel to be gray.
   wave->setBackgroundColor( IColor( IColor::kPaleGray ) );

   //Create the video device, but if we get an exception then
   //we will still display the video player, but it will be disabled
   try
   {
      vidPlayer = new IMMDigitalVideo();
      ampMixer3 = new IMMAmpMixer(vidPlayer->connectedDeviceId(IMMDevice::waveStream));
//      ampMixer3->enableMonitoring();
      ampMixer3->setCloseOnDestroy(false);
   }
   catch (...)
   {
      vidPlayer = 0;
      ampMixer3 = 0;
   }
   video    = new VIDEO(vidPlayer, VIDEO_ID,  &clientCanvas, &clientCanvas);
   if (vidPlayer)
      vidPlayer->enableNotification();
   else
   {
      ((IMultiCellCanvas*)video)->disable();
      selectVideo.disable();
   }

   // Color is inherited from the parent.  The parent is clientCanvas and
   // its color is black.  We want to player panel to be gray.
   video->setBackgroundColor( IColor( IColor::kPaleGray ) );

   //Create the amplifier mixer panel, to control the sound for all of the
   //device's amplifier mixers
   amp      = new Amp  (ampMixer1,ampMixer2,ampMixer3, AMP_ID, &clientCanvas, this);

   // Color is inherited from the parent.  The parent is clientCanvas and
   // its color is black.  We want to player panel to be gray.
   amp->setBackgroundColor( IColor( IColor::kPaleGray ) );

   clientCanvas.setBackgroundColor(IColor(IColor::kBlack));
   setBackgroundColor(IColor(IColor::kPaleGray));

   setClient(&clientCanvas);
   clientCanvas.setDeckOrientation(ISetCanvas::vertical);
   ISize size = clientCanvas.minimumSize();
   moveSizeToClient(IRectangle(0, 0, size.width(), size.height()));

   if( cdPlayer )
   {
      selectCD.click();
   }
   else if( wavPlayer )
   {
      selectWave.click();
   }
   else if( vidPlayer )
   {
      selectVideo.click();
   }

   show();
   setFocus();
}

MainWindow::~MainWindow()
{
   if (amp)
      delete amp;
   if (cd)
      delete cd;
   if (wave)
      delete wave;
   if (video)
      delete video;
   if (cdPlayer)
      delete cdPlayer;
   if (wavPlayer)
      delete wavPlayer;
   if (vidPlayer)
      delete vidPlayer;
   if (ampMixer1)
      delete ampMixer1;
   if (ampMixer2)
      delete ampMixer2;
   if (ampMixer3)
      delete ampMixer3;
}

MainWindow& MainWindow::enableComponent( IMultiCellCanvas& component, bool enable )
{
   IWindow::ChildCursor childCursor( component );
   childCursor.setToFirst();

   while( childCursor.isValid() )
   {
      IWindow* child = component.childWindowAt(childCursor);
      child->enable( enable );
      childCursor.setToNext();
   }	
   component.enable( enable );
   
   return *this;
}

bool MainWindow::selected(IControlEvent& event)
{
   bool bResult = true;
   IMMAmpMixer* ampMixer = 0;

   switch( event.controlId() )
   {
      case IDB_CD:
      {
         enableComponent( *cd, true );
         enableComponent( *video, false );
         enableComponent( *wave, false );
         ampMixer = ampMixer1;
      }
      break;
      case IDB_WAVE:
      {
         enableComponent( *cd, false );
         enableComponent( *video, false );
         enableComponent( *wave, true );
         ampMixer = ampMixer2;
      }
      break;
      case IDB_VIDEO:
      {
         enableComponent( *cd, false );
         enableComponent( *video, true );
         enableComponent( *wave, false );
         ampMixer = ampMixer3;
      }
      break;
      default:
         bResult = false;
      break;
   }
   if( bResult )
   {
      if( ampMixer )
         enableComponent( *amp, true );
      else
         enableComponent( *amp, false );
   }

   return bResult;
}
