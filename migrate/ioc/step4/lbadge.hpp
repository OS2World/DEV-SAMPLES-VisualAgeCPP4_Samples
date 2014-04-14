/*******************************************************************************
* FILE NAME: lbadge.hpp                                                        *
*                                                                              *
* DESCRIPTION:                                                                 *
*                                                                              *
* Classes                                                                      *
*   BadgeCnrObj                                                                *
*   BadgePage                                                                  *
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
Boolean
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
Boolean
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

Boolean
  isAquery;

};

#endif
