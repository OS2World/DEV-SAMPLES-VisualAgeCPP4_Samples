/******************************************************************************
* .FILE:         pushpop.cpp                                                  *
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
| pushpop.CPP  -  Simple example for the use of the Stack.      |
|                                                   """""       |
\*-------------------------------------------------------------*/

#include <string.h>
#include <iostream.h>
                      // Let's use the default stack: IStack
#include <istk.h>

typedef IStack <char*> SimpleStack;
                      // The stack requires iteration to be const.
typedef IConstantApplicator <char*> StackApplicator;


/*-------------------------------------------------------------*\
* Test variables to put into our Stack:                         *
\*-------------------------------------------------------------*/

char *String[9] = {
   "The",
   "quick",
   "brown",
   "fox",
   "jumps",
   "over",
   "a",
   "lazy",
   "dog."
};


/*-------------------------------------------------------------*\
* A class to display the contents of our Stack:                 *
\*-------------------------------------------------------------*/

class PrintClass : public StackApplicator
{
public:
   IBoolean applyTo(char* const& w)
      {
      cout << w << endl;
      return(True);
      }
};


/*-------------------------------------------------------------*\
* Main program                                                  *
\*-------------------------------------------------------------*/
int main()
{
   SimpleStack Stack1, Stack2;
   char *S;
   PrintClass Print;

   // We specify two stacks.
   // First all the strings are pushed onto the first stack.
   // Next, they are popped from the first and pushed onto
   // the second.
   // Finally they are popped from the second and printed.
   // During this final print the strings must appear
   // in their original order.

   int i;

   for (i = 0; i < 9; i ++) {
      Stack1.push(String[i]);
      }

   cout << "Contents of Stack1:" << endl;
   Stack1.allElementsDo(Print);
   cout << "----------------------------" << endl;

   while (!Stack1.isEmpty()) {
      Stack1.pop(S);             // Pop from stack 1
      Stack2.push(S);            // Add it on top of stack 2
      }

   cout << "Contents of Stack2:" << endl;
   Stack2.allElementsDo(Print);
   cout << "----------------------------" << endl;

   while (!Stack2.isEmpty()) {
      Stack2.pop(S);
      cout << "Popped from Stack 2: " << S << endl;
      }

   return(0);
}


