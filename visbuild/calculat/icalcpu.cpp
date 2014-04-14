/******************************************************************************
* .FILE:        icalcpu.cpp                                                   *
*                                                                             *
* .DESCRIPTION: Implementation for the class, ICalcPU                         *
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

#include <stdio.h>                    //for sprintf
#include "icalcpu.hpp"                //ICalcPU header
#include "icalcop.hpp"                //ICalcOperator header
#include "icalcfnc.hpp"               //ICalcFunction header
#include <inotifev.hpp>

//
// Events
//

INotificationId ICalcPU :: bufferId = "ICalcPU::buffer";
INotificationId ICalcPU :: evaluateId = "ICalcPU::evaluate";

/*******************************************************************
 * Contructors/Destructors
 *******************************************************************/

ICalcPU :: ICalcPU() :
        dBuffer(""),
        dCurrentReg(none),
        dR2SetFromDisplay(false),
        dExpectNewOperand(false),
        dPendingOp(0)
{
}

ICalcPU :: ~ICalcPU()
{
}

/*******************************************************************
 * Access Member Functions (Part Actions)
 *******************************************************************/

//
// The Buffer attribute represents calculator display
//

IString ICalcPU :: buffer () const
{
  return dBuffer;
}


ICalcPU & ICalcPU :: setBuffer
  (const char * iBuffer)
{

  if (dBuffer != iBuffer)
  {
    dBuffer = iBuffer;                  //Set class.attribute
    notifyObservers(INotificationEvent(bufferId,*this));
  }

  return *this;

}


/*******************************************************************
 * Implementor Member Functions (Part Actions)
 *******************************************************************/


//
// Process each digit input to the PU
//

ICalcPU & ICalcPU :: processDigit (IString iCurrentDigit)
{
  IString tempString;

  //
  // If expecting a new input number or if the display has been cleared,
  // start a new number. Otherwise get the current buffer contents and
  // add the new digit to what is already there.
  //

  if (dExpectNewOperand || dBuffer == "")
  {
     tempString = "";
     dExpectNewOperand = false;
  }

  else tempString = dBuffer;

  tempString += iCurrentDigit;   // Add to the current buffer contents
  setBuffer(tempString);         // Want event, bufferId(), to get
                                 //   signalled, so call set to display.
  return *this;

}


//
// Process each binary operator key input to the PU
//

ICalcPU & ICalcPU :: processOperator (ICalcOperator *iCurrentOp)
{

  //
  // Set display contents into the current register.
  // If the current register is register 2, evaluate the pending
  // operation.
  // Set the current operation as the pending operation and wait for
  // a new operand to be entered.
  //

  setCurrentRegFromDisplay ();

  if (dCurrentReg == R2) evaluateIt();

  dPendingOp = iCurrentOp;
  dExpectNewOperand = true;
  return *this;

}


//
// Process the results of any binary operation.
//

ICalcPU & ICalcPU :: processOperatorResult (double iAccumulator)
{

  //
  // Get the result of come operation, set it into register 1,
  // display the results,and wait for the next operand to be entered.
  //

  dCurrentReg = R1;
  dRegisters[dCurrentReg] = iAccumulator;
  dExpectNewOperand = true;
  setDisplayFromAccumulator(iAccumulator);
  return *this;

}


//
// Process each function key input to the PU
//

ICalcPU & ICalcPU :: processFunction (ICalcFunction *iCurrentFunc)
{

  //
  // Invoke the specified unary function
  //

  iCurrentFunc->perform(*this);
  return *this;

}


//
// Evaluate any pending binary operation
//

double ICalcPU :: evaluateOperation ()
{

  //
  // Invoke the pending operation
  //

  return dPendingOp->evaluate (dRegisters[R1], dRegisters[R2]);

}


//
// Clear the calculator PU
//

ICalcPU & ICalcPU :: clearCalc ()
{

  setBuffer("");
  dCurrentReg = none;
  dExpectNewOperand = false;
  dR2SetFromDisplay = false;  //reinit R2 has been set flag
  dRegisters[R1] = 0;
  dRegisters[R2] = 0;

  return *this;

}


/*******************************************************************
 * Implementor Member Functions (not Part Actions)
 *******************************************************************/

ICalcPU & ICalcPU :: evaluateOperator ()
{

   setCurrentRegFromDisplay ();

   if (dR2SetFromDisplay) evaluateIt();

   dExpectNewOperand = true;
   return *this;

}


/*******************************************************************
 * Helping Member Functions (Not Part Actions)
 *******************************************************************/

ICalcPU & ICalcPU :: evaluateIt ()
{
   notifyObservers(INotificationEvent(evaluateId,*this));
   return *this;
}


ICalcPU & ICalcPU ::
  setDisplayFromAccumulator (double iAccumulator)
{
  char tempString[20];
  signed long tempAccum = iAccumulator;

  //
  // Convert the accumulator value to a string and display it
  //

  if (iAccumulator != tempAccum)
     sprintf(tempString, "%f", iAccumulator);

  else
     sprintf(tempString, "%d", tempAccum);

  setBuffer ( tempString );             //want the event, bufferId(),
                                        //to be signalled, so call set
  return *this;

}


ICalcPU & ICalcPU ::
  setCurrentRegFromDisplay ()           
{

  /*****************************************************************
   * As a precaution, only set the current register if dBuffer,
   * which represents the calculator display, is not a nullstring.
   * NOTE:  dBuffer should never be a nullstring as long as the
   *        entry field that maps to it (i.e., that represents
   *        the calculator display) is always a display-only field.
   *****************************************************************/

  if (dBuffer.size() && !dExpectNewOperand)
  {
     dRegisters[++dCurrentReg] = dBuffer.asDouble();

     if ((dCurrentReg == R2) && (!dR2SetFromDisplay)) 
     {
        dR2SetFromDisplay = true;
     }

  }

  return *this;

}

