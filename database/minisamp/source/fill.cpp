// IBM VisualAge C++ Professional, Version 4.0
// Licensed Materials - Property of IBM
// (C) Copyright IBM Corp. 1995, 1998. All Rights Reserved.
// US Government Users Restricted Rights - Use, duplication or disclosure restricted
// by GSA ADP Schedule Contract with IBM Corp.

// Please refer to the Release Notes on how to run this sample.

#include <iostream.h>
#include "Dept.hpp"

void test( int argc, char* argv[] )
{
      // Create the Datastore and Manager objects
      DepartmentDatastore theDepartmentDatastore;
      DepartmentManager   theDeptMgr;

      // Connect to database
      cout << "Connecting to " << theDepartmentDatastore.datastoreName() << "..." << endl;
      if ( argc >= 3 )
         theDepartmentDatastore.connect( argv[1], argv[2] );
      else
         theDepartmentDatastore.connect();
      theDepartmentDatastore.enableAutoCommit( false );
      cout <<"...Connected" << endl;

      cout << "Listing of all departments, sorted by name:" << endl;

      // Open the cursor on the entire database,
      // ordering the records by department name
      theDeptMgr.open( "ORDER BY DEPTNAME" );

      // Fetch all the rows
      theDeptMgr.fill( 0 );
      IVSequence<Department*>::Cursor csr( *theDeptMgr.items() );

      // loop through the items
      forCursor( csr )
      {
         // Get the row out of the vector
         Department * theDept = csr.element();

         // Print out the row
            cout << theDept->asString() << endl;
      }

      // close the cursor
      theDeptMgr.close();

      // Disconnect from the database
      theDepartmentDatastore.rollback();
      theDepartmentDatastore.disconnect();

      // All done
      cout << endl << "Done" << endl;
}
