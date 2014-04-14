/******************************************************************************
* .FILE:        iaddrrec.cpp                                                  *
*                                                                             *
* .DESCRIPTION: Implementation for the class, IAddressRecord                  *
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
#include "iaddrrec.hpp"               //IAddressRecord header

/*******************************************************************
 * Manager Member Functions
 *******************************************************************/
IAddressRecord :: IAddressRecord() :
                     IRecord(),
                     dMySize(57L)
{
   dParentSize = size();
   setSize( dParentSize + dMySize );  //pad with '\x00'
}

IAddressRecord :: IAddressRecord ( const IString & stringData ) :
                     IRecord(),
                     dMySize(57L)
{
   dParentSize = size();
   *this = stringData;
   setSize( dParentSize + dMySize );  //truncate or pad as appropriate
}

IAddressRecord :: IAddressRecord ( const IAddressRecord & aRecord ) :
                     IRecord(),
                     dMySize(57L)
{
   dParentSize = size();
   *this = aRecord;
  /*------------------------------------------------------------------
   * NOTE:  this record would have gotten set with the correct size
   *        if had called the IRecord (aRecord) constructor, but
   *        need to determine what dParentSize is (the assignment
   *        operators need this info).
   *-----------------------------------------------------------------*/
}

IAddressRecord :: ~IAddressRecord()
{
}

/*******************************************************************
 * Access Member Functions
 *******************************************************************/
/*------------------------------------------------------------------
 * street
 *-----------------------------------------------------------------*/
IString IAddressRecord :: street () const
{
   IString buffer;
   return field(buffer, 1, 30);   //pad with NULLs
}

IAddressRecord & IAddressRecord :: setStreet
  (IString iStreet)
{
   setField(iStreet, 1, 30);      //pad with NULLs
   return *this;
}

/*------------------------------------------------------------------
 * city
 *-----------------------------------------------------------------*/
IString IAddressRecord :: city () const
{
   IString buffer;
   return field(buffer, 31, 20);  //pad with NULLs
}

IAddressRecord & IAddressRecord :: setCity
  (const IString & iCity)
{
   setField(iCity, 31, 20);       //pad with NULLs
   return *this;
}

/*------------------------------------------------------------------
 * state
 *-----------------------------------------------------------------*/
IString IAddressRecord :: state () const
{
   IString buffer;
   return field(buffer, 51, 2);   //pad with NULLs
}

IAddressRecord & IAddressRecord :: setState
  (const IString iState)
{
   setField(iState, 51, 2);       //pad with NULLs
   return *this;
}

/*------------------------------------------------------------------
 * zip
 *-----------------------------------------------------------------*/
IString IAddressRecord :: zip () const
{
   IString buffer;
   return field(buffer, 53, 5);   //pad with NULLs
}

IAddressRecord & IAddressRecord :: setZip
  (const IString & iZip)
{
   setField(iZip, 53, 5);         //pad with NULLs
   return *this;
}


/*******************************************************************
 * Implementor Member Functions
 *******************************************************************/
/*------------------------------------------------------------------------------
| Function Name: IAddressRecord :: operator =
|
| Implementation:
|   Replace our data with the source IAddressRecord data.
------------------------------------------------------------------------------*/
IAddressRecord & IAddressRecord :: operator = ( const IAddressRecord & aRecord )
{
  IRecord::operator=(aRecord);
  return( *this );
}

/*------------------------------------------------------------------------------
| Function Name: IAddressRecord :: operator =
|
| Implementation:
|   Replace our data with the source IString data.
------------------------------------------------------------------------------*/
IAddressRecord & IAddressRecord :: operator = ( const IString & aString )
{
  IRecord::operator=(aString);
  setSize (dParentSize + dMySize);
  return( *this );
}
