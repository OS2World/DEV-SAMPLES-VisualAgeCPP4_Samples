/******************************************************************************
* .FILE:         lmainwin.hpp                                                 *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Definition       *
*                                                                             *
* .CLASSES:      LMainWindow                                                  *
*                LMainWindowCommandHandler                                    *
*                LMainCnr                                                     *
*                LMainCnrObject                                               *
*                LMainWindowHelpHandler                                       *
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
#ifndef _LMAINWIN_
  #define _LMAINWIN_

#include <iapp.hpp>
#include <irect.hpp>
#include <istring.hpp>
#include <iframe.hpp>
#include <ititle.hpp>
#include <iinfoa.hpp>
#include <imenubar.hpp>
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
#include "linfowin.hpp"
#include "lcnrobj.hpp"
#include "ldbase.hpp"
#include "lancelot.h"

class LMainWindow;

/******************************************************************************
* Class LMainCnrObject - LMainWindow's container object                       *
******************************************************************************/
class LMainCnrObject : public LCnrObject
{
   public:
      enum ObjectType { personnel, project, query };

/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in one of four ways:                                   |
| 1) Existing object                                                          |
| 2) Icon resourceId, title, ObjectType, and description.                     |
| 3) Icon resourceId, title resourceId, ObjectType, & description resourceId. |
| 4) Icon resourceId, title, ObjectType, and description resourceId.          |
-----------------------------------------------------------------------------*/
      LMainCnrObject( const LMainCnrObject& cnrobj );

      LMainCnrObject( unsigned long icon, IString title,
                      ObjectType type, IString description );

      LMainCnrObject( unsigned long icon, IResourceId title,
                      ObjectType type, IResourceId description );

      LMainCnrObject( unsigned long icon, IString title,
                      ObjectType type, IResourceId description );

      virtual
         ~LMainCnrObject();

/*------------------------------- Accessors -----------------------------------
| These functions provide a means of getting and setting the accessible       |
| attributes of instances of this class:                                      |
|   type                - Returns the type of the container object            |
|   description         - Returns the description.                            |
|   setType             - Sets the type.                                      |
|   setDescription      - Sets the description.                               |
|   typeOffset          - Returns the container offset for the type.          |
|   descOffset          - Returns the container offset for the description.   |
-----------------------------------------------------------------------------*/
      inline ObjectType
         type() const { return theType; };
      inline IString
         description() const { return theDesc; };

      inline LMainCnrObject
         &setType( ObjectType newType ) { theType=newType; return *this; };
      inline LMainCnrObject
         &setDescription( IString desc ) { theDesc=desc; return *this; };

      inline static unsigned long
         typeOffset() { return ICONTAINERCOLUMN_OFFSETOF( LMainCnrObject, theType ); };
      inline static unsigned long
         descOffset() { return ICONTAINERCOLUMN_OFFSETOF( LMainCnrObject, theDesc ); };

   private:

      ObjectType
         theType;

      IString
         theDesc;
};


/******************************************************************************
* Class LMainCnr - Main window's container                                    *
******************************************************************************/
class LMainCnr : public IContainerControl,
                 protected ICnrHandler,
                 protected ICnrMenuHandler
{
   public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in only one way:                                       |
| 1) Window id, parent, owner, and location                                   |
-----------------------------------------------------------------------------*/
      LMainCnr( unsigned long id, LMainWindow* parent,
                LMainWindow* owner, IRectangle location=IRectangle() );
      virtual
         ~LMainCnr();

/*------------------------------- Accessors -----------------------------------
| These functions provide a means of getting and setting the accessible        |
| attributes of instances of this class:                                       |
|   lastPopupMenuObject - Returns the last container object that had a         |
|                         popup menu over it.  But not guaranteed that the     |
|                         last action was a popup menu.                        |
|   setLastPopupMenuObject - Sets the last container object that had a popup   |
|                         menu over it.                                        |
-----------------------------------------------------------------------------*/
      inline LMainCnrObject
        *lastPopupMenuObject() { return ptheLastPopupMenuObject; };

      inline LMainCnr
        &setLastPopupMenuObject( LMainCnrObject* object )
                               { ptheLastPopupMenuObject = object; return *this; };

/*------------------------------- Manipulation --------------------------------
| These functions provide a means of manipulating the instances of this class:|
|   populate            - Populate the container with query objects.          |
|   addLastQuery        - Add the new saved query to the container.           |
-----------------------------------------------------------------------------*/
      LMainCnr
        &populate();

      LMainCnr
        &addLastQuery( IString queryName );

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

      LMainCnrObject
        *pCnrObject[ ID_MAIN_MAX_CNROBJECTS ];

      IContainerColumn
         colIcon,
         colIconText,
         colDesc;

      LMainCnrObject
        *ptheLastPopupMenuObject;

      IHelpWindow
        *helpWin;

      IPopUpMenu
        *popm;

      unsigned long
         objCount;
};


/******************************************************************************
* Class LMainWindowCommandHandler - Handle command events.                    *
******************************************************************************/
class LMainWindowCommandHandler : public ICommandHandler
{
   public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in only one way:                                       |
| 1) Owner, help window, and container.                                       |
-----------------------------------------------------------------------------*/
      LMainWindowCommandHandler( LMainWindow* owner,
                                 IHelpWindow* helpWin,
                                 LMainCnr* cnrCtl );
      virtual
        ~LMainWindowCommandHandler();

/*------------------------- Container Object Actions --------------------------
| These functions provide a means of performing actions on container objects.  |
|   openAction          - Opens/views the container object.                    |
|   deleteAction        - Deletes the container object.                        |
-----------------------------------------------------------------------------*/
      LMainWindowCommandHandler
        &openAction( LMainCnrObject* cnrObject );

      bool
         deleteAction( LMainCnrObject* cnrObject );

   protected:
/*----------------------------- Event Processing ------------------------------
| Handle and process events:                                                  |
|   command             - Process command events.                             |
-----------------------------------------------------------------------------*/
      virtual bool
         command( ICommandEvent& event );

   private:
      LMainWindow
        *pOwner;

      IHelpWindow
        *pHelp;

      LMainCnr
        *pCnr;
};


/******************************************************************************
* Class LMainWindowHelpHandler - Handle help events.                          *
******************************************************************************/
class LMainWindowHelpHandler : public IHelpHandler
{
   public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in only one way:                                       |
| 1) No parameters.                                                           |
-----------------------------------------------------------------------------*/
      LMainWindowHelpHandler();

      virtual
        ~LMainWindowHelpHandler();

   protected:
/*----------------------------- Event Processing ------------------------------
| Handle and process events:                                                  |
|   keysHelpId          - Process help events for the container.              |
-----------------------------------------------------------------------------*/
      virtual bool
         keysHelpId( IEvent& event );
};


/******************************************************************************
* Class LMainToolBar - Toolbar class                                          *
******************************************************************************/
class LMainToolBar : public IToolBar
{
   public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in only one way:                                       |
| 1) Resource id, owner, information area.                                    |
-----------------------------------------------------------------------------*/
      LMainToolBar( unsigned long id, IFrameWindow* owner,
                    ITextControl* infoArea );

/*----------------------------- Manipulators ----------------------------------
| These functions provide a means of manipulating the attributes of            |
| instances of this class:                                                     |
|   enableSelects       - Enable or disables the select-all and deselect-all   |
|                         toolbar buttons.                                     |
-----------------------------------------------------------------------------*/
      LMainToolBar
       &enableSelects( bool which = true );

   private:
      IToolBarButton
         openButton,
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
* Class LMainWindow - Main frame window.                                      *
******************************************************************************/
class LMainWindow : public IFrameWindow
{
   public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in only one way:                                       |
| 1) No parameters.                                                           |
-----------------------------------------------------------------------------*/
      LMainWindow();

      virtual
       ~LMainWindow();

/*------------------------------- Accessors -----------------------------------
| These functions provide a means of getting and setting the accessible        |
| attributes of instances of this class:                                       |
|   helpWindow          - Returns the help window for this frame window.       |
|   selectsAllowed      - Returns true if select all/deselect all is allowed. |
-----------------------------------------------------------------------------*/
      inline IHelpWindow
       *helpWindow() { return &help; };

      inline bool
         selectsAllowed() { return aSelects; };
/*----------------------------- Manipulators ----------------------------------
| These functions provide a means of manipulating the attributes of            |
| instances of this class:                                                     |
|   enableSelects       - Enable or disables the select-all and deselect-all   |
|                         menuitems and toolbar buttons.                       |
-----------------------------------------------------------------------------*/
      LMainWindow
       &enableSelects( bool which = true );

   private:
      ITitle
         title;

      IMenuBar
         menubar;

      IInfoArea
         infoarea;

      LMainCnr
         cnr;

      LMainToolBar
         toolbar;

      IHelpWindow
         help;

      LMainWindowCommandHandler
         cmdHdr;

      LMainWindowHelpHandler
         helpHdr;

      bool
         aSelects;
};
#endif
