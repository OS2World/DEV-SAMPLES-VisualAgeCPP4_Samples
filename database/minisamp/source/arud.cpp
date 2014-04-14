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
      Department          theDept;

      // Connect to database
      cout << "Connecting to " << theDepartmentDatastore.datastoreName() << "..." << endl;
      if ( argc >= 3 )
         theDepartmentDatastore.connect( argv[1], argv[2] );
      else
         theDepartmentDatastore.connect();
      theDepartmentDatastore.enableAutoCommit( false );
      cout <<"...Connected" << endl;

      // List all departments as they are
      cout << endl << "Listing of all departments, sorted by name:" << endl;
      theDeptMgr.open( "ORDER BY DEPTNAME" );
      while( theDeptMgr.fetchNext() )
      {
         cout << theDeptMgr.element()->asString() << endl;
      }
      theDeptMgr.close();

      // Add a new Department
      cout << endl << " Add a new Department '031'" << endl;
      theDept.setDeptno(   "031" );
      theDept.setDeptname( "Data Access Builder Team    " );
      theDept.setMgrno(    "154326" );
      theDept.setAdmrdept( "71" );
      theDept.setLocation( "North York" );
      theDept.add();
      // List all departments again to show changes
      cout <<"Listing of all departments, after add:" << endl;
      theDeptMgr.open( "ORDER BY DEPTNAME" );
      while( theDeptMgr.fetchNext() )
      {
          cout << theDeptMgr.element()->asString() << endl;
      }
      theDeptMgr.close();

      // update a Department
      cout << endl << " Update Department 031" << endl;
      theDept.setDeptno(   "031" );
      theDept.setDeptname( "New DAX Team" );
      theDept.setMgrno(    "123" );
      theDept.setAdmrdept(   "IBM" );
      theDept.setLocation( "Toronto Lab" );
      theDept.update();
      cout <<"Listing of all departments, after update:" << endl;
      theDeptMgr.open( "ORDER BY DEPTNAME" );
      while( theDeptMgr.fetchNext() )
      {
         cout << theDeptMgr.element()->asString() << endl;
      }
      theDeptMgr.close();

      // delete a Department
      cout << endl << " Delete Department 031" << endl;
      theDept.setDeptno(   "031" );
      theDept.del();
      cout <<"Listing of all departments, after deletion:" << endl;
      theDeptMgr.open( "ORDER BY DEPTNAME" );
      while( theDeptMgr.fetchNext() )
      {
         cout << theDeptMgr.element()->asString() << endl;
      }
      theDeptMgr.close();


      // Rollback the changes so this sample can run again
      theDepartmentDatastore.rollback();

      // Disconnect from the database
      theDepartmentDatastore.disconnect();

      // All done
      cout <<"Done" << endl;
}
