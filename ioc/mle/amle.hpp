/******************************************************************************
* .FILE:         amle.hpp                                                     *
*                                                                             *
* .DESCRIPTION:  Multiline Edit Sample Program:        Class Definition       *
*                                                                             *
* .CLASSES:      AEditorWindow                                                *
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
#ifndef AEDITORWINDOW_HPP
#define AEDITORWINDOW_HPP

#include <iframe.hpp>
#include <icmdhdr.hpp>
#include <imenuhdr.hpp>         // IMenuHandler
#include <imenubar.hpp>
#include <imle.hpp>
#include <ithread.hpp>
#include <iinfoa.hpp>
#include <ititle.hpp>
#include <istring.hpp>
#include "auwmhdr.hpp"

/******************************************************************************/
/* Class:   AEditorWindow                                                     */
/*                                                                            */
/* Purpose: Main window for mle sample application                            */
/*          It is derived from the classes IFrameWindow, ICommandHandler      */
/*          IMenuHandler & AUserMessageHandler                                */
/******************************************************************************/
class AEditorWindow : public IFrameWindow
                    , public ICommandHandler
                    , public IMenuHandler
                    , public AUserMessageHandler
{
  public:
    AEditorWindow(unsigned long windowId);
    AEditorWindow
     &openFile(bool fUseThread),
     &saveFile(),
     &saveAsFile(),
     &openFont(),
     &loadOnThread(unsigned long eventId),
     &load();

  protected:
    bool command(ICommandEvent& cmdEvent);
    bool menuShowing( IMenuEvent& mnEvt
                       , ISubmenu&   smnAboutToShow);
    bool userMessage( IEvent& evt );
    bool setFileMenuitemsState( bool f );
    AEditorWindow &displayLoadFailedMsg();
    bool loadMLE();

  private:
    IMultiLineEdit mle;
    ITitle         titleBar;
    IMenuBar       menuBar;
    IInfoArea      infoArea;
    IString        filename;
    IThreadId      primaryThreadId;
};

/******************************************************************************/
/* Class   : AThreadFn                                                        */
/*                                                                            */
/* Purpose : this class can be used to execute the member function            */
/*           AEditorWindow::loadOnThread(unsigned long)                       */
/*           on a separate thread.                                            */
/*           It is a subclass of IThreadFn                                    */
/*                                                                            */
/******************************************************************************/
class AThreadFn : public IThreadFn
{
  public:
    AThreadFn(AEditorWindow &obj, unsigned long evtId)
      : object(obj)
      , eventId(evtId)
        {;}
    void run() { object.loadOnThread(eventId); }

  private:
    AEditorWindow   &object;
    unsigned long    eventId;
};

#endif
