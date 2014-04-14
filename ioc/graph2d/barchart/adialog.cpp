/*
-------------------------------------------------------------------------------
Copyright (c) IBM Corporation 1997.
All Rights Reserved.

Permission is granted to copy, use, modify, and merge this software into your
applications and to permit others to do any of the foregoing. You must include
this permission and copyright notice in all copies and modified versions of
this software. THIS SOFTWARE IS PROVIDED IN ITS 'AS IS' CONDITION. IBM
DISCLAIMS ANY LIABILITY OF ANY KIND FOR DAMAGES WHATSOEVER RESULTING
FROM THE USE OF THIS SOFTWARE.
-------------------------------------------------------------------------------
*/

/******************************************************************************
* .FILE:         adialog.cpp                                                  *
*                                                                             *
* .DESCRIPTION:  BarChart Sample Program:  Class Implementation               *
*                                                                             *
* .CLASSES:      AInputDialog                                                 *
*                AInputDialogCommandHandler                                   *
*                                                                             *
* .NOTE: WE RECOMMEND USING A FIXED SPACE FONT TO LOOK AT THE SOURCE          *
*                                                                             *
******************************************************************************/

#include "adialog.h"
#include "adialog.hpp"

#include <ibase.hpp>
#include <istring.hpp>
#include <ireslib.hpp>


/**************************************************************************
* Function:  AInputDialog :: AInputDialog()
*
* Parameter:
*          i) a string ID used to set the first static text
*          ii)a window pointer
*
* Purpose: constructor for AInputDialog
**************************************************************************/
AInputDialog :: AInputDialog( unsigned long  firstStrID,
                                                                                                         IWindow * ownerWnd)
             : IFrameWindow(IResourceId(WND_TEXTDIALOG)
                  ,IWindow::desktopWindow()
                  ,ownerWnd
                  ,IRectangle(450, 300, 770, 525)
                  ,IWindow::synchPaint
                    |IWindow::clipSiblings
                    |IWindow::saveBits
                    |dialogBackground
                    |dialogBorder
                    |systemMenu
                    |titleBar)
               ,clientCanvas(WND_MCCANVAS,this,this)
               ,buttons(WND_STCANVAS, &clientCanvas, &clientCanvas)
                ,firstText(DID_FIRSTSTATIC,&clientCanvas,&clientCanvas)
               ,firstField( DID_FIRSTENTRY,&clientCanvas,&clientCanvas)
                                                         ,secondText(DID_SECONDSTATIC,&clientCanvas,&clientCanvas)
                                                         ,secondField( DID_SECONDENTRY,&clientCanvas,&clientCanvas)
               ,pushButton1( DID_OK,&buttons,&buttons)
               ,pushButton2(DID_CANCEL,&buttons,&buttons)
               ,dialogCommandHandler(this)
{

        firstField.disableAutoScroll().enableMargin().enableTabStop();

  IResourceLibrary reslib ;
        IString str1 =  reslib.loadString(firstStrID);
  firstText.setText(str1);

  pushButton1.enableDefault().setText(IResourceId(DID_OK)).enableTabStop();
  pushButton2.setText(IResourceId(DID_CANCEL));
  buttons.setPackType(ISetCanvas::expanded).setMargin(ISize());

/*------------------------------------------------------------------------|
|  Position the dialog controls in the multicell canvas.                  |
-------------------------------------------------------------------------*/
  clientCanvas.addToCell(&firstText , 2, 3);
  clientCanvas.addToCell(&firstField, 2, 5);
  clientCanvas.addToCell(&buttons,   2,9);

/*------------------------------------------------------------------------|
|  Set the multicell canvas as the AInputDialog client window.             |
|  Have the command handler start handling events for the frame window.   |
|  Set the focus to the entry fields.                                      |
|------------------------------------------------------------------------*/
  setClient( &clientCanvas );
  dialogCommandHandler.handleEventsFor(this);
  firstField.setFocus();

} /* end AInputDialog :: AInputDialog(...) */




/**************************************************************************
* Function:  AInputDialog :: AInputDialog()
*
* Parameter:
*          i) a string ID used to set the first static text
*          ii) another string ID used to set the first static text
*          ii)a window pointer
*
* Purpose: constructor for AInputDialog
**************************************************************************/

AInputDialog :: AInputDialog( unsigned long  firstStrID,
                             unsigned long secondStrID,
                                                                                                          IWindow * ownerWnd)
             : IFrameWindow(IResourceId(WND_TEXTDIALOG)
                  ,IWindow::desktopWindow()
                  ,ownerWnd
                  ,IRectangle(450, 300, 770, 570)
                  ,IWindow::synchPaint
                    |IWindow::clipSiblings
                    |IWindow::saveBits
                    |dialogBackground
                    |dialogBorder
                    |systemMenu
                    |titleBar)
               ,clientCanvas(WND_MCCANVAS,this,this)
               ,buttons(WND_STCANVAS, &clientCanvas, &clientCanvas)
               ,firstText(DID_FIRSTSTATIC,&clientCanvas,&clientCanvas)
               ,firstField( DID_FIRSTENTRY,&clientCanvas,&clientCanvas)
                                                         ,secondText(DID_SECONDSTATIC,&clientCanvas,&clientCanvas)
                                                         ,secondField( DID_SECONDENTRY,&clientCanvas,&clientCanvas)
               ,pushButton1( DID_OK,&buttons,&buttons)
               ,pushButton2(DID_CANCEL,&buttons,&buttons)
               ,dialogCommandHandler(this)
{

        firstField.disableAutoScroll().enableMargin().enableTabStop();

  IResourceLibrary reslib ;
        IString str1 =  reslib.loadString(firstStrID);
  firstText.setText(str1);

  secondField.disableAutoScroll().enableMargin().enableTabStop();

        IString str2 =  reslib.loadString(secondStrID);
  secondText.setText(str2);


  pushButton1.enableDefault().setText(IResourceId(DID_OK)).enableTabStop();
  pushButton2.setText(IResourceId(DID_CANCEL));
  buttons.setPackType(ISetCanvas::expanded).setMargin(ISize());

/*------------------------------------------------------------------------|
|  Position the dialog controls in the multicell canvas.                  |
-------------------------------------------------------------------------*/
  clientCanvas.addToCell(&firstText , 2, 3);
  clientCanvas.addToCell(&firstField, 2, 5);
  clientCanvas.addToCell(&secondText , 2, 8);
  clientCanvas.addToCell(&secondField, 2, 10);
  clientCanvas.addToCell(&buttons, 2,12);

/*------------------------------------------------------------------------|
|  Set the multicell canvas as the AInputDialog client window.             |
|  Have the command handler start handling events for the frame window.   |
|  Set the focus to the entry fields.                                      |
|------------------------------------------------------------------------*/
  setClient( &clientCanvas );
  dialogCommandHandler.handleEventsFor(this);

  firstField.setFocus();
}




/**************************************************************************
* Function:  AInputDialog ::~AInputDialog()
*
* Purpose: destructor for AInputDialog
*
**************************************************************************/
AInputDialog :: ~AInputDialog()
{
  dialogCommandHandler.stopHandlingEventsFor(this);
}



/**************************************************************************
* Function:  AInputDialog ::getValueFromFirstEntry()
*
* Parameter:  None
*
* Return Value: a string that user inputs in the first entry field
*
* Purpose: get a text from the first entry field
*
**************************************************************************/
IString
  AInputDialog::getValueFromFirstEntry()
{
  return firstField.text();
}




/**************************************************************************
* Function:  AInputDialog ::getValueFromSecondEntry()
*
* Parameter:  None
*
* Return Value: a string that user inputs in the second entry field
*
* Purpose: get a text from the second entry field
*
**************************************************************************/
IString
  AInputDialog::getValueFromSecondEntry()
{
  return secondField.text();
}




/**************************************************************************
* Function:  AInputDialogCommandHandler::AInputDialogCommandHandler()
*
* Parameter:  a pointer to the AInputDialog that events are handled for.
*
* Purpose: constructor for AInputDialogCommandHandler which constructs the
*           command handler for the dialog box.
*                                                                         *
**************************************************************************/

AInputDialogCommandHandler :: AInputDialogCommandHandler(AInputDialog *dialogFrame)
  :frame(dialogFrame)
{
}



/**************************************************************************
* Function:  AInputDialogCommandHandler::command()
*
* Parameter:  command events that need to be handled
*
* Purpose: Handle menu commands for dialog window
*                                                                         *
**************************************************************************/

bool AInputDialogCommandHandler :: command(ICommandEvent & cmdEvent)
{
  bool eventProcessed(true);         //Assume event will be processed

/*------------------------------------------------------------------------|
|  Depending on the command event ID,                                     |
|    optionally update the Hello World text;                              |
|    then dismiss the text dialog passing the event ID as the result.     |
|------------------------------------------------------------------------*/
  switch (cmdEvent.commandId()) {
    case DID_OK:
      frame->dismiss(DID_OK);
      break;
    case DID_CANCEL:
      frame->dismiss(DID_CANCEL);
      break;
    default:
/*------------------------------------------------------------------------|
| The event was not processed                                             |
-------------------------------------------------------------------------*/
      eventProcessed=false;
  } /* end switch */

  return(eventProcessed);
} /* end AInputDialogCommandHandler :: command(...) */

