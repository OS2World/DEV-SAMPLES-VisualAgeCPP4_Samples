/******************************************************************************
* .FILE:         anotebw6.hpp                                                 *
*                                                                             *
* .DESCRIPTION:  Hello World Sample Program Version 6: NoteBookWindow Header  *
*                                                                             *
* .CLASSES:      ANotebookWindow                                              *
*                ANotebookCommandHandler                                      *
*                AHelloWindow                                                 *
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
#ifndef _ANOTEBW6_
#define _ANOTEBW6_

#include <iframe.hpp>
#include <icmdhdr.hpp>
#include <inotebk.hpp>
#include <imcelcv.hpp>
#include <isetcv.hpp>
#include <istattxt.hpp>
#include <icheckbx.hpp>
#include <islider.hpp>
#include <iradiobt.hpp>
#include <ipushbut.hpp>
#include "ahellow6.hpp"

//Forward declarations for other classes:
class ANotebookWindow;
class AHelloWindow;

/**************************************************************************
* Class ANotebookCommandHandler - Command handler that process commands   *
*   for notebook window.                                                  *
**************************************************************************/
class ANotebookCommandHandler : public ICommandHandler
{
  public:
/*---------------------------- Constructor -------------------------------|
| Constructs an object with:                                              |
| 1) A pointer to the notebook window                                     |
-------------------------------------------------------------------------*/
    ANotebookCommandHandler(ANotebookWindow *nbFrame);

/*---------------------------- Destructor --------------------------------|
| Destructs an object with:                                               |
| 1) A pointer to the notebook window                                     |
-------------------------------------------------------------------------*/
    virtual
     ~ANotebookCommandHandler() { }

  protected:
/*------------------------ Override Command Function ---------------------|
| The command function is called to process application command events.   |
|------------------------------------------------------------------------*/
    virtual bool
      command(ICommandEvent& cmdEvent);

  private:
    ANotebookWindow *frame;
};

/**************************************************************************
* Class ANotebookWindow - Frame Window class containing an INotebook      *
*   window for changing settings in the C++ Hello World sample.           *
**************************************************************************/
class ANotebookWindow : public IFrameWindow
{
  public:
    ANotebookWindow(unsigned long windowId, AHelloWindow *ownerWnd);
    virtual
     ~ANotebookWindow();

/*------------------------ Public Settings Functions ---------------------|
| These functions are used to change settings in the AHelloWindow and     |
|   to set the values in the notebook when it is intialized and when      |
|   the reset push button is pressed.                                     |
|   applyEarthSettings - use earthPage settings to change earthWindow     |
|              attributes.                                                |
|   resetEarthSettings - set earthPage values by querying earthWindow     |
|              attributes.                                                |
|   applyDateTimeSettings - use dateTimePage settings to change           |
|              AHelloWindow attributes.                                   |
³   resetDateTimeSettings - set dateTimePage values by querying           |
|              AHelloWindow attributes.                                   |
|------------------------------------------------------------------------*/
    ANotebookWindow
     &applyEarthSettings(),
     &resetEarthSettings(),
     &applyDateTimeSettings(),
     &resetDateTimeSettings();

  private:
    INotebook
      helloSettingsNotebook;
    IMultiCellCanvas
      earthPage,
      earthColorSettings,
      dateTimePage,
      dateSettings,
      timeSettings;
    ISetCanvas
      starsSettings,
      earthPageButtons,
      dateTimePageButtons;
    IStaticText
      earthPageHeading,
      starsHeading,
      layersHeading,
      earthColorHeading,
      dateTimePageHeading,
      dateHeading,
      dateLongExample,
      dateShortExample,
      timeHeading,
      timeLongExample,
      timeShortExample;
    ISlider
      layersSlider;
    ICheckBox
      twinkleBox,
      brightBox;
    IPushButton
      earthApplyButton,
      earthResetButton,
      earthCloseButton,
      dateTimeApplyButton,
      dateTimeResetButton,
      dateTimeCloseButton;
    IRadioButton
      cyanButton,
      greenButton,
      whiteButton,
      yellowButton,
      dateLongButton,
      dateShortButton,
      timeLongButton,
      timeShortButton;
    ANotebookCommandHandler
      notebookCommandHandler;
};

#endif
