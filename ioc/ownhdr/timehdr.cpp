/******************************************************************************
* .FILE:         timehdr.cpp                                                  *
*                                                                             *
* .DESCRIPTION:  Your Own Time Handler :  Class Implementation                *
*                                                                             *
* .CLASSES:      ATimeHandler                                                 *
*                                                                             *
* .COPYRIGHT:                                                                 *
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
#include <iwindow.hpp>                  //Include IWindow class header

#ifdef IC_PM                            //For OS/2,
  #define TIMER_ID      1               //  Set the timer ID as a constant
  #define INCL_WINTIMER                 //  Include the timer routines
  #include <os2.h>                      //    from the OS/2 libraries
  #include <ithread.hpp>                //  Include IThread class header
#endif

#ifdef IC_MOTIF                         //For AIX,
  #define WM_TIMER      0xF024          //  Create an event id for a timer
  extern "C" {                          //  Include the X-Window header files
  #include <X11/Intrinsic.h>            //    as C externals
  }
  extern void _System                   //Forward declare for post function
    postATimeHandlerEvent (IWindow *, XtIntervalId *);
#endif

#ifdef IC_WIN                           //For Windows,
  #define TIMER_ID      1               //  Set the timer ID as a constant
  #include <windows.h>                  //  From Windows libraries
#endif

#include "timehdr.hpp"
#include "ownhdr.h"

/**************************************************************************
* ATimeHandler :: handleEventsFor                                         *
*   Begin processing timer events for the window passed in by starting    *
*     the appropriate system timer.                                       *
**************************************************************************/
ATimeHandler
  &ATimeHandler :: handleEventsFor( IWindow *window )
{

#ifdef IC_MOTIF
/*--------------------------- Start a Timer ------------------------------|
| The X-Windows application add timeout routine is called by specifying,  |
|   the application context which is obtained using the window handle,    |
|   a time interval in milliseconds which is set to a constant 1000UL,    |
|   an external routine that is called when the timer is up, and          |
|   client_data which is a pointer to application specific data.          |
| The timerId is a unique ID returned from the add timer routine that     |
|   will be used when processing the expired timer.                       |
| When the timer expires, the callback routine will be called with        |
|   two parameters, the client_data and the timer id.                     |
|------------------------------------------------------------------------*/
  timerId = XtAppAddTimeOut (
                   XtWidgetToApplicationContext ((Widget)window->handle()),
                   TIME_INTERVAL,
                   (XtTimerCallbackProc) postATimeHandlerEvent,
                   window);
#endif

#ifdef IC_PM
/*--------------------------- Start a Timer ------------------------------|
| The Presentation Manager start timer routine is called by specifying    |
|   the anchor block handle for the current thread,                       |
|   the handle of the window passed in,                                   |
|   a unique timer ID that is below the PM TID_USER_MAX constant, and     |
|   a time interval in milliseconds which is set to a constant 1000UL.    |
| Since this application uses only a single timer, the timer ID is        |
|   specified as a constant.                                              |
| When the timer expires, PM will post a WM_TIMER event to the window     |
|   specified in parameter 2 of the WinStartTimer call.  IParameter1      |
|   of the timer event will contain the timer ID.                         |
|------------------------------------------------------------------------*/
  timerId = TIMER_ID;
  WinStartTimer( IThread::current().anchorBlock(),
                 window->handle(), timerId, TIME_INTERVAL);
#endif

#ifdef IC_WIN
/*--------------------------- Start a Timer ------------------------------|
| The Windows start timer routine is called by specifying the handle to   |
|   the window processing messages.                                       |
| Since this application uses only a single timer, the timer ID is        |
|   specified as a constant.                                              |
| When the timer expires, Windows posts a WM_TIMER event to the window    |
|   specified in parameter 1 of the SetTimer call.                        |
|------------------------------------------------------------------------*/
  timerId = TIMER_ID;
  SetTimer( window->handle(), timerId, TIME_INTERVAL, NULL );
#endif

/*------------------------- Start the Handler ----------------------------|
| Start the handler by explicitly calling the overridden function.        |
|------------------------------------------------------------------------*/
  Inherited::handleEventsFor(window);
  return (*this);
}

#ifdef IC_MOTIF
/**************************************************************************
* external postATimeHandlerEvent - timer callback routine                 *
*   Post a WM_TIMER event.  This is only necessary in MOTIF.              *
*     OS/2 PM timer calls automatically post the WM_TIMER event.          *
**************************************************************************/
  extern void _System
    postATimeHandlerEvent (IWindow * window, XtIntervalId *timerUp)
{
/*-------------------------- Is Window Valid ? ---------------------------|
| This test prevents an exception in IWindow in the case where a timer    |
|   expires while the window is being closed.  If the window is not valid,|
|   do nothing.                                                           |
|------------------------------------------------------------------------*/
  if (window->isValid())
{
/*--------------------------- Add Next Timer -----------------------------|
| When an X-Windows timer is up, it does not restart automatically.       |
|   Therefore, the callback routine starts another timer and registers    |
|   itself as the callback routine.  The new timer ID is passed to the    |
|   time handler in the timer event as parameter 2.                       |
|------------------------------------------------------------------------*/
    IEventParameter2 newTimer = XtAppAddTimeOut (
              XtWidgetToApplicationContext((Widget)window->handle()),
              TIME_INTERVAL,
              (XtTimerCallbackProc)postATimeHandlerEvent,
              window);
/*-------------------------- Post Timer Event ----------------------------|
| The timer event is created by posting an event to the window passed     |
|   in as client_data to the callback routine.  The ID of the timer that  |
|   expired is passed to the time handler as IParameter1 of the event.    |
|------------------------------------------------------------------------*/
    window->postEvent (WM_TIMER, IEventParameter1(*timerUp), newTimer);
  }
}
#endif

/**************************************************************************
* ATimeHandler :: dispatchHandlerEvent                                    *
*   Call tick when one of our timer events are dispatched.                *
**************************************************************************/
bool
  ATimeHandler :: dispatchHandlerEvent(IEvent& event)
{
  bool eventProcessed(false);        //Assume event will not be proccessed
/*--------------------------- Test the Event -----------------------------|
| This event must be a timer event and parameter 1 must contain the       |
|   ID of the timer that was started by this handler.                     |
|------------------------------------------------------------------------*/
  if ((event.eventId() == WM_TIMER) && (event.parameter1() == timerId))
  {
#ifdef IC_MOTIF
/*--------------------------- Save New Timer ID --------------------------|
| Since the timer ID is not constant in MOTIF, the new timer id, which    |
|   is passed as parameter 2 of the event, must be saved.                 |
|------------------------------------------------------------------------*/
   timerId = event.parameter2();
#endif
/*------------------------- Process Timer Event --------------------------|
| Process the timer event by calling the virtual function tick, which     |
|   should be overridden by an inheriting class.  The returned boolean    |
|   value determines whether the event was actually processed by tick.    |
|   The default ATimeHandler::tick function does not process the event.   |
|------------------------------------------------------------------------*/
    eventProcessed = tick(event);
  }
  return (eventProcessed);
}

/**************************************************************************
* ATimeHandler :: tick                                                    *
*   Default tick handler that should be overridden by inheriting classes  *
**************************************************************************/
bool
  ATimeHandler :: tick(IEvent& event)
{
  return (false);                       //The timer event is not processed
}

/**************************************************************************
* ATimeHandler :: stopHandlingEventsFor                                   *
*   Stop processing timer events for the window passed in.                *
**************************************************************************/
ATimeHandler
  &ATimeHandler :: stopHandlingEventsFor( IWindow *window )
{

#ifdef IC_MOTIF
/*--------------------------- Stop the Timer -----------------------------|
| The X-Windows remove timeout routine is called to stop the outstanding  |
|   timer which is identified by the ID stored in timerId.                |
|------------------------------------------------------------------------*/
  XtRemoveTimeOut (timerId);
  timerId = 0;
#endif

#ifdef IC_PM
/*--------------------------- Stop the Timer -----------------------------|
| The Presentation Manager stop timer routine is called to stop the       |
|   outstanding timer which is identified by,                             |
|     the anchor block handle of the current thread,                      |
|     the handle of the window passed in, and                             |
|     the ID stored in timerId.                                           |
|------------------------------------------------------------------------*/
  if ( window->isValid() )
    WinStopTimer( IThread::current().anchorBlock(),
                  window->handle(), timerId);
#endif

#ifdef IC_WIN
/*--------------------------- Stop the Timer -----------------------------|
| The Windows stop timer routine is called to stop the                    |
|   outstanding timer which is identified by                              |
|     the window handle processing messages.                              |
|------------------------------------------------------------------------*/
  if ( window->isValid() )
    KillTimer( window->handle(), timerId );
#endif

/*-------------------------- Stop the Handler ----------------------------|
| Stop the handler by explicitly calling the overridden function.  Its    |
|   returned value is used to determine the success of this routine.      |
|------------------------------------------------------------------------*/
  Inherited::stopHandlingEventsFor(window);
  return (*this);
}

