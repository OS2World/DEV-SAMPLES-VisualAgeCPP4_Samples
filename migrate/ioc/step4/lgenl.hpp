/*******************************************************************************
* FILE NAME: lgenl.hpp                                                         *
*                                                                              *
* DESCRIPTION:                                                                 *
*                                                                              *
* Class                                                                        *
*   LPictureVerifyHandler                                                      *
*   EmployeeType                                                               *
*   GeneralPage                                                                *
*                                                                              *
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

inline Boolean
    isRegSelected() { return reg.isSelected();};
inline Boolean
    isMgrSelected() { return mgr.isSelected();};
inline Boolean
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
Boolean
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

Boolean
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


Boolean
  isAquery;
};

#endif
