/******************************************************************************
* .FILE:         timehdr.hpp                                                  *
*                                                                             *
* .DESCRIPTION:  Create your own time handler : Class Definitions             *
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
#ifndef _ATIMEHDR_
#define _ATIMEHDR_

#ifndef _IHANDLER_
  #include <ihandler.hpp>
#endif

/**************************************************************************
* Class:   ATimeHandler                                                   *
*                                                                         *
* Purpose: New Handler class that processes timer events.                 *
*                                                                         *
**************************************************************************/
class ATimeHandler : public IHandler
{
  typedef IHandler
    Inherited;
  public:
    ATimeHandler() : timerId(0) { }       //Initialize timerId data member
    virtual ~ATimeHandler() { }

/*----------------- Override Public IHandler Functions -------------------|
| These public IHandler functions are overridden to add start and stop    |
|   timer calls, respectively.                                            |
|------------------------------------------------------------------------*/
    virtual ATimeHandler
      &handleEventsFor(IWindow *window),
      &stopHandlingEventsFor(IWindow *window );

  protected:
/*------------------- Override Protected IHandler Function ---------------|
| The dispatchHandlerEvent function is overridden to call the tick        |
|   function for processing timer events.                                 |
| The tick function is added in ATimeHandler and should be overridden     |
|   by classes that inherit from ATimeHandler.                            |
|------------------------------------------------------------------------*/
    bool
      dispatchHandlerEvent(IEvent& event);
    virtual bool
      tick(IEvent& event);

  private:
/*--------------------------- Private Data Member ------------------------|
| The timerId private data member is used by the ATimeHandler functions   |
|   to save the ID of the outstanding timer call.                         |
|------------------------------------------------------------------------*/
    unsigned long timerId;
};
#endif
