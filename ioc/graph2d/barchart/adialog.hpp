/*
-------------------------------------------------------------------------------
Copyright (c) IBM Corporation 1997.
All Rights Reserved.

Permission is granted to copy, use, modify, and merge this software into your
applications and to permit others to do any of the foregoing. You must include
this permission and copyright notice in all copies and modified versions of
this software. THIS SOFTWARE IS PROVIDED IN ITS 'AS IS' CONDITION.
IBM DISCLAIMS ANY LIABILITY OF ANY KIND FOR DAMAGES WHATSOEVER RESULTING
FROM THE USE OF THIS SOFTWARE.
-------------------------------------------------------------------------------
*/

/******************************************************************************
* .FILE:         adialog.hpp                                                  *
*                                                                             *
* .DESCRIPTION:  BarChart Sample Program: Class Header                        *
*                                                                             *
* .CLASSES:      AInputDialogCommandHandler                                   *
*                AInputDialog                                                 *
*                                                                             *
* .NOTE: WE RECOMMEND USING A FIXED SPACE FONT TO LOOK AT THE SOURCE          *
*                                                                             *
******************************************************************************/
#ifndef _ADIALOG_HPP
#define _ADIALOG_HPP

#include <iframe.hpp>
#include <icmdhdr.hpp>
#include <istring.hpp>
#include <imcelcv.hpp>
#include <istattxt.hpp>
#include <ientryfd.hpp>
#include <isetcv.hpp>
#include <ipushbut.hpp>

class AInputDialog;

/**************************************************************************
* Class AInputDialogCommandHandler - Command handler for AInputDialogWindow class   *
**************************************************************************/
class AInputDialogCommandHandler : public ICommandHandler
{
  public:
/*---------------------------- Constructor -------------------------------|
| Constructs an object with:                                              |
| 1) A pointer to the InputDialog                                          |
-------------------------------------------------------------------------*/
    AInputDialogCommandHandler(AInputDialog *dialogFrame);

/*----------------------------- Destructor -------------------------------|
| Destructs an object with:                                               |
| 1) No parameters                                                        |
-------------------------------------------------------------------------*/
    virtual
     ~AInputDialogCommandHandler() { }


  protected:
/*------------------------ Override Command Function ---------------------|
| The command function is called to handle application command events.    |
|------------------------------------------------------------------------*/
  virtual bool
    command(ICommandEvent& cmdEvent);

  private:
    AInputDialog
     *frame;
};


/**************************************************************************
* Class AInputDialog - Dialog Window class that takes input data           *
**************************************************************************/
class AInputDialog : public IFrameWindow
{
  public:
         // constructor
                AInputDialog( unsigned long   firstStrID,  IWindow * ownerWnd);

                AInputDialog( unsigned long   firstStrID, unsigned long  secondStrID , IWindow * ownerWnd);

    //destructor
                virtual
     ~AInputDialog();

    // get the input string from first enty
    virtual IString
     getValueFromFirstEntry();

    // get the input string from second enty
    virtual IString
     getValueFromSecondEntry();

  private:
    IMultiCellCanvas
      clientCanvas;
    IStaticText
      firstText;
    IEntryField
      firstField;
    IStaticText
      secondText;
    IEntryField
      secondField;
    ISetCanvas
      buttons;
    IPushButton
      pushButton1,
      pushButton2;
    AInputDialogCommandHandler
      dialogCommandHandler;

/*------------------------------ Operators -------------------------------|
| Operators defined for this class:                                       |
|  =  -- Assignment operator                                              |
-------------------------------------------------------------------------*/
    AInputDialog
      &operator=(const AInputDialog&);
};

#endif // _ADIALOG_HPP
