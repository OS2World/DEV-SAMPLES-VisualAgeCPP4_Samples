/******************************************************************************
* .FILE:         wordbag.cpp                                                  *
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

/*---------------------------------------------------------------*\
|  wordbag.CPP  -  Word Bag, example for the use of the           |
|                  Key Sorted Bag to perform statistics on words. |
|                  """"""""""""""                                 |
|  The elements handled in the collections are the words of a     |
|  phrase. The key of each word is the number of its letters.     |
|  The Key Sorted Bag will store all occurences of each key.      |
|  We use this to calculate the number of n-letter words in       |
|  the phrase.                                                    |
|                                                                 |
\*---------------------------------------------------------------*/

   #include <iostream.h>
                                // Class Word
   #include "toyword.h"
                                // Let's use the defaults:
   #include <iksb.h>

   typedef IKeySortedBag <Word, unsigned> WordBag;


int main()
{
   IString    phrase[10] = {"people", "who", "live", "in", "glass",
                   "houses", "should", "not", "throw", "stones"};
   const size_t phraseWords = sizeof(phrase) / sizeof(IString);

   WordBag wordbag(phraseWords);

   for (int cnt=0; cnt < phraseWords; cnt++)  {
    unsigned keyValue = phrase[cnt].length();
    Word theWord(phrase[cnt],keyValue);
    wordbag.add (theWord);
   }

   cout << "Contents of our WordBag sorted by number of letters:"
        << endl;

   WordBag::Cursor wordBagCursor(wordbag);
   forICursor(wordBagCursor)
     cout << "WB: " << wordBagCursor.element().getWord() << endl;

   cout << endl << "Our phrase has " << phraseWords << " words."
        << endl;

   cout << "In our WordBag are " << wordbag.numberOfElements()
        << " words." << endl << endl;

   cout << "There are " << wordbag.numberOfDifferentKeys()
        << " different word lengths." << endl << endl;

   wordBagCursor.setToFirst();
   do  {
      unsigned letters = wordbag.key(wordBagCursor.element());
      cout << "There are "
           << wordbag.numberOfElementsWithKey(letters)
           << " words with " << letters << " letters." << endl;
   }  while  (wordbag.setToNextWithDifferentKey(wordBagCursor));

   return 0;
}
