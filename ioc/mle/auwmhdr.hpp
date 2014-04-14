/******************************************************************************
* .FILE:         auwmhdr.hpp                                                  *
*                                                                             *
* .DESCRIPTION:  Multiline Edit Sample Program:    Class Definition           *
*                                                                             *
* .CLASSES:      AUserMessageHandler                                          *
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
#ifndef AUSERMESSAGEHANDLER_HPP
#define AUSERMESSAGEHANDLER_HPP

#include <ihandler.hpp>

/******************************************************************************/
/* Class   : AUserMessageHandler                                              */
/*                                                                            */
/* Purpose : Instances of this class can be user to process user messages.    */
/*           Objects of this class process messages with the ID that the      */
/*           the object is created with. The class provides the virtual       */
/*           function userMessage which you should override to do your        */
/*           application specific processing.                                 */
/*           It is derived from IHandler                                      */
/*                                                                            */
/******************************************************************************/
class AUserMessageHandler : public IHandler
{
  public:
    AUserMessageHandler( unsigned long uwmId )
      : userMessageId( uwmId ) {;}
  bool
    dispatchHandlerEvent( IEvent& evt );

  protected:
    virtual bool
       userMessage( IEvent& evt ) { return false; }

  private:
    unsigned long   userMessageId;
};

#endif
