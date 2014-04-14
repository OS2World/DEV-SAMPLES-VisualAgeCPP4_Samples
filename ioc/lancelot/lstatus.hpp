/******************************************************************************
* .FILE:         lstatus.hpp                                                  *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Definition       *
*                                                                             *
* .CLASSES:      StatusPage                                                   *
*                StatusCnrObj                                                 *
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
#ifndef _LSTATUS_
#define _LSTATUS_

#include <iselhdr.hpp>
#include <imcelcv.hpp>
#include <icmdhdr.hpp>
#include <icheckbx.hpp>
#include <ientryfd.hpp>
#include <imsgbox.hpp>
#include <inotebk.hpp>
#include <iapp.hpp>

#include "ldbase.hpp"
#include "lpagectl.hpp"
#include "lgeneric.hpp"


//**************************************************************************
// Class StatusPage
//**************************************************************************
class StatusPage : public IMultiCellCanvas,
                   public ICommandHandler,
                   public ISelectHandler
{
public: // ---------------------- PUBLIC -------------------------------------

friend class QueryStatus;

//----------------------- Contructor/Destructor ------------------------------
// Class StatusPage  :: StatusPage()
//----------------------------------------------------------------------------
  StatusPage(IWindow* pParent,
             const IString& aKey="");

  StatusPage(IWindow* pParent, LQueryData& qd);

  ~StatusPage();

//----------------------------------------------------------------------------
// Class StatusPage  :: verifyAndSave()
//----------------------------------------------------------------------------
bool
  verifyAndSave( IString& theString,
                 IString& theEntry,
                 const IString& saveName="");

INotebook::PageSettings
  pageSettings();

protected: //----------------------- PROTECTED--------------------------------

bool
  command( ICommandEvent& event );

StatusPage&
  handleIt();

private: //----------------------- PRIVATE --------------------------------

StatusPage&
  setCells();

StatusPage&
  displayData();

PageButtons
  pageButtons;

IStaticText
  statusText,
  activeText,
  startDateText,
  endDateText,
  rateText;

ICheckBox
 *pActiveCheckBox,
 *pQueryActive;

IEntryField
  startDate,
  endDate,
  hourlyRate;

IString
  Key;

LStatusData
  statusData;

QueryRange
 *pStartRange,
 *pEndRange,
 *pPayRange;

ACheckBoxHandler
  checkBoxHandler;

INotebook::PageSettings
  thePageSettings;

bool
  isAquery;
};

#endif
