/******************************************************************************
* .FILE:         intkyset.cpp                                                 *
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
|  intkyset.CPP  -  Integer Key Set for demonstration of using  |
|                   a KeySet.                                   |
\*-------------------------------------------------------------*/
#include <iostream.h>
#include <iglobals.h>

#include <iks.h>
                      // Class DemoElement:
#include "demoelem.h"

typedef IKeySet < DemoElement,int > TestKeySet;

ostream & operator << ( ostream & sout, TestKeySet const & t)
{ sout << t.numberOfElements() << " elements are in the set:" << endl;

  TestKeySet::Cursor cursor (t);

  //  forICursor(c)
  // expands to
  //  for ((c).setToFirst (); (c).isValid (); (c).setToNext ())

  forICursor (cursor)
    sout << "   " << cursor.element () << endl;

  return sout << endl;
}


main()
{
  TestKeySet t;

  t.add(DemoElement(1,1));
  t.add(DemoElement(2,4711));
  t.add(DemoElement(3,1));
  t.add(DemoElement(4,443));

  cout << t;

  t.removeElementWithKey (3);

  cout << t;

  return 0;
}
