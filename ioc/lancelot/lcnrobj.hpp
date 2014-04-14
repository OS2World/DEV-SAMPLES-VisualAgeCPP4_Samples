/******************************************************************************
* .FILE:         lcnrobj.hpp                                                  *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Definition       *
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
#ifndef _LCNROBJ_
#define _LCNROBJ_
#include <icnrobj.hpp>
#include <istring.hpp>
#include <ireslib.hpp>

/******************************************************************************
* Class LCnrObject - Generic container object                                 *
******************************************************************************/
class LCnrObject : public IContainerObject
{
   public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in three of four ways:                                 |
| 1) String title, icon resourceId.                                           |
| 2) ResourceId title, icon resourceId.                                       |
| 3) Existing object                                                          |
-----------------------------------------------------------------------------*/
      LCnrObject( IString title, unsigned long icon );

      LCnrObject( IResourceId title, unsigned long icon );

      LCnrObject( const LCnrObject& cnrobj );

     ~LCnrObject();

/*------------------------------- Accessors -----------------------------------
| These functions provide a means of getting and setting the accessible       |
| attributes of instances of this class:                                      |
|   incrementUsage      - Increments the cnr object usage count               |
|   decrementUsage      - Decrements the cnr object usage count               |
|   usageCount          - Returns the current usage count for the cnr object  |
-----------------------------------------------------------------------------*/
      inline LCnrObject
         &incrementUsage() { incrementUseCount(); return *this; };
      inline LCnrObject
         &decrementUsage() { decrementUseCount(); return *this; };

      inline unsigned long
         usageCount() { return useCount(); };
};
#endif
