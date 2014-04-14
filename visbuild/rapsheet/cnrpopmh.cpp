/******************************************************************************
* .FILE:        cnrpopmh.cpp                                                  *
*                                                                             *
* .DESCRIPTION: Handler that customizes the popup menu for a container.       *
*               When the mouse is clicked over a container object, the        *
*               menu items identified in the aCnrMenuItemList parm are        *
*               deleted from the popup menu.  When the mouse is clicked       *
*               over the background of the container itself, the menu         *
*               items identified in the aCnrObjMenuItemList parm are          *
*               deleted from the popup menu.  All changes to the popup        *
*               menu are undone when the menu terminates.                     *
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
#include <itrace.hpp>
#include <ivseq.h>
#include <isubmenu.hpp>
#include "cnrpopmh.hpp"            //CnrPopupMenuHandler

//*******************************************************************
// Constructor
//*******************************************************************
CnrPopupMenuHandler :: CnrPopupMenuHandler(
                             IVSequence<unsigned long>* aCnrObjMenuItemList,
                             IVSequence<unsigned long>* aCnrMenuItemList) :
     ICnrMenuHandler(),
     iCnrObjMenuItemList(aCnrObjMenuItemList),
     iCnrMenuItemList(aCnrMenuItemList)
{
}

//*******************************************************************
// Destructor
//*******************************************************************
CnrPopupMenuHandler :: ~CnrPopupMenuHandler()
{
}

//*******************************************************************
// menuShowing()
//*******************************************************************
bool CnrPopupMenuHandler::menuShowing(IMenuEvent& menuEvent,
                                         ISubmenu& popupAboutToShow)
{
     IContainerObject* popupObject = popupMenuObject();
     unsigned long menuItemId;

     IFUNCTRACE_DEVELOP();

     if (popupObject)     //a popup menu was requested for a container object
     {
         /* delete all the menu items that apply to the container */
         IVSequence<unsigned long>::Cursor aCursor(*iCnrMenuItemList);
         forCursor(aCursor)
         {
            menuItemId = iCnrMenuItemList->elementAt(aCursor);
            popupAboutToShow.deleteItem(menuItemId);
         }
     }
     else               //a popup menu was requested for the container itself
     {
         /* delete all the menu items that apply to a container object */
         IVSequence<unsigned long>::Cursor aCursor(*iCnrObjMenuItemList);
         forCursor(aCursor)
         {
            menuItemId = iCnrObjMenuItemList->elementAt(aCursor);
            popupAboutToShow.deleteItem(menuItemId);
         }
     }

     return true;   //undo changes to popupAboutToShow when
                    //IMenuHandler::menuEnded is called after the
                    //menu terminates.
}
