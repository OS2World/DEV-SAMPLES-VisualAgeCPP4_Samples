/******************************************************************************
* .FILE:         lgenl.hpp                                                    *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Definition       *
*                                                                             *
* .CLASSES:      EmployeeType                                                 *
*                GeneralPage                                                  *
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
#ifndef _LGENL_
#define _LGENL_

#include <imcelcv.hpp>
#include <istattxt.hpp>
#include <ientryfd.hpp>
#include <iradiobt.hpp>
#include <inotebk.hpp>
#include <icmdhdr.hpp>
#include <istring.hpp>

#include "lpagectl.hpp"
#include "ldbase.hpp"

//----------------------------------------------------------------------------
// class EmployeeType
//----------------------------------------------------------------------------
class EmployeeType :  public ISetCanvas  // IGroupBox
{

public:
// ---------------------- PUBLIC -------------------------------------

//----------------------- Contructor/Destructor ------------------------------
// Class EmployeeType:: EmployeeType()
//----------------------------------------------------------------------------
  EmployeeType(IWindow* pParent) ;
  ~EmployeeType();

inline EmployeeType& selectReg() {reg.select(); return *this; };
inline EmployeeType& selectMgr() {mgr.select(); return *this; };
inline EmployeeType& selectSup() {sup.select(); return *this;};

inline EmployeeType& deselectReg() {reg.deselect(); return *this;};
inline EmployeeType& deselectMgr() {mgr.deselect(); return *this;};
inline EmployeeType& deselectSup() {sup.deselect(); return *this;};

inline bool
    isRegSelected() { return reg.isSelected();};
inline bool
    isMgrSelected() { return mgr.isSelected();};
inline bool
    isSupSelected() { return sup.isSelected();};

private:
//--------------------------- PRIVATE ----------------------------------------

IRadioButton
  reg,
  mgr,
  sup;

};


//----------------------------------------------------------------------------
// Class GeneralPage
//----------------------------------------------------------------------------
class GeneralPage : public IMultiCellCanvas,
                    public ICommandHandler,
                    public ISelectHandler
{

public:
//---------------------------------- PUBLIC ----------------------------------

friend class QueryGenl;
//----------------------- Contructor/Destructor ------------------------------
// Contructor for GeneralPage()
//----------------------------------------------------------------------------

  GeneralPage(IWindow* pParent,
              const IString empNum="");

  GeneralPage(IWindow* pParent,
               LQueryData& qd);

  ~GeneralPage();

//----------------------------------------------------------------------------
// verfiyAndSave - save database data
//----------------------------------------------------------------------------
bool
  verifyAndSave( IString& theString,
                 IString& theEntry,
                 const IString saveName="");

//----------------------------------------------------------------------------
// setEmployeeData - populate page
//----------------------------------------------------------------------------
GeneralPage&
  setEmployeeData();

//----------------------------------------------------------------------------
// getKey - database key
//----------------------------------------------------------------------------
inline IString
  key() {return Key;};

//----------------------------------------------------------------------------
// pageSettings() - used to size the notebook
//----------------------------------------------------------------------------
INotebook::PageSettings
  pageSettings();


protected:
//----------------------- PROTECTED ------------------------------------------

bool
  command( ICommandEvent& event );

GeneralPage
 &handleIt();

private:
//------------------------ PRIVATE --------------------------------------------

GeneralPage&
  setUp();

GeneralPage&
  setCells();              // build multi-cell canvas

GeneralPage&
  displayData();

LEmployeeData
  employeeData;

PageButtons
  pageButtons;

IStaticText
  employeeIdText,
  lastNameText,
  middleNameText,
  firstNameText,
  intPhoneText,
  extPhoneText,
  roomText,
  deptText,
  bldgText,
  divText,
  mgrEmpNumText,
  mgrEmpNameText;

IEntryField
  employeeId,
  lastName,
  firstName,
  middleInitial,
  intPhone,
  extPhone,
  room,
  building,
  deptName,
  division;

EmployeeType
  employeeType;

IEntryField
  mgrEmpId,
  mgrName;

IString
  Key;               // employee number
INotebook::PageSettings
  thePageSettings;

bool
  isAquery;
};

#endif
