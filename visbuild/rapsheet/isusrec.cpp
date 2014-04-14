/******************************************************************************
* .FILE:        isusrec.cpp                                                   *
*                                                                             *
* .DESCRIPTION: Implementation for the class, ISuspectRecord                  *
*                                                                             *
* .CLASSES:     ISuspectRecord                                                *
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
#include "isusrec.hpp"     // ISuspectRecord header file
#include <istring.hpp>
#include "rap.h"


//******************************************************************
// Manager Member Functions (constructors/destructor)
//******************************************************************


//******************************************************************************
//  Default initialization of the record data IString is okay.
//  Call IRecord's (superclass') constructor
//******************************************************************************
ISuspectRecord :: ISuspectRecord() : IRecord(), dMySize(sizeof(SUSPECT_STRUCT))
{
  dParentSize = size();
  setSize( dParentSize + dMySize );            // pad with '\x00'
}


//******************************************************************************
// Copy the passed in data string via IRecord's constructor
//******************************************************************************
ISuspectRecord :: ISuspectRecord ( const IString & stringData ) :
                  IRecord (), dMySize(sizeof(SUSPECT_STRUCT))
{
  dParentSize = size();
  setSize ( dParentSize + dMySize );           //truncate or pad as appropriate
  *this = stringData.subString(1, size());
}


//******************************************************************************
// Copy the passed in record data via IRecord's constructor
//******************************************************************************
ISuspectRecord :: ISuspectRecord ( const ISuspectRecord & aRecord ) :
                  IRecord (), dMySize(sizeof(SUSPECT_STRUCT))
{
  dParentSize = size();
  *this = aRecord;

  dParentSize = size();
  *this = aRecord;

  //
  //NOTE:  this record would have gotten set with the correct size
  //       if had called the IRecord (aRecord) constructor, but
  //       need to determine what dParentSize is (the assignment
  //       operators need this info).
  //
}


//******************************************************************************
// The implementation IString is automatically deleted.             (destructor)
//******************************************************************************
ISuspectRecord :: ~ISuspectRecord()
{
  ;
}

/*------------------------------------------------------------------------------
| ISuspectRecord::asDebugInfo                                                  |
|                                                                              |
| Generate a string that identifies for debugging purposes what data           |
| an ISuspectRecord instance contains.                                         |
|                                                                              |
------------------------------------------------------------------------------*/
IString ISuspectRecord :: asDebugInfo () const
{
  IString debugInfo("size=" + IString(dMySize) + ",");
  debugInfo += "bookNum=" + IString(bookNumber()) + ",";
  debugInfo += "lName=" + lastName() + ",";
  debugInfo += "fName=" + firstName() + ",";
  debugInfo += "eyeColor=" + IString(eyeColor()) + ",";
  debugInfo += "gender=" + IString(gender()) + ",";
  debugInfo += "hairColor=" + IString(hairColor()) + ",";
  debugInfo += "height=" + IString(height()) + ",";
  debugInfo += "weight=" + IString(weight()) + ",";
  debugInfo += "mugLeft=" + IString(mugLeft()) + ",";
  debugInfo += "mugFront=" + IString(mugFront()) + ",";
  debugInfo += "mugRight=" + IString(mugRight()) + ",";
  debugInfo += "hasMole=" + IString(hasMole()) + ",";
  debugInfo += "hasScar=" + IString(hasScar()) + ",";
  debugInfo += "hasTattoo=" + IString(hasTattoo()) + ",";
  debugInfo += "bdate=" + birthDate() + ",";
  debugInfo += "street=" + street() + ",";
  debugInfo += "city=" + city() + ",";
//debugInfo += "county=" + county() + ",";
  debugInfo += "state=" + state() + ",";
  debugInfo += "zip=" + zip() + ".";

  return debugInfo;
}

/*********************************************************************************
 * Access Member Functions
 *********************************************************************************/

//**************************
// suspect last name
//**************************
IString ISuspectRecord :: lastName () const
{
  IString buffer;
  return field(buffer, offsetof(SUSPECT_STRUCT, lastName)+1, LAST_NAME_LEN);   //pad with NULLs
}

ISuspectRecord & ISuspectRecord :: setLastName (const IString & aSuspectLastName)
{
  setField(aSuspectLastName, offsetof(SUSPECT_STRUCT, lastName)+1, LAST_NAME_LEN);   //pad with NULLs
  return *this;
}

//**************************
// suspect first name
//**************************
IString ISuspectRecord :: firstName () const
{
  IString buffer;
  return field(buffer, offsetof(SUSPECT_STRUCT, firstName)+1, FIRST_NAME_LEN);   //pad with NULLs
}

ISuspectRecord & ISuspectRecord :: setFirstName (const IString & aSuspectFirstName)
{
  setField(aSuspectFirstName, offsetof(SUSPECT_STRUCT, firstName)+1, FIRST_NAME_LEN);   //pad with NULLs
  return *this;
}

//**************************
// suspect street
//**************************
IString ISuspectRecord :: street() const
{
  IString buffer;
  return field(buffer, offsetof(SUSPECT_STRUCT, street)+1, ADDRESS_STREET_LEN);   //pad with NULLs
}

ISuspectRecord & ISuspectRecord :: setStreet(const IString & aSuspectStreet)
{
  setField(aSuspectStreet, offsetof(SUSPECT_STRUCT, street)+1, ADDRESS_STREET_LEN);   //pad with NULLs
  return *this;
}

//**************************
// suspect city
//**************************
IString ISuspectRecord :: city() const
{
  IString buffer;
  return field(buffer, offsetof(SUSPECT_STRUCT, city)+1, ADDRESS_CITY_LEN);   //pad with NULLs
}

ISuspectRecord & ISuspectRecord :: setCity(const IString & aSuspectCity)
{
  setField(aSuspectCity, offsetof(SUSPECT_STRUCT, city)+1, ADDRESS_CITY_LEN);   //pad with NULLs
  return *this;
}

//**************************
// suspect county
//**************************
IString ISuspectRecord :: county() const
{
  IString buffer;
  return field(buffer, offsetof(SUSPECT_STRUCT, county)+1, ADDRESS_COUNTY_LEN);   //pad with NULLs
}

ISuspectRecord & ISuspectRecord :: setCounty(const IString & aSuspectCounty)
{
  setField(aSuspectCounty, offsetof(SUSPECT_STRUCT, county)+1, ADDRESS_COUNTY_LEN);   //pad with NULLs
  return *this;
}

//**************************
// suspect state
//**************************
IString ISuspectRecord :: state() const
{
  IString buffer;
  return field(buffer, offsetof(SUSPECT_STRUCT, state)+1, ADDRESS_STATE_LEN);   //pad with NULLs
}

ISuspectRecord & ISuspectRecord :: setState(const IString & aSuspectState)
{
  setField(aSuspectState, offsetof(SUSPECT_STRUCT, state)+1, ADDRESS_STATE_LEN);   //pad with NULLs
  return *this;
}

//**************************
// suspect zip
//**************************
IString ISuspectRecord :: zip() const
{
  IString buffer;
  return field(buffer, offsetof(SUSPECT_STRUCT, zip)+1, ADDRESS_ZIP_LEN);   //pad with NULLs
}

ISuspectRecord & ISuspectRecord :: setZip(const IString & aSuspectZip)
{
  setField(aSuspectZip, offsetof(SUSPECT_STRUCT, zip)+1, ADDRESS_ZIP_LEN);   //pad with NULLs
  return *this;
}

//**************************
// suspect description
//**************************
IString ISuspectRecord :: description() const
{
  IString buffer;
  return field(buffer, offsetof(SUSPECT_STRUCT, info)+1, SUSPECT_INFO_LEN);   //pad with NULLs
}

ISuspectRecord & ISuspectRecord :: setDescription(const IString & aSuspectInfo)
{
  setField(aSuspectInfo, offsetof(SUSPECT_STRUCT, info)+1, SUSPECT_INFO_LEN);   //pad with NULLs
  return *this;
}

//**************************
// suspect book Number
//**************************
unsigned long ISuspectRecord :: bookNumber() const
{
   unsigned long buffer;
   return field(buffer, offsetof(SUSPECT_STRUCT, book_number)+1);
}

ISuspectRecord & ISuspectRecord :: setBookNumber(unsigned long aSuspectBookNumber)
{
   setField(aSuspectBookNumber, offsetof(SUSPECT_STRUCT, book_number)+1);
   return *this;
}

//**************************
// suspect gender
//**************************
unsigned short ISuspectRecord :: gender() const
{
   unsigned short buffer;
   return field(buffer, offsetof(SUSPECT_STRUCT, gender)+1);
}

ISuspectRecord & ISuspectRecord :: setGender(unsigned short aSuspectGender)
{
   setField(aSuspectGender, offsetof(SUSPECT_STRUCT, gender)+1);
   return *this;
}

//**************************
// suspect height
//**************************
unsigned short ISuspectRecord :: height() const
{
   unsigned short buffer;
   return field(buffer, offsetof(SUSPECT_STRUCT, height)+1);
}

ISuspectRecord & ISuspectRecord :: setHeight(unsigned short aSuspectHeight)
{
   setField(aSuspectHeight, offsetof(SUSPECT_STRUCT, height)+1);
   return *this;
}

//**************************
// suspect weight
//**************************
unsigned short ISuspectRecord :: weight() const
{
   unsigned short buffer;
   return field(buffer, offsetof(SUSPECT_STRUCT, weight)+1);
}
ISuspectRecord & ISuspectRecord :: setWeight(unsigned short aSuspectWeight)
{
   setField(aSuspectWeight, offsetof(SUSPECT_STRUCT, weight)+1);
   return *this;
}

//**************************
// suspect hair color
//**************************
unsigned short ISuspectRecord :: hairColor() const
{
   unsigned short buffer;
   return field(buffer, offsetof(SUSPECT_STRUCT, hairColor)+1);
}

ISuspectRecord & ISuspectRecord :: setHairColor(unsigned short aSuspectHairColor)
{
   setField(aSuspectHairColor, offsetof(SUSPECT_STRUCT, hairColor)+1);
   return *this;
}

//**************************
// suspect eye color
//**************************
unsigned short ISuspectRecord :: eyeColor() const
{
   unsigned short buffer;
   return field(buffer, offsetof(SUSPECT_STRUCT, eyeColor)+1);
}

ISuspectRecord & ISuspectRecord :: setEyeColor(unsigned short aSuspectEyeColor)
{
   setField(aSuspectEyeColor, offsetof(SUSPECT_STRUCT, eyeColor)+1);
   return *this;
}

//**************************
// suspect has mole
//**************************
unsigned short ISuspectRecord :: hasMole() const
{
   unsigned short buffer;
   return field(buffer, offsetof(SUSPECT_STRUCT, hasMole)+1);
}

ISuspectRecord & ISuspectRecord :: enableHasMole(unsigned short suspectHasMole)
{
   setField(suspectHasMole, offsetof(SUSPECT_STRUCT, hasMole)+1);
   return *this;
}

//**************************
// suspect has scar
//**************************
unsigned short ISuspectRecord :: hasScar() const
{
   unsigned short buffer;
   return field(buffer, offsetof(SUSPECT_STRUCT, hasScar)+1);
}
ISuspectRecord & ISuspectRecord :: enableHasScar(unsigned short suspectHasScar)
{
   setField(suspectHasScar, offsetof(SUSPECT_STRUCT, hasScar)+1);
   return *this;
}

//**************************
// suspect has tattoo
//**************************
unsigned short ISuspectRecord :: hasTattoo() const
{
   unsigned short buffer;
   return field(buffer, offsetof(SUSPECT_STRUCT, hasTattoo)+1);
}
ISuspectRecord & ISuspectRecord :: enableHasTattoo(unsigned short suspectHasTattoo)
{
   setField(suspectHasTattoo, offsetof(SUSPECT_STRUCT, hasTattoo)+1);
   return *this;
}

//**************************
// suspect mug front
//**************************
unsigned short ISuspectRecord :: mugFront() const
{
   unsigned short buffer;
   return field(buffer, offsetof(SUSPECT_STRUCT, mugFront)+1);
}

ISuspectRecord & ISuspectRecord :: setMugFront(unsigned short aSuspectMugFront)
{
   setField(aSuspectMugFront, offsetof(SUSPECT_STRUCT, mugFront)+1);
   return *this;
}

//**************************
// suspect mug right
//**************************
unsigned short ISuspectRecord :: mugRight() const
{
   unsigned short buffer;
   return field(buffer, offsetof(SUSPECT_STRUCT, mugRight)+1);
}
ISuspectRecord & ISuspectRecord :: setMugRight(unsigned short aSuspectMugRight)
{
   setField(aSuspectMugRight, offsetof(SUSPECT_STRUCT, mugRight)+1);
   return *this;
}

//**************************
// suspect mug left
//**************************
unsigned short ISuspectRecord :: mugLeft() const
{
   unsigned short buffer;
   return field(buffer, offsetof(SUSPECT_STRUCT, mugLeft)+1);
}

ISuspectRecord & ISuspectRecord :: setMugLeft(unsigned short aSuspectMugLeft)
{
   setField(aSuspectMugLeft, offsetof(SUSPECT_STRUCT, mugLeft)+1);
   return *this;
}

//**************************
// suspect birthdate
//**************************
IString ISuspectRecord :: birthDate() const
{
  IString buffer;
  return field(buffer, offsetof(SUSPECT_STRUCT, birthDate)+1, DATE_LEN); //pad with NULLs
}

ISuspectRecord & ISuspectRecord :: setBirthDate(const IString & aSuspectBirthDate)
{
  setField(aSuspectBirthDate, offsetof(SUSPECT_STRUCT, birthDate)+1, DATE_LEN);   //pad with NULLs return *this;
  return *this;
}

//**************************
// suspect mo
//**************************
IString ISuspectRecord :: MO() const
{
  IString buffer;
  return field(buffer, offsetof(SUSPECT_STRUCT, MO)+1, SUSPECT_MO_DESC_LEN);   //pad with NULLs
}

ISuspectRecord & ISuspectRecord :: setMO(const IString & aSuspectMO)
{
  setField(aSuspectMO, offsetof(SUSPECT_STRUCT, MO)+1, SUSPECT_MO_DESC_LEN);   //pad with NULLs
  return *this;
}

//**************************
// suspect mole description
//**************************
IString ISuspectRecord :: moleDescription() const
{
  IString buffer;
  return field(buffer, offsetof(SUSPECT_STRUCT, moleDescription)+1, SUSPECT_TRAIT_DESC_LEN); //pad with NULLs
}

ISuspectRecord & ISuspectRecord :: setMoleDescription(const IString & aSuspectMoleDescription)
{
  setField(aSuspectMoleDescription, offsetof(SUSPECT_STRUCT, moleDescription)+1, SUSPECT_TRAIT_DESC_LEN); //pad with NULLs
  return *this;
}

//**************************
// suspect scar description
//**************************
IString ISuspectRecord :: scarDescription() const
{
  IString buffer;
  return field(buffer, offsetof(SUSPECT_STRUCT, scarDescription)+1, SUSPECT_TRAIT_DESC_LEN); //pad with NULLs
}

ISuspectRecord & ISuspectRecord :: setScarDescription(const IString & aSuspectScarDescription)
{
  setField(aSuspectScarDescription, offsetof(SUSPECT_STRUCT, scarDescription)+1, SUSPECT_TRAIT_DESC_LEN); //pad with NULLs
  return *this;
}

//**************************
// suspect tattoo description
//**************************
IString ISuspectRecord :: tattooDescription() const
{
  IString buffer;
  return field(buffer, offsetof(SUSPECT_STRUCT, tattooDescription)+1, SUSPECT_TRAIT_DESC_LEN); //pad with NULLs
}

ISuspectRecord & ISuspectRecord :: setTattooDescription(const IString & aSuspectTattooDescription)
{
  setField(aSuspectTattooDescription, offsetof(SUSPECT_STRUCT, tattooDescription)+1, SUSPECT_TRAIT_DESC_LEN); //pad with NULLs
  return *this;
}


/*******************************************************************
 * Implementor Member Functions
 *******************************************************************/
/*------------------------------------------------------------------------------
| Function Name: ISuspectRecord :: operator =
|
| Implementation:
|   Replace our data with the source ISuspectRecord data.
------------------------------------------------------------------------------*/
ISuspectRecord & ISuspectRecord :: operator = ( const ISuspectRecord & aRecord )
{
  IRecord::operator=(aRecord);
  return( *this );
}

/*------------------------------------------------------------------------------
| Function Name: ISuspectRecord :: operator =
|
| Implementation:
|   Replace our data with the source IString data.
------------------------------------------------------------------------------*/
ISuspectRecord & ISuspectRecord :: operator = ( const IString & aString )
{
  IRecord::operator=(aString);
  setSize (dParentSize + dMySize);
  return( *this );
}

