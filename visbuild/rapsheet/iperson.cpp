/******************************************************************************
* .FILE:        iperson.cpp                                                   *
*                                                                             *
* .DESCRIPTION: Implementation for the class, IPerson                         *
*                                                                             *
* .CLASSES:     IPerson                                                       *
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
#include "iperson.hpp"
#ifndef _IVBMAIN_
  #include <ivbmain.hpp>
#endif
#ifndef _IVBDEFS_
  #include <ivbdefs.h>
#endif
#include <inotifev.hpp>
#include <ireslib.hpp>
#include "rap.h"

INotificationId IPerson::addressId = "IPerson::address";
INotificationId IPerson::aliasListId = "IPerson::aliasList";
INotificationId IPerson::birthDateId = "IPerson::birthDate";
INotificationId IPerson::eyeColorId = "IPerson::eyeColor";
INotificationId IPerson::firstNameId = "IPerson::firstName";
INotificationId IPerson::genderId = "IPerson::gender";
INotificationId IPerson::hairColorId = "IPerson::hairColor";
INotificationId IPerson::heightId = "IPerson::height";
INotificationId IPerson::infoId = "IPerson::info";
INotificationId IPerson::lastNameId = "IPerson::lastName";
INotificationId IPerson::weightId = "IPerson::weight";

/*------------------------------------------------------------------------------
 | IPerson::IPerson
 |
 | Standard constructor.
 -----------------------------------------------------------------------------*/
IPerson :: IPerson() : IStandardNotifier (),
  iAddress (new IAddress()),
  iAliasList (new IVSequence<IAlias *> ()),
  iBirthDate (""),
  iEyeColor (0),
  iFirstName ("John"),
  iGender (0),
  iHairColor (0),
  iHeight (70),
  iInfo (""),
  iLastName ("Smith"),
  iWeight (150)
{
  enableNotification();
  iAddress->enableNotification();
  iAliasList->enableNotification();
}

/*------------------------------------------------------------------------------
 | IPerson::IPerson
 |
 | Standard copy constructor.
 -----------------------------------------------------------------------------*/
IPerson :: IPerson (const IPerson& partCopy)
  : IStandardNotifier (partCopy),
  iAddress (new IAddress (*partCopy.address())),
  iAliasList (new IVSequence <IAlias *> (*partCopy.aliasList())),
  iBirthDate (partCopy.birthDate()),
  iEyeColor (partCopy.eyeColor()),
  iFirstName (partCopy.firstName()),
  iGender (partCopy.gender()),
  iHairColor (partCopy.hairColor()),
  iHeight (partCopy.height()),
  iInfo (partCopy.info()),
  iLastName (partCopy.lastName()),
  iWeight (partCopy.weight())
{
  enableNotification();
  iAddress->enableNotification();
  iAliasList->enableNotification();
}

/*------------------------------------------------------------------------------
 | IPerson::~IPerson
 |
 | Empty destructor here for page tuning.
 -----------------------------------------------------------------------------*/
IPerson :: ~IPerson()
{
  ISequence<IAlias *> tempList;
  IAlias *            alias;

  if (iAddress)
    delete iAddress;

  if (iAliasList)
  {
     IVSequence <IAlias*>::Cursor cursor(*iAliasList);
     forCursor( cursor )
       tempList.addAsFirst( iAliasList->elementAt( cursor ) );

     iAliasList->removeAll( );

     ISequence <IAlias*>::Cursor tempCursor( tempList );
     forCursor( cursor )
     {
       alias = tempList.elementAt ( tempCursor );
       delete alias;
     }
     tempList.removeAll( );

     delete iAliasList;
  }
}

/*------------------------------------------------------------------------------
 | IPerson::IPerson
 |
 | Standard operator=
 -----------------------------------------------------------------------------*/
IPerson & IPerson :: operator= (const IPerson & aPerson)
{
  if (this == &aPerson)
    return *this;

  IStandardNotifier::operator=(aPerson);
  setAddress(new IAddress (*aPerson.address()));
  setAliasList(new IVSequence <IAlias*> (*aPerson.aliasList()));
  setBirthDate(aPerson.birthDate());
  setEyeColor(aPerson.eyeColor());
  setFirstName(aPerson.firstName());
  setGender(aPerson.gender());
  setHairColor(aPerson.hairColor());
  setHeight(aPerson.height());
  setInfo(aPerson.info());
  setLastName(aPerson.lastName());
  setWeight(aPerson.weight());

  return *this;
}

/*------------------------------------------------------------------------------
 | IPerson::asString                                                           |
 |                                                                             |
 | Perform asString.                                                           |
 | NOTE: This also identifies what data should be displayed for an             |
 |       ISuspect element of a list (that maps to the 'items' attribute        |
 |       of a list box).                                                       |
 -----------------------------------------------------------------------------*/
IString IPerson :: asString () const
{
  return (lastName() + ", " + firstName());
}

/*------------------------------------------------------------------------------
| IPerson::asDebugInfo                                                         |
|                                                                              |
| Generate a string that identifies for debugging purposes what data           |
| an ISuspect instance contains.                                               |
|                                                                              |
| NOTE: attributes not included:  iInfo.                                       |
| NOTE: to see what some of the values map to, see the enumerations that       |
|       are defined in IPerson.hpp.                                            |
------------------------------------------------------------------------------*/
IString IPerson :: asDebugInfo () const
{
  IString debugInfo("lName=" + iLastName + ",");
  debugInfo += "fName=" + iFirstName + ",";
//debugInfo += iAddress->asDebugInfo();
  debugInfo += "numAlias=" + IString(iAliasList->numberOfElements()) + ",";
  debugInfo += "bdate=" + IString(iBirthDate) + ",";
  debugInfo += "eyeColor=" + IString(iEyeColor) + ",";
  debugInfo += "gender=" + IString(iGender) + ",";
  debugInfo += "hairColor=" + IString(iHairColor) + ",";
  debugInfo += "height=" + IString(iHeight) + ",";
  debugInfo += "weight=" + IString(iWeight) + ",";

  return debugInfo;
}


/*------------------ Attribute Get/Set Member Functions ------------------------
 -----------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------
 | address
 -----------------------------------------------------------------------------*/
IAddress * IPerson::address() const
{
  return iAddress;
}

IPerson & IPerson::setAddress(IAddress * aAddress)
{
  if (iAddress != aAddress)
  {
    if (iAddress)
      delete iAddress;
    iAddress = new IAddress(*aAddress);
    notifyObservers(INotificationEvent(IPerson::addressId, *this));
  } // endif
  return *this;
}

/*------------------------------------------------------------------------------
 | aliasList
 -----------------------------------------------------------------------------*/
IVSequence<IAlias *> * IPerson::aliasList() const
{
  return iAliasList;
}

IPerson & IPerson::setAliasList(IVSequence<IAlias *> * aAliasList)
{
  if (iAliasList != aAliasList)
  {
    iAliasList->removeAll();
    iAliasList->addAllFrom(*aAliasList);
//  notifyObservers(INotificationEvent(IPerson::aliasListId, *this));
  } // endif
  return *this;
}

/*------------------------------------------------------------------------------
 | birthDate
 -----------------------------------------------------------------------------*/
IString IPerson::birthDate() const
{
  return iBirthDate;
}

IPerson & IPerson::setBirthDate(const IString & aBirthDate)
{
  if (iBirthDate != aBirthDate)
  {
    iBirthDate = aBirthDate;
    notifyObservers(INotificationEvent(IPerson::birthDateId, *this));
  } // endif
  return *this;
}

/*------------------------------------------------------------------------------
 | eyeColorAsString, eyeColor
 -----------------------------------------------------------------------------*/
IString IPerson::eyeColorAsString() const
{
  IString eyeColor;
  switch (iEyeColor)
  {
     case blue_eyes:
        eyeColor = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(BLUE_EYES_STR);
        break;
     case brown_eyes:
        eyeColor = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(BROWN_EYES_STR);
        break;
     case green_eyes:
        eyeColor = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(GREEN_EYES_STR);
        break;
     case hazel_eyes:
        eyeColor = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(HAZEL_EYES_STR);
        break;
  }
  return eyeColor;
}

IPerson & IPerson::setEyeColorAsString(const IString & aEyeColor)
{
  if (aEyeColor == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(BLUE_EYES_STR))
     setEyeColor(blue_eyes);
  else if (aEyeColor == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(BROWN_EYES_STR))
     setEyeColor(brown_eyes);
  else if (aEyeColor == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(GREEN_EYES_STR))
     setEyeColor(green_eyes);
  else if (aEyeColor == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(HAZEL_EYES_STR))
     setEyeColor(hazel_eyes);
  return *this;
}

unsigned short IPerson::eyeColor() const
{
  return iEyeColor;
}

IPerson & IPerson::setEyeColor(const unsigned short aEyeColor)
{
  if (iEyeColor != aEyeColor)
  {
    iEyeColor = aEyeColor;
    notifyObservers(INotificationEvent(IPerson::eyeColorId, *this));
  } // endif
  return *this;
}

/*------------------------------------------------------------------------------
 | firstName
 -----------------------------------------------------------------------------*/
IString IPerson::firstName() const
{
  return iFirstName;
}

IPerson & IPerson::setFirstName(const IString & aFirstName)
{
  if (iFirstName != aFirstName)
  {
    iFirstName = aFirstName;
    notifyObservers(INotificationEvent(IPerson::firstNameId, *this));
  } // endif
  return *this;
}

/*------------------------------------------------------------------------------
 | gender/isMale
 -----------------------------------------------------------------------------*/
unsigned short IPerson::gender() const
{
  return iGender;
}

IPerson & IPerson::setGender(const unsigned short aGender)
{
  if (iGender != aGender)
  {
    iGender = aGender;
    notifyObservers(INotificationEvent(IPerson::genderId, *this));
  } // endif
  return *this;
}

bool IPerson::isMale() const
{
  bool gender;
  if (iGender == male)
    gender = true;
  else
    gender = false;
  return gender;
}

IPerson & IPerson::enableIsMale(bool aGender)
{
  if (aGender)
    setGender(male);
  else
    setGender(female);
  return *this;
}

/*------------------------------------------------------------------------------
 | hairColorAsString, hairColor
 -----------------------------------------------------------------------------*/
IString IPerson::hairColorAsString() const
{
  IString hairColor;
  switch (iHairColor)
  {
     case no_hair:
        hairColor = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(NO_HAIR_STR);
        break;
     case black_hair:
        hairColor = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(BLACK_HAIR_STR);
        break;
     case blonde_hair:
        hairColor = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(BLONDE_HAIR_STR);
        break;
     case brown_hair:
        hairColor = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(BROWN_HAIR_STR);
        break;
     case grey_hair:
        hairColor = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(GREY_HAIR_STR);
        break;
     case red_hair:
        hairColor = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(RED_HAIR_STR);
        break;
  }
  return hairColor;
}

IPerson & IPerson::setHairColorAsString(const IString & aHairColor)
{
  if (aHairColor == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(NO_HAIR_STR))
     setHairColor(no_hair);
  else if (aHairColor == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(BLACK_HAIR_STR))
     setHairColor(black_hair);
  else if (aHairColor == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(BLONDE_HAIR_STR))
     setHairColor(blonde_hair);
  else if (aHairColor == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(BROWN_HAIR_STR))
     setHairColor(brown_hair);
  else if (aHairColor == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(GREY_HAIR_STR))
     setHairColor(grey_hair);
  else if (aHairColor == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(RED_HAIR_STR))
     setHairColor(red_hair);
  return *this;
}

unsigned short IPerson::hairColor() const
{
  return iHairColor;
}

IPerson & IPerson::setHairColor(const unsigned short aHairColor)
{
  if (iHairColor != aHairColor)
  {
    iHairColor = aHairColor;
    notifyObservers(INotificationEvent(IPerson::hairColorId, *this));
  } // endif
  return *this;
}

/*------------------------------------------------------------------------------
 | heightAsString, height
 -----------------------------------------------------------------------------*/
IString IPerson::heightAsString() const
{
  return IString(iHeight);
}

IPerson & IPerson::setHeightAsString(const IString & aHeight)
{
  setHeight(aHeight.asUnsigned());
  return *this;
}

unsigned short IPerson::height() const
{
  return iHeight;
}

IPerson & IPerson::setHeight(const unsigned short aHeight)
{
  if (iHeight != aHeight)
  {
    iHeight = aHeight;
    notifyObservers(INotificationEvent(IPerson::heightId, *this));
  } // endif
  return *this;
}

/*------------------------------------------------------------------------------
 | info
 -----------------------------------------------------------------------------*/
IString IPerson::info() const
{
  return iInfo;
}

IPerson & IPerson::setInfo(const IString & aInfo)
{
  if (iInfo != aInfo)
  {
    iInfo = aInfo;
    notifyObservers(INotificationEvent(IPerson::infoId, *this));
  } // endif
  return *this;
}

/*------------------------------------------------------------------------------
 | lastName
 -----------------------------------------------------------------------------*/
IString IPerson::lastName() const
{
  return iLastName;
}

IPerson & IPerson::setLastName(const IString & aLastName)
{
  if (iLastName != aLastName)
  {
    iLastName = aLastName;
    notifyObservers(INotificationEvent(IPerson::lastNameId, *this));
  } // endif
  return *this;
}

/*------------------------------------------------------------------------------
 | weightAsString, weight
 -----------------------------------------------------------------------------*/
IString IPerson::weightAsString() const
{
  return IString(iWeight);
}

IPerson & IPerson::setWeightAsString(const IString & aWeight)
{
  setHeight(aWeight.asUnsigned());
  return *this;
}

unsigned short IPerson::weight() const
{
  return iWeight;
}

IPerson & IPerson::setWeight(const unsigned short aWeight)
{
  if (iWeight != aWeight)
  {
    iWeight = aWeight;
    notifyObservers(INotificationEvent(IPerson::weightId, *this));
  } // endif
  return *this;
}

/*------------------------------------------------------------------------------
 | IPerson::operator == (const IPerson & value)
 -----------------------------------------------------------------------------*/
bool IPerson::operator == (const IPerson & value) const
{
  if (lastName() != value.lastName())
    return false;
  if (firstName() != value.firstName())
    return false;
  if (address() != value.address())
    return false;
  return true;
}

/*------------------------------------------------------------------------------
 | IPerson::operator != (const IPerson & value)
 -----------------------------------------------------------------------------*/
bool IPerson::operator != (const IPerson & value) const
{
  if (lastName() != value.lastName())
    return true;
  if (firstName() != value.firstName())
    return true;
  if (address() != value.address())
    return true;
  return false;
}

/*------------------------------------------------------------------------------
 | IPerson::operator == (const IPerson * value)
 -----------------------------------------------------------------------------*/
bool IPerson::operator == (const IPerson * value) const
{
  if (lastName() != value->lastName())
    return false;
  if (firstName() != value->firstName())
    return false;
  if (address() != value->address())
    return false;
  return true;
}

/*------------------------------------------------------------------------------
 | IPerson::operator != (const IPerson * value)
 -----------------------------------------------------------------------------*/
bool IPerson::operator != (const IPerson * value) const
{
  if (lastName() != value->lastName())
    return true;
  if (firstName() != value->firstName())
    return true;
  if (address() != value->address())
    return true;
  return false;
}

