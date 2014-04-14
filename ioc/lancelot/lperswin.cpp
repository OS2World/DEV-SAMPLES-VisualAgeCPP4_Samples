/****************************************************************************
* LANCELOT SAMPLE PROGRAM - lperswin.cpp                                    *
*                                                                           *
* Classes : LPersonnelWindow                                                *
*           LPersonnelWindowCommandHandler                                  *
*           LPersonnelCnr                                                   *
*           LPersonnelCnrObject                                             *
*           LPersonnelWindowHelpHandler                                     *
*                                                                           *
* COPYRIGHT:                                                                *
*    IBM Open Class Library                                                   *
*    Licensed Material - Program-Property of IBM                            *
*    (C) Copyright IBM Corp. 1992, 1997 - All Rights Reserved               *
*                                                                           *
* DISCLAIMER OF WARRANTIES:                                                 *
*   The following [enclosed] code is sample code created by IBM             *
*   Corporation.  This sample code is not part of any standard IBM product  *
*   and is provided to you solely for the purpose of assisting you in the   *
*   development of your applications.  The code is provided "AS IS",        *
*   without warranty of any kind.  IBM shall not be liable for any damages  *
*   arising out of your use of the sample code, even if they have been      *
*   advised of the possibility of such damages.                             *
****************************************************************************/
#include "lperswin.hpp"
#include "linfowin.hpp"
#include "lgoodies.hpp"
#include "lprdinfo.hpp"

/******************************************************************************
* Class LPersonnelWindow :: LPersonnelWindow - Constructor for the personnel  *
*   window.                                                                   *
*                                                                             *
* Define yourself as an IFrameWindow                                          *
* Create title                                                                *
* Create menubar                                                              *
* Create information area                                                     *
* Create container                                                            *
* Create toolbar (PM only)                                                    *
* Create help window                                                          *
* Create command handler                                                      *
* Create help handler                                                         *
* Store department query string                                               *
******************************************************************************/
LPersonnelWindow::LPersonnelWindow( IWindow* owner,
                                    QueryIntersection& bagOfIds,
                                    const IString deptQuery )
     :IFrameWindow         ( ID_PERSONNEL, 0, owner ),
      title                ( this, STR_MAIN_TITLE, STR_PERSONNEL_TITLE ),
      menubar              ( ID_PERSONNEL, this ),
      infoarea             ( this ),
      cnr                  ( ID_PERSONNEL_CNR, this, this ),
      toolbar              ( ID_PERSONNEL_TOOLBAR, this, &infoarea ),
      help                 ( ID_HELP_TABLE2, this ),
      cmdHdr               ( this, &help, &cnr ),
      helpHdr              (),
      aDeptQuery           ( deptQuery ),
      aSelects             ( true )
{
/*-----------------------------------------------------------------------------
| Attempt to load the help file                                               |
-----------------------------------------------------------------------------*/
   try
   {
      help.addLibraries( "lanchelp.hlp" );
      help.setTitle( STR_HELP_TITLE );
   }
   catch( ... )
   {}

/*-----------------------------------------------------------------------------
| Handle Drag/Drop                                                            |
-----------------------------------------------------------------------------*/
   cnr.setItemProvider( &this->provider );
   IDMHandler::enableDragDropFor( &cnr );

/*-----------------------------------------------------------------------------
| Handle command events for this frame window                                 |
| Handle help events for this frame window                                    |
 ----------------------------------------------------------------------------*/
   cmdHdr.handleEventsFor( this );
   helpHdr.handleEventsFor( this );

/*-----------------------------------------------------------------------------
| Set the application icon                                                    |
| Set the client to be the container                                          |
| Identify the offset for the infoarea strings                                |
| Set the inactive text for the infoarea                                      |
| Populate the cnr with cnr objects                                           |
| Set the application's focus and show it                                     |
 ----------------------------------------------------------------------------*/
   setIcon( ID_PERSONNEL );
   setClient( &cnr );
   infoarea.setStringTableOffset( ID_PERSONNEL_OFFSET_INFOAREA );
   infoarea.setDefaultText( ID_PERSONNEL_OFFSET_INFOAREA+ID_PERSONNEL );
   populate( bagOfIds );

/*-----------------------------------------------------------------------------
| Resize the frame window based on the minimum width of the toolbar           |
-----------------------------------------------------------------------------*/
   IRectangle
      clientRect = clientRectFor( rect() );
   moveSizeToClient( IRectangle( clientRect.bottomLeft(),
                     IPoint( clientRect.left() + toolbar.minimumSize().width(),
                     clientRect.top() ) ) );

/*-----------------------------------------------------------------------------
| Move the frame window to the best location for the display size             |
| Set the application's focus and show it                                     |
 ----------------------------------------------------------------------------*/
   IPoint
      newLocation( LFrameWindow::bestFit( this ) );
   moveTo( newLocation );
   if ( ( ! newLocation.x() ) || ( ! newLocation.y()  ) )
      maximize();
   cnr.setFocus();
   show();
}


/******************************************************************************
* Class LPersonnelWindow :: ~LPersonnelWindow - Destructor for the            *
*   personnel window.                                                         *
******************************************************************************/
LPersonnelWindow::~LPersonnelWindow()
{
/*-----------------------------------------------------------------------------
| Stop handling events.                                                       |
-----------------------------------------------------------------------------*/
   cmdHdr.stopHandlingEventsFor( this );
   helpHdr.stopHandlingEventsFor( this );
}


/******************************************************************************
* Class LPersonnelWindow :: enableSelects - Enable/disable the selection      *
*   menu items.                                                               *
******************************************************************************/
LPersonnelWindow& LPersonnelWindow::enableSelects( bool which )
{
   menubar.enableItem( ID_PERSONNEL_VIEW_SELECT, which );
   toolbar.enableSelects( which );
   aSelects = which;

   return *this;
}


/******************************************************************************
* Class LPersonnelWindow :: populate() - Populate the container with people   *
******************************************************************************/
LPersonnelWindow& LPersonnelWindow::populate( QueryIntersection& empIds )
{
/*-----------------------------------------------------------------------------
| Hide the cnr until we're finished deleting and adding all cnr objects       |
-----------------------------------------------------------------------------*/
   cnr.hide();
/*-----------------------------------------------------------------------------
| If there are employees that match the search criteria,                      |
| - Iterate each employee and create a cnr object                             |
-----------------------------------------------------------------------------*/
   for ( empIds.setFirstId();
         empIds.isValid();
         empIds.setNextId() )
   {
      LEmployeeData
         emp( empIds.getId() );
      unsigned long
         empType = ID_ICON_PERSON1;
      switch ( emp.employeeType() )
      {
         case LEmployeeData::Regular:
         {
            empType = ID_ICON_PERSON1;
            break;
         }
         case LEmployeeData::Manager:
         {
            empType = ID_ICON_PERSON2;
            break;
         }
         case LEmployeeData::Supplemental:
         {
            empType = ID_ICON_PERSON3;
            break;
         }
         case LEmployeeData::Unemployed:
         {
            empType = ID_ICON_PERSON4;
            break;
         }
         default:
         {
            empType = ID_ICON_PERSON_UNKNOWN;
            break;
         }
      }
      LPersonnelCnrObject
        *pCnrObject = new LPersonnelCnrObject( empType, emp );

      cnr.addObject( pCnrObject );
   }

/*-----------------------------------------------------------------------------
| Arrange the icons                                                           |
| Reshow it                                                                   |
-----------------------------------------------------------------------------*/
   cnr.arrangeIconView();
   cnr.show();

   return *this;
}


/******************************************************************************
* Class LPersonnelCnr :: LPersonnelCnr - Constructor for the personnel        *
*   container.                                                                *
*                                                                             *
* Define yourself as an IContainerControl                                     *
* Create the various container columns                                        *
* Define a help window as NULL                                                *
* Define a popup menu as NULL                                                 *
* Define the last popup menu container object as NULL                         *
******************************************************************************/
LPersonnelCnr::LPersonnelCnr( unsigned long id, LPersonnelWindow* parent,
                              LPersonnelWindow* owner, IRectangle location )
     :IContainerControl    ( id, parent, owner, location,
                             IContainerControl::extendedSelection ),
      colIcon              ( IContainerColumn::isIcon ),
      colIconText          ( IContainerColumn ::isIconViewText ),
      colLastName          ( ICONTAINERCOLUMN_OFFSETOF( LPersonnelCnrObject, theEmployee.theLastName ) ),
      colFirstName         ( ICONTAINERCOLUMN_OFFSETOF( LPersonnelCnrObject, theEmployee.theFirstName ) ),
      colMiddleInitial     ( ICONTAINERCOLUMN_OFFSETOF( LPersonnelCnrObject, theEmployee.theMiddleInitial ) ),
      colEmployeeNumber    ( ICONTAINERCOLUMN_OFFSETOF( LPersonnelCnrObject, theEmployee.theEmployeeNum ) ),
      colInternalPhone     ( ICONTAINERCOLUMN_OFFSETOF( LPersonnelCnrObject, theEmployee.theInternalPhone ) ),
      colExternalPhone     ( ICONTAINERCOLUMN_OFFSETOF( LPersonnelCnrObject, theEmployee.theExternalPhone ) ),
      colInternalAddress   ( ICONTAINERCOLUMN_OFFSETOF( LPersonnelCnrObject, theEmployee.theInternalAddr ) ),
      colExternalAddress   ( ICONTAINERCOLUMN_OFFSETOF( LPersonnelCnrObject, theEmployee.theExternalAddr ) ),
      colRoom              ( ICONTAINERCOLUMN_OFFSETOF( LPersonnelCnrObject, theEmployee.theRoom ) ),
      colBuilding          ( ICONTAINERCOLUMN_OFFSETOF( LPersonnelCnrObject, theEmployee.theBuilding ) ),
      colDepartment        ( ICONTAINERCOLUMN_OFFSETOF( LPersonnelCnrObject, theEmployee.theDeptName ) ),
      colManagerNumber     ( ICONTAINERCOLUMN_OFFSETOF( LPersonnelCnrObject, theEmployee.theManagerNum ) ),
      colManagerName       ( ICONTAINERCOLUMN_OFFSETOF( LPersonnelCnrObject, theEmployee.theManagerName ) ),
      helpWin              ( NULL ),
      popm                 ( NULL ),
      ptheLastPopupMenuObject ( NULL )
{
/*-----------------------------------------------------------------------------
| Start handling container events for the container                           |
| Start handling container menu events for the container                      |
-----------------------------------------------------------------------------*/
   ICnrHandler::handleEventsFor( this );
   ICnrMenuHandler::handleEventsFor( this );

/*-----------------------------------------------------------------------------
| Add the cnr columns to the cnr                                              |
-----------------------------------------------------------------------------*/
   addColumn( &colIcon );
   addColumn( &colIconText );
   addColumn( &colLastName );
   addColumn( &colFirstName );
   addColumn( &colMiddleInitial );
   addColumn( &colEmployeeNumber );
   addColumn( &colInternalPhone );
   addColumn( &colExternalPhone );
   addColumn( &colInternalAddress );
   addColumn( &colExternalAddress );
   addColumn( &colRoom );
   addColumn( &colBuilding );
   addColumn( &colDepartment );
   addColumn( &colManagerNumber );
   addColumn( &colManagerName );

/*-----------------------------------------------------------------------------
| Set the cnr column headings                                                 |
-----------------------------------------------------------------------------*/
   colIconText.setHeadingText( STR_PERSON );
   colLastName.setHeadingText( STR_LASTNAME );
   colFirstName.setHeadingText( STR_FIRSTNAME );
   colMiddleInitial.setHeadingText( STR_MI );
   colEmployeeNumber.setHeadingText( STR_EMPLOYEENUM );
   colInternalPhone.setHeadingText( STR_INTPHONE );
   colExternalPhone.setHeadingText( STR_EXTPHONE );
   colInternalAddress.setHeadingText( STR_INTADDR );
   colExternalAddress.setHeadingText( STR_EXTADDR );
   colRoom.setHeadingText( STR_ROOM );
   colBuilding.setHeadingText( STR_BUILDING );
   colDepartment.setHeadingText( STR_DEPT );
   colManagerNumber.setHeadingText( STR_MGRNUM );
   colManagerName.setHeadingText( STR_MGR );

/*-----------------------------------------------------------------------------
| Define column separators for details view                                   |
-----------------------------------------------------------------------------*/
   colLastName.showSeparators();
   colFirstName.showSeparators();
   colMiddleInitial.showSeparators();
   colEmployeeNumber.showSeparators();
   colInternalPhone.showSeparators();
   colExternalPhone.showSeparators();
   colInternalAddress.showSeparators();
   colExternalAddress.showSeparators();
   colRoom.showSeparators();
   colBuilding.showSeparators();
   colDepartment.showSeparators();
   colManagerNumber.showSeparators();
   colManagerName.showSeparators();

/*-----------------------------------------------------------------------------
| Delete cnr objects on closing of the container                              |
-----------------------------------------------------------------------------*/
   setDeleteObjectsOnClose();

/*-----------------------------------------------------------------------------
| Regardless of the font size, display the same number of characters          |
| for the icon text in details view                                           |
-----------------------------------------------------------------------------*/
   IFont
      cnrFont( this );
   setDetailsViewSplit( &colIconText,
                        iconSize().width() +
                        cnrFont.avgCharWidth() * ID_PERSONNEL_CNR_TITLE_WIDTH );

/*-----------------------------------------------------------------------------
| Set the container title                                                     |
| Show the container title                                                    |
| Arrange the icons                                                           |
| Show the container                                                          |
-----------------------------------------------------------------------------*/
   setTitle( STR_PERSONNEL_CNR_TITLE );
   showTitle();
   arrangeIconView();
   show();
}


/******************************************************************************
* Class LPersonnelCnr :: ~LPersonnelCnr - Destructor                          *
******************************************************************************/
LPersonnelCnr::~LPersonnelCnr()
{
/*-----------------------------------------------------------------------------
| Delete the help window.                                                     |
-----------------------------------------------------------------------------*/
   delete helpWin;
}


/******************************************************************************
* Class LPersonnelCnr :: makePopUpMenu()                                      *
*   Create popup menus based on whether is over cnr or cnr object.            *
******************************************************************************/
bool LPersonnelCnr::makePopUpMenu( IMenuEvent& evt )
{
/*-----------------------------------------------------------------------------
| Get the object with the last popup menu                                     |
-----------------------------------------------------------------------------*/
   ptheLastPopupMenuObject = (LPersonnelCnrObject*) popupMenuObject();

/*-----------------------------------------------------------------------------
| Create a popup menu based on the object's type                              |
| Disable the select menu item if it exists for this menu.                    |
| Automatically delete the popup menu when no longer needed                   |
| Show the popup menu at the mouse position                                   |
-----------------------------------------------------------------------------*/
   bool
      hasSelectItem = true;

   if ( lastPopupMenuObject() )
   {
      popm =
         new IPopUpMenu ( ID_PERSONNEL_OBJECT_POP, evt.controlWindow() );
      hasSelectItem = false;
   }
   else
      popm =
         new IPopUpMenu ( ID_PERSONNEL_POP, owner() );

   if ( hasSelectItem &&
      !((LPersonnelWindow*)owner())->selectsAllowed() )
      popm->enableItem( ID_PERSONNEL_VIEW_SELECT, false );
   popm->setAutoDeleteObject();
   popm->show( evt.mousePosition() );

   return true;
}


/******************************************************************************
* Class LPersonnelCnr :: enter() - Process the enter key on a container object*
******************************************************************************/
bool LPersonnelCnr::enter( ICnrEnterEvent& evt )
{
/*---------------------------------------------------------------------------
| If the user pressed enter on a cnr object, send an open message           |
---------------------------------------------------------------------------*/
   if ( evt.validObject() )
   {
      ptheLastPopupMenuObject = (LPersonnelCnrObject*) evt.object();
      postEvent( IWindow::command, ID_PERSONNEL_SELECTED_OPEN );
   }

   return true;
}


/******************************************************************************
* Class LPersonnelCnr :: help() - Process the help key over a container.      *
******************************************************************************/
bool LPersonnelCnr::help( ICnrHelpEvent& evt )
{
   delete helpWin;
   helpWin = IHelpWindow::helpWindow( this );
   if ( helpWin )
      helpWin->show( IResourceId( ID_PERSONNEL_C ) );

   return true;
}

/******************************************************************************
* Class LPersonnelCnrObject :: LPersonnelCnrObject - Constructor for          *
*   container object given an existing object.                                *
******************************************************************************/
LPersonnelCnrObject::LPersonnelCnrObject( const LPersonnelCnrObject& cnrobj )
     :LCnrObject           ( (const LCnrObject&) cnrobj ),
      theEmployee          ( cnrobj.employeeRecord() )
{}


/****************************************************************************
* Class LPersonnelCnrObject :: LPersonnelCnrObject - Constructor for        *
*   container object given an employee.                                     *
****************************************************************************/
LPersonnelCnrObject::LPersonnelCnrObject( unsigned long icon,
                                          const LEmployeeData& employee )
     :LCnrObject           ( IString( employee.lastName() ) + ", " +
                             employee.firstName(), icon ),
      theEmployee          ( employee )
{}


/******************************************************************************
* Class LPersonnelCnrObject :: ~LPersonnelCnrObject - Destructor              *
******************************************************************************/
LPersonnelCnrObject::~LPersonnelCnrObject()
{}


/******************************************************************************
* Class LPersonnelToolBar :: LPersonnelToolBar - Constructor for toolbar      *
*   given a resource id                                                       *
*                                                                             *
* Define yourself as an IToolBar                                              *
* Create the various IToolBarButtons                                          *
* Create flyover help                                                         *
* Create flyover help handler                                                 *
******************************************************************************/
LPersonnelToolBar::LPersonnelToolBar( unsigned long id, IFrameWindow* owner,
                                      ITextControl* infoarea )
     :IToolBar             ( id, owner, IToolBar::aboveClient, false,
                             IToolBar::classDefaultStyle
                             & ~IToolBar::buttonBitmapVisible
                             | IToolBar::buttonBitmapAndTextVisible ),
      openButton           ( ID_PERSONNEL_SELECTED_OPEN, this, this ),
      createButton         ( ID_PERSONNEL_SELECTED_CREATE, this, this ),
      transferButton       ( ID_PERSONNEL_SELECTED_TRANSFER, this, this, IRectangle(),
                             IToolBarButton::defaultStyle()
                             | IToolBarButton::transparentBitmap ),
      helpButton           ( ID_PERSONNEL_HELP_INDEX, this, this ),
      deleteButton         ( ID_PERSONNEL_SELECTED_DELETE, this, this),
      iconButton           ( ID_PERSONNEL_VIEW_OPEN_ICON, this, this ),
      treeButton           ( ID_PERSONNEL_VIEW_OPEN_TREE, this, this ),
      detailsButton        ( ID_PERSONNEL_VIEW_OPEN_DETAILS, this, this ),
      selectAllButton      ( ID_PERSONNEL_VIEW_SELECT_ALL, this, this ),
      deselectAllButton    ( ID_PERSONNEL_VIEW_SELECT_DE, this, this ),
      sortAscButton        ( ID_PERSONNEL_VIEW_SORT_ASC, this, this ),
      sortDescButton       ( ID_PERSONNEL_VIEW_SORT_DESC, this, this ),
      arrangeButton        ( ID_PERSONNEL_VIEW_ARRANGE, this, this ),
      flyText              ( ID_PERSONNEL_FLYTEXT, this ),
      flyHelpHdr           ( &flyText, infoarea, 0, 0 )
{
/*-----------------------------------------------------------------------------
| For these buttons, use the standard bitmaps for these buttons.              |
-----------------------------------------------------------------------------*/
   openButton.setBitmap( IC_ID_OPEN );
   createButton.setBitmap( IC_ID_NEW );
   helpButton.setBitmap( IC_ID_HELP );
   deleteButton.setBitmap( IC_ID_DELETE );
   selectAllButton.setBitmap( IC_ID_SELECTALL );
   deselectAllButton.setBitmap( IC_ID_DESELECTALL );
   sortAscButton.setBitmap( IC_ID_SORTUP );
   sortDescButton.setBitmap( IC_ID_SORTDOWN );
   arrangeButton.setBitmap( IC_ID_RIGHTALIGNOBJ );


/*-----------------------------------------------------------------------------
| Add the buttons to the toolbar.                                             |
-----------------------------------------------------------------------------*/
   addAsLast( &openButton );
   addAsLast( &createButton );
   addAsLast( &transferButton );
   addAsLast( &deleteButton );
   addAsLast( &iconButton, true );
   addAsLast( &treeButton );
   addAsLast( &detailsButton );
   addAsLast( &selectAllButton, true );
   addAsLast( &deselectAllButton );
   addAsLast( &sortAscButton, true );
   addAsLast( &sortDescButton );
   addAsLast( &arrangeButton );
   addAsLast( &helpButton, true );

/*-----------------------------------------------------------------------------
| Identify the flytext string table offset for the fly-over help              |
| Identify the long string table offset for the fly-over help                 |
| Set the missing text to blank                                               |
 ----------------------------------------------------------------------------*/
   flyHelpHdr.setFlyTextStringTableOffset( ID_PERSONNEL_OFFSET_FLYTEXT );
   flyHelpHdr.setLongStringTableOffset( ID_PERSONNEL_OFFSET_INFOAREA );
   flyHelpHdr.setDefaultText( ID_PERSONNEL_OFFSET_INFOAREA+ID_PERSONNEL );
   flyHelpHdr.handleEventsFor( this );
}


/******************************************************************************
* Class LPersonnelToolBar :: enableSelects - Enable/disable the selection     *
*   toolbar buttons.                                                          *
******************************************************************************/
LPersonnelToolBar& LPersonnelToolBar::enableSelects( bool which )
{
   selectAllButton.enable( which );
   deselectAllButton.enable( which );
   return *this;
}


/******************************************************************************
* Class LPersonnelWindowCommandHandler :: LPersonnelWindowCommandHandler -    *
*  Constructor for handling command events for the frame window               *
******************************************************************************/
LPersonnelWindowCommandHandler::LPersonnelWindowCommandHandler
                           ( LPersonnelWindow* owner,
                             IHelpWindow* helpWin,
                             LPersonnelCnr* cnrCtl )
     :pOwner( owner ),
      pHelp( helpWin ),
      pCnr( cnrCtl )
{}


/******************************************************************************
* Class LPersonnelWindowCommandHandler :: ~LPersonnelWindowCommandHandler -   *
*   Destructor                                                                *
******************************************************************************/
LPersonnelWindowCommandHandler::~LPersonnelWindowCommandHandler()
{}


/******************************************************************************
* Class LPersonnelWindowCommandHandler :: command() - Handle the command event*
******************************************************************************/
bool LPersonnelWindowCommandHandler::command( ICommandEvent& evt )
{
   bool
      useObjectCollection = true;
   unsigned long
      cmdId = evt.commandId ();

/*-----------------------------------------------------------------------------
| Get the last popup menu object                                              |
| Get a cursor for all the selected items in the cnr                          |
 ----------------------------------------------------------------------------*/
   LPersonnelCnrObject
     *pcurObject = pCnr->lastPopupMenuObject();
   IContainerControl::ObjectCursor
      cnrObjectsSelected( *pCnr, IContainerObject::selected );

   cnrObjectsSelected.setToFirst();
   switch( cmdId )
   {
/*-----------------------------------------------------------------------------
| If the object with the last popup menu is not selected,                     |
|  do not use all selected cnr objects.                                       |
| Else fall through to the ID_PERSONNEL_SELECTED_OPEN.                        |
-----------------------------------------------------------------------------*/
      case ID_PERSONNEL_OBJECT_POP_OPEN:
      {
         if ( pcurObject && !pCnr->isSelected( pcurObject ) )
            useObjectCollection = false;
      }

      case ID_PERSONNEL_SELECTED_OPEN:
      {
         if ( useObjectCollection )
         {
/*-----------------------------------------------------------------------------
| Open each selected object.                                                  |
 ----------------------------------------------------------------------------*/
            for ( cnrObjectsSelected.setToFirst();
                  cnrObjectsSelected.isValid();
                  cnrObjectsSelected.setToNext() )
            {
               LPersonnelCnrObject
                  *pcurObject = (LPersonnelCnrObject *) cnrObjectsSelected.current();
               if ( pcurObject )
                  openAction( pcurObject );
            }
         }
         else
         {
/*-----------------------------------------------------------------------------
| Open only the current selected object.                                      |
-----------------------------------------------------------------------------*/
            if ( pcurObject )
               openAction( pcurObject );
         }
         break;
      }

/*-----------------------------------------------------------------------------
| If the object with the last popup menu and is not selected,                 |
|  do not use all selected cnr objects.                                       |
| Else fall through to the ID_PERSONNEL_SELECTED_DELETE.                      |
-----------------------------------------------------------------------------*/
      case ID_PERSONNEL_OBJECT_POP_CREATE:
      {
         if ( pcurObject && !pCnr->isSelected( pcurObject ) )
            useObjectCollection = false;
      }

      case ID_PERSONNEL_SELECTED_CREATE:
      {
         if ( useObjectCollection )
         {
/*-----------------------------------------------------------------------------
| Create each selected object.                                                |
 ----------------------------------------------------------------------------*/
            for ( cnrObjectsSelected.setToFirst();
                  cnrObjectsSelected.isValid();
                 cnrObjectsSelected.setToNext() )
            {
               LPersonnelCnrObject
                 *pcurObject = (LPersonnelCnrObject *) cnrObjectsSelected.current();
               if ( pcurObject )
                  createAction( pcurObject );
            }
         }
         else
         {
/*-----------------------------------------------------------------------------
| Create only the current selected object.                                    |
-----------------------------------------------------------------------------*/
            if ( pcurObject )
               createAction( pcurObject );
         }
         break;
      }

/*-----------------------------------------------------------------------------
| If the object with the last popup menu and is not selected,                 |
|  do not use all selected cnr objects.                                       |
| Else fall through to the ID_PERSONNEL_SELECTED_TRANSFER.                    |
-----------------------------------------------------------------------------*/
      case ID_PERSONNEL_OBJECT_POP_TRANSFER:
      {
         if ( pcurObject && !pCnr->isSelected( pcurObject ) )
            useObjectCollection = false;
      }

      case ID_PERSONNEL_SELECTED_TRANSFER:
      {
         if ( useObjectCollection )
         {
/*-----------------------------------------------------------------------------
| Transfer each selected object.                                              |
 ----------------------------------------------------------------------------*/
            for ( cnrObjectsSelected.setToFirst();
                  cnrObjectsSelected.isValid();
                  cnrObjectsSelected.setToNext() )
            {
               LPersonnelCnrObject
                  *pcurObject = (LPersonnelCnrObject *) cnrObjectsSelected.current();
               if ( pcurObject )
                  transferAction( pcurObject );
            }
         }
         else
         {
/*-----------------------------------------------------------------------------
| Transfer only the current selected object.                                  |
-----------------------------------------------------------------------------*/
            if ( pcurObject )
               transferAction( pcurObject );
         }
         break;
      }

/*-----------------------------------------------------------------------------
| If the object with the last popup menu and is not selected,                 |
|  do not use all selected cnr objects.                                       |
| Else fall through to the ID_PERSONNEL_SELECTED_DELETE.                      |
-----------------------------------------------------------------------------*/
      case ID_PERSONNEL_OBJECT_POP_DELETE:
      {
         if ( pcurObject && !pCnr->isSelected( pcurObject ) )
            useObjectCollection = false;
      }

      case ID_PERSONNEL_SELECTED_DELETE:
      {
         if ( useObjectCollection )
         {
/*-----------------------------------------------------------------------------
| Delete each selected object.                                                |
-----------------------------------------------------------------------------*/
            do
            {
               LPersonnelCnrObject
                  *pcurObject = (LPersonnelCnrObject *)cnrObjectsSelected.current();
               if ( pcurObject )
               {
                  bool
                     wasDeleted = deleteAction( pcurObject );
                  if ( !wasDeleted )
                     try
                     {
                       pCnr->setSelected( pcurObject, false );
                     }
                     catch(...)
                     {
                     }
               }
               cnrObjectsSelected.setToFirst();
            }
            while ( cnrObjectsSelected.isValid() && !pCnr->isTreeIconView() );

         }
         else
         {
/*-----------------------------------------------------------------------------
| Delete only the current selected object.                                    |
-----------------------------------------------------------------------------*/
            if ( pcurObject )
               deleteAction( pcurObject );
         }
         break;
      }

/*-----------------------------------------------------------------------------
| Show the cnr as details view                                                |
-----------------------------------------------------------------------------*/
      case ID_PERSONNEL_VIEW_OPEN_DETAILS:
      {
         pCnr->showDetailsView();
         pOwner->enableSelects();
         break;
      }

/*-----------------------------------------------------------------------------
| Show the cnr as tree view                                                   |
-----------------------------------------------------------------------------*/
      case ID_PERSONNEL_VIEW_OPEN_TREE:
      {
         pCnr->showTreeIconView();
         pOwner->enableSelects( false );
         break;
      }

/*-----------------------------------------------------------------------------
| Show the cnr as icon view                                                   |
-----------------------------------------------------------------------------*/
      case ID_PERSONNEL_VIEW_OPEN_ICON:
      {
         pCnr->showIconView();
         pOwner->enableSelects();
         break;
      }

/*-----------------------------------------------------------------------------
| Select all cnr objects by selecting each cnr object                         |
-----------------------------------------------------------------------------*/
      case ID_PERSONNEL_VIEW_SELECT_ALL:
      {
         IContainerControl::ObjectCursor
            objCursor( *pCnr );
         for ( objCursor.setToFirst();
               objCursor.isValid();
               objCursor.setToNext() )
         {
            pCnr->setSelected( objCursor.current() );
         }
         break;
      }

/*-----------------------------------------------------------------------------
| Select all cnr objects by deselecting each cnr object                       |
-----------------------------------------------------------------------------*/
      case ID_PERSONNEL_VIEW_SELECT_DE:
      {
         IContainerControl::ObjectCursor
            objCursor( *pCnr );
         for ( objCursor.setToFirst();
               objCursor.isValid();
               objCursor.setToNext() )
         {
            try
            {
              pCnr->setSelected( objCursor.current(), false );
            }
            catch(...)
            {
            }
         }
         break;
      }

/*-----------------------------------------------------------------------------
| Arrange the cnr objects for icon view                                       |
-----------------------------------------------------------------------------*/
      case ID_PERSONNEL_VIEW_ARRANGE:
      {
         pCnr->arrangeIconView();
         break;
      }

/*-----------------------------------------------------------------------------
| Sort the cnr objects ascending by their icon text                           |
-----------------------------------------------------------------------------*/
      case ID_PERSONNEL_VIEW_SORT_ASC:
      {
         pCnr->sortByIconText();
         pCnr->arrangeIconView();
         break;
      }

/*-----------------------------------------------------------------------------
| Sort the cnr objects descending by their icon text                          |
-----------------------------------------------------------------------------*/
      case ID_PERSONNEL_VIEW_SORT_DESC:
      {
         pCnr->sortByIconText( false );
         pCnr->arrangeIconView();
         break;
      }

/*-----------------------------------------------------------------------------
| Show help index                                                             |
-----------------------------------------------------------------------------*/
      case ID_PERSONNEL_HELP_INDEX:
      {
         pHelp->show( IHelpWindow::index );
         break;
      }

/*-----------------------------------------------------------------------------
| Show general help                                                           |
-----------------------------------------------------------------------------*/
      case ID_PERSONNEL_HELP_GENERAL:
      {
         pHelp->show( IHelpWindow::general );
         break;
      }

/*-----------------------------------------------------------------------------
| Show using help                                                             |
-----------------------------------------------------------------------------*/
      case ID_PERSONNEL_HELP_USING:
      {
         pHelp->show( IHelpWindow::usingHelp );
         break;
      }

/*-----------------------------------------------------------------------------
| Show product information                                                    |
-----------------------------------------------------------------------------*/
      case ID_PERSONNEL_HELP_PRODUCT:
      {
         LProdInfoDialog prodInfo( pOwner );
         prodInfo.showModally();
        break;
      }

/*-----------------------------------------------------------------------------
| Close the frame window                                                      |
-----------------------------------------------------------------------------*/
      case ID_PERSONNEL_VIEW_CLOSE:
      {
         pOwner->close();
         break;
      }

      default:
      {
         return false;
      }
    }

    return true;
}


/******************************************************************************
* Class LPersonnelWindowCommandHandler :: openAction() - Open the person.     *
******************************************************************************/
LPersonnelWindowCommandHandler& LPersonnelWindowCommandHandler::openAction
                           ( LPersonnelCnrObject* pObject )
{
/*-----------------------------------------------------------------------------
| Get the employee's record                                                   |
| Set the object as open                                                      |
| Show an information window for the employee                                 |
-----------------------------------------------------------------------------*/
   LEmployeeData
      tempData( pObject->employeeRecord() );
   pObject->setOpen();
   LInfoWindow
     *pEmployeeWindow = new LInfoWindow( ID_INFO_WINDOW, 0, pOwner,
                                         IPoint( 100, 100 ),
                                         pObject,
                                         tempData,
                                         false );
   pEmployeeWindow->setAutoDeleteObject( true );

   return *this;
}


/******************************************************************************
* Class LPersonnelWindowCommandHandler :: createAction() - Create a person.   *
******************************************************************************/
LPersonnelWindowCommandHandler& LPersonnelWindowCommandHandler::createAction
                           ( LPersonnelCnrObject* pObject )
{
/*-----------------------------------------------------------------------------
| Start an information window for the new employee                            |
-----------------------------------------------------------------------------*/
   LEmployeeData
      tempData( "" );
   LInfoWindow
     *pEmployeeWindow = new LInfoWindow( ID_INFO_WINDOW, 0, pOwner,
                                         IPoint( 100, 100 ),
                                         pObject,
                                         tempData,
                                         false );
   pEmployeeWindow->setAutoDeleteObject( true );

   return *this;
}


/******************************************************************************
* Class LPersonnelWindowCommandHandler :: transferAction() - Transfer a       *
*   person.                                                                   *
******************************************************************************/
LPersonnelWindowCommandHandler& LPersonnelWindowCommandHandler::transferAction
                           ( LPersonnelCnrObject* pObject )
{
/*-----------------------------------------------------------------------------
| Get the employee's record                                                   |
-----------------------------------------------------------------------------*/
   LEmployeeData
      empData = pObject->employeeRecord();
   IString
      person = IString("'") + empData.firstName() + " " +
               empData.lastName() + "'";
   IString
      curDept = IString("'") + empData.department() + "'";

/*-----------------------------------------------------------------------------
| Ask the user for the new department name                                    |
-----------------------------------------------------------------------------*/
   LAskUser
      askUser( ID_ASKUSER, IWindow::desktopWindow(), pOwner,
               IApplication::current().userResourceLibrary().
               loadString( STR_TRANSFER_MSG1 ) + person,
               IApplication::current().userResourceLibrary().
               loadString( STR_TRANSFER_MSG2 ) +
               curDept + ".",
               IApplication::current().userResourceLibrary().
               loadString( STR_TRANSFER_MSG3 ) );


/*-----------------------------------------------------------------------------
| If the user pressed OK                                                      |
| - Get the text the user specified in the dialog                             |
| - Change the employee's department to the user specified text               |
| - Put the change to the database                                            |
-----------------------------------------------------------------------------*/
   if ( askUser.pressedOk() )
   {
      IString
         newDept = askUser.text();
      if ( newDept.length() )
      {
         empData.setDepartment( newDept );
         empData.save( empData.employeeNumber() );
         curDept = IString("'") + newDept + "'";

         IMessageBox
            msg( pOwner );
          msg.show( person + IApplication::current().userResourceLibrary().
                    loadString( STR_TRANSFER_MSG4 ) +
                    curDept + ".",
                    IMessageBox::informationIcon );
      }
   }

   return *this;
}


/******************************************************************************
* Class LPersonnelWindowCommandHandler :: deleteAction() - Fire a person!     *
******************************************************************************/
bool LPersonnelWindowCommandHandler::deleteAction
                           ( LPersonnelCnrObject* pObject )
{
   bool
      retCode = false;

/*-----------------------------------------------------------------------------
| Ask if the user really wants to delete or just set to inactive.             |
-----------------------------------------------------------------------------*/
   IMessageBox
      msgBox( pOwner );
   IMessageBox::Response
      response = msgBox.show( IResourceId( STR_PERSONNEL_DELETE_MSG ),
                              IMessageBox::warningIcon |
                              IMessageBox::yesNoCancelButton,
                              ID_PERSONNEL_DELETE_HELP );

/*-----------------------------------------------------------------------------
| Get the employee's record                                                   |
-----------------------------------------------------------------------------*/
   LEmployeeData
      empData = pObject->employeeRecord();
   IString
      person = empData.firstName() + " " +
               empData.lastName();

/*-----------------------------------------------------------------------------
| Delete the employee                                                         |
| - Delete the employee from the database                                     |
| - Delete the cnr object                                                     |
-----------------------------------------------------------------------------*/
   if ( response == IMessageBox::no )
   {
      LDeleteEmployee
         deleteEmp;
      deleteEmp.deleteFromDataBase( empData.employeeNumber() );
      delete pObject;
      msgBox.show( STR_PERSONNEL_DELETED_MSG,
                   IMessageBox::okButton |
                   IMessageBox::informationIcon );
      retCode = true;
   }

/*-----------------------------------------------------------------------------
| Set the employee to inactive                                                |
| - Get the employee's status data                                            |
| - Put the status data back with active set to false                         |
-----------------------------------------------------------------------------*/
   else if ( response == IMessageBox::yes )
   {
      LStatusData
         statData( empData.employeeNumber() );
      statData.save( empData.employeeNumber(),
                     statData.statusRate(),
                     statData.statusStart(),
                     statData.statusEnd(),
                     false );
      msgBox.show( STR_PERSONNEL_INACTIVE_MSG,
                   IMessageBox::okButton
                   | IMessageBox::informationIcon );
      retCode = false;
   }

   return retCode;
}


/******************************************************************************
* Class LPersonnelWindowHelpHandler :: LPersonnelWindowHelpHandler -          *
*   Constructor for handling help events.                                     *
******************************************************************************/
LPersonnelWindowHelpHandler::LPersonnelWindowHelpHandler()
{}


/******************************************************************************
* Class LPersonnelWindowHelpHandler :: ~LPersonnelWindowHelpHandler -         *
*   Destructor                                                                *
******************************************************************************/
LPersonnelWindowHelpHandler::~LPersonnelWindowHelpHandler()
{}


/******************************************************************************
* Class LPersonnelHelpWindowHelpHandler :: keysHelpId()                       *
*   Handle the keys help request event.                                       *
*   This overrides the default provided by library.                           *
******************************************************************************/
bool LPersonnelWindowHelpHandler::keysHelpId( IEvent& evt )
{
   evt.setResult( ID_PERSONNEL_HELP_KEYS_PANEL);
   return true;
}
