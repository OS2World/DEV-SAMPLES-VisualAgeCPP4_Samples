/******************************************************************************
* .FILE:         notify.cpp                                                   *
*                                                                             *
* .DESCRIPTION:  Notify Sample Application: Class Implementation              *
*                                                                             *
* .CLASSES:      CustomerObject                                               *
*                efObserver                                                   *
*                MenuCommandHandler                                           *
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
#include <iapp.hpp>
#include <iframe.hpp>
#include <ientryfd.hpp>
#include <isetcv.hpp>
#include <istattxt.hpp>
#include <imsgbox.hpp>
#include <ipushbut.hpp>
#include <ireslib.hpp>
#include <imenubar.hpp>
#include <icoordsy.hpp>
#include "notify.hpp"
#include "notify.h"


/*******************************************************************************
* Global Varaibles that are used by various functions                          *
*******************************************************************************/
IFrameWindow
 *frame;
IEntryField
 *ef;
IPushButton
 *pb;
CustomerObject
 *co;
IStaticText
 *display;


/*******************************************************************************
* main  - Application entry point                                              *
*******************************************************************************/
int main()
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::kOriginLowerLeft );

  IResourceLibrary
    reslib;

/*-----------------------------------------------------------------------------|
| Create our bogus customer object                                             |
------------------------------------------------------------------------------*/
  co = new CustomerObject;

/*-----------------------------------------------------------------------------|
| Create the frame window and give it an icon and menu bar.                    |
------------------------------------------------------------------------------*/
  frame = new IFrameWindow(reslib.loadString(WND_MAIN),WND_MAIN);
  frame->setIcon( WND_MAIN );
  MenuCommandHandler* menuCmdHandler = new MenuCommandHandler();
  menuCmdHandler->handleEventsFor(frame);
  IMenuBar* menuBar = new IMenuBar(MAIN_MENU, frame);

/*-----------------------------------------------------------------------------|
| Create a canvas with a statictext, entryfield and a pushbutton.              |
------------------------------------------------------------------------------*/
  ISetCanvas* sc  = new ISetCanvas(SC_1, frame, frame);
  IStaticText* st = new IStaticText(ST_1, sc, sc);
  st->setText(STR_ALPHA_ONLY);
  ef = new IEntryField(EF_1, sc, sc);
  pb = new IPushButton(PB_1, sc, sc);
  pb->setText(STR_ENTER);
  pb->disable();

/*-----------------------------------------------------------------------------|
| Create our observer and tell it to observe the entryfield and pushbutton.    |
------------------------------------------------------------------------------*/
  efObserver* entryFieldObserver = new efObserver();
  entryFieldObserver->handleNotificationsFor(*ef);
  entryFieldObserver->handleNotificationsFor(*pb);

/*-----------------------------------------------------------------------------|
| Enable the entryfield and pushbutton for notifications                       |
------------------------------------------------------------------------------*/
  ef->enableNotification();
  pb->enableNotification();

/*-----------------------------------------------------------------------------|
| Add another static text field to display the contents of our customer object.|
------------------------------------------------------------------------------*/
  display = new IStaticText(ST_2, sc, sc);

  frame->setClient(sc);
  frame->setFocus();
  frame->show();

  IApplication::current().run();

  return 0;
}


/*******************************************************************************
* Class CustomerObject::storeName - stores the customer name                   *
*******************************************************************************/
CustomerObject
 &CustomerObject::storeName(IString name)
{
  firstName = name;
  return *this;
}

/*******************************************************************************
* Class CustomerObject::name - returns the customer name                       *
*******************************************************************************/
IString
  CustomerObject::name()
{
  return firstName;
}

/*******************************************************************************
* Class efObserver::dispatchNotificationEvent - Dispatches events related to   *
*   the entryfield.                                                            *
*******************************************************************************/

IObserver
  &efObserver::dispatchNotificationEvent (const INotificationEvent& anEvent)
{
  if (anEvent.notificationId() == IEntryField::textId)
  {
    IWindow& window = ((IWindow&)anEvent.notifierAddress().notifier());
    IEntryField* entryField = ((IEntryField*)&window);
    IString text(entryField->text());
    if (!(text.isAlphabetic()))
    {
      pb->disable();
      IMessageBox msgBox(frame);
      msgBox.setTitle(TITLE_NOTIF_INF);
      IResourceLibrary
        reslib;
      IString
        str(reslib.loadString(STR_ILLEGAL_CHARS));
       msgBox.show(str, IMessageBox::information);
    }
    else
    {
      pb->enable();
    }
  }
  else if (anEvent.notificationId() == IEntryField::enableId)
  {
/*---------------------------------------------------------------------------|
| If the entryField is enabled, enable our pushbutton...                     |
| if the entryField is disabled, disable our pushbutton.                     |
----------------------------------------------------------------------------*/
    if (anEvent.eventData().asUnsignedLong())
    {
      pb->enable();
    }
    else
    {
      pb->disable();
    }
  }
  else if (anEvent.notificationId() == IButton::buttonClickId)
  {
/*-----------------------------------------------------------------------------|
| Store the data in our bogus object.                                          |
------------------------------------------------------------------------------*/
    co->storeName(ef->text());
  }
  return *this;
}


/******************************************************************************
* MenuCommandHandler::command - Handles all menu events                       *
******************************************************************************/
bool MenuCommandHandler::command(ICommandEvent& event)
{
  switch(event.commandId())
  {
    case MI_DISABLEEF:
      ef->disable();
      return true;
    case MI_ENABLEEF:
      ef->enable();
      return true;
    case MI_SHOW:
      display->setText(co->name());
      return true;
  }
  return false;
}
