/*******************************************************************************
* FILE NAME: ltask.cpp                                                         *
*                                                                              *
* DESCRIPTION:                                                                 *
*                                                                              *
* Classes                                                                      *
*   TasksPage                                                                  *
*   TaskCnrObj                                                                 *
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

#ifndef _IBASE_                         //Make sure ibase.hpp is included
  #include <ibase.hpp>                  //  since that is where IC_<environ>
#endif                                  //  is defined.
#include <ireslib.hpp>
#include <ihelp.hpp>
#include <iexcbase.hpp>
#include "ltask.hpp"
#include "lancelot.h"

/******************************************************************************
* Class TasksPage :: TasksPage - Constructor for the task page                *
*                                                                             *
* Define yourself as an IMultiCellCanvas                                      *
* Create generic page buttons                                                 *
* Create generic page container buttons                                       *
* Create static text for the task                                             *
* Create static text for the billable status                                  *
* Create static text for the description                                      *
* Create static text for the responsible manager                              *
* Create entryfield for the task                                              *
* Create checkbox for the active status                                       *
* Create entryfield for the description                                       *
* Define a null container pointer                                             *
* Define a null container object pointer                                      *
* Define a null container column pointer                                      *
* Define a null container column pointer                                      *
* Create an task data object given the key                                    *
* Create a empty task data object                                             *
* Set the key in your private data                                            *
* Create the notebook page settings                                           *
* Create a alphanumeric handler (MOTIF only)                                  *
* Create a container select handler                                           *
******************************************************************************/
TasksPage::TasksPage       ( IWindow* pParent,
                             const IString& aKey )
     :IMultiCellCanvas     ( ID_TASK_PAGE, pParent, pParent ),
      pageButtons          ( ID_TASK_PAGE_BUTTONS, this, this, false ),
      pageCnrButtons       ( ID_TASK_PAGE_CNRBUTTONS, this, this, false ),
      taskText             ( ID_NO_ITEM, this, this ),
      billableText         ( ID_NO_ITEM, this, this ),
      descrText            ( ID_NO_ITEM, this, this ),
//    currentTasksText     ( ID_NO_ITEM, this, this ),
//    descr2Text           ( ID_NO_ITEM, this, this ),
//    billable2Text        ( ID_NO_ITEM, this, this ),
      task                 ( ID_TSK_TASK_EF, this, this,
                             IRectangle(),
                             IEntryField::classDefaultStyle
                           | IControl::tabStop ),
      billable             ( ID_TSK_BILLABLE_CB, this, this ),
      descr                ( ID_TSK_DESCR_EF, this, this,
                             IRectangle(),
                             IEntryField::classDefaultStyle
                             | IControl::tabStop ),
      pCnr                 ( (IContainerControl*) NULL ),
      pTaskCnrObj          ( (TaskCnrObj*) NULL ),
      pColTask             ( (IContainerColumn*) NULL ),
      pColBill             ( (IContainerColumn*) NULL ),
      taskData             ( aKey ),
      origTaskData         (),
      Key                  ( aKey ),
      thePageSettings      ( IApplication::current().userResourceLibrary().
                             loadString( STR_TSK_TASKS_TAB ), NULL,
                             INotebook::PageSettings::autoPageSize
                             | INotebook::PageSettings::majorTab ),
      cnrSelHandler        ( this )
{
/*-----------------------------------------------------------------------------
| Save the task data to another object in case the user wishes to             |
|  undo any changes.                                                          |
| Label the static text objects.                                              |
| Set the limit for the entryfields.                                          |
-----------------------------------------------------------------------------*/
   origTaskData = taskData;
   taskText.setText( STR_TSK_TASK );
   billableText.setText( STR_TSK_BILLABLE );
   descrText.setText( STR_TSK_DESCR );
   task.setLimit( DISPLAY_LARGE );
   descr.setLimit( DISPLAY_LARGE );

/*-----------------------------------------------------------------------------
| Fill the container from the database.                                       |
| Set the objects on yourself (IMultiCellCanvas).                             |
| Start handling the events.                                                  |
-----------------------------------------------------------------------------*/
   fillCnr();
   setCells();
   handleIt();
}

/******************************************************************************
* Class TaskPage :: ~TaskPage - Destructor for the task page                  *
******************************************************************************/
TasksPage :: ~TasksPage()
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
* Class ProjectPage :: handleIt()                                             *
******************************************************************************/
TasksPage&  TasksPage :: handleIt()
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
TasksPage& TasksPage::fillCnr()
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
      pCnr = new IContainerControl( ID_TSK_CNR,
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

/*-----------------------------------------------------------------------------
| Create four container columns.                                              |
-----------------------------------------------------------------------------*/
      pColTask =
         new IContainerColumn( pTaskCnrObj->taskOffset(),
                               IContainerColumn::defaultHeadingStyle(),
                               IContainerColumn::string );

      pColDesc =
         new IContainerColumn( pTaskCnrObj->descOffset(),
                               IContainerColumn::defaultHeadingStyle(),
                               IContainerColumn::string );

      pColBill =
         new IContainerColumn( pTaskCnrObj->billOffset(),
                               IContainerColumn::defaultHeadingStyle(),
                               IContainerColumn::string );

/*-----------------------------------------------------------------------------
| Label the container column headings.                                        |
| Show the headings.                                                          |
| Show the headings.                                                          |
-----------------------------------------------------------------------------*/
      pColTask->setHeadingText( STR_TSK_CURR );
      pColDesc->setHeadingText( STR_TSK_DESCR2 );
      pColBill->setHeadingText( STR_TSK_BILLABLE2 );
     pCnr->showDetailsViewTitles();

/*-----------------------------------------------------------------------------
| Add the columns to the container.                                           |
| Add column separators between the columns.                                  |
-----------------------------------------------------------------------------*/
      pCnr->addColumn( pColTask );
      pCnr->addColumn( pColDesc );
      pCnr->addColumn( pColBill );
      pColTask->showSeparators( IContainerColumn::verticalSeparator
                                | IContainerColumn::horizontalSeparator );
      pColDesc->showSeparators( IContainerColumn::verticalSeparator
                                | IContainerColumn::horizontalSeparator );
      pColBill->showSeparators( IContainerColumn::horizontalSeparator );
   }

/*-----------------------------------------------------------------------------
| Start from the beginning of the task data.                                  |
| While there exists items,                                                   |
|   add objects to the container.                                             |
| Refresh the container.                                                      |
| Return yourself.                                                            |
-----------------------------------------------------------------------------*/
   IString
      theTask,
      theDesc,
      theBill;
   LTaskData::Rule
      rule;

   taskData.setFirst();
   while ( taskData.getItem( theTask, theDesc, theBill, rule ) )
   {
      addTask( theTask, theDesc, theBill );
      taskData.getNext();
   }

   billable.select();
   pCnr->refresh();

   return *this;
}


/******************************************************************************
* Class TasksPage :: setCells - Set up your multicell canvas cells            *
******************************************************************************/
TasksPage& TasksPage::setCells()
{
/*-----------------------------------------------------------------------------
| Add the objects to your multicell canvas.                                   |
| Allow the container to expand horizontally.                                 |
| Allow the page buttons to expand horizontally.                              |
| Return yourself.                                                            |
-----------------------------------------------------------------------------*/
   addToCell( &taskText,         2,  2 );
   addToCell( &task,             2,  4 );

   addToCell( &billable,         4,  4 );
   addToCell( &billableText,     5,  4 );

   addToCell( &descrText,        2,  5 );
   addToCell( &descr,            2,  6 );

   addToCell( pCnr,              2,  8,  6,  3 );
   addToCell( &pageCnrButtons,   8,  9 );
   setColumnWidth(               7,  0, true );

   addToCell( &pageButtons,      2, 11,  5,  3 );
   setColumnWidth(               6,  0,  true );

   return *this;
}


/******************************************************************************
* Class TasksPage :: verifyAndSave - Save page information to the database    *
******************************************************************************/
IBase::Boolean TasksPage::verifyAndSave( IString& theString,
                                         IString& theEntry,
                                         const IString theName )
{

/*-----------------------------------------------------------------------------
| If there is no data or is a query, return.                                  |
-----------------------------------------------------------------------------*/
   if ( ( ! theName.length() )
        && ( ! Key.length() ) )
      return true;

/*-----------------------------------------------------------------------------
| If able to retrieve the container information,                              |
|  save the information to the database based on the key or query name.       |
-----------------------------------------------------------------------------*/
   if ( setTasksData() )
   {
      if ( theName.length() )
         taskData.save( theName );
      else
         taskData.save( Key );
   }

   return true;
}


/******************************************************************************
* Class TasksPage :: setTasksData - Retrieve the page information             *
******************************************************************************/
IBase::Boolean TasksPage::setTasksData()
{
   IContainerControl::ObjectCursor
      iterator( *pCnr );

   iterator.setToFirst();
   if ( ! iterator.isValid() )
      return false;

   TaskCnrObj
     *cnrEntry;
   IString
      it1,
      it2;

/*-----------------------------------------------------------------------------
| Empty the bag.                                                              |
| Iterate through the cursor and add objects to the bag.                      |
-----------------------------------------------------------------------------*/
   taskData.emptyBag();
   while ( iterator.isValid() )
   {
      cnrEntry = (TaskCnrObj *) iterator.current();
      this->taskData.putItem( cnrEntry->task(),
                              cnrEntry->desc(),
                              cnrEntry->bill() );
      cnrEntry = (TaskCnrObj *) iterator.next();
   }

   return true;
};

/******************************************************************************
* Class TasksPage :: fillEntryfields - Fill the entryfields for the object    *
******************************************************************************/
TasksPage& TasksPage::fillEntryfields( TaskCnrObj* pCnrObject )
{
/*-----------------------------------------------------------------------------
| Set the entryfields for the given task container object.                    |
| Return yourself.                                                            |
-----------------------------------------------------------------------------*/
   task.setText( pCnrObject->task() );
   descr.setText( pCnrObject->desc() );
   if ( pCnrObject->bill() == "yes" )
      billable.select();
   else
      billable.select( false );

   return *this;
};


/******************************************************************************
* Class TasksPage :: command - Catch and process command events.              *
******************************************************************************/
IBase::Boolean TasksPage::command( ICommandEvent& cmdEvent )
{
   IString
      theTask = task.text(),
      theDesc = descr.text(),
      theBill = ( true == billable.isSelected() ) ? "yes" : "no";
   LTaskData::Rule
      theRule = LTaskData::na;
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
| Reset the task data to the original task data.                              |
| Reset the container.                                                        |
| Reset the entryfields and checkbox.                                         |
-----------------------------------------------------------------------------*/
      case ID_BUTTON_UNDO:
      {
         taskData = origTaskData;
         fillCnr();
         task.setText("");
         descr.setText("");
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
            TaskCnrObj *pObj = (TaskCnrObj *) soc.current();
            taskData.putItem( pObj->task(),
                              pObj->desc(),
                              pObj->bill(),
                              LTaskData::remove );
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
            if ( theTask.length() )
            {
               changeTask( theTask, theDesc, theBill,
                  (TaskCnrObj*) soc.current() );
               task.setText( "" );
               descr.setText( "" );
               billable.select();
            }
         }
         else
         {
             IMessageBox warning(owner());
             warning.show( STR_MSG_CHANGE,
                        IMessageBox::enterButton |
                        IMessageBox::informationIcon);
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
         if ( theTask.length() )
         {
            addTask( theTask, theDesc, theBill );
            task.setText( "" );
            descr.setText( "" );
            billable.select();
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
            show( IResourceId( ID_TASK_PAGE ) );
         rc = true;
         break;
      }
  }

  return rc;
}

/******************************************************************************
* Class TaskPage :: addTask - Add the task information to the container       *
******************************************************************************/
IBase::Boolean TasksPage::addTask( IString& theTask, IString& theDesc,
                                   IString& theBill )
{
   Boolean
      rc = true;

/*-----------------------------------------------------------------------------
| Create a container text cursor based on the task.                           |
-----------------------------------------------------------------------------*/
   IContainerControl::TextCursor
      txtCur( *pCnr, IString( theTask ), true, false, true );

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
      taskData.putItem( theTask, theDesc, theBill, LTaskData::add );
      pTaskCnrObj = new TaskCnrObj( theTask, theDesc, theBill );
      pCnr->addObject( pTaskCnrObj );
      pCnr->refresh();
   }

   return rc;
}

/******************************************************************************
* Class TaskPage :: changeTask - Change the task information for the          *
*  selected container object.                                                 *
******************************************************************************/
IBase::Boolean TasksPage::changeTask( IString& theTask, IString& theDesc,
                                     IString& theBill,
                                     TaskCnrObj* pCnrObj )
{
   Boolean
      rc = true;

/*-----------------------------------------------------------------------------
| Create a container text cursor based on the task.                           |
-----------------------------------------------------------------------------*/
   IContainerControl::TextCursor
      txtCur( *pCnr, IString( theTask ), true, false, true );


   txtCur.setToFirst();
   if ( !txtCur.isValid() )
      rc = false;

/*-----------------------------------------------------------------------------
| If the container object exists -and- the task exists,                       |
|  Set the container object's data.                                           |
|  Reset the entryfields.                                                     |
|  Deselect the container objects.                                            |
-----------------------------------------------------------------------------*/
   if ( pCnrObj && rc )
   {
      pCnrObj->setTask( theTask );
      pCnrObj->setDesc( theDesc );
      pCnrObj->setBill( theBill );

   }

   return rc;
}


/******************************************************************************
* Class TasksPage :: unMark - Deselect the selected container objects.        *
******************************************************************************/
TasksPage& TasksPage :: unMark()
{
   IContainerControl::ObjectCursor
      co( *pCnr );
   for ( co.setToFirst();
         co.isValid();
         co.setToNext() )
   {
      try
      {
         pCnr->removeSelected(pCnr->objectAt( co ) );
      }
      catch ( IException& exc )
      {}
   }

   return *this;
};


/******************************************************************************
* Class TasksCnrObj :: TasksCnrObj - Constructor for tasks container          *
*  objects.                                                                   *
*                                                                             *
* Define yourself as a container object.                                      *
* Set the task in your private data.                                          *
* Set the description in your private data.                                   *
* Set the billable flag in your private data.                                 *
******************************************************************************/
TaskCnrObj::TaskCnrObj( const IString& stTask,
                        const IString& stDesc,
                        const IString& stBill )
     :IContainerObject(),
      Task( stTask ),
      Desc( stDesc ),
      Bill( stBill )
{}


/******************************************************************************
* Class TasksCnrObj :: ~TasksCnrObj - Destructor for task container           *
*  object.                                                                    *
******************************************************************************/
TaskCnrObj::~TaskCnrObj()
{}
