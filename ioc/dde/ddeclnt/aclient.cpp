/******************************************************************************
* .FILE:         aclient.cpp                                                  *
*                                                                             *
* .DESCRIPTION:  Dynamic Data Exchange Client Program: Class Implementation   *
*                                                                             *
* .CLASSES:      AClientWindow                                                *
*                AConversation                                                *
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
#include <imenubar.hpp>                 //IMenuBar Class
#include <imle.hpp>                     //IMultiLineEdit (MLE) Class
#include <istattxt.hpp>                 //IStatic Text
#include <iapp.hpp>                     //IApplication Classes
#include <istring.hpp>                  //IString Class
#include <iddeevt.hpp>                  //IDDEEvent Classes
#include <iinfoa.hpp>                   //IInfoArea Class
#include <isplitcv.hpp>                 //ISplitCanvas Class
#include <ifont.hpp>                    //IFont Class
#include <imsgbox.hpp>                  //IMessageBox Class
#include <icolor.hpp>                   //IColor
#include <icoordsy.hpp>
#include "aclient.h"
#include "aclient.hpp"

//*************************************************************************
// main  - Application entry point
//*************************************************************************
int main(int argc,char **argv)
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::kOriginLowerLeft );

   AClientWindow clientWindow(WND_CLIENT);//Create main window

   IApplication::current().run();       //Display main window & start events

   return 0;
} /* end main */

//**************************************************************************
// AClientWindow :: AClientWindow - Constructor for our main window
//**************************************************************************
AClientWindow :: AClientWindow(unsigned long windowId)
  : IFrameWindow (windowId),            //Call IFrameWindow constructor
    menuBar(WND_CLIENT, this),
    statusLine(WND_STATUS, this, this), //Create status line
    todoStatus(WND_TODOSTA, &statusLine, //Create todo status line
      &statusLine),
    workStatus(WND_WORKSTA, &statusLine,//Create work status line
      &statusLine),
    doneStatus(WND_DONESTA, &statusLine,//Create done status line
      &statusLine),
    cArea(WND_CAREA, this, this),       //Create Client Area
    workWindow(WND_WORKW, &cArea, this),//Create work window
    mle(WND_MLE, &cArea, &cArea),       //Create MLE to display DDE activities
    infoArea(this),                     //Create Information Area
    resLib()
{
  handleEventsFor(this);                //Set self as command event handler
  conversation = 0;

  cArea.setOrientation(                 //Set the orientation
    ISplitCanvas::horizontalSplit);     //  to horizontal
  setIcon( id() );                      //Set the icon
  setClient(&cArea);                    //Set Client to cArea

  addExtension(&statusLine,             //Add Status Line above the client
    IFrameWindow::aboveClient,          //  and specify the height
    IFont(&statusLine).maxCharHeight());//  and specify height

  setExtensionSize(&infoArea,           //
         IFont(&infoArea).maxCharHeight());//and specify height
  infoArea.setDefaultText(STR_HOTNO);  //Set information area text from RC

  todoCount=0;
  workCount=0;
  doneCount=0;

  menuBar.disableItem(MI_END_CONV);     //Disable End Conversation
  menuBar.disableItem(MI_REQUEST_DATA); //Disable request data
  menuBar.disableItem(MI_POKE_DATA);    //Disable poke data
  menuBar.disableItem(MI_BEGIN_HOTLINK);//Disable begin hot link
  menuBar.disableItem(MI_END_HOTLINK);  //Disable end hot link

  workWindow.setAlignment(              //Set Alignment to Center in both
    IStaticText::centerCenter);         //  directions
  IFont tempFont("Helv", 16);           //Create Temp. Font
  workWindow.setFont(tempFont);         //Set Font for Work Item Text

  sizeTo(ISize(400,300));               //Set the size of main window
  updateStatus();                       //Update status line
  setFocus();                           //Set Focus to main window
  show();

} /* end AClientWindow :: AClientWindow(...) */

//**************************************************************************
// AClientWindow :: AClientWindow - Destructor for our main window
//**************************************************************************
AClientWindow :: ~AClientWindow()
{
  if (conversation)
  {
    try
    {
      conversation->endHotLinks();
    }
    catch (IException& exc)             //Catch Error
    {
    }
    delete conversation;
  } /* endif */
} /* end AClientWindow :: ~AClientWindow() */

//**************************************************************************
// AClientWindow :: command(..)
//**************************************************************************
bool AClientWindow::command(ICommandEvent& cmdevt)
{
  IResourceLibrary resLib;
  switch(cmdevt.commandId())
  {
    case MI_START_CONV:
    {
      conversation=new AConversation(this);
      log( MI_BEGIN_SENT );
      conversation->begin(
        resLib.loadString( MI_APP ),
        resLib.loadString( MI_TOPIC ) );
      menuBar.disableItem(MI_START_CONV);   //Disable Start Conversation
      menuBar.enableItem(MI_END_CONV);      //Enable End Conversation
      menuBar.enableItem(MI_REQUEST_DATA);  //Enable request data
      menuBar.enableItem(MI_POKE_DATA);     //Enable poke data
      menuBar.enableItem(MI_BEGIN_HOTLINK); //Enable begin hot link
      break;
    }
    case MI_END_CONV:
    {
	menuBar.enableItem(MI_START_CONV);    //Enable Start Conversation
      menuBar.disableItem(MI_END_CONV);     //Disable End Conversation
      menuBar.disableItem(MI_REQUEST_DATA); //Enable request data
      menuBar.disableItem(MI_POKE_DATA);    //Enable poke data
      if (!menuBar.isItemEnabled(MI_BEGIN_HOTLINK))
      {
        log( MI_END_HOT_SENT );
        conversation->endHotLinks();
      }
      log( MI_END_SENT );
      conversation->end();
      menuBar.disableItem(MI_BEGIN_HOTLINK); //Disable begin hot link
      menuBar.disableItem(MI_END_HOTLINK);   //Disable end hot link
      infoArea.setDefaultText(STR_HOTNO);    //Set information area text from RC
      todoStatus.setForegroundColor(         //Set todo status color
        IColor(IColor::kBlue));
      workStatus.setForegroundColor(         //Set work status color
        IColor(IColor::kBlue));
      doneStatus.setForegroundColor(         //Set done status color
        IColor(IColor::kBlue));
	delete conversation;
	conversation = 0;
      break;
    }
    case MI_REQUEST_DATA:
    {
      workItemDone();                       //Set work item done
      log( MI_REQDATA_SENT );
      try
      {
        conversation->requestData( resLib.loadString( MI_NEXTTODO ));
      }
      catch (IException& exc)           //Catch Error
      {
        IMessageBox mbox(this);         //Create Message Box
        mbox.show(exc);
        return false;                   //Return error
      }
      break;
    }
    case MI_POKE_DATA:
    {
      workItemDone();                   //Set work item done
      break;
    }
    case MI_BEGIN_HOTLINK:
    {
      log( MI_BEGIN_HOTLINK_HOTTODO_SENT );
      conversation->beginHotLink( resLib.loadString( MI_HOTTODO ) );
      log( MI_BEGIN_HOTLINK_HOTWORK_SENT );
      conversation->beginHotLink( resLib.loadString( MI_HOTWORK ) );
      log( MI_BEGIN_HOTLINK_HOTDONE_SENT );
      conversation->beginHotLink( resLib.loadString( MI_HOTDONE ) );
      menuBar.disableItem(MI_BEGIN_HOTLINK);//Disable begin hot link
      menuBar.enableItem(MI_END_HOTLINK);   //Enable end hot link
      infoArea.setDefaultText(STR_HOTYES); //Set information area text from RC
      todoStatus.setForegroundColor(        //Set todo status color
        IColor(IColor::kRed));
      workStatus.setForegroundColor(        //Set work status color
        IColor(IColor::kRed));
      doneStatus.setForegroundColor(        //Set done status color
        IColor(IColor::kRed));
      conversation->requestData( resLib.loadString( MI_HOTTODO ) );
      conversation->requestData( resLib.loadString( MI_HOTWORK ) );
      conversation->requestData( resLib.loadString( MI_HOTDONE ) );
      break;
    }
    case MI_END_HOTLINK:
    {
      log( MI_END_HOT_SENT );
      conversation->endHotLinks();
      menuBar.enableItem(MI_BEGIN_HOTLINK); //Enable begin hot link
      menuBar.disableItem(MI_END_HOTLINK);  //Disable end hot link
      infoArea.setDefaultText(STR_HOTNO);  //Set information area text from RC
      todoStatus.setForegroundColor(        //Set todo status color
        IColor(IColor::kBlue));
      workStatus.setForegroundColor(        //Set work status color
        IColor(IColor::kBlue));
      doneStatus.setForegroundColor(        //Set done status color
        IColor(IColor::kBlue));
      break;
    }
    default:
    {
      return false;
    }
  }
  return true;
} /* end AClientWindow :: command(..) */

//**************************************************************************
// AClientWindow :: log(..)
//**************************************************************************
bool AClientWindow::log( IResourceId resId )
{
  IResourceLibrary resLib;
  mle.addLineAsLast(resLib.loadString( resId ));    //Add to mle message log

  return true;
} /* end AClientWindow :: log(..) */

//**************************************************************************
// AClientWindow :: log(..)
//**************************************************************************
bool AClientWindow::log( const char * message )
{
  mle.addLineAsLast( message );                     //Add to mle message log

  return true;
} /* end AClientWindow :: log(..) */

//**************************************************************************
// AClientWindow :: workItemDone(..)
//**************************************************************************
bool AClientWindow::workItemDone()
{
  IResourceLibrary resLib;
  IString workItem(workWindow.text());
  if (workItem.size() > 1)
  {
    log( MI_POKEDATA_SENT );
    conversation->pokeData(
      resLib.loadString( MI_DONEPOKE ), (char*)workItem,
       workItem.size());
    setWorkItem("");
  } /* endif */
  return true;
} /* end AClientWindow :: workItemDone(..) */

//**************************************************************************
// AClientWindow :: setWorkItem(..)
//**************************************************************************
bool AClientWindow::setWorkItem(char * message)
{
  workWindow.setText(message);          //Update new work item
  return true;
} /* end AClientWindow :: setWorkItem(..) */

//**************************************************************************
// AClientWindow :: workItem(..)
//**************************************************************************
IString AClientWindow::workItem()
{
  return IString(workWindow.text());
} /* end AClientWindow :: workItem(..) */

//**************************************************************************
// AClientWindow :: updateStatus()
//**************************************************************************
bool AClientWindow::updateStatus()
{
  todoStatus.setText(                   //Set the status to todo count
    IString(resLib.loadString( MI_TODO_COUNT ) )+
    IString(todoCount));
  workStatus.setText(                   //Set the status to work count
    IString(resLib.loadString( MI_WORK_COUNT ) )+
    IString(workCount));
  doneStatus.setText(                   //Set the status to done count
    IString(resLib.loadString( MI_DONE_COUNT ) )+
    IString(doneCount));
  return true;
} /* end AClientWindow :: updateStatus() */

//**************************************************************************
// AClientWindow :: updateTodo(..)
//**************************************************************************
bool AClientWindow::updateTodo(char * newCount)
{
  todoStatus.setText(                   //Set the status to todo count
    IString(resLib.loadString( MI_TODO_COUNT ) )+
    IString(newCount));
  return true;
} /* end AClientWindow :: updateTodo(..) */

//**************************************************************************
// AClientWindow :: updateWork(..)
//**************************************************************************
bool AClientWindow::updateWork(char * newCount)
{
  workStatus.setText(                   //Set the status to work count
    IString(resLib.loadString( MI_WORK_COUNT ) )+
    IString(newCount));
  return true;
} /* end AClientWindow :: updateWork(..) */

//**************************************************************************
// AClientWindow :: updateDone(..)
//**************************************************************************
bool AClientWindow::updateDone(char * newCount)
{
  doneStatus.setText(                   //Set the status to done count
    IString(resLib.loadString( MI_DONE_COUNT ) )+
    IString(newCount));
  return true;
} /* end AClientWindow :: updateDone(..) */

//**************************************************************************
// AConversation :: AConversation - Constructor for our conversation
//**************************************************************************
AConversation::AConversation(AClientWindow* frameWin)
              : IDDEClientConversation(false),
                clientWindow(frameWin),
                resLib()
{
}

//**************************************************************************
// AConversation :: data(..)
//**************************************************************************
bool AConversation :: data(IDDEDataEvent& event)
{
  IString newWorkItem;
  IString newData(event.data());
  IString item(event.item());

  if (event.isDataFromHotLink())        //Is Data from hot link?
  {
    mainWindow()->log(IString(resLib.loadString( MI_DATA_HOTLINK ) )
      + item + IString("):")
      + newData
      + IString(resLib.loadString( MI_RECEIVED )));
  }
  else                                  //New work item from server
  {
    mainWindow()->log(IString(resLib.loadString( MI_DATA ))
      + item + IString("):")
      + newData
      + IString(resLib.loadString( MI_RECEIVED )));
  } /* endif */

  if (item == IString(resLib.loadString( MI_NEXTTODO )))    //Is item the Next Todo?
  {
    mainWindow()->setWorkItem(newData);
  } /* endif */
  if (item == IString(resLib.loadString( MI_HOTTODO )))     //Is item the todo counter?
  {
    mainWindow()->updateTodo(newData);
  } /* endif */
  if (item == IString(resLib.loadString( MI_HOTWORK )))     //Is item the work counter?
  {
    mainWindow()->updateWork(newData);
  } /* endif */
  if (item == IString(resLib.loadString( MI_HOTDONE )))     //Is item the done counter?
  {
    mainWindow()->updateDone(newData);
  } /* endif */
  return true;
} /* end AConversation :: data(..) */

void AConversation :: conversationEnded(IDDEClientEndEvent& endEvt)
/**********************************************************/
/* Do any cleanup on close of conversation by server      */
/**********************************************************/
{
   if (endEvt.sourceOfEnd() == IDDEEndEvent::server)
     mainWindow()->log(IString(resLib.loadString( MI_TOPIC_END )) +
       IString(endEvt.topic()) + IString(resLib.loadString( MI_IN_APP )) +
       IString(endEvt.application()) + IString(resLib.loadString( MI_BY_SERVER )));
   else if (endEvt.sourceOfEnd() == IDDEEndEvent::client)
     mainWindow()->log(IString(resLib.loadString( MI_TOPIC_END )) +
       IString(endEvt.topic()) + IString(resLib.loadString( MI_IN_APP )) +
       IString(endEvt.application()) + IString(resLib.loadString( MI_BY_CLIENT )));
   else
     mainWindow()->log(IString(resLib.loadString( MI_TOPIC_END )) +
       IString(endEvt.topic()) + IString(resLib.loadString( MI_IN_APP )) +
       IString(endEvt.application()) + IString(resLib.loadString( MI_BY_ERROR )));
}

/**********************************************************/
/* Handle Ack Events                                      */
/**********************************************************/
void AConversation :: acknowledged(IDDEClientAcknowledgeEvent& event)
{
   mainWindow()->log( MI_ACK_RECEIVED );
}
