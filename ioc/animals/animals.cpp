/******************************************************************************
* .FILE:         animal.cpp                                                   *
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
/*------------------------------------------------------------*\
| animals.CPP  -  Example for the use of the Key Bag           |
|                                            """""""           |
| We keep a Key Bag of our observations on animals.  Elements  |
| handled in this Key Bag are of type animal, the key is the   |
| name of the animal.                                          |
| This Key Bag allows us to efficiently access all observations|
| on an animal.                                                |
| We use a Sequence to store the names of all extinct animals. |
| At last we remove all extinct animals from the Key Bag.      |
\*------------------------------------------------------------*/

#include <iostream.h>
               // Class Animal:
#include "animal.h"

               // Let's use the default Key Bag:
#include <ikb.h>
typedef IKeyBag<Animal, IString> Animals;

               // For keys let's use the default Sequence:
#include <iseq.h>
typedef ISequence<IString> Names;


main() {

   Animals animals;
   Animals::Cursor animalsCur1(animals), animalsCur2(animals);

   animals.add(Animal("bear", "heavy"));
   animals.add(Animal("bear", "strong"));
   animals.add(Animal("dinosaur", "heavy"));
   animals.add(Animal("dinosaur", "huge"));
   animals.add(Animal("dinosaur", "extinct"));
   animals.add(Animal("eagle", "black"));
   animals.add(Animal("eagle", "strong"));
   animals.add(Animal("lion", "dangerous"));
   animals.add(Animal("lion", "strong"));
   animals.add(Animal("mammoth", "long haired"));
   animals.add(Animal("mammoth", "extinct"));
   animals.add(Animal("sabre tooth tiger", "extinct"));
   animals.add(Animal("zebra", "striped"));

                 // Display all elements in animals:
   cout << endl
        << "All our observations on animals:" << endl;
   forICursor(animalsCur1)  cout << "    " << animalsCur1.element();

   cout << endl << endl
        << "Number of observations on animals: "
        << animals.numberOfElements() << endl;

   cout << endl
        << "Number of different animals: "
        << animals.numberOfDifferentKeys() << endl;

   Names namesOfExtinct(animals.numberOfDifferentKeys());
   Names::Cursor extinctCur1(namesOfExtinct);

   animalsCur1.setToFirst();
   do {
      IString name = animalsCur1.element().name();

      cout << endl
           << "We have " << animals.numberOfElementsWithKey(name)
           << " observations on " << name << ":" << endl;

                   // We need to use a separate cursor here
                   // because otherwise animalsCur1 would become
                   // invalid after last locateNextElement...()
      animals.locateElementWithKey(name, animalsCur2);
      do  {
         IString attribute = animalsCur2.element().attribute();
         cout << "    " << attribute << endl;
         if (attribute == "extinct") namesOfExtinct.add(name);
      } while (animals.locateNextElementWithKey(name, animalsCur2));

   } while (animals.setToNextWithDifferentKey(animalsCur1));

                 // Remove all observations on extinct animals:
   forICursor(extinctCur1)
      animals.removeAllElementsWithKey(extinctCur1.element());

                 // Display all elements in animals:
   cout << endl << endl
        << "After removing all observations on extinct animals:"
        << endl;
   forICursor(animalsCur1)  cout << "    " << animalsCur1.element();

   cout << endl
        << "Number of observations on animals: "
        << animals.numberOfElements() << endl;

   cout << endl
        << "Number of different animals: "
        << animals.numberOfDifferentKeys() << endl;

   return 0;
}
