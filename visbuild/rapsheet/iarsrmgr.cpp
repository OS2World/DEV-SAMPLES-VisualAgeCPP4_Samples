/******************************************************************************
* .FILE:        iarsrmgr.cpp                                                  *
*                                                                             *
* .DESCRIPTION: Implementation for the class, IArrestClientMgr                *
*                                                                             *
* .CLASSES:     IArrestClientMgr                                              *
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
#include "iarsrmgr.hpp"               //IArrestClientMgr header
#include <inotifev.hpp>
#include <itrace.hpp>
#include "irsltrec.hpp"               //IResultRecord header
#include "iarstrec.hpp"               //IArrestRecord header
#include "querydb.hpp"

/*******************************************************************
 * Events
 *******************************************************************/
INotificationId IArrestClientMgr :: parsedResultId = "IArrestClientMgr::parsedResult";
INotificationId IArrestClientMgr :: requestBufferId = "IArrestClientMgr::requestBuffer";
INotificationId IArrestClientMgr :: resultBufferId = "IArrestClientMgr::resultBuffer";
INotificationId IArrestClientMgr :: resultListId = "IArrestClientMgr::resultList";
INotificationId IArrestClientMgr :: resultListWrapperId = "IArrestClientMgr::resultListWrapper";
INotificationId IArrestClientMgr :: resultObjectId = "IArrestClientMgr::resultObject";
INotificationId IArrestClientMgr :: resultWrapperId = "IArrestClientMgr::resultWrapper";
INotificationId IArrestClientMgr :: sameRequestId = "IArrestClientMgr::sameRequest";
INotificationId IArrestClientMgr :: noObjectsFoundId = "IArrestClientMgr::noObjectsFound";
INotificationId IArrestClientMgr :: oneObjectFoundId = "IArrestClientMgr::oneObjectFound";
INotificationId IArrestClientMgr :: manyObjectsFoundId = "IArrestClientMgr::manyObjectsFound";

/*******************************************************************
 * Constructors
 *******************************************************************/
IArrestClientMgr :: IArrestClientMgr() :
        dRequestBuffer(""),
        dResultBuffer(""),
        dResultWrapper(0),
        dResultListWrapper(new IVSequence<IArrest *>)
{
   enableNotification();
   dResultListWrapper->enableNotification();
}

/*******************************************************************
 * Destructor
 *******************************************************************/
IArrestClientMgr :: ~IArrestClientMgr()
{
  ISequence<IArrest *> tempList;
  IArrest *            arrest;

// if (dResultWrapper)
//    delete dResultWrapper;
  if (dResultListWrapper)
  {
     IVSequence<IArrest*>::Cursor cursor(*dResultListWrapper);
     forCursor( cursor )
       tempList.addAsFirst( dResultListWrapper->elementAt( cursor ) );

     dResultListWrapper->removeAll( );

     ISequence<IArrest*>::Cursor tempCursor( tempList );
     forCursor( cursor )
     {
       arrest = tempList.elementAt ( tempCursor );
       delete arrest;
     }
     tempList.removeAll( );

     delete dResultListWrapper;
  }
}


/*******************************************************************
 * Attribute Access Member Functions
 *******************************************************************/
/*------------------------------------------------------------------
 * requestBuffer
 *-----------------------------------------------------------------*/
IString IArrestClientMgr :: requestBuffer () const
{
  return dRequestBuffer;
}

IArrestClientMgr & IArrestClientMgr ::
  setRequestBuffer (const IString & iRequestBuffer)
{
  if (dRequestBuffer != iRequestBuffer)
  {
    dRequestBuffer = iRequestBuffer;
    notifyObservers(INotificationEvent(requestBufferId, *this, true,
                                       IEventData((char *)iRequestBuffer)));
  }
  else
    notifyObservers(INotificationEvent(sameRequestId, *this, false));
  return *this;
}

/*------------------------------------------------------------------
 * resultBuffer
 *-----------------------------------------------------------------*/
IString IArrestClientMgr :: resultBuffer () const
{
  return dResultBuffer;
}

IArrestClientMgr & IArrestClientMgr ::
  setResultBuffer (const IString & iResultBuffer)
{
  if (dResultBuffer != iResultBuffer)
  {
    dResultBuffer = iResultBuffer;
    notifyObservers(INotificationEvent(resultBufferId, *this, true,
                               IEventData((char *)iResultBuffer)));
  } /* endif */
  return *this;
}

/*------------------------------------------------------------------
 * resultList (read-only) and resultListWrapper
 *-----------------------------------------------------------------*/
IVSequence <IArrest *> IArrestClientMgr ::
  resultList () const
{
  return *dResultListWrapper;
}

IVSequence <IArrest *> * IArrestClientMgr ::
  resultListWrapper () const
{
  return dResultListWrapper;
}

/*------------------------------------------------------------------
 * resultObject and resultWrapper (read-only)
 *-----------------------------------------------------------------*/
IArrest * IArrestClientMgr :: resultWrapper () const
{
  return dResultWrapper;
}

IArrest IArrestClientMgr :: resultObject () const
{
  return *dResultWrapper;
}


/*******************************************************************
 * Actions
 *******************************************************************/
/*------------------------------------------------------------------
 * allbyBookNumber
 *-----------------------------------------------------------------*/
IString IArrestClientMgr :: allByBookNumber (unsigned long aBookNumber)
{
  IResultRecord rsltRec;
  IString suspectKey = IString(aBookNumber);

  IFUNCTRACE_DEVELOP();
  ITRACE_DEVELOP("suspectKey: " + suspectKey + ".");

  if (dRequestBuffer != suspectKey)
  {
     setRequestBuffer(suspectKey);
     ITRACE_DEVELOP("Calling the DB server.");
     rsltRec = getAllArrests(aBookNumber);
     ITRACE_DEVELOP("Number arrest records found: " + IString(rsltRec.numResults()));
  }
  else
     setRequestBuffer(suspectKey);

  return rsltRec.asString();
}

/*------------------------------------------------------------------
 * processResult()
 *    The user controls when dResultBuffer should be processed.
 *-----------------------------------------------------------------*/
IArrestClientMgr & IArrestClientMgr :: processResult ()
{
   IArrest *          arrestWrapper;
   IArrestRecord      arrestRec;
   unsigned short     recOffset, i;
   IString            buffer;

  IFUNCTRACE_DEVELOP();

  if (!dResultBuffer.isWhiteSpace())
  {
   IResultRecord resultRec(dResultBuffer);

   //clear the result list if it's not empty (i.e., if it was set in a previous invocation)
   if (dResultListWrapper->numberOfElements())
      dResultListWrapper->removeAll();

   recOffset = 1;
   for (i=0 ; i < resultRec.numResults(); i++)
   {
      arrestWrapper = new IArrest;

      buffer = resultRec.resultData().subString(
               recOffset,arrestRec.size());
      arrestRec = buffer;

      arrestWrapper->setCharge(arrestRec.charge());
      arrestWrapper->setStatus(arrestRec.status());
      arrestWrapper->setStatusDate(arrestRec.statusDate());

      addResult(arrestWrapper);  //adds arrestWrapper to
                                 //the result list

      recOffset += arrestRec.size();  //get the next arrestRec
   }

   notifyObservers(INotificationEvent(parsedResultId, *this, false));
   if (resultRec.numResults() == 1)
      notifyObservers(INotificationEvent(oneObjectFoundId, *this, false));
   else if (resultRec.numResults() == 0)
   {
      notifyObservers(INotificationEvent(noObjectsFoundId, *this, false));
      throw IException("No aliases exist for the specified suspect."); }
   else
      notifyObservers(INotificationEvent(manyObjectsFoundId, *this, false));
  }

   return *this;
}

/*******************************************************************
 * Class Member Functions
 *******************************************************************/
/*------------------------------------------------------------------
 * addResult()
 *-----------------------------------------------------------------*/
IArrestClientMgr & IArrestClientMgr ::
  addResult (IArrest * iArrestWrapper)
{
   IFUNCTRACE_DEVELOP();
   ITRACE_DEVELOP("addResult(*) of iarsrmgr.");

   if (dResultListWrapper->isEmpty())
   {
      setResultWrapper(iArrestWrapper);
   }

   dResultListWrapper->add(iArrestWrapper);
   return *this;
}

/*------------------------------------------------------------------
 * addResult()
 *-----------------------------------------------------------------*/
IArrestClientMgr & IArrestClientMgr ::
  addResult (IArrest & iArrest)
{
   IFUNCTRACE_DEVELOP();
   ITRACE_DEVELOP("addResult(&) of iarsrmgr.");

   if (dResultListWrapper->isEmpty())
   {
      setResultWrapper(&iArrest);
   }

   dResultListWrapper->add(&iArrest);
   return *this;
}

/*------------------------------------------------------------------
 * setResultWrapper()
 *-----------------------------------------------------------------*/
IArrestClientMgr & IArrestClientMgr ::
  setResultWrapper (IArrest * iResultWrapper)
{
  if (dResultWrapper != iResultWrapper)
  {
     if (dResultWrapper)
        delete dResultWrapper;
     dResultWrapper = iResultWrapper;
     notifyObservers(INotificationEvent(resultObjectId, *this, false));
     notifyObservers(INotificationEvent(resultWrapperId, *this, false));
  }
  return *this;
}

/*------------------------------------------------------------------
 * setResultWrapper()
 *-----------------------------------------------------------------*/
IArrestClientMgr & IArrestClientMgr ::
  setResultWrapper (const IArrest & iResult)
{
  /*****************************************************************
   * Have to make a copy of the IArrest object passed in since it's
   * identified as being a const.  That is, the compiler won't
   * allow dResultWrapper = &iResultWrapper, since it would allow
   * us, via dResultWrapper, to update the IArrest object.
   *****************************************************************/
  return setResultWrapper(new IArrest(iResult));
}

