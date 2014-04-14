/******************************************************************************
* .FILE:         ahellow6.hpp                                                 *
*                                                                             *
* .DESCRIPTION:  Hello World Sample Program Version 6: Class Header           *
*                                                                             *
* .CLASSES:      AEarthWindow                                                 *
*                ANoteBookWindow                                              *
*                ASelectHandler                                               *
*                AHelpHandler                                                 *
*                AHelloTimeHandler                                            *
*                APopUpHandler                                                *
*                ANotebookWindow                                              *
*                ACommandHandler                                              *
*                ATimeTick                                                    *
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
#ifndef _AHELLOW6_
#define _AHELLOW6_

#include <iframe.hpp>
#include <istattxt.hpp>
#include <iinfoa.hpp>
#include <imenubar.hpp>
#include <icmdhdr.hpp>
#include <isetcv.hpp>
#include <ipushbut.hpp>
#include <isplitcv.hpp>
#include <ilistbox.hpp>
#include <iselhdr.hpp>
#include <ihelphdr.hpp>
#include <ihelp.hpp>
#include <ipopmenu.hpp>
#include <imenuhdr.hpp>
#include "aearthw6.hpp"
#include "anotebw6.hpp"

//Forward declarations for other classes:
class AHelloWindow;
class ANotebookWindow;

/**************************************************************************
* Class TimeUpdate - Time Handler class the processes time ticks          *
*   for AHelloWindow.                                                     *
**************************************************************************/
class TimeUpdate : public ITimerFn
{
  public:
/*---------------------------- Constructor -------------------------------|
| Constructs the object with                                              |
| 1) A pointer to the the main window                                     |
-------------------------------------------------------------------------*/
    TimeUpdate( AHelloWindow *a ) : ahw(a) {}

/*------------------------ Overridden Functions---------------------------|
| timerExpired function is called each time the ITimer expires.           |
-------------------------------------------------------------------------*/
    virtual void
      timerExpired (unsigned long);

  private:
    AHelloWindow
     *ahw;
};


/**************************************************************************
* Class ACommandHandler - Command Handler class that handles commands     *
*   specifically for AHelloWindow class windows.                          *
**************************************************************************/
class ACommandHandler : public ICommandHandler
{
  public:
/*----------------------------- Constructor ------------------------------|
| Constructs an object with                                               |
| 1) A pointer to the window being handled                                |
-------------------------------------------------------------------------*/
    ACommandHandler(AHelloWindow *helloFrame);

/*----------------------------- Destructor -------------------------------|
| Destructs an object with                                                |
| 1) no parameters                                                        |
-------------------------------------------------------------------------*/
    virtual ~ACommandHandler() { }

  protected:
/*------------------------ Override Command Function ---------------------|
| The command function is called to handle application command events.    |
|------------------------------------------------------------------------*/
    virtual bool
      command(ICommandEvent& cmdEvent);

  private:
    AHelloWindow *frame;
};

/**************************************************************************
* Class ASelectHandler - Select Handler class that handles list box       *
*   selections specifically for AHelloWindow class windows.               *
**************************************************************************/
class ASelectHandler : public ISelectHandler
{
  public:
/*----------------------------- Constructor ------------------------------|
| Constructs an object with                                               |
| 1) A pointer to the window being handled                                |
-------------------------------------------------------------------------*/
    ASelectHandler(AHelloWindow *helloFrame);

/*----------------------------- Destructor -------------------------------|
| Destructs an object with                                                |
| 1) no parameters                                                        |
-------------------------------------------------------------------------*/
    virtual
     ~ASelectHandler() { }

  protected:
/*------------------------ Override Selected Function --------------------|
| The selected() function is called to handle list box selection events.  |
|------------------------------------------------------------------------*/
    virtual bool
      selected(IControlEvent& ctlEvent);

  private:
    AHelloWindow
     *frame;
};

/**************************************************************************
* Class AHelpHandler - Help Handler class that only overrides one         *
*          IHelpHandler function, keysHelpId().  If keysHelpId()          *
*          is not overridden, then the default action sets the event      *
*          result to zero, which indicates that no action is required,    *
*          that is, no help information for keys is displayed.            *
**************************************************************************/
class AHelpHandler : public IHelpHandler
{
  public:
/*----------------------------- Destructor -------------------------------|
| Destructs an object with                                                |
| 1) no parameters                                                        |
-------------------------------------------------------------------------*/
    virtual
     ~AHelpHandler() { }

  protected:
/*----------------------- Override keysHelpId Function -------------------|
| The keysHelpId() function is called to set the event result to the      |
|   ID within the Hello World help libraries for Keys Help.               |
|------------------------------------------------------------------------*/
    virtual bool
         keysHelpId(IEvent& evt);
};

/**************************************************************************
* Class APopUpHandler : Menu Handler class that handles makePopUpMenu     *
*   requests specifically for AHelloWindow class windows.                 *
**************************************************************************/
class APopUpHandler : public IMenuHandler
{
  protected:
/*------------------- Override MakePopUpMenu Function --------------------|
| The makePopUpMenu function is called to process requests for showing    |
|   pop-up menus for windows attached to this handler.                    |
|------------------------------------------------------------------------*/
    virtual bool
      makePopUpMenu(IMenuEvent& menuEvent);
};

/**************************************************************************
* Class AHelloWindow - Main Window class                                  *
**************************************************************************/
class AHelloWindow : public IFrameWindow
{
  public:
/*---------------------------- Constructor -------------------------------|
| Constructs an object with                                               |
| 1) the window ID                                                        |
-------------------------------------------------------------------------*/
    AHelloWindow(unsigned long windowId);

/*----------------------------- Destructor -------------------------------|
| Destructs an object with                                                |
| 1) no parameters                                                        |
-------------------------------------------------------------------------*/
    virtual ~AHelloWindow();

/*------------------------ Hello Text Alignment --------------------------|
| The following enumeration type is used to specify the alignment of      |
| text in the hello static text window.                                   |
|------------------------------------------------------------------------*/
    enum Alignment
    {
      left, center, right
    };
/*---------------------- Hello Static Text Functions ---------------------|
| These functions are used to change the hello static text window.        |
|   setAlignment - Align the static text horizontally.  The text is       |
|           always centered vertically by design.                         |
|   editText - Use a modal dialog window to edit the text in the static   |
|           text window.                                                  |
|   setTextFromListBox -  Set the text to the first selected item in the  |
|           list box.                                                     |
³   setHelloFont - Use a modal font dialog window to change the font of   |
|           static text.                                                  |
|------------------------------------------------------------------------*/
    virtual AHelloWindow
       &setTextAlignment(const Alignment alignment),
       &editText(),
       &setTextFromListBox(),
       &setHelloFont();
/*----------------------- Hello Settings Functions -----------------------|
| These functions are used to manage attributes of the hello and          |
| earthWindow static text windows.                                        |
|   readHelloSettings - Read saved settings from an IProfile file.  A     |
|           message box displays the success or failure of the read       |
|           operation.                                                    |
|   openHelloSettings - Open a non-modal frame window containing a        |
|           notebook window with multiple controls for changing           |
|           settings in AHelloWindow.                                     |
|   saveHelloSettings - Save current AHelloWindow settings in an IProfile |
|           file.  A message box displays the success or failure of the   |
|           save operation.                                               |
|   earth - Provide non-AHelloWindow functions with access to the         |
|           AEarthWindow settings functions by returning a pointer to     |
|           the earthWindow object contained in AHelloWindow.             |
|------------------------------------------------------------------------*/
    virtual AHelloWindow
     &readHelloSettings(),
     &openHelloSettings(),
     &saveHelloSettings();
    AEarthWindow
     *earth();
/*-------------------- Hello Date and Time Functions ---------------------|
| These functions are used to manage the date and time static text        |
| windows in AHelloWindow.                                                |
|   tickTime - Update date and time windows if the current values are     |
|           different than what is displayed.  This is the function that  |
|           the AHelloTimeHandler::tick calls each time a timer event isu |
|           processed.                                                    |
|   enableDateLong - Change the format of the date to long,               |
|           for example, August 10, 1994.                                 |
|   disableDateLong - Change the format of the date to short,             |
|           for example, 08/10/94 (depending on locale).                  |
|   enableTimeLong - Change the format of the time to long,               |
|           for example, 01:57:59.                                        |
|   disableTimeLong - Change the format of the time to short,             |
|           for example, 13:57.                                           |
|   isDateLong - Return true is date format is long.                      |
|   isTimeLong - Return true is time format is long.                      |
|------------------------------------------------------------------------*/
    virtual AHelloWindow
     &tickTime(),
     &enableDateLong(bool makingLong=true),
     &disableDateLong(),
     &enableTimeLong(bool makingLong=true),
     &disableTimeLong();
    const bool
      isDateLong(),
      isTimeLong();

  private:
    IMenuBar
      menuBar;
    ISplitCanvas
      statusCanvas,
      clientWindow,
      helloCanvas;
    ISetCanvas
      buttons;
    IStaticText
      hello,
      statusLine,
      statusDate,
      statusTime;
    AEarthWindow
      earthWindow;
    IListBox
      listBox;
    IPushButton
      leftButton,
      centerButton,
      rightButton,
      helpButton;
    IInfoArea
      infoArea;
    ACommandHandler
      commandHandler;
    ASelectHandler
      selectHandler;
    AHelpHandler
      helpHandler;
    IHelpWindow
      helpWindow;
    APopUpHandler
      popUpHandler;
    ANotebookWindow
     *settingsNotebook;
    bool
      dateLong,
      timeLong;
    ITimer
      timeTicker;
};
#endif
