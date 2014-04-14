#ifndef _ISUSPECT_
#define _ISUSPECT_
/******************************************************************************
* .FILE:        isuspect.hpp                                                  *
*                                                                             *
* .DESCRIPTION: Header file for the class ISuspect                            *
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
#include "ivbsamps.h"
#include <istring.hpp>
#include <ivseq.h>
#include <ireslib.hpp>
#include "iperson.hpp"
#include "iarrest.hpp"

/*----------------------------------------------------------------------------*/
/* Align classes on four byte boundary.                                       */
/*----------------------------------------------------------------------------*/
#pragma pack(4)

class IVBSAMP_IMPORT ISuspect : public IPerson {

/*--------------------------- PUBLIC -----------------------------------------*/
public:

/*------------------------- Constructors/Destructor ----------------------------
 -----------------------------------------------------------------------------*/
  ISuspect ();
  ISuspect (const ISuspect & partCopy);
virtual
  ~ISuspect ();

/*---------------------  ENUMERATED TYPES  ------------------------
 *-----------------------------------------------------------------*/
enum IMugAngle   {left,                     //0
                  front,                    //1
                  right};                   //2

/*-------------------------------- Operators -----------------------------------
------------------------------------------------------------------------------*/
  ISuspect & operator= (const ISuspect & aSuspect);

  bool
    operator == (const ISuspect & value) const,
    operator != (const ISuspect & value) const,
    operator == (const ISuspect * value) const,
    operator != (const ISuspect * value) const;

  virtual IString asString () const;
  virtual IString asDebugInfo () const;



/*-------------------------------- Attributes ----------------------------------
 | The following are attributes for this class:
 |    arrestList                 - list of arrests associated with a suspect
 |    bookNumber                 - number assigned to a suspect when first booked
 |    bookNumberAsString         - number assigned to a suspect when first booked
 |                                 (as an IString)
 |    hasMole                    - indicates if suspect has one or more moles
 |    hasScar                    - indicates if suspect has one or more scars
 |    hasTattoo                  - indicates if suspect has one or more tattoos
 |    MO                         - modis operandi
 |    moleDesc                   - description and location of suspect's moles
 |    mugFront                   - Id of bitmap for suspect's front portrait
 |    mugLeft                    - Id of bitmap for suspect's left portrait
 |    mugRight                   - Id of bitmap for suspect's right portrait
 |    mugFrontAsHandle           - Resource handle for Id of Bitmap for suspect's front portrait
 |    mugLeftAsHandle            - Resource handle for Id of bitmap for suspect's left portrait
 |    mugRightAsHandle           - Resource handle for Id of bitmap for suspect's right portrait
 |    scarDesc                   - description and location of suspect's scars
 |    tattooDesc                 - description and location of suspect's tattoos
 -----------------------------------------------------------------------------*/
  virtual IVSequence<IArrest *> * arrestList() const;
  virtual ISuspect & setArrestList(IVSequence<IArrest *> * aArrestList);

  virtual IString bookNumberAsString() const;
  virtual ISuspect & setBookNumberAsString(const IString & aBookNumber);

  virtual unsigned long bookNumber() const;
  virtual ISuspect & setBookNumber(const unsigned long aBookNumber);

  virtual bool hasMole() const;
  virtual ISuspect & enableHasMole(bool enable = true);

  virtual bool hasScar() const;
  virtual ISuspect & enableHasScar(bool enable = true);

  virtual bool hasTattoo() const;
  virtual ISuspect & enableHasTattoo(bool enable = true);

  virtual IString MO() const;
  virtual ISuspect & setMO(const IString & aMO);

  virtual IString moleDesc() const;
  virtual ISuspect & setMoleDesc(const IString & aMoleDesc);

  virtual unsigned short mugFront() const;
  virtual ISuspect & setMugFront(const unsigned short aMugFront);

  virtual unsigned short mugLeft() const;
  virtual ISuspect & setMugLeft(const unsigned short aMugLeft);

  virtual unsigned short mugRight() const;
  virtual ISuspect & setMugRight(const unsigned short aMugRight);

  virtual IBitmapHandle mugFrontAsHandle() const;
  virtual IBitmapHandle mugLeftAsHandle() const;
  virtual IBitmapHandle mugRightAsHandle() const;

  virtual IString scarDesc() const;
  virtual ISuspect & setScarDesc(const IString & aScarDesc);

  virtual IString tattooDesc() const;
  virtual ISuspect & setTattooDesc(const IString & aTattooDesc);


/*----------------------- Notification Event Ids -------------------------------
 -----------------------------------------------------------------------------*/
  static INotificationId arrestListId;
  static INotificationId bookNumberId;
  static INotificationId hasMoleId;
  static INotificationId hasScarId;
  static INotificationId hasTattooId;
  static INotificationId MOId;
  static INotificationId moleDescId;
  static INotificationId mugFrontId;
  static INotificationId mugLeftId;
  static INotificationId mugRightId;
  static INotificationId scarDescId;
  static INotificationId tattooDescId;

/*--------------------------- PRIVATE ----------------------------------------*/
private:
  static const unsigned short defaultMugId;
  static const IDynamicLinkLibrary mugLib;
  unsigned long  iBookNumber;
  unsigned short iMugFront;
  unsigned short iMugLeft;
  unsigned short iMugRight;
  bool iHasMole;
  bool iHasScar;
  bool iHasTattoo;
  IString iMO;
  IString iMoleDesc;
  IString iScarDesc;
  IString iTattooDesc;
  IVSequence<IArrest *> *iArrestList;

};   //ISuspect

/*----------------------------------------------------------------------------*/
/* Resume compiler default packing.                                           */
/*----------------------------------------------------------------------------*/
#pragma pack()

#endif

