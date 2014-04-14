/******************************************************************************
* .FILE:         ahellow6.cpp                                                 *
*                                                                             *
* .DESCRIPTION:  Hello World Sample Program Version 6: Class Implementation   *
*                                                                             *
* .CLASSES:      AEarthWindow                                                 *
*                ANoteBookWindow                                              *
*                ASelectHandler                                               *
*                AHelpHandler                                                 *
*                AHelloTimeHandler                                            *
*                APopUpHandler                                                *
*                ANotebookWindow                                              *
*                ACommandHandler                                              *
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
#include <ifont.hpp>
#include <istring.hpp>
#include <idate.hpp>
#include <itime.hpp>
#include <imsgbox.hpp>
#include <iprofile.hpp>
#include <ifontdlg.hpp>
#include <stdlib.h>
#include <icoordsy.hpp>

#include "aearthw6.hpp"
#include "ahellow6.hpp"
#include "ahellow6.h"
#include "adialog6.hpp"
#define HELP_LIBRARIES "ahellow6.hlp"
#define APPLICATION_NAME "Hello6"


/**************************************************************************
* main  - Application entry point for Hello World Version 6.              *
*                                                                         *
* Seeds the random number generator                                       *                                                                         *
* Creates a new object mainWindow of class AHelloWindow                   *
* Sets Hello World window alignment                                       *
* Sets the size of mainWindow                                             *
* Sets the window focus to mainWindow                                     *
* Displays the mainWindow                                                 *
* Starts the events processing for the application                        *
**************************************************************************/
int main()
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::kOriginLowerLeft );
  srand(time(NULL));
  #ifdef USE_IPF
  IHelpWindow::setDefaultStyle( IHelpWindow::defaultStyle()
                                | IHelpWindow::ipfCompatible );
  #endif
  AHelloWindow mainWindow (WND_MAIN);
  mainWindow.setTextAlignment(AHelloWindow::left);
  mainWindow.sizeTo(ISize(400,300));
  mainWindow.setFocus();
  mainWindow.show();
  IApplication::current().run();
  return 0;
} /* end main */

/**************************************************************************
* AHelloWindow :: AHelloWindow - Constructor for the main window          *
*                                                                         *
* Construct the IFrameWindow using the default style plus minimizedIcon,  *
*   which gets the Icon identified in the resource file and associates it *
*   with the main window.  The accelerator style causes the accelerator   *
*   table to be loaded from the resource file.                            *
*  Create a menu bar object for the main window menu bar that was loaded  *
*    from the resource file.  menuBar is used by setAlignment to          *
*    manipulate check marks on the menu items.                            *
*  Create the statusCanvas split canvas making the AHelloWindow its       *
*    parent window and let its orientation default to vertical.           *
*  Create a static text object for displaying the status of the           *
*    Hello World text alignment and make it the first child of the        *
*    statusCanvas.  It will be the leftmost window of the statusCanvas.   *
*  Create static text objects for displaying the date and time and        *
*    make them children of the statusCanvas.  The date will be in the     *
*    center window of the canvas while the time will be on the right.     *
*  Create the clientWindow split canvas to be used as the client window   *
*    of this frame and let its orientation default to vertical.           *
*  Create the helloCanvas split canvas making the clientWindow its parent *
*    window and orient it horizontally.                                   *
*  Create the hello and earthWindow static text objects as children of    *
*    the helloCanvas.  hello is placed in the topmost window of the       *
*    horizontal split canvas because it is created first.  earthWindow    *
*    is placed in the bottom window of the split canvas.                  *
*  Create the listBox window making the clientWindow its parent window    *
*    and enabling it for tabbing and preventing it from being resized     *
*    due to an item being too long.  helloCanvas is placed in the         *
*    leftmost window of the vertical split canvas because it is created   *
*    first.  listBox is placed in the right window of the split canvas.   *
*  Create a set canvas that will contain the push buttons and will be     *
*    added to the frame as an extension.                                  *
*  Create each push button with the set canvas as parent and owner.       *
*  Additionally for Help, specify help style and noPointerFocus style.    *
*    noPointerFocus prevents the mouse from changing the input focus      *
*    to the Help push button when you select it using the mouse.  This    *
*    allows you to use contextual help for the control with the input     *
*    focus rather than for the Help push button itself.                   *
*  Create the Hello World information area object from IInfoArea class.   *
*    The information area is automatically added as an extension below    *
*    the client window of the frame.                                      *
*  Create a command handler to process command events from menu item,     *
*    push button, and accelerator key selections.                         *
*  Create a select handler to process selections made in the list box.    *
*  Create an IHelpWindow object that is displayed when help is requested  *
*    from a help menu item, the help push button, or the help accelerator *
*    key, normally F1.                                                    *
*  An IHelpHandler object, helpHandler is created implicitly, see class   *
*    definition for AHelloWindow in ahellow5.hpp.                         *
*  Initialize the date and time boolean objects that contain the state of *
*    the data and time formats.                                           *
**************************************************************************/
AHelloWindow :: AHelloWindow(unsigned long windowId)
  : IFrameWindow(IFrameWindow::defaultStyle() |
                 IFrameWindow::minimizedIcon  |
                 IFrameWindow::accelerator,
                 windowId)
   ,menuBar(windowId, this)
   ,statusCanvas(WND_STATUSCANVAS,this, this)
   ,statusLine(WND_STATUS, &statusCanvas, &statusCanvas)
   ,statusDate(WND_DATE, &statusCanvas, &statusCanvas)
   ,statusTime(WND_TIME, &statusCanvas, &statusCanvas)
   ,clientWindow(WND_CANVAS, this, this)
   ,helloCanvas(WND_HCANVAS,
                &clientWindow,
                &clientWindow,
                IRectangle(),
                IWindow::visible |
                ISplitCanvas::horizontal)
   ,hello(WND_HELLO, &helloCanvas, &helloCanvas)
   ,earthWindow(WND_EARTH, &helloCanvas)
   ,listBox(WND_LISTBOX,
            &clientWindow,
            &clientWindow,
            IRectangle(),
            IListBox::defaultStyle() |
            IControl::tabStop |
            IListBox::noAdjustPosition)
   ,buttons(WND_BUTTONS, this, this)
   ,leftButton(MI_LEFT, &buttons, &buttons)
   ,centerButton(MI_CENTER, &buttons, &buttons)
   ,rightButton(MI_RIGHT, &buttons, &buttons)
   ,helpButton(MI_HELP,
               &buttons,
               &buttons,
               IRectangle(),
               IPushButton::defaultStyle() |
               IPushButton::help           |
               IButton::noPointerFocus)
   ,infoArea(this)
   ,commandHandler(this)
   ,selectHandler(this)
   ,helpWindow(HELP_TABLE,this)
   ,dateLong(false)
   ,timeLong(true)
   ,settingsNotebook( 0 )
{
/*------------------------------------------------------------------------|
|  Set the clientWindow split canvas as the client window for the         |
|    AHelloWorld frame.                                                   |
|  Set the HelloCanvas object to occupy 60% of the client canvas.         |
|  Set the list box object to occupy 40% of the client canvas.            |
|------------------------------------------------------------------------*/
  setClient(&clientWindow);
  clientWindow.setSplitWindowPercentage(&helloCanvas, 60);
  clientWindow.setSplitWindowPercentage(&listBox, 40);

/*------------------------------------------------------------------------|
|  Add the status area as an extension to the frame above the client      |
|    window with the height calculated from the maximum height of a       |
|    character in the current font.                                       |
|  Start processing timer events for updating the time.                   |
|------------------------------------------------------------------------*/
  addExtension(&statusCanvas, IFrameWindow::aboveClient,
                 IFont(&statusLine).maxCharHeight());

/*------------------------------------------------------------------------|
|  Add the different language versions of Hello World to the list box in  |
|    ascending order.  Hello World text strings are stored in the         |
|    resource file with IDs beginning with HI_WORLD with each subsequent  |
|    ID incremented up to HI_WORLD + HI_COUNT - 1.                        |
|  Have the select handler handle selections made in the list box.        |
|    The select handler's selected() function is called to process        |
|    list box selections.                                                 |
|------------------------------------------------------------------------*/
  for (int i=0;i<HI_COUNT;i++ )
     listBox.addAscending(HI_WORLD+i);
  selectHandler.handleEventsFor(&listBox);

/*------------------------------------------------------------------------|
|  Change the size of the information area using the maximum height of    |
|    a character in the current font.                                     |
|------------------------------------------------------------------------*/
  setExtensionSize(&infoArea, IFont(&infoArea).maxCharHeight());

/*------------------------------------------------------------------------|
|  Set the values for the text controls from strings in the resource file.|
|    The infoArea inactive text is displayed when no menu item is active. |
|------------------------------------------------------------------------*/
  hello.setText(STR_HELLO);
  leftButton.setText(STR_LEFTB);
  centerButton.setText(STR_CENTERB);
  rightButton.setText(STR_RIGHTB);
  helpButton.setText(STR_HELPB);
  infoArea.setDefaultText(STR_INFO);

/*------------------------------------------------------------------------|
|  Set the canvas margins and padding between buttons to zero.            |
|  Add the set canvas that contains the push buttons to the frame window  |
|    as an extension immediately below the client window with a height    |
|    equal to the minimum height of the push buttons.  You must set the   |
|    text in the push buttons first.                                      |
|------------------------------------------------------------------------*/
  leftButton.enableTabStop();
  buttons.setMargin(ISize());
  buttons.setPad(ISize());
  addExtension(&buttons, IFrameWindow::belowClient,
                (unsigned long)buttons.minimumSize().height());

/*------------------------------------------------------------------------|
|  Have the command handler handle commands sent from the frame window.   |
|    The command handler's command() function is called to process        |
|    menu item, push button, and accelerator key selections.              |
|  Attach the command handler to the hello and earthWindow static text    |
|    windows to handle command events generated for these windows by      |
|    the pop-up menus.                                                    |
|  Attach the pop-up menu handler to the hello and earthWindow static text|
|    windows to handle pop-up menu requests made while the pointer is     |
|    over these windows.  The makePopUpMenu function will be called when  |
|    the user requests a pop-up menu using the mouse in these windows.    |
|  Start the timer to update the time and date.                           |
|------------------------------------------------------------------------*/
  commandHandler.handleEventsFor(this);
  commandHandler.handleEventsFor(&hello);
  commandHandler.handleEventsFor(&earthWindow);
  popUpHandler.handleEventsFor(&hello);
  popUpHandler.handleEventsFor(&earthWindow);
  timeTicker.setInterval(1000);
  timeTicker.start(new TimeUpdate(this));

/*------------------------------------------------------------------------|
|   Add the help library to the help window using addLibraries().         |
|   Set the help window title from a string in the resource file.         |
|   Begin handling help events for the frame window.                      |
|------------------------------------------------------------------------*/
   try
   {
      helpWindow.addLibraries( HELP_LIBRARIES );
      helpWindow.setTitle(STR_HTITLE);
      helpHandler.handleEventsFor(this);
   }
   catch( ... )
   {
      IMessageBox
         msgBox( this );
      msgBox.show( STR_HELP_NOT_FOUND, IMessageBox::warning );
   }

/*------------------------------------------------------------------------|
| Align the static text, set the status line, and set the check mark in   |
|   the menu bar.                                                         |
|------------------------------------------------------------------------*/
  setTextAlignment(center);

} /* end AHelloWindow :: AHelloWindow(...) */

/**************************************************************************
* Class AHelloWindow :: ~AHelloWindow - Destructor for the main window    *
*                                                                         *
* Stop handling command events for the frame.                             *
* Stop handling select events for the list box.                           *
* Stop handling help events for the frame.                                *
* Stop handling timer events for the frame.                               *
* Stop handling menu events for the frame.                                *
**************************************************************************/
AHelloWindow :: ~AHelloWindow()
{
  commandHandler.stopHandlingEventsFor(this);
  commandHandler.stopHandlingEventsFor(&earthWindow);
  commandHandler.stopHandlingEventsFor(&hello);
  selectHandler.stopHandlingEventsFor(&listBox);
  helpHandler.stopHandlingEventsFor(this);

  popUpHandler.stopHandlingEventsFor(&hello);
  popUpHandler.stopHandlingEventsFor(&earthWindow);
  timeTicker.stop();
} /* end AHelloWindow :: ~AHelloWindow() */

/**************************************************************************
* Class AHelloWindow :: setTextAlignment - Align static text in client    *
*   window                                                                *
**************************************************************************/
AHelloWindow &
  AHelloWindow :: setTextAlignment(const Alignment alignment)
{
/*--------------------- Update Window for New Alignment ------------------|
|  Depending on the value passed, update the window as follows:           |
|    Set the alignment of the static text control in the client window.   |
|    Set the text of the alignment status line static text control.       |
|    Check the selected menu item; remove check marks from the other two. |
|------------------------------------------------------------------------*/
  switch(alignment)
  {
  case left:
    hello.setAlignment(IStaticText::centerLeft);
    statusLine.setText(STR_LEFT);
    menuBar.uncheckItem(MI_CENTER);
    menuBar.checkItem(MI_LEFT);
    menuBar.uncheckItem(MI_RIGHT);
    break;
  case center:
    hello.setAlignment(IStaticText::centerCenter);
    statusLine.setText(STR_CENTER);
    menuBar.checkItem(MI_CENTER);
    menuBar.uncheckItem(MI_LEFT);
    menuBar.uncheckItem(MI_RIGHT);
    break;
 case right:
    hello.setAlignment(IStaticText::centerRight);
    statusLine.setText(STR_RIGHT);
    menuBar.uncheckItem(MI_CENTER);
    menuBar.uncheckItem(MI_LEFT);
    menuBar.checkItem(MI_RIGHT);
    break;
 }
 return (*this);                        //Return a reference to the frame

} /* end AHelloWindow :: setTextAlignment(...) */

/**************************************************************************
* Class AHelloWindow :: editText - Create and show a dialog window for    *
*   inputting text that will be used to replace the "Hello World!!!"      *
*   static text string.                                                   *
**************************************************************************/
AHelloWindow &
  AHelloWindow :: editText()
{
/*------------------------------------------------------------------------|
|  Store the current value of the text to be changed.                     |
|  Set the text in the information area from the dialog information       |
|    string in the resource file.                                         |
|------------------------------------------------------------------------*/
  IString textValue(hello.text());
  infoArea.setDefaultText(STR_INFODLG);

/*------------------------------------------------------------------------|
|  Create a new text dialog with textValue as the string to edit and      |
|    AHelloWindow as the owner window.                                    |
|  Show the dialog modally.  This means that the owner window cannot have |
|    the focus back until the dialog is ended.                            |
|------------------------------------------------------------------------*/
  ATextDialog textDialog(textValue,this);
  textDialog.showModally();

/*------------------------------------------------------------------------|
|  If the OK button was used to end the dialog, then the static text,     |
|    hello, is set to the textValue string.  Else, it is not changed.     |
|  Reset the information area inactive text.                              |
|------------------------------------------------------------------------*/
  if (textDialog.result() == DID_OK)
        hello.setText(textValue);
  infoArea.setDefaultText(STR_INFO);

  return (*this);                       //Return a reference to the frame
}  /* end AHelloWindow :: editText() */

/**************************************************************************
* Class AHelloWindow :: setTextFromListBox - Set the Hello World text     *
*   from the first selected item in the AHelloWindow listBox.             *
**************************************************************************/
AHelloWindow &
  AHelloWindow :: setTextFromListBox()
{

/*------------------------------------------------------------------------|
|  Create a cursor to the list box.  Using the default filter for a       |
|    list box cursor, selectedItems, causes the setToFirst() function     |
|    to position the cursor to the first selected item.                   |
|  Set the hello IStaticText control text value.                          |
|------------------------------------------------------------------------*/
  IListBox::Cursor lbCursor(listBox);
  lbCursor.setToFirst();
  hello.setText(listBox.elementAt(lbCursor));

  return (*this);                       //Return a reference to the frame
}  /* end AHelloWindow :: setTextFromListBox() */

/**************************************************************************
* AHelloWindow :: setHelloFont - Starts a font dialog for changing the    *
*   font of the Hello World text.                                         *
**************************************************************************/
AHelloWindow &
  AHelloWindow :: setHelloFont()
{
/*------------------------------------------------------------------------|
|  Set the text in the information area from the font dialog information  |
|    string in the resource file.                                         |
|  Create a font from the current font of the hello static text object.   |
|  Create a font settings object from the tempFont object.                |
|  Set the title to be used in the font dialog from a string resource in  |
|    the resource file.                                                   |
|  Start the font dialog by creating an IFontDialog object.  The font     |
|    dialog is created as a modal dialog window with the desktopWindow    |
|    as the parent, the AHelloWindow frame as the owner, resetButton      |
|    style which supplies the user with a way to reset the fields in the  |
|    dialog, and the font settings that were just created.                |
|------------------------------------------------------------------------*/
  infoArea.setDefaultText(STR_FONTDLGT);
  IFont tempFont(&hello);
  IFontDialog::Settings fontSettings(&tempFont);
  fontSettings.setTitle(IResourceId(STR_FONTDLGT));
  IFontDialog fontDialog( desktopWindow(), this,
                          IFontDialog::resetButton, fontSettings);

/*------------------------------------------------------------------------|
|  If the user pressed OK in the font dialog, then change the font for    |
|    the hello IStaticText object using the tempFont object that was set  |
|    by the font dialog.                                                  |
|  Reset the information area inactive text.                              |
|------------------------------------------------------------------------*/
  if (fontDialog.pressedOK())
  {
    hello.setFont(tempFont);
  }
  infoArea.setDefaultText(STR_INFO);
  return (*this);                       //Return a reference to the frame
}  /* end AHelloWindow :: setHelloFont() */

/**************************************************************************
* Class AHelloWindow :: readHelloSettings - Reads in user settings from   *
*   an IProfile class profile.                                            *
**************************************************************************/
AHelloWindow &
  AHelloWindow :: readHelloSettings()
{
/*------------------------------------------------------------------------|
|  The try-catch blocks are used to prevent a missing profile from        |
|    abending the program.                                                |
|------------------------------------------------------------------------*/
  try
  {
/*------------------------------------------------------------------------|
|  A file named Hello6.ini.iclDB on AIX, or Hello6.ini on OS/2, is        |
|   is expected to exist, and if so, will be opened and the default       |
|   application name, Hello6, is set.                                     |
|------------------------------------------------------------------------*/
    IProfile profile(IString(APPLICATION_NAME)+".ini");
    profile.setDefaultApplicationName(APPLICATION_NAME);

/*------------------------------------------------------------------------|
|  Each Hello6 element in the profile is read using the elementWithKey or |
|    integerWithKey function, where element is used for reading strings   |
|    and integer is used for values.  The elements are identified using   |
|    unique names that are defined by this application.                   |
|  The appropriate AHelloWindow function is called to set the date and    |
|    time formats.  The arguments for the functions are integers,         |
|    representing true(1) and false(0).                                   |
|  The Font... settings are used to reset the AHelloWindow::hello         |
|    static text window font.                                             |
|  The appropriate AEarthWindow functions are called to set the painting  |
|    settings for the Earth window.                                       |
|------------------------------------------------------------------------*/
    enableDateLong(profile.integerWithKey("DateLong"));
    enableTimeLong(profile.integerWithKey("TimeLong"));

IFont
    helloFont(&hello);
    helloFont.useVectorOnly(profile.integerWithKey("FontVector"));
    helloFont.useNonPropOnly(profile.integerWithKey("FontNonProp"));
    helloFont.setName(profile.elementWithKey("FontFace"));
    helloFont.setPointSize(profile.integerWithKey("FontSize"));
    helloFont.setBold(profile.integerWithKey("FontBold"));
    helloFont.setItalic(profile.integerWithKey("FontItalic"));
    hello.setFont(helloFont);

    earth()->enableTwinkle(profile.integerWithKey("Twinkling"));
    earth()->enableBright(profile.integerWithKey("Bright"));
    earth()->setLayers(profile.integerWithKey("Layers"));

long
    hue=profile.integerWithKey("EarthColor");
    if (hue==IColor(IColor::kGreen).asRGBLong())
      { earth()->setEarthColor(IColor(IColor::kGreen)); }
    else if (hue==IColor(IColor::kWhite).asRGBLong())
      { earth()->setEarthColor(IColor(IColor::kWhite)); }
    else if (hue==IColor(IColor::kYellow).asRGBLong())
      { earth()->setEarthColor(IColor(IColor::kYellow)); }
    else
      { earth()->setEarthColor(IColor(IColor::kCyan)); }

/*------------------------------------------------------------------------|
|  A message box with an ok button is used to inform the user that the    |
|    read settings function completed successfully.            .          |
|------------------------------------------------------------------------*/
    IMessageBox mbox(this);
    mbox.setTitle(WND_MAIN).show(STR_READOK,IMessageBox::okButton);
  }
  catch (IException& exc)
  {
/*------------------------------------------------------------------------|
|  A default exception message box is used to inform the user that the    |
|    read settings function failed.                            .          |
|------------------------------------------------------------------------*/
    IMessageBox mbox(this);
    mbox.show(exc);
  }
  return (*this);                       //Return a reference to the frame
}  /* end AHelloWindow :: readHelloSettings() */

/**************************************************************************
* Class AHelloWindow :: saveHelloSettings -Saves user settings in an      *
*   IProfile class profile.                                               *
**************************************************************************/
AHelloWindow &
  AHelloWindow :: saveHelloSettings()
{
/*------------------------------------------------------------------------|
|  The try-catch blocks are used to prevent a profile error from          |
|    abending the program.                                                |
|------------------------------------------------------------------------*/
  try
  {
/*------------------------------------------------------------------------|
|  A file named Hello6.ini.iclDB on AIX, or Hello6.ini on OS/2, is        |
|   is opened, if found, or created, if not found, and the default        |
|   application name, Hello6, is set.                                     |
|------------------------------------------------------------------------*/
    IProfile profile(IString(APPLICATION_NAME)+".ini");
    profile.setDefaultApplicationName(APPLICATION_NAME);

/*------------------------------------------------------------------------|
|  The IProfile overloaded function, addOrReplaceElementWithKey, is used  |
|    to save each setting value in the profile.  Numeric and boolean      |
|    values are stored as long integers, while strings are stored as      |
|    character strings.                                                   |
|------------------------------------------------------------------------*/
    profile.addOrReplaceElementWithKey(
                    "DateLong", (long)isDateLong());
    profile.addOrReplaceElementWithKey(
                    "TimeLong", (long)isTimeLong());

IFont
    helloFont(&hello);
    profile.addOrReplaceElementWithKey(
                    "FontVector", helloFont.isVectorOnly());
    profile.addOrReplaceElementWithKey(
                    "FontNonProp", helloFont.isNonPropOnly());
    profile.addOrReplaceElementWithKey(
                    "FontFace", helloFont.name());
    profile.addOrReplaceElementWithKey(
                    "FontSize", helloFont.pointSize());
    profile.addOrReplaceElementWithKey(
                    "FontBold", helloFont.isBold());
    profile.addOrReplaceElementWithKey(
                    "FontItalic", helloFont.isItalic());

    profile.addOrReplaceElementWithKey(
                    "Twinkling",(long)earth()->isTwinkling());
    profile.addOrReplaceElementWithKey(
                    "Bright",   (long)earth()->isBright());
    profile.addOrReplaceElementWithKey(
                    "Layers",   (long)earth()->layers());
    profile.addOrReplaceElementWithKey(
                    "EarthColor",earth()->earthColor().asRGBLong());

/*------------------------------------------------------------------------|
|  A message box with an ok button is used to inform the user that the    |
|    save settings function completed successfully.            .          |
|------------------------------------------------------------------------*/
    IMessageBox mbox(this);
    mbox.setTitle(WND_MAIN).show(STR_SAVEDOK,IMessageBox::okButton);
  }
  catch (IException& exc)
  {
/*------------------------------------------------------------------------|
|  A default exception message box is used to inform the user that the    |
|    save settings function failed.                            .          |
|------------------------------------------------------------------------*/
    IMessageBox mbox(this);
    mbox.show(exc);
  }

  return (*this);                       //Return a reference to the frame
}  /* end AHelloWindow :: saveHelloSettings() */

/**************************************************************************
* Class AHelloWindow :: openHelloSettings - Opens a settings notebook for *
*   changing Hello World window attributes.                               *
**************************************************************************/
AHelloWindow &
  AHelloWindow :: openHelloSettings()
{
/*------------------------------------------------------------------------|
|  Check if the notebook already exists.                                  |
|    Zero is returned if the notebook does not exist.                     |
|------------------------------------------------------------------------*/

  if ( settingsNotebook )
  {
    delete settingsNotebook;
  }


/*------------------------------------------------------------------------|
|  Using the new operator causes the ANotebookWindow object to be         |
|    dynamically allocated.  This means that that the object will not go  |
|    out of scope, therefore the application should delete it when it is  |
|    finished with it.                                                    |
|------------------------------------------------------------------------*/

  settingsNotebook = new ANotebookWindow(WND_NOTEBOOKFRAME,this);

/*------------------------------------------------------------------------|
|  Move the notebook to ensure the entire window is visible on a small    |
|    display.                                                             |
|  The notebook is given control and shown by using setFocus and show.    |
|    The restore function is used in case the window was created          |
|    previously, but minimized.                                           |
|------------------------------------------------------------------------*/
  settingsNotebook->moveTo( IPoint(50,50) );
  settingsNotebook->restore().setFocus().show();
  return (*this);                       //Return a reference to the frame
}  /* end AHelloWindow :: openHelloSettings() */

/**************************************************************************
* ACommandHandler :: ACommandHandler - constructor for the command handler*
**************************************************************************/
ACommandHandler :: ACommandHandler(AHelloWindow *helloFrame)
{
   frame=helloFrame;                     //Save frame to be handled
} /* end ACommandHandler :: ACommandHandler(...) */

/**************************************************************************
* Class ACommandHandler :: command - Handle menu and button commands      *
**************************************************************************/
bool
  ACommandHandler :: command(ICommandEvent & cmdEvent)
{
  bool eventProcessed(true);         //Assume event will be processed

/*--------------------- Process command events ---------------------------|
|  Depending on the command event ID, call the AHelloWindow::setAlignment |
|    function with the appropriate AHelloWorld::Alignment value.          |
|  Do this except when the Text menu item is selected;                    |
|    then call the AHelloWindow::editText function for changing the       |
|    Hello World text using a dialog.                                     |
|------------------------------------------------------------------------*/
  switch (cmdEvent.commandId()) {
    case MI_CENTER:
      frame->setTextAlignment(AHelloWindow::center);
      break;
    case MI_LEFT:
      frame->setTextAlignment(AHelloWindow::left);
      break;
    case MI_RIGHT:
      frame->setTextAlignment(AHelloWindow::right);
      break;
    case MI_TEXT:
      frame->editText();
      break;
    case MI_FONT:
      frame->setHelloFont();
      break;
    case MI_READSETS:
      frame->readHelloSettings();
      break;
    case MI_OPENSETS:
      frame->openHelloSettings();
      break;
    case MI_SAVESETS:
      frame->saveHelloSettings();
      break;
    case MI_TWINKLE:                    //Toggle the twinkle setting
      frame->earth()->enableTwinkle(!frame->earth()->isTwinkling());
      break;
    case MI_BRIGHT:
      frame->earth()->enableBright();
      break;
    case MI_DIM:
      frame->earth()->disableBright();
      break;

    default:                            //Otherwise,
      eventProcessed=false;             //  the event wasn't processed
  } /* end switch */

  return(eventProcessed);
} /* end ACommandHandler :: command(...) */

/**************************************************************************
* Class ASelectHandler :: ASelectHandler - constructor for the select     *
*   handler                                                               *
**************************************************************************/
ASelectHandler :: ASelectHandler(AHelloWindow *helloFrame)
{
   frame=helloFrame;                     //Save frame to be handled
} /* end ASelectHandler :: ASelectHandler(...) */


/**************************************************************************
* Class ASelectHandler :: selected - Handle items selected within the     *
*   list box.                                                             *
**************************************************************************/
bool
  ASelectHandler :: selected(IControlEvent & evt)
{

/*------------------------------------------------------------------------|
|  Call the AHelloWindow::setTextFromListBox function for the frame used  |
|    to construct this select handler.                                    |
|------------------------------------------------------------------------*/
  frame->setTextFromListBox();

  return (true);                        //Event is always processed
} /* end ASelectHandler :: selected(...) */

/**************************************************************************
* Class AHelpHandler :: keysHelpId - Handle the keys help request event   *
**************************************************************************/
bool
  AHelpHandler :: keysHelpId(IEvent& evt)
{
  evt.setResult(1000);                  //1000=keys help ID in
                                        //  ahellow5.ipf file

  return (true);                        //Event is always processed
} /* end AHelpHandler :: keysHelpId(...) */
/**************************************************************************
* Class TimeUpdate :: timeExpired - Handles timer events for updating       *
*   the date and time.                                                    *
**************************************************************************/
void
  TimeUpdate::timerExpired( unsigned long id)
{
  ahw->tickTime();
}


/**************************************************************************
* Class AHelloWindow :: tickTime - Update the date and time using current *
*   formats if necessary                                                  *
**************************************************************************/
AHelloWindow
  &AHelloWindow::tickTime()
{
  IString
    formattedDate,
    formattedTime;

/*------------------------------------------------------------------------|
|  If the date format is long, date should appear as August 10, 1994.     |
|    Otherwise it should appear in the default locale format, eg 08/10/94.|
|------------------------------------------------------------------------*/
  if (isDateLong())
  {
    formattedDate =( (IDate().monthName()) +" "+
              IString(IDate().dayOfMonth())+", "+
              IString(IDate().year()));
  }
  else formattedDate = IDate().asString();

/*------------------------------------------------------------------------|
|  If the time format is long, time should appear as 01:44:59 pm.         |
|    Otherwise it should appear in shortened military time, eg 13:44.     |
|------------------------------------------------------------------------*/
  if (isTimeLong())
  {
    formattedTime = ITime().asString("%I:%M:%S %p");
  }
  else
    formattedTime = ITime().asString("%H:%M");

/*------------------------------------------------------------------------|
|  If the date and/or time have changed, update the status area.          |
|------------------------------------------------------------------------*/
  if (formattedDate != statusDate.text())
    statusDate.setText(formattedDate);
  if (formattedTime != statusTime.text())
    statusTime.setText(formattedTime);
  return (*this);
} /* end AHelloWindow :: tickTime() */

/**************************************************************************
* Class AHelloWindow :: earth - Accesses the earthWindow contained within *
*     AHelloWindow class object.                                          *
**************************************************************************/
AEarthWindow
  *AHelloWindow::earth()
{
  return (&earthWindow);
} /* end AHelloWindow :: earth() */

/**************************************************************************
* Class AHelloWindow :: isDateLong - Querys the state of the date format. *
**************************************************************************/
const bool
  AHelloWindow::isDateLong()
{
  return (dateLong);
} /* end AHelloWindow :: isDateLong() */

/**************************************************************************
* Class AHelloWindow :: enableDateLong - Sets the date format to long.    *
**************************************************************************/
AHelloWindow
  &AHelloWindow::enableDateLong(bool makingLong)
{
  dateLong = makingLong;
  return (*this);
} /* end AHelloWindow :: enableDateLong(...) */

/**************************************************************************
* Class AHelloWindow :: disableDateLong - Sets the date format to short.  *
**************************************************************************/
AHelloWindow
  &AHelloWindow::disableDateLong()
{
  dateLong = false;
  return (*this);
} /* end AHelloWindow :: disableDateLong() */

/**************************************************************************
* Class AHelloWindow :: isTimeLong - Querys the state of the time format. *
**************************************************************************/
const bool
  AHelloWindow::isTimeLong()
{
  return (timeLong);
} /* end AHelloWindow :: isTimeLong() */

/**************************************************************************
* Class AHelloWindow :: enableTimeLong - Set the time format to long.     *
**************************************************************************/
AHelloWindow
  &AHelloWindow::enableTimeLong(bool makingLong)
{
  timeLong = makingLong;
  return (*this);
} /* end AHelloWindow :: enableTimeLong(...) */

/**************************************************************************
* Class AHelloWindow :: disableTimeLong - Sets the time format to short.  *
**************************************************************************/
AHelloWindow
  &AHelloWindow::disableTimeLong()
{
  timeLong = false;
  return (*this);
} /* end AHelloWindow :: disableTimeLong() */

/**************************************************************************
* Class APopUpHandler :: makePopUpMenu - Creates a pop-up menu for        *
*   windows attached to the handler when requested by the pointing device *
**************************************************************************/
bool APopUpHandler::makePopUpMenu(IMenuEvent &menuEvent)
{
  bool
    eventProcessed(true);         //Assume event will be processed
  IPopUpMenu
   *popUpMenu;
/*------------------------------------------------------------------------|
|  The window pointer stored in the menu event points to the owner of     |
|    the menu to be popped up.                                            |
|------------------------------------------------------------------------*/
  IWindow       *popUpOwner = menuEvent.controlWindow();
  IStaticText   *hello;
  AEarthWindow  *earth;
/*------------------------------------------------------------------------|
|  Determine which menu to pop up based on the window ID of the window    |
|    for which the menu event is being handled.                           |
|------------------------------------------------------------------------*/
  switch (popUpOwner->id()) {
    case WND_HELLO:
/*------------------------------------------------------------------------|
|  Create a pop-up menu for the menu WND_HELLOPOPUP.                      |
|  The pointer, hello, is created by casting the popUpOwner to the type   |
|    of the AHelloWindow::hello object.  The pointer is used to call      |
|    the AHelloWindow::alignment function to determine which pop-up menu  |
|    item to disable.                                                     |
|------------------------------------------------------------------------*/
      popUpMenu = new IPopUpMenu(WND_HELLOPOPUP,popUpOwner);

      if (popUpMenu)
      {
        hello = (IStaticText *)popUpOwner;
        popUpMenu->enableItem(MI_LEFT,
                        hello->alignment()!=IStaticText::centerLeft);
        popUpMenu->enableItem(MI_CENTER,
                        hello->alignment()!=IStaticText::centerCenter);
        popUpMenu->enableItem(MI_RIGHT,
                        hello->alignment()!=IStaticText::centerRight);
      }
                                        //If the pop-up wasn't found,
      else eventProcessed=false;        //  the event wasn't processed
      break;
    case WND_EARTH:
/*------------------------------------------------------------------------|
|  If the earthWindow pop-up is requested, then create the pop-up menu    |
|    dynamically, with the earthWindow as the owner.  This approach is    |
|    used to create pop-up menus on demand.  The setAutoDeleteObject      |
|    function is used to automatically delete the menu after the user     |
|    has made a selection.                                                |
|  The pointer, earth, is created by casting the popUpOwner to the type   |
|    of the earthWindow object.  The pointer is used to call the          |
|    AEarthWindow  isTwinkling and isBright functions.                    |
|  The Twinkling menu item contains a check mark when isTwinkling is true.|
|  Either the Bright or Dim menu item is disabled, depending on the       |
|    result of isBright.                                                  |
|------------------------------------------------------------------------*/
      popUpMenu = new IPopUpMenu(WND_EARTHPOPUP,popUpOwner);
      if (popUpMenu)
      {
        popUpMenu->setAutoDeleteObject();
        earth = (AEarthWindow *)popUpOwner;
        popUpMenu->checkItem(MI_TWINKLE,earth->isTwinkling());
        if (earth->isBright())
        { popUpMenu->disableItem(MI_BRIGHT); }
        else
        { popUpMenu->disableItem(MI_DIM); }
      }
                                        //If the pop-up wasn't created,
      else eventProcessed=false;        //  the event wasn't processed
      break;
    default:                            //If the owner wasn't hello or eart
      eventProcessed=false;             //  the event wasn't processed
  } /* end switch */
/*------------------------------------------------------------------------|
|  If the pop-up menus were setup successfully, use the                   |
|    IPopUpMenu::show function to show the menu at the position where the |
|    pointing device was when the menu event occurred.                    |
|------------------------------------------------------------------------*/
  if (eventProcessed)
    popUpMenu->show(menuEvent.mousePosition());
  return(eventProcessed);
} /* end APopUpHandler :: makePopUpMenu(...) */

