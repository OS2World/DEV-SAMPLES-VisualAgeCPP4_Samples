/******************************************************************************
* .FILE:         dmsamp3.cpp                                                  *
*                                                                             *
* .DESCRIPTION:  Direct Manipulation Sample Program 3: Class Implementation   *
*                                                                             *
* .CLASSES:      MyWindow                                                     *
*                MySourceWin                                                  *
*                MyTargetWin                                                  *
*                Customer                                                     *
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
#include <icoordsy.hpp>
#include "dmsamp3.hpp"

/*------------------------------------------------------------------------------
| main                                                                         |
------------------------------------------------------------------------------*/
int main()
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::kOriginLowerLeft );
   MySourceWin sourceWin (WND_SOURCE);
   MyTargetWin targetWin (WND_TARGET);
   IApplication::current().run();
   return 0;
}


/*------------------------------------------------------------------------------
| MyWindow::MyWindow                                                           |
|                                                                              |
| Constructor.                                                                 |
------------------------------------------------------------------------------*/
MyWindow :: MyWindow ( unsigned long windowId ) :
            IFrameWindow ( windowId ),

            cnrCtl (new IContainerControl (windowId + 20, this, this, IRectangle()
              ,IContainerControl::classDefaultStyle
              ,IContainerControl::classDefaultAttribute | IContainerControl::treeView)),

            car ((Customer *) 0),
            space ((Customer *) 0),
            bolt ((Customer *) 0),
            starfleet ((Customer *) 0),

            reslib()
{
  /***********************************************************************/
  /* Set the frame icon                                                  */
  /* Set the container as the frame client.                              */
  /***********************************************************************/
  setIcon( id() );
  setClient(cnrCtl);

  /***********************************************************************/
  /* Create the container objects ...                                    */
  /***********************************************************************/
  car =       new Customer (reslib.loadString(STR_ITEM_11)
                           , CAR
                           ,reslib.loadString(STR_ITEM_12)
                           ,reslib.loadString(STR_ITEM_13)
                           ,reslib.loadString(STR_ITEM_14)
                           ,this);
  space =     new Customer (reslib.loadString(STR_ITEM_21)
                           , SPACE
                           ,reslib.loadString(STR_ITEM_22)
                           ,reslib.loadString(STR_ITEM_23)
                           ,reslib.loadString(STR_ITEM_24)
                           ,this);
  bolt =      new Customer (reslib.loadString(STR_ITEM_31)
                           , BOLT
                           ,reslib.loadString(STR_ITEM_32)
                           ,reslib.loadString(STR_ITEM_33)
                           ,reslib.loadString(STR_ITEM_34)
                           ,this);
  starfleet = new Customer (reslib.loadString(STR_ITEM_41)
                           , STARFLEET
                           ,reslib.loadString(STR_ITEM_42)
                           ,reslib.loadString(STR_ITEM_43)
                           ,reslib.loadString(STR_ITEM_44)
                           ,this);
  /***********************************************************************/
  /* and add them to the container.                                      */
  /***********************************************************************/
  cnrCtl->addObject(car);
  cnrCtl->addObject(space);
  cnrCtl->addObject(bolt);
  cnrCtl->addObject(starfleet, space);

  /***********************************************************************/
  /* Set the container's attributes.                                     */
  /***********************************************************************/
  cnrCtl->setDeleteObjectsOnClose();
  cnrCtl->showTreeLine();
  cnrCtl->showTitle();
  cnrCtl->enableDrawItem();

  /***********************************************************************/
  /* Container view will be tree icon view.                              */
  /***********************************************************************/
  cnrCtl->showTreeIconView();

  /***********************************************************************/
  /* Show it ...                                                         */
  /***********************************************************************/
  show();
  cnrCtl->show();
}

/*------------------------------------------------------------------------------
| MySourceWin::MySourceWin                                                     |
|                                                                              |
| Constructor.                                                                 |
------------------------------------------------------------------------------*/
MySourceWin :: MySourceWin ( unsigned long windowId ) :
               MyWindow ( windowId )
{
  ITitle title (this,TITLE_SOURCE  );

  /***********************************************************************/
  /* Enable the source for dragging from (only).                         */
  /***********************************************************************/
  IDMHandler::enableDragFrom( cnrCtl );
};

/*------------------------------------------------------------------------------
| MyTargetWin::MyTargetWin                                                     |
|                                                                              |
| Constructor.                                                                 |
------------------------------------------------------------------------------*/
MyTargetWin :: MyTargetWin ( unsigned long windowId ) :
               MyWindow ( windowId )
{
  ITitle title (this, TITLE_TARGET );

  /***********************************************************************/
  /* Enable the target for dropping on (only).                           */
  /***********************************************************************/
  IDMHandler::enableDropOn( cnrCtl );
}

/*------------------------------------------------------------------------------
| Custoner::Customer                                                           |
|                                                                              |
| Copy constructor.                                                            |
------------------------------------------------------------------------------*/
Customer :: Customer ( const Customer &cnrobj )  :
            IContainerObject ( (const IContainerObject &)cnrobj ),
            strName ( cnrobj.name() ),
            strAddress ( cnrobj.address() ),
            strPhone ( cnrobj.phone() ),
            myWin ( cnrobj.myWin )
{
}

/*------------------------------------------------------------------------------
| Custoner::Customer                                                           |
|                                                                              |
| Constructor.                                                                 |
------------------------------------------------------------------------------*/
Customer :: Customer ( const IString &Text,
                       unsigned long Icon,
                       const IString &Name,
                       const IString &Address,
                       const IString &Phone,
                       MyWindow* win )  :
                       IContainerObject ( Text, Icon ),
                       strName ( Name ),
                       strAddress ( Address ),
                       strPhone ( Phone ),
                       myWin ( win )
{
}

/*------------------------------------------------------------------------------
| Customer::objectCopy                                                         |
|                                                                              |
| Make a copy of the Customer object.  Called by                               |
| IContainerObject::copyObjectTo().                                            |
------------------------------------------------------------------------------*/
IContainerObject* Customer :: objectCopy()
{
  /***********************************************************************/
  /* Use Customer copy constructor to make a copy of the object.         */
  /***********************************************************************/
  Customer *copy = new Customer(*this);
  return((IContainerObject *)copy);
}

