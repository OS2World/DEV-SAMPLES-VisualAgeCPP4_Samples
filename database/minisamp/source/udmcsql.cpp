// IBM VisualAge C++ Professional, Version 4.0
// Licensed Materials - Property of IBM
// (C) Copyright IBM Corp. 1995, 1998. All Rights Reserved.
// US Government Users Restricted Rights - Use, duplication or disclosure restricted
// by GSA ADP Schedule Contract with IBM Corp.

// Please refer to the Release Notes on how to run this sample.

#include <iostream.h>
#include "Empl.hpp"

void test( int argc, char* argv[] )
{
      // Create the Datastore and Manager objects
      EmployeeDatastore theEmpDatastore;
      EmployeeManager   theEmpMgr;
      Employee          theEmp;

      // Connect to database
      cout << "Connecting to " << theEmpDatastore.datastoreName() << "..." << endl;
      if ( argc >= 3 )
         theEmpDatastore.connect( argv[1], argv[2] );
      else
         theEmpDatastore.connect();
      theEmpDatastore.enableAutoCommit( false );
      cout <<"...Connected" << endl;

      // Count all Employees in Department D11
      int numEmp = theEmp.numEmpInDept( "D11" );
      cout << "Count of all Employees in Department D11: " << numEmp << endl;

      // Disconnect from the database
      theEmpDatastore.rollback();
      theEmpDatastore.disconnect();

      // All done
      cout << "Done" << endl;
}
