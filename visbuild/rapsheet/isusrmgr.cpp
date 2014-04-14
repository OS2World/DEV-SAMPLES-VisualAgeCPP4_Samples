/******************************************************************************
* .FILE:        isusrmgr.cpp                                                  *
*                                                                             *
* .DESCRIPTION: Implementation for the class, ISuspectClientMgr               *
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
#include "isusrmgr.hpp"
#include <inotifev.hpp>
#include <itrace.hpp>
#include <iexcbase.hpp>
#include <iprofile.hpp>
#include <iadd.hpp>
#include "irsltrec.hpp"
#include "isusrec.hpp"
#include "querydb.hpp"


/*******************************************************************
 * Events
 *******************************************************************/
INotificationId ISuspectClientMgr :: requestBufferId = "ISuspectClientMgr::requestBuffer";
INotificationId ISuspectClientMgr :: resultBufferId = "ISuspectClientMgr::resultBuffer";
INotificationId ISuspectClientMgr :: resultListId = "ISuspectClientMgr::resultList";
INotificationId ISuspectClientMgr :: resultListWrapperId = "ISuspectClientMgr::resultListWrapper";
INotificationId ISuspectClientMgr :: resultObjectId = "ISuspectClientMgr::resultObject";
INotificationId ISuspectClientMgr :: resultWrapperId = "ISuspectClientMgr::resultWrapper";

INotificationId ISuspectClientMgr :: parsedResultId = "ISuspectClientMgr::parsedResult";
INotificationId ISuspectClientMgr :: sameRequestId = "ISuspectClientMgr::sameRequest";
INotificationId ISuspectClientMgr :: noObjectsFoundId = "ISuspectClientMgr::noObjectsFound";
INotificationId ISuspectClientMgr :: oneObjectFoundId = "ISuspectClientMgr::oneObjectFound";
INotificationId ISuspectClientMgr :: manyObjectsFoundId = "ISuspectClientMgr::manyObjectsFound";


/*******************************************************************
 * Constructors
 *******************************************************************/
ISuspectClientMgr :: ISuspectClientMgr() :
        dRequestBuffer(""),
        dResultBuffer(""),
        dResultWrapper(0),
        dResultListWrapper(new IVSequence<ISuspect *>)
{
   enableNotification();
   dResultListWrapper->enableNotification();
}


/*******************************************************************
 * Destructor
 *******************************************************************/
ISuspectClientMgr :: ~ISuspectClientMgr()
{
  ISequence<ISuspect *> tempList;
  ISuspect *            suspect;

// if (dResultWrapper)
//    delete dResultWrapper;
  if (dResultListWrapper)
  {
     IVSequence<ISuspect*>::Cursor cursor(*dResultListWrapper);
     forCursor( cursor )
       tempList.addAsFirst( dResultListWrapper->elementAt( cursor ) );

     dResultListWrapper->removeAll( );

     ISequence<ISuspect*>::Cursor tempCursor( tempList );
     forCursor( cursor )
     {
       suspect = tempList.elementAt ( tempCursor );
       delete suspect;
     }
     tempList.removeAll( );

     delete dResultListWrapper;
  }
}


/****************************************************************************
 * Attribute Access Member Functions
 ****************************************************************************/
/*------------------------------------------------------------------
 * requestBuffer
 *-----------------------------------------------------------------*/
IString ISuspectClientMgr :: requestBuffer () const
{
  return dRequestBuffer;
}

ISuspectClientMgr & ISuspectClientMgr ::
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
IString ISuspectClientMgr :: resultBuffer () const
{
  return dResultBuffer;
}

ISuspectClientMgr & ISuspectClientMgr ::
  setResultBuffer (const IString & iResultBuffer)
{
  if (dResultBuffer != iResultBuffer)
  {
    dResultBuffer = iResultBuffer;                  //Set class.attribute.title%>
    notifyObservers(INotificationEvent(resultBufferId, *this, true,
                                       IEventData((char *)iResultBuffer)));
  }
  else
    notifyObservers(INotificationEvent(resultBufferId, *this, false));
    //moved this outside of the test so would fire each time; found wasn't
    //getting message displayed when did 2 consecutive not-found searches

  return *this;
}

/*------------------------------------------------------------------
 * resultList (read-only) and resultListWrapper
 *-----------------------------------------------------------------*/
IVSequence <ISuspect *> ISuspectClientMgr ::
  resultList () const
{
  return *dResultListWrapper;
}

IVSequence <ISuspect *> * ISuspectClientMgr ::
  resultListWrapper () const
{
  return dResultListWrapper;
}

/*------------------------------------------------------------------
 * resultObject and resultWrapper (read-only)
 *-----------------------------------------------------------------*/
ISuspect * ISuspectClientMgr :: resultWrapper () const
{
  return dResultWrapper;
}

ISuspect ISuspectClientMgr :: resultObject () const
{
  return *dResultWrapper;
}


/*******************************************************************
 * Actions
 *******************************************************************/
/*------------------------------------------------------------------
 * getAll  (retrieves all suspects from DB2/2 database)
 *-----------------------------------------------------------------*/
IString ISuspectClientMgr :: getAll()
{

  IResultRecord rsltRec;

  IFUNCTRACE_DEVELOP();
  ITRACE_DEVELOP("Calling the DB server.");
  rsltRec = getAllSuspects();
  ITRACE_DEVELOP("Number suspects found: " + IString(rsltRec.numResults()));

  return rsltRec.asString();
}

/*------------------------------------------------------------------
 * primeDBWithSuspects
 *-----------------------------------------------------------------*/
ISuspectClientMgr & ISuspectClientMgr :: primeDBWithSuspects ()
{
   IString profKey,
           profData;

   /***************************************************************
    * Prime the DB with some suspects
    ***************************************************************/
   IProfile suspectProfile(SUSPECT_INI);
   suspectProfile.setDefaultApplicationName(SUSPECT_APPNAME);

   profKey = "0";
   profData = "Mamo,Lou,1,1,1,145,63,0,0,1,01-01-1951,0,7,7,7,101 Main St,Kalamazoo,Dunn,MI,34534, ,Ring leader of the notorious CLASS mob., , ,Rose on right forearm,";
   suspectProfile.addOrReplaceElementWithKey(profKey, profData);

   profKey = "1";
   profData = "Lavin,Dave,1,2,0,155,69,1,0,0,06-18-1956,1,1,3,2,234 Main St,Cary,Wake,NC,27512, ,Hit man for Knuckles Mamo. Works closely with the Hammer.,2 inch scar above right eyebrow, , ,";
   suspectProfile.addOrReplaceElementWithKey(profKey, profData);

   profKey = "2";
   profData = "Spung,Peter,1,3,3,165,72,0,0,0,11-28-1958,2,7,7,7,565 Capitol Ave, Raleigh,Wake,NC,27444, ,Juggles the books for Knuckles Mamo. Likes to gamble., , , ,";
   suspectProfile.addOrReplaceElementWithKey(profKey, profData);

   profKey = "3";
   profData = "Lebda,Ken,1,0,2,165,70,0,0,0,10-31-1953,3,5,6,4,767 Western Blvd,Raleigh,Wake,NC,27890, ,Main hit man for Knuckles Mamo. Likes to use wooden weapons., , , ,";
   suspectProfile.addOrReplaceElementWithKey(profKey, profData);

   profKey = "4";
   profData = "Carpenter,Susan,0,3,3,135,62,0,0,0,07-07-1957,4,7,7,7,777 Orchard Lane,Cary,Wake,NC,27512, ,Prints conterfeit money., , , ,";
   suspectProfile.addOrReplaceElementWithKey(profKey, profData);

   /***************************************************************
    * Prime the DB with the suspects' aliases
    ***************************************************************/
   IProfile aliasProfile(ALIAS_INI);
   aliasProfile.setDefaultApplicationName(ALIAS_APPNAME);

   profKey = "0";
   profData = "0,Louie Knuckles Mamo,";
   aliasProfile.addOrReplaceElementWithKey(profKey, profData);

   profKey = "1";
   profData = "0,The God Father,";
   aliasProfile.addOrReplaceElementWithKey(profKey, profData);

   profKey = "2";
   profData = "1,Waves Lavin,";
   aliasProfile.addOrReplaceElementWithKey(profKey, profData);

   profKey = "3";
   profData = "2,The Juggler,";
   aliasProfile.addOrReplaceElementWithKey(profKey, profData);

   profKey = "4";
   profData = "3,The Hammer,";
   aliasProfile.addOrReplaceElementWithKey(profKey, profData);

   /***************************************************************
    * Prime the DB with the suspects' arrests
    ***************************************************************/
   IProfile arrestProfile(ARREST_INI);
   arrestProfile.setDefaultApplicationName(ARREST_APPNAME);

   profKey = "0";
   profData = "0,Murder,Acquitted,03-02-1994,";
   arrestProfile.addOrReplaceElementWithKey(profKey, profData);

   profKey = "1";
   profData = "1,Accomplice to murder,arrigned,05-30-1994,";
   arrestProfile.addOrReplaceElementWithKey(profKey, profData);

   profKey = "2";
   profData = "2,fraud,arrested,02-15-1994,";
   arrestProfile.addOrReplaceElementWithKey(profKey, profData);

   profKey = "3";
   profData = "2,embezzlement,arrested,04-15-1994,";
   arrestProfile.addOrReplaceElementWithKey(profKey, profData);

   profKey = "4";
   profData = "3,premeditated murder,arraigned,05-30-1994,";
   arrestProfile.addOrReplaceElementWithKey(profKey, profData);

   return *this;
}

/*------------------------------------------------------------------
 * processResult
 *    The user controls when dResultBuffer should be processed.
 *-----------------------------------------------------------------*/
ISuspectClientMgr & ISuspectClientMgr :: processResult ()
{
   ISuspect           *suspect;
   ISuspectRecord     suspectRec;
   IAddress           address;
   unsigned short     recOffset, i;
   IString            buffer;

  IFUNCTRACE_DEVELOP();

  if (!dResultBuffer.isWhiteSpace())
  {
     ITRACE_DEVELOP("resultBuffer received.");
     IResultRecord resultRec(dResultBuffer);
     ITRACE_DEVELOP(resultRec.asDebugInfo());

     //clear the result list if it's not empty (i.e., if it was set in a previous invocation)
     if (dResultListWrapper->numberOfElements())
     {
        ITRACE_DEVELOP("had to empty the resultList");
        dResultListWrapper->removeAll();
     }

     if (resultRec.numResults() != 0)
     {
        recOffset = 1;
        bool noError = true;

        for (i=0 ; i < resultRec.numResults() && noError; i++)
        {
           suspect = new ISuspect;
           if (recOffset + suspectRec.size() - 1 <= resultRec.size() - 2)
           {
              buffer = resultRec.resultData().subString(recOffset,suspectRec.size());
              suspectRec = buffer;
              ITRACE_DEVELOP("Suspect record" + IString(i) + " ...");
              ITRACE_DEVELOP(suspectRec.asDebugInfo());

              suspect->setLastName(suspectRec.lastName().strip());
              suspect->setFirstName(suspectRec.firstName().strip());
              suspect->setInfo(suspectRec.description().strip());
              suspect->enableHasMole(suspectRec.hasMole());
              suspect->enableHasScar(suspectRec.hasScar());
              suspect->enableHasTattoo(suspectRec.hasTattoo());
              suspect->setBirthDate(suspectRec.birthDate().strip());
              suspect->setBookNumber(suspectRec.bookNumber());
              suspect->setMO(suspectRec.MO().strip());
              suspect->setMoleDesc(suspectRec.moleDescription().strip());
              suspect->setScarDesc(suspectRec.scarDescription().strip());
              suspect->setTattooDesc(suspectRec.tattooDescription().strip());
              suspect->setEyeColor(suspectRec.eyeColor());
              suspect->setHairColor(suspectRec.hairColor());
              suspect->setGender(suspectRec.gender());
              suspect->setHeight(suspectRec.height());
              suspect->setWeight(suspectRec.weight());
              suspect->setMugFront(suspectRec.mugFront());
              suspect->setMugLeft(suspectRec.mugLeft());
              suspect->setMugRight(suspectRec.mugRight());

              address.setStreet(suspectRec.street().strip());
              address.setCity(suspectRec.city().strip());
              address.setState(suspectRec.state().strip());
              address.setZip(suspectRec.zip().strip());
//            address.setCounty(suspectRec.county().strip());

              suspect->setAddress(new IAddress( address ));

              ITRACE_DEVELOP(suspect->asDebugInfo());
              addResult(suspect);              //adds suspect to dResultList
              recOffset += suspectRec.size();
           }
           else
           {
              ITRACE_DEVELOP("The capacity of the result record buffer has been exceeded.");
              noError = false;
           }
        }
     }

     notifyObservers(INotificationEvent(parsedResultId, *this, false));
     if (resultRec.numResults() == 1)
        notifyObservers(INotificationEvent(oneObjectFoundId, *this, false));
     else if (resultRec.numResults() == 0)
     {
        notifyObservers(INotificationEvent(noObjectsFoundId, *this, false));
        throw IException("No information exists for the specified suspect.");
     }
     else
        notifyObservers(INotificationEvent(manyObjectsFoundId, *this, false));

  }
   return *this;
}

/*------------------------------------------------------------------
 * addResult()
 *-----------------------------------------------------------------*/
ISuspectClientMgr & ISuspectClientMgr :: addResult
   (ISuspect * iSuspectWrapper)
{
   IFUNCTRACE_DEVELOP();
   ITRACE_DEVELOP("addResult(*)");
   ITRACE_DEVELOP(iSuspectWrapper->asDebugInfo());

   if (dResultListWrapper->isEmpty())
   {
      setResultWrapper(iSuspectWrapper);
   }

   dResultListWrapper->addAsLast(iSuspectWrapper);
   ITRACE_DEVELOP("added a suspect to the resultList");
   return *this;
}

/*------------------------------------------------------------------
 * addResult()
 *-----------------------------------------------------------------*/
ISuspectClientMgr & ISuspectClientMgr :: addResult
   (ISuspect & iSuspect)
{
   IFUNCTRACE_DEVELOP();
   ITRACE_DEVELOP("addResult(&)");

   if (dResultListWrapper->isEmpty())
   {
      setResultWrapper(&iSuspect);
   }

   dResultListWrapper->addAsLast(&iSuspect);
   ITRACE_DEVELOP("added a suspect to the resultList");
   return *this;
}

/*------------------------------------------------------------------
 * setResultWrapper()
 *-----------------------------------------------------------------*/
ISuspectClientMgr & ISuspectClientMgr ::
  setResultWrapper (ISuspect * iResultWrapper)
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
ISuspectClientMgr & ISuspectClientMgr ::
  setResultWrapper (const ISuspect & iResult)
{
  /*****************************************************************
   * Have to make a copy of the ISuspect object passed in since it's
   * identified as being a const.  That is, the compiler won't
   * allow dResultWrapper = &iResultWrapper, since it would allow
   * us, via dResultWrapper, to update the ISuspect object.
   *****************************************************************/
  return setResultWrapper(new ISuspect(iResult));
}

