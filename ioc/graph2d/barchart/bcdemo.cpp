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
* .FILE:         bcdemo.cpp                                                   *
*                                                                             *
* .DESCRIPTION:  BarChart Sample Program:  Class Implementation and main      *
*                program                                                      *
*                                                                             *
* .CLASSES:      MainWindow                                                   *
*                                                                             *
* .NOTE: WE RECOMMEND USING A FIXED SPACE FONT TO LOOK AT THE SOURCE          *
*                                                                             *
******************************************************************************/

#include "bcdemo.h"
#include "bcdemo.hpp"
#include  "adialog.hpp"
#include  "adialog.h"
#include <iostream.h>
#include <imsgbox.hpp>

class AInputDialog;


/*************************************************************************
* Function: MainWindow::MainWindow()
*
* Parameter: a  window ID
*
* Purpose: constructor for class MainWindow
*
**************************************************************************/
MainWindow::MainWindow(unsigned long windowId)
  : IFrameWindow (                      //Call IFrameWindow constructor
    IFrameWindow::defaultStyle()        //  Use default plus
    | IFrameWindow::animated,           //  set to show with "animation"
    windowId),                          //  Main Window ID
    drawingArea( WND_DRAW, this, this ),
    menuBar( WND_MAIN, this),
      fBarChart(0)  //  NULL pointer
{
   // create a barchart
    fBarChart = new BarChart() ;

  // start up the event handlers
  ICommandHandler::handleEventsFor(this);

#ifdef IC_WIN
        IPaintHandler::handleEventsFor(this);
#else
        IPaintHandler::handleEventsFor(&drawingArea);
#endif

  setClient(&drawingArea);
  setFocus();
  show();
}

/****************************************************************************
 * Function: MainWindow::~MainWindow
 *
 * Purpose: destructor for MainWindow
 *
 ****************************************************************************/

MainWindow::~MainWindow()
{
  // shut down the event handlers
  ICommandHandler::stopHandlingEventsFor(this);
  IPaintHandler::stopHandlingEventsFor(this);

   delete fBarChart ;
}

/***************************************************************************
 * Function: MainWindow::command
 *
 * Parameters:
 *   event: contains the command id of the event to be handled
 *
 * Return value: returns true when the event is processed
 *
 * Purpose: handles selections from the menu bar, tool bar, and pop-up menus
 *
 *****************************************************************************/

bool MainWindow::command( ICommandEvent& event )

{
  bool fProcessed = false;

  switch (event.commandId()) {

     case ID_SETBCHARTPOSITION: {
         // create a dialog for input
         AInputDialog myDialog(STR_ENTERXPOS, STR_ENTERYPOS, this);
         myDialog.showModally();

         if (myDialog.result() == DID_OK) {
           // get the input as a string
            IString  x = myDialog.getValueFromFirstEntry();
            IString  y = myDialog.getValueFromSecondEntry();

            //convert string  into mumerica data and use it to set bar chart position
           fBarChart->SetBChartPosition(IGPoint2D(x.asDouble(), y.asDouble()));
         }
         break;
      }

      case ID_SETBCHARTHEIGHT:{
         // create a dialog for input
      AInputDialog myDialog(STR_ENTERHEIGHT,this);
         myDialog.showModally();

         if (myDialog.result() == DID_OK) {
           // get the input as a string
            IString  dataValue = myDialog.getValueFromFirstEntry();

            // convert string  into mumerica data and use it to set bar chart height
           fBarChart->SetBChartHeight(dataValue.asDouble());
         }
         break;
      }

      case ID_SETBCHARTWIDTH:{
         // create a dialog for input
      AInputDialog myDialog(STR_ENTERWIDTH,this);
         myDialog.showModally();

         if (myDialog.result() == DID_OK) {
           // get the input as a string
            IString  dataValue = myDialog.getValueFromFirstEntry();

            // convert string  into mumerica data and use it to set bar chart width
           fBarChart->SetBChartWidth(dataValue.asDouble());
         }
         break;
      }

      case ID_REPLACEATPOSITION:{
         // create a dialog for input
         AInputDialog myDialog(STR_ENTERPOS, STR_ENTERDATA, this);
         myDialog.showModally();

         if (myDialog.result() == DID_OK) {
           // get the input as a string
            IString  posValue = myDialog.getValueFromFirstEntry();
            IString  dataValue = myDialog.getValueFromSecondEntry();

           if ( !fBarChart->ReplaceAtPosition(posValue.asDouble(), dataValue.asDouble()))
              displayMsg(STR_POSINVALID); //display error message
         }
         break;
      }

      case ID_ADDFIRST:{
         // create a dialog for input
       AInputDialog myDialog(STR_ENTERDATA,this);
         myDialog.showModally();

         if (myDialog.result() == DID_OK) {
           // get the input as a string
            IString  dataValue = myDialog.getValueFromFirstEntry();

           if ( !fBarChart->AddAsFirst(dataValue.asDouble()))
              displayMsg(STR_ISFULL);
         }
         break;
    }

      case ID_ADDLAST:{
         // create a dialog for input
       AInputDialog myDialog(STR_ENTERDATA,this);
         myDialog.showModally();

         if (myDialog.result() == DID_OK) {
           // get the input as a string
            IString  dataValue = myDialog.getValueFromFirstEntry();

           if ( !fBarChart->AddAsLast(dataValue.asDouble()))
              displayMsg(STR_ISFULL);
         }
         break;
      }

      case ID_ADDATPOSITION :{
         // create a dialog for input
         AInputDialog myDialog(STR_ENTERPOS, STR_ENTERDATA, this);
         myDialog.showModally();

         if (myDialog.result() == DID_OK) {
           // get the input as a string
            IString  posValue = myDialog.getValueFromFirstEntry();
            IString  dataValue = myDialog.getValueFromSecondEntry();

           if (!fBarChart->AddAtPosition(posValue.asDouble(), dataValue.asDouble()))
              displayMsg(STR_POSINVALID);
         }
         break;
      }

      case ID_REMOVEFIRST:{
        if (! fBarChart->RemoveAsFirst())
           displayMsg(STR_ISEMPTY);
         break;
      }

      case ID_REMOVELAST:{
        if (! fBarChart->RemoveAsLast())
           displayMsg(STR_ISEMPTY);
         break;
      }

      case ID_REMOVEATPOSITION : {
         // create a dialog for input
      AInputDialog myDialog(STR_ENTERPOS,this);
         myDialog.showModally();

         if (myDialog.result() == DID_OK) {
           // get the input as a string
            IString  pos = myDialog.getValueFromFirstEntry();

           if ( ! fBarChart->RemoveAtPosition(pos.asDouble()))
              displayMsg(STR_POSINVALID);
         }
         break;
      }

      case ID_GETBCHARTPOSITION: {
         IGPoint2D pos = fBarChart->GetBChartPosition();
          displayMsg(STR_POSITION, pos.fX, pos.fY);
         break;
      }

      case ID_GETBCHARTHEIGHT:{
        GCoordinate height = fBarChart->GetBChartHeight() ;
         displayMsg(STR_HEIGHT, height);
         break;
      }

      case ID_GETBCHARTWIDTH:{
        GCoordinate width = fBarChart->GetBChartWidth() ;
         displayMsg (STR_WIDTH, width);
         break;
      }

      case ID_SHOWATPOSITION:{
         // create a dialog for input
         AInputDialog myDialog(STR_ENTERPOS,  this);
         myDialog.showModally();

         if (myDialog.result() == DID_OK) {
           // get the input as a string
            IString  posValue = myDialog.getValueFromFirstEntry();

           if (fBarChart->PosCheck(posValue.asDouble()))
              displayMsg(STR_BARDATA, fBarChart->DataAtPosition(posValue.asDouble()));
           else
              displayMsg(STR_POSINVALID);
         }
         break;
      }
  }//END OF switch

  fProcessed = true;
  refresh();// update the display

  return fProcessed;

}


/**********************************************************************************
 * Function: MainWindow::paintWindow()
 *
 * Parameters:
 *   event: identifies the type of paint event to be processed
 *
 * Return value: returns true when the event is processed
 *
 * Purpose: handles the rendering of graphics to the screen, and handles
 *          repaint updates
 **********************************************************************************/

bool MainWindow::paintWindow( IPaintEvent& event )
{

  bool fProcessed = false;

// clear the drawing area

#ifdef IC_WIN
        drawingArea.refresh(IWindow::paintAllImmediate);
#else
        event.clearBackground( IColor::white );
#endif
                                                     
// create a  grafPort for display
  IRootGrafPort *myDisplayPort;
  IManagedPresSpaceHandle  presSPace(&drawingArea);
  myDisplayPort = new IRootGrafPort(presSPace);
// draw the barchart
  fBarChart->Draw(myDisplayPort);
  delete myDisplayPort; 
  return true;
}



/*************************************************************************
* Function: MainWindow::demoIntialize()
*
* Purpose: initialize some data for the barchart object for  demo
*
**************************************************************************/
void MainWindow::demoIntialize()
{
  // four numerical data are added to the barchart
   fBarChart->AddAsFirst(21);
   fBarChart->AddAtPosition(2, -15);
   fBarChart->AddAsLast(30);
   fBarChart->AddAsLast(7);
}




/*************************************************************************
* Function: MainWindow::displayMsg()
*
* Parameter:  a string ID  representing string message to be displayed
*
* Purpose:  create a message box and display a message
*
**************************************************************************/
void MainWindow::displayMsg(unsigned long strID )
{
 IMessageBox msg(this);

 msg.setTitle( " Message Box ");

 // load the string that strID represents
 IResourceLibrary reslib ;
 IString str =  reslib.loadString(strID);

 // display the message in the message box
 /*msg.show(str, IMessageBox::okButton |

                      IMessageBox::defButton1 |
                      IMessageBox::warningIcon |
                      IMessageBox::moveable);


*/
 // display the message in the message box
 msg.show(str, IMessageBox::okButton | IMessageBox::defButton1 |    IMessageBox::warningIcon   );

}

/*************************************************************************
* Function: MainWindow::displayMsg()
*
* Parameter:
*            i)  a string ID  representing string message to be displayed
*            ii) data to be displayed
*
* Purpose:  create a message box and display a message
*
**************************************************************************/
void MainWindow::displayMsg(unsigned long strID, GCoordinate data )
{
 IMessageBox msg(this);
 msg.setTitle( " Message Box ");

 // load the string that strID represents
 IResourceLibrary reslib ;
 IString str1 =  reslib.loadString(strID);

 //convert numerica data into string
 IString str2(data) ;

 // concatenate two strings to be one single string for display
 strncat(str1, str2, 6);

 // display the message in the message box
 msg.show(str1, IMessageBox::okButton |
               IMessageBox::defButton1 |
                      IMessageBox::informationIcon |
                      IMessageBox::moveable);
}


/*************************************************************************
* Function: MainWindow::displayMsg()
*
* Parameter:
*            i)  a string ID  representing string message to be displayed
*            ii) first data to be displayed
*            iii)second data to be displayed
*
* Purpose:  create a message box and display a message
*
**************************************************************************/

void MainWindow::displayMsg(unsigned long strID, GCoordinate data2, GCoordinate data3)
{
 IMessageBox msg(this);
 msg.setTitle( " Message Box ");

 // load the string that strID represents
 IResourceLibrary reslib ;
 IString str1 =  reslib.loadString(strID);

 //convert numerica data into string
 IString str2(data2) ;

 IString str3(data3) ;

 // concatenate several strings to be one single string for display
 strncat(str1, str2, 3);
 strncat(str1, " , ", 3);
 strncat(str1, str3, 3);

 // display the message in the message box
 msg.show(str1, IMessageBox::okButton |
               IMessageBox::defButton1 |
                      IMessageBox::informationIcon |
                      IMessageBox::moveable);
}



/*************************************************************************
* Function:  main()
*
* Purpose:   program entry point
 *************************************************************************/

void main()
{
  //Create a main window on the desktop
  MainWindow  mainWindow(WND_MAIN);

  //initialize some dat  just for the demo of a bar chart
   mainWindow.demoIntialize() ;

  //Get the current application and run it
   IApplication::current().run();

} /* end main */



