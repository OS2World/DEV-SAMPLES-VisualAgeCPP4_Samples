/******************************************************************************
* .FILE:         lbadge.hpp                                                   *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Definition       *
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
#ifndef _LBADGE_
#define _LBADGE_

#include <imcelcv.hpp>
#include <ientryfd.hpp>
#include <icmdhdr.hpp>
#include <imsgbox.hpp>
#include <istring.hpp>
#include <inotebk.hpp>
#include <iapp.hpp>

#include "ldbase.hpp"
#include "lgeneric.hpp"
#include "lpagectl.hpp"


//----------------------------------------------------------------------------
// class BadgePage
//----------------------------------------------------------------------------
class BadgePage : public IMultiCellCanvas,
                  public ICommandHandler,
                  public ISelectHandler
{

public: // ---------------------- PUBLIC -------------------------------------

friend class QueryBadge;

//----------------------- Contructor/Destructor ------------------------------
// Class BadgePage :: BadgePage()
//----------------------------------------------------------------------------
  BadgePage(IWindow* pParent,
            const IString& aKey= "") ;

  BadgePage(IWindow* pParent, LQueryData& qd);

  ~BadgePage();

//----------------------------------------------------------------------------
// Class BadgePage :: verifyAndSave()
//----------------------------------------------------------------------------
bool
  verifyAndSave( IString& theString,
                 IString& theEntry ,
                 const IString& saveName="");

//----------------------------------------------------------------------------
// Class BadgePage :: badgeNumber() - return the badge number
//----------------------------------------------------------------------------
inline IString
  badgeNumber() const { return BadgeNumber.text(); };

//----------------------------------------------------------------------------
// Class BadgePage :: badgeNumber() - return the badge number
//----------------------------------------------------------------------------
inline IString
  issueDate()   const { return IssueDate.text(); };

//----------------------------------------------------------------------------
// Class BadgePage :: expDate() - return the expiration date
//----------------------------------------------------------------------------
inline IString
  expDate()     const { return ExpDate.text(); };

//----------------------------------------------------------------------------
// Class BadgePage :: expDate() - return the expiration date
//----------------------------------------------------------------------------
INotebook::PageSettings
    pageSettings();

protected: //----------------------- PROTECTED --------------------------------

//----------------------------------------------------------------------------
// Class BadgePage :: command()
//----------------------------------------------------------------------------
bool
  command( ICommandEvent& event );

BadgePage&
  handleIt();

private: //------------- PRIVATE ------------------------------------------

//----------------------------------------------------------------------------
// Class BadgePage :: setCells()
//----------------------------------------------------------------------------
BadgePage&
    setCells();       // build multi-cell canvas


//----------------------------------------------------------------------------
// Class BadgePage :: displayData()
//----------------------------------------------------------------------------
BadgePage&
  displayData();

LBadgeData
  badgeData;

PageButtons
  pageButtons;

QueryRange
 *pIssueRange;

QueryRange
 *pExpRange;

IStaticText
  badgeNumberText,
  issueDateText,
  expDateText;

IEntryField
  BadgeNumber,
  IssueDate,
  ExpDate;

IString
  Key;

INotebook::PageSettings
  thePageSettings;

bool
  isAquery;

};

#endif
