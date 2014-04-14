/******************************************************************************
* .FILE:         animal.h                                                     *
*                                                                             *
* .DESCRIPTION:  Class Animal for use with the example animals.C              *
*                                                                             *
* .CLASSES:      Animal                                                       *
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


  #include <iglobals.h>           // For definition of Boolean:
  #include <istring.hpp>          // Class IString:
  #include <iostream.h>

class Animal {
  IString nm;
  IString attr;

public:

  Animal(IString n, IString a) : nm(n), attr(a)  {}

  // For copy constructor we use the compiler generated default.

  // For assignment we use the compiler generated default.

  IBoolean operator==(Animal const& p) const  {
     return  ((nm == p.name()) && (attr == p.attribute()));
  }

  IString const& name() const {
     return nm;
  }

  IString const& attribute() const {
     return attr;
  }

  friend ostream& operator<<(ostream& os, Animal const& p)  {
     return os << "The " << p.name() << " is " << p.attribute()
     << "." << endl;
  }

};

  // Key access:
inline IString const& key(Animal const& p)  {
  return p.name();
}

  // We need a hash function for the key type as well.
  // Let's just use the default provided for IString.
inline unsigned long hash(Animal const& animal, unsigned long n) {
  return hash(animal.name(), n);
}
