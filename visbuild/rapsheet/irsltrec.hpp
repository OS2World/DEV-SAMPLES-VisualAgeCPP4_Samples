#ifndef _IRSLTREC_
#define _IRSLTREC_
/******************************************************************************
* .FILE:        irsltrec.hpp                                                  *
*                                                                             *
* .DESCRIPTION: Header file for the class IResultRecordClass                  *
*                                                                             *
* .CLASSES:     IResultRecordClass                                            *
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

//**************************************************************************
// Class:   IResultRecord
//
// Purpose: Describes IResultRecord
//
//**************************************************************************
class IVBSAMP_IMPORT IResultRecord : public IRecord
{
public:
           IResultRecord ();
           IResultRecord ( const IString & recordData );
           IResultRecord ( const IResultRecord & aRecord );
  virtual  ~IResultRecord ();

IResultRecord & operator = ( const IResultRecord & aRecord );
IResultRecord & operator = ( const IString & aString );

IString asDebugInfo () const;

/*------------------------------------------------------------------
 * numResults
 *-----------------------------------------------------------------*/
virtual unsigned short
  numResults () const;
virtual IResultRecord &
  setNumResults (unsigned short iNumResults);

/*------------------------------------------------------------------
 * resultData
 *-----------------------------------------------------------------*/
virtual IString
  resultData () const;
virtual IResultRecord &
  setResultData (const IString & iResultData);


private:
   unsigned long dParentSize;
   const unsigned long dMySize;
};

#endif

