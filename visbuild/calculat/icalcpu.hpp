#ifndef _ICALCPU_
#define _ICALCPU_
/******************************************************************************
* .FILE:        icalcpu.hpp                                                   *
*                                                                             *
* .DESCRIPTION: Header file for the class, ICalcPU                            *
*                                                                             *
* .CLASSES:     ICalcPU                                                       *
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

//Forward declarations of other classes

class ICalcOperator;
class ICalcFunction;


//**************************************************************************
// Class:   ICalcPU
//
// Purpose: Describes ICalcPU
//   This is the Calculator Processing Unit Part
//************************************************************************** */

class IVBSAMP_IMPORT ICalcPU : public IStandardNotifier
{
public:
           ICalcPU                ();
  virtual  ~ICalcPU ();

//
// List of Part Events
//

static INotificationId bufferId;
static INotificationId evaluateId;

//
// List of Part Attributes - (query and set members)
//

virtual IString
  buffer () const;

virtual ICalcPU&
  setBuffer (const char * iBuffer);

//
// List of Implementor Function Methods that are Part Actions
//

virtual ICalcPU &
  processOperatorResult (double iAccumulator);

virtual ICalcPU &
  processDigit (IString iCurrentDigit);

virtual ICalcPU &
  processOperator (ICalcOperator *iCurrentOp);

virtual ICalcPU &
  processFunction (ICalcFunction *iCurrentFunc);

virtual double
  evaluateOperation ();

virtual ICalcPU &
  clearCalc ();

//
// List of Implementor Function Methods that are not Part Actions
//

virtual ICalcPU &
  evaluateOperator ();

protected:
//
// List of enumeration types
//

enum Register { none=-1, R1, R2 };

//
// List of data members that are Attributes
//

  IString dBuffer;   // Active Display


//
// List of Data Members that are not Attributes
//

  double dRegisters[2];
  unsigned long dCurrentReg;
  bool dR2SetFromDisplay;
  bool dExpectNewOperand;
  ICalcOperator *dPendingOp;

//
// List of Helping Function Methods that are not Part Actions
//

virtual ICalcPU &
  evaluateIt ();

virtual ICalcPU &
  setDisplayFromAccumulator (double iAccumulator);

virtual ICalcPU &
  setCurrentRegFromDisplay ();

};

#endif
