/******************************************************************************
* .FILE:         dmsamp4.cpp                                                  *
*                                                                             *
* .DESCRIPTION:  Direct Manipulation Sample Program 4: Class Implementation   *
*                                                                             *
* .CLASSES:      DMSample4Window                                              *
*                CustomerItem                                                 *
*                MyWindow                                                     *
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
#include "dmsamp4.hpp"

/*------------------------------------------------------------------------------
| main                                                                         |
------------------------------------------------------------------------------*/
int main( int argc, char* argv[] )
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::kOriginLowerLeft );

  /***********************************************************************/
  /* Permit debugging during the drag ...                                */
  /***********************************************************************/
  IDMOperation::setDebugSupport( true );

  /***********************************************************************/
  /* Create window ...                                                   */
  /***********************************************************************/
  DMSample4Window
    frame( argv[1] );

  /***********************************************************************/
  /* Show it ...                                                         */
  /***********************************************************************/
  frame.show();
  IApplication::current().run();
  return 0;
}

/*------------------------------------------------------------------------------
| CustomerItem::CustomerItem                                                   |
|                                                                              |
| Constructor.                                                                 |
------------------------------------------------------------------------------*/
CustomerItem :: CustomerItem ( const IDMItem::Handle& item ) :
                IDMCnrItem ( item )
{
  IString
    rmf1 = IDMItem::rmfFrom( IDM::rmLibrary, IDM::rfSharedMem ),
    rmf2 = IDMItem::rmfFrom( IDM::rmDiscard, IDM::rfUnknown );

  /***********************************************************************/
  /* Get pointer to the associated Customer container object             */
  /***********************************************************************/
  Customer *pCustomer = (Customer *)object();

  /***********************************************************************/
  /* Build and set contents.  We can only do this on the source          */
  /* side.  Note that since we call this constructor on both source      */
  /* and target sides, we must distinguish them.  That is done           */
  /* here by checking the "object" pointer.  If this constructor was     */
  /* called from within our generateSourceItems, then this value         */
  /* will be non-zero.  If called from with the template provider's      */
  /* provideTargetItemFor, then it will be zero.                         */
  /***********************************************************************/
  if (pCustomer)
  {
    IString
      contents,
      delim = '\x01';

    contents += pCustomer->iconText() + delim;
    contents += pCustomer->name() + delim;
    contents += pCustomer->address() + delim;
    contents += pCustomer->phone() + delim;
    contents += pCustomer->iconId();

    setContents( contents );

    /*********************************************************************/
    /* Add RMFs supported by this class (IDMCnrItem will have            */
    /* already specified the other RMFs we use)                          */
    /*********************************************************************/
    addRMF( rmf1 );
    addRMF( rmf2 );
  }
  else
  {
    /*********************************************************************/
    /* On target side, add in <rmLibrary,rfSharedMem> if source concurs  */
    /* (and it's not already in there)...                                */
    /*********************************************************************/
    if ((item->supportsRMF( rmf1 ))  &&
        !(supportsRMF( rmf1 )))
    {
      addRMF( rmf1 );
    }
  }
}

/*------------------------------------------------------------------------------
| CustomerItem::generateSourceItems                                            |
|                                                                              |
| Called to give CustomerItem opportunity to attach new CustomerItem's to the  |
| argument IDMSourceOperation object.                                          |
------------------------------------------------------------------------------*/
bool CustomerItem :: generateSourceItems ( IDMSourceOperation* pSrcOp )
{
  /***********************************************************************/
  /* Get generic container items.  Note that we call the inherited       */
  /* function since it already has logic to deal with multi-selection,   */
  /* etc...                                                              */
  /***********************************************************************/
  bool result = Inherited::generateSourceItems( pSrcOp );

  /***********************************************************************/
  /* Now, replace each IDMCnrItem with a CustomerItem                    */
  /***********************************************************************/
  for (unsigned i = 1; i <= pSrcOp->numberOfItems(); i++)
  {
    pSrcOp->replaceItem( i, new CustomerItem( pSrcOp->item( i ) ) );
  }

  /***********************************************************************/
  /* Set stack3AndFade as the default image style and set the stacking   */
  /* percentage that is used to set the stacking offset as a percentage  */
  /* of the image size.                                                  */
  /***********************************************************************/
  pSrcOp->setImageStyle( IDM::stack3AndFade );
  pSrcOp->setStackingPercentage( IPair( 25, 25 ) );
  return( result );
}

/*------------------------------------------------------------------------------
| CustomerItem::supportedOperationsFor                                         |
|                                                                              |
| Called when a CustomerItem is dropped on a target container.                 |
------------------------------------------------------------------------------*/
unsigned long CustomerItem ::
              supportedOperationsFor ( const IString& rmf ) const
{
  if (rmf == IDMItem::rmfFrom( IDM::rmLibrary, IDM::rfSharedMem ))
  {
    /*********************************************************************/
    /* If using <rmLibrary,rfSharedMem> then only copy is supported      */
    /*********************************************************************/
    return( IDMItem::copyable & supportedOperations() );
  }

  /***********************************************************************/
  /* Otherwise, whatever base class supports...                          */
  /***********************************************************************/
  return( Inherited::supportedOperationsFor( rmf ) );
}

/*------------------------------------------------------------------------------
| CustomerItem::sourceDiscard                                                  |
|                                                                              |
| Called when a CustomerItem is dropped on a Workplace Shell shredder.         |
------------------------------------------------------------------------------*/
bool CustomerItem :: sourceDiscard ( IDMSourceDiscardEvent& event )
{
  /***********************************************************************/
  /* Remove the object from the container                                */
  /***********************************************************************/
  IContainerControl
   *pCnr = (IContainerControl *)(event.sourceOperation()->sourceWindow());
  IContainerObject
   *pCnrObj = (IContainerObject *)(object());

  pCnr->removeObject( pCnrObj );
  return( true );
}

/*------------------------------------------------------------------------------
| CustomerItem::targetDrop                                                     |
|                                                                              |
| Called when a CustomerItem is dropped on a target container.                 |
------------------------------------------------------------------------------*/
bool CustomerItem :: targetDrop ( IDMTargetDropEvent& event )
{
  bool result = true;

  /***********************************************************************/
  /* Check if using ICLUI shared memory rendering format                 */
  /***********************************************************************/
  IString myRMF = IDMItem::rmfFrom( IDM::rmLibrary, IDM::rfSharedMem );
  if (selectedRMF() == myRMF)
  {
    /*********************************************************************/
    /* Yes, construct new Customer object from passed data               */
    /*********************************************************************/
    IString
      contents = this->contents(),
      delim    = '\x01',
      text     = contents.subString( 1, contents.indexOf( delim ) - 1 );

    contents   = contents.subString( contents.indexOf( delim ) + 1 );
    IString
      name     = contents.subString( 1, contents.indexOf( delim ) - 1 );

    contents   = contents.subString( contents.indexOf( delim ) + 1 );
    IString
      addr     = contents.subString( 1, contents.indexOf( delim ) - 1 );

    contents   = contents.subString( contents.indexOf( delim ) + 1 );
    IString
      phone    = contents.subString( 1, contents.indexOf( delim ) - 1 ),
      iconId   = contents.subString( contents.indexOf( delim ) + 1 );

    IContainerControl *pCnr = event.container();
    Customer *pNewCustomer = new Customer( text,
                                           iconId.asUnsigned(),
                                           name,
                                           addr,
                                           phone,
                                           (MyWindow *)(pCnr->parent()) );

    /*********************************************************************/
    /* ...and insert the new Customer object into the container          */
    /*********************************************************************/
    pCnr->addObject( pNewCustomer );

    /*********************************************************************/
    /* Create an IDMItem::Handle                                         */
    /*                                                                   */
    /* Note:  We must break this into 2 statements due to a bug in the   */
    /*        IRefCounted class.  If we use an initializer to create     */
    /*        the handle, this sample will eventually trap due to the    */
    /*        inability of the initializer to properly increment the     */
    /*        drag item object use count:                                */
    /*          IDMItem::Handle thisHandle = this;  //initializer form   */
    /*                                                                   */
    /*        When we break the create into 2 statements, it takes the   */
    /*        form of an assignment which does not have the problem.     */
    /*********************************************************************/
    IDMItem::Handle thisHandle;
    thisHandle = this;

    /*********************************************************************/
    /* Position the object within the container                          */
    /*********************************************************************/
    IPoint pos = targetOperation()->dropPosition( thisHandle, event );
    pCnr->moveObjectTo( pNewCustomer,
                        0,
                        pCnr,
                        0,
                        pos );
  }
  else
  {
    /*********************************************************************/
    /* Some other RMF, base class must support it                        */
    /*********************************************************************/
    result = Inherited::targetDrop( event );
  }

  return( result );
}

/*------------------------------------------------------------------------------
| DMSample4Window::DMSample4Window                                             |
|                                                                              |
| Constructor.                                                                 |
------------------------------------------------------------------------------*/
DMSample4Window :: DMSample4Window ( const char* aTitle ) :
                   MyWindow( WND_MAIN ),
                   title( this )
{
  /***********************************************************************/
  /* Set title                                                           */
  /***********************************************************************/
  if (aTitle)
    title.setTitleText( aTitle );
  else
    title.setTitleText( WND_MAIN );

  /***********************************************************************/
  /* Tailor the container                                                */
  /***********************************************************************/
  this->cnrCtl->hideTitle();
  this->cnrCtl->showIconView();
  this->cnrCtl->arrangeIconView();
  this->cnrCtl->setExtendedSelection();

  /***********************************************************************/
  /* Set the item provider                                               */
  /***********************************************************************/
  this->cnrCtl->setItemProvider( &this->provider );

  /***********************************************************************/
  /* Enable drag/drop                                                    */
  /***********************************************************************/
  IString sTitle = aTitle;
  if (sTitle.includes( STR_SOURCE_ONLY))
    IDMHandler::enableDragFrom( this->cnrCtl );
  else
  {
    if (sTitle.includes(SET_ONLY))
      IDMHandler::enableDropOn( this->cnrCtl );
    else
      IDMHandler::enableDragDropFor( this->cnrCtl );
  }

  /***********************************************************************/
  /* Resize the container                                                */
  /***********************************************************************/
  this->sizeTo( ISize( 250, 275 ) );
}

/*------------------------------------------------------------------------------
| MyWindow::MyWindow                                                           |
|                                                                              |
| Constructor.                                                                 |
------------------------------------------------------------------------------*/
MyWindow :: MyWindow ( unsigned long windowId ) :
            IFrameWindow ( windowId ),

            cnrCtl (new IContainerControl (windowId + 20, this, this, IRectangle())),

            car ((Customer *) 0),
            space ((Customer *) 0),
            bolt ((Customer *) 0),
            starfleet ((Customer *) 0),

            reslib()
{
  /***********************************************************************/
  /* Set the icon                                                        */
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
  ITitle title (this, TITLE_SOURCE );

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
            ulIconId ( cnrobj.iconId() ),
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
                       ulIconId ( Icon ),
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


