/******************************************************************************
* .FILE:         lgeneric.hpp                                                 *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Definition       *
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
#ifndef _LGENERIC_
#define _LGENERIC_


#include <iselhdr.hpp>
/******************************************************************************/
/* Class   : ACheckBoxHandler                                                 */
/*                                                                            */
/* Purpose : this is the select handler for a check box.                      */
/*           The button handler is called when a radio button is selected.    */
/*           ACheckBoxHandler is derived from ISelectHandler                  */
/******************************************************************************/
class ACheckBoxHandler : public ISelectHandler
{
public:
   enum Toggle { false, true };
   ACheckBoxHandler() : toggle(true) {};
   inline ACheckBoxHandler&  setToggle(Toggle tog ) { toggle = tog;return *this;};
   Toggle getToggle() { return toggle; };
protected:
   bool selected      ( IControlEvent& evt );
private:
   Toggle   toggle;
};


#endif
