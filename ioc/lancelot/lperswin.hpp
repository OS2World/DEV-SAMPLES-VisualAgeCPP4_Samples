/******************************************************************************
* .FILE:         lperswin.hpp                                                 *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Definition       *
*                                                                             *
* .CLASSES:      LPersonnelWindow                                             *
*                LPersonnelWindowCommandHandler                               *
*                LPersonnelCnr                                                *
*                LPersonnelCnrObject                                          *
*                LPersonnelWindowHelpHandler                                  *
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
#ifndef _LPERSWIN_
  #define _LPERSWIN_

#include <iapp.hpp>
#include <irect.hpp>
#include <istring.hpp>
#include <iframe.hpp>
#include <ititle.hpp>
#include <iinfoa.hpp>
#include <imenubar.hpp>
#include <idmhndlr.hpp>
#include <itbar.hpp>
#include <itbarbut.hpp>
#include <iflytext.hpp>
#include <iflyhhdr.hpp>
#include <icmdhdr.hpp>
#include <icnrhdr.hpp>
#include <icnrmhdr.hpp>
#include <ievent.hpp>
#include <icnr.hpp>
#include <icnrobj.hpp>
#include <icnrctl.hpp>
#include <icnrcol.hpp>
#include <ipopmenu.hpp>
#include <ifont.hpp>
#include <imsgbox.hpp>
#include <ihelp.hpp>
#include <ihelphdr.hpp>
#include "lcnrobj.hpp"
#include "ldbase.hpp"
#include "ldbqry.hpp"
#include "lancelot.h"
#include "lperswdm.hpp"

class LPersonnelWindow;

/******************************************************************************
* Class LPersonnelCnrObject - LPersonnelMainWindow's container object         *
******************************************************************************/
class LPersonnelCnrObject : public LCnrObject
{
   friend class LPersonnelCnr;

   public:

/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in two of four ways:                                   |
| 1) Existing object                                                          |
| 2) Icon resourceId and EmployeeData object.                                 |
-----------------------------------------------------------------------------*/
      LPersonnelCnrObject( const LPersonnelCnrObject& cnrobj );

      LPersonnelCnrObject( unsigned long icon,
            const LEmployeeData& employee );

      virtual
        ~LPersonnelCnrObject();

/*------------------------------- Accessors -----------------------------------
| These functions provide a means of getting and setting the accessible        |
| attributes of instances of this class:                                       |
|   employeeRecord      - Returns the employee data                            |
-----------------------------------------------------------------------------*/
      inline LEmployeeData
         employeeRecord() const { return theEmployee; };

   private:

      LEmployeeData
         theEmployee;
};


/******************************************************************************
* Class LPersonnelCnr - Personnel window's container                          *
******************************************************************************/
class LPersonnelCnr : public IContainerControl,
                      protected ICnrHandler,
                      protected ICnrMenuHandler

{
   public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in only one way:                                       |
| 1) Window id, parent, owner, and location                                   |
-----------------------------------------------------------------------------*/
      LPersonnelCnr( unsigned long id, LPersonnelWindow* parent,
                     LPersonnelWindow* owner, IRectangle location=IRectangle() );
      virtual
        ~LPersonnelCnr();

/*------------------------------- Accessors -----------------------------------
| These functions provide a means of getting and setting the accessible        |
| attributes of instances of this class:                                       |
|   lastPopupMenuObject - Returns the last container object that had a         |
|                         popup menu over it.  But not guaranteed that the     |
|                         last action was a popup menu.                        |
|   setLastPopupMenuObject - Sets the last container object that had a popup   |
|                         menu over it.                                        |
-----------------------------------------------------------------------------*/
      LPersonnelCnrObject
        *lastPopupMenuObject() { return ptheLastPopupMenuObject; };

      LPersonnelCnr
        &setLastPopupMenuObject( LPersonnelCnrObject* object )
                               { ptheLastPopupMenuObject = object; return *this; };

   protected:
/*----------------------------- Event Processing ------------------------------
| Handle and process events:                                                  |
|   makePopupMenu       - Process popup menu events.                          |
|   enter               - Process the enter key for container objects.        |
|   help                - Process the help key for container objects.         |
-----------------------------------------------------------------------------*/
      virtual bool
         makePopUpMenu( IMenuEvent& evt ),
         enter( ICnrEnterEvent& evt ),
         help( ICnrHelpEvent& evt );

   private:
      LPersonnelCnrObject
        *pCnrObject[ ID_PERSONNEL_MAX_CNROBJECTS ];

      IContainerColumn
         colIcon,
         colIconText,
         colLastName,
         colFirstName,
         colMiddleInitial,
         colEmployeeNumber,
         colInternalPhone,
         colExternalPhone,
         colInternalAddress,
         colExternalAddress,
         colRoom,
         colBuilding,
         colDepartment,
         colManagerNumber,
         colManagerName;

      LPersonnelCnrObject
        *ptheLastPopupMenuObject;

      IHelpWindow
        *helpWin;

      IPopUpMenu
        *popm;

};


/******************************************************************************
* Class LPersonnelWindowCommandHandler - Handle command events.               *
******************************************************************************/
class LPersonnelWindowCommandHandler : public ICommandHandler
{
   public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in only one way:                                       |
| 1) Owner, help window, and container.                                       |
-----------------------------------------------------------------------------*/
      LPersonnelWindowCommandHandler( LPersonnelWindow* owner,
                                      IHelpWindow* helpWin,
                                      LPersonnelCnr* cnrCtl );
      virtual
        ~LPersonnelWindowCommandHandler();

/*------------------------- Container Object Actions --------------------------
| These functions provide a means of performing actions on container objects.  |
|   openAction          - Opens/views the container object.                    |
|   createAction        - Creates a new container object.                      |
|   transferAction      - Transfer the container object to another department. |
|   deleteAction        - Deletes the container object.                        |
-----------------------------------------------------------------------------*/
      LPersonnelWindowCommandHandler
        &openAction( LPersonnelCnrObject* cnrObject ),
        &createAction( LPersonnelCnrObject* cnrObject ),
        &transferAction( LPersonnelCnrObject* cnrObject );
      bool
        deleteAction( LPersonnelCnrObject* cnrObject );

   protected:
/*----------------------------- Event Processing ------------------------------
| Handle and process events:                                                  |
|   command             - Process command events.                             |
-----------------------------------------------------------------------------*/
      virtual bool
         command( ICommandEvent& event );

   private:
      LPersonnelWindow
        *pOwner;

      IHelpWindow
        *pHelp;

      LPersonnelCnr
        *pCnr;
};


/******************************************************************************
* Class LPersonnelWindowHelpHandler - Handle help events.                     *
******************************************************************************/
class LPersonnelWindowHelpHandler : public IHelpHandler
{
   public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in only one way:                                       |
| 1) No parameters.                                                           |
-----------------------------------------------------------------------------*/
      LPersonnelWindowHelpHandler();

      virtual
         ~LPersonnelWindowHelpHandler();

   protected:
/*----------------------------- Event Processing ------------------------------
| Handle and process events:                                                  |
|   keysHelpId          - Process help events for the container.              |
-----------------------------------------------------------------------------*/
      virtual bool
         keysHelpId( IEvent& event );
};


/******************************************************************************
* Class LPersonnelToolBar - Toolbar class                                     *
******************************************************************************/
class LPersonnelToolBar : public IToolBar
{
   public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in only one way:                                       |
| 1) Resource id, owner, information area.                                    |
-----------------------------------------------------------------------------*/
      LPersonnelToolBar( unsigned long id, IFrameWindow* owner,
                         ITextControl* infoArea );

/*----------------------------- Manipulators ----------------------------------
| These functions provide a means of manipulating the attributes of            |
| instances of this class:                                                     |
|   enableSelects       - Enable or disables the select-all and deselect-all   |
|                         toolbar buttons.                                     |
-----------------------------------------------------------------------------*/
      LPersonnelToolBar
       &enableSelects( bool which = true );

   private:
      IToolBarButton
         openButton,
         createButton,
         transferButton,
         deleteButton,
         iconButton,
         treeButton,
         detailsButton,
         selectAllButton,
         deselectAllButton,
         sortAscButton,
         sortDescButton,
         arrangeButton,
         helpButton;

      IFlyText
         flyText;

      IFlyOverHelpHandler
         flyHelpHdr;
};

/******************************************************************************
* Class LPersonnelWindow - Personnel frame window.                            *
******************************************************************************/
class LPersonnelWindow : public IFrameWindow
{
   public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in only one way:                                       |
| 1) Owner, QueryIntersection object, query string.                           |
-----------------------------------------------------------------------------*/
      LPersonnelWindow( IWindow* owner, QueryIntersection& bagOfIds,
                         const IString deptQuery);
      virtual
       ~LPersonnelWindow();

/*------------------------------- Accessors -----------------------------------
| These functions provide a means of getting and setting the accessible       |
| attributes of instances of this class:                                      |
|   helpWindow          - Returns the help window for this frame window.      |
|   deptQuery           - If a fully-qualified department name was specified  |
|                         on the query, return the department name.           |
|   selectsAllowed      - Returns true if select all/deselect all is allowed. |
-----------------------------------------------------------------------------*/
      inline IHelpWindow
       *helpWindow() { return &help; };

      inline IString
        deptQuery() { return aDeptQuery; };

      inline bool
         selectsAllowed() { return aSelects; };

/*------------------------------- Manipulation --------------------------------
| These functions provide a means of manipulating the instances of this class:|
|   populate            - Populate the container with employee objects.       |
|   enableSelects       - Enable or disables the select-all and deselect-all   |
|                         toolbar buttons.                                     |
-----------------------------------------------------------------------------*/
      LPersonnelWindow
       &populate( QueryIntersection& bagOfIds );

      LPersonnelWindow
       &enableSelects( bool which = true );

      IDMItemProviderFor< EmployeeItem >
         provider;

/*----------------------------- Event Processing ------------------------------
| Handle and process events:                                                  |
|   command             - Process command events.                             |
|   keysHelpId          - Process the help key for container objects.         |
-----------------------------------------------------------------------------*/
   protected:
      bool
         command( ICommandEvent& evt ),
         keysHelpId( IEvent& evt );

   private:
      ITitle
         title;

      IMenuBar
         menubar;

      IInfoArea
         infoarea;

      LPersonnelCnr
         cnr;

      LPersonnelToolBar
         toolbar;

      IHelpWindow
         help;

      LPersonnelWindowCommandHandler
         cmdHdr;

      LPersonnelWindowHelpHandler
         helpHdr;

      IString
         aDeptQuery;

      bool
         aSelects;
};
#endif
