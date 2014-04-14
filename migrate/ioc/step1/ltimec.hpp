/*******************************************************************************
* FILE NAME: ltimec.hpp                                                        *
*                                                                              *
* DESCRIPTION:                                                                 *
*                                                                              *
* Class                                                                        *
*   TimeCard                                                                   *
*   TimeCardPage                                                               *
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
Boolean
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

Boolean
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
