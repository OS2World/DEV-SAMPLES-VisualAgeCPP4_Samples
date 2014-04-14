/******************************************************************************
* .FILE:         ahellow4.hpp                                                 *
*                                                                             *
* .DESCRIPTION:  Hello World Sample Program Version 4: Class Header           *
*                                                                             *
* .CLASSES:      AHelloWindow                                                 *
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
#ifndef _AHELLOW4_
#define _AHELLOW4_

#include <iframe.hpp>
#include <istattxt.hpp>
#include <iinfoa.hpp>
#include <imenubar.hpp>
#include <icmdhdr.hpp>
#include <isetcv.hpp>
#include <ipushbut.hpp>

class AHelloWindow;

/**************************************************************************
* Class ACommandHandler -- Handler for main frame window                  *                                                *
**************************************************************************/
class ACommandHandler : public ICommandHandler
{
  public:

/*------------------------------ Constructor -----------------------------|
| Construct the object with:                                              |
| 1) A pointer to the main frame window                                   |
-------------------------------------------------------------------------*/
    ACommandHandler(AHelloWindow *helloFrame);

/*------------------------------ Destructor ------------------------------|
| Destruct the object with:                                               |
| 1) No parameters                                                        |
-------------------------------------------------------------------------*/
    virtual
     ~ACommandHandler() { };

  protected:
/*------------------------ Override Command Function ---------------------|
| The command function is called to handle application command events.    |
-------------------------------------------------------------------------*/
    virtual bool
      command(ICommandEvent& cmdEvent);

  private:
    AHelloWindow
     *frame;
};


/**************************************************************************
* Class AHelloWindow--Main Frame Window                                   *
**************************************************************************/
class AHelloWindow : public IFrameWindow
{
  public:

/*------------------------------------------------------------------------|
| The following enumeration type is used to specify the alignment of      |
| text in the hello static text window.                                   |
|------------------------------------------------------------------------*/
    enum Alignment
    {
      left, center, right
    };
/*-------------------------- Constructor ----------------------------------
| Constructs the object by either:                                        |
| 1) WindowID                                                             |
|------------------------------------------------------------------------*/
    AHelloWindow(const unsigned long windowId);

/*--------------------------- Destructor ----------------------------------
| Destruct the object in only one way:                                    |
| 1) No Parameters                                                        |
|------------------------------------------------------------------------*/
    virtual
     ~AHelloWindow();

/*------------------------------------------------------------------------|
| This function is used to change the hello static text window.           |
|   setTextAlignment - Align the static text horizontally.  The text is   |
|           always centered vertically by design.                         |
|   editText - Use a modal dialog window to edit the text in the static   |
|           text window.                                                  |
|------------------------------------------------------------------------*/
    virtual AHelloWindow
     &setTextAlignment( const Alignment alignment),
     &editText();

  private:
    IMenuBar
      menuBar;
    IStaticText
      statusLine,
      hello;
    ISetCanvas
      buttons;
    IPushButton
      leftButton,
      centerButton,
      rightButton;
    IInfoArea
      infoArea;
    ACommandHandler
      commandHandler;

/*------------------------------ Operators -------------------------------|
| Operators defined for this class:                                       |
|  =  -- Assignment operator                                              |
-------------------------------------------------------------------------*/
    AHelloWindow
      &operator=(const AHelloWindow&);    //Default assignment operator
};
#endif
