/******************************************************************************
* .FILE:        iarrest.cpp                                                   *
*                                                                             *
* .DESCRIPTION: Implementation for the class, IArrest                         *
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
#include "iarrest.hpp"                 //IArrest class header
#ifndef _IVBMAIN_
  #include <ivbmain.hpp>
#endif
#ifndef _IVBDEFS_
  #include <ivbdefs.h>
#endif
#include <ireslib.hpp>
#include <inotifev.hpp>
#include "rap.h"

/****************************************************************************
 * Constructors
 ****************************************************************************/
IArrest :: IArrest() :
    dCharge(IArrest::burglary),
    dStatus(IArrest::arrested),
    dReport(""),
    dStatusDate("")
{
}

/****************************************************************************
 * Destructor
 ****************************************************************************/
IArrest :: ~IArrest()
{
}


/*------------------------------------------------------------------------------
 | IArrest::IArrest
 |
 | Standard operator=
 -----------------------------------------------------------------------------*/
IArrest & IArrest :: operator= (const IArrest & anArrest)
{
  if (this == &anArrest)
    return *this;

  setCharge(anArrest.charge());
  setStatus(anArrest.status());
  setStatusDate(anArrest.statusDate());
  setReport(anArrest.report());
  return *this;
}

/****************************************************************************
 * Events
 ****************************************************************************/
INotificationId IArrest :: chargeId = "IArrest::charge";
INotificationId IArrest :: statusId = "IArrest::status";
INotificationId IArrest :: statusDateId = "IArrest::statusDate";
INotificationId IArrest :: reportId = "IArrest::report";


/****************************************************************************
 * Attribute Access Member Functions
 ****************************************************************************/
/*------------------------------------------------------------------
 * charge
 *-----------------------------------------------------------------*/
unsigned short IArrest :: charge () const
{
  return dCharge;
}

IArrest& IArrest :: setCharge (const unsigned short iCharge)
{
  if (dCharge != iCharge)
  {
     dCharge = iCharge;
     notifyObservers(INotificationEvent(chargeId, *this, true,
                                        IEventData((char *)iCharge)));
  }
  else
     notifyObservers(INotificationEvent(chargeId, *this, false));
  return *this;
}

IString IArrest::chargeAsString() const
{
  IString sCharge;
  switch (dCharge)
  {
     case arson:
        sCharge = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(ARSON_STR);
        break;
     case accomplice_to_murder:
        sCharge = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(ACCOMPLICE_TO_MURDER_STR);
        break;
     case assault:
        sCharge = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(ASSAULT_STR);
        break;
     case assault_w_deadly_weapon:
        sCharge = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(ASSAULT_W_DEADLY_WEAPON_STR);
        break;
     case breaking_and_entering:
        sCharge = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(BREAKING_AND_ENTERING_STR);
        break;
     case burglary:
        sCharge = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(BURGLARY_STR);
        break;
     case DWI:
        sCharge = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(DWI_STR);
        break;
     case embezzlement:
        sCharge = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(EMBEZZLEMENT_STR);
        break;
     case fraud:
        sCharge = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(FRAUD_STR);
        break;
     case hijacking:
        sCharge = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(HIJACKING_STR);
        break;
     case hit_and_run:
        sCharge = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(HIT_AND_RUN_STR);
        break;
     case kidnapping:
        sCharge = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(KIDNAPPING_STR);
        break;
     case manslaughter:
        sCharge = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(MANSLAUGHTER_STR);
        break;
     case murder:
        sCharge = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(MURDER_STR);
        break;
     case perjury:
        sCharge = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(PERJURY_STR);
        break;
     case trespassing:
        sCharge = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(TRESPASSING_STR);
        break;
     case vandalism:
        sCharge = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(VANDALISM_STR);
        break;
     case wreckless_driving:
        sCharge = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(WRECKLESS_DRIVING_STR);
        break;
  }
  return sCharge;
}


IArrest & IArrest::setChargeFromString(const IString & aCharge)
{
  if (aCharge == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(ARSON_STR))
     setCharge(arson);
  else if (aCharge == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(ACCOMPLICE_TO_MURDER_STR))
     setCharge(accomplice_to_murder);
  else if (aCharge == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(ASSAULT_STR))
     setCharge(assault);
  else if (aCharge == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(ASSAULT_W_DEADLY_WEAPON_STR))
     setCharge(assault_w_deadly_weapon);
  else if (aCharge == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(BREAKING_AND_ENTERING_STR))
     setCharge(breaking_and_entering);
  else if (aCharge == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(BURGLARY_STR))
     setCharge(burglary);
  else if (aCharge == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(DWI_STR))
     setCharge(DWI);
  else if (aCharge == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(EMBEZZLEMENT_STR))
     setCharge(embezzlement);
  else if (aCharge == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(FRAUD_STR))
     setCharge(fraud);
  else if (aCharge == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(HIJACKING_STR))
     setCharge(hijacking);
  else if (aCharge == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(HIT_AND_RUN_STR))
     setCharge(hit_and_run);
  else if (aCharge == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(KIDNAPPING_STR))
     setCharge(kidnapping);
  else if (aCharge == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(MANSLAUGHTER_STR))
     setCharge(manslaughter);
  else if (aCharge == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(MURDER_STR))
     setCharge(murder);
  else if (aCharge == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(PERJURY_STR))
     setCharge(perjury);
  else if (aCharge == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(TRESPASSING_STR))
     setCharge(trespassing);
  else if (aCharge == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(VANDALISM_STR))
     setCharge(vandalism);
  else if (aCharge == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(WRECKLESS_DRIVING_STR))
     setCharge(wreckless_driving);
  return *this;
}

/*------------------------------------------------------------------
 * status
 *-----------------------------------------------------------------*/
unsigned short IArrest :: status () const
{
  return dStatus;
}

IArrest& IArrest :: setStatus (const unsigned short iStatus)
{
  if (dStatus != iStatus)
  {
     dStatus = iStatus;
     notifyObservers(INotificationEvent(statusId, *this, true,
                                        IEventData((char *)iStatus)));
  }
  else
     notifyObservers(INotificationEvent(statusId, *this, false));
  return *this;
}

IString IArrest::statusAsString() const
{
  IString sStatus;
  switch (dStatus)
  {
     case acquitted:
        sStatus = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(ACQUITTED_STR);
        break;
     case arrested:
        sStatus = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(ARRESTED_STR);
        break;
     case arraigned:
        sStatus = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(ARRAIGNED_STR);
        break;
     case convicted:
        sStatus = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(CONVICTED_STR);
        break;
     case dropped:
        sStatus = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(DROPPED_STR);
        break;
     case escaped:
        sStatus = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(ESCAPED_STR);
        break;
     case free_on_bond:
        sStatus = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(FREE_ON_BOND_STR);
        break;
     case released:
        sStatus = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(RELEASED_STR);
        break;
     case released_on_parole:
        sStatus = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(RELEASED_ON_PAROLE_STR);
        break;
     case under_suspicion:
        sStatus = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(UNDER_SUSPICION_STR);
        break;
     case wanted:
        sStatus = IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(WANTED_STR);
        break;
  }
  return sStatus;
}


IArrest & IArrest::setStatusFromString(const IString & aStatus)
{
  if (aStatus == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(ACQUITTED_STR))
     setCharge(acquitted);
  else if (aStatus == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(ARRESTED_STR))
     setCharge(arrested);
  else if (aStatus == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(ARRAIGNED_STR))
     setCharge(arraigned);
  else if (aStatus == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(CONVICTED_STR))
     setCharge(convicted);
  else if (aStatus == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(DROPPED_STR))
     setCharge(dropped);
  else if (aStatus == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(ESCAPED_STR))
     setCharge(escaped);
  else if (aStatus == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(FREE_ON_BOND_STR))
     setCharge(free_on_bond);
  else if (aStatus == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(RELEASED_STR))
     setCharge(released);
  else if (aStatus == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(RELEASED_ON_PAROLE_STR))
     setCharge(released_on_parole);
  else if (aStatus == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(UNDER_SUSPICION_STR))
     setCharge(under_suspicion);
  else if (aStatus == IDynamicLinkLibrary(VBRESLIBNAME("rapres"),IVBMain::defaultResourcePath()).tryToLoadString(WANTED_STR))
     setCharge(wanted);
  return *this;
}

/*------------------------------------------------------------------
 * statusDate
 *-----------------------------------------------------------------*/
IString IArrest :: statusDate () const
{
  return dStatusDate;
}

IArrest & IArrest :: setStatusDate (const IString & iStatusDate)
{
  if (dStatusDate != iStatusDate)
  {
     dStatusDate = iStatusDate;
     notifyObservers(INotificationEvent(statusDateId, *this, true,
                                        IEventData((char *)iStatusDate)));
  }
  else
     notifyObservers(INotificationEvent(statusDateId, *this, false));
  return *this;
}


/*------------------------------------------------------------------
 * report
 *-----------------------------------------------------------------*/
IString IArrest :: report () const
{
  return dReport;
}

IArrest & IArrest :: setReport (const IString & iReport)
{
  dReport = iReport;
  notifyObservers(INotificationEvent(reportId, *this, true,
                                     IEventData((char *)iReport)));
  return *this;
}


/****************************************************************************
 * Member Functions
 ****************************************************************************/
/*------------------------------------------------------------------------------
| IArrest::asDebugInfo                                                         |
|                                                                              |
| Generate a string that identifies for debugging purposes what data           |
| an IArrest  instance contains.                                               |
|                                                                              |
| NOTE: attributes not included:  charge, , status, statusDate and report      |
| NOTE: to see what some of the values map to, see the enumerations that       |
|       are defined in IArrest.hpp.                                           |
------------------------------------------------------------------------------*/
IString IArrest :: asDebugInfo () const
{
  IString debugInfo("charge=" + IString(dCharge) + ",");
  debugInfo += "status=" + IString(dStatus) + ",";
  debugInfo += "StatusDate=" + dStatusDate + ",";
  debugInfo += "Report=" + dReport + ",";
  return debugInfo;
}

/*------------------------------------------------------------------
 * asString() - used to identify what gets shown in a listbox
 *-----------------------------------------------------------------*/
IString  IArrest :: asString() const
{
  return (chargeAsString() + "     " + statusAsString() + "     " + dStatusDate);
}


/****************************************************************************
 * Operators
 ****************************************************************************/
/*------------------------------------------------------------------
 * Operator == (const IArrest & value)
 *-----------------------------------------------------------------*/
bool
  IArrest :: operator == (const IArrest & value) const
{
  if (charge() != value.charge()) {
    return false;
  } /* endif */
  if (status() != value.status()) {
    return false;
  } /* endif */
  if (statusDate() != value.statusDate()) {
    return false;
  } /* endif */
  return true;
}

/*------------------------------------------------------------------
 * Operator != (const IArrest & value)
 *-----------------------------------------------------------------*/
bool
  IArrest :: operator != (const IArrest & value) const
{
  if (charge() != value.charge()) {
    return true;
  } /* endif */
  if (status() != value.status()) {
    return true;
  } /* endif */
  if (statusDate() != value.statusDate()) {
    return true;
  } /* endif */
  return false;
}

/*------------------------------------------------------------------
 * Operator == (const IArrest * value)
 *-----------------------------------------------------------------*/
bool
  IArrest :: operator == (const IArrest * value) const
{
  if (charge() != value->charge()) {
    return false;
  } /* endif */
  if (status() != value->status()) {
    return false;
  } /* endif */
  if (statusDate() != value->statusDate()) {
    return false;
  } /* endif */
  return true;
}

/*------------------------------------------------------------------
 * Operator != (const IArrest * value)
 *-----------------------------------------------------------------*/
bool
  IArrest :: operator != (const IArrest * value) const
{
  if (charge() != value->charge()) {
    return true;
  } /* endif */
  if (status() != value->status()) {
    return true;
  } /* endif */
  if (statusDate() != value->statusDate()) {
    return true;
  } /* endif */
  return false;
}

