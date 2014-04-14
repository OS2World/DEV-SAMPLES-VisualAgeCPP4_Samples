#ifndef _IALIAS_
#define _IALIAS_
/******************************************************************************
* .FILE:        ialias.hpp                                                    *
*                                                                             *
* .DESCRIPTION: Header file for the class IAlias                              *
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
#include "ivbsamps.h"
#include <istdntfy.hpp>             //Parent of IStandardNotifier
#include <istring.hpp>

//Forward class references


//**************************************************************************
// Class:   IAlias
//
// Purpose: Describes IAlias Class.
//   This class defines Alias objects for use in applications such as the
//      Police Rap Sheet.
//   These objects hold and manage all the data relevant to a person's alias.
//
//**************************************************************************
class IVBSAMP_IMPORT IAlias : public IStandardNotifier
{

public:

/*---------------------  CONSTRUCTORS/DESTRUCTORS  ----------------
 *-----------------------------------------------------------------*/
IAlias();
virtual  ~IAlias();


/*---------------------  NOTIFICATION EVENTS  ----------------------
 | These INotificationId strings are used for all notifications that
 | this class provides to its observers:
 |     -aliasId            Notification identifier provided to
 |                         observers when the alias attribute changes.
 *-----------------------------------------------------------------*/
static INotificationId aliasId;


/*---------------------  ATTRIBUTES  -------------------------------
 | The following members are for accessing the attributes of this class:
 |     -alias              Returns the alias attribute.
 |     -setAlias           Sets the alias attribute.
 *-----------------------------------------------------------------*/
virtual IString
   alias() const;
virtual IAlias &
   setAlias(const IString & aAlias);


/*---------------------  ACTIONS   ---------------------------------
 | asString    Formatted string for listbox and debugging output.
 *-----------------------------------------------------------------*/
virtual IString
   asString() const;


/*---------------------  OPERATORS   -------------------------------
 *-----------------------------------------------------------------*/
bool
   operator ==(const IAlias & value) const;
   operator ==(const IAlias * value) const;
   operator !=(const IAlias & value) const;
   operator !=(const IAlias * value) const;

protected:

private:
/*---------------------  PRIVATE MEMBER DATA  ---------------------
 *-----------------------------------------------------------------*/
   IString dAlias;

};   //IAlias

#endif

