/******************************************************************************
* .FILE:         letterdq.cpp                                                 *
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
|                                                               |
| letterdq.CPP  -  Letter Double Ended Queue                    |
|                  This is an example of using a Deque.         |
|                                                """""          |
\*-------------------------------------------------------------*/

#include <iostream.h>

#include <idqu.h>
                     // Let's use the default deque
typedef IDeque <char> Deque;
                     // The deque requires iteration to be const
typedef IConstantApplicator <char> CharApplicator;

class Print : public CharApplicator
{
public:
   IBoolean applyTo(char const&c)
      {
      cout << c;
      return True;
      }
};

/*-------------------------------------------------------------*\
| Test variables                                                |
\*-------------------------------------------------------------*/

char *String = "Teqikbonfxjmsoe  aydg.o zlarv pu o wr cu h";


/*-------------------------------------------------------------*\
| Main program                                                  |
\*-------------------------------------------------------------*/
int main()
{
   Deque D;
   char  C;
   IBoolean ReadFront = True;

   int i;

   // Put all characters in the deque.
   // Then read it, changing the end to read from
   // with every character read.

   cout << endl
        << "Adding characters to the back end of the deque:" << endl;

   for (i = 0; String[i] != 0; i ++) {
      D.addAsLast(String[i]);
      cout << String[i];
      }

   cout << endl << endl
        << "Current number of elements in the deque: "
        <<  D.numberOfElements() << endl;

   cout << endl
        << "Contents of the deque:" << endl;
   Print Aprinter;
   D.allElementsDo(Aprinter);

   cout << endl << endl
        << "Reading from the deque one element from front, one "
        << "from back, and so on:" << endl;

   while (!D.isEmpty())
      {
      if (ReadFront)                  // Read from front of Deque
         {
         C = D.firstElement();        // Get the character
         D.removeFirst();             // Delete it from the Deque
         }
      else
         {
         C = D.lastElement();
         D.removeLast();
         }
      cout << C;

      ReadFront = !ReadFront;     // Switch to other end of Deque
      }

   cout << endl;

   return(0);
}

