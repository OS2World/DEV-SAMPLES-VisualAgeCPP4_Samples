#ifndef _IARREST_
#define _IARREST_
/******************************************************************************
* .FILE:        iarrest.hpp                                                   *
*                                                                             *
* .DESCRIPTION: Header file for the class IArrest                             *
*                                                                             *
* .CLASSES:     IArrest                                                       *
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
#include "ivbsamps.h"
#include <istdntfy.hpp>               //Parent of IArrest
#include <istring.hpp>

/*----------------------------------------------------------------------------*/
/* Align classes on four byte boundary.                                       */
/*----------------------------------------------------------------------------*/
#pragma pack(4)

//**************************************************************************
// Class:   IArrest
//
// Purpose: Describes IArrest Class.
//   This class defines Arrest objects for use in applications such as the
//      Police Rap Sheet.
//   These objects hold and manage all the data relevant to an arrest.
//
//**************************************************************************
class IVBSAMP_IMPORT IArrest : public IStandardNotifier
{

public:


/*---------------------  CONSTRUCTORS/DESTRUCTORS  ----------------
 *-----------------------------------------------------------------*/
IArrest  ();
virtual  ~IArrest ();

/*---------------------  ENUMERATED TYPES  ------------------------
 *-----------------------------------------------------------------*/
/*------------------------------------------------------------------
 | WARNING:  Add new types to the end of the list.
 *-----------------------------------------------------------------*/
enum ICharge {arson,                            // 0
              accomplice_to_murder,             // 1
              assault,                          // 2
              assault_w_deadly_weapon,          // 3
              breaking_and_entering,            // 4
              burglary,                         // 5
              DWI,                              // 6
              embezzlement,                     // 7
              fraud,                            // 8
              hijacking,                        // 9
              hit_and_run,                      // 10
              kidnapping,                       // 11
              manslaughter,                     // 12
              murder,                           // 13
              perjury,                          // 14
              trespassing,                      // 15
              vandalism,                        // 16
              wreckless_driving};               // 17

/*------------------------------------------------------------------
 | WARNING:  Add new types to the end of the list.
 *-----------------------------------------------------------------*/
enum IStatus {acquitted,                        // 0
              arrested,                         // 1
              arraigned,                        // 2
              convicted,                        // 3
              dropped,                          // 4
              escaped,                          // 5
              free_on_bond,                     // 6
              released,                         // 7
              released_on_parole,               // 8
              under_suspicion,                  // 9
              wanted};                          // 10

/*---------------------  NOTIFICATION EVENTS  ----------------------
 | These INotificationId strings are used for all notifications that
 | this class provides to its observers:
 |     -chargeId           Notification identifier provided to
 |                         observers when the charge attribute changes.
 |     -statusId           Notification identifier provided to
 |                         observers when the status attribute changes.
 |     -statusDateId       Notification identifier provided to
 |                         observers when the statusDate attribute changes.
 |     -reportId           Notification identifier provided to
 |                         observers when the report attribute changes.
 *-----------------------------------------------------------------*/
static INotificationId chargeId;
static INotificationId statusId;
static INotificationId statusDateId;
static INotificationId reportId;


virtual IString asDebugInfo() const;


/*---------------------  ATTRIBUTES  -------------------------------
 | The following members are for accessing the attributes of this class:
 |     -charge                Returns the charge attribute.
 |     -status                Returns the status attribute.
 |     -statusDate            Returns the statusDate attribute.
 |     -report                Returns the arrest report
 |     -chargeAsString        Returns the string value associated with the charge numeric value
 |     -statusAsString        Returns the string value associated with the status numeric value
 |     -setCharge             Sets the charge attribute.
 |     -setStatus             Sets the status attribute.
 |     -setReport             Sets the report
 |     -setStatusDate         Sets the statusDate attribute.
 |     -setChargeFromString   Returns the string value associated with the charge numeric value
 |     -setStatusFromString   Returns the string value associated with the status numeric value
 *-----------------------------------------------------------------*/
virtual unsigned short charge () const;
virtual unsigned short status () const;
virtual IString        statusDate () const;
virtual IString        report () const;
virtual IArrest&       setCharge (const unsigned short iCharge);
virtual IArrest&       setStatus (const unsigned short iStatus);
virtual IArrest&       setStatusDate (const IString & aStatusDate);
virtual IArrest&       setReport (const IString & aReport);
virtual IString        chargeAsString() const;
virtual IArrest&       setChargeFromString(const IString & aCharge);
virtual IString        statusAsString() const;
virtual IArrest&       setStatusFromString(const IString & aStatus);



/*---------------------  ACTIONS   ---------------------------------
 | asString    Formatted string for listbox and debugging output.
 *-----------------------------------------------------------------*/
virtual IString asString () const;


/*---------------------  OPERATORS   -------------------------------
 *-----------------------------------------------------------------*/
IArrest & operator= (const IArrest & anArrest);

bool
  operator == (const IArrest & value) const,
  operator != (const IArrest & value) const,
  operator == (const IArrest * value) const,
  operator != (const IArrest * value) const;

protected:

private:
/*---------------------  PRIVATE MEMBER DATA  ---------------------
 *-----------------------------------------------------------------*/
  unsigned short dCharge;       // The charge made when arrested.
  unsigned short dStatus;       // The current status of the arrest.
  IString dStatusDate;          // The date the arrest status was last changed.
  IString dReport;              // The arrest report

};

/*----------------------------------------------------------------------------*/
/* Resume compiler default packing.                                           */
/*----------------------------------------------------------------------------*/
#pragma pack()

#endif

