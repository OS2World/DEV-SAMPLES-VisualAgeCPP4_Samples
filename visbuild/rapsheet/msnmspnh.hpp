#ifndef _MSNMSPNH_
#define _MSNMSPNH_
/******************************************************************************
* .FILE:        msnmspnh.hpp                                                  *
*                                                                             *
* .DESCRIPTION: Header file for the class MasterServantNumSpinHandler         *
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
#include <ispinhdr.hpp>              // ISpinHandler, parent class, which
                                     // indirectly includes IControlEvent.

//forward class references
class INumericSpinButton;

//**************************************************************************
// Class:   MasterServantNumSpinHandler
//
// Purpose: Supports the master and servant spin buttons used to represent
//          servant and inch fields.
//
//***************************************************************************
class MasterServantNumSpinHandler : public ISpinHandler
{

public:
   MasterServantNumSpinHandler(INumericSpinButton * master,
                     INumericSpinButton * servant);
   virtual ~MasterServantNumSpinHandler();     //destructor

protected:
   virtual bool arrowUp(IControlEvent& controlEvent);
   virtual bool arrowDown(IControlEvent& controlEvent);

private:
   INumericSpinButton * imaster;
   INumericSpinButton * iservant;

};   //MasterServantNumSpinHandler

#endif
