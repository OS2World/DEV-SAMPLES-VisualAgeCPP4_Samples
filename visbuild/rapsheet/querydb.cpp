/******************************************************************************
* .FILE:        querydb.cpp                                                   *
*                                                                             *
* .DESCRIPTION: Source file used to query for the suspect data                *
*                                                                             *
* .CLASSES:                                                                   *
*                                                                             *
* .COPYRIGHT:                                                                 *
*    Licensed Material - Program-Property of IBM                              *
*    (C) Copyright IBM Corp. 1992, 1996 - All Rights Reserved                 *
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
#include <stdio.h>
#include <stdlib.h>
#include <itrace.hpp>
#include <fstream.h>
#include <iostream.h>
#include <iprofile.hpp>
#include "irsltrec.hpp"
#include "isusrec.hpp"
#include "iarstrec.hpp"
#include "ialsrec.hpp"
#include "querydb.hpp"
#include "rap.h"

IString delimeter(",");

/*****************************************************************/
/*                                                               */
/* getAllSuspects                                                */
/*                                                               */
/*Function: Gets the list of suspects from the database          */
/*                                                               */
/*****************************************************************/

IResultRecord getAllSuspects()
{

  IBoolean firstSuspectRecord=true;

  IString   lastName, firstName, gender, hairColor, eyeColor, weight, height,
            enableHasScar, enableHasMole, enableHasTattoo, birthDate,
            bookNumber, mugFront, mugRight, mugLeft, street,
            city, county, state, zip, description, MO,
            scarDescription, moleDescription, tattooDescription,
            tempRecords, suspectData;

  ISuspectRecord  suspectRecord;
  IResultRecord   resultRecord;
  unsigned long   numberOfSuspects;
  long            numberOfResults;
  unsigned short  delimeterPos=0,
                  searchPos=1;

//-------------------------------------------------------------------------------
// Setup the IProfile
//-------------------------------------------------------------------------------

   IFUNCTRACE_DEVELOP();
   ITRACE_DEVELOP("Creating and associating application name with suspect profile");
   IString appName(SUSPECT_APPNAME);
   IProfile suspectProfile(IString(SUSPECT_INI));
   suspectProfile.setDefaultApplicationName(SUSPECT_APPNAME); // set default app name
   ITRACE_DEVELOP("Creating and associating application name with suspect profile done.");

//-------------------------------------------------------------------------------
// Iterate through the suspect profile and process each suspect data
//-------------------------------------------------------------------------------

   IProfile::Cursor cursor(suspectProfile, appName);
   for (cursor.setToFirst();cursor.isValid();cursor.setToNext())
   {

      // retrieve one suspect's data
      // NOTE: the order of the retrieves must be as following;
      // it matches how the IProfile is build in susprof.cpp

      IString key = suspectProfile.applicationOrKeyAt(cursor);
      suspectData = suspectProfile.elementWithKey(key);

      // get LastName from suspectData and set in the suspectRecord

      delimeterPos = suspectData.indexOf (delimeter,searchPos);
      lastName = suspectData.subString(searchPos,delimeterPos-searchPos);
      searchPos = delimeterPos + 1;         // set next search position
      suspectRecord.setLastName(lastName);

      // get FirstName from suspectData and set in the suspectRecord

      delimeterPos = suspectData.indexOf (delimeter,searchPos);
      firstName = suspectData.subString(searchPos,delimeterPos-searchPos);
      searchPos =  delimeterPos + 1;         // set next search position
      suspectRecord.setFirstName(firstName);

      // get Gender from suspectData and set in the suspectRecord

      delimeterPos = suspectData.indexOf (delimeter,searchPos);
      gender = suspectData.subString(searchPos,delimeterPos-searchPos);
      searchPos =  delimeterPos +1;         // set next search position
      suspectRecord.setGender((unsigned short)gender.asUnsigned());


      // get HairColor from suspectData and set in the suspectRecord

      delimeterPos = suspectData.indexOf (delimeter,searchPos);
      hairColor = suspectData.subString(searchPos,delimeterPos-searchPos);
      searchPos =  delimeterPos+1;         // set next search position
      suspectRecord.setHairColor((unsigned short)hairColor.asUnsigned());


      // get EyeColor from suspectData and set in the suspectRecord

      delimeterPos = suspectData.indexOf (delimeter,searchPos);
      eyeColor = suspectData.subString(searchPos,delimeterPos-searchPos);
      searchPos =   delimeterPos+1;         // set next search position
      suspectRecord.setEyeColor((unsigned short)eyeColor.asUnsigned());

      // get Weight from suspectData and set in the suspectRecord

      delimeterPos = suspectData.indexOf (delimeter,searchPos);
      weight = suspectData.subString(searchPos,delimeterPos-searchPos);
      searchPos =  delimeterPos+1;         // set next search position
      suspectRecord.setWeight((unsigned short)weight.asUnsigned());

      // get Height from suspectData and set in the suspectRecord

      delimeterPos = suspectData.indexOf (delimeter,searchPos);
      height = suspectData.subString(searchPos,delimeterPos-searchPos);
      searchPos =   delimeterPos+1;         // set next search position
      suspectRecord.setHeight((unsigned short)height.asUnsigned());


      // get enableHasScar from suspectData and set in the suspectRecord

      delimeterPos = suspectData.indexOf (delimeter,searchPos);
      enableHasScar = suspectData.subString(searchPos,delimeterPos-searchPos);
      searchPos =   delimeterPos+1;         // set next search position
      suspectRecord.enableHasScar((unsigned short)enableHasScar.asUnsigned());

      // get enableHasMole from suspectData and set in the suspectRecord

      delimeterPos = suspectData.indexOf (delimeter,searchPos);
      enableHasMole = suspectData.subString(searchPos,delimeterPos-searchPos);
      searchPos =   delimeterPos+1;         // set next search position
      suspectRecord.enableHasMole((unsigned short)enableHasMole.asUnsigned());


      // get enableHasTattoo from suspectData and set in the suspectRecord

      delimeterPos = suspectData.indexOf (delimeter,searchPos);
      enableHasTattoo = suspectData.subString(searchPos,delimeterPos-searchPos);
      searchPos =   delimeterPos+1;         // set next search position
      suspectRecord.enableHasTattoo((unsigned short)enableHasTattoo.asUnsigned());

      // get BirthDate from suspectData and set in the suspectRecord

      delimeterPos = suspectData.indexOf (delimeter,searchPos);
      birthDate = suspectData.subString(searchPos,delimeterPos-searchPos);
      searchPos =   delimeterPos+1;         // set next search position
      suspectRecord.setBirthDate(birthDate);

      // get BookNumber from suspectData and set in the suspectRecord

      delimeterPos = suspectData.indexOf (delimeter,searchPos);
      bookNumber = suspectData.subString(searchPos,delimeterPos-searchPos);
      searchPos =   delimeterPos+1;         // set next search position
      suspectRecord.setBookNumber(bookNumber.asUnsigned());

      // example: unsigned long count = strCount.asUnsigned(); strCount is IString


      // get MugFront from suspectData and set in the suspectRecord

      delimeterPos = suspectData.indexOf (delimeter,searchPos);
      mugFront = suspectData.subString(searchPos,delimeterPos-searchPos);
      searchPos =   delimeterPos+1;         // set next search position
      suspectRecord.setMugFront((unsigned short)mugFront.asUnsigned());

      // get MugRight from suspectData and set in the suspectRecord

      delimeterPos = suspectData.indexOf (delimeter,searchPos);
      mugRight = suspectData.subString(searchPos,delimeterPos-searchPos);
      searchPos =   delimeterPos+1;         // set next search position
      suspectRecord.setMugRight((unsigned short)mugRight.asUnsigned());

      // get MugLeft from suspectData and set in the suspectRecord

      delimeterPos = suspectData.indexOf (delimeter,searchPos);
      mugLeft = suspectData.subString(searchPos,delimeterPos-searchPos);
      searchPos = delimeterPos+1;         // set next search position
      suspectRecord.setMugLeft((unsigned short)mugLeft.asUnsigned());

      // get Street from suspectData and set in the suspectRecord

      delimeterPos = suspectData.indexOf (delimeter,searchPos);
      street  = suspectData.subString(searchPos,delimeterPos-searchPos);
      searchPos = delimeterPos+1;         // set next search position
      suspectRecord.setStreet(street);

      // get City from suspectData and set in the suspectRecord

      delimeterPos = suspectData.indexOf (delimeter,searchPos);
      city = suspectData.subString(searchPos,delimeterPos-searchPos);
      searchPos = delimeterPos+1;         // set next search position
      suspectRecord.setCity(city);

      // get County from suspectData and set in the suspectRecord

      delimeterPos = suspectData.indexOf (delimeter,searchPos);
      county = suspectData.subString(searchPos,delimeterPos-searchPos);
      searchPos = delimeterPos+1;         // set next search position
      suspectRecord.setCounty(county);

      // get State from suspectData and set in the suspectRecord

      delimeterPos = suspectData.indexOf (delimeter,searchPos);
      state = suspectData.subString(searchPos,delimeterPos-searchPos);
      searchPos = delimeterPos+1;         // set next search position
      suspectRecord.setState(state);

      // get zip from suspectData and set in the suspectRecord

      delimeterPos = suspectData.indexOf (delimeter,searchPos);
      zip = suspectData.subString(searchPos,delimeterPos-searchPos);
      searchPos = delimeterPos+1;         // set next search position
      suspectRecord.setZip(zip);

      // get Description from suspectData and set in the suspectRecord

      delimeterPos = suspectData.indexOf (delimeter,searchPos);
      description = suspectData.subString(searchPos,delimeterPos-searchPos);
      searchPos =   delimeterPos+1;         // set next search position
      suspectRecord.setDescription(description);

      // get MO from suspectData and set in the suspectRecord

      delimeterPos = suspectData.indexOf (delimeter,searchPos);
      MO  = suspectData.subString(searchPos,delimeterPos-searchPos);
      searchPos = delimeterPos+1;         // set next search position
      suspectRecord.setMO(MO);

      // get ScarDescription from suspectData and set in the suspectRecord

      delimeterPos = suspectData.indexOf (delimeter,searchPos);
      scarDescription = suspectData.subString(searchPos,delimeterPos-searchPos);
      searchPos =   delimeterPos+1;         // set next search position
      suspectRecord.setScarDescription(scarDescription);

      // get MoleDescription from suspectData and set in the suspectRecord

      delimeterPos = suspectData.indexOf (delimeter,searchPos);
      moleDescription = suspectData.subString(searchPos,delimeterPos-searchPos);
      searchPos =   delimeterPos+1;         // set next search position
      suspectRecord.setMoleDescription(moleDescription);

      // get TattooDescription from suspectData and set in the suspectRecord

      delimeterPos = suspectData.indexOf (delimeter,searchPos);
      tattooDescription = suspectData.subString(searchPos,delimeterPos-searchPos);
      searchPos =   delimeterPos+1;         // set next search position
      suspectRecord.setTattooDescription(tattooDescription);

      // at this time, one suspect record has been built

      //-----------------------------------------------------------------
      // If this is the first suspect record then copy it to a temporary
      // area. Otherwise, append it to the temporary area
      // When all records are copied/appended, copy the temporary
      // suspect record to the result record.
      //-----------------------------------------------------------------

      if (firstSuspectRecord) {
       ITRACE_DEVELOP("This is the first suspect record.");
       firstSuspectRecord = false;
       tempRecords = suspectRecord.asString();
       }
      else {
       ITRACE_DEVELOP("This is not the first suspect record.");
       tempRecords += suspectRecord.asString();
       }

      delimeterPos = 0;              // reset for each suspect data
      searchPos = 1;

   }  // end of for loop for processing each suspect

   //------------------------------------------------------
   // Finished building suspect records. Build the result record
   //------------------------------------------------------


   ITRACE_DEVELOP("Setting up result record.");
   numberOfSuspects = suspectProfile.numberOfKeys();
   resultRecord.setNumResults(numberOfSuspects); // #of suspects
   resultRecord.setResultData(tempRecords);

   return resultRecord;
} // getAllSuspects()


/*****************************************************************/
/*                                                               */
/* getAllAliases                                                 */
/*                                                               */
/*Function: Gets the list of aliases from  the database          */
/*          using the book number from the suspect object        */
/*                                                               */
/*****************************************************************/

IResultRecord getAllAliases(unsigned long bookNumber)
{
  IBoolean       firstAliasRecord = true;
  unsigned short delimeterPos=0,
                 searchPos=1;
  IString        tempRecords, name,
                 key, data, profBookNumber;             // used with IProfile
  IAliasRecord   aliasRecord;
  IResultRecord  aliasResultRecord;
  long           numberOfAliases=0;


  //-----------------------
  // Setup the aliasProfile
  //-----------------------

  IFUNCTRACE_DEVELOP();
  ITRACE_DEVELOP("Creating and associating application name with alias profile");
  IString appName(ALIAS_APPNAME);
  IProfile aliasProfile(IString(ALIAS_INI));
  aliasProfile.setDefaultApplicationName(ALIAS_APPNAME);       // set default app name
  ITRACE_DEVELOP("Creating and associating app. name with aliases profile done.");

  //------------------------------------------------------------------
  // Iterate through the alias profile and build the aliasResultRecord
  //------------------------------------------------------------------

  IProfile::Cursor cursor(aliasProfile, ALIAS_APPNAME);
  for (cursor.setToFirst();cursor.isValid();cursor.setToNext())
  {
     key = aliasProfile.applicationOrKeyAt(cursor);
     data = aliasProfile.elementWithKey(key);

     delimeterPos = data.indexOf (delimeter,searchPos);
     profBookNumber = data.subString(searchPos,delimeterPos-searchPos);
     if (bookNumber == profBookNumber.asUnsigned())           // process the alias
        {
         numberOfAliases = numberOfAliases +1;
         searchPos = delimeterPos +1;

         // extract the name from the alias data from the profile
         // and add to the aliasRecord

         delimeterPos = data.indexOf (delimeter,searchPos);
         name = data.subString(searchPos,delimeterPos-searchPos);

         aliasRecord.setName(name);
         //-----------------------------------------------------------------
         // If this is the first alias record then COPY it to a temporary
         // area. Otherwise, APPEND it to the temporary area
         // When all records are copied/appended, copy the temporary
         // alias record to the result record.
         //-----------------------------------------------------------------
         if (firstAliasRecord)
         {
          ITRACE_DEVELOP("this is the first alias");
          firstAliasRecord = false;
          tempRecords = aliasRecord.asString();
          ITRACE_DEVELOP("tempRecords in first record code: " + tempRecords + ".");
         }
         else
         {
          tempRecords += aliasRecord.asString();
          ITRACE_DEVELOP("tempRecords in subsequent record code: " + tempRecords + ".");
         }
        }
     delimeterPos = 0;                     // reset for next alias data read in
     searchPos = 1;
  }  // end of for iteration of the aliasProfile

  //----------------------------------------------------------
  // Finished building alias records. Add to the result record
  //----------------------------------------------------------
  ITRACE_DEVELOP("setting the result data");
  aliasResultRecord.setResultData(tempRecords);
  aliasResultRecord.setNumResults(numberOfAliases);
  ITRACE_DEVELOP("set the result data");

  return aliasResultRecord;
}


/*****************************************************************/
/*                                                               */
/* getAllArrests                                                 */
/*                                                               */
/*Function: Gets the list of arrests from  the database          */
/*          using the book number from the suspect object        */
/*                                                               */
/*****************************************************************/
IResultRecord getAllArrests(unsigned long bookNumber)
{
  IBoolean              firstArrestRecord = true;
  IString               tempRecords,
                        key,arrestData, profBookNumber, // used with IProfile
                        arrestCharge,arrestStatus,arrestDate;
  IArrestRecord         arrestRecord;
  IResultRecord         arrestResultRecord;
  long                  numberOfArrests=0;
  unsigned short        searchPos=1, delimeterPos=0;

  //-------------------------
  // Setup the arrestsProfile
  //-------------------------

  IFUNCTRACE_DEVELOP();
  ITRACE_DEVELOP("Creating and associating application name with arrest profile");
  IString appName(ARREST_APPNAME);
  IProfile arrestsProfile(IString(ARREST_INI));
  arrestsProfile.setDefaultApplicationName(ARREST_APPNAME);       // set default app name
  ITRACE_DEVELOP("Creating and associating app. name with arrests profile done.");

  //-----------------------------------------------------------------------
  // Iterate through the arrests profile and build the arrest result record
  //-----------------------------------------------------------------------

  IProfile::Cursor cursor(arrestsProfile, ARREST_APPNAME);
  for (cursor.setToFirst();cursor.isValid();cursor.setToNext())
  {
     key = arrestsProfile.applicationOrKeyAt(cursor);
     arrestData = arrestsProfile.elementWithKey(key);

     delimeterPos = arrestData.indexOf (delimeter,searchPos);
     profBookNumber = arrestData.subString(searchPos,delimeterPos-searchPos);
     if (bookNumber == profBookNumber.asUnsigned())           // process the alias
        {
         numberOfArrests = numberOfArrests + 1;

         // extract the arrestCharge, arrestStatus, and arrestDate from
         // the aliasData from the profile and add to the arrestRecord

         searchPos = delimeterPos+1;         // set next search position
         delimeterPos = arrestData.indexOf (delimeter,searchPos);
         arrestCharge = arrestData.subString(searchPos,delimeterPos-searchPos);
         arrestRecord.setCharge(arrestCharge.asUnsigned());

         searchPos = delimeterPos +1;
         delimeterPos = arrestData.indexOf (delimeter,searchPos);
         arrestStatus = arrestData.subString(searchPos,delimeterPos-searchPos);
         arrestRecord.setStatus(arrestStatus.asUnsigned());

         searchPos = delimeterPos +1;
         delimeterPos = arrestData.indexOf (delimeter,searchPos);
         arrestDate = arrestData.subString(searchPos,delimeterPos-searchPos);
         arrestRecord.setStatusDate(arrestDate);

         //-----------------------------------------------------------------
         // If this is the first alias record then COPY it to a temporary
         // area. Otherwise, APPEND it to the temporary area
         // When all records are copied/appended, copy the temporary
         // alias record to the result record.
         //-----------------------------------------------------------------
         if (firstArrestRecord)
         {
          ITRACE_DEVELOP("this is the first alias");
          firstArrestRecord = false;
          tempRecords = arrestRecord.asString();
          ITRACE_DEVELOP("tempRecords in first record code: " + tempRecords + ".");
         }
         else
         {
          tempRecords += arrestRecord.asString();
          ITRACE_DEVELOP("tempRecords in subsequent record code: " + tempRecords + ".");
         }
        }
     delimeterPos = 0;                     // reset for next alias data read in
     searchPos = 1;
  }  // end of for iteration of the arrestProfile

  //------------------------------------------------------------------
  // Finished building arrest records. Add to the arrest result record
  //------------------------------------------------------------------
  ITRACE_DEVELOP("setting the result data");
  arrestResultRecord.setResultData(tempRecords);
  arrestResultRecord.setNumResults(numberOfArrests);
  ITRACE_DEVELOP("set the result data");

  return arrestResultRecord;

}


/*****************************************************************************
 ! error(const char *message)
 !
 !   Display error message and exit.
 *****************************************************************************/
void error(const char *message)
{
   cout << "\n\nERROR: %s\n\n", message;
   exit(1);
}


