/******************************************************************************
* .FILE:         lperswdm.hpp                                                 *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Definition       *
*                                                                             *
* .CLASSES:      EmployeeItem                                                 *
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
#ifndef _LPERSWDM_
#define _LPERSWDM_


#include "lancelot.h"
#include "ldbase.hpp"

#include <idmprov.hpp>
#include <idmcnrit.hpp>
#include <idmevent.hpp>
#include <idmimage.hpp>
#include <ititle.hpp>
#include <itrace.hpp>
#include <istring.hpp>

class
    LPersonnelCnrObject;
class
    LPersonnelWindow;

class EmployeeItem : public IDMCnrItem {
typedef IDMCnrItem
  Inherited;
public:
  EmployeeItem ( const IDMItem::Handle &item );
  ~EmployeeItem ( );

static bool
  generateSourceItems ( const IDMSourceOperation::Handle &srcOp );

virtual bool
  sourceDiscard ( IDMSourceDiscardEvent &event );

virtual bool
  targetDrop ( IDMTargetDropEvent &event ) ;

virtual unsigned long
  supportedOperationsFor ( const IString &rmf ) const;

IContainerObject*  objectCopy();

EmployeeItem& transferActionDM( LPersonnelCnrObject* pObject,
                                IString xfrDept,
                                LPersonnelWindow* theWindow);


bool deleteActionDM( LPersonnelCnrObject* pObject,
                               LPersonnelWindow* theWindow);

}; // Class EmployeeItem

#endif
