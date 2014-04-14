/******************************************************************************
* .FILE:         wordseq.cpp                                                  *
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
|  wordseq.CPP  -  Example for using the Sequence.              |
|                                        """"""""               |
|  This Sequence is used to handle elements of type Word.       |
|                                                               |
|  This example also demonstrates two different ways of         |
|  iteration, using an object of an applicator class            |
|  and using a cursor.                                          |
\*-------------------------------------------------------------*/

#include <iostream.h>

              // Get definition and declaration of class Word:
#include "toyword.h"

              // Define a compare function to be used for sort:
inline long wordCompare ( Word const& w1, Word const& w2) {
   return (w1.getWord() > w2.getWord());
}

/*-------------------------------------------------------------*\
|  We want to use the default Sequence called ISequence.        |
\*-------------------------------------------------------------*/
#include <iseq.h>

typedef ISequence <Word> WordSeq;
typedef IApplicator <Word> WordApplicator;


/*-------------------------------------------------------------*\
|  Our Applicator class for use with allElementsDo().           |
|                                                               |
|  The alternative method of iteration, using a cursor, does    |
|  not need such an applicator class. If you want to see        |
|  this alternative, search for occurences of cursor below.     |
|                                             """"""            |
\*-------------------------------------------------------------*/
class PrintClass : public WordApplicator
{
public:
   IBoolean applyTo(Word &w)
      {
      cout << endl << w.getWord();    // Print the string
      return(True);
      }
};




/*-------------------------------------------------------------*\
| Main program                                                  |
\*-------------------------------------------------------------*/
int main()  {

   IString wordArray [9] = {
      "the",    "quick",   "brown",   "fox",   "jumps",
      "over",   "a",       "lazy",    "dog"
   };

   WordSeq WL;
   WordSeq::Cursor cursor(WL);
   PrintClass Print;

   int i;

   for (i = 0; i < 9; i ++) {     // Put all strings into Sequence
      Word aWord(wordArray[i]);   // Fill object with right value
      WL.addAsLast(aWord);        // Add it to the Sequence at end
   }

   cout << endl << "Sequence in initial order:" << endl;
   WL.allElementsDo(Print);

   WL.sort(wordCompare);       // Sort the Sequence ascending
   cout << endl << endl << "Sequence in sorted order:" << endl;
   WL.allElementsDo(Print);

   // Use iteration via cursor now:

   cout << endl << endl << "Look for \"fox\" in the Sequence:" << endl;
   for (cursor.setToFirst();
        cursor.isValid() && (WL.elementAt(cursor).getWord() != "fox");
        cursor.setToNext());

   if (WL.elementAt(cursor).getWord() != "fox") {
       cout << endl << "The element was not found." << endl;
   }
   else {
       cout << endl << " The element was found." << endl;
   }

   cout << endl << "The element at position 9: "
        << WL.elementAtPosition(9).getWord()
        << endl;

   return(0);
}

