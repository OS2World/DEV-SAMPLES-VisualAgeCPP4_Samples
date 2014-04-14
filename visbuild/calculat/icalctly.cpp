/******************************************************************************
* .FILE:        icalctly.cpp                                                  *
*                                                                             *
* .DESCRIPTION: Implementation for the class, ICalcTally                      *
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

#include "icalctly.hpp" 

#include <inotifev.hpp>

/*******************************************************************
 * Contructors/Destructors
 *******************************************************************/

ICalcTally :: ICalcTally()
{
   reset();
}

ICalcTally :: ~ICalcTally()
{
}

//
// List of Events
//

INotificationId ICalcTally :: bufferId = "ICaclTally::buffer";
INotificationId ICalcTally :: nextTallyLineId = "ICalcTally::nextTallyLine";
INotificationId ICalcTally :: notEmptyId = "ICalcTally::notEmpty";

/*******************************************************************
 * Access Member Functions (Part Attributes/Actions)
 *******************************************************************/

IString ICalcTally :: buffer () const
{
  return dBuffer;
}


//
// Set the Tally Chip buffer attribute.
// This attribute must be kept in sync with the calculator display.
//

ICalcTally & ICalcTally :: setBuffer
  (IString iBuffer)
{
   dBuffer = iBuffer;

   //
   // If the buffer is being cleared, make sure will attempt to send
   // the buffer to the Tally Display.  Otherwise the buffer is a
   // candidate for sending to the Tally Display.
   //

   if (dBuffer == "") dUpdateTally = false;
   else dUpdateTally = true;

   //
   // If the buffer is being updated because of some functional
   // operation as opposed to keypad input, then send this
   // string to the Tally Display.
   //

   if (dUpdateTally && dResultExpected) {
      setNextTallyLine(dBuffer);

      //
      // If there is an accompanying operator symbol, send the operator
      // symbol to the Tally Display as well.
      //

      if (dLastOperator != "") setNextTallyLine(dLastOperator);

      dUpdateTally = false;
      dResultExpected = false;
      dLastOperator = "";
   }
   
      return *this;
}


//
// Query the NextTallyLine attribute.
//

IString ICalcTally :: nextTallyLine () const
{
   return dNextTallyLine;
}


//
// Set the NextTallyLine attribute.
// Construct the actual string to be added to the Tally MLE.
// This includes the proper carriage control and notification
// of any state change of the Tally (empty to not empty).
//

ICalcTally & ICalcTally :: setNextTallyLine 
  (IString iString)
{
   if (iString != "") {

      //
      // Set the required carriage control to force MLE to add
      // lines the way I want them added and issue event indicating
      // that the line is ready to be added to the Tally Display (MLE).
      //

      if (!dEmptyMark) dNextTallyLine = "\r\n";
      else dNextTallyLine = "";

      dNextTallyLine += iString ;
      notifyObservers(INotificationEvent(nextTallyLineId, *this));

      //
      // Issue event of state change of Tally from empty to not empty
      // when appropriate.
      //

      if (dEmptyMark) {
         dEmptyMark = false;
         notifyObservers(INotificationEvent(notEmptyId, *this));
      }

   }

   return *this;
}


/***************************************************************************
 Implementor Member Functions (Part Actions)
****************************************************************************/

//
// Reset the Tally object.
//

bool ICalcTally :: reset ()
{
   dBuffer = "";
   dNextTallyLine = "";
   dUpdateTally = false;
   dProcessBinaryOp = false;
   dEmptyMark = true;
   dResultExpected = false;
   dLastOperator = "";
   return dEmptyMark;
}


//
// Process a Binary operator.
//

bool ICalcTally :: processBinaryOperator (IString iBinaryOpSym)
{
   bool updated;
    
   //
   // If there is something in the Tally Chip buffer which needs to be
   // sent to the Tally Display, then do it.
   // Otherwise indicate that the Tally Display has not been updated from the
   // Tally Chip buffer.
   //

   if (dUpdateTally) {
      setNextTallyLine(buffer());
      dUpdateTally = false;
      updated = true;
      }

   else updated = false;

   //
   // If previous operator not a binary operator, send this operator
   // symbol to the Tally Display
   //

   if (!dProcessBinaryOp) {
      setNextTallyLine(iBinaryOpSym);
      dProcessBinaryOp = true;
      dResultExpected = false;
      dLastOperator = "";
      }

   //
   // Else the previous operator was a binary operator and if Tally Display
   // was not updated from the Tally Chip Buffer, send this operator to
   // the Tally Display.  Otherwise, save this operator for later display
   // because need to display Tally Chip Buffer contents before displaying
   // the binary operator symbol associated with the buffer contents.
   //

   else {
      if (!updated) {
         setNextTallyLine(iBinaryOpSym);
         dLastOperator = "";
      }
       
      else dLastOperator = iBinaryOpSym;

      dResultExpected = true;   // Are expecting a buffer update as a result
                                // of some binary function operation.

      } 

   return updated;
}


//
// Process a Unary Operator
//

bool ICalcTally :: processUnaryOperator (IString iUnaryOpSym)
{
   bool updated;
   
   //
   // If there is something in the Tally Chip buffer which needs to be
   // sent to the Tally Display, then do it.
   // Otherwise indicate that the Tally Display has not been updated from the
   // Tally Chip buffer.
   //

   if (dUpdateTally) {
      setNextTallyLine(buffer());
      dUpdateTally = false;
      updated = true;
      }

   else updated = false;

   //
   // Send the unary operator symbol to the Tally Display.
   // Expect some update from the unary function operation.
   // No delay waiting for completion of a binary operation.
   //

   setNextTallyLine(iUnaryOpSym);
   dResultExpected = true;
   dProcessBinaryOp = false;
   
   return updated;
}

