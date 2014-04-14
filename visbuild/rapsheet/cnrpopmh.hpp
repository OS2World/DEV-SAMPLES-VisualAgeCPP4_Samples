#ifndef _CNRPOPMH_
#define _CNRPOPMH_
/******************************************************************************
* .FILE:        cnrpopmh.hpp                                                  *
*                                                                             *
* .DESCRIPTION: Header file for the class, CnrPopupMenuHandler                *
*                                                                             *
* .CLASSES:     CnrPopupMenuHandler                                           *
*                                                                             *
* .COPYRIGHT:                                                                 *
*    Licensed Material - Program-Property of IBM                              *
*    (C) Copyright IBM Corp. 1992, 1996 - All Rights Reserved                 *
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
#include <icnrmhdr.hpp>              // ICnrMenuHandler, parent class, which
                                     // indirectly includes IMenuEvent.

//forward class references
template <class Element> class IVSequence;
class ISubmenu;

//**************************************************************************
// Class:   CnrPopupMenuHandler
//
// Purpose: Provides popup menu support for a container control.
//          When the popup menu is about to be shown, this handler
//          customizes the popup menu.  If the popup menu is over
//          a container object, it deletes all the menu items whose
//          ids are listed in the ctor parm, aCnrMenuItemList.
//          And if the popup menu is over the container, it deletes
//          all the menu items whose ids are listed in the ctor parm,
//          aCnrObjMenuItemList.  All the changes are undone when
//          IMenuHandler::menuEnded is called upon menu termination.
//
//***************************************************************************
class CnrPopupMenuHandler : public ICnrMenuHandler
{

public:
   CnrPopupMenuHandler(IVSequence<unsigned long> *aCnrObjMenuItemList,
                       IVSequence<unsigned long> *aCnrMenuItemList);
   virtual ~CnrPopupMenuHandler();     //destructor

protected:
   bool menuShowing(IMenuEvent& menuEvent,
                       ISubmenu& popupAboutToShow);

private:
   IVSequence<unsigned long>
      *iCnrObjMenuItemList,
      *iCnrMenuItemList;

};   //CnrPopupMenuHandler

#endif
