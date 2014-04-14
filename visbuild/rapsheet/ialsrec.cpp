/******************************************************************************
* .FILE:        ialsrec.cpp                                                   *
*                                                                             *
* .DESCRIPTION: Implementation for the class, IAliasRecord                    *
*                                                                             *
* .CLASSES:     IAliasRecord                                                  *
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
#include "ialsrec.hpp"               //IAliasRecord header
#include "rap.h"

/*******************************************************************
 * Manager Member Functions
 *******************************************************************/
IAliasRecord :: IAliasRecord() :
                     IRecord (),
                     dMySize(ALIAS_NAME_LEN)
{
   dParentSize = size();
   setSize( dParentSize + dMySize );  //pad with '\x00'
}

IAliasRecord :: IAliasRecord ( const IString & stringData ) :
                     IRecord(),
                     dMySize(ALIAS_NAME_LEN)

{
   dParentSize = size();
   *this = stringData;
   setSize( dParentSize + dMySize );  //truncate or pad as appropriate
}

IAliasRecord :: IAliasRecord ( const IAliasRecord & aRecord ) :
                     IRecord(),
                     dMySize(ALIAS_NAME_LEN)
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

IAliasRecord :: ~IAliasRecord()
{
}

/*******************************************************************
 * Access Member Functions
 *******************************************************************/
/*------------------------------------------------------------------
 * name
 *-----------------------------------------------------------------*/
IString IAliasRecord :: name () const
{
   IString buffer;
   return field(buffer, 1, ALIAS_NAME_LEN);
}

IAliasRecord & IAliasRecord :: setName
  (const IString & iName)
{
   setField(iName, 1, ALIAS_NAME_LEN);
   return *this;
}

/*******************************************************************
 * Implementor Member Functions (not Part Actions)
 *******************************************************************/
/*------------------------------------------------------------------------------
| Function Name: IAliasRecord :: operator =
|
| Implementation:
|   Replace our data with the source IAliasRecord data.
------------------------------------------------------------------------------*/
IAliasRecord & IAliasRecord :: operator = ( const IAliasRecord & aRecord )
{
  IRecord::operator=(aRecord);
  return( *this );
}

/*------------------------------------------------------------------------------
| Function Name: IAliasRecord :: operator =
|
| Implementation:
|   Replace our data with the source IString data.
------------------------------------------------------------------------------*/
IAliasRecord & IAliasRecord :: operator = ( const IString & aString )
{
  IRecord::operator=(aString);
  setSize (dParentSize + dMySize);
  return( *this );
}
