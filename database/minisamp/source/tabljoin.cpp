// IBM VisualAge C++ Professional, Version 4.0
// Licensed Materials - Property of IBM
// (C) Copyright IBM Corp. 1995, 1998. All Rights Reserved.
// US Government Users Restricted Rights - Use, duplication or disclosure restricted
// by GSA ADP Schedule Contract with IBM Corp.

// Please refer to the Release Notes on how to run this sample.

#include <iostream.h>
#include "Join.hpp"

void test( int argc, char* argv[] )
{
      // Create the Datastore and Manager objects
      JoinDatastore theJoinDatastore;
      JoinManager   theJoinMgr;

      // Connect to database
      cout << "Connecting to " << theJoinDatastore.datastoreName() << "..." << endl;
      if ( argc >= 3 )
         theJoinDatastore.connect( argv[1], argv[2] );
      else
         theJoinDatastore.connect();
      theJoinDatastore.enableAutoCommit( false );
      cout <<"...Connected" << endl;

      cout << "Listing of all Rows:" << endl;

      // Open the cursor on the entire database,
      theJoinMgr.open( "" );

      // Repeat for each row
      while( theJoinMgr.fetchNext() )
      {
         // Print out the row
         cout << theJoinMgr.element()->asString() << endl;
      }

      // close the cursor
      theJoinMgr.close();

      // Disconnect from the datastore
      theJoinDatastore.rollback();
      theJoinDatastore.disconnect();

      // All done
      cout << "Done" << endl;
}
