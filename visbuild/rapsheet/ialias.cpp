/******************************************************************************
* .FILE:        ialias.cpp                                                    *
*                                                                             *
* .DESCRIPTION: Implementation for the class, IAlias                          *
*                                                                             *
* .CLASSES:     IAlias                                                        *
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
#include "ialias.hpp"
#include <inotifev.hpp>
#include <itrace.hpp>

/****************************************************************************
 * Constructors
 ****************************************************************************/
IAlias :: IAlias() :
    dAlias("")
{
}

/****************************************************************************
 * Destructor
 ****************************************************************************/
IAlias :: ~IAlias()
{
  IFUNCTRACE_DEVELOP();
  ITRACE_DEVELOP("About to destruct alias: " + dAlias);
}


/****************************************************************************
 * Events
 ****************************************************************************/
INotificationId IAlias :: aliasId = "IAlias::alias";


/****************************************************************************
 * Attribute Access Member Functions
 ****************************************************************************/
/*------------------------------------------------------------------
 * alias
 *-----------------------------------------------------------------*/
IString IAlias :: alias() const
{
  return dAlias;
}

IAlias &  IAlias ::
  setAlias(const IString & iAlias)
{
  if (dAlias != iAlias)
  {
     dAlias = iAlias;
     notifyObservers(INotificationEvent(aliasId, *this, true,
                                        IEventData((char *)iAlias)));
  }
  else
     notifyObservers(INotificationEvent(aliasId, *this, false));
  return *this;
}


/****************************************************************************
 * Action Member Functions
 ****************************************************************************/
/*------------------------------------------------------------------
 * asString()
 *-----------------------------------------------------------------*/
IString  IAlias :: asString() const
{
  return alias();
}


/****************************************************************************
 * Operators
 ****************************************************************************/
/*------------------------------------------------------------------
 * Operator == (const IAlias & value)
 *-----------------------------------------------------------------*/
bool IAlias::operator ==(const IAlias & value) const
{
  if (alias() != value.alias()) return false;
  return true;
}

/*------------------------------------------------------------------
 * Operator == (const IAlias * value)
 *-----------------------------------------------------------------*/
bool IAlias::operator == (const IAlias * value) const
{
  if (alias() != value->alias()) return false;
  return true;
}

/*------------------------------------------------------------------
 * Operator != (const IAlias & value)
 *-----------------------------------------------------------------*/
bool IAlias::operator != (const IAlias & value) const
{
  if (alias() != value.alias()) return true;
  return false;
}

/*------------------------------------------------------------------
 * Operator != (const IAlias * value)
 *-----------------------------------------------------------------*/
bool IAlias::operator != (const IAlias * value) const
{
  if (alias() != value->alias()) return true;
  return false;
}

