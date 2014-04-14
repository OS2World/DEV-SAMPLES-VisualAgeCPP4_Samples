#ifndef _IPERSON_
#define _IPERSON_
/******************************************************************************
* .FILE:        iperson.hpp                                                   *
*                                                                             *
* .DESCRIPTION: Header file for the class IPerson                             *
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
#include "ivbsamps.h"
#include <istdntfy.hpp>
#include <istring.hpp>
#include <ivseq.h>
#include <iadd.hpp>
#include "ialias.hpp"

/*----------------------------------------------------------------------------*/
/* Align classes on four byte boundary.                                       */
/*----------------------------------------------------------------------------*/
#pragma pack(4)

//**************************************************************************
// Class:   IPerson
//
// Purpose:
//
//**************************************************************************
class IVBSAMP_IMPORT IPerson : public IStandardNotifier {

/*--------------------------- PUBLIC -----------------------------------------*/
public:

/*------------------------- Constructors/Destructor ----------------------------
------------------------------------------------------------------------------*/
  IPerson ();
  IPerson (const IPerson & partCopy);
virtual
  ~IPerson ();

/*---------------------  ENUMERATED TYPES  ------------------------
 *-----------------------------------------------------------------*/
enum IEyeColor  {blue_eyes,                 //0
                 brown_eyes,                //1
                 green_eyes,                //2
                 hazel_eyes};               //3
enum IGender    {female,                    //0
                 male};                     //1
enum IHairColor {no_hair,                   //0
                 black_hair,                //1
                 blonde_hair,               //2
                 brown_hair,                //3
                 grey_hair,                 //4
                 red_hair};                 //5

/*-------------------------------- Operators -----------------------------------
------------------------------------------------------------------------------*/
  IPerson & operator= (const IPerson & aPerson);

  bool
    operator == (const IPerson & value) const,
    operator != (const IPerson & value) const,
    operator == (const IPerson * value) const,
    operator != (const IPerson * value) const;

  virtual IString asString () const;
  virtual IString asDebugInfo () const;


/*-------------------------------- Attributes ----------------------------------
 | The following are attributes for this class:
 |    address                    - address of the person
 |    aliasList                  - list of aliases/nicknames the person is known by
 |    birthDate                  - the date the person was born
 |    eyeColor                   - the color of the person's eyes (as an enum value)
 |    eyeColorAsString           - the color of the person's eyes (as an IString)
 |    firstName                  - the person's first name
 |    gender                     - the gender/sex of the person
 |    hairColor                  - the color of the person's hair (as an enum value)
 |    hairColorAsString          - the color of the person's hair (as an IString)
 |    height                     - the person's height (in inches)
 |    heightAsString             - the person's height (in inches) (as an IString)
 |    info                       - a description of the person
 |    isMale                     - the gender/sex of the person (as a bool)
 |    lastName                   - the person's last name
 |    weight                     - the person's weight (in pounds)
 |    weightAsString             - the person's weight (in pounds) (as an IString)
 -----------------------------------------------------------------------------*/
  virtual IAddress * address() const;
  virtual IPerson & setAddress(IAddress * aAddress);

  virtual IVSequence<IAlias *> * aliasList() const;
  virtual IPerson & setAliasList(IVSequence<IAlias *> * aAliasList);

  virtual IString birthDate() const;
  virtual IPerson & setBirthDate(const IString & aBirthDate);

  virtual IString eyeColorAsString() const;
  virtual IPerson & setEyeColorAsString(const IString & aEyeColor);

  virtual unsigned short eyeColor() const;
  virtual IPerson & setEyeColor(const unsigned short aEyeColor);

  virtual IString firstName() const;
  virtual IPerson & setFirstName(const IString & aFirstName);

  virtual unsigned short gender() const;
  virtual IPerson & setGender(const unsigned short aGender);

  virtual IString hairColorAsString() const;
  virtual IPerson & setHairColorAsString(const IString & aHairColor);

  virtual unsigned short hairColor() const;
  virtual IPerson & setHairColor(const unsigned short aHairColor);

  virtual IString heightAsString() const;
  virtual IPerson & setHeightAsString(const IString & aHeight);

  virtual unsigned short height() const;
  virtual IPerson & setHeight(const unsigned short aHeight);

  virtual IString info() const;
  virtual IPerson & setInfo(const IString & aInfo);

  virtual bool isMale() const;
  virtual IPerson & enableIsMale(bool aMale = true);

  virtual IString lastName() const;
  virtual IPerson & setLastName(const IString & aLastName);

  virtual IString weightAsString() const;
  virtual IPerson & setWeightAsString(const IString & aWeight);

  virtual unsigned short weight() const;
  virtual IPerson & setWeight(const unsigned short aWeight);


/*----------------------- Notification Event Ids -------------------------------
------------------------------------------------------------------------------*/
  static INotificationId addressId;
  static INotificationId aliasListId;
  static INotificationId birthDateId;
  static INotificationId eyeColorId;
  static INotificationId firstNameId;
  static INotificationId genderId;
  static INotificationId hairColorId;
  static INotificationId heightId;
  static INotificationId infoId;
  static INotificationId lastNameId;
  static INotificationId weightId;


/*--------------------------- PRIVATE ----------------------------------------*/
private:
  unsigned short iEyeColor;
  unsigned short iGender;
  unsigned short iHairColor;
  unsigned short iHeight;
  unsigned short iWeight;
  IString iBirthDate;
  IString iFirstName;
  IString iLastName;
  IString iInfo;
  IVSequence<IAlias *> *iAliasList;
  IAddress *iAddress;

};   //IPerson

/*----------------------------------------------------------------------------*/
/* Resume compiler default packing.                                           */
/*----------------------------------------------------------------------------*/
#pragma pack()

#endif

