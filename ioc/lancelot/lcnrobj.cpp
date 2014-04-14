/******************************************************************************
* .FILE:         lcnrobj.cpp                                                  *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Implementation   *
*                                                                             *
* .CLASSES:      LCnrObject                                                   *
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
#include "lcnrobj.hpp"

/******************************************************************************
* Class LCnrObject :: LCnrObject - Constructor for the cnr object given a     *
*   string title.                                                             *
*                                                                             *
* Define yourself as an IContainerObject                                      *
******************************************************************************/
LCnrObject::LCnrObject( IString title, unsigned long icon )
     :IContainerObject     ( title, icon )
{
/*-----------------------------------------------------------------------------
| Decrement object usage count                                                |
-----------------------------------------------------------------------------*/
   decrementUsage();
}


/******************************************************************************
* Class LCnrObject :: LCnrObject - Constructor for the cnr object given a     *
*   resourceId title.                                                         *
*                                                                             *
* Define yourself as an IContainerObject                                      *
******************************************************************************/
LCnrObject::LCnrObject( IResourceId title, unsigned long icon )
     :IContainerObject     ( title, icon )
{
/*-----------------------------------------------------------------------------
| Decrement object usage count                                                |
-----------------------------------------------------------------------------*/
   decrementUsage();
}


/******************************************************************************
* Class LCnrObject :: LCnrObject - Constructor for the cnr object given an    *
*   existing cnr object.                                                      *
*                                                                             *
* Define yourself as an IContainerObject                                      *
******************************************************************************/
LCnrObject::LCnrObject( const LCnrObject& cnrobj )
     :IContainerObject     ( (const IContainerObject&) cnrobj )
{}


/******************************************************************************
* Class LCnrObject :: ~LCnrObject - Destructor for the info window            *
******************************************************************************/
LCnrObject::~LCnrObject()
{}
