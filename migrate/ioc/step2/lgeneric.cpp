/*******************************************************************************
* FILE NAME: lgeneric.cpp                                                      *
*                                                                              *
* DESCRIPTION:                                                                 *
*                                                                              *
* Class                                                                        *
*   AcheckBoxHandler                                                           *
*                                                                              *
* COPYRIGHT:                                                                   *
*   Licensed Materials - Property of IBM                                       *
*   (C) Copyright IBM Corporation 1992, 1995                                   *
*   All Rights Reserved                                                        *
*   US Government Users Restricted Rights - Use, duplication, or disclosure    *
*   restricted by GSA ADP Schedule Contract with IBM Corp.                     *
*                                                                              *
* CHANGE HISTORY:                                                              *
*******************************************************************************/

#ifndef _IBASE_                         //Make sure ibase.hpp is included
  #include <ibase.hpp>                  //  since that is where IC_<environ>
#endif                                  //  is defined.
#include "lancelot.h"
#include <ictlevt.hpp>
#include "lgeneric.hpp"

/******************************************************************************/
/* ACheckBoxHandler::selected      - an ISelectEventHandler                     */
/*   return true if event handled else return false                           */
/* display the number of the button selected in a text control                */
/******************************************************************************/
IBase :: Boolean ACheckBoxHandler::selected(IControlEvent& evt )
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
