/******************************************************************************
* .FILE:         transelm.h                                                   *
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
|  transelm.h  -  Class TranslationElement  for use with the    |
|                 Translation Table example.                    |
\*-------------------------------------------------------------*/
#ifndef _TRANSELM_H
#define _TRANSELM_H

#include <iglobals.h>

class TranslationElement  {

  char ivAscCode;
  char ivEbcCode;

public:

  /* Let the compiler generate Default and Copy Constructor,*/
  /* Destructor and Assignment for us.                      */

  char const& ascCode () const
       { return ivAscCode;
       }

  char const& ebcCode () const
       { return ivEbcCode;
       }

  TranslationElement (char asc, char ebc)
       : ivAscCode(asc), ivEbcCode(ebc) {};

  /* We need to define the equality.                        */
  IBoolean operator == (TranslationElement const& te) const  {
     return ivAscCode == te.ivAscCode
        &&  ivEbcCode == te.ivEbcCode;
   };

  /* An ordering relation must not be defined for           */
  /* elements in a map.                                     */

  /* We need to define the key access for the elements.     */
  /* We decided to define all key operations in a           */
  /* separate operations class in file trmapops.h.          */

};

#endif
