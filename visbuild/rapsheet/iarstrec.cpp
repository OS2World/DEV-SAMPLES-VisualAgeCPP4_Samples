/******************************************************************************
* .FILE:        iarstrec.cpp                                                  *
*                                                                             *
* .DESCRIPTION: Implementation for the class, IArrestRecord                   *
*                                                                             *
* .CLASSES:     IArrestRecord                                                 *
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
#include "iarstrec.hpp"               //IArrestRecord header

/*******************************************************************
 * Manager Member Functions
 *******************************************************************/
IArrestRecord :: IArrestRecord() :
                     IRecord(),
                     dMySize(14L)
{
   dParentSize = size();
   setSize( dParentSize + dMySize );  //pad with '\x00'
}

IArrestRecord :: IArrestRecord ( const IString & stringData ) :
                     IRecord(),
                     dMySize(14L)
{
   dParentSize = size();
   *this = stringData;
   setSize( dParentSize + dMySize );  //truncate or pad as appropriate
}

IArrestRecord :: IArrestRecord ( const IArrestRecord & aRecord ) :
                     IRecord(),
                     dMySize(14L)
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

IArrestRecord :: ~IArrestRecord()
{
}

/*******************************************************************
 * Access Member Functions
 *******************************************************************/
/*------------------------------------------------------------------
 * charge
 *-----------------------------------------------------------------*/
unsigned short IArrestRecord :: charge () const
{
   unsigned short buffer;
   return field(buffer, 1);
}

IArrestRecord & IArrestRecord :: setCharge
  (unsigned short iCharge)
{
   setField(iCharge, 1);
   return *this;
}

/*------------------------------------------------------------------
 * status
 *-----------------------------------------------------------------*/
unsigned short IArrestRecord :: status () const
{
   unsigned short buffer;
   return field(buffer, 3);
}

IArrestRecord & IArrestRecord :: setStatus
  (unsigned short iStatus)
{
   setField(iStatus, 3);
   return *this;
}

/*------------------------------------------------------------------
 * statusDate
 *-----------------------------------------------------------------*/
IString IArrestRecord :: statusDate () const
{
   IString buffer;
   return field(buffer, 5, 10);   //pad with NULLs
}

IArrestRecord & IArrestRecord :: setStatusDate
  (const IString & iStatusDate)
{
   setField(iStatusDate, 5, 10);       //pad with NULLs
   return *this;
}


/*******************************************************************
 * Implementor Member Functions
 *******************************************************************/
/*------------------------------------------------------------------------------
| Function Name: IArrestRecord :: operator =
|
| Implementation:
|   Replace our data with the source IArrestRecord data.
------------------------------------------------------------------------------*/
IArrestRecord & IArrestRecord :: operator = ( const IArrestRecord & aRecord )
{
  IRecord::operator=(aRecord);
  return( *this );
}

/*------------------------------------------------------------------------------
| Function Name: IArrestRecord :: operator =
|
| Implementation:
|   Replace our data with the source IString data.
------------------------------------------------------------------------------*/
IArrestRecord & IArrestRecord :: operator = ( const IString & aString )
{
  IRecord::operator=(aString);
  setSize (dParentSize + dMySize);
  return( *this );
}

