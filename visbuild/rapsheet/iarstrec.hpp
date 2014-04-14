#ifndef _IARSTREC_
#define _IARSTREC_
/******************************************************************************
* .FILE:        iarstrec.hpp                                                  *
*                                                                             *
* .DESCRIPTION: Header file for the class IArrestRecord                       *
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
#include "ivbsamps.h"
#include <istring.hpp>
#include <irecord.hpp>

//Forward declarations of other classes

/*----------------------------------------------------------------------------*/
/* Align classes on four byte boundary.                                       */
/*----------------------------------------------------------------------------*/
#pragma pack(4)

//**************************************************************************
// Class:   IArrestRecord
//
// Purpose: Describes IArrestRecord
//
//**************************************************************************
class IVBSAMP_IMPORT IArrestRecord : public IRecord
{
public:
           IArrestRecord ();
           IArrestRecord ( const IString & recordData );
           IArrestRecord ( const IArrestRecord & aRecord );
  virtual  ~IArrestRecord ();

IArrestRecord & operator = ( const IArrestRecord & aRecord );
IArrestRecord & operator = ( const IString & aString );

/*------------------------------------------------------------------
 * charge
 *-----------------------------------------------------------------*/
virtual unsigned short charge () const;
virtual IArrestRecord & setCharge (unsigned short iCharge);

/*------------------------------------------------------------------
 * status
 *-----------------------------------------------------------------*/
virtual unsigned short status () const;
virtual IArrestRecord & setStatus (unsigned short iStatus);

/*------------------------------------------------------------------
 * statusDate
 *-----------------------------------------------------------------*/
virtual IString statusDate () const;
virtual IArrestRecord & setStatusDate (const IString & iStatusDate);


private:
   unsigned long dParentSize;
   const unsigned long dMySize;
};

/*----------------------------------------------------------------------------*/
/* Resume compiler default packing.                                           */
/*----------------------------------------------------------------------------*/
#pragma pack()

#endif

