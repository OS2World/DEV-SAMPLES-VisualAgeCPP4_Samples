/******************************************************************************
* .FILE:         demoelem.h                                                   *
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
|  demoelem.h  -  DemoElement for use with Key Collections      |
\*-------------------------------------------------------------*/
#ifndef _DEMOELEM_H
#define _DEMOELEM_H

#include <stdlib.h>
#include <iglobals.h>
#include <iostream.h>
#include <istdops.h>

class DemoElement {

  int i;
  int j;

public:

           DemoElement ()
           : i(0), j(0)
           {
           }

           DemoElement (int i,int j)
           : i (i), j(j)
           {
           }

           operator int () const
           { return i;
           }

  IBoolean operator == (DemoElement const& k) const
           { return i == k.i && j == k.j;
           }

  IBoolean operator < (DemoElement const& k) const
           { return i < k.i || (i == k.i && j < k.j);
           }

  friend unsigned long
           hash (DemoElement const& k, unsigned long n)
           { return k.i % n;
           }

  int const &
           geti () const
           { return i;
           }

  int const &
           getj () const
           { return j;
           }

};

inline ostream & operator << (ostream &sout, DemoElement const& e)
{ sout << e.geti () << "," << e.getj ();
  return sout;
}

inline int const& key (DemoElement const& k)
{ return k.geti ();
}

// NOTE: You must return a const & in the key function!
// Otherwise the implicitly created standard element operations
// will return a reference to a temporary. This would lead to
// incorrect behavior of the collection operations.

// The key function must be declared in the header file of
// the collection's element type.

// If either of these is not possible or undesirable,
// an element operations class must be used.

#endif
