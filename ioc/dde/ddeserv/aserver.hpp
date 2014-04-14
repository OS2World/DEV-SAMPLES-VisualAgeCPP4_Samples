/******************************************************************************
* .FILE:         aserver.hpp                                                  *
*                                                                             *
* .DESCRIPTION:  Dynamic Data Exchange Server Program: Class Definitions      *
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
#ifndef ASERVERWINDOW_HPP
#define ASERVERWINDOW_HPP

#include <iframe.hpp>                             //IFrameWindow
#include <iddetsrv.hpp>                           //IDDEServer Classes
#include <ireslib.hpp>

class ISplitCanvas;
class IStaticText;
class IListBox;
class IMultiLineEdit;
class IInfoArea;
class AServerWindow;

class ATopicServer : public IDDETopicServer {
public:
  ATopicServer(const char* app,                   //ATopicServer Constructor
          const char* topic,
          AServerWindow* mainWin) ;

  bool           acceptConversation(           //Start conversation
                      unsigned long conversationId,
                      IDDEBeginEvent& event);
  bool           beginHotLink(
                       unsigned long conversationId,
                       IDDEServerHotLinkEvent& event);
  bool           pokeData(                     //Poke Data
                      unsigned long conversationId,
                      IDDEPokeEvent& event);
  bool           requestData(                  //Client requesting data
                      unsigned long conversationId,
                      IDDERequestDataEvent& event);
  void              requestHotLinkData(           //Client requesting hot link
                      IDDERequestDataEvent& event);
  void              hotLinkEnded(
                      unsigned long conversationId,
                      IDDEEvent& event);
  void              conversationEnded(           //End conversation
                      unsigned long conversationId,
                      IDDEEndEvent& conv);

  AServerWindow *   mainWindow() const { return serverWindow;}

private:
  AServerWindow *   serverWindow;
  IResourceLibrary  resLib;                       //Resource library
}; /* End of ATopicServer */

/**********************************************************/
/* Define our DDE Server Active conversation Window       */
/**********************************************************/
class AServerWindow : public IFrameWindow
{
public:
  AServerWindow     (unsigned long windowId);     //Constructor
  virtual bool   log(char * message);          //Log message to window
  virtual bool   log(IResourceId id);          //Log message to window
  virtual bool   addDone(char * newDone);      //Add item to done list
  virtual bool   addTodo(IResourceId id);      //Add item to todo list
  virtual bool   moreTodo();                   //Add more to todo list
  virtual bool   addHot();                     //Set hot link active flag
  virtual bool   removeHot();                  //Set hot link active flag
  virtual IString   nextTodo();                   //Get next todo
  virtual IString   todo();                       //Get todo count
  virtual IString   work();                       //Get work count
  virtual IString   done();                       //Get done count
  virtual bool   updateStatus();               //Update status line

private:
  ISplitCanvas      statusLine;                   //Status line
  IStaticText       todoStatus;                   //Todo list status
  IStaticText       workStatus;                   //Work list status
  IStaticText       doneStatus;                   //Done list status
  ISplitCanvas      cArea;                        //Client area canvas
  ISplitCanvas      dArea;                        //Data area canvas
  IListBox          todoList;                     //Todo list
  IListBox          workList;                     //Work list
  IListBox          doneList;                     //Done list
  IMultiLineEdit    mle;                          //MLE to log status
  IInfoArea         infoArea;                     //Information Area
  int               hot;                          //true=hot link active
  IResourceLibrary  resLib;                       //Resource library
  ATopicServer      server;                       //DDE Topic Server
}; /* End of AServerWindow */

#endif
