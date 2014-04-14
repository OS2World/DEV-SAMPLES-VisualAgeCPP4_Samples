/*******************************************************************************
* FILE NAME: lstatus.cpp                                                       *
*                                                                              *
* DESCRIPTION:                                                                 *
*                                                                              *
* Classes                                                                      *
*   StatusCnrObj                                                               *
*   StatusPage                                                                 *
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
#include "lancelot.h"
#include "lstatus.hpp"
#include "lpagectl.hpp"

//-----------------------------------------------------------------------------
// CLASS StatusPage - constructor
//-----------------------------------------------------------------------------
StatusPage :: StatusPage(IWindow* pParent,
                         const IString& aKey)
          : IMultiCellCanvas(ID_STATUS_PAGE, pParent, pParent),
            pageButtons( ID_STATUS_PAGE_BUTTONS,
                         this, this, false ),
            statusText(ID_NO_ITEM, this, this ),
            activeText(ID_NO_ITEM, this, this ),
            startDateText(ID_NO_ITEM, this, this ),
            endDateText(ID_NO_ITEM, this, this ),
            rateText(ID_NO_ITEM, this, this ),
            pActiveCheckBox(NULL),
            pQueryActive(NULL),
            pQueryInactive(NULL),
            startDate(ID_STA_START_DATE_EF, this, this,
                    IRectangle(),
                    IEntryField::classDefaultStyle |
                    IControl::tabStop),
            endDate(ID_STA_END_DATE_EF, this, this,
                    IRectangle(),
                    IEntryField::classDefaultStyle |
                    IControl::tabStop),
            hourlyRate(ID_STA_HOURLY_RATE_EF, this, this,
                    IRectangle(),
                    IEntryField::classDefaultStyle |
                    IControl::tabStop),
            statusData(aKey),
            Key(aKey),
            pStartRange(NULL),
            pEndRange(NULL),
            pPayRange(NULL),
            thePageSettings( IApplication::current().userResourceLibrary().loadString(
                              STR_STA_STATUS_TAB), NULL,
                              INotebook::PageSettings::autoPageSize
                            | INotebook::PageSettings::majorTab ),
            isAquery(false)
{
   statusText.setText(    STR_STA_TITLE  );
   startDateText.setText( STR_STA_START  );
   endDateText.setText(   STR_STA_END    );
   rateText.setText(      STR_STA_HOURLY );

   startDate.setLimit( DISPLAY_LIMIT);
   endDate.setLimit(   DISPLAY_LIMIT);
   hourlyRate.setLimit(DISPLAY_LIMIT);

   activeText.setText(    STR_STA_ACTIVE );
   pActiveCheckBox = new ICheckBox( ID_CHECK_BOX
                                  , this
                                  , this);

   displayData();
   setCells();
   handleIt();
}

//-----------------------------------------------------------------------------
// CLASS StatusPage - constructor - a query page
//-----------------------------------------------------------------------------

StatusPage :: StatusPage(IWindow* pParent, LQueryData& qd)
          : IMultiCellCanvas(  ID_STATUS_PAGE, pParent, pParent),
            pageButtons( ID_STATUS_PAGE_BUTTONS
                         , this
                         , this
                         , true),
            statusText(ID_NO_ITEM, this, this ),
            activeText(ID_NO_ITEM, this, this ),
            startDateText(ID_NO_ITEM, this, this ),
            endDateText(ID_NO_ITEM, this, this ),
            rateText(ID_NO_ITEM, this, this ),
            pActiveCheckBox(NULL),
            pQueryActive(NULL),
            pQueryInactive(NULL),
            startDate(ID_STA_START_DATE_EF, this, this ),
            endDate(ID_STA_END_DATE_EF, this, this ),
            hourlyRate(ID_STA_HOURLY_RATE_EF, this, this ),
            statusData(qd),
            Key(qd.queryName()),
            pStartRange(NULL),
            pEndRange(NULL),
            pPayRange(NULL),
            thePageSettings( IApplication::current().userResourceLibrary().loadString(
                              STR_STA_STATUS_TAB), NULL,
                              INotebook::PageSettings::autoPageSize
                            | INotebook::PageSettings::majorTab ),
            isAquery(true )
{

   statusText.setText(    STR_STA_TITLE  );
   startDateText.setText( STR_STA_START  );
   endDateText.setText(   STR_STA_END    );
   rateText.setText(      STR_STA_HOURLY );

   startDate.setLimit( DISPLAY_LIMIT_DATE);
   endDate.setLimit(   DISPLAY_LIMIT_DATE);
   hourlyRate.setLimit(DISPLAY_SMALL);

   pQueryActive = new ICheckBox( ID_STATUS_QUERY_ACTIVE, this, this);
   pQueryInactive = new ICheckBox( ID_STATUS_QUERY_INACTIVE, this, this);

   pStartRange  = new QueryRange( ID_STATUS_PAGE_START
                                , this
                                , this
                                , ID_STATUS_START);

   pEndRange    = new QueryRange( ID_STATUS_PAGE_END
                                , this
                                , this
                                , ID_STATUS_END);

   pPayRange = new QueryRange( ID_STATUS_PAGE_PAY
                             , this
                             , this
                             , ID_STATUS_PAY);

   pQueryActive->setText(STR_STA_ACTIVE);
   pQueryInactive->setText(STR_STA_INACTIVE);

   displayData();
   setCells();
   handleIt();
}

//-----------------------------------------------------------------------------
// CLASS StatusPage :: ~StatusPage - destructor
//-----------------------------------------------------------------------------
StatusPage :: ~StatusPage()
{
   ICommandHandler::stopHandlingEventsFor( &pageButtons );
   ISelectHandler::stopHandlingEventsFor( &pageButtons );
   if (pActiveCheckBox)
      checkBoxHandler.stopHandlingEventsFor ( pActiveCheckBox);
}

//*****************************************************************************
// CLASS StatusPage :: handleIt()
//*****************************************************************************
StatusPage&  StatusPage :: handleIt()
{
   ICommandHandler::handleEventsFor( &pageButtons );
   ISelectHandler::handleEventsFor( &pageButtons );
   if (pActiveCheckBox)
     checkBoxHandler.handleEventsFor ( pActiveCheckBox );
   return *this;
}

//-----------------------------------------------------------------------------
// CLASS StatusPage :: setCells() - set up the multi-cell canvas
//-----------------------------------------------------------------------------
StatusPage& StatusPage :: setCells()
{
  addToCell(&statusText,         2,  2);

  if (pActiveCheckBox)
  {
    addToCell(&activeText,       2,  4);
    addToCell(pActiveCheckBox,   3,  4);
  }
  else
  {
    addToCell(pQueryActive,      2,  4,  5,  1);
    addToCell(pQueryInactive,    2,  5,  5,  1);
  }

  addToCell(&startDateText,      2,  8);
  addToCell(&startDate,          2,  9);
  if ( !pActiveCheckBox )
    addToCell(pStartRange,       3,  9,  5,  3);

  addToCell(&endDateText,        2, 11);
  addToCell(&endDate,            2, 12);
  if ( !pActiveCheckBox )
    addToCell(pEndRange,         3, 12,  5,  3);

  addToCell(&rateText,           2, 14);
  addToCell(&hourlyRate,         2, 15);
  if ( !pActiveCheckBox )
    addToCell(pPayRange,         3, 15,  5,  2);

  addToCell(&pageButtons,        2, 17,  7,  3);
  setColumnWidth( 8, 0, true );

  return *this;
}

//-----------------------------------------------------------------------------
// CLASS StatusPage :: verifyAndSave() - save to status database (ini)
//-----------------------------------------------------------------------------
IBase :: Boolean StatusPage :: verifyAndSave( IString& theString
                                             ,IString& theEntry
                                             ,const IString& theName )
{
     // verify data

     if ((theName.length() == 0) &&
         (Key.length()==0) || isAquery)
        return true;


    if ((theName.length() > 0 ) && (theName.isAlphanumeric()))
        statusData.save( theName
                        ,hourlyRate.text()
                        ,startDate.text()
                        ,endDate.text()
                        ,(Boolean) checkBoxHandler.getToggle());
    else
      if ((Key.length() > 0 ) && (Key.isAlphanumeric()))
          statusData.save( Key
                         ,hourlyRate.text()
                         ,startDate.text()
                         ,endDate.text()
                         ,(Boolean) checkBoxHandler.getToggle());

     return true;
}


//-----------------------------------------------------------------------------
// CLASS StatusPage :: displayData() - populate page
//-----------------------------------------------------------------------------
StatusPage& StatusPage :: displayData()
{
   startDate.setText(statusData.statusStart() );
   endDate.setText(statusData.statusEnd()    );
   hourlyRate.setText(statusData.statusRate() );

   if (pActiveCheckBox) {
      if ((statusData.statusActive() == "yes") ||
          (statusData.statusActive() == "new"))  {
         // the checkbox
         pActiveCheckBox->select();
         checkBoxHandler.setToggle(ACheckBoxHandler::true);
      }
      else {
           pActiveCheckBox->deselect();
           checkBoxHandler.setToggle(ACheckBoxHandler::false);
      }
   }
   else {
      // a query page
      if (statusData.statusActive() == "yes")
         pQueryActive->select();
      else
         pQueryActive->deselect();

      if (statusData.statusInactive() == "yes")
         pQueryInactive->select();
      else
         pQueryInactive->deselect();

      if (statusData.theRateRange().length() > 0)
         pPayRange->setRange(statusData.theRateRange());

      if (statusData.theStartRange().length() > 0)
         pStartRange->setRange(statusData.theStartRange());

      if (statusData.theEndRange().length() > 0)
         pEndRange->setRange(statusData.theEndRange());


   }

   // for queryies
   if (statusData.theRateRange().length() != 0)
       pPayRange->setRange(statusData.theRateRange());

   if (statusData.theStartRange().length() != 0)
      pStartRange->setRange(statusData.theStartRange());

   if (statusData.theEndRange().length() != 0)
      pEndRange->setRange(statusData.theEndRange());

   return *this;
}




//-----------------------------------------------------------------------------
// CLASS StatusPage :: command() - command handler
//-----------------------------------------------------------------------------
IBase :: Boolean StatusPage :: command(ICommandEvent &cmdEvent)
{
  switch (cmdEvent.commandId()) {       //Get command id

    case ID_BUTTON_UNDO:                       //Get the original data back
      displayData();
      return(true);                     //Return command processed
      break;                            //

    case ID_BUTTON_HELP:
       // Product Information processing
       IHelpWindow::helpWindow( this )->show(
           IResourceId( ID_STATUS_PAGE ) );
       return true;

  } /* end switch */

  return(false);                        //Return command not processed
}

//-----------------------------------------------------------------------------
// CLASS StatusPage :: pageSettings() - notebook sizing
//-----------------------------------------------------------------------------
INotebook :: PageSettings StatusPage :: pageSettings()
{
   return thePageSettings;
}

