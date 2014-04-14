#ifndef _ICALCDC_
#define _ICALCDC_
/******************************************************************************
* .FILE:        icalcdc.hpp                                                   *
*                                                                             *
* .DESCRIPTION: Header file for the class, ICalcDivisionChip                  *
*                                                                             *
* .CLASSES:     ICalcDivisionChip                                             *
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
#include "icalcop.hpp"

//**************************************************************************
// Class:   ICalcDivisionChip
//
// Purpose: Describes ICalcDivisionChip
//   Defines the calculator division chip
//************************************************************************** */

class IVBSAMP_IMPORT ICalcDivisionChip : public ICalcOperator
{
public:
           ICalcDivisionChip          ();
  virtual  ~ICalcDivisionChip ();

//Implementor Method Functions

virtual double
  evaluate (double operand1, double operand2);

};

#endif
