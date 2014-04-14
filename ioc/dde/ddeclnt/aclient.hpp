/******************************************************************************
* .FILE:         aclient.hpp                                                  *
*                                                                             *
* .DESCRIPTION:  Dynamic Data Exchange Client Program: Class Definitions      *
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
#ifndef ACLIENTWINDOW_HPP
#define ACLIENTWINDOW_HPP

#include <iframe.hpp>                             //IFrameWindow
#include <icmdhdr.hpp>                            //ICommandHandler
#include <iddetsrv.hpp>                           //IDDEServer Classes
#include <iddeccnv.hpp>
#include <ireslib.hpp>

class IMenuBar;
class ISplitCanvas;
class IStaticText;
class IInfoArea;
class AConversation;

/**********************************************************/
/* Define our Customer DDE Client Window                  */
/**********************************************************/
class AClientWindow : public IFrameWindow, public ICommandHandler
{
public:
  AClientWindow     (unsigned long windowId);     //Constructor
  ~AClientWindow    ();                           //Destructor
  virtual bool   log(const char *);            //Log message to window
  virtual bool   log(IResourceId id);          //Log message to window
  virtual bool   setWorkItem(char * message);  //Set new work item
  virtual IString   workItem();                   //Get work item
  virtual bool   workItemDone();               //Set work item done
  virtual bool   updateStatus();               //Update status line
  virtual bool   updateTodo(char * newCount);  //Update todo count
  virtual bool   updateWork(char * newCount);  //Update work count
  virtual bool   updateDone(char * newCount);  //Update done count

protected:
  virtual bool   command(ICommandEvent& cmdevt);

private:
  IMenuBar          menuBar;                      //Menu Bar
  ISplitCanvas      statusLine;                   //Status line
  IStaticText       todoStatus;                   //Todo list status
  IStaticText       workStatus;                   //Work list status
  IStaticText       doneStatus;                   //Done list status
  ISplitCanvas      cArea;                        //Client area canvas
  IStaticText       workWindow;                   //Work static window
  IMultiLineEdit    mle;                          //MLE to log status
  IInfoArea         infoArea;                     //Information Area
  AConversation *   conversation;
  long              todoCount;
  long              workCount;
  long              doneCount;
  IResourceLibrary  resLib;
};

class AConversation : public IDDEClientConversation
{
public:

  AConversation(AClientWindow* frameWin);

  void              conversationEnded(IDDEClientEndEvent& conv);
  void              acknowledged(IDDEClientAcknowledgeEvent& event);
  bool           data(IDDEDataEvent& event);
  AClientWindow *   mainWindow() { return clientWindow; }

private:
  AClientWindow *   clientWindow;
  IResourceLibrary  resLib;
};  // end AConversation
#endif
