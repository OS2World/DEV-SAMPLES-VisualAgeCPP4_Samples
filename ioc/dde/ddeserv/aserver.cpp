/******************************************************************************
* .FILE:         aserver.cpp                                                  *
*                                                                             *
* .DESCRIPTION:  Dynamic Data Exchange Server Program: Class Implementation   *
*                                                                             *
* .CLASSES:      AServerWindow                                                *
*                ATopicServer                                                 *
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
#include <imle.hpp>
#include <istattxt.hpp>
#include <iinfoa.hpp>
#include <ilistbox.hpp>
#include <isplitcv.hpp>
#include <iapp.hpp>
#include <ifont.hpp>
#include <imsgbox.hpp>
#include <istring.hpp>
#include <iddeevt.hpp>
#include <icoordsy.hpp>
#include "aserver.h"
#include "aserver.hpp"

//*************************************************************************
// main  - Application entry point
//*************************************************************************
int main()
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::kOriginLowerLeft );

  AServerWindow serverWindow(WND_SERVER);//Create main window

  IApplication::current().run();        //Start event handling

  return 0;
} /* end main */

//**************************************************************************
// AServerWindow :: AServerWindow - Constructor for our main window
//**************************************************************************
AServerWindow :: AServerWindow(unsigned long windowId)
  : IFrameWindow (windowId),            //Call IFrameWindow constructor
    statusLine(WND_STATUS, this, this), //Create status line
    todoStatus(WND_TODOSTA, &statusLine,//Create todo status line
      &statusLine),
    workStatus(WND_WORKSTA, &statusLine,//Create work status line
      &statusLine),
    doneStatus(WND_DONESTA, &statusLine,//Create done status line
      &statusLine),
    cArea(WND_CAREA, this, this),       //Create Client Area
    dArea(WND_DAREA, &cArea, this),     //Create Data Area Cannvas
    todoList(WND_TODO, &dArea, this,    //Create todo list
      IRectangle(),                     //
      (IListBox::defaultStyle()         //  Use default style with
      | IListBox::noAdjustPosition)),   //  Canvas controling size
    workList(WND_WORK, &dArea, this,    //Create working list
      IRectangle(),                     //
      (IListBox::defaultStyle()         //
      | IListBox::noAdjustPosition)),   //  Allow the Canvas to control size
    doneList(WND_DONE, &dArea, this,    //Create done list
      IRectangle(),                     //
      (IListBox::defaultStyle()         //  Use default style with
      | IListBox::noAdjustPosition)),   //  Canvas controling size
    mle(WND_MLE, &cArea, &cArea),       //Create MLE to display DDE activities
    infoArea(this),                     //Create Information Area
    resLib(),                           //Resource library
    server(resLib.loadString( MI_APP ), //Create DDE Server (application name,
       resLib.loadString( MI_TOPIC ),   //  topic name, window)
       this )
{
  hot=0;                                //Hot link not active
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

  sizeTo(ISize(600,400));               //Set the size of main window
  moreTodo();                           //Initialize the todo list
  updateStatus();                       //Update status line
  setFocus();                           //Set Focus to main window
  show();
} /* end AServerWindow :: AServerWindow(...) */

//**************************************************************************
// AServerWindow :: log(..)
//**************************************************************************
bool AServerWindow::log(IResourceId resId)
{
  mle.addLineAsLast( resLib.loadString( resId )); //Add to mle message log

  return true;
} /* end AServerWindow :: log(..) */

//**************************************************************************
// AServerWindow :: log(..)
//**************************************************************************
bool AServerWindow::log(char * message)
{
  mle.addLineAsLast( message );                  //Add to mle message log

  return true;
} /* end AServerWindow :: log(..) */

//**************************************************************************
// AServerWindow :: addDone(..)
//**************************************************************************
bool AServerWindow::addDone(char * newDone)
{
  doneList.addAsLast(newDone);          //Add new done item
  try
  {
    unsigned long index=                //Locate this item in the work list
      workList.locateText(newDone);
    workList.remove(index);             //Remove from work list
  }
  catch (IException& exc)               //Catch Error
  {                                     //
    IMessageBox mbox(this);             //Create Message Box
    mbox.show(exc);                     //
    return false;                       //Return error
  }                                     //
  updateStatus();                       //Update status
  if (hot)                              //Is hot link active?
  {
    log( MI_HOTLINKUPDATE_HOTWORK );
    server.hotLinkUpdate( resLib.loadString( MI_HOTWORK ));  //Update work hot link
    log( MI_HOTLINKUPDATE_HOTDONE );
    server.hotLinkUpdate( resLib.loadString( MI_HOTDONE ));  //Update done hot link
  } /* endif */
  return true;
} /* end AServerWindow :: addDone(..) */

//**************************************************************************
// AServerWindow :: addTodo(..)
//**************************************************************************
bool AServerWindow::addTodo( IResourceId resId )
{
  todoList.addAsLast( resId );          //Add new todo
  return true;
} /* end AServerWindow :: addTodo(..) */

//**************************************************************************
// AServerWindow :: moreTodo()
//**************************************************************************
bool AServerWindow::moreTodo()       //Add more items to the todo list
{
  addTodo( MI_BUY_GIFTS );              //Add item to todo list
  addTodo( MI_PAY_PHONE );              //
  addTodo( MI_PAY_TAXES );              //
  addTodo( MI_PAPERS );                 //
  addTodo( MI_TRASH );                  //
  addTodo( MI_WASH_CAR );               //
  addTodo( MI_WASH_DISH );              //
  todoList.select(0);                   //Set the first item selected
  return true;                          //
} /* end AServerWindow :: moreTodo() */

//**************************************************************************
// AServerWindow :: addHot()
//**************************************************************************
bool AServerWindow::addHot()
{
  hot=hot+1;                            //Set new value
  if (hot == 1)
  {
    infoArea.setDefaultText(STR_HOTYES);//Set information area text from RC
  } /* endif */
  return true;                          //
} /* end AServerWindow :: addHot() */

//**************************************************************************
// AServerWindow :: removeHot()
//**************************************************************************
bool AServerWindow::removeHot()
{
  hot=hot-1;                            //Set new value
  if (hot == 0)
  {
    infoArea.setDefaultText(STR_HOTNO);//Set information area text from RC
  } /* endif */
  return true;                          //
} /* end AServerWindow :: removeHot(..) */

//**************************************************************************
// AServerWindow :: nextTodo()
//**************************************************************************
IString AServerWindow::nextTodo()
{
  IListBox::Cursor lbCursor(todoList);  //List Box Cursor
  lbCursor.setToFirst();                //Set to first item selected
  IString temp(                         //Set temp to text of 1st item selected
    todoList.elementAt(lbCursor));      //
  workList.addAsLast(temp);             //Add to work list
  todoList.removeAt(lbCursor);          //Remove this item
  if (todoList.count() == 0)            //If zero count then add more items
    moreTodo();                         //  since the work is never done
  todoList.select(0);                   //Set the selection to first
  if (hot)                              //Is hot link active?
  {
    log( MI_HOTLINKUPDATE_HOTTODO );
    server.hotLinkUpdate(resLib.loadString( MI_HOTTODO )); //Update todo hot link
    log( MI_HOTLINKUPDATE_HOTWORK );
    server.hotLinkUpdate(resLib.loadString( MI_HOTWORK )); //Update work hot link
  } /* endif */
  updateStatus();                       //Update the status line
  return temp;                          //Return String
} /* end AServerWindow :: nextTodo() */

//**************************************************************************
// AServerWindow :: todo()
//**************************************************************************
IString AServerWindow::todo()
{
  IString temp(todoList.count());       //Get count
  return temp;                          //Return String
} /* end AServerWindow :: todo() */

//**************************************************************************
// AServerWindow :: work()
//**************************************************************************
IString AServerWindow::work()
{
  IString temp(workList.count());       //Get count
  return temp;                          //Return String
} /* end AServerWindow :: work() */

//**************************************************************************
// AServerWindow :: done()
//**************************************************************************
IString AServerWindow::done()
{
  IString temp(doneList.count());       //Get count
  return temp;                          //Return String
} /* end AServerWindow :: done() */

//**************************************************************************
// AServerWindow :: updateStatus()
//**************************************************************************
bool AServerWindow::updateStatus()
{
  todoStatus.setText(                   //Set the status to todo count
    IString(resLib.loadString( MI_TODO_COUNT ))+
    IString(todoList.count()));
  workStatus.setText(                   //Set the status to work count
    IString(resLib.loadString( MI_WORK_COUNT ))+
    IString(workList.count()));
  doneStatus.setText(                   //Set the status to done count
    IString(resLib.loadString( MI_DONE_COUNT ))+
    IString(doneList.count()));

  return true;
} /* end AServerWindow :: updateStatus() */


//**************************************************************************
// ATopicServer :: ATopicServer - Constructor for our DDE server class
//**************************************************************************
ATopicServer :: ATopicServer(           //Constructor for ATopicServer
                 const char* app,       //Application Name
                 const char* topic,     //Topic Name
                 AServerWindow* mainWin)//Windower
              : IDDETopicServer(        //Call IDDETopicServer constructor
                 app,                   //
                 topic,                 //
                 mainWin, false),       //
                 serverWindow(mainWin), //Set window
                 resLib()               //Resource library
{;} /* end ATopicServer :: ATopicServer(..) */

//**************************************************************************
// ATopicServer :: requestHotLinkData(..)
//**************************************************************************
void ATopicServer :: requestHotLinkData(IDDERequestDataEvent& event)
{
  bool rc=true;
  if(event.item()==IString(resLib.loadString( MI_HOTTODO )))  //Check the requested item
  {                                     //  the request is ok
    rc=false;
    IString todo;                       //  Define string to return
    todo=mainWindow()->todo();          //  Get todo count from window
    mainWindow()->log(                  //  Log this request with
      IString(resLib.loadString( MI_REQDATA ))+//   function member name
      event.item()+                     //    event item (todo)
      IString(resLib.loadString( MI_RETURNING ))+ // returned to client
      todo);
    event.setData((char*)todo);         //  Set data to return to client
  }
  if(event.item()==IString(resLib.loadString( MI_HOTWORK )))  //Check the requested item
  {                                     //  the request is ok
    rc=false;
    IString work;                       //  Define string to return
    work=mainWindow()->work();          //  Get work count from window
    mainWindow()->log(                  //  Log this request with
      IString(resLib.loadString( MI_REQDATA ))+//   function member name
      event.item()+                     //    event item (work)
      IString(resLib.loadString( MI_RETURNING ))+ // returned to client
      work);                            //
    event.setData((char*)work);         //  Set data to return to client
  }
  if(event.item()==IString(resLib.loadString( MI_HOTDONE )))  //Check the requested item
  {                                     //  the request is ok
    rc=false;
    IString done;                       //  Define string to return
    done=mainWindow()->done();          //  Get done count from window
    mainWindow()->log(                  //  Log this request with
      IString(resLib.loadString( MI_REQDATA ))+//   function member name
      event.item()+                     //    event item (done)
      IString(resLib.loadString( MI_RETURNING ))+ // returned to client
      done);                            //
    event.setData((char*)done);         //  Set data to return to client
  }
  if (rc)                               //Request does not match
  {                                     //
    mainWindow()->log(
      IString(resLib.loadString( MI_REQDATA2 ))+//   function member name
      IString(resLib.loadString( MI_UNABLE_PROVIDE )) +
      event.item());
  }
} /* end ATopicServer :: requestHotLinkData(..) */

//**************************************************************************
// ATopicServer :: beginHotLink(..)
//**************************************************************************
bool ATopicServer :: beginHotLink(unsigned long conversationId,
                          IDDEServerHotLinkEvent& event)
{
  bool rc=false;                     //Define return code
  if(event.item()==IString(resLib.loadString(MI_HOTTODO)))  //Check the requested item
  {                                     //  the request is ok
    rc=true;                            //
    mainWindow()->log(                  //  Log this request with
      IString(resLib.loadString(MI_BEGIN_HOTLINK))+ // function member name
      event.item()+                     //    event item
      IString(resLib.loadString(MI_FROM))+
      IString(conversationId));         //    conversation ID
  }
  if(event.item()==IString(resLib.loadString(MI_HOTWORK)))  //Check the requested item
  {                                     //  the request is ok
    mainWindow()->log(                  //  Log this request with
      IString(resLib.loadString(MI_BEGIN_HOTLINK))+ // function member name
      event.item()+                     //    event item
      IString(resLib.loadString(MI_FROM))+
      IString(conversationId));         //    conversation ID
    rc=true;                            //
  }
  if(event.item()==IString(resLib.loadString(MI_HOTDONE)))  //Check the requested item
  {                                     //  the request is ok
    mainWindow()->log(                  //  Log this request with
      IString(resLib.loadString(MI_BEGIN_HOTLINK))+ // function member name
      event.item()+                     //    event item
      IString(resLib.loadString(MI_FROM))+
      IString(conversationId));         //    conversation ID
    rc=true;                            //
  }
  if (!rc)                              //Request does not match
  {                                     //
    mainWindow()->log(
      IString(resLib.loadString( MI_BEGINDATA2 ))+ // function member name
      IString(resLib.loadString( MI_UNABLE_HANDLE ))+
      event.item());        //
  }
  else
  {
    mainWindow()->addHot();             //Set hot link active
  }
  return rc;
} /* end ATopicServer :: beginHotLink(..) */

//**************************************************************************
// ATopicServer :: hotLinkEnded(..)
//**************************************************************************
void ATopicServer :: hotLinkEnded(unsigned long conversationId,
                          IDDEEvent& event)
{
  mainWindow()->log(                  //  Log this request with
    IString(resLib.loadString( MI_END_HOTLINK ))+ // function member name
    event.item()+                     //    event item
    IString(resLib.loadString( MI_FROM ))+  //
    IString(conversationId));         //    conversation ID
  mainWindow()->removeHot();          //Set hot link inactive
  mainWindow()->removeHot();          //Set hot link inactive
  mainWindow()->removeHot();          //Set hot link inactive
} /* end ATopicServer :: beginHotLink(..) */

//**************************************************************************
// ATopicServer :: pokeData(..)
//**************************************************************************
bool ATopicServer :: pokeData(unsigned long conversationId,
                          IDDEPokeEvent& event)
{
  int rc=1;                             //Set default return code to processed
  if(event.item()==IString(resLib.loadString( MI_DONEPOKE ))) //Check the requested item
  {                                     //  the request is ok
    IString workItem=event.pokedData(); //Get poked Data
    mainWindow()->log(                  //  Log this request with
      IString(resLib.loadString( MI_POKEDATA ))+ // function member name
      event.item()+                     //    event item (nextTodo)
      IString(resLib.loadString( MI_DATA ))+workItem+ // work item from client
      IString(resLib.loadString( MI_FROM ))+  //
      IString(conversationId));         //    conversation ID
    mainWindow()->addDone(workItem);    //Add this item to the done list
  }
  else                                  //Request does not match
  {                                     //
    mainWindow()->log(
      IString(resLib.loadString( MI_POKEDATA2 ))+
      IString(resLib.loadString( MI_UNABLE_HANDLE )) +
      event.item());
    rc=0;                               //Set return code to event not processed
  }
  return rc;
} /* end ATopicServer :: pokeData(..) */

//**************************************************************************
// ATopicServer :: requestData(..)
//**************************************************************************
bool ATopicServer :: requestData(unsigned long conversationId,
                               IDDERequestDataEvent& event)
{
  int rc=false;                         //Set default return code to processed
  if(event.item()==IString(resLib.loadString( MI_NEXTTODO ))) //Check the requested item
  {                                     //  the request is ok
    rc=true;
    IString workItem;                   //  Define work item
    workItem=mainWindow()->nextTodo();  //  Get work item from todo list
    mainWindow()->log(                  //  Log this request with
      IString(resLib.loadString( MI_REQDATA3 ))+      //    member name
      event.item()+                     //    event item (nextTodo)
      IString(resLib.loadString( MI_RETURNING ))+workItem+ //    work item returned to client
      IString(resLib.loadString( MI_TO ))+                 //
      IString(conversationId));         //    conversation ID
    event.setData((char*)workItem);     //  Set data to return to client
  }
  if(event.item()==IString(resLib.loadString( MI_HOTTODO )))  //Check the requested item
  {                                     //  the request is ok
    rc=true;
    IString todo;                       //  Define string to return
    todo=mainWindow()->todo();          //  Get todo count from window
    mainWindow()->log(                  //  Log this request with
      IString(resLib.loadString( MI_REQDATA3 ))+      //    member name
      event.item()+                     //    event item (todo)
      IString(resLib.loadString( MI_RETURNING ))+ //    work item returned to client
      todo);                            //
    event.setData((char*)todo);         //  Set data to return to client
  }
  if(event.item()==IString(resLib.loadString( MI_HOTWORK )))  //Check the requested item
  {                                     //  the request is ok
    rc=true;
    IString work;                       //  Define string to return
    work=mainWindow()->work();          //  Get work count from window
    mainWindow()->log(                  //  Log this request with
      IString(resLib.loadString( MI_REQDATA3 ))+      //    member name
      event.item()+                     //    event item (work)
      IString(resLib.loadString( MI_RETURNING ))+ //    work item returned to client
      work);                            //
    event.setData((char*)work);         //  Set data to return to client
  }
  if(event.item()==IString(resLib.loadString( MI_HOTDONE )))  //Check the requested item
  {                                     //  the request is ok
    rc=true;
    IString done;                       //  Define string to return
    done=mainWindow()->done();          //  Get done count from window
    mainWindow()->log(                  //  Log this request with
      IString(resLib.loadString( MI_REQDATA3 ))+      //    member name
      event.item()+                     //    event item (done)
      IString(resLib.loadString( MI_RETURNING ))+ //    work item returned to client
      done);                            //
    event.setData((char*)done);         //  Set data to return to client
  }
  if (!rc)                              //Request does not match
  {                                     //
    mainWindow()->log(
      IString(resLib.loadString( MI_REQDATA4 ))+
      IString(resLib.loadString( MI_UNABLE_PROVIDE ))+
      event.item());
  }
  return rc;
} /* end ATopicServer :: requestData(..) */

//**************************************************************************
// ATopicServer :: acceptConversation(..)
//**************************************************************************
bool ATopicServer :: acceptConversation(unsigned long conversationId,
                                      IDDEBeginEvent& event)
{
  mainWindow()->log(                    //  Log this message with
    IString(resLib.loadString( MI_ACCEPT ))+  //member function name
    IString(conversationId));           //    conversation ID
  return true;
} /* end ATopicServer :: acceptConversation(..) */

//**************************************************************************
// ATopicServer :: conversationEnded(..)
//**************************************************************************
void ATopicServer :: conversationEnded(unsigned long conversationId,
                                   IDDEEndEvent& endEvt)
{
  if (endEvt.sourceOfEnd() == IDDEEndEvent::server)
    mainWindow()->log(                  //Log this message with
      IString(resLib.loadString( MI_END_CONV ))+//member function name
      IString(conversationId)+          //     conversation ID
      IString(resLib.loadString( MI_BY_SERVER )));     //     by the Server

  else if (endEvt.sourceOfEnd() == IDDEEndEvent::client)
    mainWindow()->log(                  //Log this message
      IString(resLib.loadString( MI_END_CONV ))+//member function name
      IString(conversationId)+          //     conversation ID
      IString(resLib.loadString( MI_BY_CLIENT )));     //     by the Client

  else
    mainWindow()->log(                  //Log this message
      IString(resLib.loadString( MI_END_CONV2 ))+//member function name
      IString(conversationId)+          //     conversation ID
      IString(resLib.loadString( MI_BY_ERROR )));   //     due to an error

} /* end ATopicServer :: conversationEnded(..) */
