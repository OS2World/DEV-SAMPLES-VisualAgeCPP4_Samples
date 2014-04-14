/******************************************************************************
* .FILE:        isuspect.cpp                                                  *
*                                                                             *
* .DESCRIPTION: Implementation for the class, ISuspect                        *
*                                                                             *
* .CLASSES:     ISuspect                                                      *
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
#include "isuspect.hpp"
#ifndef _IVBMAIN_
  #include <ivbmain.hpp>
#endif
#ifndef _IVBDEFS_
  #include <ivbdefs.h>
#endif
#include <inotifev.hpp>
#include <itrace.hpp>

/****************************************************************************
 * Static Member Data Initializations
 ****************************************************************************/
const unsigned short ISuspect :: defaultMugId = 7;
const IDynamicLinkLibrary ISuspect :: mugLib(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath());

INotificationId ISuspect::arrestListId = "ISuspect::arrestList";
INotificationId ISuspect::bookNumberId = "ISuspect::bookNumber";
INotificationId ISuspect::hasMoleId = "ISuspect::hasMole";
INotificationId ISuspect::hasScarId = "ISuspect::hasScar";
INotificationId ISuspect::hasTattooId = "ISuspect::hasTattoo";
INotificationId ISuspect::MOId = "ISuspect::mO";
INotificationId ISuspect::moleDescId = "ISuspect::moleDesc";
INotificationId ISuspect::mugFrontId = "ISuspect::mugFront";
INotificationId ISuspect::mugLeftId = "ISuspect::mugLeft";
INotificationId ISuspect::mugRightId = "ISuspect::mugRight";
INotificationId ISuspect::scarDescId = "ISuspect::scarDesc";
INotificationId ISuspect::tattooDescId = "ISuspect::tattooDesc";

/*------------------------------------------------------------------------------
| ISuspect::ISuspect                                                           |
|                                                                              |
| Standard constructor.                                                        |
------------------------------------------------------------------------------*/
ISuspect :: ISuspect() : IPerson (),
  iArrestList (new IVSequence <IArrest *> ()),
  iBookNumber (0),
  iHasMole (0),
  iHasScar (0),
  iHasTattoo (0),
  iMO (""),
  iMoleDesc (""),
  iMugFront (defaultMugId),
  iMugLeft (defaultMugId),
  iMugRight (defaultMugId),
  iScarDesc (""),
  iTattooDesc ("")
{
  enableNotification();
  iArrestList->enableNotification();
}

/*------------------------------------------------------------------------------
| ISuspect::ISuspect                                                           |
|                                                                              |
| Standard copy constructor.                                                   |
------------------------------------------------------------------------------*/
ISuspect :: ISuspect (const ISuspect & partCopy)
  : IPerson (partCopy),
  iArrestList (new IVSequence <IArrest *> (*partCopy.arrestList())),
  iBookNumber (partCopy.bookNumber()),
  iHasMole (partCopy.hasMole()),
  iHasScar (partCopy.hasScar()),
  iHasTattoo (partCopy.hasTattoo()),
  iMO (partCopy.MO()),
  iMoleDesc (partCopy.moleDesc()),
  iMugFront (partCopy.mugFront()),
  iMugLeft (partCopy.mugLeft()),
  iMugRight (partCopy.mugRight()),
  iScarDesc (partCopy.scarDesc()),
  iTattooDesc (partCopy.tattooDesc())
{
  enableNotification ();
  iArrestList->enableNotification();
}

/*------------------------------------------------------------------------------
| ISuspect::~ISuspect                                                          |
|                                                                              |
| Empty destructor here for page tuning.                                       |
------------------------------------------------------------------------------*/
ISuspect :: ~ISuspect()
{
  ISequence<IArrest *> tempList;
  IArrest *            arrest;

  if (iArrestList)
  {
     IVSequence<IArrest*>::Cursor cursor(*iArrestList);
     forCursor( cursor )
       tempList.addAsFirst( iArrestList->elementAt( cursor ) );

     iArrestList->removeAll( );

     ISequence<IArrest*>::Cursor tempCursor( tempList );
     forCursor( cursor )
     {
       arrest = tempList.elementAt ( tempCursor );
       delete arrest;
     }
     tempList.removeAll( );

     delete iArrestList;
  }
}

/*------------------------------------------------------------------------------
 | ISuspect::ISuspect
 |
 | Standard operator=
 -----------------------------------------------------------------------------*/
ISuspect & ISuspect :: operator= (const ISuspect & aSuspect)
{
  if (this == &aSuspect)
    return *this;

  IPerson::operator=(aSuspect);
  setArrestList (new IVSequence <IArrest *> (*aSuspect.arrestList()));
  setBookNumber (aSuspect.bookNumber());
  enableHasMole (aSuspect.hasMole());
  enableHasScar (aSuspect.hasScar());
  enableHasTattoo (aSuspect.hasTattoo());
  setMO (aSuspect.MO());
  setMoleDesc (aSuspect.moleDesc());
  setMugFront (aSuspect.mugFront());
  setMugLeft (aSuspect.mugLeft());
  setMugRight (aSuspect.mugRight());
  setScarDesc (aSuspect.scarDesc());
  setTattooDesc (aSuspect.tattooDesc());

  return *this;
}

/*------------------------------------------------------------------------------
| ISuspect::asString                                                           |
|                                                                              |
| Perform asString.                                                            |
| NOTE: This also identifies what data should be displayed for an              |
|       ISuspect element of a list (that maps to the 'items' attribute         |
|       of a list box).                                                        |
------------------------------------------------------------------------------*/
IString ISuspect :: asString () const
{
  return (IString(bookNumber()));
}

/*------------------------------------------------------------------------------
| ISuspect::asDebugInfo                                                        |
|                                                                              |
| Generate a string that identifies for debugging purposes what data           |
| an ISuspect instance contains.                                               |
|                                                                              |
| NOTE: attributes not included:  iMO, iHasMoleDesc, iHasScarDesc, and         |
|       iHasTattooDesc.                                                        |
------------------------------------------------------------------------------*/
IString ISuspect :: asDebugInfo () const
{
  IString debugInfo("bookNum=" + IString(iBookNumber) + ",");
  debugInfo += IPerson::asDebugInfo();
  debugInfo += "numArrest=" + IString(iArrestList->numberOfElements()) + ".";
  debugInfo += "hasMole=" + IString(iHasMole) + ",";
  debugInfo += "hasScar=" + IString(iHasScar) + ",";
  debugInfo += "hasTattoo=" + IString(iHasTattoo) + ",";
  debugInfo += "mugLeft=" + IString(iMugLeft) + ",";
  debugInfo += "mugFront=" + IString(iMugFront) + ",";
  debugInfo += "mugRight=" + IString(iMugRight) + ",";

  return debugInfo;
}


/*------------------ Attribute Get/Set Member Functions ------------------------
 -----------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------
 | arrestList
 -----------------------------------------------------------------------------*/
IVSequence<IArrest *> * ISuspect::arrestList() const
{
  return iArrestList;
}

ISuspect & ISuspect::setArrestList(IVSequence<IArrest *> * aArrestList)
{
  if (iArrestList != aArrestList)
  {
    iArrestList->removeAll();
    iArrestList->addAllFrom(*aArrestList);
    notifyObservers(INotificationEvent(ISuspect::arrestListId, *this));
  } // endif
  return *this;
}

/*------------------------------------------------------------------------------
 | bookNumber
 -----------------------------------------------------------------------------*/
IString ISuspect::bookNumberAsString() const
{
  return IString(iBookNumber);
}

ISuspect & ISuspect::setBookNumberAsString(const IString & aBookNumber)
{
  setBookNumber(aBookNumber.asUnsigned());
  return *this;
}

unsigned long ISuspect::bookNumber() const
{
  return iBookNumber;
}

ISuspect & ISuspect::setBookNumber(const unsigned long aBookNumber)
{
  if (iBookNumber != aBookNumber)
  {
    iBookNumber = aBookNumber;
    notifyObservers(INotificationEvent(ISuspect::bookNumberId, *this));
  } // endif
  return *this;
}

/*------------------------------------------------------------------------------
 | hasMole
 -----------------------------------------------------------------------------*/
bool ISuspect::hasMole() const
{
  return iHasMole;
}

ISuspect & ISuspect::enableHasMole(bool enable)
{
  if (iHasMole != enable)
  {
    iHasMole = enable;
    notifyObservers(INotificationEvent(ISuspect::hasMoleId, *this));
  } // endif
  return *this;
}

/*------------------------------------------------------------------------------
 | hasScar
 -----------------------------------------------------------------------------*/
bool ISuspect::hasScar() const
{
  return iHasScar;
}

ISuspect & ISuspect::enableHasScar(bool enable)
{
  if (iHasScar != enable)
  {
    iHasScar = enable;
    notifyObservers(INotificationEvent(ISuspect::hasScarId, *this));
  } // endif
  return *this;
}

/*------------------------------------------------------------------------------
 | hasTattoo
 -----------------------------------------------------------------------------*/
bool ISuspect::hasTattoo() const
{
  return iHasTattoo;
}

ISuspect & ISuspect::enableHasTattoo(bool enable)
{
  if (iHasTattoo != enable)
  {
    iHasTattoo = enable;
    notifyObservers(INotificationEvent(ISuspect::hasTattooId, *this));
  } // endif
  return *this;
}

/*------------------------------------------------------------------------------
 | MO
 -----------------------------------------------------------------------------*/
IString ISuspect::MO() const
{
  return iMO;
}

ISuspect & ISuspect::setMO(const IString & aMO)
{
  if (iMO != aMO)
  {
    iMO = aMO;
    notifyObservers(INotificationEvent(ISuspect::MOId, *this));
  } // endif
  return *this;
}

/*------------------------------------------------------------------------------
 | moleDesc
 -----------------------------------------------------------------------------*/
IString ISuspect::moleDesc() const
{
  return iMoleDesc;
}

ISuspect & ISuspect::setMoleDesc(const IString & aMoleDesc)
{
  if (iMoleDesc != aMoleDesc)
  {
    iMoleDesc = aMoleDesc;
    notifyObservers(INotificationEvent(ISuspect::moleDescId, *this));
  } // endif
  return *this;
}

/*------------------------------------------------------------------------------
 | mugFront
 -----------------------------------------------------------------------------*/
unsigned short ISuspect::mugFront() const
{
  return iMugFront;
}

ISuspect & ISuspect::setMugFront(const unsigned short aMugFront)
{
  if (iMugFront != aMugFront)
  {
    iMugFront = aMugFront;
    notifyObservers(INotificationEvent(ISuspect::mugFrontId, *this));
  } // endif
  return *this;
}

IBitmapHandle ISuspect::mugFrontAsHandle() const
{
  IBitmapHandle aHandle;

  aHandle = mugLib.tryToLoadBitmap(iMugFront);
  if (aHandle == 0)   //couldn't load bitmap, use default bitmap
  {
     ITRACE_DEVELOP("Couldn't load the bitmap " +
                    IString(iMugFront) + " from the DLL rapres.");
     aHandle = mugLib.loadBitmap(defaultMugId);   //exception occurs, if fails
  }

  return aHandle;
}

/*------------------------------------------------------------------------------
 | mugLeft
 -----------------------------------------------------------------------------*/
unsigned short ISuspect::mugLeft() const
{
  return iMugLeft;
}

ISuspect & ISuspect::setMugLeft(const unsigned short aMugLeft)
{
  if (iMugLeft != aMugLeft)
  {
    iMugLeft = aMugLeft;
    notifyObservers(INotificationEvent(ISuspect::mugLeftId, *this));
  } // endif
  return *this;
}

IBitmapHandle ISuspect::mugLeftAsHandle() const
{
  IBitmapHandle aHandle;

  aHandle = mugLib.tryToLoadBitmap(iMugLeft);
  if (aHandle == 0)   //couldn't load bitmap, use default bitmap
  {
     ITRACE_DEVELOP("Couldn't load the bitmap " +
                    IString(iMugLeft) + " from the DLL rapres.");
     aHandle = mugLib.loadBitmap(defaultMugId);   //exception occurs, if fails
  }

  return aHandle;
}

/*------------------------------------------------------------------------------
 | mugRight
 -----------------------------------------------------------------------------*/
unsigned short ISuspect::mugRight() const
{
  return iMugRight;
}

ISuspect & ISuspect::setMugRight(const unsigned short aMugRight)
{
  if (iMugRight != aMugRight)
  {
    iMugRight = aMugRight;
    notifyObservers(INotificationEvent(ISuspect::mugRightId, *this));
  } // endif
  return *this;
}

IBitmapHandle ISuspect::mugRightAsHandle() const
{
  IBitmapHandle aHandle;

  aHandle = mugLib.tryToLoadBitmap(iMugRight);
  if (aHandle == 0)   //couldn't load bitmap, use default bitmap
  {
     ITRACE_DEVELOP("Couldn't load the bitmap " +
                    IString(iMugRight) + " from the DLL rapres.");
     aHandle = mugLib.loadBitmap(defaultMugId);   //exception occurs, if fails
  }

  return aHandle;
}

/*------------------------------------------------------------------------------
 | scarDesc
 -----------------------------------------------------------------------------*/
IString ISuspect::scarDesc() const
{
  return iScarDesc;
}

ISuspect & ISuspect::setScarDesc(const IString & aScarDesc)
{
  if (iScarDesc != aScarDesc)
  {
    iScarDesc = aScarDesc;
    notifyObservers(INotificationEvent(ISuspect::scarDescId, *this));
  } // endif
  return *this;
}

/*------------------------------------------------------------------------------
 | tattooDesc
 -----------------------------------------------------------------------------*/
IString ISuspect::tattooDesc() const
{
  return iTattooDesc;
}

ISuspect & ISuspect::setTattooDesc(const IString & aTattooDesc)
{
  if (iTattooDesc != aTattooDesc)
  {
    iTattooDesc = aTattooDesc;
    notifyObservers(INotificationEvent(ISuspect::tattooDescId, *this));
  } // endif
  return *this;
}

/*------------------------------------------------------------------------------
 | ISuspect::operator == (const ISuspect & value)
 -----------------------------------------------------------------------------*/
bool ISuspect::operator == (const ISuspect & value) const
{
  if (bookNumber() != value.bookNumber())
    return false;
  return true;
}

/*------------------------------------------------------------------------------
 | ISuspect::operator != (const ISuspect & value)
 -----------------------------------------------------------------------------*/
bool ISuspect::operator != (const ISuspect & value) const
{
  if (bookNumber() != value.bookNumber())
    return true;
  return false;
}

/*------------------------------------------------------------------------------
 | ISuspect::operator == (const ISuspect * value)
 -----------------------------------------------------------------------------*/
bool ISuspect::operator == (const ISuspect * value) const
{
  if (bookNumber() != value->bookNumber())
    return false;
  return true;
}

/*------------------------------------------------------------------------------
 | ISuspect::operator != (const ISuspect * value)
 -----------------------------------------------------------------------------*/
bool ISuspect::operator != (const ISuspect * value) const
{
  if (bookNumber() != value->bookNumber())
    return true;
  return false;
}

