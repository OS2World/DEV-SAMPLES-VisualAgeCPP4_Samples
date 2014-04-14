// IBM VisualAge C++ Professional, Version 4.0
// Licensed Materials - Property of IBM
// (C) Copyright IBM Corp. 1995, 1998. All Rights Reserved.
// US Government Users Restricted Rights - Use, duplication or disclosure restricted
// by GSA ADP Schedule Contract with IBM Corp.

// Please refer to the Release Notes on how to run this sample.

#include <iostream.h>
#include <fstream.h>
#include "Photo.hpp"

void test( int argc, char* argv[] )
{
   // Create the Datastore and Manager objects
   Emp_photoDatastore  thePhotoDatastore;
   Emp_photo           thePhoto;

   if ( argc <= 1 )
   {
      cout << "Please enter an employee number." << endl;
   }
   else
   {
      // Connect to database
      cout << "Connecting to " << thePhotoDatastore.datastoreName() << "..." << endl;
      if ( argc >= 4 )
         thePhotoDatastore.connect( argv[2], argv[3] );
      else
         thePhotoDatastore.connect();
      thePhotoDatastore.enableAutoCommit( false );
      cout <<"...Connected" << endl;

      thePhoto.setEmpno( argv[1] );
      thePhoto.setPhoto_format( "gif" );
      try
      {
         thePhoto.retrieve();
         thePhoto.picture().putContentsToFile( IString(argv[1]) + ".gif" );
         cout << "Gif for " << argv[1]
              << " has been retrieved into file "
              << IString(argv[1]) << ".gif"
              << endl;
      }
      catch( IException& s )
      {
         cout << s.text() << endl;
         cout << "Gif for " << argv[1] << " not found." << endl;
      }
      // Disconnect from the database
      thePhotoDatastore.rollback();
      thePhotoDatastore.disconnect();

      // All done
      cout << "Done" << endl;
   }
}
