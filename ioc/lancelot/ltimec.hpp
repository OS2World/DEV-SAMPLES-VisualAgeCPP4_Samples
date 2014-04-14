/******************************************************************************
* .FILE:         ltimec.hpp                                                   *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Definition       *
*                                                                             *
* .CLASSES:      TimeCard                                                     *
*                TimeCardPage                                                 *
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
#ifndef _LTIMEC_
#define _LTIMEC_

#include <imcelcv.hpp>
#include <icnrctl.hpp>
#include <icnrcol.hpp>
#include <istring.hpp>
#include <icombobx.hpp>
#include <ientryfd.hpp>
#include <ivport.hpp>
#include <isplitcv.hpp>
#include <ifont.hpp>
#include <ispinnum.hpp>
#include <inotebk.hpp>
#include <icmdhdr.hpp>
#include "ldbase.hpp"
#include "lpagectl.hpp"
#include "lproject.hpp"
#include "ltask.hpp"
#include "ltimepie.hpp"


//----------------------------------------------------------------------------
// class WeekEndingDate
//----------------------------------------------------------------------------
class WeekEndingDate : public IDate
{
public: // ------------------------- PUBLIC ----------------------------------
enum WeekScroll{ next,
                 previous
               };
  WeekEndingDate(IDate date = IDate());
  ~WeekEndingDate();

const IDate
  nextDate(WeekScroll scroll = next );

inline const IDate
  date() { return theDate;};

private: // ------------------------ PRIVATE --------------------------------

IDate
  theDate;

};

//----------------------------------------------------------------------------
// class TimeCard
//----------------------------------------------------------------------------
class TimeCard : public IMultiCellCanvas
{
public: // ----------------------- PUBLIC -----------------------------------
     // to get to private data in verifyAndSave()
friend class TimeCardPage;
  TimeCard(IWindow* pParent,
           ProjectPage* pProjPage,
           TasksPage* pTasksPage,
           LTimeCardData* pTimeCardData);

    ~TimeCard();

TimeCard&
    fillVp(LTimeCardData * tcp);

TimeCard&
    fillVpText();

TimeCard&
  fillHours(const IString &theKey);

TimeCard&
  setHours(const IString &key);

inline int
  getTotalHours() {return totalHours;};

inline int
  getTotalBillable() {return totalBillable;};

TimeCard&
  mtComboBoxes();

TimeCard&
  fillComboBox();

protected: // ---------------------- PROTECTED --------------------------------

TimeCard&
 handleIt();

private: // ------------------------ PRIVATE --------------------------------

TimeCard&
  setCells();       // build multi-cell canvas

IEntryField
 *date[ID_TIMECARD_ENTRIES];

IComboBox
 *proj[ID_TIMECARD_ENTRIES],
 *task[ID_TIMECARD_ENTRIES];

INumericSpinButton
 *hours[ID_TIMECARD_ENTRIES];

IStaticText
  dateHeader,
  projectHeader,
  taskHeader,
  hourHeader;

ProjectPage
 *pProjectPage;

TasksPage
 *pTasksPage;

int
  totalHours,
  totalBillable;

};


//----------------------------------------------------------------------------
// class TimeCardPage
//----------------------------------------------------------------------------
class TimeCardPage : public IMultiCellCanvas,
                     public ICommandHandler,
                     public ISelectHandler
{
public: // -------------------------- PUBLIC -------------------------------
friend class LTimeCardData;
  TimeCardPage(  IWindow* pParent,
                 ProjectPage* pProjPage,
                 TasksPage  * pTasksPage,
                 const IString& theKey= NULL);

     ~TimeCardPage();
bool
  verifyAndSave( IString& theString,
                 IString& theEntry,
                 const IString saveName=NULL);

inline INotebook::PageSettings
  pageSettings() { return thePageSettings; };

inline IString
 &key() {return Key;};

TimeCardPage&
  deleteObject(IString theKey);

inline TimeCardPage&
  fillCBagain() {timeCard.fillComboBox(); return *this;};


protected: // -------------------------- PROTECTED --------------------------

bool
  command( ICommandEvent& event );

TimeCardPage&
  handleIt();

private: //----------------------------- PRIVATE ----------------------------

TimeCardPage&
  setCells();

TimeCardPage&
  setDisplayText(const char* totHours, const char* totBillable);

PageButtons
  pageButtons;

PageScrollButtons
  pageScrollButtons;

IViewPort
  tcVp;

IStaticText
  totalHoursText,
  totalBillableHoursText;

ProjectPage
 *pProjectPage;

TasksPage
 *pTasksPage;

WeekEndingDate
  weekEndingDate;

LTimeCardData
 *pTimeCardData;

TimeCard
    timeCard;

LTimeCardPieChart
  pieChart;

IString
    Key;               // employee number

INotebook::PageSettings
    thePageSettings;

};

#endif
