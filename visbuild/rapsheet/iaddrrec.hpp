#ifndef _IADDRREC_
#define _IADDRREC_
/******************************************************************************
* .FILE:        iaddrrec.hpp                                                  *
*                                                                             *
* .DESCRIPTION: Header file for the class, IAddressRecord                     *
*                                                                             *
* .CLASSES:     IAddressRecord                                                *
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
#include <irecord.hpp>

//Forward declarations of other classes

/*----------------------------------------------------------------------------*/
/* Align classes on four byte boundary.                                       */
/*----------------------------------------------------------------------------*/
#pragma pack(4)

//**************************************************************************
// Class:   IAddressRecord
//
// Purpose: Describes IAddressRecord
//
//**************************************************************************
class IVBSAMP_IMPORT IAddressRecord : public IRecord
{
public:
           IAddressRecord ();
           IAddressRecord ( const IString & recordData );
           IAddressRecord ( const IAddressRecord & aRecord );
  virtual  ~IAddressRecord ();

IAddressRecord & operator = ( const IAddressRecord & aRecord );
IAddressRecord & operator = ( const IString & aString );

/*------------------------------------------------------------------
 * street
 *-----------------------------------------------------------------*/
virtual IString street () const;
virtual IAddressRecord & setStreet (IString iStreet);

/*------------------------------------------------------------------
 * city
 *-----------------------------------------------------------------*/
virtual IString city () const;
virtual IAddressRecord & setCity (const IString & iCity);

/*------------------------------------------------------------------
 * state
 *-----------------------------------------------------------------*/
virtual IString state () const;
virtual IAddressRecord & setState (const IString iState);

/*------------------------------------------------------------------
 * zip
 *-----------------------------------------------------------------*/
virtual IString zip () const;
virtual IAddressRecord & setZip (const IString & iZip);


private:
   unsigned long dParentSize;
   const unsigned long dMySize;
};

/*----------------------------------------------------------------------------*/
/* Resume compiler default packing.                                           */
/*----------------------------------------------------------------------------*/
#pragma pack()

#endif

