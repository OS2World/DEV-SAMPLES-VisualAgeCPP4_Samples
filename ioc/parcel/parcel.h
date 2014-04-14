/******************************************************************************
* .FILE:         parcel.h                                                     *
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
|  parcel.h  -  Class Parcel and its parts for use with the     |
|               example for Key Sorted Set and Heap.            |
\*-------------------------------------------------------------*/
#include <iostream.h>

                        // For definition of Boolean:
#include <iglobals.h>
                        // Class IString:
#include <istring.hpp>


class PlaceTime {

  IString cty;
  int   daynum;  // Keeping it simple:  January 9 is day 9

public:

  PlaceTime(IString acity, int aday) : cty(acity), daynum(aday) {}

  PlaceTime(IString acity) : cty(acity) {daynum = 0;}

  IString const& city() const {
     return cty;
  }

  int const& day() const {
     return daynum;
  }

  void operator=(PlaceTime const& pt) {
      cty = pt.cty;
      daynum = pt.daynum;
  }

  IBoolean operator==(PlaceTime const& pt)  const {
     return ( (cty == pt.cty)
           && (daynum == pt.daynum) );
  }
};


class Parcel {

  PlaceTime org, lstAr;
  IString dst, id;

public:

  Parcel(IString orig,  IString dest, int day, IString ident)
     :  org(orig, day),  lstAr(orig, day),  dst(dest), id(ident) {}

  void arrivedAt(IString const& acity, int const& day) {
     PlaceTime nowAt(acity, day);
                              // Only if not already there before
     if (nowAt.city() != lstAr.city())
        lstAr = nowAt;
  }

  void wasDelivered(int const& day) {arrivedAt(dst, day);  }

  PlaceTime const& origin() const {
     return org;
  }

  IString const& destination() const {
     return dst;
  }

  PlaceTime const& lastArrival() const {
     return lstAr;
  }

  IString const& ID() const {
     return id;
  }

  friend ostream& operator<<(ostream& os, Parcel const& p) {
    os << p.id << ": From " << p.org.city()
       << "(day "  << p.org.day() << ") to " << p.dst;

    if (p.lstAr.city() != p.dst) {
       os << endl << "            is at " << p.lstAr.city()
          << "  since day " << p.lstAr.day() << ".";
    }
    else {
       os << endl << "            was delivered on day "
          << p.lstAr.day() << ".";
    }
    return os;
  }
};

                        // Key access:
  inline  IString const& key( Parcel const&  p) {
  return p.ID();
  }
                        // We need a compare function for the key.
                        // Let's use the default provided for IString:
  inline long compare(Parcel const& p1, Parcel const& p2) {
     return compare(p1.ID(), p2.ID());
  }
