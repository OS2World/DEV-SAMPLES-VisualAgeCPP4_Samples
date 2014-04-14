/******************************************************************************
* .FILE:         litems.hpp                                                   *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Definition       *
*                                                                             *
* .CLASSES:      Item                                                         *
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
#ifndef _LITEMS_
#define _LITEMS_

#include <iostream.h>

#include <istring.hpp>
#include <ikeybag.h>
#include <ibag.h>

// forward declaration
class Itemb;
class Item;
class Entry;

typedef IBag<IString> ItemsBag;
typedef IKeyBag<Item, Entry> Items;


#include <istring.hpp>
#include <iglobals.h>

                             // Class lentry:
#include "lentry.hpp"


//----------------------------------------------------------------------------
// class Item
//----------------------------------------------------------------------------
class Item
{

public: // ---------------------- PUBLIC -------------------------------------

enum Rule {
           na,
           file,
           add,
           replace,
           remove
           };

//----------------------- Contructor/Destructor ------------------------------
// Class Item:: Item()
//----------------------------------------------------------------------------
  Item(char *a
     , char *b=(char *)""
     , char *c=(char *)""
     , char *d=(char *)""
     , char *e=(char *)""
  ) : i1(a), i2(b), i3(c), i4(d), i5(e), stat(na)  {};

  Item(Rule s,
       char *a
       , char *b
       , char *c=(char *)""
       , char *d=(char *)""
       , char *e=(char *)""
  ) : stat(s),
      i1(a), i2(b), i3(c), i4(d), i5(e) {};

  // For copy constructor we use the compiler generated default.

  // For assignment we use the compiler generated default.

inline bool operator==(Item const& p) const  {
       return  (
                ((i1 == p.i1) &&
                 (i2 == p.i2) &&
                 (i3 == p.i3) &&
                 (i4 == p.i4) &&
                 (i5 == p.i5)) );
       };

inline Entry const& item1() const { return i1; };

inline Entry const& item2() const { return i2; };

inline  Entry const& item3() const { return i3; };

inline  Entry const& item4() const { return i4; };

inline  Entry const& item5() const { return i5; };

inline  Rule  rule() const { return stat; };

inline  IString  sRule() const {

     switch (stat) {
        case  (na):
           return (IString("na"));
        case (file):
           return (IString("file"));
        case (add):
           return (IString("add"));
        case (replace):
           return (IString("replace"));
        case (remove):
           return (IString("remove"));
     }
     return (IString("ERROR"));
   };

friend ostream& operator<<(ostream& os, Item const& p)  {
     return os << "> Item1 <" << p.item1().text()
               << "> Item2 <" << p.item2().text()
               << "> Item3 <" << p.item3().text()
               << "> Item4 <" << p.item4().text()
               << "> Item5 <" << p.item5().text()
               << " rule = " << p.sRule() << "> \n";

};

private: //----------------------- Private --------------------------------------------

// replace with IStrings..

Entry
  i1,
  i2,
  i3,
  i4,
  i5;

Rule
  stat;

};

// Key access:
inline Entry const& key(Item const& p)  {
  return p.item1();
}

// We need a hash function for the key type as well.
// Let's just use the default provided for char*.

inline unsigned long hash(Entry const& ts, unsigned long n) {
  return hash(ts.text(), n);
}

#endif
