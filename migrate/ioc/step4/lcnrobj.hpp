/******************************************************************************
* FILE NAME: lcnrobj.hpp                                                      *
*                                                                             *
* DESCRIPTION: Generic container object                                       *
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
