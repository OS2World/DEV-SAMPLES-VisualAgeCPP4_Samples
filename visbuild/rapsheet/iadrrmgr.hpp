#ifndef _IADRRMGR_
#define _IADRRMGR_
/******************************************************************************
* .FILE:        iadrrmgr.hpp                                                  *
*                                                                             *
* .DESCRIPTION: Header file for the class IAddressClientMgr                   *
*                                                                             *
* .CLASSES:     IAddressClientMgr                                             *
*                                                                             *
* .COPYRIGHT:                                                                 *
*    Licensed Material - Program-Property of IBM                              *
*    (C) Copyright IBM Corp. 1992, 1996 - All Rights Reserved                 *
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
#include "ivbsamps.h"
#include <istdntfy.hpp>                  //Parent of IAddressClientMgr
#include <istring.hpp>                //IString header
#include <ivseq.h>                    //IVSequence header
#include <iadd.hpp>                   //IAddress header

//Forward declarations of other classes

//**************************************************************************
// Class:   IAddressClientMgr
//
// Purpose: Describes IAddressClientMgr
//
//**************************************************************************
class IVBSAMP_IMPORT IAddressClientMgr : public IStandardNotifier
{

public:
/*---------------------  CONSTRUCTORS/DESTRUCTORS  ----------------
 *-----------------------------------------------------------------*/
IAddressClientMgr ();
virtual  ~IAddressClientMgr ();


/*---------------------  NOTIFICATION EVENTS  ----------------------
 | These INotificationId strings are used for all notifications that IWindow
 | provides to its observers:
 |     -parseResultId      Notification identifier provided to
 |                         observers when the parsing of dResultBuffer
 |                         has completed.
 |     -resultBufferId     Notification identifier provided to
 |                         observers when the resultBuffer attribute
 |                         changes.
 |     -resultListId       Notification identifier provided to
 |                         observers when the resultList attribute
 |                         changes.
 |     -resultObjectId     Notification identifier provided to
 |                         observers when the resultObject attribute
 |                         changes.
 |     -resultWrapperId    Notification identifier provided to
 |                         observers when the resultWrapper attribute
 |                         changes.
 *-----------------------------------------------------------------*/
static INotificationId parsedResultId;
static INotificationId resultBufferId;
static INotificationId resultListId;
static INotificationId resultObjectId;
static INotificationId resultWrapperId;


/*---------------------  ATTRIBUTES  -------------------------------
 | The following members are for accessing the attributes of this class:
 |     -resultBuffer       Returns the resultBuffer attribute.
 |     -resultList         Returns resultList attribute, which
 |                         represents the list of address objects
 |                         that were created via parsing the
 |                         resultBuffer attribute.
 |     -resultObject       Returns the resultObject attribute, which
 |                         represents the first address object parsed
 |                         from the resultBuffer attribute.
 |     -resultWrapper      Returns a pointer to the resultObject
 |                         attribute.
 |     -setResultBuffer    Sets the resultBuffer attribute.
 |                         NOTE: the IString passed in should map to
 |                               an IResultRecord, where the resultData
 |                               of the IResultRecord represents zero
 |                               or more address records (IAddressRecord).
 |                               numResults of the IResultRecord must
 |                               indicate how many address records
 |                               resultData contains.
 *-----------------------------------------------------------------*/
virtual IString
  resultBuffer () const;
virtual IVSequence <IAddress *>
  resultList () const;
virtual IVSequence <IAddress *> *
  resultListWrapper () const;
virtual IAddress
  resultObject () const;
virtual IAddress *
  resultWrapper () const;
virtual IAddressClientMgr&
  setResultBuffer (const IString & iResultBuffer);


/*---------------------  ACTIONS   ---------------------------------
 | processResult()  Creates a list of adddress objects by parsing
 |                  information contained in the resultBuffer
 |                  attribute.
 *-----------------------------------------------------------------*/
virtual IAddressClientMgr &
   processResult();


/*---------------------  OPERATORS   -------------------------------
 *-----------------------------------------------------------------*/


protected:
/*---------------------  ENUMERATED TYPES  ------------------------
 *-----------------------------------------------------------------*/

/*---------------------  PROTECTED SERVICES  ----------------------
| These operations or services provided by this class:
-------------------------------------------------------------------*/


private:
/*---------------------  PRIVATE MEMBER DATA  ---------------------
 *-----------------------------------------------------------------*/
  IString dResultBuffer;
  IAddress *dResultWrapper;
  IVSequence <IAddress *> *dResultListWrapper;

/*---------------------  PRIVATE SERVICES  -------------------------
| These operations or services provided by this class:
|    addResult()              adds an Address object's pointer to
|                             the result list.
|    setResultWrapper()       sets the dResultList member data.
-------------------------------------------------------------------*/
IAddressClientMgr & IAddressClientMgr ::
  addResult(IAddress * iAddress);
IAddressClientMgr & IAddressClientMgr ::
  addResult(IAddress & iAddress);

IAddressClientMgr&
  setResultWrapper (IAddress * iResultWrapper);
IAddressClientMgr&
  setResultWrapper (const IAddress & iResult);

};

#endif

