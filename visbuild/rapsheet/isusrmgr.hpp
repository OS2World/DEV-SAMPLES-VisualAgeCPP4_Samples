#ifndef _ISUSRMGR_
#define _ISUSRMGR_
/******************************************************************************
* .FILE:        isusrmgr.hpp                                                  *
*                                                                             *
* .DESCRIPTION: Header file for the class ISuspectClientMgr                   *
*                                                                             *
* .CLASSES:     ISuspectClientMgr                                             *
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
#include <istdntfy.hpp>
#include <istring.hpp>
#include <ivseq.h>
#include "isuspect.hpp"


/*----------------------------------------------------------------------------*/
/* Align classes on four byte boundary.                                       */
/*----------------------------------------------------------------------------*/
#pragma pack(4)

//**************************************************************************
// Class:   ISuspectClientMgr
//
// Purpose:
//
//**************************************************************************
class IVBSAMP_IMPORT ISuspectClientMgr : public IStandardNotifier
{

public:

/*---------------------  CONSTRUCTORS/DESTRUCTORS  ----------------
 *-----------------------------------------------------------------*/
ISuspectClientMgr ();
virtual  ~ISuspectClientMgr ();


/*---------------------  NOTIFICATION EVENTS  ----------------------
 | These INotificationId strings are used for all notifications that
 | this class provides to its observers:
 *-----------------------------------------------------------------*/
static INotificationId requestBufferId;
static INotificationId resultBufferId;
static INotificationId resultListId;
//temporarily added resultListWrapperId
static INotificationId resultListWrapperId;
static INotificationId resultObjectId;
static INotificationId resultWrapperId;

static INotificationId manyObjectsFoundId;
static INotificationId noObjectsFoundId;
static INotificationId oneObjectFoundId;
static INotificationId parsedResultId;
static INotificationId sameRequestId;


/*---------------------  ATTRIBUTES  -------------------------------
 *-----------------------------------------------------------------*/
/*------------------------------------------------------------------
 * requestBuffer
 *-----------------------------------------------------------------*/
virtual IString
  requestBuffer () const;
virtual ISuspectClientMgr&
  setRequestBuffer (const IString & iRequestBuffer);

/*------------------------------------------------------------------
 * resultBuffer
 *-----------------------------------------------------------------*/
virtual IString
  resultBuffer () const;
virtual ISuspectClientMgr&
  setResultBuffer (const IString & iResultBuffer);

/*------------------------------------------------------------------
 * resultList (read-only) and resultListWrapper
 *-----------------------------------------------------------------*/
virtual IVSequence<ISuspect *>
  resultList () const;
virtual IVSequence <ISuspect *> *
  resultListWrapper () const;

/*------------------------------------------------------------------
 * resultObject and resultWrapper (read-only)
 *-----------------------------------------------------------------*/
virtual ISuspect
  resultObject () const;
virtual ISuspect *
  resultWrapper () const;


/*---------------------  ACTIONS   ---------------------------------
 | getAll                Get all suspects from the database.
 |                       (This application is limited in scope;
 |                       the primary purpose was to show the use
 |                       of a container and notebook.  So, the
 |                       use of a database is limited.  Information
 |                       about suspects are retrieved from the database.)
 | primeDBWithSuspects   prime the database with a small set of suspects
 |                       so the sample can enable data to be viewed
 | processResult         Creates a list of suspect objects by parsing
 |                       information contained in the resultBuffer
 |                       attribute.
 *-----------------------------------------------------------------*/
virtual IString getAll ();
virtual ISuspectClientMgr & primeDBWithSuspects ();
virtual ISuspectClientMgr & processResult ();


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
  IVSequence<ISuspect *> * dResultListWrapper;
  ISuspect * dResultWrapper;

// List of Data Members that are not Attributes

/*---------------------  PRIVATE SERVICES  -------------------------
| These operations or services provided by this class:
|    addResult()              adds a suspect object's pointer to the
|                             result list.
|    setResultWrapper()       sets the dResultList member data.
-------------------------------------------------------------------*/
virtual ISuspectClientMgr &
  addResult (ISuspect * iSuspectWrapper);
virtual ISuspectClientMgr &
  addResult (ISuspect & iSuspect);

virtual ISuspectClientMgr &
  setResultWrapper (ISuspect * iResultWrapper);
virtual ISuspectClientMgr &
  setResultWrapper (const ISuspect & iResult);
};

/*----------------------------------------------------------------------------*/
/* Resume compiler default packing.                                           */
/*----------------------------------------------------------------------------*/
#pragma pack()

#endif

