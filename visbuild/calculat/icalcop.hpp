#ifndef _ICALCOP_
#define _ICALCOP_
/******************************************************************************
* .FILE:        icalcop.hpp                                                   *
*                                                                             *
* .DESCRIPTION: Header file for the class, ICalcOperator                      *
*                                                                             *
* .CLASSES:     ICalcOperator                                                 *
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

#include <istring.hpp>
#include <istdntfy.hpp>
#include "ivbsamps.h"

//**************************************************************************
// Class:   ICalcOperator
//
// Purpose: Describes ICalcOperator
//   This is the abstract base class for all calculator binary operations.
//   This defines the pluggable interface for all binary operation
//   functions.
//************************************************************************** */

class IVBSAMP_IMPORT ICalcOperator : public IStandardNotifier
{
public:
           ICalcOperator          ();
  virtual  ~ICalcOperator ();

//
// List of Part Events
//

static INotificationId resultId;

//
// List of Part Actions
//

virtual double
  result () const;

virtual double
  setResult (double iResult);

//
//Implementor Method Functions
//

virtual double
  evaluate (double operand1, double operand2) = 0;


protected:
// List of data members
  double dResult;

};

#endif
