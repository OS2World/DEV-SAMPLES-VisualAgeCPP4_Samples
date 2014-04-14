#ifndef _IALSRMGR_
#define _IALSRMGR_
/******************************************************************************
* .FILE:        ialsrmgr.hpp                                                  *
*                                                                             *
* .DESCRIPTION: Header file for the class IAliasClientMgr                     *
*                                                                             *
* .CLASSES:     IAliasClientMgr                                               *
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
#include <istdntfy.hpp>               //Parent of IAliasClientMgr
#include <istring.hpp>                //IString header
#include <ivseq.h>                    //IVSequence header
#include "ialias.hpp"                 //IAlias header

//Forward declarations of other classes

//**************************************************************************
// Class:   IAliasClientMgr
//
// Purpose: Describes IAliasClientMgr
//
//**************************************************************************
class IVBSAMP_IMPORT IAliasClientMgr : public IStandardNotifier
{

public:
/*---------------------  CONSTRUCTORS/DESTRUCTORS  ----------------
 *-----------------------------------------------------------------*/
IAliasClientMgr ();
virtual  ~IAliasClientMgr ();


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
static INotificationId requestBufferId;
static INotificationId resultBufferId;
static INotificationId resultListId;
//temporarily added resultListWrapperId
static INotificationId resultListWrapperId;
static INotificationId resultObjectId;
static INotificationId resultWrapperId;
static INotificationId sameRequestId;
static INotificationId manyObjectsFoundId;
static INotificationId noObjectsFoundId;
static INotificationId oneObjectFoundId;


/*---------------------  ATTRIBUTES  -------------------------------
 | The following members are for accessing the attributes of this class:
 |     -resultBuffer       Returns the resultBuffer attribute.
 |     -resultList         Returns resultList attribute, which
 |                         represents the list of alias objects
 |                         that were created via parsing the
 |                         resultBuffer attribute.
 |     -resultObject       Returns the resultObject attribute, which
 |                         represents the first alias object parsed
 |                         from the resultBuffer attribute.
 |     -resultWrapper      Returns a pointer to the resultObject
 |                         attribute.
 |     -setResultBuffer    Sets the resultBuffer attribute.
 |                         NOTE: the IString passed in should map to
 |                               an IResultRecord, where the resultData
 |                               of the IResultRecord represents zero
 |                               or more alias records (IAliasRecord).
 |                               numResults of the IResultRecord must
 |                               indicate how many alias records
 |                               resultData contains.
 *-----------------------------------------------------------------*/
virtual IString
  requestBuffer () const;
virtual IString
  resultBuffer () const;
virtual IVSequence <IAlias *>
  resultList () const;
virtual IVSequence <IAlias *> *
  resultListWrapper () const;
virtual IAlias
  resultObject () const;
virtual IAlias *
  resultWrapper () const;
virtual IAliasClientMgr&
  setRequestBuffer (const IString & iRequestBuffer);
virtual IAliasClientMgr&
  setResultBuffer (const IString & iResultBuffer);


/*---------------------  ACTIONS   ---------------------------------
 | allByBookNumber()  Retrieves from the database a list of aliases
 |                    for a given suspect.
 | processResult()    Creates a list of adddress objects by parsing
 |                    information contained in the resultBuffer
 |                    attribute.
 *-----------------------------------------------------------------*/
virtual IString
   allByBookNumber (unsigned long aBookNumber);
virtual IAliasClientMgr &
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
  IString dRequestBuffer;
  IString dResultBuffer;
  IAlias *dResultWrapper;
  IVSequence <IAlias *> *dResultListWrapper;

/*---------------------  PRIVATE SERVICES  -------------------------
| These operations or services provided by this class:
|    addResult()              adds an Alias object's pointer to
|                             the result list.
|    setResultWrapper()       sets the dResultList member data.
-------------------------------------------------------------------*/
IAliasClientMgr & IAliasClientMgr ::
  addResult(IAlias * iAlias);
IAliasClientMgr & IAliasClientMgr ::
  addResult(IAlias & iAlias);

IAliasClientMgr&
  setResultWrapper (IAlias * iResultWrapper);
IAliasClientMgr&
  setResultWrapper (const IAlias & iResult);

};

#endif

