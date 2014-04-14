/******************************************************************************
* .FILE:         lgeneric.cpp                                                 *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Implementation   *
*                                                                             *
* .CLASSES:      ACheckBoxHandler                                             *
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
#include "lancelot.h"
#include <ictlevt.hpp>
#include "lgeneric.hpp"

/******************************************************************************/
/* ACheckBoxHandler::selected      - an ISelectEventHandler                     */
/*   return true if event handled else return false                           */
/* display the number of the button selected in a text control                */
/******************************************************************************/
bool ACheckBoxHandler::selected(IControlEvent& evt )
{

   unsigned long ulButtonId = evt.controlId();
                                       // if the id is one of the buttons
                                       // then display the button number in the

  switch (evt.controlId()) {       //Get command id

    case ID_CHECK_BOX:                    //Code to Process
      //atusData.toggleActive();
      if (toggle == true)
         toggle = ACheckBoxHandler::false;
      else
         toggle = ACheckBoxHandler::true;

      return(true);                     //Return command processed
      break;                            //

   }                            // static text control

   return (false);

} /* end ACheckBoxHandler::selected(...) */
