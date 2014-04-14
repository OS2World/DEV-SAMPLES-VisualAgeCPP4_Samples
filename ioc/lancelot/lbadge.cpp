/******************************************************************************
* .FILE:         lbadge.cpp                                                   *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Implementation   *
*                                                                             *
* .CLASSES:      BadgePage                                                    *
*                BadgeCnrObj                                                  *
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
#include <ireslib.hpp>
#include <ihelp.hpp>
#include "lancelot.h"

#include "lbadge.hpp"

//--------------------------------------------------------------------------
//  CLASS BadgePage - BadgePage - constructor
//--------------------------------------------------------------------------
BadgePage :: BadgePage(IWindow* pParent,
                       const IString& aKey)
          : IMultiCellCanvas(ID_BADGE_PAGE, pParent, pParent),
            badgeData(aKey),
            pageButtons( ID_BADGE_PAGE_BUTTONS,
                         this, this, false),
            pIssueRange(NULL),
            pExpRange(NULL),
            badgeNumberText(ID_NO_ITEM, this, this ),
            issueDateText(ID_NO_ITEM, this, this ),
            expDateText(ID_NO_ITEM, this, this ),
            BadgeNumber(ID_BDG_BADGE_NUMBER_EF, this, this,
                        IRectangle(),
                        IEntryField::classDefaultStyle |
                        IControl::tabStop),
            IssueDate(ID_BDG_ISSUE_DATE_EF, this, this,
                      IRectangle(),
                      IEntryField::classDefaultStyle |
                      IControl::tabStop),
            ExpDate(ID_BDG_EXP_DATE_EF, this, this,
                    IRectangle(),
                    IEntryField::classDefaultStyle |
                    IControl::tabStop),
            Key(aKey),
            thePageSettings( IApplication::current().userResourceLibrary().loadString(
                              STR_BDG_BADGE_TAB), NULL,
                              INotebook::PageSettings::autoPageSize
                            | INotebook::PageSettings::majorTab ),
            isAquery(false)
{
   badgeNumberText.setText( STR_BDG_BADGE_NUMBER);
   issueDateText.setText(   STR_BDG_ISSUE_DATE  );
   expDateText.setText(     STR_BDG_EXP_DATE    );

   BadgeNumber.setLimit(DISPLAY_LIMIT);
   IssueDate.setLimit(DISPLAY_LIMIT);
   ExpDate.setLimit(DISPLAY_LIMIT);

   displayData();
   setCells();
   handleIt();
}

//--------------------------------------------------------------------------
//  CLASS BadgePage - BadgePage - constructor
//--------------------------------------------------------------------------
BadgePage :: BadgePage(IWindow* pParent, LQueryData& qd)
          : IMultiCellCanvas(ID_BADGE_PAGE, pParent, pParent),
            badgeData(qd),
            pageButtons( ID_BADGE_PAGE_BUTTONS,
                         this, this, true),
            pIssueRange(NULL),
            pExpRange(NULL),
            badgeNumberText(ID_NO_ITEM, this, this ),
            issueDateText(ID_NO_ITEM, this, this ),
            expDateText(ID_NO_ITEM, this, this ),
            BadgeNumber(ID_BDG_BADGE_NUMBER_EF, this, this ),
            IssueDate(ID_BDG_ISSUE_DATE_EF, this, this ),
            ExpDate(ID_BDG_EXP_DATE_EF, this, this ),
            Key(qd.queryName()),
            thePageSettings( IApplication::current().userResourceLibrary().loadString(
                              STR_BDG_BADGE_TAB), NULL,
                              INotebook::PageSettings::autoPageSize
                            | INotebook::PageSettings::majorTab ),
            isAquery(true)
{
   badgeNumberText.setText( STR_BDG_BADGE_NUMBER);
   issueDateText.setText(   STR_BDG_ISSUE_DATE  );
   expDateText.setText(     STR_BDG_EXP_DATE    );

   BadgeNumber.setLimit(DISPLAY_LIMIT);
   IssueDate.setLimit(DISPLAY_LIMIT);
   ExpDate.setLimit(DISPLAY_LIMIT);

   pIssueRange = new QueryRange( ID_BADGE_PAGE_RANGE_EF1
                                   , this
                                   , this
                                   , ID_BADGE_RANGE_1);

   pExpRange = new QueryRange( ID_BADGE_PAGE_RANGE_EF2
                                 , this
                                 , this
                                 , ID_BADGE_RANGE_2);

   displayData();
   setCells();
   handleIt();
}

//--------------------------------------------------------------------------
// CLASS BadgePage- ~BadgePage - destructor
//--------------------------------------------------------------------------
BadgePage :: ~BadgePage()
{
   ICommandHandler::stopHandlingEventsFor( &pageButtons );
   ISelectHandler::stopHandlingEventsFor( &pageButtons );
}


//--------------------------------------------------------------------------
// CLASS BadgePage- setCells()   set up multi cell
//--------------------------------------------------------------------------
BadgePage&  BadgePage :: setCells()
{
   addToCell(&badgeNumberText, 2,  2);
   addToCell(&BadgeNumber    , 2,  3);

   addToCell(&issueDateText  , 2,  5);
   addToCell(&IssueDate      , 2,  6);

   if (pIssueRange != NULL)
       addToCell(pIssueRange,  3,  6,  5,  3);

   addToCell(&expDateText    , 2,  8);
   addToCell(&ExpDate        , 2,  9);

   if (pExpRange != NULL)
      addToCell(pExpRange,     3,  9,  5,  3);

   addToCell(&pageButtons,     2, 12,  7,  3);
   setColumnWidth( 8, 0, true );

   return *this;
}

//*****************************************************************************
// CLASS BadgePage :: handleIt()
//*****************************************************************************
BadgePage&  BadgePage :: handleIt()
{
   ICommandHandler::handleEventsFor( &pageButtons );
   ISelectHandler::handleEventsFor( &pageButtons );
   return *this;
}

//--------------------------------------------------------------------------
// CLASS BadgePage- verifyAndSave()  save database info
//--------------------------------------------------------------------------
bool BadgePage :: verifyAndSave( IString& theString,
                                             IString& theEntry,
                                             const IString& theName )
{

  // verify input

    if ((theName.length() == 0) && (Key.length() == 0)
       || isAquery)
       return true;

    if ((theName.length() > 0 ) && (theName.isAlphanumeric()))
       badgeData.save( theName
                    ,BadgeNumber.text()
                    ,IssueDate.text()
                    ,ExpDate.text() ) ;
    else
      if ((Key.length() > 0 ) && (Key.isAlphanumeric()))
         badgeData.save( Key
                    ,BadgeNumber.text()
                    ,IssueDate.text()
                    ,ExpDate.text() ) ;

     return (true);
}



//--------------------------------------------------------------------------
// CLASS BadgePage- displayData()  data to page
//--------------------------------------------------------------------------
BadgePage&  BadgePage :: displayData()
{

   BadgeNumber.setText(badgeData.badgeNumber() );
   IssueDate.setText(badgeData.badgeIssue()    );
   ExpDate.setText(badgeData.badgeExpire()    );


   if (badgeData.theIssueRange().length()  != 0)
      pIssueRange->setRange(badgeData.theIssueRange());

   if (badgeData.theExpRange().length()  != 0)
      pExpRange->setRange(badgeData.theIssueRange());

   return *this;
}



//--------------------------------------------------------------------------
// CLASS BadgePage- command()
//--------------------------------------------------------------------------
bool BadgePage :: command(ICommandEvent &cmdEvent)
{

  switch (cmdEvent.commandId()) {       //Get command id

    case ID_BUTTON_UNDO:                       //Get the original data back
      this->displayData();
      return(true);                     //Return command processed
      break;                            //

    case ID_BUTTON_HELP:
       // Product Information processing
       IHelpWindow::helpWindow( this )->show(
           IResourceId( ID_BADGE_PAGE ) );
       return true;

  } /* end switch */                    //

  return(false);                        //Return command not processed

}


//--------------------------------------------------------------------------
// CLASS BadgePage- pageSettings - notebook sizing
//--------------------------------------------------------------------------
INotebook :: PageSettings BadgePage :: pageSettings()
{
   return thePageSettings;
}

