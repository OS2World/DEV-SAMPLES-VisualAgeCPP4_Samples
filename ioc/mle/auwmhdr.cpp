/******************************************************************************
* .FILE:         auwmhdr.cpp                                                  *
*                                                                             *
* .DESCRIPTION:  Multiline Edit Sample Program:        Class Implementation   *
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
#include "auwmhdr.hpp"

/******************************************************************************/
/* AUserMessageHandler::dispatchHandlerEvent - catch user events              */
/******************************************************************************/
bool AUserMessageHandler::dispatchHandlerEvent( IEvent& evt )
{
  if ( evt.eventId() == userMessageId )
    return userMessage( evt );

  return false;
}  /* end  AUserMessageHandler::dispatchHandlerEvent(...)  */
