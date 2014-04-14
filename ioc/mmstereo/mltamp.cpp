/******************************************************************************
* .FILE:         mltamp.cpp                                                   *
*                                                                             *
* .DESCRIPTION:  Multimedia Stereo Sample:             Class Implementation   *
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
#include <ireslib.hpp>
#include "mmstereo.hpp"
#include "mltamp.hpp"

/*------------------------------------------------------------------------------
| Amp::Amp                                                                     |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
Amp::Amp( IMMAmpMixer*  aAmp1,
          IMMAmpMixer*  aAmp2,
          IMMAmpMixer*  aAmp3,
          unsigned long windowid,
          IWindow*      parent,
          IWindow*      owner)
   : IMultiCellCanvas(windowid,parent,owner),
     name            (AMPNAMEID, this,owner),
     slVolume        (SL_VOLUME_ID,this,this,IRectangle(),
                      ICircularSlider::defaultStyle()
                      | ICircularSlider::proportionalTicks ),
     slBalance       (SL_BALANCE_ID,this,this,IRectangle(),
                      ICircularSlider::defaultStyle()
                      | ICircularSlider::proportionalTicks ),
     slBass          (SL_BASS_ID,this,this,IRectangle(),
                      ICircularSlider::defaultStyle()
                      | ICircularSlider::proportionalTicks ),
     slTreble        (SL_TREBLE_ID,this,this,IRectangle(),
                      ICircularSlider::defaultStyle()
                      | ICircularSlider::proportionalTicks ),
     slPitch         (SL_PITCH_ID,this,this,IRectangle(),
                      ICircularSlider::defaultStyle()
                      | ICircularSlider::proportionalTicks ),
     slGain          (SL_GAIN_ID,this,this,IRectangle(),
                      ICircularSlider::defaultStyle()
                      | ICircularSlider::proportionalTicks ),
     pAmpMixer1(aAmp1),
     pAmpMixer2(aAmp2),
     pAmpMixer3(aAmp3),
     ampHandler()
{
   IResourceLibrary reslib;

   //Set up the title
   name.setText(reslib.loadString(TITLE_MIXER));
   name.setForegroundColor     ( IColor(IColor::kRed)   );

   slVolume.setArmRange          (IRange(0,100));
   slVolume.setRotationIncrement (10);
   slVolume.setTickSpacing       (1);
   slVolume.setText              (reslib.loadString(STR_VOLUME));
   addToCell                     (&slVolume,     1, 1, 1, 1);

   slBalance.setArmRange         (IRange(0,100));
   slBalance.setRotationIncrement(10);
   slBalance.setTickSpacing      (1);
   slBalance.setText             (reslib.loadString(STR_BALANCE));
   addToCell                     (&slBalance,    2, 1, 1, 1);

   slBass.setArmRange            (IRange(0,100));
   slBass.setRotationIncrement   (10);
   slBass.setTickSpacing         (1);
   slBass.setText                (reslib.loadString(STR_BASS));
   addToCell                     (&slBass,       3, 1, 1, 1);

   slTreble.setArmRange          (IRange(0,100));
   slTreble.setRotationIncrement (10);
   slTreble.setTickSpacing       (1);
   slTreble.setText              (reslib.loadString(STR_TREBLE));
   addToCell                     (&slTreble,     4, 1, 1, 1);

   slPitch.setArmRange           (IRange(0,100));
   slPitch.setRotationIncrement  (10);
   slPitch.setTickSpacing        (1);
   slPitch.setText               (reslib.loadString(STR_PITCH));
   addToCell                     (&slPitch,      5, 1, 1, 1);

   slGain.setArmRange            (IRange(0,100));
   slGain.setRotationIncrement   (10);
   slGain.setTickSpacing         (1);
   slGain.setText                (reslib.loadString(STR_GAIN));
   addToCell                     (&slGain,       6, 1, 1, 1);

   addToCell                     (&name,         3, 2, 3, 1);

   ampHandler.handleEventsFor(this);
   IMMAmpMixer* tempAmp = 0;
   if (pAmpMixer3)
      tempAmp=pAmpMixer3;
   else if (pAmpMixer2)
      tempAmp=pAmpMixer2;
   else if (pAmpMixer1)
      tempAmp=pAmpMixer1;
   if (tempAmp)
   {
      slVolume.setValue (tempAmp->volume ());
      slBalance.setValue(tempAmp->balance());
      slBass.setValue   (tempAmp->bass   ());
      slTreble.setValue (tempAmp->treble ());
      slPitch.setValue  (tempAmp->pitch  ());
      slGain.setValue   (tempAmp->gain   ());
   } /* endif */
}

/*------------------------------------------------------------------------------
| AmpHandler::AmpHandler                                                       |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
AmpHandler::AmpHandler()
          : AmpHandler::Inherited()
{}


/*------------------------------------------------------------------------------
| AmpHandler::tracking                                                         |
|                                                                              |
|                                                                              |
------------------------------------------------------------------------------*/
bool AmpHandler::moving   (IControlEvent& evt)
{
   bool result=false;
   Amp* pAmp = (Amp*)(evt.window());
   ICircularSlider* pSld = (ICircularSlider*)(evt.controlWindow());
   short val = pSld->value();

   switch (evt.controlId())
   {
    case SL_VOLUME_ID:
         if (pAmp->pAmpMixer1)
           pAmp->pAmpMixer1->setVolume(val);
         if (pAmp->pAmpMixer2)
           pAmp->pAmpMixer2->setVolume(val);
         if (pAmp->pAmpMixer3)
            pAmp->pAmpMixer3->setVolume(val);
         result = true;
         break;
    case SL_BALANCE_ID:
         if (pAmp->pAmpMixer1)
            pAmp->pAmpMixer1->setBalance(val);
         if (pAmp->pAmpMixer2)
            pAmp->pAmpMixer2->setBalance(val);
         if (pAmp->pAmpMixer3)
            pAmp->pAmpMixer3->setBalance(val);
         //0 is full to the left and 100 is full to the right
         result = true;
         break;
    case SL_BASS_ID:
         if (pAmp->pAmpMixer1)
            pAmp->pAmpMixer1->setBass(val);
         if (pAmp->pAmpMixer2)
            pAmp->pAmpMixer2->setBass(val);
         if (pAmp->pAmpMixer3)
            pAmp->pAmpMixer3->setBass(val);
         result = true;
         break;
    case SL_TREBLE_ID:
         if (pAmp->pAmpMixer1)
            pAmp->pAmpMixer1->setTreble(val);
         if (pAmp->pAmpMixer2)
            pAmp->pAmpMixer2->setTreble(val);
         if (pAmp->pAmpMixer3)
            pAmp->pAmpMixer3->setTreble(val);
         result = true;
         break;
    case SL_PITCH_ID:
         if (pAmp->pAmpMixer1)
            pAmp->pAmpMixer1->setPitch(val);
         if (pAmp->pAmpMixer2)
            pAmp->pAmpMixer2->setPitch(val);
         if (pAmp->pAmpMixer3)
            pAmp->pAmpMixer3->setPitch(val);
         result = true;
         break;
    case SL_GAIN_ID:
         if (pAmp->pAmpMixer1)
            pAmp->pAmpMixer1->setGain(val);
         if (pAmp->pAmpMixer2)
            pAmp->pAmpMixer2->setGain(val);
         if (pAmp->pAmpMixer3)
            pAmp->pAmpMixer3->setGain(val);
         result = true;
         break;
   } /* endswitch */

   return result;
}

