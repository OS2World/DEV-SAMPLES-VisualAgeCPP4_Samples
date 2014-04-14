/******************************************************************************
* .FILE:         ownhdr.hpp                                                   *
*                                                                             *
* .DESCRIPTION:  Create your own handler window :  Class Definitions          *
*                                                                             *
* .CLASSES:      MyTimeHandler                                                *
*                MyWindow                                                     *
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
#ifndef _TIMEWIN_
#define _TIMEWIN_
#include <iframe.hpp>
#include <ititle.hpp>
#include <istattxt.hpp>
#include "timehdr.hpp"


/******************************************************************************
* Class MyTimeHandler - Time handler                                          *
******************************************************************************/
class MyTimeHandler : public ATimeHandler
{
  public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in only one way:                                       |
| 1) Parameter for updating static text                                       |
-----------------------------------------------------------------------------*/
    MyTimeHandler( IStaticText* staticText );

  protected:
/*----------------------------- Override Callbacks ----------------------------
| These functions provide a means of getting notification of events:           |
|   tick                - Called when a timed event occur                      |
-----------------------------------------------------------------------------*/
    virtual bool
      tick( IEvent& event );

  private:
    IStaticText
     *pText;
};


/******************************************************************************
* Class MyWindow - Main window                                                *
******************************************************************************/
class MyWindow : public IFrameWindow
{
  public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in only one way:                                       |
| 1) No parameters.                                                           |
-----------------------------------------------------------------------------*/
    MyWindow();
    virtual
     ~MyWindow();

  private:
    ITitle
      title;
    IStaticText
      staticText;
    MyTimeHandler
      timeHdr;
};
#endif
