/******************************************************************************
* .FILE:        ialsrmgr.cpp                                                  *
*                                                                             *
* .DESCRIPTION: Implementation for the class, IAliasClientMgr                 *
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
#include "ialsrmgr.hpp"               //IAliasClientMgr header
#include <inotifev.hpp>
#include <itrace.hpp>
#include "irsltrec.hpp"               //IResultRecord header
#include "ialsrec.hpp"                //IAliasRecord header
#include "querydb.hpp"


/*******************************************************************
 * Events
 *******************************************************************/
INotificationId IAliasClientMgr :: parsedResultId = "IAliasClientMgr::parsedResult";
INotificationId IAliasClientMgr :: requestBufferId = "IAliasClientMgr::requestBuffer";
INotificationId IAliasClientMgr :: resultBufferId = "IAliasClientMgr::resultBuffer";
INotificationId IAliasClientMgr :: resultListId = "IAliasClientMgr::resultList";
INotificationId IAliasClientMgr :: resultListWrapperId = "IAliasClientMgr::resultListWrapper";
INotificationId IAliasClientMgr :: resultObjectId = "IAliasClientMgr::resultObject";
INotificationId IAliasClientMgr :: resultWrapperId = "IAliasClientMgr::resultWrapper";
INotificationId IAliasClientMgr :: sameRequestId = "IAliasClientMgr::sameRequest";
INotificationId IAliasClientMgr :: noObjectsFoundId = "IAliasClientMgr::noObjectsFound";
INotificationId IAliasClientMgr :: oneObjectFoundId = "IAliasClientMgr::oneObjectFound";
INotificationId IAliasClientMgr :: manyObjectsFoundId = "IAliasClientMgr::manyObjectsFound";


/*******************************************************************
 * Constructors
 *******************************************************************/
IAliasClientMgr :: IAliasClientMgr() :
        dRequestBuffer(""),
        dResultBuffer(""),
        dResultWrapper(0),
        dResultListWrapper(new IVSequence<IAlias *>)
{
   enableNotification();
   dResultListWrapper->enableNotification();
}


/*******************************************************************
 * Destructor
 *******************************************************************/
IAliasClientMgr :: ~IAliasClientMgr()
{
  ISequence<IAlias *> tempList;
  IAlias *            alias;

// if (dResultWrapper)
//    delete dResultWrapper;
  if (dResultListWrapper)
  {
     IVSequence<IAlias*>::Cursor cursor(*dResultListWrapper);
     forCursor( cursor )
       tempList.addAsFirst( dResultListWrapper->elementAt( cursor ) );

     dResultListWrapper->removeAll( );

     ISequence<IAlias*>::Cursor tempCursor( tempList );
     forCursor( cursor )
     {
       alias = tempList.elementAt ( tempCursor );
       delete alias;
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
IString IAliasClientMgr :: requestBuffer () const
{
  return dRequestBuffer;
}

IAliasClientMgr & IAliasClientMgr ::
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
IString IAliasClientMgr :: resultBuffer () const
{
  return dResultBuffer;
}

IAliasClientMgr & IAliasClientMgr ::
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
IVSequence <IAlias *> IAliasClientMgr ::
  resultList () const
{
  return *dResultListWrapper;
}

IVSequence <IAlias *> * IAliasClientMgr ::
  resultListWrapper () const
{
  return dResultListWrapper;
}

/*------------------------------------------------------------------
 * resultObject and resultWrapper (read-only)
 *-----------------------------------------------------------------*/
IAlias * IAliasClientMgr :: resultWrapper () const
{
  return dResultWrapper;
}

IAlias IAliasClientMgr :: resultObject () const
{
  return *dResultWrapper;
}


/*******************************************************************
 * Actions
 *******************************************************************/
/*------------------------------------------------------------------
 * allbyBookNumber
 *-----------------------------------------------------------------*/
IString IAliasClientMgr :: allByBookNumber (unsigned long aBookNumber)
{
  IFUNCTRACE_DEVELOP();

  IResultRecord rsltRec;
  IString suspectKey = IString(aBookNumber);

  ITRACE_DEVELOP("suspectKey: " + suspectKey + ".");

  if (dRequestBuffer != suspectKey)
  {
     setRequestBuffer(suspectKey);
     ITRACE_DEVELOP("Calling the DB server.");
     rsltRec = getAllAliases(aBookNumber);
     ITRACE_DEVELOP("Number aliases found: " + IString(rsltRec.numResults()));
  }
  else
     setRequestBuffer(suspectKey);

  return rsltRec.asString();
}

/*------------------------------------------------------------------
 * processResult()
 *    The user controls when dResultBuffer should be processed.
 *-----------------------------------------------------------------*/
IAliasClientMgr & IAliasClientMgr :: processResult ()
{
   IAlias *           aliasObj;
   IAliasRecord       aliasRec;
   unsigned short     recOffset, i;
   IString            buffer;

  IFUNCTRACE_DEVELOP();

  if (!dResultBuffer.isWhiteSpace())
  {
     ITRACE_DEVELOP("resultBuffer received: " + dResultBuffer + ".");
     IResultRecord resultRec(dResultBuffer);
     ITRACE_DEVELOP(resultRec.asDebugInfo());

     //clear the result list if it's not empty (i.e., if it was set in a previous invocation)
     if (dResultListWrapper->numberOfElements())
     {
        ITRACE_DEVELOP("had to empty the resultList");
        dResultListWrapper->removeAll();
     }

     recOffset = 1;
     for (i=0 ; i < resultRec.numResults(); i++)
     {
        aliasObj = new IAlias;

        buffer = resultRec.resultData().subString(recOffset,
                                                  aliasRec.size());
        aliasRec = buffer;

        ITRACE_DEVELOP("alias name pulled from the record: " + aliasRec.name() + ".");
        aliasObj->setAlias(aliasRec.name());
        ITRACE_DEVELOP("alias name set in alias object: " + aliasObj->alias() + ".");

        addResult(aliasObj);      //adds alias to
                                  //the result list

        recOffset += aliasRec.size();  //get the next aliasRec
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
IAliasClientMgr & IAliasClientMgr ::
  addResult (IAlias * iAliasWrapper)
{
   IFUNCTRACE_DEVELOP();
   ITRACE_DEVELOP("addResult(*) of ialsrmgr.");

   if (dResultListWrapper->isEmpty())
   {
      setResultWrapper(iAliasWrapper);
   }

   dResultListWrapper->add(iAliasWrapper);
   ITRACE_DEVELOP("added an alias to the resultList");
   return *this;
}

/*------------------------------------------------------------------
 * addResult()
 *-----------------------------------------------------------------*/
IAliasClientMgr & IAliasClientMgr ::
  addResult (IAlias & iAlias)
{
   IFUNCTRACE_DEVELOP();
   ITRACE_DEVELOP("addResult(&) of ialsrmgr.");

   if (dResultListWrapper->isEmpty())
   {
      setResultWrapper(&iAlias);
   }

   dResultListWrapper->add(&iAlias);
   ITRACE_DEVELOP("added an alias to the resultList");
   return *this;
}

/*------------------------------------------------------------------
 * setResultWrapper()
 *-----------------------------------------------------------------*/
IAliasClientMgr & IAliasClientMgr ::
  setResultWrapper (IAlias * iResultWrapper)
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
IAliasClientMgr & IAliasClientMgr ::
  setResultWrapper (const IAlias & iResult)
{
  /*****************************************************************
   * Have to make a copy of the IAlias object passed in since it's
   * identified as being a const.  That is, the compiler won't
   * allow dResultWrapper = &iResultWrapper, since it would allow
   * us, via dResultWrapper, to update the IAlias object.
   *****************************************************************/
  return setResultWrapper(new IAlias(iResult));
}

