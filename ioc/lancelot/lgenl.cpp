/******************************************************************************
* .FILE:         lgenl.cpp                                                    *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Implementation   *
*                                                                             *
* .CLASSES:      GeneralPage                                                  *
*                EmployeeType                                                 *
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
#include <ireslib.hpp>
#include <iexcbase.hpp>
#include <ihelp.hpp>
#include "lancelot.h"
#include "lgenl.hpp"

//*****************************************************************************
// CLASS GeneralPage - Contructor
//*****************************************************************************
GeneralPage :: GeneralPage(IWindow* pParent,
                           const IString empNum)
             : IMultiCellCanvas(ID_GENERAL_PAGE, pParent, pParent),
               employeeData(empNum ),
               pageButtons(ID_GENERAL_PAGE_BUTTONS,
                          this,this, false),
               employeeIdText  (ID_NO_ITEM, this, this ),
               lastNameText    (ID_NO_ITEM, this, this ),
               firstNameText   (ID_NO_ITEM, this, this ),
               middleNameText  (ID_NO_ITEM, this, this ),
               intPhoneText    (ID_NO_ITEM, this, this ),
               extPhoneText    (ID_NO_ITEM, this, this ),
               roomText        (ID_NO_ITEM, this, this ),
               deptText        (ID_NO_ITEM, this, this ),
               bldgText        (ID_NO_ITEM, this, this ),
               divText         (ID_NO_ITEM, this, this ),
               mgrEmpNumText   (ID_NO_ITEM, this, this ),
               mgrEmpNameText  (ID_NO_ITEM, this, this ),
               employeeId     (ID_GEN_EMPLOYEE_ID_EF   , this, this,
                              IRectangle(),
                              IEntryField::classDefaultStyle |
                              IControl::tabStop),
               lastName       (ID_GEN_LAST_NAME_EF     , this, this,
                               IRectangle(),
                               IEntryField::classDefaultStyle |
                               IControl::tabStop),
               firstName      (ID_GEN_FIRST_NAME_EF    , this, this,
                               IRectangle(),
                               IEntryField::classDefaultStyle |
                               IControl::tabStop),
               middleInitial  (ID_GEN_MIDDLE_INITIAL_EF, this, this,
                               IRectangle(),
                               IEntryField::classDefaultStyle |
                               IControl::tabStop),
               intPhone       (ID_GEN_INT_PHONE_EF, this, this,
                               IRectangle(),
                               IEntryField::classDefaultStyle |
                               IControl::tabStop),
               extPhone       (ID_GEN_EXT_PHONE_EF, this, this,
                               IRectangle(),
                               IEntryField::classDefaultStyle |
                               IControl::tabStop),
               room           (ID_GEN_ROOM_EF     , this, this,
                               IRectangle(),
                               IEntryField::classDefaultStyle |
                               IControl::tabStop),
               building       (ID_GEN_BUILDING_EF , this, this,
                               IRectangle(),
                               IEntryField::classDefaultStyle |
                               IControl::tabStop),
               deptName       (ID_GEN_DEPT_EF     , this, this,
                               IRectangle(),
                               IEntryField::classDefaultStyle |
                               IControl::tabStop),
               division       (ID_GEN_DIVISION_EF , this, this,
                               IRectangle(),
                               IEntryField::classDefaultStyle |
                               IControl::tabStop),
               employeeType   (this),
               mgrEmpId       (ID_GEN_MGR_EMP_ID_EF, this, this,
                               IRectangle(),
                               IEntryField::classDefaultStyle |
                               IControl::tabStop),
               mgrName        (ID_GEN_MGR_NAME_EF  , this, this,
                               IRectangle(),
                               IEntryField::classDefaultStyle |
                               IControl::tabStop),
               Key(empNum),
               thePageSettings( IApplication::current().userResourceLibrary().loadString(
                                STR_GEN_GENERAL_TAB), NULL,
                                INotebook::PageSettings::autoPageSize
                                | INotebook::PageSettings::majorTab ),
              isAquery(false)
{
   // set up the fields
   setUp();
   if ( employeeId.text().length() )
      employeeId.disableDataUpdate();

   // set up the page
   setCells();

   // populate the page from any database info
   displayData();
   handleIt();
}


//*****************************************************************************
// CLASS GeneralPage - Contructor  query
//*****************************************************************************
GeneralPage :: GeneralPage(IWindow* pParent
                          , LQueryData& qd)
             :IMultiCellCanvas(ID_GENERAL_PAGE, pParent, pParent),
              employeeData(qd),
              pageButtons(ID_GENERAL_PAGE_BUTTONS,
                          this,this, true),
              employeeIdText  (ID_NO_ITEM, this, this ),
              lastNameText    (ID_NO_ITEM, this, this ),
              firstNameText   (ID_NO_ITEM, this, this ),
              middleNameText  (ID_NO_ITEM, this, this ),
              intPhoneText    (ID_NO_ITEM, this, this ),
              extPhoneText    (ID_NO_ITEM, this, this ),
              roomText        (ID_NO_ITEM, this, this ),
              deptText        (ID_NO_ITEM, this, this ),
              bldgText        (ID_NO_ITEM, this, this ),
              divText         (ID_NO_ITEM, this, this ),
              mgrEmpNumText   (ID_NO_ITEM, this, this ),
              mgrEmpNameText  (ID_NO_ITEM, this, this ),
              employeeId     (ID_GEN_EMPLOYEE_ID_EF   , this, this,
                              IRectangle(),
                              IEntryField::classDefaultStyle |
                              IControl::tabStop),
              lastName       (ID_GEN_LAST_NAME_EF     , this, this,
                              IRectangle(),
                              IEntryField::classDefaultStyle |
                              IControl::tabStop),
              firstName      (ID_GEN_FIRST_NAME_EF    , this, this,
                              IRectangle(),
                              IEntryField::classDefaultStyle |
                              IControl::tabStop),
              middleInitial  (ID_GEN_MIDDLE_INITIAL_EF, this, this,
                              IRectangle(),
                              IEntryField::classDefaultStyle |
                              IControl::tabStop),
              intPhone       (ID_GEN_INT_PHONE_EF, this, this,
                              IRectangle(),
                              IEntryField::classDefaultStyle |
                              IControl::tabStop),
              extPhone       (ID_GEN_EXT_PHONE_EF, this, this,
                              IRectangle(),
                              IEntryField::classDefaultStyle |
                              IControl::tabStop),
              room           (ID_GEN_ROOM_EF     , this, this,
                              IRectangle(),
                              IEntryField::classDefaultStyle |
                              IControl::tabStop),
              building       (ID_GEN_BUILDING_EF , this, this,
                              IRectangle(),
                              IEntryField::classDefaultStyle |
                              IControl::tabStop),
              deptName       (ID_GEN_DEPT_EF     , this, this,
                              IRectangle(),
                              IEntryField::classDefaultStyle |
                              IControl::tabStop),
              division       (ID_GEN_DIVISION_EF , this, this,
                              IRectangle(),
                              IEntryField::classDefaultStyle |
                              IControl::tabStop),
              employeeType(this),
              mgrEmpId (ID_GEN_MGR_EMP_ID_EF, this, this,
                              IRectangle(),
                              IEntryField::classDefaultStyle |
                              IControl::tabStop),
              mgrName  (ID_GEN_MGR_NAME_EF  , this, this,
                              IRectangle(),
                              IEntryField::classDefaultStyle |
                              IControl::tabStop),
              Key(qd.queryName()),
              thePageSettings( IApplication::current().userResourceLibrary().loadString(
                               STR_GEN_GENERAL_TAB), NULL,
                               INotebook::PageSettings::autoPageSize
                               | INotebook::PageSettings::majorTab ),
              isAquery(true)
{

   // set up the entry field limits
   setUp();

   // set up the page
   setCells();

   // this is a query do not query an employeeType unless selected
   employeeType.deselectReg();
   employeeType.deselectMgr();
   employeeType.deselectSup();

   // populate the page from any database info
   displayData();

   handleIt();

}


//*****************************************************************************
// CLASS GeneralPage :: handleIt()
//*****************************************************************************
GeneralPage&  GeneralPage :: handleIt()
{
   ICommandHandler::handleEventsFor( &pageButtons );
   ISelectHandler::handleEventsFor( &pageButtons );
   return *this;
}
//*****************************************************************************
// CLASS GeneralPage :: setUp()
//*****************************************************************************
GeneralPage&  GeneralPage :: setUp()
{
   employeeIdText.setText(  STR_GEN_EMPLOYEE_ID_TEXT);
   lastNameText.setText(    STR_GEN_LAST_NAME_TEXT);
   firstNameText.setText(   STR_GEN_FIRST_NAME_TEXT);
   middleNameText.setText(  STR_GEN_MIDDLE_NAME_TEXT);
   intPhoneText.setText(    STR_GEN_INT_PHONE_TEXT);
   extPhoneText.setText(    STR_GEN_EXT_PHONE_TEXT);
   roomText.setText(        STR_GEN_ROOM_TEXT);
   deptText.setText(        STR_GEN_DEPT_TEXT);
   bldgText.setText(        STR_GEN_BLD_TEXT);
   divText.setText(         STR_GEN_DIV_TEXT);
   mgrEmpNumText.setText(   STR_GEN_MGR_EMP_NUM_TEXT);
   mgrEmpNameText.setText(  STR_GEN_MGR_EMP_NAME_TEXT);

   employeeId.setLimit   (DISPLAY_LARGE);
   lastName.setLimit     (DISPLAY_LARGE);
   firstName.setLimit    (DISPLAY_LARGE);
   middleInitial.setLimit(DISPLAY_VERY_SMALL);
   intPhone.setLimit     (DISPLAY_LARGE);
   extPhone.setLimit     (DISPLAY_LARGE);
   room.setLimit         (DISPLAY_LARGE);
   building.setLimit     (DISPLAY_LARGE);
   deptName.setLimit     (DISPLAY_LARGE);
   division.setLimit     (DISPLAY_LARGE);
   mgrEmpId.setLimit     (DISPLAY_LARGE);
   mgrName.setLimit      (DISPLAY_LARGE);

/*---------------------------------------------------------------------------
| On a VGA monitor, the general page almost completely fills the screen.    |
| Therefore, reduce the default minimum size of the entryfields.            |
---------------------------------------------------------------------------*/
   ISize efMinSize( employeeId.minimumSize() );
   efMinSize.setWidth( efMinSize.width() - 40 );
   employeeId.setMinimumSize   (efMinSize);
   lastName.setMinimumSize     (efMinSize);
   firstName.setMinimumSize    (efMinSize);
   intPhone.setMinimumSize     (efMinSize);
   extPhone.setMinimumSize     (efMinSize);
   room.setMinimumSize         (efMinSize);
   building.setMinimumSize     (efMinSize);
   deptName.setMinimumSize     (efMinSize);
   division.setMinimumSize     (efMinSize);
   mgrEmpId.setMinimumSize     (efMinSize);
   mgrName.setMinimumSize      (efMinSize);

   return *this;
}


//*****************************************************************************
// CLASS GeneralPage :: ~GeneralPage()
//*****************************************************************************
GeneralPage :: ~GeneralPage()
{
   ICommandHandler::stopHandlingEventsFor( &pageButtons );
   ISelectHandler::stopHandlingEventsFor( &pageButtons );
}

//*****************************************************************************
// CLASS GeneralPage :: setCells() - set up the multi-cell canvas cells
//*****************************************************************************
GeneralPage&  GeneralPage :: setCells()
{
/*---------------------------------------------------------------------------
| Add objects to the multicell.                                             |
| Allow the entryfields to dynamically widen if the user enlarges the       |
| notebook.                                                                 |
---------------------------------------------------------------------------*/
   //                         col,row,col,row
   addToCell(&employeeIdText ,  2,  2);
   addToCell(&employeeId     ,  3,  2);
   setColumnWidth( 3, 2, true );

   addToCell(&lastNameText   ,  2,  4);
   addToCell(&lastName       ,  3,  4);
   setColumnWidth( 3, 2, true );

   addToCell(&firstNameText  ,  5,  4);
   addToCell(&firstName      ,  6,  4);
   setColumnWidth( 6, 2, true );

   addToCell(&middleNameText ,  8,  4,  2, 1);
   addToCell(&middleInitial  , 10,  4,  2, 1);

   addToCell(&intPhoneText    , 2,  6);
   addToCell(&intPhone        , 3,  6);
   setColumnWidth( 3, 2, true );

   addToCell(&extPhoneText    , 5,  6);
   addToCell(&extPhone        , 6,  6);
   setColumnWidth( 6, 2, true );

   addToCell(&roomText        , 2,  8);
   addToCell(&room            , 3,  8);
   setColumnWidth( 3, 2, true );

   addToCell(&bldgText        , 5,  8);
   addToCell(&building        , 6,  8);
   setColumnWidth( 6, 2, true );

   addToCell(&deptText        , 2, 10);
   addToCell(&deptName        , 3, 10);
   setColumnWidth( 3, 2, true );

   addToCell(&divText         , 5, 10);
   addToCell(&division        , 6, 10);
   setColumnWidth( 6, 2, true );

   addToCell(&employeeType    , 2, 12, 5, 5);

   addToCell(&mgrEmpNumText   , 2, 19);
   addToCell(&mgrEmpId        , 3, 19);
   setColumnWidth( 3, 2, true );

   addToCell(&mgrEmpNameText  , 5, 19);
   addToCell(&mgrName         , 6, 19);
   setColumnWidth( 6, 2, true );

   addToCell(&pageButtons     , 2, 21, 5, 4);

   return *this;
}


//*****************************************************************************
// CLASS GeneralPage :: displayData() - set up
//*****************************************************************************
GeneralPage&  GeneralPage :: displayData()
{

    employeeId.setText(   employeeData.employeeNumber());
    lastName.setText(     employeeData.lastName());
    firstName.setText(    employeeData.firstName());
    middleInitial.setText(employeeData.middleInitial());
    intPhone.setText(     employeeData.internalPhone() );
    extPhone.setText(     employeeData.externalPhone());
    room.setText(         employeeData.room());
    building.setText(     employeeData.building());
    deptName.setText(     employeeData.department());
    division.setText(     employeeData.division());

    switch ((LEmployeeData::EmplType)employeeData.employeeType()) {

      case (LEmployeeData::Regular):    //Get the original data back
           employeeType.selectReg();
           break;
      case (LEmployeeData::Manager):
           employeeType.selectMgr();
           break;
      case (LEmployeeData::Supplemental):
           employeeType.selectSup();
           break;
    }

    mgrEmpId.setText(employeeData.managerNumber());
    mgrName.setText(employeeData.managerName());

    return *this;

}


//*****************************************************************************
// CLASS GeneralPage :: verifyAndSave() - save database info
//*****************************************************************************
bool GeneralPage :: verifyAndSave( IString& theString,
                                               IString& theEntry,
                                               const IString theName )
{

    /*  verify data for correctness */

    if ((theName.length() == 0) && (employeeId.text().length() == 0 ))
        return true;

    // save person information
    if ((theName.length() == 0 ) && (employeeId.text().isAlphanumeric()))
        Key = employeeId.text();
    else
       Key = theName;

    // prime the page from data area
    setEmployeeData();

    //-------------------------------------------------------------------------
    // Save the query
    // The key is either what was passed in or the employee number
    //-------------------------------------------------------------------------
    if (theName.length()>0)
       employeeData.save(theName);
    else
       if ( (!isAquery) &&
            (Key.length()> 0 ))
             employeeData.save(Key);

     return true;
}



//*****************************************************************************
// CLASS GeneralPage :: setEmployeeData() - set page info to data area
//*****************************************************************************
GeneralPage&  GeneralPage :: setEmployeeData()
{

     LEmployeeData::EmplType emplType;

     employeeData.setEmployeeNumber(employeeId.text());
     employeeData.setLastName(      lastName.text());
     employeeData.setFirstName(     firstName.text());
     employeeData.setMiddleInitial( middleInitial.text());
     employeeData.setInternalPhone( intPhone.text());
     employeeData.setExternalPhone( extPhone.text());
     employeeData.setRoom(          room.text());
     employeeData.setBuilding(      building.text());
     employeeData.setDepartment(    deptName.text());
     employeeData.setDivision(      division.text());

     if (employeeType.isRegSelected())
        emplType = (LEmployeeData:: Regular);
     else
     if (employeeType.isMgrSelected())
        emplType = (LEmployeeData:: Manager);
     else
     if (employeeType.isSupSelected())
        emplType = (LEmployeeData:: Supplemental);
     else
        emplType = (LEmployeeData:: Unemployed);

     employeeData.setEmployeeType(emplType);

     employeeData.setManagerNumber(mgrEmpId.text());
     employeeData.setManagerName(  mgrName.text());

     return *this;
}


//*****************************************************************************
// CLASS GeneralPage :: command() - command handler
//*****************************************************************************
bool GeneralPage :: command(ICommandEvent &cmdEvent)
{

  switch (cmdEvent.commandId()) {       //Get command id

    case ID_BUTTON_UNDO:                       //Get the original data back
      this->displayData();
      return(true);                     //Return command processed
      break;                            //

    case ID_BUTTON_HELP:
       // Product Information processing
       IHelpWindow::helpWindow( this )->show(
           IResourceId( ID_GENERAL_PAGE ) );
       return true;

  } /* end switch */

  return(false);                        //Return command not processed

}

//*****************************************************************************
// CLASS  EmployeeType - EmployeeType - constructor
//*****************************************************************************
EmployeeType :: EmployeeType(IWindow* pParent )
              : ISetCanvas(ID_EMPLOYEE_TYPE_GROUP_BOX, pParent, pParent,
                           IRectangle(),
                           defaultStyle() | ISetCanvas::border ),
                reg(ID_GEN_REG_BT,  this, this),
                mgr(ID_GEN_MGR_BT,  this, this),
                sup(ID_GEN_SUP_BT,  this, this)
{
   reg.setText(STR_GEN_REG_TEXT);
   mgr.setText(STR_GEN_MGR_TEXT);
   sup.setText(STR_GEN_SUP_TEXT);
   setBorderText(IResourceId(STR_GEN_EMPLOYEE_TYPE_TEXT));

   setDeckOrientation(ISetCanvas::horizontal);

   // a regular employee is the default
   reg.select();
}

//***************************************************************************** */
// Class EmployeeType :: ~EmployeeType() _ Destructor
//*****************************************************************************
EmployeeType :: ~EmployeeType()
{}

//*****************************************************************************
// CLASS GeneralPage - pageSettings()
//*****************************************************************************
INotebook :: PageSettings GeneralPage :: pageSettings()
{
   return thePageSettings;
}

