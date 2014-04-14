/******************************************************************************
* .FILE:         evenodd.cpp                                                  *
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
/*--------------------------------------------------------------*\
|                                                                |
|  evenodd.CPP  -  Even and Odd numbers are handled in different |
|                  Sets do demonstrate using Sets.               |
|                                            """                 |
\*--------------------------------------------------------------*/

#include <iostream.h>

#include <iset.h>        // Take the defaults for the Set and for
                         // the required functions for integer
typedef ISet <int> IntSet;

/*-------------------------------------------------------------*\
| For iteration we want to use an object of an iterator class   |
\*-------------------------------------------------------------*/
class PrintClass : public IIterator<int>  {
  public:
    virtual IBoolean applyTo(int& i)
      { cout << " " << i << " "; return True;}
};


/*-------------------------------------------------------------*\
| Local prototype for the function to display an IntSet.        |
\*-------------------------------------------------------------*/
void    List(char *, IntSet &);


/*-------------------------------------------------------------*\
| Main program                                                  |
\*-------------------------------------------------------------*/
int main ()  {
   IntSet odd, prime;
   IntSet oddPrime, evenPrime;

   int One = 1, Two = 2, Three = 3, Five = 5, Seven = 7, Nine = 9;

// Fill odd set with odd integers < 10
   odd.add( One );
   odd.add( Three );
   odd.add( Five );
   odd.add( Seven );
   odd.add( Nine );
   List("Odds less than 10:  ", odd);

// Fill prime set with primes < 10
   prime.add( Two );
   prime.add( Three );
   prime.add( Five );
   prime.add( Seven );
   List("Primes less than 10:  ", prime);

// Intersect 'Odd' and 'Prime' to give 'OddPrime'
   oddPrime.addIntersection( odd, prime);
   List("Odd primes less than 10:  ", oddPrime);

// Subtract all 'Odd' from 'Prime' to give 'EvenPrime'
   evenPrime.addDifference( prime, oddPrime);
   List("Even primes less than 10:  ", evenPrime);

   return(0);
}

/*-------------------------------------------------------------*\
| Local function to display an IntSet.                          |
\*-------------------------------------------------------------*/

void List(char *Message, IntSet &anIntSet)  {
   PrintClass Print;

   cout << Message;
   anIntSet.allElementsDo(Print);
   cout << endl;
}

