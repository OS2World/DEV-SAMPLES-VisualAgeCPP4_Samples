/******************************************************************************
* .FILE         anotebw6.cpp                                                  *
*                                                                             *
* .DESCRIPTION: Hello World Sample Program Version 6: Notebook Implementation *
*                                                                             *
* .CLASSES:     ANotebookWindow                                               *
*               ANotebookHandler                                              *
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
#include "anotebw6.hpp"
#include "ahellow6.h"

/**************************************************************************
* Class ANotebookWindow :: ANotebookWindow - Construcs a child window     *
*   that contains the setting notebook.                                   *
**************************************************************************/
ANotebookWindow :: ANotebookWindow(unsigned long windowId,
                                   AHelloWindow * ownerWnd)
  : IFrameWindow(windowId, IWindow::desktopWindow(), ownerWnd, IRectangle(),
                 classDefaultStyle |
                 dialogBackground  |
                 dialogBorder)
  , helloSettingsNotebook(WND_NOTEBOOK, this, this)
  , earthPage(WND_EARTHPAGE,&helloSettingsNotebook,&helloSettingsNotebook)
  , earthPageHeading(WND_EARTHPAGEHEADING, &earthPage, &earthPage)
  , starsHeading(WND_STARSHEADING, &earthPage, &earthPage)
  , starsSettings(WND_STARSSETTINGS, &earthPage, &earthPage)
  , twinkleBox(WND_TWINKLEBOX, &starsSettings, &starsSettings)
  , brightBox(WND_BRIGHTBOX, &starsSettings, &starsSettings)
  , layersHeading(WND_LAYERSHEADING, &earthPage, &earthPage)
  , layersSlider(WND_LAYERSSPIN, &earthPage, &earthPage,
                 IRectangle(), 4ul, 0,
                 IProgressIndicator::alignBottom   |
                 IProgressIndicator::snapToTickMark|
                 IProgressIndicator::primaryScale1 |
                 IProgressIndicator::horizontal    |
                 IProgressIndicator::homeLeft      |
                 ISlider::buttonsRight |
                 IWindow::visible)
  , earthColorHeading(WND_EARTHCOLORHEADING, &earthPage, &earthPage)
  , earthColorSettings(WND_EARTHCOLORSETTINGS, &earthPage, &earthPage)
  , cyanButton(WND_CYANBUTTON, &earthColorSettings,&earthColorSettings)
  , greenButton(WND_GREENBUTTON, &earthColorSettings,&earthColorSettings)
  , whiteButton(WND_WHITEBUTTON, &earthColorSettings,&earthColorSettings)
  , yellowButton(WND_YELLOWBUTTON, &earthColorSettings,&earthColorSettings)
  , earthPageButtons(WND_EARTHPAGEBUTTONS, &earthPage, &earthPage)
  , earthApplyButton(DID_EARTHAPPLY, &earthPageButtons,&earthPageButtons)
  , earthResetButton(DID_EARTHRESET, &earthPageButtons,&earthPageButtons)
  , earthCloseButton(DID_NOTEBOOKCLOSE, &earthPageButtons,&earthPageButtons)
  , dateTimePage(WND_DATETIMEPAGE, &helloSettingsNotebook,&helloSettingsNotebook)
  , dateTimePageHeading(WND_DATETIMEPAGEHEADING, &dateTimePage,&dateTimePage)
  , dateHeading(WND_DATEHEADING, &dateTimePage, &dateTimePage)
  , dateSettings(WND_DATESETTINGS, &dateTimePage, &dateTimePage)
  , dateLongButton(WND_DATELONGBOX, &dateSettings, &dateSettings)
  , dateShortButton(WND_DATESHORTBOX, &dateSettings, &dateSettings)
  , dateLongExample(WND_DATELONGEXAMPLE, &dateSettings, &dateSettings)
  , dateShortExample(WND_DATESHORTEXAMPLE,&dateSettings,&dateSettings)
  , timeHeading(WND_TIMEHEADING, &dateTimePage, &dateTimePage)
  , timeSettings(WND_TIMESETTINGS, &dateTimePage, &dateTimePage)
  , timeLongButton(WND_TIMELONGBOX, &timeSettings, &timeSettings)
  , timeShortButton(WND_TIMESHORTBOX, &timeSettings, &timeSettings)
  , timeLongExample(WND_TIMELONGEXAMPLE, &timeSettings, &timeSettings)
  , timeShortExample(WND_TIMESHORTEXAMPLE,&timeSettings,&timeSettings)
  , dateTimePageButtons(WND_DATETIMEPAGEBUTTONS, &dateTimePage,&dateTimePage)
  , dateTimeApplyButton(DID_DATETIMEAPPLY, &dateTimePageButtons,
                  &dateTimePageButtons)
  , dateTimeResetButton(DID_DATETIMERESET, &dateTimePageButtons,
                  &dateTimePageButtons)
  , dateTimeCloseButton(DID_NOTEBOOKCLOSE, &dateTimePageButtons,
                  &dateTimePageButtons)
  , notebookCommandHandler(this)
{
/*------------------------------------------------------------------------|
| Load text strings from the resource file and set alignment where needed.|
|------------------------------------------------------------------------*/
  earthPageHeading.setText(IResourceId(STR_EARTHPAGEHEADING))
                  .setAlignment(IStaticText::centerCenter);
  starsHeading.setText(IResourceId(STR_STARSHEADING));
  twinkleBox.setText(IResourceId(STR_TWINKLEBOX));
  brightBox.setText(IResourceId(STR_BRIGHTBOX));
  layersHeading.setText(IResourceId(STR_LAYERSHEADING));
  earthColorHeading.setText(IResourceId(STR_EARTHCOLORHEADING));
  cyanButton.setText(IResourceId(STR_CYAN));
  greenButton.setText(IResourceId(STR_GREEN));
  whiteButton.setText(IResourceId(STR_WHITE));
  yellowButton.setText(IResourceId(STR_YELLOW));
  earthApplyButton.setText(IResourceId(STR_APPLY));
  earthResetButton.setText(IResourceId(STR_RESET));
  earthCloseButton.setText(IResourceId(STR_CLOSE));

  dateTimePageHeading.setText(IResourceId(STR_DATETIMEPAGEHEADING))
                     .setAlignment(IStaticText::centerCenter);
  dateHeading.setText(IResourceId(STR_DATEHEADING));
  dateLongButton.setText(IResourceId(STR_DATELONGBOX));
  dateShortButton.setText(IResourceId(STR_DATESHORTBOX));
  dateLongExample.setText(IResourceId(STR_DATELONGEXAMPLE))
                 .setAlignment(IStaticText::centerLeft);
  dateShortExample.setText(IResourceId(STR_DATESHORTEXAMPLE))
                  .setAlignment(IStaticText::centerLeft);
  timeHeading.setText(IResourceId(STR_TIMEHEADING));
  timeLongButton.setText(IResourceId(STR_TIMELONGBOX));
  timeShortButton.setText(IResourceId(STR_TIMESHORTBOX));
  timeLongExample.setText(IResourceId(STR_TIMELONGEXAMPLE))
                 .setAlignment(IStaticText::centerLeft);
  timeShortExample.setText(IResourceId(STR_TIMESHORTEXAMPLE))
                  .setAlignment(IStaticText::centerLeft);
  dateTimeApplyButton.setText(IResourceId(STR_APPLY));
  dateTimeResetButton.setText(IResourceId(STR_RESET));
  dateTimeCloseButton.setText(IResourceId(STR_CLOSE));

/*------------------------------------------------------------------------|
| Set the width and value for each tick mark on the slider.               |
|------------------------------------------------------------------------*/
  layersSlider.setTickLength(5)
              .setTickText(0,"0")
              .setTickText(1,"1")
              .setTickText(2,"2")
              .setTickText(3,"3");

/*------------------------------------------------------------------------|
| Place the color buttons in the colors canvas.                           |
|   Start with column 2 to get a left margin.                             |
|------------------------------------------------------------------------*/
  earthColorSettings.addToCell(&cyanButton,  2,1)
                    .addToCell(&greenButton, 2,2)
                    .addToCell(&whiteButton, 3,1)
                    .addToCell(&yellowButton,3,2);

/*------------------------------------------------------------------------|
| Organize the Earth settings page on the earthPage multicell canvas.     |
|   Start with column 2 to get a left margin.                             |
|   The headings span 2 columns to prevent stretching of the controls.    |
|------------------------------------------------------------------------*/
  earthPage.addToCell(&earthPageHeading,   2, 1,2,1)
           .addToCell(&starsHeading,       2, 4,2,1)
           .addToCell(&starsSettings,      2, 5,1,1)
           .addToCell(&layersHeading,      2, 8,2,1)
           .addToCell(&layersSlider,       2, 9,1,2)
           .addToCell(&earthColorHeading,  2,13,2,1)
           .addToCell(&earthColorSettings, 2,14,1,2)
           .addToCell(&earthPageButtons,   2,18,2,1);

/*------------------------------------------------------------------------|
| Call the function that sets the earth page values from the source       |
|   AEarthWindow.                                                         |
|------------------------------------------------------------------------*/
  resetEarthSettings();
  twinkleBox.enableTabStop();
  layersSlider.enableTabStop();
  cyanButton.enableTabStop();
  earthApplyButton.enableTabStop();

/*------------------------------------------------------------------------|
| Organize the date & time radio buttons and examples on the              |
|   dateTimeSettings multicell canvas.                                    |
|   Start with column 2 to get a left margin.                             |
|   The controls are placed in column 2 and the examples in column 3.     |
|   The setAlignment(IStaticText::centerLeft) functions used when setting |
|     the text values cause the examples to align vertically.             |
|------------------------------------------------------------------------*/

  dateSettings.addToCell(&dateLongButton,  2, 1)
              .addToCell(&dateLongExample, 3, 1)
              .addToCell(&dateShortButton, 2, 2)
              .addToCell(&dateShortExample,3, 2);
  timeSettings.addToCell(&timeLongButton,  2, 1)
              .addToCell(&timeLongExample, 3, 1)
              .addToCell(&timeShortButton, 2, 2)
              .addToCell(&timeShortExample,3, 2);

/*------------------------------------------------------------------------|
| Organize the date & time settings page on the dateTimePage canvas.      |
|   Start with column 2 to get a left margin.                             |
|   The headings span 2 columns to prevent stretching of the controls.    |
|   The settings canvases contained in the page canvas is assigned to an  |
|     area that is two columns by two rows.                               |
|------------------------------------------------------------------------*/
  dateTimePage.addToCell(&dateTimePageHeading,2, 1,2,1)
              .addToCell(&dateHeading,        2, 4,2,1)
              .addToCell(&dateSettings,       2, 5,2,2)
              .addToCell(&timeHeading,        2, 9,1,1)
              .addToCell(&timeSettings,       2,10,2,2)
              .addToCell(&dateTimePageButtons,2,14,2,1);

/*------------------------------------------------------------------------|
| Call the function that sets the date & time page values from the source |
|   AHelloWindow.                                                         |
|------------------------------------------------------------------------*/
  resetDateTimeSettings();
  dateLongButton.enableTabStop();
  timeLongButton.enableTabStop();
  dateTimeApplyButton.enableTabStop();

/*-------------------- Setup the Settings Notebook -----------------------|
| Create the notebook page settings with attributes for a major tab and   |
|   automatic page size.                                                  |
| Set tab text to the Earth tab text from the resource file.              |
| Use the earthPage canvas and the notebook settings to add a page to the |
|   beginning of the notebook.                                            |
| Reset the tab text to the date and time tab text from the resource file.|
| Use the dateTimePage canvas and the notebook settings to add a page to  |
|   the end of the notebook.                                              |
| The Motif release of the User Interface Class Library automatically     |
|    sizes the major tab. For other releases, manually resize the tabs.   |
|------------------------------------------------------------------------*/
  INotebook::PageSettings
        helloSettings(INotebook::PageSettings::majorTab|
                      INotebook::PageSettings::autoPageSize);
  helloSettings.setTabText(IResourceId(STR_EARTHTAB));
  helloSettingsNotebook.addFirstPage(helloSettings,&earthPage);
  helloSettings.setTabText(IResourceId(STR_DATETIMETAB));
  helloSettingsNotebook.addLastPage(helloSettings,&dateTimePage);
  helloSettingsNotebook.setMajorTabSize(ISize(100,30));  // Ignored on Motif

/*------------------------------------------------------------------------|
| When a page is added to a notebook and using the autoPageSize style,    |
| the pages are automatically resized to the current notebook size.       |
| Therefore, we need to resize the notebook pages to their minimum size   |
| so that the notebook can properly calculate it's minimum size.          |
-------------------------------------------------------------------------*/
  earthPage.sizeTo( earthPage.minimumSize() );
  dateTimePage.sizeTo( dateTimePage.minimumSize() );

/*-------------------- Complete Setup of the Frame -----------------------|
| Place the notebook into the client portion of the ANotebookWindow frame.|
| Start processing command events for all the controls in the notebook.   |
|------------------------------------------------------------------------*/
  setClient(&helloSettingsNotebook);
  notebookCommandHandler.handleEventsFor(&helloSettingsNotebook);

/*--------------------------------------------------------------------------|
| Resize the notebook frame window based on the minimum size of the notebook|
---------------------------------------------------------------------------*/
  moveSizeToClient( IRectangle( position(),
                    helloSettingsNotebook.minimumSize() ) );

} /* end ANotebookWindow :: ANotebookWindow(...) */

/**************************************************************************
* Class ANotebookWindow :: ~ANotebookWindow - Destructor for the notebook *
*   window                                                                *
**************************************************************************/
ANotebookWindow :: ~ANotebookWindow()
{
  notebookCommandHandler.stopHandlingEventsFor(&helloSettingsNotebook);
} /* end ANotebookWindow :: ~ANotebookWindow() */

/**************************************************************************
* Class ANotebookWindow :: applyEarthSettings -Apply earth settings       *
*   changes to the owner's earth window.                                  *
**************************************************************************/
ANotebookWindow& ANotebookWindow :: applyEarthSettings()
{
  AHelloWindow *helloWindow = (AHelloWindow *)owner();
  helloWindow->earth()->enableTwinkle(twinkleBox.isSelected());
  helloWindow->earth()->enableBright(brightBox.isSelected());
  helloWindow->earth()->setLayers(layersSlider.armTickOffset());
  if (cyanButton.isSelected())
    helloWindow->earth()->setEarthColor(IColor::kCyan);
  if (greenButton.isSelected())
    helloWindow->earth()->setEarthColor(IColor::kGreen);
  if (whiteButton.isSelected())
    helloWindow->earth()->setEarthColor(IColor::kWhite);
  if (yellowButton.isSelected())
    helloWindow->earth()->setEarthColor(IColor::kYellow);

  return (*this);
} /* end ANotebookWindow :: applyEarthSettings() */

/**************************************************************************
* Class ANotebookWindow :: resetEarthSettings - Reset local earth         *
*   settings to the current settings from the owner's earth window.       *
**************************************************************************/
ANotebookWindow& ANotebookWindow :: resetEarthSettings()
{
  AHelloWindow *helloWindow = (AHelloWindow *)owner();
  helloWindow->earth()->isTwinkling()  ? twinkleBox.select()
                                        : twinkleBox.deselect();
  helloWindow->earth()->isBright()     ? brightBox.select()
                                        : brightBox.deselect();
  layersSlider.moveArmToTick(helloWindow->earth()->layers());
  if (helloWindow->earth()->earthColor().predefinedColor()==IColor::kCyan)
    cyanButton.select();
  if (helloWindow->earth()->earthColor().predefinedColor()==IColor::kGreen)
    greenButton.select();
  if (helloWindow->earth()->earthColor().predefinedColor()==IColor::kWhite)
    whiteButton.select();
  if (helloWindow->earth()->earthColor().predefinedColor()==IColor::kYellow)
    yellowButton.select();

  return (*this);
} /* end ANotebookWindow :: resetEarthSettings() */

/**************************************************************************
* Class ANotebookWindow :: applyDateTimeSettings -Apply date and time     *
*   settings changes to the owner's window.                               *
**************************************************************************/
ANotebookWindow& ANotebookWindow :: applyDateTimeSettings()
{
  AHelloWindow *helloWindow = (AHelloWindow *)owner();
  helloWindow->enableDateLong(dateLongButton.isSelected());
  helloWindow->enableTimeLong(timeLongButton.isSelected());

  return (*this);
} /* end ANotebookWindow :: applyDateTimeSettings() */

/**************************************************************************
* Class ANotebookWindow :: resetDateTimeSettings - Reset local date and   *
*   time settings to current settings from the owner's window.            *
**************************************************************************/
ANotebookWindow
  &ANotebookWindow :: resetDateTimeSettings()
{
  AHelloWindow *helloWindow = (AHelloWindow *)owner();
  helloWindow->isDateLong() ? dateLongButton.select()
                            : dateShortButton.select();
  helloWindow->isTimeLong() ? timeLongButton.select()
                            : timeShortButton.select();
  return (*this);
} /* end ANotebookWindow :: resetDateTimeSettings() */

/**************************************************************************
* Class ANotebookCommandHandler :: ANotebookCommandHandler - Constructor  *
*   for the command handler                                               *
* Stores a pointer to the window for which events will be handled.        *
**************************************************************************/
ANotebookCommandHandler :: ANotebookCommandHandler(ANotebookWindow *nbFrame)
   : frame(nbFrame)
{
} /* end ANotebookCommandHandler :: ANotebookCommandHandler(...) */

/**************************************************************************
* Class ANotebookCommandHandler :: command - Process command events for   *
*   ANotebookWindow.                                                      *
**************************************************************************/
bool
  ANotebookCommandHandler :: command(ICommandEvent & cmdEvent)
{
  bool eventProcessed(true);         //Assume event will be processed

/*------------------------------------------------------------------------|
|  Depending on the command event ID,                                     |
|    update or reset local settings to the Hello World settings.          |
|  Regardless of the page, if the close button is pressed, close notebook.|
|------------------------------------------------------------------------*/
  switch (cmdEvent.commandId()) {
    case DID_EARTHAPPLY:
      frame->applyEarthSettings();
      break;
    case DID_EARTHRESET:
      frame->resetEarthSettings();
      break;
    case DID_DATETIMEAPPLY:
      frame->applyDateTimeSettings();
      break;
    case DID_DATETIMERESET:
      frame->resetDateTimeSettings();
      break;
    case DID_NOTEBOOKCLOSE:
      frame->close();
      break;
    default:                            //Otherwise,
      eventProcessed=false;             //  the event wasn't processed
  } /* end switch */

  return(eventProcessed);
} /* end ANotebookCommandHandler :: command(...) */
