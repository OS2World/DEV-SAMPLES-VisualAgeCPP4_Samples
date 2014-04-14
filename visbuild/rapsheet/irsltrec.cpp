/******************************************************************************
* .FILE:        irsltrec.cpp                                                  *
*                                                                             *
* .DESCRIPTION: Implementation for the class, IResultRecord                   *
*                                                                             *
* .CLASSES:     IResultRecord                                                 *
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
#include "irsltrec.hpp"               //IResultRecord header

/*******************************************************************
 * Manager Member Functions
 *******************************************************************/
IResultRecord :: IResultRecord() :
                     IRecord(),
                     dMySize(32759L)
{
   dParentSize = size();
   setSize( dParentSize + dMySize );  //pad with NULLs
}

IResultRecord :: IResultRecord ( const IString & stringData ) :
                     IRecord(),
                     dMySize(32759L)
{
   dParentSize = size();
   *this = stringData;
   setSize( dParentSize + dMySize );  //truncate or pad as appropriate
}

IResultRecord :: IResultRecord ( const IResultRecord & aRecord ) :
                     IRecord(),
                     dMySize(32759L)
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

IResultRecord :: ~IResultRecord()
{
}

/*------------------------------------------------------------------------------
| IResultRecord::asDebugInfo                                                   |
|                                                                              |
| Generate a string that identifies for debugging purposes what data           |
| an IResultRecord instance contains.                                          |
|                                                                              |
------------------------------------------------------------------------------*/
IString IResultRecord :: asDebugInfo () const
{
  IString debugInfo("size=" + IString(dMySize) + ",");
  debugInfo += "numResults=" + IString(numResults()) + ",";
  debugInfo += "data=" + resultData() + ".";

  return debugInfo;
}

/*******************************************************************
 * Access Member Functions
 *******************************************************************/
/*------------------------------------------------------------------
 * numResults
 *-----------------------------------------------------------------*/
unsigned short IResultRecord :: numResults () const
{
   unsigned short buffer;
   return field(buffer, 1);
}

IResultRecord & IResultRecord :: setNumResults
  (unsigned short iNumResults)
{
   setField(iNumResults, 1);
   return *this;
}

/*------------------------------------------------------------------
 * resultsData
 *-----------------------------------------------------------------*/
IString IResultRecord :: resultData () const
{
   IString buffer;
   return field(buffer, 3, 32757);
   }

IResultRecord & IResultRecord :: setResultData
  (const IString & iResultData)
{
   setField(iResultData, 3, 32757);
   return *this;
}

/*******************************************************************
 * Implementor Member Functions
 *******************************************************************/
/*------------------------------------------------------------------------------
| Function Name: IResultRecord :: operator =
|
| Implementation:
|   Replace our data with the source IResultRecord data.
------------------------------------------------------------------------------*/
IResultRecord & IResultRecord :: operator = ( const IResultRecord & aRecord )
{
  IRecord::operator=(aRecord);
  return( *this );
}

/*------------------------------------------------------------------------------
| Function Name: IResultRecord :: operator =
|
| Implementation:
|   Replace our data with the source IString data.
------------------------------------------------------------------------------*/
IResultRecord & IResultRecord :: operator = ( const IString & aString )
{
  IRecord::operator=(aString);
  setSize (dParentSize + dMySize);
  return( *this );
}

