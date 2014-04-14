/*******************************************************************************
* FILE NAME: lstatus.hpp                                                       *
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
Boolean
  verifyAndSave( IString& theString,
                 IString& theEntry,
                 const IString& saveName="");

INotebook::PageSettings
  pageSettings();

protected: //----------------------- PROTECTED--------------------------------

Boolean
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
 *pQueryActive,
 *pQueryInactive;

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

Boolean
  isAquery;
};

#endif
