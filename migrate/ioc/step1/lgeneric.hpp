/*******************************************************************************
* FILE NAME: lgeneric.hpp                                                      *
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
   Boolean selected      ( IControlEvent& evt );
private:
   Toggle   toggle;
};


#endif
