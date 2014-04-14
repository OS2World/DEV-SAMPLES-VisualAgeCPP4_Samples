/******************************************************************************
* .FILE:         ltimec.cpp                                                   *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Implementation   *
*                                                                             *
* .CLASSES:      TimeCardPage                                                 *
*                WeekEndingDate                                               *
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
#include <stdio.h>
#include <iexcbase.hpp>
#include <ireslib.hpp>
#include <ihelp.hpp>
#include <iscroll.hpp>
#include "lancelot.h"
#include "ltimec.hpp"


/*************************************************************/
/* CLASS TimeCardPage - constructor                          */
/*************************************************************/

TimeCardPage :: TimeCardPage( IWindow*        pParent,
                        ProjectPage*   pProjPage,
                        TasksPage*     pTasksPage,
                        const IString&  aKey)
              : IMultiCellCanvas( ID_TIMECARD_PAGE, pParent, pParent),
                pageButtons(ID_TIMECARD_PAGE_BUTTONS, this, this, false),
                pageScrollButtons( ID_TIMECARD_PAGE_SCROLL_BUTTONS,
                        this, this ),
                tcVp(ID_TIMECARD_VP, this, this,
                        IRectangle(),
                        (IViewPort::defaultStyle() &
                        ~IViewPort::asNeededVerticalScrollBar ) |
                        IViewPort::alwaysVerticalScrollBar),
                totalHoursText(ID_NO_ITEM, this , this ),
                totalBillableHoursText (ID_NO_ITEM, this, this ),
                pProjectPage(pProjPage),
                pTasksPage(pTasksPage),
                weekEndingDate(IDate()),
                pTimeCardData( new
                        LTimeCardData( aKey, weekEndingDate.date() ) ),
                timeCard(&tcVp,
                        pProjPage,
                        pTasksPage,
                        pTimeCardData),
                pieChart( ID_TIMECARD_PIECHART,
                        this, this, IRectangle(), pTimeCardData ),
                Key(aKey),
                thePageSettings( IApplication::current().userResourceLibrary().loadString(
                        STR_TCD_TIMECARD_TAB), NULL,
                        INotebook::PageSettings::autoPageSize
                        | INotebook::PageSettings::majorTab )
{
  pageScrollButtons.setDisplayText(pTimeCardData->theWeek.asString());

  totalHoursText.setAlignment(IStaticText::topCenter);
  totalBillableHoursText.setAlignment(  IStaticText::topCenter);

  setDisplayText(IString(timeCard.getTotalHours()),
                 IString(timeCard.getTotalBillable()));

  setCells();
  handleIt();
};

/*************************************************************/
/* CLASS TimeCardPage - ~TimeCardPage - destructor           */
/*************************************************************/

TimeCardPage :: ~TimeCardPage()
{
   ICommandHandler::stopHandlingEventsFor( &pageButtons );
   ICommandHandler::stopHandlingEventsFor( &pageScrollButtons );
   ISelectHandler::stopHandlingEventsFor( &pageButtons );
   delete( pTimeCardData );
};


/****************************************************************************
* CLASS TimeCardPage :: handleIt()                                          *
****************************************************************************/
TimeCardPage&  TimeCardPage :: handleIt()
{
   ICommandHandler::handleEventsFor( &pageButtons );
   ICommandHandler::handleEventsFor( &pageScrollButtons );
   ISelectHandler::handleEventsFor( &pageButtons );
   return *this;
}

/****************************************************************************
* CLASS TimeCardPage :: setCells() - set up the multi-cell canvas cells     *
****************************************************************************/
TimeCardPage& TimeCardPage :: setCells()
{
   addToCell(&pageScrollButtons,       2,  1);

   addToCell(&tcVp,                    1,  4,  3,  1);

   addToCell(&pieChart,                4,  4);
   setColumnWidth( 4, 0, true );
   setRowHeight( 4, 0, true );

   addToCell(&totalHoursText,          2,  6);
   addToCell(&totalBillableHoursText,  2,  7);

   addToCell(&pageButtons,             2,  8);

/*---------------------------------------------------------------------------
| Get the minimum size for the view-window portion of the viewport.         |
| Since the viewport will have a vertical scrollbar, we need to add it's    |
|  width to the view-window's width.                                        |
| Since the timecard's height is too much to fit on the notebook page,      |
|  reduce the height by 1/4.                                                |
| Set the minimum size of the viewport.                                     |
---------------------------------------------------------------------------*/
   ISize tcVpMinSize( windowWithHandle( tcVp.viewWindow() )->minimumSize() );
   tcVpMinSize += ISize( tcVp.verticalScrollBar()->size().width(), 0 );
   tcVpMinSize.setHeight( tcVpMinSize.height()/4 );
   tcVp.setMinimumSize( tcVpMinSize );

   return *this;
};

/**************************************************************************/
/* CLASS TimeCardPage :: setDisplayText()                                 */
/**************************************************************************/

TimeCardPage& TimeCardPage :: setDisplayText(const char* totHrs,
                                             const char* totBillHrs)
{
   totalHoursText.setText(         STR_TCD_TOTAL_HOURS_TEXT );
   totalBillableHoursText.setText( STR_TCD_TOTAL_BILLABLE_HOURS_TEXT);

   totalHoursText.setText( totalHoursText.text() + totHrs);
   totalBillableHoursText.setText( totalBillableHoursText.text() + totBillHrs);

   return *this;
};




TimeCard :: TimeCard(IWindow* pParent
                   , ProjectPage* pProjPage
                   , TasksPage  * pTasksPage
                   , LTimeCardData  * rLTimeCardData)
          : IMultiCellCanvas(ID_TIMECARD_PAGE,
                               pParent, pParent,
                               IRectangle() )
            ,dateHeader(ID_TIMECARD_DATE_HEADER, this, this)
            ,projectHeader(ID_TIMECARD_PROJECT_HEADER, this, this)
            ,taskHeader(ID_TIMECARD_TASK_HEADER, this, this)
            ,hourHeader(ID_TIMECARD_HOUR_HEADER, this, this)
            ,pProjectPage(pProjPage)
            ,pTasksPage(pTasksPage)
            ,totalHours(0)
            ,totalBillable(0)
{
  dateHeader.setText(IApplication::current().userResourceLibrary()
                     .loadString(STR_TCD_DATE_HEADER));
  projectHeader.setText(IApplication::current().userResourceLibrary()
                     .loadString(STR_TCD_PROJECT_HEADER));
  taskHeader.setText(IApplication::current().userResourceLibrary()
                     .loadString(STR_TCD_TASK_HEADER));
  hourHeader.setText(IApplication::current().userResourceLibrary()
                     .loadString(STR_TCD_HOUR_HEADER));

  for ( unsigned short index=0; index < ID_TIMECARD_ENTRIES; index++ )
  {
/*---------------------------------------------------------------------------
| Create an entryfield for entering the date.                               |
| Set the character limit.                                                  |
| Since the default minimumSize is too wide,                                |
| - get the minimumSize                                                     |
| - get the current font's average character width                          |
| - multiply the font width by the limit of the entryfield and add a buffer |
|   to avoid the entryfield from scrolling                                  |
| Set the new minimum size.                                                 |
| Auto delete the object when no longer available.                          |
| Create a de the object when no longer available.                          |
---------------------------------------------------------------------------*/
    date[index] = new IEntryField(ID_TCD_DATE0_EF, this, this,
                                  IRectangle(),
                                  IEntryField::classDefaultStyle |
                                  IControl::tabStop);
    date[index]->setLimit(  DISPLAY_LIMIT_DATE  );
    ISize dateMinSize( date[index]->minimumSize() );
    dateMinSize.setWidth( font().avgCharWidth() * ( DISPLAY_LIMIT_DATE + 2 ) );
    date[index]->setMinimumSize( dateMinSize );
    date[index]->setAutoDeleteObject();

/*---------------------------------------------------------------------------
| Create a downdownlist combobox for the project.                           |
| Set the character limit.                                                  |
| Auto delete the object when no longer available.                          |
---------------------------------------------------------------------------*/
    proj[index] = new IComboBox(ID_TCD_PROJ0_CBX, this, this,
                               IRectangle(),
                               IComboBox::defaultStyle() &
                               ~IComboBox::simpleType     |
                               IComboBox::readOnlyDropDownType |
                               IControl::tabStop);
    proj[index]->setLimit(  DISPLAY_LIMIT       );
    proj[index]->setAutoDeleteObject();

/*---------------------------------------------------------------------------
| Create a downdownlist combobox for the task.                              |
| Set the character limit.                                                  |
| Auto delete the object when no longer available.                          |
---------------------------------------------------------------------------*/
    task[index] = new IComboBox(ID_TCD_TASK0_CBX, this, this,
                               IRectangle(),
                               IComboBox::defaultStyle() &
                               ~IComboBox::simpleType     |
                               IComboBox::readOnlyDropDownType |
                               IControl::tabStop);
    task[index]->setLimit(  DISPLAY_LIMIT       );
    task[index]->setAutoDeleteObject();

/*---------------------------------------------------------------------------
| Create a spinbutton for entering the hours.                               |
| Set the character limit.                                                  |
| Since the default minimumSize is too wide,                                |
| - get the minimumSize                                                     |
| - get the current font's average character width                          |
| - multiply the font width by the limit of the entryfield and add a buffer |
|   to avoid the entryfield from scrolling and for the spinbutton's arrows  |
| Set the new minimum size                                                  |
| Auto delete the object when no longer available.                          |
---------------------------------------------------------------------------*/
    hours[index] = new INumericSpinButton(ID_TCD_HOURS0_EF, this, this,
                               IRectangle(),
                               INumericSpinButton::defaultStyle() |
                               IControl::tabStop);
    hours[index]->setLimit( DISPLAY_LIMIT_HOURS );
    ISize hoursMinSize( hours[index]->minimumSize() );
    hoursMinSize.setWidth( font().avgCharWidth() * ( DISPLAY_LIMIT_HOURS + 2 + 3 ) );
    hours[index]->setMinimumSize( hoursMinSize );
    hours[index]->setAutoDeleteObject();
  }

  fillComboBox();
  fillVp(rLTimeCardData);
  fillHours(rLTimeCardData->employeeNumber());
  handleIt();
  setCells();
};


/*************************************************************/
/* CLASS TimeCard - ~TimeCardPage - destructor           */
/*************************************************************/

TimeCard :: ~TimeCard()
{
};

/*************************************************************/
/* CLASS TimeCard - handleIt()                               */
/*************************************************************/

TimeCard& TimeCard :: handleIt()
{
  return *this;
};


TimeCard& TimeCard :: fillHours(const IString& key)
{
  LTaskData taskD(key);
  int billable = 0;
  int hrs=0;

  for ( unsigned short index=0; index < ID_TIMECARD_ENTRIES; index++ )
  {
    if (hours[index]->isValid())
      hrs += hours[index]->value();
    if (taskD.isInAndBillable(key, task[index]->text()))
      billable += hours[index]->value();
  }

  totalHours = hrs;
  totalBillable = billable;
  return *this;
};

/*************************************************************/
/* CLASS TimeCard - fillVp                                   */
/*************************************************************/

TimeCard& TimeCard :: fillVp(LTimeCardData * tcp)
{
  for ( unsigned short index=0; index < ID_TIMECARD_ENTRIES; index++ )
  {
    date[index]->setText(   tcp->tcard[index].date()          );
    proj[index]->setText(   tcp->tcard[index].projectName()   );
    task[index]->setText(   tcp->tcard[index].taskName()      );
    hours[index]->setValue( tcp->tcard[index].hours().asInt() );
  }

  return *this;
};


/**************************************************************************/
/* CLASS TimeCard :: setCells() - set up the multi-cell canvas cells   */
/**************************************************************************/

TimeCard& TimeCard :: setCells()
{
  unsigned short theRow;

  addToCell(&dateHeader,     1,  1);
  addToCell(&projectHeader,  3,  1);
  addToCell(&taskHeader,     5,  1);
  addToCell(&hourHeader,     7,  1);

  for ( unsigned short index=0; index < ID_TIMECARD_ENTRIES; index++ )
  {
     theRow = (index+1) * 2 + 1;
     addToCell(date[index],  1, theRow);
     addToCell(proj[index],  3, theRow);
     addToCell(task[index],  5, theRow);
     addToCell(hours[index], 7, theRow);
  }

   return *this;
};


/**************************************************************************/
/* CLASS TimeCard :: fillListBox() - set up the drop down list boxes  */
/**************************************************************************/

TimeCard& TimeCard :: fillComboBox()
{
  // make sure pointers are ok
  IString
    theProj,
    theDesc,
    theMgr,
    theAct,
    theTask,
    theBill;

  LProjectData::Rule theRule=LProjectData::na;
  LTaskData::Rule theRuleT=LTaskData::na;

  mtComboBoxes();

  pProjectPage->setProjectData();
  // get project data and fill up drop down
  if (pProjectPage->projData().setFirst())

     while (pProjectPage->projData().getItem(theProj,
                                              theDesc,
                                              theMgr,
                                              theAct,
                                              theRule)) {
       for ( unsigned short index=0; index < ID_TIMECARD_ENTRIES; index++ )
       {
         proj[index]->addAsLast(theProj);
       }
         pProjectPage->projData().getNext();
     }



  pTasksPage->setTasksData();
  // get task data and fill up drop down
  if (pTasksPage->getTaskData().setFirst()) {

     while (pTasksPage->getTaskData().getItem(theTask,
                                         theDesc,
                                         theBill,
                                         theRuleT))
     {
       for ( unsigned short index=0; index < ID_TIMECARD_ENTRIES; index++ )
       {
         task[index]->addAsLast(theTask);
       }

         pTasksPage->getTaskData().getNext();
     }
  }

   for ( unsigned short index=0; index < ID_TIMECARD_ENTRIES; index++ )
   {
     hours[index]->setRange(IRange(0, 24));
   }

  return *this;
};


TimeCard& TimeCard :: mtComboBoxes() {
  for ( unsigned short index=0; index < ID_TIMECARD_ENTRIES; index++ )
  {
    proj[index]->removeAll();
    task[index]->removeAll();
  }
  return *this;
};

// need to check date is in range

bool TimeCardPage :: verifyAndSave( IString& theString
                                               ,IString& theEntry
                                               ,const IString theName )
{
    int ix;
    long hrs;

  // verify the data

     if ((theName.length() == 0) && (Key.length() == 0 ))
        return true ;

     // take what is in the bag and write it to the database
     // data is ok, now save it.

     IString a,b,c,d ;
     int totalHours=0;

     // get the data from the ui fields and save in the data area

     bool incompleteMsg( false );
     unsigned short saveIndex( 0 );

     for ( unsigned short index=0; index < ID_TIMECARD_ENTRIES; index++ )
     {
       a = timeCard.date[index]->text();
       b = timeCard.proj[index]->text();
       c = timeCard.task[index]->text();
       hrs = timeCard.hours[index]->value();

       pTimeCardData->tcard[index].setDate( "" );
       pTimeCardData->tcard[index].setProjectName( "" );
       pTimeCardData->tcard[index].setTaskName( "" );
       pTimeCardData->tcard[index].setHours( 0 );

       if ((0 != a.length() ) &&
           (0 != b.length() ) &&
           (0 != c.length() ))
       {
          d = IString(hrs) ;
          totalHours += hrs ;

          pTimeCardData->tcard[saveIndex].setDate(        a);
          pTimeCardData->tcard[saveIndex].setProjectName( b);
          pTimeCardData->tcard[saveIndex].setTaskName(    c);
          pTimeCardData->tcard[saveIndex].setHours(       d);
          saveIndex++;
       }
       else if ( ( !incompleteMsg ) &&
                 ( 0 != a.length() ) ||
                 ( 0 != b.length() ) ||
                 ( 0 != c.length() ) )
       {
         IMessageBox msgBox( this );
         msgBox.show( STR_TIMECARD_NOSAVE
                      ,IMessageBox::warningIcon |
                      IMessageBox::okButton );
         incompleteMsg = true;
         continue;
       }
     } /* endfor */

     IString k;

    if (theName.length()>0)
       k = theName;
    else
       k = Key ;

     // concat the date
     k+= pTimeCardData->theWeek.asString();

     pTimeCardData->save(k);

     return (true);
};


bool TimeCardPage :: command(ICommandEvent &cmdEvent)
{
  bool rc = false;
  LTimeCardData *pTCD;
  IString badString, badControl;

  switch (cmdEvent.commandId()) {       //Get command id

    case ID_BUTTON_UNDO:             //Get the original data back
      delete(pTimeCardData);
      pTimeCardData =  new LTimeCardData( Key, weekEndingDate.date() );
      timeCard.fillVp(pTimeCardData);
      timeCard.fillHours(pTimeCardData->employeeNumber());
      pageScrollButtons.setDisplayText(pTimeCardData->theWeek.asString());
      rc = true;
      break;

   case   ID_BUTTON_NEXT:
      verifyAndSave( badString, badControl, Key);
      delete(pTimeCardData);
      pTimeCardData =  new LTimeCardData( Key,
                       weekEndingDate.nextDate(WeekEndingDate::next) );
      timeCard.fillVp(pTimeCardData);
      timeCard.fillHours(pTimeCardData->employeeNumber());
      pieChart.refreshData( pTimeCardData );
      pieChart.drawPie();
      pageScrollButtons.setDisplayText(pTimeCardData->theWeek.asString());
      setDisplayText(IString(timeCard.getTotalHours()),
                     IString(timeCard.getTotalBillable()));
      rc = true;
      break;

   case   ID_BUTTON_PREV:
      verifyAndSave( badString, badControl, Key);
      delete(pTimeCardData);
      pTimeCardData =  new LTimeCardData( Key,
                       weekEndingDate.nextDate(WeekEndingDate::previous) );

      timeCard.fillVp(pTimeCardData);
      timeCard.fillHours(pTimeCardData->employeeNumber());
      pieChart.refreshData( pTimeCardData );
      pieChart.drawPie();
      pageScrollButtons.setDisplayText(pTimeCardData->theWeek.asString());
      setDisplayText(IString(timeCard.getTotalHours()),
                     IString(timeCard.getTotalBillable()));
      rc = true;
      break;

    case ID_BUTTON_HELP:
      // Product Information processing
      IHelpWindow::helpWindow( this )->show(
           IResourceId( ID_TIMECARD_PAGE ) );
      rc = true;

  } /* end switch */

  return rc;
};


WeekEndingDate :: WeekEndingDate(IDate aDate)
{
   // given a date, set it to friday (it should be so easy!)
   while (aDate.dayOfWeek() != IDate::Friday) {
      aDate+=1;
   }

   theDate = aDate;
};

WeekEndingDate :: ~WeekEndingDate()
{};

const IDate WeekEndingDate :: nextDate(WeekScroll scroll)
{
    (scroll == WeekEndingDate::next) ? theDate += 7 : theDate -= 7;
    return theDate;
};

