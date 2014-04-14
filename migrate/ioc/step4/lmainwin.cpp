/******************************************************************************
* FILE NAME: lmainwin.cpp                                                     *
*                                                                             *
* Classes:                                                                    *
*   LMainWindow                                                               *
*   LMainCnr                                                                  *
*   LMainCnrObject                                                            *
*   LMainWindowCommandHandler                                                 *
*   LMainWindowHelpHandler                                                    *
*                                                                             *
* COPYRIGHT:                                                                  *
*   Licensed Materials - Property of IBM                                      *
*   (C) Copyright IBM Corporation 1992, 1995                                  *
*   All Rights Reserved                                                       *
*   US Government Users Restricted Rights - Use, duplication, or disclosure   *
*   restricted by GSA ADP Schedule Contract with IBM Corp.                    *
******************************************************************************/

#ifndef _IBASE_                         //Make sure ibase.hpp is included
  #include <ibase.hpp>                  //  since that is where IC_<environ>
#endif                                  //  is defined.
#include "lmainwin.hpp"
#include "lgoodies.hpp"

/******************************************************************************
* Class LMainWindow :: LMainWindow - Constructor for the main window          *
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
******************************************************************************/
LMainWindow::LMainWindow()
     :IFrameWindow         ( ID_MAIN ),
      title                ( this, STR_MAIN_TITLE, STR_MAIN_TITLE2 ),
      menubar              ( ID_MAIN, this ),
      infoarea             ( this ),
      cnr                  ( ID_MAIN_CNR, this, this ),
      toolbar              ( ID_MAIN_TOOLBAR, this, &infoarea ),
      help                 ( ID_HELP_TABLE, this ),
      cmdHdr               ( this, &help, &cnr ),
      helpHdr              (),
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
   {
      IMessageBox
         msgBox( this );
      msgBox.show( STR_HELP_NOT_FOUND, IMessageBox::warning );
   }

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
| Set the application's focus and show it                                     |
 ----------------------------------------------------------------------------*/
   setIcon( ID_MAIN );
   setClient( &cnr );
   infoarea.setStringTableOffset( ID_MAIN_OFFSET_INFOAREA );
   infoarea.setInactiveText( ID_MAIN_OFFSET_INFOAREA+ID_MAIN );

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
   if ( ( ! newLocation.x() ) || ( ! newLocation.y() )  )
      maximize();
   setFocus().show();
}


/******************************************************************************
* Class LMainWindow :: ~LMainWindow - Destructor for the main window          *
******************************************************************************/
LMainWindow::~LMainWindow()
{
/*-----------------------------------------------------------------------------
| Stop handling events.                                                       |
-----------------------------------------------------------------------------*/
   cmdHdr.stopHandlingEventsFor( this );
   helpHdr.stopHandlingEventsFor( this );
}


/******************************************************************************
* Class LMainWindow :: enableSelects - Enable/disable the selection           *
*   menu items.                                                               *
******************************************************************************/
LMainWindow& LMainWindow::enableSelects( Boolean which )
{
   menubar.enableItem( ID_MAIN_VIEW_SELECT, which );
   toolbar.enableSelects( which );
   aSelects = which;
   return *this;
}


/******************************************************************************
* Class LMainCnr :: LMainCnr - Constructor for the main container.            *
*                                                                             *
* Create yourself as an IContainerControl                                     *
* Create the container columns.                                               *
* Define a help window as NULL.                                               *
* Define a poup menu as NULL.                                                 *
* Define the last popup menu object as NULL.                                  *
* Set the object count to 0.                                                  *
******************************************************************************/
LMainCnr::LMainCnr( unsigned long id, LMainWindow* parent,
                    LMainWindow* owner, IRectangle location )
     :IContainerControl    ( id, parent, owner, location,
                             IContainerControl::extendedSelection ),
      colIcon              ( IContainerColumn::isIcon ),
      colIconText          ( IContainerColumn::isIconViewText ),
      colDesc              ( LMainCnrObject::descOffset() ),
      helpWin              ( NULL ),
      popm                 ( NULL ),
      ptheLastPopupMenuObject ( NULL ),
      objCount             ( 0 )
{
/*-----------------------------------------------------------------------------
| Start handling container events for the container                           |
| Start handling container menu events for the container                      |
-----------------------------------------------------------------------------*/
   ICnrHandler::handleEventsFor( this );
   ICnrMenuHandler::handleEventsFor( this );

/*-----------------------------------------------------------------------------
| Populate the container with objects                                         |
-----------------------------------------------------------------------------*/
   populate();

/*-----------------------------------------------------------------------------
| Add the cnr columns to the cnr                                              |
-----------------------------------------------------------------------------*/
   addColumn( &colIcon );
   addColumn( &colIconText );
   addColumn( &colDesc );

/*-----------------------------------------------------------------------------
| Set the cnr column headings                                                 |
-----------------------------------------------------------------------------*/
   colIconText.setHeadingText( STR_TITLE );
   colDesc.setHeadingText( STR_DESC );

/*-----------------------------------------------------------------------------
| Delete cnr objects on closing of the container                              |
-----------------------------------------------------------------------------*/
   setDeleteObjectsOnClose();

/*-----------------------------------------------------------------------------
| Regardless of the font size, display the same number of characters          |
|  for the icon text in details view                                          |
-----------------------------------------------------------------------------*/
   IFont
      cnrFont( this );
   setDetailsViewSplit( &colIconText,
                        iconSize().width() +
                        cnrFont.avgCharWidth() * ID_MAIN_CNR_TITLE_WIDTH );

/*-----------------------------------------------------------------------------
| Arrange the icons                                                           |
| Show the cnr title and show it                                              |
-----------------------------------------------------------------------------*/
   arrangeIconView();
   showTitle();
   show();
}


/******************************************************************************
* Class LMainCnr :: ~LMainCnr - Destructor                                    *
******************************************************************************/
LMainCnr::~LMainCnr()
{
/*-----------------------------------------------------------------------------
| Delete the help window.                                                     |
-----------------------------------------------------------------------------*/
   delete helpWin;
}


/******************************************************************************
* Class LMainCnr :: populate() - Populate with container objects.             *
******************************************************************************/
LMainCnr& LMainCnr::populate()
{
/*-----------------------------------------------------------------------------
| Hide the cnr until we're finished deleting and adding all cnr objects       |
-----------------------------------------------------------------------------*/
   hide();
   deleteAllObjects();
   objCount = 0;

/*-----------------------------------------------------------------------------
| Add the "Query Personnel" cnr object                                        |
-----------------------------------------------------------------------------*/
   pCnrObject[ ID_MAIN_CNROBJECT + ++objCount ] =
      new LMainCnrObject( ID_ICON_QUERY,
                          IResourceId( STR_QUERY_PERSONNEL_OBJECT ),
                          LMainCnrObject::personnel,
                          IResourceId( STR_QUERY_PERSONNEL_DESC ) );
   addObject( pCnrObject[ ID_MAIN_CNROBJECT + objCount ] );

/*-----------------------------------------------------------------------------
| If there is saved query data,                                               |
| - Iterate each saved query and create a cnr object                          |
-----------------------------------------------------------------------------*/
   QueryQry
      qdata;
   for ( qdata.setFirstId();
         qdata.isValid();
         qdata.setNextId() )
   {
      pCnrObject[ ID_MAIN_CNROBJECT + ++objCount ] =
         new LMainCnrObject( ID_ICON_QUERY2, qdata.getQry(),
                             LMainCnrObject::query,
                             IResourceId( STR_CUSTOM_QUERY_DESC ) );
      addObject( pCnrObject[ ID_MAIN_CNROBJECT + objCount ] );
   }

/*-----------------------------------------------------------------------------
| Arrange the icons                                                           |
| Reshow it                                                                   |
-----------------------------------------------------------------------------*/
   arrangeIconView();
   show();

   return *this;
}


/******************************************************************************
* Class LMainCnr :: addLastQuery() - Add saved query to container.            *
******************************************************************************/
LMainCnr& LMainCnr::addLastQuery( IString queryName )
{
/*-----------------------------------------------------------------------------
| Add new query to container                                                  |
-----------------------------------------------------------------------------*/
   pCnrObject[ ID_MAIN_CNROBJECT + ++objCount ] =
      new LMainCnrObject( ID_ICON_QUERY2, queryName,
                          LMainCnrObject::query,
                          IResourceId( STR_CUSTOM_QUERY_DESC ) );
   addObject( pCnrObject[ ID_MAIN_CNROBJECT + objCount ] );

/*-----------------------------------------------------------------------------
| Arrange the icons                                                           |
-----------------------------------------------------------------------------*/
   arrangeIconView();

   return *this;
}


/******************************************************************************
* Class LMainCnr :: makePopUpMenu()                                           *
*   Create popup menus based on the type of the cnr object                    *
******************************************************************************/
IBase::Boolean LMainCnr::makePopUpMenu( IMenuEvent& evt )
{
   Boolean
      retCode = true,
      hasSelectItem = true;
   unsigned long
      whichMenu = 0;
/*-----------------------------------------------------------------------------
| Get the object with the last popup menu                                     |
-----------------------------------------------------------------------------*/
   LMainCnrObject
     *pcnrObject = (LMainCnrObject*)popupMenuObject();
   if ( pcnrObject )
      switch( pcnrObject->type() )
      {
         case LMainCnrObject::personnel :
         {
            whichMenu = ID_MAIN_FUNC_POP;
            hasSelectItem = false;
            break;
         }

         case LMainCnrObject::query :
         {
            whichMenu = ID_MAIN_QUERY_POP;
            hasSelectItem = false;
            break;
         }
      }
   else
      whichMenu = ID_MAIN_POP;

   if ( whichMenu )
   {
/*-----------------------------------------------------------------------------
| Create a popup menu based on the object's type                              |
| Disable the select menu item if it exists for this menu.                    |
| Automatically delete the popup menu when no longer needed                   |
| Set the last popup menu object to be this cnr object                        |
| Show the popup menu at the mouse position                                   |
-----------------------------------------------------------------------------*/
      popm =
         new IPopUpMenu ( whichMenu, owner() );
      if ( hasSelectItem &&
           !((LMainWindow*)owner())->selectsAllowed() )
         popm->enableItem( ID_MAIN_VIEW_SELECT, false );
      popm->setAutoDeleteObject();
      ptheLastPopupMenuObject = (LMainCnrObject*) popupMenuObject();
      popm->show( evt.mousePosition() );
   }
   return retCode;
}


/******************************************************************************
* Class LMainCnr :: enter() - Process the enter key on a container object.    *
******************************************************************************/
IBase::Boolean LMainCnr::enter( ICnrEnterEvent& evt )
{
   Boolean
      retCode = false;

/*-----------------------------------------------------------------------------
| If the user pressed enter on a cnr object, send an open message             |
-----------------------------------------------------------------------------*/
   if ( evt.validObject() )
   {
      setLastPopupMenuObject( (LMainCnrObject*) evt.object() );
      postEvent( IWindow::command, ID_MAIN_SELECTED_OPEN );
      retCode = true;
   }

   return retCode;
}


/******************************************************************************
* Class LMainCnr :: help() - Process the help key over a container.           *
******************************************************************************/
IBase::Boolean LMainCnr::help( ICnrHelpEvent& evt )
{
   delete helpWin;
   helpWin = IHelpWindow::helpWindow( this );
   if ( helpWin )
      helpWin->show( IResourceId( ID_MAIN ) );
   return true;
}


/******************************************************************************
* Class LMainCnrObject :: LMainCnrObject - Constructor for container object   *
*   given another cnr object                                                  *
******************************************************************************/
LMainCnrObject::LMainCnrObject( const LMainCnrObject& cnrobj )
     :LCnrObject           ( (const LCnrObject&) cnrobj ),
      theType              ( cnrobj.type() ),
      theDesc              ( cnrobj.description() )
{}


/******************************************************************************
* Class LMainCnrObject :: LMainCnrObject - Constructor for container object   *
*   given a string title and string description                               *
******************************************************************************/
LMainCnrObject::LMainCnrObject( unsigned long icon, IString title,
                                ObjectType type, IString description )
     :LCnrObject( title, icon ),
      theType( type ),
      theDesc( description )
{}


/******************************************************************************
* Class LMainCnrObject :: LMainCnrObject - Constructor for container object   *
*   given a resource id title and resource id description                     *
****************************************************************************/
LMainCnrObject::LMainCnrObject( unsigned long icon, IResourceId title,
                                ObjectType type, IResourceId description )
     :LCnrObject( title, icon ),
      theType( type ),
      theDesc( IApplication::current().userResourceLibrary().
               loadString( description.id() ) )
{}


/******************************************************************************
* Class LMainCnrObject :: LMainCnrObject - Constructor for container object   *
*   given a string title and resource id description                          *
******************************************************************************/
LMainCnrObject::LMainCnrObject( unsigned long icon, IString title,
                                ObjectType type, IResourceId description )
     :LCnrObject( title, icon ),
      theType( type ),
      theDesc( IApplication::current().userResourceLibrary().
               loadString( description.id() ) )
{}


/******************************************************************************
* Class LMainCnrObject :: ~LMainCnrObject - Destructor                        *
******************************************************************************/
LMainCnrObject::~LMainCnrObject()
{}


/******************************************************************************
* Class LMainToolBar :: LMainToolBar - Constructor for toolbar                *
*   given a resource id                                                       *
******************************************************************************/
LMainToolBar::LMainToolBar( unsigned long id, IFrameWindow* owner,
                            ITextControl* infoarea )
     :IToolBar             ( id, owner, IToolBar::aboveClient, false,
                             IToolBar::classDefaultStyle
                             & ~IToolBar::buttonBitmapVisible
                             | IToolBar::buttonBitmapAndTextVisible ),
      openButton           ( ID_MAIN_SELECTED_OPEN, this, this ),
      helpButton           ( ID_MAIN_HELP_INDEX, this, this ),
      deleteButton         ( ID_MAIN_SELECTED_DELETE, this, this ),
      iconButton           ( ID_MAIN_VIEW_OPEN_ICON, this, this ),
      treeButton           ( ID_MAIN_VIEW_OPEN_TREE, this, this ),
      detailsButton        ( ID_MAIN_VIEW_OPEN_DETAILS, this, this ),
      selectAllButton      ( ID_MAIN_VIEW_SELECT_ALL, this, this ),
      deselectAllButton    ( ID_MAIN_VIEW_SELECT_DE, this, this ),
      sortAscButton        ( ID_MAIN_VIEW_SORT_ASC, this, this ),
      sortDescButton       ( ID_MAIN_VIEW_SORT_DESC, this, this ),
      arrangeButton        ( ID_MAIN_VIEW_ARRANGE, this, this ),
      flyText              ( ID_MAIN_FLYTEXT, this ),
      flyHelpHdr           ( &flyText, infoarea, 0, 0 )
{
/*-----------------------------------------------------------------------------
| For these buttons, use the standard bitmaps for these buttons.              |
-----------------------------------------------------------------------------*/
   openButton.setBitmap( IC_ID_OPEN );
   helpButton.setBitmap( IC_ID_HELP );

/*-----------------------------------------------------------------------------
| Add the buttons to the toolbar.                                             |
-----------------------------------------------------------------------------*/
   addAsLast( &openButton );
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
   flyHelpHdr.setFlyTextStringTableOffset( ID_MAIN_OFFSET_FLYTEXT );
   flyHelpHdr.setLongStringTableOffset( ID_MAIN_OFFSET_INFOAREA );
   flyHelpHdr.setDefaultText( ID_MAIN_OFFSET_INFOAREA+ID_MAIN );
   flyHelpHdr.handleEventsFor( this );
}

/******************************************************************************
* Class LMainToolBar :: enableSelects - Enable/disable the selection          *
*   toolbar buttons.                                                          *
******************************************************************************/
LMainToolBar& LMainToolBar::enableSelects( Boolean which )
{
   selectAllButton.enable( which );
   deselectAllButton.enable( which );
   return *this;
}


/******************************************************************************
* Class LMainWindowCommandHandler :: LMainWindowCommandHandler - Constructor  *
*  for handling command events for the frame window                           *
******************************************************************************/
LMainWindowCommandHandler::LMainWindowCommandHandler
                           ( LMainWindow* owner,
                             IHelpWindow* helpWin,
                             LMainCnr* cnrCtl )
     :pOwner( owner ),
      pHelp( helpWin ),
      pCnr( cnrCtl )
{}


/******************************************************************************
* Class LMainWindowCommandHandler :: ~LMainWindowCommandHandler - Destructor  *
******************************************************************************/
LMainWindowCommandHandler::~LMainWindowCommandHandler()
{}


/******************************************************************************
* Class LMainWindowCommandHandler :: command() - Handle the command events    *
******************************************************************************/
IBase::Boolean LMainWindowCommandHandler::command( ICommandEvent& evt )
{
   IBase::Boolean
      useObjectCollection = true;
   unsigned long
      cmdId = evt.commandId ();

/*-----------------------------------------------------------------------------
| Get the last popup menu object                                              |
| Get a cursor for all the selected items in the cnr                          |
 ----------------------------------------------------------------------------*/
   LMainCnrObject
     *pcurObject = pCnr->lastPopupMenuObject();
   IContainerControl::ObjectCursor
      cnrObjectsSelected( *pCnr, IContainerObject::selected );

   cnrObjectsSelected.setToFirst();
   switch( cmdId )
   {
      case ID_MAIN_OBJECT_POP_OPEN:
      {
/*-----------------------------------------------------------------------------
| If the object with the last popup menu is not selected,                     |
|  do not use all selected cnr objects.                                       |
| Else fall through to the ID_MAIN_SELECTED_OPEN.                             |
-----------------------------------------------------------------------------*/
         if ( pcurObject && !pCnr->isSelected( pcurObject ) )
            useObjectCollection = false;
      }

      case ID_MAIN_SELECTED_OPEN:
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
               LMainCnrObject
                 *pcurObject = (LMainCnrObject *) cnrObjectsSelected.current();
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

      case ID_MAIN_OBJECT_POP_DELETE:
      {
/*-----------------------------------------------------------------------------
| If the object with the last popup menu and is not selected,                 |
|  do not use all selected cnr objects.                                       |
| Else fall through to the ID_MAIN_SELECTED_DELETE.                           |
-----------------------------------------------------------------------------*/
         if ( pcurObject && !pCnr->isSelected( pcurObject ) )
            useObjectCollection = false;
      }

      case ID_MAIN_SELECTED_DELETE:
      {
         if ( useObjectCollection )
         {
/*-----------------------------------------------------------------------------
| Delete each selected object.                                                |
| - Since the selected cnr object cursor becomes invalidated when             |
|   the object is deleted, we must reset the position each time.              |
-----------------------------------------------------------------------------*/
            do
            {
               LMainCnrObject
                 *pcurObject = (LMainCnrObject *) cnrObjectsSelected.current();
               if ( pcurObject )
               {
                  Boolean
                     wasDeleted = deleteAction( pcurObject );
                  if ( !wasDeleted )
                     pCnr->setSelected( pcurObject, false );
               }
               cnrObjectsSelected.setToFirst();
            }
            while ( cnrObjectsSelected.isValid() );
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
      case ID_MAIN_VIEW_OPEN_DETAILS:
      {
         pCnr->showDetailsView();
         pOwner->enableSelects();
         break;
      }

/*-----------------------------------------------------------------------------
| Show the cnr as icon tree view                                              |
-----------------------------------------------------------------------------*/
      case ID_MAIN_VIEW_OPEN_TREE:
      {
         pCnr->showTreeIconView();
         pOwner->enableSelects( false );
         break;
      }

/*-----------------------------------------------------------------------------
| Show the cnr as icon view                                                   |
-----------------------------------------------------------------------------*/
      case ID_MAIN_VIEW_OPEN_ICON:
      {
         pCnr->showIconView();
         pOwner->enableSelects();
         break;
      }

/*-----------------------------------------------------------------------------
| Select all cnr objects by selecting each cnr object                         |
-----------------------------------------------------------------------------*/
      case ID_MAIN_VIEW_SELECT_ALL:
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
| Deselect all cnr objects by deselecting each cnr object                     |
-----------------------------------------------------------------------------*/
      case ID_MAIN_VIEW_SELECT_DE:
      {
         IContainerControl::ObjectCursor
            objCursor( *pCnr );
         for ( objCursor.setToFirst();
               objCursor.isValid();
               objCursor.setToNext() )
         {
            pCnr->setSelected( objCursor.current(), false );
         }
         break;
      }

/*-----------------------------------------------------------------------------
| Arrange the cnr objects for icon view                                       |
-----------------------------------------------------------------------------*/
      case ID_MAIN_VIEW_ARRANGE:
      {
         pCnr->arrangeIconView();
         break;
      }

/*-----------------------------------------------------------------------------
| Sort the cnr objects ascending by their icon text                           |
-----------------------------------------------------------------------------*/
      case ID_MAIN_VIEW_SORT_ASC:
      {
         pCnr->sortByIconText();
         pCnr->arrangeIconView();
         break;
      }

/*-----------------------------------------------------------------------------
| Sort the cnr objects descending by their icon text                          |
-----------------------------------------------------------------------------*/
      case ID_MAIN_VIEW_SORT_DESC:
      {
         pCnr->sortByIconText( false );
         pCnr->arrangeIconView();
         break;
      }

/*-----------------------------------------------------------------------------
| Show index help                                                             |
-----------------------------------------------------------------------------*/
      case ID_MAIN_HELP_INDEX:
      {
         pHelp->show( IHelpWindow::index );
         break;
      }

/*-----------------------------------------------------------------------------
| Show general help                                                           |
-----------------------------------------------------------------------------*/
      case ID_MAIN_HELP_GENERAL:
      {
         pHelp->show( IHelpWindow::general );
         break;
      }

/*-----------------------------------------------------------------------------
| Show using help                                                             |
-----------------------------------------------------------------------------*/
      case ID_MAIN_HELP_USING:
      {

//   In VisualAge C++ 4.0, the following needs to be changed to
//       pHelp->show( IHelpWindow::usingHelp );

         pHelp->show( IHelpWindow::usingHelp );
         break;
      }

/*-----------------------------------------------------------------------------
| Show product information                                                    |
-----------------------------------------------------------------------------*/
      case ID_MAIN_HELP_PRODUCT:
      {
         IMessageBox
            productBox( pOwner );
         productBox.show( STR_ABOUT_MSG,
                          IMessageBox::informationIcon );
         break;
      }

/*-----------------------------------------------------------------------------
| Close this application                                                      |
-----------------------------------------------------------------------------*/
      case ID_MAIN_VIEW_CLOSE:
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
* Class LMainWindowCommandHandler :: openAction() - Open the object.          *
******************************************************************************/
LMainWindowCommandHandler& LMainWindowCommandHandler::openAction( LMainCnrObject* pObject )
{
   IMessageBox
      msg( pOwner );

   switch( pObject->type() )
   {
/*-----------------------------------------------------------------------------
| If a personnel query, then open an empty information window                 |
-----------------------------------------------------------------------------*/
      case LMainCnrObject::personnel :
      {
         pObject->setOpen();
         LInfoWindow
           *pqueryWindow = new LInfoWindow( ID_INFO_WINDOW, 0, pOwner,
                                            IPoint(100,100),
                                            pCnr,
                                            pObject,
                                            "" );
         pqueryWindow->setAutoDeleteObject( true );
         break;
      }

/*-----------------------------------------------------------------------------
| If a custom personnel query, then open an information window given          |
|  the custom search criteria                                                 |
-----------------------------------------------------------------------------*/
      case LMainCnrObject::query :
      {
         pObject->setOpen();
         LInfoWindow
           *pqueryWindow = new LInfoWindow( ID_INFO_WINDOW, 0, pOwner,
                                            IPoint(100,100),
                                            pCnr,
                                            pObject,
                                            pObject->iconText() );
         pqueryWindow->setAutoDeleteObject( true );
         break;
      }
   }

   return *this;
}


/******************************************************************************
* Class LMainWindowCommandHandler :: deleteAction() - Delete the object.      *
******************************************************************************/
IBase::Boolean LMainWindowCommandHandler::deleteAction( LMainCnrObject* pObject )
{
   Boolean
      retCode = false;

   switch( pObject->type() )
   {
/*-----------------------------------------------------------------------------
| If a personnel query, do not allow it to be deleted                         |
-----------------------------------------------------------------------------*/
      case LMainCnrObject::personnel :
      {
         IString
            objectName = IString( "'" ) +
                         pObject->iconText() + "'";
         IMessageBox
            msg( pOwner );
         msg.show( IApplication::current().userResourceLibrary().
                   loadString( STR_MAIN_DELETE_MSG1 ) +
                   objectName +
                   IApplication::current().userResourceLibrary().
                   loadString( STR_MAIN_DELETE_MSG2 ),
                   IMessageBox::catastrophic );
         retCode = false;
         break;
      }

/*-----------------------------------------------------------------------------
| If a customer personnel query,                                              |
| - delete the query from the database                                        |
| - delete the object from the cnr                                            |
-----------------------------------------------------------------------------*/
      case LMainCnrObject::query :
      {
         LQueryData
            queryData;
         IString
            queryName = pObject->iconText();
         queryData.deleteItem( queryName );
         delete pObject;
         retCode = true;
         break;
      }
   }

   return retCode;
}


/******************************************************************************
* Class LMainWindowHelpHandler :: LMainWindowHelpHandler - Constructor for    *
*   handling help events.                                                     *
******************************************************************************/
LMainWindowHelpHandler::LMainWindowHelpHandler()
{}


/******************************************************************************
* Class LMainWindowHelpHandler :: ~LMainWindowHelpHandler - Destructor        *
******************************************************************************/
LMainWindowHelpHandler::~LMainWindowHelpHandler()
{}


/******************************************************************************
* Class LMainHelpWindowHelpHandler :: keysHelpId()                            *
*   Handle the keys help request event.                                       *
*   This overrides the default provided by library.                           *
******************************************************************************/
IBase::Boolean LMainWindowHelpHandler::keysHelpId( IEvent& evt )
{
   evt.setResult( ID_MAIN_HELP_KEYS_PANEL);
   return true;
}
