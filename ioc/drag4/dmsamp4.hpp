/******************************************************************************
* .FILE:         dmsamp4.cpp                                                  *
*                                                                             *
* .DESCRIPTION:  Direct Manipulation Sample Program 4: Class Implementation   *
*                                                                             *
* .CLASSES:      DMSample4Window                                              *
*                CustomerItem                                                 *
*                MyWindow                                                     *
*                MySourceWin                                                  *
*                MyTargetWin                                                  *
*                Customer                                                     *
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
#include "dmsamp3.hpp"

#include <idmprov.hpp>
#include <idmcnrit.hpp>
#include <idmevent.hpp>
#include <idmimage.hpp>
#include <ititle.hpp>
#include <itrace.hpp>
#include <istring.hpp>


class CustomerItem : public IDMCnrItem {
typedef IDMCnrItem
  Inherited;
/*******************************************************************************
* Objects of this class are used to show direct manipulation support for       *
* containers.  Instances of this object are created to allow a demonstration   *
* of copying of Customer objects between inter-process containers, when 2      *
* copies of this sample are started.                                           *
*******************************************************************************/
public:
/*--------------------------- Constructor/Destructor ---------------------------
| Objects of this class are constructed from a generic item handle.            |
------------------------------------------------------------------------------*/
  CustomerItem  ( const IDMItem::Handle& item );
  ~CustomerItem ( ) {};

/*------------------------------ Source Items ----------------------------------
| This function generates source items:                                        |
|   generateSourceItems - Generates Customer object items based upon           |
|                         selected object(s) in the source container.          |
------------------------------------------------------------------------------*/
static bool
  generateSourceItems ( IDMSourceOperation* srcOp );

/*-------------------------------- Operations ----------------------------------
|   supportedOperationsFor - Restricts the operation to copy only if the       |
|                            selected RMF is the ICLUI shared memory RMF.      |
------------------------------------------------------------------------------*/
virtual unsigned long
  supportedOperationsFor ( const IString& rmf ) const;

/*---------------------------------- Shredder ----------------------------------
|   sourceDiscard - Removes the Customer object from the source container.     |
------------------------------------------------------------------------------*/
virtual bool
  sourceDiscard ( IDMSourceDiscardEvent& event );

/*------------------------------ Drop Processing -------------------------------
| targetDrop - Create a copy of the dropped Customer object.                   |
------------------------------------------------------------------------------*/
virtual bool
  targetDrop ( IDMTargetDropEvent& event );

};

/*******************************************************************************
* These windows are similar to those from dmsamp3 but use icon view and        *
* permit dragging/dropping within the same window.  Note that sometimes it     *
* is necessary to restrict target support so if the window title includes      *
* "source only" or "target only" we only permit drag/drop, respectively.       *
*******************************************************************************/
class DMSample4Window : public MyWindow {
public:
/*-------------------------- Constructor/Destructor ----------------------------
| Objects of this class are constructed by providing the following:            |
|   o A pointer to a window title                                              |
------------------------------------------------------------------------------*/
  DMSample4Window  ( const char *aTitle );
  ~DMSample4Window ( ) {};

private:
IDMItemProviderFor< CustomerItem >
  provider;

ITitle
  title;
};
