#ifndef _ICALCTLY_
#define _ICALCTLY_
/******************************************************************************
* .FILE:        icalctly.hpp                                                  *
*                                                                             *
* .DESCRIPTION: Header file for the class, ICalcTally                         *
*                                                                             *
* .CLASSES:     ICalcTally                                                    *
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
// Class:   ICalcTally
//
// Purpose: Describes ICalcTally Class.
//   This is the Tally function for the Calculator
//**************************************************************************

class IVBSAMP_IMPORT ICalcTally : public IStandardNotifier
{
public:
           ICalcTally            ();
  virtual  ~ICalcTally ();

//
// List of Part Events
//

static INotificationId bufferId;
static INotificationId nextTallyLineId;
static INotificationId notEmptyId;

//
// List of Part Attributes - (query and set members)
//

virtual IString
  buffer () const;

virtual ICalcTally&
  setBuffer (IString iBuffer);

virtual IString
  nextTallyLine () const;

virtual ICalcTally&
  setNextTallyLine (IString iString);

//
// List of Part Actions
//

virtual bool
  reset ();

virtual bool
  processBinaryOperator (IString iBinaryOpSym);

virtual bool
  processUnaryOperator (IString iUnaryOpSym);

protected:
//
// List of data members - Attributes
//

  IString dBuffer;        // Active Display Image
  IString dNextTallyLine; // Next line to add to the Tally

//
// Non-exposed data members
//

  bool dUpdateTally;
  bool dProcessBinaryOp;
  bool dEmptyMark;
  bool dResultExpected;
  IString dLastOperator;


};

#endif
