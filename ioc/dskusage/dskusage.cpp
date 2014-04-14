/******************************************************************************
* .FILE:         dskusage.cpp                                                 *
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
|  dskusage.CPP -  Disk Usage Information is handled using      |
|                  a Sorted Map and a Sorted Relation.          |
|                    """"""""""       """""""""""""""           |
|                                                               |
|  This program reads a file containing disk space usage        |
|  records 'DiskSpaceUR'. Each record is added into two         |
|  Equality Key Sorted Collections.                             |
|                                                               |
|  One of these collections, DSURbyName, is a Sorted Map.       |
|  The key is the name, which is unique.                        |
|                                                               |
|  The other collection, DSURbySpace, is a Sorted Relation.     |
|  The key is the space, which can occur multiple times.        |
|                                                               |
|  Using the iteration method allElementsDo, both Collections   |
|  then print their contents in the sorted order.               |
|                                                               |
|  Note: If we could be sure that there would never be two      |
|        identical records in the input data, it would be better|
|        to use the corresponding collections that do not need  |
|        element equality.  These are KeySorted Set and         |
|        KeySorted Bag instead of Sorted Map and                |
|        Sorted Relation.                                       |
\*-------------------------------------------------------------*/



#include "dsur.h"
                       // Our own common exit for all errors:
void errorExit(int, char*, char* = "");

                       // Use the default Sorted Map as is:
#include <ism.h>
                       // Use the default Sorted Relation as is:
#include <isr.h>

int main (int argc, char* argv[])
{ char* fspec = "dsu.dat"; // Default for input file

  if (argc > 1)   fspec = argv[1];

  ifstream  inputfile (fspec);
  if (!inputfile)
    errorExit(20, "Unable to open input file", fspec);

  ISortedMap <DiskSpaceUR, char*> dsurByName;
  ISortedMap <DiskSpaceUR, char*>::Cursor curByName (dsurByName);

  IGSortedRelation <DiskSpaceUR, int, DSURBySpaceOps>
         dsurBySpace;
  IGSortedRelation <DiskSpaceUR, int, DSURBySpaceOps>::Cursor
         curBySpace(dsurBySpace);

                           // Read all records into dsurByName
  while (inputfile.good()) {
    DiskSpaceUR dsur (inputfile);
    if (dsur.isValid ()) {
      dsurByName.add (dsur);
      dsurBySpace.add (dsur);
    }
  }
  if (! inputfile.eof ())
    errorExit (39, "Error during read of", fspec);

  cout << endl << endl
       << "All Disk Space Usage records "
       << "sorted (ascending) by name:" << endl << endl;

  forICursor (curByName)
    cout << "  " << dsurByName.elementAt (curByName) << endl;

  cout << endl << endl
       << "All Disk Space Usage records "
       << "sorted (descending) by space:" << endl << endl;

  for (curBySpace.setToLast ();
       curBySpace.isValid ();
       curBySpace.setToPrevious ())
    cout << "  " << dsurBySpace.elementAt (curBySpace) << endl;

  return 0;
}

#include <stdlib.h> // for exit () definition

void errorExit (int rc, char* s1, char* s2)
{ cerr << s1 << " " << s2 << endl;
  exit (rc);
}
