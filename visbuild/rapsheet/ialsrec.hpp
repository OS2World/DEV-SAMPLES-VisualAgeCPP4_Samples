#ifndef _IALSREC_
#define _IALSREC_
/******************************************************************************
* .FILE:        ialsrec.hpp                                                   *
*                                                                             *
* .DESCRIPTION: Header file for the class IAliasRecord                        *
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
#include "ivbsamps.h"
#include <istring.hpp>
#include <irecord.hpp>

//Forward declarations of other classes

/*----------------------------------------------------------------------------*/
/* Align classes on four byte boundary.                                       */
/*----------------------------------------------------------------------------*/
#pragma pack(4)

//**************************************************************************
// Class:   IAliasRecord
//
// Purpose: Describes IAliasRecord
//
//**************************************************************************
class IVBSAMP_IMPORT IAliasRecord : public IRecord
{
public:
           IAliasRecord ();
           IAliasRecord ( const IString & stringData );
           IAliasRecord ( const IAliasRecord & aRecord );
  virtual  ~IAliasRecord ();

IAliasRecord & operator = ( const IAliasRecord & aRecord );
IAliasRecord & operator = ( const IString & aString );

/*------------------------------------------------------------------
 * name
 *-----------------------------------------------------------------*/
virtual IString name () const;
virtual IAliasRecord & setName (const IString & iName);

private:
   unsigned long dParentSize;
   const unsigned long dMySize;
};

/*----------------------------------------------------------------------------*/
/* Resume compiler default packing.                                           */
/*----------------------------------------------------------------------------*/
#pragma pack()

#endif

