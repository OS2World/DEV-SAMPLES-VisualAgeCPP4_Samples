/******************************************************************************
* FILE NAME: linfonb.cpp                                                      *
*                                                                             *
* Classes:                                                                    *
*   LInfoNotebook                                                             *
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
#include <irect.hpp>
#include <ifont.hpp>
#include <istring.hpp>
#include <ireslib.hpp>
#include <ipagehdr.hpp>
#include "linfowin.hpp"
#include "lancelot.h"
#include "linfonb.hpp"
#include "lperswin.hpp"
#include "ldbqry.hpp"
#include "lgoodies.hpp"
#include "lmainwin.hpp"

/******************************************************************************
* Class LInfoNotebook :: LInfoNotebook - Constructor for information notebook *
*   given an employee.                                                        *
*                                                                             *
* Define yourself as an INoteBook                                             *
* Ignore query data                                                           *
* Create the general notebook page                                            *
* Create the account notebook page                                            *
* Create the badge notebook page                                              *
* Create the skill notebook page                                              *
* Create the status notebook page                                             *
* Create the project notebook page                                            *
* Create the task notebook page                                               *
* Create the timecard notebook page                                           *
* Define the general page query as NULL                                       *
* Define the account page query as NULL                                       *
* Define the skill page query as NULL                                         *
* Define the badge page query as NULL                                         *
* Define the status page query as NULL                                        *
******************************************************************************/
LInfoNotebook::LInfoNotebook( IWindow* parent,
                              IWindow* owner,
                              LEmployeeData& employee,
                              Boolean isQuery )
     :INotebook            ( ID_INFO_NOTEBOOK, parent, owner ),
      queryData            ( "" ),
      generalPage          ( this, employee.employeeNumber() ),
      accountPage          ( this, generalPage.key() ),
      badgePage            ( this, generalPage.key() ),
      skillPage            ( this, generalPage.key() ),
      statusPage           ( this, generalPage.key() ),
      pProjectPage         ( new ProjectPage( this, generalPage.key() ) ),
      pTasksPage           ( new TasksPage( this, generalPage.key() ) ),
      pTimeCardPage        ( new TimeCardPage( this, pProjectPage, pTasksPage,
                             generalPage.key() ) ),
      pQueryGenl           ( NULL ),
      pQueryAcct           ( NULL ),
      pQuerySkill          ( NULL ),
      pQueryBadge          ( NULL ),
      pQueryStatus         ( NULL ),
      pCnr                 ( NULL )
{
/*-----------------------------------------------------------------------------
| Start handling any command events for the notebook                          |
-----------------------------------------------------------------------------*/
   ICommandHandler::handleEventsFor( this );

/*-----------------------------------------------------------------------------
| Set the notebook characteristics                                            |
-----------------------------------------------------------------------------*/
   setBinding( INotebook::spiral );
   setOrientation( INotebook::backpagesBottomTabsRight );
   refresh();

/*-----------------------------------------------------------------------------
| In order to correctly size the notebook tabs                                |
| - Get the current font size                                                 |
| - Size the tabs based on the current font size                              |
-----------------------------------------------------------------------------*/
   IFont
      notebookFont( this );
   setTabShape( INotebook::rounded );
   setMajorTabSize( ISize( notebookFont.avgCharWidth() *
                           ID_INFO_NOTEBOOK_TAB_CHARS,
                           notebookFont.avgUppercase() * 2 ) );

/*-----------------------------------------------------------------------------
| Add each page to the notebook                                               |
-----------------------------------------------------------------------------*/
   addLastPage( generalPage.pageSettings(),
                &generalPage );

   addLastPage( accountPage.pageSettings(),
                &accountPage );

   addLastPage( badgePage.pageSettings(),
                &badgePage );

   addLastPage( skillPage.pageSettings(),
                &skillPage );

   addLastPage( statusPage.pageSettings(),
                &statusPage );

   addLastPage( pProjectPage->pageSettings(),
                pProjectPage );

   addLastPage( pTasksPage->pageSettings(),
                pTasksPage );

   phTimeCardPage = addLastPage( pTimeCardPage->pageSettings(),
                                 pTimeCardPage );

/*-----------------------------------------------------------------------------
| When a page is added to a notebook and using the autoPageSize style,        |
| the pages are automatically resized to the current notebook size.           |
| Therefore, we need to resize the notebook pages to their minimum size       |
| so that the notebook can properly calculate it's minimum size.              |
-----------------------------------------------------------------------------*/
   turnToPage( firstPage() );

/*-----------------------------------------------------------------------------
| Start handling any page events for the notebook                             |
-----------------------------------------------------------------------------*/
   IPageHandler::handleEventsFor( this );

/*-----------------------------------------------------------------------------
| When a page is added to a notebook and using the autoPageSize style,        |
| the pages are automatically resized to the current notebook size.           |
| Therefore, we need to resize the notebook pages to their minimum size       |
| so that the notebook can properly calculate it's minimum size.              |
-----------------------------------------------------------------------------*/
   generalPage.sizeTo( generalPage.minimumSize() );
   accountPage.sizeTo( accountPage.minimumSize() );
   badgePage.sizeTo( badgePage.minimumSize() );
   skillPage.sizeTo( skillPage.minimumSize() );
   statusPage.sizeTo( statusPage.minimumSize() );
   pProjectPage->sizeTo( pProjectPage->minimumSize() );
   pTasksPage->sizeTo( pTasksPage->minimumSize() );
   pTimeCardPage->sizeTo( pTimeCardPage->minimumSize() );
}


/******************************************************************************
* Class LInfoNotebook :: LInfoNotebook - Constructor for information notebook *
*   given a query.                                                            *
*                                                                             *
* Define yourself as an INoteBook                                             *
* Store the query data                                                        *
* Create the general notebook page                                            *
* Create the account notebook page                                            *
* Create the badge notebook page                                              *
* Create the skill notebook page                                              *
* Create the status notebook page                                             *
* Define the project notebook page as NULL                                    *
* Define the task notebook page as NULL                                       *
* Define the timecard notebook page as NULL                                   *
* Create the general page query                                               *
* Create the account page query                                               *
* Create the skill page query                                                 *
* Create the badge page query                                                 *
* Create the status page query                                                *
* Store a pointer to the container                                            *
******************************************************************************/
LInfoNotebook::LInfoNotebook( IWindow* parent,
                              IWindow* owner,
                              LMainCnr* cnr,
                              const IString queryName )
     :INotebook            ( ID_INFO_NOTEBOOK, parent, owner ),
      queryData            ( queryName ),
      generalPage          ( this, queryData ),
      accountPage          ( this, queryData ),
      badgePage            ( this, queryData ),
      skillPage            ( this, queryData ),
      statusPage           ( this, queryData ),
      pProjectPage         ( NULL ),
      pTasksPage           ( NULL ),
      pTimeCardPage        ( NULL ),
      pQueryGenl           ( new QueryGenl() ),
      pQueryAcct           ( new QueryAcct() ),
      pQuerySkill          ( new QuerySkill() ),
      pQueryBadge          ( new QueryBadge() ),
      pQueryStatus         ( new QueryStatus() ),
      pCnr                 ( cnr )
{
/*-----------------------------------------------------------------------------
| Start handling any command events for the notebook                          |
-----------------------------------------------------------------------------*/
   ICommandHandler::handleEventsFor( this );

/*-----------------------------------------------------------------------------
| Set the notebook characteristics                                            |
-----------------------------------------------------------------------------*/
   setBinding( INotebook::spiral );
   setOrientation( INotebook::backpagesBottomTabsRight );
   refresh();

/*-----------------------------------------------------------------------------
| In order to correctly size the notebook tabs                                |
| - Get the current font size                                                 |
| - Size the tabs based on the current font size                              |
-----------------------------------------------------------------------------*/
   IFont
      notebookFont( this );
   setTabShape( INotebook::rounded );
   setMajorTabSize( ISize( notebookFont.avgCharWidth() *
                           ID_INFO_NOTEBOOK_TAB_CHARS,
                           notebookFont.avgUppercase() * 2 ) );

/*-----------------------------------------------------------------------------
| Add each page to the notebook                                               |
-----------------------------------------------------------------------------*/
   addLastPage( generalPage.pageSettings(),
                &generalPage );

   addLastPage( accountPage.pageSettings(),
                &accountPage );

   addLastPage( badgePage.pageSettings(),
                &badgePage );

   addLastPage( skillPage.pageSettings(),
                &skillPage );

   addLastPage( statusPage.pageSettings(),
                &statusPage );

/*-----------------------------------------------------------------------------
| When a page is added to a notebook and using the autoPageSize style,        |
| the pages are automatically resized to the current notebook size.           |
| Therefore, we need to resize the notebook pages to their minimum size       |
| so that the notebook can properly calculate it's minimum size.              |
-----------------------------------------------------------------------------*/
   turnToPage( firstPage() );
   generalPage.sizeTo( generalPage.minimumSize() );
   accountPage.sizeTo( accountPage.minimumSize() );
   badgePage.sizeTo( badgePage.minimumSize() );
   skillPage.sizeTo( skillPage.minimumSize() );
   statusPage.sizeTo( statusPage.minimumSize() );
}


/******************************************************************************
* Class LInfoNotebook :: ~LInfoNotebook - Destructor for the info window      *
******************************************************************************/
LInfoNotebook::~LInfoNotebook()
{
/*-----------------------------------------------------------------------------
| Delete the dynamically allocated notebook pages.                            |
-----------------------------------------------------------------------------*/
   delete( pProjectPage );
   delete( pTasksPage );
   delete( pTimeCardPage );

/*-----------------------------------------------------------------------------
| Delete the dynamically allocated notebook page queries.                     |
-----------------------------------------------------------------------------*/
   delete( pQueryGenl );
   delete( pQueryAcct );
   delete( pQuerySkill );
   delete( pQueryBadge );
   delete( pQueryStatus );
}


/******************************************************************************
* Class LInfoNotebook :: verifyPages                                          *
*   Verify data for each notebook page and save to the database               *
******************************************************************************/
IBase::Boolean LInfoNotebook::verifyPages( IString queryName )
{
   Boolean
      retCode = true;
   IString
      badString,
      badControl;
   IString
      message = IApplication::current().userResourceLibrary().
                loadString( STR_INCOMPLETE_DATA );

/*-----------------------------------------------------------------------------
| Verify and save each page                                                   |
-----------------------------------------------------------------------------*/
   try
   {
      if ( !generalPage.verifyAndSave( badString, badControl, queryName ) )
      {
         IMessageBox
            msg( parent() );
         msg.show( badControl +
                   " " + message + " " +
                   badString,
                   IMessageBox::catastrophic );
         retCode = false;
      }
      else if ( !accountPage.verifyAndSave( badString, badControl,
                                            generalPage.key() ) )
      {
         IMessageBox
            msg( parent() );
         msg.show( badControl +
                   " " + message + " " +
                   badString,
                   IMessageBox::catastrophic );
         retCode = false;
      }
      else if ( !badgePage.verifyAndSave( badString, badControl,
                                          generalPage.key() ) )
      {
         IMessageBox
            msg( parent() );
         msg.show( badControl +
                   " " + message + " " +
                   badString,
                   IMessageBox::catastrophic );
         retCode = false;
      }
      else if ( !skillPage.verifyAndSave( badString, badControl,
                                          generalPage.key() ) )
      {
         IMessageBox
            msg( parent() );
         msg.show( badControl +
                   " " + message + " " +
                   badString,
                   IMessageBox::catastrophic );
         retCode = false;
      }
      else if ( !statusPage.verifyAndSave( badString, badControl,
                                           generalPage.key() ) )
      {
         IMessageBox
            msg( parent() );
         msg.show( badControl +
                   " " + message + " " +
                   badString,
                   IMessageBox::catastrophic );
         retCode = false;
      }
      else if ( pProjectPage )
      {
         if ( !pProjectPage->verifyAndSave( badString, badControl,
                                            generalPage.key() ) )
         {
            IMessageBox
               msg( parent() );
            msg.show( badControl +
                      " " + message + " " +
                      badString,
                      IMessageBox::catastrophic );
            retCode = false;
         }
      }
      if ( pTasksPage)
      {
         if ( !pTasksPage->verifyAndSave( badString, badControl,
                                          generalPage.key() ) )
         {
            IMessageBox
               msg( parent() );
            msg.show( badControl +
                      " " + message + " " +
                      badString,
                      IMessageBox::catastrophic );
            retCode = false;
         }
      }
      if ( pTimeCardPage )
      {
         if ( !pTimeCardPage->verifyAndSave( badString, badControl,
                                             generalPage.key() ) )
         {
            IMessageBox
               msg( parent() );
            msg.show( badControl +
                      " " + message + " " +
                      badString,
                      IMessageBox::catastrophic );
            retCode = false;
         }
      }

    return retCode;

   }
   catch ( IAccessError& exc )
   {
      IMessageBox
         msgBox( this );
      IString
         expt = exc.text();
      if ( ( expt == "PrfQueryProfileData" ) ||
           ( expt == "PrfOpenProfile" ) ||
           ( expt == "PrfWriteProfileString" ) ||
           ( expt == "PrfWriteProfileData" ) )
         msgBox.show( STR_DB_ERROR,
                      IMessageBox::okButton
                      | IMessageBox::errorIcon );
      else
         msgBox.show( STR_DB_UNKNOWN_ERROR,
                      IMessageBox::okButton
                      | IMessageBox::errorIcon );
   }

  return retCode;
}


/******************************************************************************
* Class LInfoNotebook :: command - Catch and process command events.          *
******************************************************************************/
IBase::Boolean LInfoNotebook::command( ICommandEvent& event )
{
   Boolean
      retCode = false;

   switch ( event.commandId() )
   {
/*-----------------------------------------------------------------------------
| If the user pressed the QUERY button                                        |
-----------------------------------------------------------------------------*/
      case ID_BUTTON_QUERY :
      {
         IString
            aId,
            allIds;;
         IMessageBox
            msgBox( this );
/*-----------------------------------------------------------------------------
| If the database is empty, ask user if they want to create a new employee    |
-----------------------------------------------------------------------------*/
         if ( pQueryGenl->isDBempty() )
         {
            IMessageBox::Response
               choice = msgBox.show( STR_DB_EMPTY,
                                    IMessageBox::queryIcon
                                    | IMessageBox::yesNoButton
                                    | IMessageBox::defButton1 );
            if ( choice == IMessageBox::yes )
            {
/*-----------------------------------------------------------------------------
| Create a new employee                                                       |
| - Create a "blank" person                                                   |
| - Create an information window to collect the data                          |
| - Delete the information window when no longer valid                        |
-----------------------------------------------------------------------------*/
               LEmployeeData
                  tempData( "" );
               LInfoWindow
                  *pNewEmp = new LInfoWindow( ID_INFO_WINDOW, 0, owner(),
                                              IPoint( 100, 100 ),
                                              NULL,
                                              tempData,
                                              false );
               pNewEmp->setAutoDeleteObject( true );
            }
         }
         else
         {
/*-----------------------------------------------------------------------------
| Query the database for each page's search criteria                          |
-----------------------------------------------------------------------------*/
            delete( pQueryGenl );
            delete( pQueryAcct );
            delete( pQuerySkill );
            delete( pQueryBadge );
            delete( pQueryStatus );

            pQueryGenl = new QueryGenl();
            pQueryAcct = new QueryAcct();
            pQuerySkill = new QuerySkill();
            pQueryBadge = new QueryBadge();
            pQueryStatus = new QueryStatus();

/*-----------------------------------------------------------------------------
| General page query                                                          |
-----------------------------------------------------------------------------*/
            pQueryGenl->getMatchList( generalPage );
            if ( pQueryGenl->numberOfMatches() )
            {
               pQueryGenl->setFirstMatchId();
               while ( pQueryGenl->getMatchId( aId ) )
               {
                  pQueryGenl->getNextMatchId();
               }
            }

/*-----------------------------------------------------------------------------
| Account page query                                                          |
-----------------------------------------------------------------------------*/
            pQueryAcct->getMatchList( accountPage );
            if ( pQueryAcct->numberOfMatches() )
            {
               pQueryAcct->setFirstMatchId();
               while ( pQueryAcct->getMatchId( aId ) )
               {
                  pQueryAcct->getNextMatchId();
               }
            }

/*-----------------------------------------------------------------------------
| Badge page query                                                            |
-----------------------------------------------------------------------------*/
            pQueryBadge->getMatchList( badgePage );
            if ( pQueryBadge->numberOfMatches() )
            {
               pQueryBadge->setFirstMatchId();
               while ( pQueryBadge->getMatchId( aId ) )
               {
                  pQueryBadge->getNextMatchId();
               }
            }

/*-----------------------------------------------------------------------------
| Skill page query                                                            |
-----------------------------------------------------------------------------*/
            pQuerySkill->getMatchList( skillPage );
            if ( pQuerySkill->numberOfMatches() )
            {
               pQuerySkill->setFirstMatchId();
               while ( pQuerySkill->getMatchId( aId ) )
               {
                  pQuerySkill->getNextMatchId();
               }
            }

/*-----------------------------------------------------------------------------
| Status page query                                                           |
-----------------------------------------------------------------------------*/
            pQueryStatus->getMatchList( statusPage );
            if ( pQueryStatus->numberOfMatches() )
            {
               pQueryStatus->setFirstMatchId();
               while ( pQueryStatus->getMatchId( aId ) )
               {
                  pQueryStatus->getNextMatchId();
               }
            }

/*-----------------------------------------------------------------------------
| Get the intersection of each page's search results                          |
-----------------------------------------------------------------------------*/
            QueryIntersection
               bagOfIds = QueryIntersection( pQueryGenl,
                                             pQuerySkill,
                                             pQueryAcct,
                                             pQueryStatus,
                                             pQueryBadge );

/*-----------------------------------------------------------------------------
| If the search is not empty,                                                 |
| - Create a personnel window with a list of employees                        |
| - Delete the personnel window when no longer valid                          |
-----------------------------------------------------------------------------*/
            if ( !bagOfIds.isIntersectionEmpty() )
            {
               LPersonnelWindow
                 *persWin = new LPersonnelWindow( owner()->owner(),
                                                  bagOfIds,
                                                  pQueryGenl->deptQuery() );
               persWin->setAutoDeleteObject( true );
            }
            else
/*-----------------------------------------------------------------------------
| No match found                                                              |
-----------------------------------------------------------------------------*/
            msgBox.show( STR_DB_NO_MATCH,
                         IMessageBox::okButton
                         | IMessageBox::informationIcon );
         }
         retCode = true;
         break;
      }

      case ID_BUTTON_SAVE:
      {
         Boolean
            isNewObject;
/*-----------------------------------------------------------------------------
| Ask the user for a name for the query                                       |
-----------------------------------------------------------------------------*/
         LAskUser
            askUser( ID_ASKUSER, IWindow::desktopWindow(), this,
                     IApplication::current().userResourceLibrary().
                     loadString( STR_ENTER_QUERY_NAME ) );
         if ( askUser.pressedOk() )
         {
            IString
               queryName = askUser.text();
            if ( queryName.length() )
            {
/*-----------------------------------------------------------------------------
| Fill the page                                                               |
| Write the query data                                                        |
-----------------------------------------------------------------------------*/
               pQueryGenl->fillPage( generalPage );
               pQueryGenl->saveToQueryData( &queryData, "GENERAL " );

               pQueryAcct->fillPage( accountPage );
               pQueryAcct->saveToQueryData( &queryData, "ACCOUNT " );

               pQueryBadge->fillPage( badgePage );
               pQueryBadge->saveToQueryData( &queryData,"BADGE " );

               pQuerySkill->fillPage( skillPage );
               pQuerySkill->saveToQueryData( &queryData,"SKILL " );

               pQueryStatus->fillPage( statusPage );
               pQueryStatus->saveToQueryData( &queryData,"STATUS " );

/*-----------------------------------------------------------------------------
| Attempt to save the query data to an IProfile                               |
-----------------------------------------------------------------------------*/
               try
               {
                  isNewObject = queryData.saveIni( queryName );
               }
               catch ( IAccessError& exc )
               {
                  IMessageBox
                     msgBox( this );
                  IString
                     expt = exc.text();
                  if ( ( expt == "PrfQueryProfileData" ) ||
                       ( expt == "PrfOpenProfile" ) ||
                       ( expt == "PrfWriteProfileString" ) ||
                       ( expt == "PrfWriteProfileData" ) )
                     msgBox.show( STR_DB_ERROR,
                                  IMessageBox::okButton
                                  | IMessageBox::errorIcon );
                  else
                     msgBox.show( STR_DB_UNKNOWN_ERROR,
                                  IMessageBox::okButton
                                  | IMessageBox::errorIcon );
                  retCode = true;
               }
 
               unsigned long
                  whichMsg = STR_SAVED_QUERY_NAME;

               if ( isNewObject )
               {
                  if ( pCnr )
                     pCnr->addLastQuery( queryName );
               }
               else
                  whichMsg = STR_REPLACED_QUERY_NAME;

               IMessageBox
                  msg( this );
               msg.show( IApplication::current().userResourceLibrary().
                         loadString( whichMsg ) +
                         "'" + queryName + "'.",
                         IMessageBox::informationIcon
                         | IMessageBox::okButton );
               retCode = true;
            }
         }
         break;
      }
   }

   return retCode;
}


/******************************************************************************
* Class LInfoNotebook :: select - Catch and process select events.            *
******************************************************************************/
IBase::Boolean LInfoNotebook::select( IPageSelectEvent& pageevt )
{
   IPageHandle
      testPage;
   IString
      pString,
      theEntry;

   testPage = pageevt.previousSelectedPageHandle();

/*-----------------------------------------------------------------------------
| Verify the page.  If an error, turn to previous page.                       |
-----------------------------------------------------------------------------*/
   if ( testPage != topPage() )
   {
      if ( topPage() == phTimeCardPage )
      {
/*-----------------------------------------------------------------------------
| Update dropdown comboboxes.                                                 |
-----------------------------------------------------------------------------*/
         pTimeCardPage->fillCBagain();
         return false;
      }
   }

   return false;
}
