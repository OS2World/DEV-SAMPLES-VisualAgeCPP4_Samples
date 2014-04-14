/******************************************************************************
* .FILE:        msnmspnh.cpp                                                  *
*                                                                             *
* .DESCRIPTION: Handler that automatically spins the specified servant        *
*               numeric spin button when the specified master numeric         *
*               spin button reaches its upper and lower bounds.               *
*                                                                             *
* .CLASSES:     MasterServantNumSpinHandler                                   *
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
#include <itrace.hpp>
#include <ispinnum.hpp>
#include "msnmspnh.hpp"            //MasterServantNumSpinHandler

//***************************************************************************
// Class:   MasterServantNumSpinHandler
//
// Purpose: Supports the master and servant spin buttons used to represent
//          the feet and inch fields.
//
//***************************************************************************

//***************************************************************************
// Constructor
//***************************************************************************
MasterServantNumSpinHandler :: MasterServantNumSpinHandler(
   INumericSpinButton * master,
   INumericSpinButton * servant) : ISpinHandler()
{
   imaster = master;
   iservant = servant;
}

//***************************************************************************
// Destructor
//***************************************************************************
MasterServantNumSpinHandler :: ~MasterServantNumSpinHandler()
{
}

//***************************************************************************
// arrowUp
//***************************************************************************
bool MasterServantNumSpinHandler::arrowUp(IControlEvent& controlEvent)
{
     IFUNCTRACE_DEVELOP();

     /***********************************************************************
      * NOTE: master->value() is already changed before the handler is called
      ***********************************************************************/
     if (imaster->value() == imaster->range().lowerBound())
        iservant->spinUp();

     return false;  //allow any other handlers to be called
}

//***************************************************************************
// arrowDown
//***************************************************************************
bool MasterServantNumSpinHandler::arrowDown(IControlEvent& controlEvent)
{
     IFUNCTRACE_DEVELOP();

     /***********************************************************************
      * NOTE: master->value() is already changed before the handler is called
      ***********************************************************************/
     if (imaster->value() == imaster->range().upperBound())
        iservant->spinDown();

     return false;  //allow any other handlers to be called
}
