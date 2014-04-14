/******************************************************************************
* .FILE: acnr.cpp                                                             *
*                                                                             *
* .DESCRIPTION: Container sample application                                  *
*                                                                             *
* .CLASSES:                                                                   *
*   ACnrexWindow                                                              *
*   ACommandHandler                                                           *
*   Department                                                                *
*   ADepartmentView                                                           *
*   ACnrHandler                                                               *
*   ACnrMenuHandler                                                           *
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
******************************************************************************/

#include <iapp.hpp>
#include <icolor.hpp>
#include <istattxt.hpp>
#include <ipopmenu.hpp>
#include <imenubar.hpp>
#include <imenuhdr.hpp>
#include <icnr.hpp>
#include <ireslib.hpp>
#include <imle.hpp>
#include <istring.hpp>
#include <imsgbox.hpp>
#include <iframe.hpp>
#include <icoordsy.hpp>
#include "acnr.hpp"
#include "acnr.h"

int main()
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::kOriginLowerLeft );

/*-----------------------------------------------------------------------------
| Create the main frame window that contains the container.                   |
 ----------------------------------------------------------------------------*/
  ACnrexWindow mainWindow (WND_MAIN);

/*-----------------------------------------------------------------------------
| If in the Windows environment, also create a main frame window that contains|
|   the PM compatible container.                                              |
 ----------------------------------------------------------------------------*/
  #ifdef IC_WIN
  IContainerControl::setDefaultStyle( IContainerControl::defaultStyle() |
                                      IContainerControl::pmCompatible );
  ACnrexWindow mainWindow2 (WND_MAIN_2);
  #endif

/*-----------------------------------------------------------------------------
| Start the application message loop.                                         |
 ----------------------------------------------------------------------------*/
  IApplication::current().run();

  return 0;
} /* end main */

/******************************************************************************
* Class ACnrexWindow :: ACnrexWincow - Constructor for the main window        *
*                                                                             *
* Create yourself as an IFrameWindow, title will default to window id resource*
* Create menubar                                                              *
* Create container                                                            *
* Create container columns                                                    *
* Create command handler                                                      *
* Create container handler                                                    *
* Create container menu handler                                               *
* Create container edit handler                                               *
******************************************************************************/
ACnrexWindow::ACnrexWindow( unsigned long windowId )
  :IFrameWindow( IFrameWindow::defaultStyle()
                | IFrameWindow::minimizedIcon
                ,windowId )
  ,menuBar( WND_MAIN, this )
  ,cnr( CNR_RESID, this, this )
  ,colIcon( IContainerColumn::isIcon )
  ,colName( IContainerColumn::isIconViewText )
  ,colCode( ICONTAINERCOLUMN_OFFSETOF( Department, strCode ))
  ,colAddress( ICONTAINERCOLUMN_OFFSETOF( Department, strAddress ))
  ,cmdHdr( this, &menuBar, &cnr, &colName, &colCode, &colAddress )
  ,cnrHdr()
  ,cnrMenuHdr( &cnr )
  ,cnrEditHdr()
{


/*-----------------------------------------------------------------------------
| Attach the command handler to the frame window                              |
| Attach the container handler to the container                               |
| Attach the container edit handler to the container                          |
| Attach the container menu handler to the container                          |
 ----------------------------------------------------------------------------*/
  cmdHdr.handleEventsFor( this );
  cnrHdr.handleEventsFor( &cnr );
  cnrEditHdr.handleEventsFor( &cnr );
  cnrMenuHdr.handleEventsFor( &cnr );

/*-----------------------------------------------------------------------------
| Set the container for extended selections                                   |
 ----------------------------------------------------------------------------*/
  cnr.setExtendedSelection();

/*-----------------------------------------------------------------------------
| Set the text of the column headings for details view                        |
 ----------------------------------------------------------------------------*/
  colIcon.setHeadingText( STR_ICON );
  colName.setHeadingText( STR_DEPT );
  colCode.setHeadingText( STR_CODE );
  colAddress.setHeadingText( STR_ADDR );

/*-----------------------------------------------------------------------------
| Show column separators                                                      |
 ----------------------------------------------------------------------------*/
  colIcon.showSeparators( IContainerColumn::horizontalSeparator );
  colName.showSeparators( IContainerColumn::verticalSeparator );
  colCode.showSeparators();
  colAddress.showSeparators();

/*-----------------------------------------------------------------------------
| Add the columns to the container                                            |
 ----------------------------------------------------------------------------*/
  cnr.addColumn( &colIcon );
  cnr.addColumn( &colName );
  cnr.addColumn( &colCode );
  cnr.addColumn( &colAddress );

/*-----------------------------------------------------------------------------
| Set the details view split at 350 pixels                                    |
| Automatically delete the container objects when closed                      |
 ----------------------------------------------------------------------------*/
  cnr.setDetailsViewSplit( &colName, 350 );
  cnr.setDeleteObjectsOnClose();

/*-----------------------------------------------------------------------------
| Begin using our resource library in order to load strings and icons for     |
|   the container objects.                                                    |
| Create container objects dept1 - dept6                                      |
 ----------------------------------------------------------------------------*/
  IResourceLibrary reslib;

  dept1=new Department(reslib.loadString(STR_ITEM_11),
                       reslib.loadIcon(IBMLOGO),
                       reslib.loadString(STR_ITEM_12),
                       reslib.loadString(STR_ITEM_13));

  dept2=new Department(reslib.loadString(STR_ITEM_21),
                       reslib.loadIcon(CLOGO),
                       reslib.loadString(STR_ITEM_22),
                       reslib.loadString(STR_ITEM_23));

  dept3=new Department(reslib.loadString(STR_ITEM_31),
                       reslib.loadIcon(WLOGO),
                       reslib.loadString(STR_ITEM_32),
                       reslib.loadString(STR_ITEM_33));

  dept4=new Department(reslib.loadString(STR_ITEM_41),
                       reslib.loadIcon(OSLOGO),
                       reslib.loadString(STR_ITEM_42),
                       reslib.loadString(STR_ITEM_43));

  dept5=new Department(reslib.loadString(STR_ITEM_51),
                       reslib.loadIcon(IBMLOGO),
                       reslib.loadString(STR_ITEM_52),
                       reslib.loadString(STR_ITEM_53));

  dept6=new Department(reslib.loadString(STR_ITEM_61),
                       reslib.loadIcon(IBMLOGO),
                       reslib.loadString(STR_ITEM_62),
                       reslib.loadString(STR_ITEM_63));

/*-----------------------------------------------------------------------------
| Allow an edit field for the container columns                               |
| Allow the container object data to also be updated directly by the user     |
 ----------------------------------------------------------------------------*/
  colName.enableDataUpdate();
  colCode.enableDataUpdate();
  colAddress.enableDataUpdate();

  dept1->enableDataUpdate();
  dept2->enableDataUpdate();
  dept3->enableDataUpdate();
  dept4->enableDataUpdate();
  dept5->enableDataUpdate();
  dept6->enableDataUpdate();

/*-----------------------------------------------------------------------------
| Add the objects to the container.  dept2 and dept3 are under dept1.         |
 ----------------------------------------------------------------------------*/
  cnr.addObject( dept1 );
  cnr.addObject( dept2, dept1 );
  cnr.addObject( dept3, dept1 );
  cnr.addObject( dept4, dept1 );
  cnr.addObject( dept5 );
  cnr.addObject( dept6 );

/*-----------------------------------------------------------------------------
| Arrange the container objects for icon view                                 |
| Set the container title from the resource library                           |
| Show container title                                                        |
| Show container tree-icon view                                               |
 ----------------------------------------------------------------------------*/
  cnr.arrangeIconView();
  cnr.setTitle( STR_CNRTITLE );
  cnr.showTitle();
  cnr.showTreeIconView();

/*-----------------------------------------------------------------------------
| Since we are initially in tree-icon view, disabled the "Mark All" and       |
|   "Unmark All" menu items.  These functions are not supported for this view.|
 ----------------------------------------------------------------------------*/
  menuBar.disableItem( ID_MARKALL );
  menuBar.disableItem( ID_UNMARKALL );

/*-----------------------------------------------------------------------------
| Set the frame window's client to the container                              |
| Set the focus to the container instead of the frame window.  This is needed |
|   because containers handle many of the keyboard and mouse events that the  |
|   frame normally handles for controls.  But we want these events to be      |
|   processed by the container first such as <ENTER> and <TAB>.               |
| Show the frame window                                                       |
 ----------------------------------------------------------------------------*/
  setClient( &cnr );
  cnr.setFocus();
  show();

} /* end ACnrexWindow :: ACnrexWindow(...) */


/******************************************************************************
* Class Department :: Department - Constructor for container objects          *
*                                                                             *
* Create yourself as an IContainerObject                                      *
* Store the strings for Code and Address                                      *
******************************************************************************/
Department::Department( const IString& Name,
                const IPointerHandle& Icon,
                const IString& Code,
                const IString& Address )
  :IContainerObject( Name, Icon )
  ,strCode( Code )
  ,strAddress( Address )
{
}


/******************************************************************************
* Class Department :: handleOpen - Override container handler function to     *
*   process open requests                                                     *
******************************************************************************/
void Department::handleOpen (IContainerControl* container)
{
/*-----------------------------------------------------------------------------
| Create a department view window                                             |
| To avoid memory leaks, auto delete the C++ view window when GUI window is   |
|   closed                                                                    |
 ----------------------------------------------------------------------------*/
  ADepartmentView* view = new ADepartmentView( this, container );
  view->setAutoDeleteObject();
}


/******************************************************************************
* Class ADepartmentView :: ADepartmentView - Constructor for viewing          *
*   department information                                                    *
*                                                                             *
* Create yourself as an IFrameWindow                                          *
* Create a static text                                                        *
******************************************************************************/
ADepartmentView::ADepartmentView (Department * aDept,
                                  IContainerControl* anOwner)
  :IFrameWindow( WND_DEPT, IWindow::desktopWindow(), anOwner )
  ,stext( WND_CNREX, this, this )
{
/*-----------------------------------------------------------------------------
| Visually indicate the object is open                                        |
| Store the department information.                                           |
 ----------------------------------------------------------------------------*/
  aDept->setOpen();
  saveDept=aDept;

/*-----------------------------------------------------------------------------
| Set the static text to the deparment's icon text                            |
| Center the text                                                             |
 ----------------------------------------------------------------------------*/
  stext.setText( aDept->iconText() );
  stext.setAlignment( IStaticText::centerCenter );

/*-----------------------------------------------------------------------------
| Set the frame window's client to the static text                            |
| Size the frame window                                                       |
| Set the focus and show the window                                           |
 ----------------------------------------------------------------------------*/
  setClient( &stext );
  sizeTo( ISize( 400, 300 ));
  setFocus().show();
}


/******************************************************************************
* Class ADepartmentView :: ~ADepartmentView - Destructor                      *
******************************************************************************/
ADepartmentView :: ~ADepartmentView ()
{
/*-----------------------------------------------------------------------------
| Visually indicate the object is closed                                      |
 ----------------------------------------------------------------------------*/
  saveDept->setClosed();
}


/******************************************************************************
* Class ACommandHandler :: ACommandHandler - Constructor for a command handler*
*                                                                             *
* Create yourself as an ICommandHandler                                       *
* Store the owner window                                                      *
* Store the owner window menubar                                              *
* Store the owner window container                                            *
* Store the owner window container column for Name                            *
* Store the owner window container column for Code                            *
* Store the owner window container column for Address                         *
******************************************************************************/
ACommandHandler::ACommandHandler( ACnrexWindow* window,
                    IMenuBar* menuBar,
                    IContainerControl* cnr,
                    IContainerColumn* colName,
                    IContainerColumn* colCode,
                    IContainerColumn* colAddr )
  :ICommandHandler()
  ,pwin( window )
  ,pmenu( menuBar )
  ,pcnr( cnr )
  ,pcolName( colName )
  ,pcolCode( colCode )
  ,pcolAddr( colAddr )
{
}


/******************************************************************************
* Class ACommandHandler :: command - Override command handler function for    *
*   handling commands                                                         *
******************************************************************************/
bool ACommandHandler::command( ICommandEvent& event )
{

  switch( event.commandId() )
  {
    case ID_VTEXT:
    {
/*-----------------------------------------------------------------------------
| Enable the mark-all and unmark-all menu items for this container view       |
| Show the text-view                                                          |
 ----------------------------------------------------------------------------*/
      pmenu->enableItem( ID_MARKALL );
      pmenu->enableItem( ID_UNMARKALL );
      pcnr->showTextView();
      break;
    }

    case ID_VFTEXT:
    {
/*-----------------------------------------------------------------------------
| Enable the mark-all and unmark-all menu items for this container view       |
| Show the flowed-text view                                                   |
 ----------------------------------------------------------------------------*/
      pmenu->enableItem( ID_MARKALL );
      pmenu->enableItem( ID_UNMARKALL );
      pcnr->showFlowedTextView();
      break;
    }

    case ID_VNAME:
    {
/*-----------------------------------------------------------------------------
| Enable the mark-all and unmark-all menu items for this container view       |
| Show the name view                                                          |
 ----------------------------------------------------------------------------*/
      pmenu->enableItem( ID_MARKALL );
      pmenu->enableItem( ID_UNMARKALL );
      pcnr->showNameView();
      break;
    }

    case ID_VFNAME:
    {
/*-----------------------------------------------------------------------------
| Enable the mark-all and unmark-all menu items for this container view       |
| Show the flowed-name view                                                   |
 ----------------------------------------------------------------------------*/
      pmenu->enableItem( ID_MARKALL );
      pmenu->enableItem( ID_UNMARKALL );
      pcnr->showFlowedNameView();
      break;
    }

    case ID_VDETAILS:
    {
/*-----------------------------------------------------------------------------
| Enable the mark-all and unmark-all menu items for this container view       |
| Show the flowed-name view                                                   |
 ----------------------------------------------------------------------------*/
      pmenu->enableItem(ID_MARKALL);  //Enable Mark All Menu Item
      pmenu->enableItem(ID_UNMARKALL);//Enable Mark All Menu Item
      pcnr->showDetailsView();
      break;
    }

    case ID_FILTER1:
    {
/*-----------------------------------------------------------------------------
| Get the selected container objects                                          |
| Filter and show these container objects                                     |
 ----------------------------------------------------------------------------*/
      SelectedObjectsFilter selObjects;
      pcnr->filter( selObjects );
      break;
    }

    case ID_FILTER2:
    {
/*-----------------------------------------------------------------------------
| Get all the container objects                                               |
| Filter and show these container objects                                     |
 ----------------------------------------------------------------------------*/
      AllObjectsFilter allObjects;
      pcnr->filter( allObjects );
      break;
    }

    case ID_SORT1:
    {
/*-----------------------------------------------------------------------------
| Sort the container based on the Icon Text.                                  |
| We call a container function to do this.                                    |
 ----------------------------------------------------------------------------*/
      pcnr->sortByIconText ( true );
      break;
    }

    case ID_SORT2:
    {
/*-----------------------------------------------------------------------------
| Sort the container based on the Code Text.                                  |
| We must create an instance of the SortByCode class and pass this in.        |
 ----------------------------------------------------------------------------*/
      SortByCode   sortByCode;
      pcnr->sort( sortByCode );
      break;
    }

    case ID_VTICON:
    {
/*-----------------------------------------------------------------------------
| Disable the mark-all and unmark-all menu items for this container view      |
| Show the tree-icon view                                                     |
 ----------------------------------------------------------------------------*/
      pmenu->disableItem( ID_MARKALL );
      pmenu->disableItem( ID_UNMARKALL );
      pcnr->showTreeIconView();
      break;
    }

    case ID_VTTEXT:
    {
/*-----------------------------------------------------------------------------
| Disable the mark-all and unmark-all menu items for this container view      |
| Show the tree-text view                                                     |
 ----------------------------------------------------------------------------*/
      pmenu->disableItem( ID_MARKALL );
      pmenu->disableItem( ID_UNMARKALL );
      pcnr->showTreeTextView();
      break;
    }

    case ID_VTNAME:
/*-----------------------------------------------------------------------------
| Disable the mark-all and unmark-all menu items for this container view      |
| Show the tree-name view                                                     |
 ----------------------------------------------------------------------------*/
    {
      pmenu->disableItem( ID_MARKALL );
      pmenu->disableItem( ID_UNMARKALL );
      pcnr->showTreeNameView();
      break;
    }

    case ID_VICON:
    {
/*-----------------------------------------------------------------------------
| Enable the mark-all and unmark-all menu items for this container view       |
| Show the icon view                                                          |
 ----------------------------------------------------------------------------*/
      pmenu->enableItem( ID_MARKALL );
      pmenu->enableItem( ID_UNMARKALL );
      pcnr->showIconView();
      break;
    }

    case ID_VARRANGE:
    {
/*-----------------------------------------------------------------------------
| Enable the mark-all and unmark-all menu items for this container view       |
| Arrange the icons                                                           |
 ----------------------------------------------------------------------------*/
      pmenu->enableItem( ID_MARKALL );
      pmenu->enableItem( ID_UNMARKALL );
      pcnr->arrangeIconView();
      break;
    }

    case ID_MARKALL:
    {
/*-----------------------------------------------------------------------------
| Get all the container objects                                               |
| Try to select all the container objects                                     |
 ----------------------------------------------------------------------------*/
      IContainerControl::ObjectCursor CO1 ( *pcnr );
      for ( CO1.setToFirst(); CO1.isValid(); CO1.setToNext() )
      {
        try
        {
          pcnr->setSelected( pcnr->objectAt( CO1 ));
        }
        catch( IException& exc )
        {
        }
      }
      break;
    }

    case ID_UNMARKALL:
    {
/*-----------------------------------------------------------------------------
| Get all the container objects                                               |
| Try to deselect all the container objects                                   |
 ----------------------------------------------------------------------------*/
      IContainerControl::ObjectCursor CO2 ( *pcnr );
      for ( CO2.setToFirst(); CO2.isValid(); CO2.setToNext() )
      {
        try
        {
          pcnr->removeSelected( pcnr->objectAt( CO2 ));
        }
        catch( IException& exc )
        {
        }
      }
      break;
    }

    case MI_EDRECORD:
    {
/*-----------------------------------------------------------------------------
| Get the cursored container objects                                          |
| Initialize the cursor to the first object                                   |
| Edit the current container object                                           |
 ----------------------------------------------------------------------------*/
      IContainerControl::ObjectCursor CO3 ( *pcnr, IContainerObject::cursored );
      CO3.setToFirst();
      pcnr->editObject( CO3.current() );
      break;
    }

    case MI_EDNAME:
    {
/*-----------------------------------------------------------------------------
| Get the cursored container objects                                          |
| Initialize the cursor to the first object                                   |
| Edit the current container object's column                                  |
 ----------------------------------------------------------------------------*/
      IContainerControl::ObjectCursor CO3 ( *pcnr, IContainerObject::cursored );
      CO3.setToFirst();
      pcnr->editObject( CO3.current(), pcolName );
      break;
    }

    case MI_EDCODE:
    {
/*-----------------------------------------------------------------------------
| Get the cursored container objects                                          |
| Initialize the cursor to the first object                                   |
| Edit the current container object's column                                  |
 ----------------------------------------------------------------------------*/
      IContainerControl::ObjectCursor CO3 ( *pcnr, IContainerObject::cursored );
      CO3.setToFirst();
      pcnr->editObject( CO3.current(), pcolCode );
      break;
    }

    case MI_EDADDRESS:
    {
/*-----------------------------------------------------------------------------
| Get the cursored container objects                                          |
| Initialize the cursor to the first object                                   |
| Edit the current container object's column                                  |
 ----------------------------------------------------------------------------*/
      IContainerControl::ObjectCursor CO3 ( *pcnr, IContainerObject::cursored );
      CO3.setToFirst();
      pcnr->editObject( CO3.current(), pcolAddr );
      break;
    }
  }  /* end switch */
  return(false);
}


/******************************************************************************
* Class ACnrMenuHandler :: makePopUpMenu - Override container menu handler    *
*   function for creating popup menus                                         *
******************************************************************************/
bool ACnrMenuHandler::makePopUpMenu( IMenuEvent& event )
{
/*-----------------------------------------------------------------------------
| If a valid container object, continue                                       |
 ----------------------------------------------------------------------------*/
  if ( popupMenuObject() )
  {
/*-----------------------------------------------------------------------------
| Create a popup menu                                                         |
| If not in details view, disable editing of Name, Code, and Address columsn. |
 ----------------------------------------------------------------------------*/
    IPopUpMenu* popUp = new IPopUpMenu( ID_POPMENU,
                event.window() );
    if ( !pcnr->isDetailsView() )
    {
      popUp->disableItem( MI_EDNAME );
      popUp->disableItem( MI_EDCODE );
      popUp->disableItem( MI_EDADDRESS );
    }
    else
    {
/*-----------------------------------------------------------------------------
| Disable editing of the object                                               |
 ----------------------------------------------------------------------------*/
      popUp->disableItem( MI_EDRECORD );
    }

/*-----------------------------------------------------------------------------
| To avoid memory leaks, auto delete the C++ popup menu when the GUI popup    |
|   window closes                                                             |
| Show the popup menu at the current mouse position                           |
| Visually indicate the container object is the source for this action        |
| Visually indicate the container object is the current cursor                |
 ----------------------------------------------------------------------------*/
    popUp->setAutoDeleteObject();
    pcnr->showSourceEmphasis( popupMenuObject() );
    pcnr->setCursor( popupMenuObject() );
    popUp->show( event.mousePosition() );
    return true;
  }
  return false;
};


int SortByCode::isEqual( IContainerObject*  object1,
                         IContainerObject*  object2,
                         IContainerControl* container ) const
{
  return container->nlsCompare(((Department*)object1)->Code(),
                               ((Department*)object2)->Code());
}
