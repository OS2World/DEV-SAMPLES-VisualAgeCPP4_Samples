// IBM VisualAge C++ Professional, Version 4.0
// Licensed Materials - Property of IBM
// (C) Copyright IBM Corp. 1995, 1998. All Rights Reserved.
// US Government Users Restricted Rights - Use, duplication or disclosure restricted
// by GSA ADP Schedule Contract with IBM Corp.

// Please refer to the Release Notes on how to run this sample.

#include <iostream.h>
#include <iexcbase.hpp>

void test( int argc, char* argv[] );

int main( int argc, char* argv[] )
{
   try
   {
      test( argc, argv );
   }
   // Catch all Exceptions here and print out what information we can.
   catch (const IException& ss)
   {
      cout << "Exception caught:" << endl ;
      cout << "message: " << ss.text() << endl ;
   }
   return 0;
}
