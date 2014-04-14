#ifndef _ISUSREC_
#define _ISUSREC_
/******************************************************************************
* .FILE:        isusrec.hpp                                                   *
*                                                                             *
* .DESCRIPTION: Header file for the class ISuspectRecord                      *
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
#include "ivbsamps.h"
#include <irecord.hpp>

//forward class declarations
class IString;

/*----------------------------------------------------------------------------*/
/* Align classes on four byte boundary.                                       */
/*----------------------------------------------------------------------------*/
#pragma pack(4)

//**************************************************************************
// Class:   ISuspectRecord
//
// Purpose: Defines the record that will be used to pass suspect data
//          to and from the database server (via communication parts).
//          This record class is based off SUSPECT_STRUCT, which is
//          defined in rap.h.
//
//**************************************************************************
class IVBSAMP_IMPORT ISuspectRecord : public IRecord
{

public:

   ISuspectRecord ( );
   ISuspectRecord ( const IString & suspectData );
   ISuspectRecord ( const ISuspectRecord & aSuspectRecord );
   virtual ~ISuspectRecord ( );

   ISuspectRecord & operator = ( const ISuspectRecord & aSuspectRecord );
   ISuspectRecord & operator = ( const IString & aString );
   ISuspectRecord & operator += ( const IString & aString);

   virtual IString asDebugInfo () const;

   virtual IString lastName() const;
   virtual ISuspectRecord & setLastName(const IString & aLastName);

   virtual IString firstName() const;
   virtual ISuspectRecord & setFirstName(const IString & aFirstName);

   virtual IString street() const;
   virtual ISuspectRecord & setStreet(const IString & aStreet);

   virtual IString city() const;
   virtual ISuspectRecord & setCity(const IString & aCity);

   virtual IString county() const;
   virtual ISuspectRecord & setCounty(const IString & aCounty);

   virtual IString state() const;
   virtual ISuspectRecord & setState(const IString & aState);

   virtual IString zip() const;
   virtual ISuspectRecord & setZip(const IString & aZip);

   virtual IString description() const;
   virtual ISuspectRecord & setDescription(const IString & info);

   virtual unsigned long bookNumber() const;
   virtual ISuspectRecord & setBookNumber(unsigned long aBookNumber);

   virtual unsigned short gender() const;
   virtual ISuspectRecord & setGender(unsigned short aGender);

   virtual unsigned short height() const;
   virtual ISuspectRecord & setHeight(unsigned short aHeight);

   virtual unsigned short weight() const;
   virtual ISuspectRecord & setWeight(unsigned short aWeight);

   virtual unsigned short hairColor() const;
   virtual ISuspectRecord & setHairColor(unsigned short aHairColor);

   virtual unsigned short eyeColor() const;
   virtual ISuspectRecord & setEyeColor(unsigned short anEyeColor);

   virtual unsigned short hasMole() const;
   virtual ISuspectRecord & enableHasMole(unsigned short hasMole);

   virtual unsigned short hasScar() const;
   virtual ISuspectRecord & enableHasScar(unsigned short hasScar);

   virtual unsigned short hasTattoo() const;
   virtual ISuspectRecord & enableHasTattoo(unsigned short hasTattoo);

   virtual unsigned short mugFront() const;
   virtual ISuspectRecord & setMugFront(unsigned short mugFront);

   virtual unsigned short mugRight() const;
   virtual ISuspectRecord & setMugRight(unsigned short mugRight);

   virtual unsigned short mugLeft() const;
   virtual ISuspectRecord & setMugLeft(unsigned short mugLeft);

   virtual IString birthDate() const;
   virtual ISuspectRecord & setBirthDate(const IString & aBirthDate);

   virtual IString MO() const;
   virtual ISuspectRecord & setMO(const IString & aMO);

   virtual IString moleDescription() const;
   virtual ISuspectRecord & setMoleDescription(const IString & aMoleDescription);

   virtual IString scarDescription() const;
   virtual ISuspectRecord & setScarDescription(const IString & aScarDescription);

   virtual IString tattooDescription() const;
   virtual ISuspectRecord & setTattooDescription(const IString & aTattooDescription);

private:
   unsigned long dParentSize;
   const unsigned long dMySize;

}; // ISuspectRecord

/*----------------------------------------------------------------------------*/
/* Resume compiler default packing.                                           */
/*----------------------------------------------------------------------------*/
#pragma pack()

#endif // _ISuspectRecord_

