/******************************************************************************
* .FILE:         notify.hpp                                                   *
*                                                                             *
* .DESCRIPTION:  Notify Sample Application: Class Header                      *
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
#include <istring.hpp>
#include <iobservr.hpp>
#include <inotifev.hpp>
#include <icmdhdr.hpp>

/*******************************************************************************
* Class CustomerObject - A class that holds the name of the customer           *
*******************************************************************************/
class CustomerObject
{
  public:
/*------------------------------ Constructor  ---------------------------------|
| Constructs object with                                                       |
| 1) A string containing the name of the customer                              |
------------------------------------------------------------------------------*/
    CustomerObject
     &storeName(IString name);
    IString
      name();

  private:
    IString
      firstName;
};

/*******************************************************************************
* Class efObserver - Declare the entryField observer class.                    *
*******************************************************************************/
class efObserver : public IObserver
{
  public:

/*------------------------- Override the Function ----------------------------|
| Override the dispatchNotificationEvent function and process the             |
| notifications needed.                                                       |
-----------------------------------------------------------------------------*/
    virtual IObserver
     &dispatchNotificationEvent (const INotificationEvent& anEvent);

};


/*******************************************************************************
* Class MenuCommandHandler - Handles menu commands                           *
*******************************************************************************/
class MenuCommandHandler : public ICommandHandler
{
  protected:

/*------------------------- Override the Function ----------------------------|
| Override the command function to handle the menu items                      |
-----------------------------------------------------------------------------*/
    virtual bool
      command(ICommandEvent& event);
};
