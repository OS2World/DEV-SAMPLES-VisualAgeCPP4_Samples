/******************************************************************************
* .FILE:         parcel.cpp                                                   *
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
| parcel.CPP  -  Parcels are handled using  a  KeySorted Set and |
|                a Heap.                       """""""""""""     |
|                  """"                                          |
| We maintain two collections that keep track of parcels in      |
| circulation and parcels delivered.  The collection for the     |
| parcels in circulation is a KeySorted Set (key, sorted,        |
| unique elements, no element equality).  For the delivered      |
| parcels we do not care about fast or sorted retrieval.         |
| So we select the Heap for this collection (no key, unordered,  |
| multiple elements, no element equality).                       |
|                                                                |
| A parcel has as member data two objects of type PlaceTime,     |
| which is a point in space and time: one object for its origin, |
| one for its current place and time. It also has as member      |
| data two objects of type IString, for the destination and      |
| for the ID.                                                    |
|                                                                |
| Function updateParcels adds parcels that have arrived at       |
| their destination to the collection for delivered parcels,     |
| and removes them from the collection of circulating parcels.   |
| This demonstrates the use of removeAll().                      |
|                                                                |
\*--------------------------------------------------------------*/
#include <iostream.h>

#include "parcel.h"
                          // Let's use the default KeySorted Set:
#include <ikss.h>
                          // Let's use the default Heap:
#include <ihp.h>

typedef IKeySortedSet<Parcel, IString> ParcelSet;
typedef IHeap        <Parcel>            ParcelHeap;

ostream& operator<<(ostream&, ParcelSet const&);
ostream& operator<<(ostream&, ParcelHeap const&);

void update(ParcelSet&, ParcelHeap&);


main()  {

  ParcelSet circulating;
  ParcelHeap delivered;

  int today = 8;

  circulating.add(Parcel("London", "Athens",
     today,      "26LoAt"));
  circulating.add(Parcel("Amsterdam", "Toronto",
     today += 2, "27AmTo"));
  circulating.add(Parcel("Washington", "Stockholm",
     today += 5, "25WaSt"));
  circulating.add(Parcel("Dublin", "Kairo",
     today += 1, "25DuKa"));
  update(circulating, delivered);
  cout << endl << "The situation at start:" << endl;
  cout << "Parcels in circulation:" << endl << circulating;

  today ++;
  circulating.elementWithKey("27AmTo").arrivedAt(
     "Atlanta",   today);
  circulating.elementWithKey("25WaSt").arrivedAt(
     "Amsterdam", today);
  circulating.elementWithKey("25DuKa").arrivedAt(
     "Paris",     today);
  update(circulating, delivered);
  cout << endl << endl << "The situation at day " << today << ":"
       << endl;
  cout << "Parcels in circulation:" << endl << circulating;

  today ++;          // One day later ...
  circulating.elementWithKey("27AmTo").arrivedAt("Chicago", today);
             // As in real life, one parcel gets lost:
  circulating.removeElementWithKey("26LoAt");
  update(circulating, delivered);
  cout << endl << endl << "The situation at day " << today << ":"
       << endl;
  cout << "Parcels in circulation:" << endl << circulating;

  today ++;
  circulating.elementWithKey("25WaSt").arrivedAt("Oslo", today);
  circulating.elementWithKey("25DuKa").arrivedAt("Kairo", today);
             // New parcels are shipped.
  circulating.add(Parcel("Dublin", "Rome", today,   "27DuRo"));
             // Let's try to add one with a key already there.
             // The KeySsorted Set should ignore it:
  circulating.add(Parcel("Nowhere", "Nirvana", today, "25WaSt"));
  update(circulating, delivered);
  cout << endl << endl << "The situation at day " << today << ":"
       << endl;
  cout << "Parcels in circulation:" << endl << circulating;
  cout << "Parcels delivered:" << endl << delivered;

                   // Now we make all parcels arrive today:
  today ++;

  ParcelSet::Cursor circulatingcursor(circulating);
  forICursor(circulatingcursor) {
     circulating.elementAt(circulatingcursor).wasDelivered(today);
  }
  update(circulating, delivered);
  cout << endl << endl << "The situation at day " << today << ":"
       << endl;
  cout << "Parcels in circulation:" << endl << circulating;
  cout << "Parcels delivered:" << endl << delivered;

  if (circulating.isEmpty())
     cout << endl << "All parcels were delivered." << endl;
  else
     cout << endl << "Something very strange happened here." << endl;

  return  0;
}


ostream& operator<<(ostream& os, ParcelSet const& parcels)  {
  ParcelSet::Cursor pcursor(parcels);
  forICursor(pcursor) {
     os <<  pcursor.element() << endl;
  }
  return os;
}

ostream& operator<<(ostream& os, ParcelHeap const& parcels)  {
  ParcelHeap::Cursor pcursor(parcels);
  forICursor(pcursor) {
     os <<  pcursor.element() << endl;
  }
  return os;
}

IBoolean wasDelivered(Parcel const& p, void* dp) {
   if ( p.lastArrival().city() == p.destination() ) {
      ((ParcelHeap*)dp)->add(p);
      return True;
   }
   else
      return False;
}

void update(ParcelSet& p, ParcelHeap& d) {
   p.removeAll(wasDelivered, &d);
}
