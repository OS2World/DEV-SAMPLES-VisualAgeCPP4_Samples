/******************************************************************************
* .FILE:         trmapops.h                                                   *
*                                                                             *
* .COPYRIGHT:                                                                 *
*    IBM Open Class Library                                                   *
*    Licensed Material - Program-Property of IBM                              *
*    (C) Copyright IBM Corp. 1992, 1997 - All Rights Reserved                 *
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

/*-------------------------------------------------------------*\
|  trmapops.h  -  Translation Map Operations                    |
|                 This is the base class for the element        |
|                 operations for our Translation Map example.   |
\*-------------------------------------------------------------*/
#ifndef _TRMAPOPS_H
#define _TRMAPOPS_H

       /* Get the standard operation classes.                  */
#include <istdops.h>

#include "transelm.h"

class TranslationOps : public IEOps < TranslationElement >
{
public:
  class KeyOps : public IStdEqOps < char >, public IStdHshOps < char >
  {
  }  keyOps;
};

       /* Operations Class for the EBCDIC-ASCII mapping:       */
class TranslationOpsE2A : public TranslationOps
{
public:                     /* Key Access                      */
  char const& key (TranslationElement const& te) const
    { return te.ebcCode (); }
};


       /* Operations Class for the ASCII-EBCDIC mapping:       */
class TranslationOpsA2E : public TranslationOps
{
public:                     /* Key Access                      */
  char const& key (TranslationElement const& te) const
    { return te.ascCode (); }
};

#endif
