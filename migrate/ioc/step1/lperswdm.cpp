/****************************************************************************
* LANCELOT SAMPLE PROGRAM - lperswdm.cpp                                    *
*                                                                           *
* Classes : EmployeeItem                                                    *
*                                                                           *
* DISCLAIMER OF WARRANTIES:                                                 *
*   The following [enclosed] code is sample code created by IBM             *
*   Corporation.  This sample code is not part of any standard IBM product  *
*   and is provided to you solely for the purpose of assisting you in the   *
*   development of your applications.  The code is provided "AS IS",        *
*   without warranty of any kind.  IBM shall not be liable for any damages  *
*   arising out of your use of the sample code, even if they have been      *
*   advised of the possibility of such damages.                             *
****************************************************************************/

#ifndef _IBASE_                         //Make sure ibase.hpp is included
  #include <ibase.hpp>                  //  since that is where IC_<environ>
#endif                                  //  is defined.
#include <icnrctl.hpp>
#include <icnrobj.hpp>
#include <imsgbox.hpp>

#include "lperswdm.hpp"
#include "lperswin.hpp"
#include "lstatus.hpp"

/****************************************************************************
* CLASS EmployeeItem - Constructor                                          *
****************************************************************************/
EmployeeItem ::  EmployeeItem( const IDMItem::Handle &item )
    : IDMCnrItem( item )
{
    IString
      rmf1 = IDMItem::rmfFrom( IDM::rmDiscard, IDM::rfUnknown );
    // Get pointer to the associated Employee container object...
    LPersonnelCnrObject
     *employee  = (LPersonnelCnrObject*)this->object();

    // Build and set contents.  We can only do this on the source
    // side.  Note that since we call this ctor on both source
    // and target sides, we must distinguish them.  That is done
    // here by checking the "object" pointer.  If this ctor was
    // called from within our generateSourceItems, then this value
    // will be non-zero.  If called from with the template provider's
    // provideTargetItemFor, then it will be zero.
    if ( employee ) {

       IString
         contents;
       contents = employee -> employeeRecord().department();
       this -> setContents( contents );

       // Add RMFs supported by this class (IDMCnrItem will have
       // already specified others)...
       this -> addRMF( rmf1 );
    }
    else
      // On target side, add in <rmLibrary,rfSharedMem> if source concurs
      // (and it's not already in there)...
      if ( item -> supportsRMF( rmf1 )
           &&
           !( this -> supportsRMF( rmf1 ) ) )
         this -> addRMF( rmf1 );

} // EmployeeItem constructor

/****************************************************************************
* CLASS EmployeeItem - Destructor                                           *
****************************************************************************/
EmployeeItem ::   ~EmployeeItem( )
    {
    }

/****************************************************************************
* CLASS EmployeeItem - generateSourceItem                                   *
****************************************************************************/
IBase::Boolean EmployeeItem ::
  generateSourceItems ( const IDMSourceOperation::Handle &srcOp )
    {
    // Get generic container items.  Note that we call the inherited
    // function since it already has smarts to deal with multi-selection,
    // etc...

//     When compiling with VisualAge C++ 4.0, the following line needs
//     to be changed to
//  Boolean
//    result = Inherited::generateSourceItems( srcOp.getAlias() );

    Boolean
      result = Inherited::generateSourceItems( srcOp );

    // Now, replace each IDMCnrItem with a employee item...
    for ( unsigned i = 1; i <= srcOp->numberOfItems(); i++ )
      srcOp -> replaceItem( i, new EmployeeItem( srcOp -> item( i ) ) );

    // Set stack3AndFade as the default image style ...
    srcOp -> setImageStyle( IDM::stack3AndFade );
    return result;
    }

/****************************************************************************
* CLASS EmployeeItem - sourceDiscard                                        *
****************************************************************************/
Boolean EmployeeItem ::
  sourceDiscard ( IDMSourceDiscardEvent &event )
    {

    IContainerControl
     *cnr = (IContainerControl*)( event.sourceOperation()->sourceWindow() );

    LPersonnelCnrObject
      *employee  = (LPersonnelCnrObject*)this->object();

    LPersonnelWindow *theWindow = (LPersonnelWindow *)cnr->parent();

    deleteActionDM( employee, theWindow );

    // Remove the object from the container...
    IContainerObject
     *obj = (IContainerObject*)( this->object() );
    cnr -> removeObject( obj );
    // discard from DB

    return true;
    }


/****************************************************************************
* CLASS EmployeeItem - targetDrop                                           *
****************************************************************************/
Boolean EmployeeItem ::
  targetDrop ( IDMTargetDropEvent &event )
    {
    Boolean
      result = true;
    // Check if using rfSharedMem...
    IString
      myRMF = IDMItem::rmfFrom( IDM::rmLibrary, IDM::rfSharedMem );

    LPersonnelCnrObject
      *employee  = (LPersonnelCnrObject*)this->object();

    if ( this->selectedRMF() == myRMF ) {

      // Yes, get dept name from passed data...

      IString
        dept     = this->contents();

      // See if the departments are different, if yes then transfer the employee
      // if it the same or the query is a dept then don't do the drop
      //

      IContainerControl
       *cnr = event.container();

      LPersonnelWindow *theWindow = (LPersonnelWindow *)cnr->parent();
      if (theWindow->deptQuery() != dept ) {
         // transfer

         LPersonnelCnrObject
          *employee  = (LPersonnelCnrObject*)this->object();

         transferActionDM( employee, dept, theWindow );
       }
    }
    else {

      // Some other RMF, base class must support it...
      // See if the departments are different, if yes then transfer the employee
      // if it the same or the query is a dept then don't do the drop
      //

      IString
        dept     = this->contents();

      IContainerControl
       *cnr = event.container();

      LPersonnelWindow *theWindow = (LPersonnelWindow *)cnr->parent();
      if ((theWindow->deptQuery() != dept ) &&
          (theWindow->deptQuery().length()>0)) {

         transferActionDM( employee, theWindow->deptQuery(), theWindow );
         result = Inherited::targetDrop( event );
       }
       else
         if (this->sourceContainer() != cnr) {
            // don't drop it, message box.
            IString aMsg;
            if (theWindow->deptQuery() == dept ) {

               aMsg = employee -> employeeRecord().firstName() + " " +
                      employee -> employeeRecord().lastName() + " " +
                         IApplication::current().userResourceLibrary().
                             loadString( STR_TRANSFER_MSG6 ) + " " + dept;
            }
            else {
               aMsg = employee -> employeeRecord().firstName() + " " +
                      employee -> employeeRecord().lastName() + " " +
                         IApplication::current().userResourceLibrary().
                          loadString( STR_TRANSFER_MSG5 );
            }

            // no message if source and target is the same
            IMessageBox msg( theWindow );
            msg.show( aMsg,
                      IMessageBox::informationIcon );
         } // not the same container

    }

    return result;
}


/****************************************************************************
* CLASS EmployeeItem - supportedOperationsFor                               *
****************************************************************************/
unsigned long  EmployeeItem ::
  supportedOperationsFor ( const IString &rmf ) const
    {
    if ( rmf == IDMItem::rmfFrom( IDM::rmLibrary, IDM::rfSharedMem ) )
      // If using <rmLibrary,rfSharedMem> then only copy is supported...
      return IDMItem::copyable & this->supportedOperations();
    else
      // Else, whatever base class supports...
      return Inherited::supportedOperationsFor( rmf );
    }


/****************************************************************************
* CLASS EmployeeItem :: objectCopy()                                             *
****************************************************************************/
IContainerObject* EmployeeItem :: objectCopy()
{
   EmployeeItem *copy = new EmployeeItem(*this);
   return((IContainerObject *)copy);
}


/****************************************************************************
* CLASS EmployeeItem :: transferActionDM()                                       *
****************************************************************************/
EmployeeItem& EmployeeItem::transferActionDM( LPersonnelCnrObject* pObject,
                                              IString xfrDept,
                                              LPersonnelWindow* theWindow)
{
/*----------------------------------------------------------------------------
| Get the employee's record                                                  |
----------------------------------------------------------------------------*/
  LEmployeeData empData = pObject->employeeRecord();
  IString person = IString("'") + empData.firstName() + " " +
                   empData.lastName() + "'";

/*----------------------------------------------------------------------------
| - Change the employee's department                                         |
| - Put the change to the database                                           |
----------------------------------------------------------------------------*/
        if ( xfrDept != "" )
        {
            empData.setDepartment( xfrDept );
            empData.save( empData.employeeNumber() );
            IString curDept = IString("'") + xfrDept + "'";

            IMessageBox msg( theWindow );
            msg.show( person +
                      IApplication::current().userResourceLibrary().
                          loadString( STR_TRANSFER_MSG4 ) +
                      xfrDept + ".",
                      IMessageBox::informationIcon );
        }
    return *this;
}

/****************************************************************************
* CLASS EmployeeItem :: deleteActionDM()                                      *
****************************************************************************/
IBase::Boolean EmployeeItem::deleteActionDM( LPersonnelCnrObject* pObject,
                                              LPersonnelWindow* theWindow)
{
    Boolean retCode = false;

    IMessageBox msgBox( theWindow );

/*----------------------------------------------------------------------------
| Ask if the user really wants to delete or just set to inactive.            |
----------------------------------------------------------------------------*/
    IMessageBox::Response
        response = msgBox.show( IResourceId( STR_PERSONNEL_DELETE_MSG ),
                                IMessageBox::warningIcon |
                                IMessageBox::yesNoCancelButton,
                                ID_PERSONNEL_DELETE_HELP );
/*----------------------------------------------------------------------------
| Get the employee's record                                                  |
----------------------------------------------------------------------------*/
    LEmployeeData empData = pObject->employeeRecord();
    IString person = empData.firstName() + " " +
                     empData.lastName();

/*----------------------------------------------------------------------------
| Delete the employee                                                        |
| - Delete the employee from the database                                    |
| - Delete the cnr object                                                    |
----------------------------------------------------------------------------*/
    if ( response == IMessageBox::no )
    {
        LDeleteEmployee deleteEmp;
        deleteEmp.deleteFromDataBase(
             empData.employeeNumber() );
        msgBox.show( STR_PERSONNEL_DELETED_MSG,
                     IMessageBox::okButton |
                     IMessageBox::informationIcon );
        retCode = true;
    }
/*----------------------------------------------------------------------------
| Set the employee to inactive                                               |
| - Get the employee's status data                                           |
| - Put the status data back with active set to false                        |
----------------------------------------------------------------------------*/
    else if ( response == IMessageBox::yes )
    {
        LStatusData statData( empData.employeeNumber() );
        statData.save( empData.employeeNumber(),
                      statData.statusRate(),
                      statData.statusStart(),
                      statData.statusEnd(),
                      false );

        msgBox.show( STR_PERSONNEL_INACTIVE_MSG,
                  IMessageBox::okButton |
                  IMessageBox::informationIcon );
        retCode = false;
    }
    return retCode;
}
