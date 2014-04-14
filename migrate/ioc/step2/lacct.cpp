/******************************************************************************
* FILE NAME: lacct.cpp                                                        *
*                                                                             *
* DESCRIPTION:                                                                *
*                                                                             *
* Classes                                                                     *
*   AcctPage                                                                  *
*   AcctCnrObj                                                                *
*                                                                             *
* COPYRIGHT:                                                                  *
*   Licensed Materials - Property of IBM                                      *
*   (C) Copyright IBM Corporation 1992, 1995                                  *
*   All Rights Reserved                                                       *
*   US Government Users Restricted Rights - Use, duplication, or disclosure   *
*   restricted by GSA ADP Schedule Contract with IBM Corp.                    *
*                                                                             *
*******************************************************************************/

#ifndef _IBASE_                         //Make sure ibase.hpp is included
  #include <ibase.hpp>                  //  since that is where IC_<environ>
#endif                                  //  is defined.
#include <ireslib.hpp>
#include <ihelp.hpp>
#include "lancelot.h"
#include "lacct.hpp"

/******************************************************************************
* Class AccountPage :: AccountPage - Constructor for the account page         *
*                                                                             *
* Define yourself as an IMultiCellCanvas                                      *
* Create generic page buttons                                                 *
* Create generic page container buttons                                       *
* Create static text for the user ID                                          *
* Create static text for the node                                             *
* Create entryfield for the user ID                                           *
* Create entryfield for the node                                              *
* Define a null container pointer                                             *
* Define a null container object pointer                                      *
* Define a null container column pointer                                      *
* Define a null container column pointer                                      *
* Create an account data object given the key                                 *
* Create a empty account data object                                          *
* Set the key in your private data                                            *
* Set the isQuery in your private data                                        *
* Create the notebook page settings                                           *
* Create a select handler and later attach to the container                   *
******************************************************************************/
AccountPage::AccountPage(  IWindow* pParent,
                           const IString& aKey )
     :IMultiCellCanvas     ( ID_ACCOUNT_PAGE, pParent, pParent ),
      pageButtons          ( ID_ACCOUNT_PAGE_BUTTONS, this, this, false ),
      pageCnrButtons       ( ID_ACCOUNT_PAGE_CNRBUTTONS,
                             this, this, false ),
      userIdText           ( ID_NO_ITEM, this, this ),
      nodeSysText          ( ID_NO_ITEM, this, this ),
      userId               ( ID_ACC_USERID_EF, this, this,
                             IRectangle(),
                             IEntryField::classDefaultStyle
                             | IControl::tabStop),
      nodeSys              ( ID_ACC_NODESYS_EF, this, this,
                             IRectangle(),
                             IEntryField::classDefaultStyle
                             | IControl::tabStop ),
      pCnr                 ( (IContainerControl*) NULL ),
      pAcctCnrObj          ( (AcctCnrObj*) NULL ),
      pColUserID           ( (IContainerColumn*) NULL ),
      pColNodeSys          ( (IContainerColumn*) NULL ),
      acctData             ( aKey ),
      origAcctData         (),
      Key                  ( aKey ),
      isAquery             ( false ),
      thePageSettings      ( IApplication::current().userResourceLibrary().
                             loadString( STR_ACC_ACCOUNT_TAB ), NULL,
                             INotebook::PageSettings::autoPageSize
                             | INotebook::PageSettings::majorTab ),
      cnrSelHandler        ( this )

{
/*-----------------------------------------------------------------------------
| Save the account data to another object in case the user wishes to          |
|  undo any changes.                                                          |
| Label the static text objects.                                              |
| Set the limit for the entryfields.                                          |
-----------------------------------------------------------------------------*/
   origAcctData = acctData;
   userIdText.setText( STR_ACC_USERID );
   nodeSysText.setText( STR_ACC_NODESYS );
   userId.setLimit(  DISPLAY_LARGE );
   nodeSys.setLimit( DISPLAY_LARGE );

/*-----------------------------------------------------------------------------
| Fill the container from the database.                                       |
| Set the objects on yourself (IMultiCellCanvas).                             |
| Start handling the events.                                                  |
-----------------------------------------------------------------------------*/
   fillCnr();
   setCells();
   handleIt();
};

/******************************************************************************
* Class AccountPage :: AccountPage - Constructor for the account page         *
*                                                                             *
* Define yourself as an IMultiCellCanvas                                      *
* Create generic page buttons                                                 *
* Create generic page container buttons                                       *
* Create static text for the user ID                                          *
* Create static text for the node                                             *
* Create entryfield for the user ID                                           *
* Create entryfield for the node                                              *
* Define a null container pointer                                             *
* Define a null container object pointer                                      *
* Define a null container column pointer                                      *
* Define a null container column pointer                                      *
* Create an account data object given the query information                   *
* Create a empty account data object                                          *
* Set the key in your private data                                            *
* Set the isQuery in your private data                                        *
* Create the notebook page settings                                           *
* Create a select handler and later attach to the container                   *
******************************************************************************/
AccountPage::AccountPage(  IWindow* pParent,
                           LQueryData& qd )
     :IMultiCellCanvas     ( ID_ACCOUNT_PAGE, pParent, pParent ),
      pageButtons          ( ID_ACCOUNT_PAGE_BUTTONS, this, this, true ),
      pageCnrButtons       ( ID_ACCOUNT_PAGE_CNRBUTTONS,
                             this, this, false),
      userIdText           ( ID_NO_ITEM, this, this ),
      nodeSysText          ( ID_NO_ITEM, this, this ),
      userId               ( ID_ACC_USERID_EF, this, this,
                             IRectangle(),
                             IEntryField::classDefaultStyle
                             | IControl::tabStop ),
      nodeSys              ( ID_ACC_NODESYS_EF, this, this,
                             IRectangle(),
                             IEntryField::classDefaultStyle |
                             IControl::tabStop ),
      pCnr                 ( (IContainerControl*) NULL ),
      pAcctCnrObj          ( (AcctCnrObj*) NULL ),
      pColUserID           ( (IContainerColumn*) NULL ),
      pColNodeSys          ( (IContainerColumn*) NULL ),
      acctData             ( qd ),
      origAcctData         (),
      Key                  ( qd.queryName() ),
      isAquery             ( true ),
      thePageSettings      ( IApplication::current().userResourceLibrary().
                             loadString( STR_ACC_ACCOUNT_TAB ), NULL,
                             INotebook::PageSettings::autoPageSize
                             | INotebook::PageSettings::majorTab ),
      cnrSelHandler        ( this )

{
/*-----------------------------------------------------------------------------
| Save the account data to another object in case the user wishes to          |
|  undo any changes.                                                          |
| Label the static text objects.                                              |
| Set the limit for the entryfields.                                          |
-----------------------------------------------------------------------------*/
   origAcctData = acctData;
   userIdText.setText( STR_ACC_USERID  );
   nodeSysText.setText( STR_ACC_NODESYS );
   userId.setLimit( DISPLAY_LARGE );
   nodeSys.setLimit( DISPLAY_LARGE );

/*-----------------------------------------------------------------------------
| Fill the container from the database.                                       |
| Set the objects on yourself (IMultiCellCanvas).                             |
| Start handling the events.                                                  |
-----------------------------------------------------------------------------*/
   fillCnr();
   setCells();
   handleIt();
};


/******************************************************************************
* Class AccountPage :: ~AccountPage - Destructor for the account page         *
******************************************************************************/
AccountPage::~AccountPage()
{
/*-----------------------------------------------------------------------------
| Stop handling events.                                                       |
-----------------------------------------------------------------------------*/
   ICommandHandler::stopHandlingEventsFor( &pageButtons );
   ICommandHandler::stopHandlingEventsFor( &pageCnrButtons );
   cnrSelHandler.stopHandlingEventsFor( pCnr );
};


/******************************************************************************
* Class AccountPage :: handleIt - Handle events for the account page          *
******************************************************************************/
AccountPage& AccountPage::handleIt()
{
/*-----------------------------------------------------------------------------
| Start handling events.                                                      |
| Return yourself.                                                            |
-----------------------------------------------------------------------------*/
   ICommandHandler::handleEventsFor( &pageButtons );
   ICommandHandler::handleEventsFor( &pageCnrButtons );
   return *this;
}


/******************************************************************************
* Class AccountPage :: fillCnr - Set up the container                         *
******************************************************************************/
AccountPage& AccountPage::fillCnr()
{
/*-----------------------------------------------------------------------------
| If the container already exists,                                            |
|  delete all the objects                                                     |
| Else create a new container.                                                |
-----------------------------------------------------------------------------*/
   if ( pCnr )
      pCnr->deleteAllObjects();
   else
   {
      pCnr = new IContainerControl( ID_ACC_CNR,
                                    this, this,
                                    IRectangle(),
                                    IContainerControl::classDefaultStyle
                                    | IContainerControl::readOnly,
                                    IContainerControl::readOnlyTitle
                                    | IContainerControl::detailsView );

/*-----------------------------------------------------------------------------
| Handle selection events for the new container.                              |
-----------------------------------------------------------------------------*/
      cnrSelHandler.handleEventsFor( pCnr );

/*-----------------------------------------------------------------------------
| Delete the objects when the container is deleted.                           |
| Tell the container to allow multiple selection.                             |
| Tell the container to automatically refresh upon changes.                   |
-----------------------------------------------------------------------------*/
      pCnr->setDeleteObjectsOnClose();
      pCnr->setDeleteColumnsOnClose();
      pCnr->setMultipleSelection();
      pCnr->setRefreshOn();

/*-----------------------------------------------------------------------------
| Create two container columns.                                               |
-----------------------------------------------------------------------------*/
      pColUserID =
         new IContainerColumn( pAcctCnrObj->currentUserIdOffset(),
                               IContainerColumn::defaultHeadingStyle(),
                               IContainerColumn::string );
      pColNodeSys =
         new IContainerColumn( pAcctCnrObj->nodeSysOffset(),
                               IContainerColumn::defaultHeadingStyle(),
                               IContainerColumn::string );

/*-----------------------------------------------------------------------------
| Label the container column headings.                                        |
| Show the headings.                                                          |
| Show the headings.                                                          |
-----------------------------------------------------------------------------*/
      pColUserID->setHeadingText( STR_ACC_USERID );
      pColNodeSys->setHeadingText( STR_ACC_NODESYS );
      pCnr->showDetailsViewTitles();

/*-----------------------------------------------------------------------------
| Add the columns to the container.                                           |
| Add column separators between the columns.                                  |
-----------------------------------------------------------------------------*/
      pCnr->addColumn( pColUserID );
      pCnr->addColumn( pColNodeSys );
      pColUserID->showSeparators( IContainerColumn::verticalSeparator
                                  | IContainerColumn::horizontalSeparator );
      pColNodeSys->showSeparators( IContainerColumn::horizontalSeparator );
   }

/*-----------------------------------------------------------------------------
| Start from the beginning of the account data.                               |
| While there exists items,                                                   |
|   add objects to the container.                                             |
| Refresh the container.                                                      |
| Return yourself.                                                            |
-----------------------------------------------------------------------------*/
   IString
      user,
      node;
   LAcctData::Rule
      rule;

   acctData.setFirst();
   while ( acctData.getItem( user, node, rule ) )
   {
      addAcct( user, node );
      acctData.getNext();
   }

   pCnr->refresh();

   return *this;
};


/******************************************************************************
* Class AccountPage :: setCells - Set up your multicell canvas cells          *
******************************************************************************/
AccountPage& AccountPage::setCells()
{
/*-----------------------------------------------------------------------------
| Add the objects to your multicell canvas.                                   |
| Allow the container to expand horizontally.                                 |
| Allow the page buttons to expand horizontally.                              |
| Return yourself.                                                            |
-----------------------------------------------------------------------------*/
   addToCell( &userIdText,        2,  2 );
   addToCell( &userId,            2,  3 );

   addToCell( &nodeSysText,       2,  4 );
   addToCell( &nodeSys,           2,  5 );

   addToCell( pCnr,               2,  7,  3,  3 );
   addToCell( &pageCnrButtons,    5,  8 );
   setColumnWidth(                4,  0, true );

   addToCell( &pageButtons,       2, 10,  2,  3 );
   setColumnWidth(                3,  0, true );

   return *this;
};


/******************************************************************************
* Class AccountPage :: verifyAndSave - Save page information to the database  *
******************************************************************************/
IBase::Boolean AccountPage::verifyAndSave( IString& theString,
                                           IString& theEntry,
                                           const IString saveName )
{
/*-----------------------------------------------------------------------------
| If there is no data or is a query, return.                                  |
-----------------------------------------------------------------------------*/
   if ( ( ! saveName.length() )
        && ( ! Key.length() )
        || isAquery )
      return true;

/*-----------------------------------------------------------------------------
| If able to retrieve the container information,                              |
|  save the information to the database based on the key or query name.       |
-----------------------------------------------------------------------------*/
   if ( setAcctData() )
   {
      if ( ( saveName.length() > 0 ) && ( saveName.isAlphanumeric() ) )
         acctData.save( saveName );
       else
         if ( ( Key.length() > 0 ) && ( Key.isAlphanumeric() ) )
            acctData.save( Key );
   }

   return true;
};


/******************************************************************************
* Class AccountPage :: setAcctData - Retrieve the page information            *
******************************************************************************/
IBase::Boolean AccountPage::setAcctData()
{
   IContainerControl::ObjectCursor
      iterator( *pCnr );

   iterator.setToFirst();
   if ( ! iterator.isValid() )
      return false;

   AcctCnrObj
      *cnrEntry;
   IString
      it1,
      it2;

/*-----------------------------------------------------------------------------
| Empty the bag.                                                              |
| Iterate through the cursor and add objects to the bag.                      |
-----------------------------------------------------------------------------*/
   acctData.emptyBag();
   while ( iterator.isValid() )
   {
      cnrEntry = (AcctCnrObj *) iterator.current();
      this->acctData.putItem( cnrEntry->getUserId(), cnrEntry->getNode() );
      cnrEntry = (AcctCnrObj *) iterator.next();
   }

   return true;
};


/******************************************************************************
* Class AccountPage :: fillEntryfields - Fill the entryfields for the object  *
******************************************************************************/
AccountPage& AccountPage::fillEntryfields( AcctCnrObj* pCnrObject )
{
/*-----------------------------------------------------------------------------
| Set the entryfields for the given account container object.                 |
| Return yourself.                                                            |
-----------------------------------------------------------------------------*/
   userId.setText( pCnrObject->getUserId() );
   nodeSys.setText( pCnrObject->getNode() );

   return *this;
};


/******************************************************************************
* Class AccountPage :: command - Catch and process command events.            *
******************************************************************************/
IBase::Boolean AccountPage::command( ICommandEvent& cmdEvent )
{
   IString
      theUser = userId.text(),
      theNode = nodeSys.text();
   LAcctData::Rule
      theRule = LAcctData::na;
   Boolean
      rc = false;
   unsigned int
      count = 0;

/*-----------------------------------------------------------------------------
| Create a container object cursor based on the selected objects.             |
| Process the command events.                                                 |
-----------------------------------------------------------------------------*/
   IContainerControl::ObjectCursor
      soc( *pCnr, IContainerObject::selected );

   switch ( cmdEvent.commandId() )
   {
/*-----------------------------------------------------------------------------
| User pressed the UNDO button.                                               |
| Reset the account data to the original account data.                        |
| Reset the container.                                                        |
| Reset the entryfields.                                                      |
-----------------------------------------------------------------------------*/
      case ID_BUTTON_UNDO:
      {
         acctData = origAcctData;
         fillCnr();
         userId.setText( "" );
         nodeSys.setText( "" );
         rc = true;
         break;
      }

/*-----------------------------------------------------------------------------
| User pressed the REMOVE button.                                             |
| Iterate through the selected objects,                                       |
|  remove the object from the the database.                                   |
-----------------------------------------------------------------------------*/
      case ID_BUTTON_REMOVE:
      {
         for ( soc.setToFirst();
               soc.isValid();
               soc.setToNext() )
         {
            AcctCnrObj
               *pObj = (AcctCnrObj *) soc.current();
            acctData.putItem( pObj->getUserId(),
                              pObj->getNode(),
                              LAcctData::remove );
            ++count;
         }

/*-----------------------------------------------------------------------------
| If no container objects were selected,                                      |
|  notify the user.                                                           |
-----------------------------------------------------------------------------*/
         if ( ! count )
         {
            IMessageBox
               warning( owner() );
            warning.show( STR_MSG_REMOVE,
                          IMessageBox::enterButton
                          | IMessageBox::informationIcon );
         }
/*-----------------------------------------------------------------------------
| Else remove the selected objects from the container.                        |
| Refresh the container.                                                      |
-----------------------------------------------------------------------------*/
         else
         {
            pCnr->removeSelectedObjects();
            userId.setText( "" );
            nodeSys.setText( "" );
            pCnr->refresh();
         }
         rc = true;
         break;
      }

/*-----------------------------------------------------------------------------
| User pressed the CHANGE button.                                             |
| Ignore all but the first selected container object.                         |
| Update the entryfields with the selected container object information.      |
-----------------------------------------------------------------------------*/
      case ID_BUTTON_CHANGE:
      {
         soc.setToFirst();
         if ( soc.isValid() )
         {
            if ( theUser.length() )
            {
               changeAcct( theUser, theNode, (AcctCnrObj*) soc.current() );
               userId.setText( "" );
               nodeSys.setText( "" );
            }

         }
/*-----------------------------------------------------------------------------
| If no container objects were selected,                                      |
|  notify the user.                                                           |
-----------------------------------------------------------------------------*/
         else
         {
            IMessageBox
               warning( owner() );
            warning.show( STR_MSG_CHANGE,
                          IMessageBox::enterButton
                          | IMessageBox::informationIcon );
         }

/*-----------------------------------------------------------------------------
| Deselect any container objects.                                             |
-----------------------------------------------------------------------------*/
         unMark();
         rc = true;
         break;
      }

/*-----------------------------------------------------------------------------
| User pressed the ADD button.                                                |
| Add the entryfield information to the database and container.               |
| Reset the entryfields.                                                      |
-----------------------------------------------------------------------------*/
      case ID_BUTTON_ADD:
      {
         if ( theUser.length() )
         {
            addAcct( theUser, theNode );
            userId.setText( "" );
            nodeSys.setText( "" );
         }

/*-----------------------------------------------------------------------------
| Deselect any container objects.                                             |
-----------------------------------------------------------------------------*/
         unMark();
         rc = true;
         break;
      }

/*-----------------------------------------------------------------------------
| User pressed the HELP button.                                               |
| Show the help for the account page.                                         |
-----------------------------------------------------------------------------*/
      case ID_BUTTON_HELP:
      {
         IHelpWindow::helpWindow( this )->
            show( IResourceId( ID_ACCOUNT_PAGE ) );
         rc = true;
         break;
      }

   }

   return rc;
};


/******************************************************************************
* Class AccountPage :: addAcct - Add the account information to the container *
******************************************************************************/
IBase::Boolean AccountPage::addAcct( IString& user, IString& node )
{
   Boolean
      rc = true;

/*-----------------------------------------------------------------------------
| Create a container text cursor based on the user ID.                        |
-----------------------------------------------------------------------------*/
   IContainerControl::TextCursor
      txtCur( *pCnr, IString( user ), true, false, true );

/*-----------------------------------------------------------------------------
| Start at the beginning of the cursor.                                       |
| If the cursor contains a duplicate, set the return code to false.           |
-----------------------------------------------------------------------------*/
   for ( txtCur.setToFirst();
         txtCur.isValid();
         txtCur.setToNext() )
   {
      if ( ( (AcctCnrObj*) txtCur.current() )->getNode() == node )
      {
         rc = false;
         break;
      }
   }

/*-----------------------------------------------------------------------------
| If the object doesn't exist,                                                |
|  Add the object to the database.                                            |
|  Create an account container object.                                        |
|  Add the object to the container.                                           |
|  Refresh the container.                                                     |
-----------------------------------------------------------------------------*/
   if ( rc )
   {
      if ( isAquery )
      {
         if ( ! user.length() )
            user = "*";
         if ( ! node.length() )
            node = "*";
      }

      acctData.putItem( user, node, LAcctData::add );
      pAcctCnrObj = new AcctCnrObj( user, node );
      pCnr->addObject( pAcctCnrObj );
      pCnr->refresh();
   }

   return rc;
}

/******************************************************************************
* Class AccountPage :: changeAcct - Change the account information for the    *
*  selected container object.                                                 *
******************************************************************************/
IBase::Boolean AccountPage::changeAcct( IString& user, IString& node,
                                        AcctCnrObj* pCnrObj )
{
   Boolean
      rc = true;

/*-----------------------------------------------------------------------------
| Create a container text cursor based on the user ID.                        |
-----------------------------------------------------------------------------*/
   IContainerControl::TextCursor
      txtCur( *pCnr, IString( user ), true, false, true );

/*-----------------------------------------------------------------------------
| Start at the beginning of the cursor.                                       |
| If the cursor contains a duplicate, set the return code to false.           |
-----------------------------------------------------------------------------*/
   for ( txtCur.setToFirst();
         txtCur.isValid();
         txtCur.setToNext() )
   {
      if ( ( (AcctCnrObj*) txtCur.current() )->getNode() == node )
      {
         rc = false;
         break;
      }
   }

/*-----------------------------------------------------------------------------
| If the container object exists -and- the user-ID/node combination do        |
|  not exist,                                                                 |
|  Set the container object's user ID and node.                               |
|  Reset the entryfields.                                                     |
|  Deselect the container objects.                                            |
-----------------------------------------------------------------------------*/
   if ( pCnrObj && rc )
   {
      pCnrObj->setUserId( user );
      pCnrObj->setNode( node );

   }

   return rc;
}

/******************************************************************************
* Class AccountPage :: unMark - Deselect the selected container objects.      *
******************************************************************************/
AccountPage& AccountPage::unMark()
{
   IContainerControl::ObjectCursor
      co ( *pCnr );

   for ( co.setToFirst();
         co.isValid();
         co.setToNext() )
   {
      try
      {
         pCnr->removeSelected( pCnr->objectAt( co ) );
      }
      catch ( IException& exc )
      {}
   }

   return *this;
};


/******************************************************************************
* Class AcctCnrObj :: AcctCnrObj - Constructor for account container objects  *
*                                                                             *
* Define yourself as a container object.                                      *
* Set the current user ID in your private data.                               *
* Set the node in your private data.                                          *
******************************************************************************/
AcctCnrObj::AcctCnrObj( const IString& stCurrentUserId,
                        const IString& stNodeSystem )
     :IContainerObject(),
      currentUserId( stCurrentUserId ),
      nodeSystem( stNodeSystem )
{};


/******************************************************************************
* Class AcctCnrObj :: ~AcctCnrObj - Destructor for account container objects  *
******************************************************************************/
AcctCnrObj::~AcctCnrObj()
{};
