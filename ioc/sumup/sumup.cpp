/******************************************************************************
* .FILE:         sumup.cpp                                                    *
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
|  sumup.CPP  - Sum up integers to demonstrate using iterators. |
|                                                    """""""""  |
|  Add all elements in a bag to demonstrate the use of          |
|  iterators with additional arguments.                         |
|  The bag elements are integers passed as arguments to main(). |
\*-------------------------------------------------------------*/

   #include <ibag.h>
   #include <iostream.h>
   #include <stdlib.h>

   typedef IBag <int> IntBag;

   class SumApplicator : public IConstantApplicator <int> {
     int ivSum;
   public:
     SumApplicator () : ivSum (0) {}
     IBoolean applyTo (int const& i) {
       ivSum += i;
       return True;
     }
     int sum () { return ivSum; }
   };


   int sumUsingApplicatorObject (IntBag const& bag) {
     SumApplicator sumUp;
     bag.allElementsDo (sumUp);
     return sumUp.sum ();
   }


   IBoolean sumUpFunction (int const& i, void* sum) {
     *(int*)sum += i;
     return True;
   };

   int sumUsingApplicatorFunction (IntBag const& bag) {
     int sum = 0;
     bag.allElementsDo (sumUpFunction, &sum);
     return sum;
   }


int main (int argc, char* argv[])  {
     IntBag intbag;
     for (int cnt=1; cnt < argc; cnt++)
        intbag.add(atoi(argv[cnt]));

     cout << "Sum obtained using an Applicator Object = "
          <<  sumUsingApplicatorObject(intbag)  << endl;

     cout << "Sum obtained using an Applicator Function = "
          <<  sumUsingApplicatorFunction(intbag)  << endl;

     return 0;
     }
