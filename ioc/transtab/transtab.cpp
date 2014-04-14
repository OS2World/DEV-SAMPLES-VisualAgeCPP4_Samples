/******************************************************************************
* .FILE:         transtab.cpp                                                 *
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
|  transtab.CPP  -  Translation table to demonstrate using a Map  |
|                                                            """  |
|  This example demontrates the use of a Map through a            |
|  bidirectional mapping between the 256 EBCDIC characters and    |
|  the 256 ASCII code points.                                     |
|                                                                 |
|  We build a map with 256 elements, each of which has            |
|  an ebcCode and an ascCode.                                     |
|  For EBCDIC-ASCII translation we want key access with           |
|  ebcCode as key,                                                |
|  for ASCII-EBCDIC translation we want key access with           |
|  ascCode as key.                                                |
|  Therefore this example demonstrates the principle of using     |
|  different keys on the same element type when stored in         |
|  different collections.                                         |
|                                                                 |
|  What you can learn from this example:                          |
|  -------------------------------------                          |
|  - What to do to use the map abstraction.                       |
|  - How to specify the required element functions in two ways:   |
|     1. defining operators for the element to store in the map   |
|     2. defining an operation class that contains                |
|        element and key functions                                |
|  - How to use the same element with different keys in           |
|    different maps.                                              |
|                                                                 |
|  This example does not show the most efficient way of           |
|  implementing an ASCII-EBCDIC translation.                      |
|                                                                 |
\*---------------------------------------------------------------*/

#include "transelm.h"

       // Get the standard operation classes:
#include <istdops.h>

#include "trmapops.h"

       //    char const translationTable[256] =  ....
#include "xebc2asc.h"

/*-------------------------------------------------------------*\
|  Now we define the two Map templates and two maps.            |
|  We want both of them to be based on the Hashtable KeySet.    |
\*-------------------------------------------------------------*/
#include <imaphsh.h>

typedef IGMapAsHshTable
          < TranslationElement, char, TranslationOpsE2A >  TransE2AMap;

typedef IGMapAsHshTable
          < TranslationElement, char, TranslationOpsA2E >  TransA2EMap;

void display(char*, char*);

int main(int argc, char* argv[])  {

   TransA2EMap  A2EMap;
   TransE2AMap  E2AMap;

       /*-----------------------------------------------------*\
       |  Load the translation table into both maps.           |
       |  The maps organize themselves according to the key    |
       |  specification already given.                         |
       \*-----------------------------------------------------*/
   int i;
   for (i=0; i < 256; i++)
   {
                       /*      ascCode          ebcCode      */
      TranslationElement te(translationTable[i],   i   );

      E2AMap.add(te);
      A2EMap.add(te);
   }
       // What do we want to convert now?
   char* toConvert;
   if  (argc > 1)  toConvert = argv[1];
   else            toConvert = "$7  (=Dollar seven)";

   size_t textLength = strlen(toConvert) +1;

   char* convertedToAsc = new char[textLength];
   char* convertedToEbc = new char[textLength];

       // Convert the strings in place, character by character
   for (i=0; toConvert[i] != 0x00; i++)   {
      convertedToAsc[i]
        = E2AMap.elementWithKey(toConvert[i]).ascCode ();
      convertedToEbc[i]
        = A2EMap.elementWithKey(toConvert[i]).ebcCode ();
   }

   display("To convert", toConvert);
   display("After EBCDIC-ASCII conversion", convertedToAsc);
   display("After ASCII-EBCDIC conversion", convertedToEbc);

   delete[] convertedToAsc;
   delete[] convertedToEbc;

   return 0;
}

#include <iostream.h>
#include <iomanip.h>

void display (char* title, char* text)  {
  cout << endl << title << ':' << endl;
  cout << "  Text: '" << text << "'" << endl;
  cout << "  Hex:   " << hex;
  for (int i=0; text[i] != 0x00; i++)    {
     cout << (int)(unsigned char) text[i] << " ";
  }
  cout << dec << endl;
}
