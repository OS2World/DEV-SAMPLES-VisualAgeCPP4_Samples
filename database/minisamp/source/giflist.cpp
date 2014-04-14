// IBM VisualAge C++ Professional, Version 4.0
// Licensed Materials - Property of IBM
// (C) Copyright IBM Corp. 1995, 1998. All Rights Reserved.
// US Government Users Restricted Rights - Use, duplication or disclosure restricted
// by GSA ADP Schedule Contract with IBM Corp.

// Please refer to the Release Notes on how to run this sample.

#include <iostream.h>
#include "Photo.hpp"

void test( int argc, char* argv[] )
{
      // Create the Datastore and Manager objects
      Emp_photoDatastore     thePhotoDatastore;
      Emp_photoDataIdManager thePhotoIdMgr;

      // Connect to database
      cout << "Connecting to " << thePhotoDatastore.datastoreName() << "..." << endl;
      if ( argc >= 3 )
         thePhotoDatastore.connect( argv[1], argv[2] );
      else
         thePhotoDatastore.connect();
      thePhotoDatastore.enableAutoCommit( false );
      cout <<"...Connected" << endl;

      thePhotoIdMgr.openListGifs( "" );
      cout << "The following gifs are in the database." << endl;
      while( thePhotoIdMgr.fetchNext() )
      {
        cout << thePhotoIdMgr.element()->empno() << endl;
      }
      thePhotoIdMgr.close();

      // Disconnect from the database
      thePhotoDatastore.rollback();
      thePhotoDatastore.disconnect();

      // All done
      cout << "Done" << endl;
}
