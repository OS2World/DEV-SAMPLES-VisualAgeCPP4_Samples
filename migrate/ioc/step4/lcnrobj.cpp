/******************************************************************************
* FILE NAME: lcnrobj.cpp                                                      *
*                                                                             *
* Classes:                                                                    *
*   LCnrObject                                                                *
*                                                                             *
* COPYRIGHT:                                                                  *
*   Licensed Materials - Property of IBM                                      *
*   (C) Copyright IBM Corporation 1992, 1995                                  *
*   All Rights Reserved                                                       *
*   US Government Users Restricted Rights - Use, duplication, or disclosure   *
*   restricted by GSA ADP Schedule Contract with IBM Corp.                    *
******************************************************************************/

#ifndef _IBASE_                         //Make sure ibase.hpp is included
  #include <ibase.hpp>                  //  since that is where IC_<environ>
#endif                                  //  is defined.
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
