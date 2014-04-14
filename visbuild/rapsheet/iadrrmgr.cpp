/******************************************************************************
* .FILE:        iadrrmgr.cpp                                                  *
*                                                                             *
* .DESCRIPTION: Implementation for the class, IAddressClientMgr               *
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
#include "iadrrmgr.hpp"               //IAddressClientMgr header
#include <inotifev.hpp>
#include "irsltrec.hpp"               //IResultRecord header
#include "iaddrrec.hpp"               //IAddressRecord header


/*******************************************************************
 * Events
 *******************************************************************/
INotificationId IAddressClientMgr :: parsedResultId = "IAddressClientMgr::parsedResult";
INotificationId IAddressClientMgr :: resultBufferId = "IAddressClientMgr::resultBuffer";
INotificationId IAddressClientMgr :: resultListId = "IAddressClientMgr::resultList";
INotificationId IAddressClientMgr :: resultObjectId = "IAddressClientMgr::resultObject";
INotificationId IAddressClientMgr :: resultWrapperId = "IAddressClientMgr::resultWrapper";

/*******************************************************************
 * Constructors
 *******************************************************************/
IAddressClientMgr :: IAddressClientMgr() :
        dResultBuffer(""),
        dResultWrapper(0),
        dResultListWrapper(new IVSequence <IAddress *>)
{
   enableNotification();
   dResultListWrapper->enableNotification();
}

/*******************************************************************
 * Destructor
 *******************************************************************/
IAddressClientMgr :: ~IAddressClientMgr()
{
  ISequence<IAddress *> tempList;
  IAddress *            address;

// if (dResultWrapper)
//    delete dResultWrapper;
  if (dResultListWrapper)
  {
     IVSequence<IAddress*>::Cursor cursor(*dResultListWrapper);
     forCursor( cursor )
       tempList.addAsFirst( dResultListWrapper->elementAt( cursor ) );

     dResultListWrapper->removeAll( );

     ISequence<IAddress*>::Cursor tempCursor( tempList );
     forCursor( cursor )
     {
       address = tempList.elementAt ( tempCursor );
       delete address;
     }
     tempList.removeAll( );

     delete dResultListWrapper;
  }
}


/*******************************************************************
 * Attribute Access Member Functions
 *******************************************************************/
/*------------------------------------------------------------------
 * resultBuffer
 *-----------------------------------------------------------------*/
IString IAddressClientMgr :: resultBuffer () const
{
  return dResultBuffer;
}

IAddressClientMgr & IAddressClientMgr ::
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
IVSequence <IAddress *> IAddressClientMgr ::
  resultList () const
{
  return *dResultListWrapper;
}

IVSequence <IAddress *> * IAddressClientMgr ::
  resultListWrapper () const
{
  return dResultListWrapper;
}

/*------------------------------------------------------------------
 * resultObject and resultWrapper (read-only)
 *-----------------------------------------------------------------*/
IAddress * IAddressClientMgr :: resultWrapper () const
{
  return dResultWrapper;
}

IAddress IAddressClientMgr :: resultObject () const
{
  return *dResultWrapper;
}


/*******************************************************************
 * Actions
 *******************************************************************/
/*------------------------------------------------------------------
 * processResult()
 *    The user controls when dResultBuffer should be processed.
 *-----------------------------------------------------------------*/
IAddressClientMgr & IAddressClientMgr :: processResult ()
{
   IAddress *         addressWrapper;
   IAddressRecord     addressRec;
   unsigned short     recOffset, i;
   IString            buffer;

   IResultRecord resultRec(dResultBuffer);

   recOffset = 1;
   for (i=0 ; i < resultRec.numResults(); i++)
   {
      addressWrapper = new IAddress;

      buffer = resultRec.resultData().subString(
               recOffset,addressRec.size());
      addressRec = buffer;

      addressWrapper->setStreet(addressRec.street());
      addressWrapper->setCity(addressRec.city());
      addressWrapper->setState(addressRec.state());
      addressWrapper->setZip(addressRec.zip());

      addResult(addressWrapper);  //adds addressWrapper to
                                  //the result list

      recOffset += addressRec.size();  //get the next addressRec
   }
   notifyObservers(INotificationEvent(parsedResultId, *this, false));
   return *this;
}

/*******************************************************************
 * Class Member Functions
 *******************************************************************/
/*------------------------------------------------------------------
 * addResult()
 *-----------------------------------------------------------------*/
IAddressClientMgr & IAddressClientMgr ::
  addResult (IAddress * iAddressWrapper)
{
   if (dResultListWrapper->isEmpty())
   {
      setResultWrapper(iAddressWrapper);
   }

   dResultListWrapper->add(iAddressWrapper);
   return *this;
}

/*------------------------------------------------------------------
 * addResult()
 *-----------------------------------------------------------------*/
IAddressClientMgr & IAddressClientMgr ::
  addResult (IAddress & iAddress)
{
   if (dResultListWrapper->isEmpty())
   {
      setResultWrapper(&iAddress);
   }

   dResultListWrapper->add(&iAddress);
   return *this;
}

/*------------------------------------------------------------------
 * setResultWrapper()
 *-----------------------------------------------------------------*/
IAddressClientMgr & IAddressClientMgr ::
  setResultWrapper (IAddress * iResultWrapper)
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
IAddressClientMgr & IAddressClientMgr ::
  setResultWrapper (const IAddress & iResult)
{
  /*****************************************************************
   * Have to make a copy of the IAddress object passed in since it's
   * identified as being a const.  That is, the compiler won't
   * allow dResultWrapper = &iResultWrapper, since it would allow
   * us, via dResultWrapper, to update the IAddress object.
   *****************************************************************/
  return setResultWrapper(new IAddress(iResult));
}

