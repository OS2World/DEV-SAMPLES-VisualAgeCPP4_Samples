/******************************************************************************
* .FILE:         adialog6.cpp                                                 *
*                                                                             *
* .DESCRIPTION:  Hello World Sample Program Version 6: Dialog Implementation  *
*                                                                             *
* .CLASSES:      ATextDialog                                                  *
*                ADialogCommandHandler                                        *
*                AHelloWorld                                                  *
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
#ifndef _ADIALOG6_
#define _ADIALOG6_

#include <iframe.hpp>
#include <icmdhdr.hpp>
#include <istring.hpp>
#include <imcelcv.hpp>
#include <istattxt.hpp>
#include <icombobx.hpp>
#include <isetcv.hpp>
#include <ipushbut.hpp>

//Forward declarations for other classes:

class ATextDialog;

/**************************************************************************
* Class ADialogCommandHandler - Command handler for ADialogWindow class   *
**************************************************************************/
class ADialogCommandHandler : public ICommandHandler
{
  public:
/*---------------------------- Constructor -------------------------------|
| Constructs an object with:                                              |
| 1) A pointer to the TextDialog                                          |
-------------------------------------------------------------------------*/
    ADialogCommandHandler(ATextDialog *dialogFrame);

/*----------------------------- Destructor -------------------------------|
| Destructs an object with:                                               |
| 1) No parameters                                                        |
-------------------------------------------------------------------------*/
    virtual
     ~ADialogCommandHandler() { }


  protected:
/*------------------------ Override Command Function ---------------------|
| The command function is called to handle application command events.    |
|------------------------------------------------------------------------*/
    virtual bool
      command(ICommandEvent& cmdEvent);

  private:
    ATextDialog
     *frame;
};

/**************************************************************************
* Class  ATextDialog - Dialog Window class for changing "Hello World!!"   *
*   string.                                                               *
**************************************************************************/
class ATextDialog : public IFrameWindow
{
  public:
/*---------------------------- Constructor -------------------------------|
| Constructs an object with:                                              |
| 1) the string to be edited and the parent window                        |
-------------------------------------------------------------------------*/
    ATextDialog(IString & textString, IWindow * ownerWnd);

/*---------------------------- Destructor --------------------------------|
| Destructs an object with:                                               |
| 1) no parameters                                                        |
-------------------------------------------------------------------------*/
    virtual
     ~ATextDialog();

    virtual ATextDialog
     &setTextFromEntryField();

  private:
    IString
     &saveText;
    IMultiCellCanvas
      clientCanvas;
    IStaticText
      statText;
    IComboBox
      textField;
    ISetCanvas
      buttons;
    IPushButton
      pushButton1,
      pushButton2;
    ADialogCommandHandler
      dialogCommandHandler;
};

#endif

