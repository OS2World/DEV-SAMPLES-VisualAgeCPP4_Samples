/******************************************************************************
* .FILE:         dsur.h                                                       *
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
|  dsur.h  -  Class for Disk Space Usage Records                |
|             This is used by the coding sample for the         |
|             Sorted Map and the Sorted Relation.               |
\*-------------------------------------------------------------*/

  #include <fstream.h>
  #include <string.h>

  #include <iglobals.h>

  const int bufSize = 60;

  class DiskSpaceUR    {
     int       blocks;
     char*     name;

   public:
     DiskSpaceUR() {}

     DiskSpaceUR (DiskSpaceUR const& dsur)  {
        init(dsur);
     }

     void operator= (DiskSpaceUR const& dsur)   {
        deInit();
        init(dsur);
     }

     DiskSpaceUR (istream& DSURfile)     {
        DSURfile >> *this;
     }

     ~DiskSpaceUR () { deInit(); }

     IBoolean operator == (DiskSpaceUR const& dsur) const  {
       return (blocks == dsur.blocks)
           && strcmp (name, dsur.name) == 0;
     }

     friend istream& operator >> (istream& DSURfile, DiskSpaceUR& dsur)
     {
         DSURfile >> dsur.blocks;

         char temp[bufSize];
         DSURfile.get(temp, bufSize);

         if (DSURfile.good())
         {
            // Remove leading tabs and blanks
            int cnt;
            for (cnt=0; (temp[cnt] == '\t') || (temp[cnt] == ' '); cnt++)
            {
            }
            dsur.name = new char[strlen(temp+cnt)+1];
            strcpy(dsur.name, temp+cnt);
         }
         else
         {
            dsur.setInvalid();
            dsur.name = new char[1];
            dsur.name[0] = '\0';
         }
         return DSURfile;
     }

     friend ostream& operator << (ostream& outstream,
                                  DiskSpaceUR& dsur)     {
         outstream.width(bufSize);
         outstream.setf(ios::left, ios::adjustfield);
         outstream << dsur.name;

         outstream.width(9);
         outstream.setf(ios::right, ios::adjustfield);
         outstream << dsur.blocks;

         return outstream;
     }

     inline int const& space () const {return blocks;}

     inline char* const& id () const {return name;}

     inline IBoolean isValid () const {return (blocks > 0);}

   protected:

     inline void init (DiskSpaceUR const& dsur)     {
        blocks = dsur.blocks;
        name = new char[strlen(dsur.name) + 1];
        strcpy(name, dsur.name);
     }

     inline void deInit() {  delete[] name;  }

     inline void setInvalid () { blocks = -1;}
  };


     // Key access on name
  inline  char* const& key (DiskSpaceUR const& dsur)  {
     return dsur.id();
  }

     // Key access on space used
     // Since we can not have two key functions with same args
     // in global name space, we need to use an operations class.
  #include <istdops.h>
     // We can inherit all from the default operations class
     // and then define just the key access function ourselfes.
     // We can not use StdKeyOps here, because the in turn
     // use the key function in global name space, which is
     // already defined for keys of type char* above.
  class DSURBySpaceOps :  public IStdMemOps,
                          public IStdAsOps< DiskSpaceUR >,
                          public IStdEqOps< DiskSpaceUR >    {
    public:
       IStdCmpOps < int > keyOps;

     // Key Access
       int const& key (DiskSpaceUR const& dsur) const
       { return dsur.space(); }
  };

