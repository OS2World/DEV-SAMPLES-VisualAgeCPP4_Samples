/******************************************************************************
* .FILE:         lproject.cpp                                                 *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Implementation   *
*                                                                             *
* .CLASSES:      ProjectPage                                                  *
*                ProjCnrObj                                                   *
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
#include <iapp.hpp>
#include <iexcbase.hpp>
#include <ihelp.hpp>
#include <ireslib.hpp>
#include "lancelot.h"
#include "lproject.hpp"

/******************************************************************************
* Class ProjectPage :: ProjectPage - Constructor for the project page         *
*                                                                             *
* Define yourself as an IMultiCellCanvas                                      *
* Create generic page buttons                                                 *
* Create generic page container buttons                                       *
* Create static text for the project                                          *
* Create static text for the active indicator                                 *
* Create static text for the description                                      *
* Create static text for the responsible manager                              *
* Create entryfield for the project                                           *
* Create checkbox for the active indicator                                    *
* Create entryfield for the description                                       *
* Create combobox for the responsible manager                                 *
* Define a null container pointer                                             *
* Define a null container object pointer                                      *
* Define a null container column pointer                                      *
* Define a null container column pointer                                      *
* Define a null container column pointer                                      *
* Define a null container column pointer                                      *
* Create an project data object given the key                                 *
* Create a empty project data object                                          *
* Set the key in your private data                                            *
* Create the notebook page settings                                           *
* Create a alphanumeric handler (MOTIF only)                                  *
* Create a container select handler                                           *
******************************************************************************/
ProjectPage::ProjectPage(  IWindow* pParent,
                           const IString& aKey )
     :IMultiCellCanvas     ( ID_PROJECT_PAGE, pParent, pParent ),
      pageButtons          ( ID_PROJECT_PAGE_BUTTONS,
                             this, this, false ),
      pageCnrButtons       ( ID_PROJECT_PAGE_CNRBUTTONS,
                             this, this, false ),
      projText             ( ID_NO_ITEM, this, this ),
      activeText           ( ID_NO_ITEM, this, this ),
      descrText            ( ID_NO_ITEM, this, this ),
      respMgrText          ( ID_NO_ITEM, this, this ),
      project              ( ID_PRJ_PROJ_EF, this, this,
                             IRectangle(),
                             IEntryField::classDefaultStyle
                             | IControl::tabStop ),
      active               ( ID_PRJ_ACTIVE_CB, this, this ),
      descr                ( ID_PRJ_DESCR_EF, this, this,
                             IRectangle(),
                             IEntryField::classDefaultStyle
                             | IControl::tabStop ),
      respMgr              ( ID_WRK_RESP_MGR_CBX, this, this,
                             IRectangle(),
                             IComboBox::defaultStyle()
                             & ~IComboBox::simpleType
                             | IComboBox::dropDownType
                             | IControl::tabStop ),
      pCnr                 ( NULL ),
      pProjCnrObj          ( (ProjCnrObj*) NULL ),
      pColProj             ( ( IContainerColumn*) NULL ),
      pColDesc             ( ( IContainerColumn*)NULL ),
      pColMgr              ( ( IContainerColumn*)NULL ),
      pColAct              ( ( IContainerColumn*)NULL ),
      projectData          ( aKey ),
      origProjectData      (),
      Key                  ( aKey ),
      thePageSettings      ( IApplication::current().userResourceLibrary().
                             loadString( STR_PRJ_PROJECT_TAB ), NULL,
                             INotebook::PageSettings::autoPageSize
                             | INotebook::PageSettings::majorTab ),
      cnrSelHandler        ( this )
{
/*-----------------------------------------------------------------------------
| Save the project data to another object in case the user wishes to          |
|  undo any changes.                                                          |
| Label the static text objects.                                              |
| Set the limit for the entryfield and combobox.                              |
| Set the combobox input type and range.                                      |
-----------------------------------------------------------------------------*/
   origProjectData = projectData;
   projText.setText( STR_PRJ_PROJ );
   activeText.setText( STR_PRJ_ACTIVE );
   descrText.setText( STR_PRJ_DESCRIPTION );
   respMgrText.setText( STR_PRJ_RESP_MGR );
   project.setLimit( DISPLAY_LARGE );
   descr.setLimit( DISPLAY_TEXT );
   respMgr.setLimit( DISPLAY_LARGE );

/*-----------------------------------------------------------------------------
| Fill the combobox from the database.                                        |
| Fill the container from the database.                                       |
| Set the objects on yourself (IMultiCellCanvas).                             |
| Start handling the events.                                                  |
-----------------------------------------------------------------------------*/
   fillPage();
   fillCnr();
   setCells();
   handleIt();
}


/******************************************************************************
* Class ProjectPage :: ~ProjectPage - Destructor for the project page         *
******************************************************************************/
ProjectPage::~ProjectPage()
{
/*-----------------------------------------------------------------------------
| Stop handling events.                                                       |
-----------------------------------------------------------------------------*/
   ICommandHandler::stopHandlingEventsFor( &pageButtons );
   ICommandHandler::stopHandlingEventsFor( &pageCnrButtons );
   ISelectHandler::stopHandlingEventsFor( &pageButtons );
   cnrSelHandler.stopHandlingEventsFor( pCnr );
}


/******************************************************************************
* Class ProjectPage :: fillPage - Populate combobox from database             *
******************************************************************************/
ProjectPage& ProjectPage :: fillPage()
{
   IString
      theId;

   QueryMgrs
     *pM = new QueryMgrs();

/*-----------------------------------------------------------------------------
| Get the manager Ids.                                                        |
-----------------------------------------------------------------------------*/
   pM->getMatchList();
   if ( pM->setFirstMatchId() )
   {
      while ( pM->getMatchId( theId ) )
      {
         LEmployeeData
           *pED = new LEmployeeData( theId );
         IString mgr =  pED->firstName() ;

/*-----------------------------------------------------------------------------
| Add middle initial with a "." only if there is one                          |
-----------------------------------------------------------------------------*/
         if ( ( pED->middleInitial().length() > 0 ) &&
              ( pED->middleInitial().isAlphabetic() > 0 ) )
            mgr += " " + pED->middleInitial() + ". " ;
         else
            mgr +=" ";

         mgr += pED->lastName() ;

         respMgr.addAsLast( mgr ) ;
         delete pED;
         pM->getNextMatchId();
      }
   }

   delete pM;

   return *this;
}


/******************************************************************************
* Class ProjectPage :: handleIt()                                             *
******************************************************************************/
ProjectPage& ProjectPage::handleIt()
{
/*-----------------------------------------------------------------------------
| Begin handling events.                                                      |
-----------------------------------------------------------------------------*/
   ICommandHandler::handleEventsFor( &pageButtons );
   ICommandHandler::handleEventsFor( &pageCnrButtons );
   ISelectHandler::handleEventsFor( &pageButtons );
   return *this;
}


/******************************************************************************
* Class ProjectPage :: fillCnr - Set up the container                         *
******************************************************************************/
ProjectPage& ProjectPage::fillCnr()
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
      pCnr = new IContainerControl( ID_PRJ_CNR,
                                    this, this,
                                    IRectangle(),
                                    IContainerControl::classDefaultStyle
                                    | IContainerControl::readOnly | IContainerControl::pmCompatible,
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

/*-----------------------------------------------------------------------------
| Create four container columns.                                              |
-----------------------------------------------------------------------------*/
      pColProj =
         new IContainerColumn( pProjCnrObj->projOffset(),
                               IContainerColumn::defaultHeadingStyle(),
                               IContainerColumn::string );

      pColDesc =
         new IContainerColumn( pProjCnrObj->descOffset(),
                               IContainerColumn::defaultHeadingStyle(),
                               IContainerColumn::string );

      pColMgr =
         new IContainerColumn( pProjCnrObj->mgrOffset(),
                               IContainerColumn::defaultHeadingStyle(),
                               IContainerColumn::string );

      pColAct =
         new IContainerColumn( pProjCnrObj->actOffset(),
                               IContainerColumn::defaultHeadingStyle(),
                               IContainerColumn::string );

/*-----------------------------------------------------------------------------
| Label the container column headings.                                        |
| Show the headings.                                                          |
| Show the headings.                                                          |
-----------------------------------------------------------------------------*/
      pColProj->setHeadingText( STR_PRJ_PROJECT2 );
      pColDesc->setHeadingText( STR_PRJ_DESCRIPTION2 );
      pColMgr->setHeadingText( STR_PRJ_MGR );
      pColAct->setHeadingText( STR_PRJ_ACTIVE2 );
      pCnr->showDetailsViewTitles();

/*-----------------------------------------------------------------------------
| Add the columns to the container.                                           |
| Add column separators between the columns.                                  |
-----------------------------------------------------------------------------*/
      pCnr->addColumn( pColProj );
      pCnr->addColumn( pColDesc );
      pCnr->addColumn( pColMgr );
      pCnr->addColumn( pColAct );
      pColProj->showSeparators( IContainerColumn::verticalSeparator
                                | IContainerColumn::horizontalSeparator );
      pColDesc->showSeparators( IContainerColumn::verticalSeparator
                                | IContainerColumn::horizontalSeparator );
      pColMgr->showSeparators( IContainerColumn::verticalSeparator
                               | IContainerColumn::horizontalSeparator );
      pColAct->showSeparators( IContainerColumn::horizontalSeparator );
   }

/*-----------------------------------------------------------------------------
| Start from the beginning of the project data.                               |
| While there exists items,                                                   |
|   add objects to the container.                                             |
| Refresh the container.                                                      |
| Return yourself.                                                            |
-----------------------------------------------------------------------------*/
   IString
      theProj,
      theDesc,
      theMgr,
      cbAct ;
   LProjectData::Rule
      rule = LProjectData::na;

   projectData.setFirst();
   while ( projectData.getItem( theProj, theDesc, theMgr, cbAct , rule ) )
   {
      addProj( theProj, theDesc, theMgr, cbAct );
      projectData.getNext();
   }

   active.select();
   pCnr->refresh();

   return *this;
}


/******************************************************************************
* Class ProjectPage :: setCells - Set up your multicell canvas cells          *
******************************************************************************/
ProjectPage& ProjectPage::setCells()
{
/*-----------------------------------------------------------------------------
| Add the objects to your multicell canvas.                                   |
| Allow the container to expand horizontally.                                 |
| Allow the page buttons to expand horizontally.                              |
| Return yourself.                                                            |
-----------------------------------------------------------------------------*/
   addToCell( &projText,        2,  2 );
   addToCell( &project,         3,  2 );

   addToCell( &active,          5,  2 );
   addToCell( &activeText,      6,  2 );

   addToCell( &descrText,       2,  3 );
   addToCell( &descr,           3,  3 );

   addToCell( &respMgrText,     2,  4 );
   addToCell( &respMgr,         3,  4 );
   respMgr.setMinimumRows( 1 );

   addToCell( pCnr,             2,  6,  7,  3 );
   addToCell( &pageCnrButtons,  9,  7 );
   setColumnWidth(              8,  0,  true );

   addToCell( &pageButtons,     2,  9,  6,  3 );
   setColumnWidth(              7,  0,  true );

   return *this;
}


/******************************************************************************
* Class ProjectPage :: verifyAndSave - Save page information to the database  *
******************************************************************************/
bool ProjectPage::verifyAndSave( IString& pString,
                                           IString& theEntry,
                                           const IString saveName )
{

/*-----------------------------------------------------------------------------
| If there is no data or is a query, return.                                  |
-----------------------------------------------------------------------------*/
   if ( ( ! saveName.length() )
        && ( ! Key.length() ) )
      return true;

/*-----------------------------------------------------------------------------
| If able to retrieve the container information,                              |
|  save the information to the database based on the key or query name.       |
-----------------------------------------------------------------------------*/
   if ( setProjectData() )
   {
      if ( saveName.length() )
         projectData.save( saveName );
      else
         projectData.save( Key );
   }

   return true;
}


/******************************************************************************
* Class ProjectPage :: setProjectData - Retrieve the page information         *
******************************************************************************/
bool ProjectPage :: setProjectData()
{
   IContainerControl::ObjectCursor
      iterator( *pCnr );

   iterator.setToFirst();
   if ( ! iterator.isValid() )
      return false;

   ProjCnrObj
     *cnrEntry;
   IString
      it1,
      it2;

/*-----------------------------------------------------------------------------
| Empty the bag.                                                              |
| Iterate through the cursor and add objects to the bag.                      |
-----------------------------------------------------------------------------*/
   projectData.emptyBag();
   while ( iterator.isValid() )
   {
      cnrEntry = (ProjCnrObj *) iterator.current();
      projectData.putItem( cnrEntry->proj(),
                           cnrEntry->desc(),
                           cnrEntry->mgr(),
                           cnrEntry->act() );
      cnrEntry = (ProjCnrObj *) iterator.next();
   }

   return true;
}


/******************************************************************************
* Class ProjectPage :: fillEntryfields - Fill the entryfields for the object  *
******************************************************************************/
ProjectPage& ProjectPage::fillEntryfields( ProjCnrObj* pCnrObject )
{
/*-----------------------------------------------------------------------------
| Set the entryfields for the given project container object.                 |
| Return yourself.                                                            |
-----------------------------------------------------------------------------*/
   project.setText( pCnrObject->proj() );
   descr.setText( pCnrObject->desc() );
   respMgr.setText( pCnrObject->mgr() );
   if ( pCnrObject->act() == "yes" )
      active.select();
   else
      active.select( false );

   return *this;
};


/******************************************************************************
* Class ProjectPage :: command - Catch and process command events.            *
******************************************************************************/
bool ProjectPage::command( ICommandEvent& cmdEvent )
{
   IString
      theProj = project.text(),
      theDesc = descr.text(),
      theMgr  = respMgr.text(),
      theAct = ( true == active.isSelected() ) ? "yes" : "no";
   LProjectData::Rule
      theRule = LProjectData::na;
   bool
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
| Reset the project data to the original project data.                        |
| Reset the container.                                                        |
| Reset the entryfields, combobox, and checkbox.                              |
-----------------------------------------------------------------------------*/
      case ID_BUTTON_UNDO:
      {
         projectData = origProjectData;
         fillCnr();
         project.setText( "" );
         descr.setText( "" );
         respMgr.setText( "" );
         active.select();
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
               soc.setToNext())
         {
            ProjCnrObj
              *pObj = (ProjCnrObj *) soc.current();
            projectData.putItem( pObj->proj(),
                                 pObj->desc(),
                                 pObj->mgr(),
                                 pObj->act(),
                                 LProjectData::remove );
            ++count;
         }
         if ( ! count )
         {
            IMessageBox
               warning( owner() );
            warning.show( STR_MSG_REMOVE,
                          IMessageBox::enterButton
                          | IMessageBox::informationIcon );
         }
         else
         {
            pCnr->removeSelectedObjects();
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
            if ( theProj.length() )
            {
               changeProj( theProj, theDesc, theMgr, theAct,
                  (ProjCnrObj*) soc.current() );
               project.setText( "" );
               descr.setText( "" );
               respMgr.setText( "" );
               active.select();
            }

         }
         else
         {
            IMessageBox
               warning( owner() );
            warning.show( STR_MSG_CHANGE,
                          IMessageBox::enterButton
                          | IMessageBox::informationIcon );
         }
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
         if ( theProj.length() )
         {
            addProj( theProj, theDesc, theMgr, theAct );
            project.setText( "" );
            descr.setText( "" );
            respMgr.setText( "" );
            active.select();
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
            show( IResourceId( ID_PROJECT_PAGE ) );
         rc = true;
         break;
      }
   }

   return rc;
}

/******************************************************************************
* Class ProjectPage :: addProj - Add the project information to the container *
******************************************************************************/
bool ProjectPage::addProj( IString& proj, IString& desc,
                                     IString& mgr, IString& act )
{
   bool
      rc = true;

/*-----------------------------------------------------------------------------
| Create a container text cursor based on the project.                        |
-----------------------------------------------------------------------------*/
   IContainerControl::TextCursor
      txtCur( *pCnr, IString( proj ), true, false, true );

   txtCur.setToFirst();
   if ( txtCur.isValid() )
      rc = false;

/*-----------------------------------------------------------------------------
| If the object doesn't exist,                                                |
|  Add the object to the database.                                            |
|  Create a container object.                                                 |
|  Add the object to the container.                                           |
|  Refresh the container.                                                     |
-----------------------------------------------------------------------------*/
   if ( rc )
   {
      projectData.putItem( proj, desc, mgr, act, LProjectData::add );
      pProjCnrObj = new ProjCnrObj( proj, desc, mgr, act );
      pCnr->addObject( pProjCnrObj );
      pCnr->refresh();
   }

   return rc;
}

/******************************************************************************
* Class ProjectPage :: changeProj - Change the project information for the    *
*  selected container object.                                                 *
******************************************************************************/
bool ProjectPage::changeProj( IString& proj, IString& desc,
                                        IString& mgr, IString& act,
                                        ProjCnrObj* pCnrObj )
{
   bool
      rc = true;

/*-----------------------------------------------------------------------------
| Create a container text cursor based on the project.                        |
-----------------------------------------------------------------------------*/
   IContainerControl::TextCursor
      txtCur( *pCnr, IString( proj ), true, false, true );


   txtCur.setToFirst();
   if ( !txtCur.isValid() )
      rc = false;

/*-----------------------------------------------------------------------------
| If the container object exists -and- the project exists,                    |
|  Set the container object's data.                                           |
|  Reset the entryfields.                                                     |
|  Deselect the container objects.                                            |
-----------------------------------------------------------------------------*/
   if ( pCnrObj && rc )
   {
      pCnrObj->setProj( proj );
      pCnrObj->setDesc( desc );
      pCnrObj->setMgr( mgr );
      pCnrObj->setAct( "yes" );

   }

   return rc;
}


/******************************************************************************
* Class ProjectPage :: unMark - Deselect the selected container objects.      *
******************************************************************************/
ProjectPage& ProjectPage::unMark()
{
   IContainerControl::ObjectCursor
      co( *pCnr );
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
   pCnr->refresh();
   return *this;
};


/******************************************************************************
* Class ProjectCnrObj :: ProjectCnrObj - Constructor for project container    *
*  objects.                                                                   *
*                                                                             *
* Define yourself as a container object.                                      *
* Set the project in your private data.                                       *
* Set the description in your private data.                                   *
* Set the manager in your private data.                                       *
* Set the active flag in your private data.                                   *
******************************************************************************/
ProjCnrObj::ProjCnrObj(    const IString& stProj,
                           const IString& stDesc,
                           const IString& stMgr,
                           const IString& stAct )
     :IContainerObject(),
      Proj( stProj ),
      Desc( stDesc ),
      Mgr(  stMgr  ),
      Act(  stAct  )
{}


/******************************************************************************
* Class ProjectCnrObj :: ~ProjectCnrObj - Destructor for project container    *
*  object.                                                                    *
******************************************************************************/
ProjCnrObj :: ~ProjCnrObj()
{}
