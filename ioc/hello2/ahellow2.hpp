/******************************************************************************
* .FILE:        ahellow2.hpp                                                  *
*                                                                             *
* .DESCRIPTION: Hello World Sample Program Version 2: Class Header            *
*                                                                             *
* .CLASSES:     AHelloWindow                                                  *
*               ACommandHandler                                               *
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
#ifndef _AHELLOW2_
#define _AHELLOW2_

#include <iframe.hpp>
#include <istattxt.hpp>
#include <iinfoa.hpp>


/**************************************************************************
* Class AHelloWindow--Main Frame Window                                   *
**************************************************************************/
class AHelloWindow : public IFrameWindow
{

/*---------------------------  Constructor  ------------------------------|
| Construct the object with:                                              |
| 1)  with the WindowID                                                   |
-------------------------------------------------------------------------*/
  public:
    AHelloWindow (const unsigned long windowId);


/*----------------------------  Destructor  ------------------------------|
| Destruct the object with:                                               |
| 1)  no parameters                                                       |
-------------------------------------------------------------------------*/
  virtual
   ~AHelloWindow() { }


  private:
    IStaticText
      hello;
    IInfoArea
      infoArea;
/*------------------------------ Operators -------------------------------|
| Operators defined for this class:                                       |
|  =  -- Assignment operator                                              |
-------------------------------------------------------------------------*/
  AHelloWindow
   &operator= (const AHelloWindow&);
};
#endif
