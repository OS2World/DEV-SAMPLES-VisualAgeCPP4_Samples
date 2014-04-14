/******************************************************************************
* .FILE:         alistbox.cpp                                                 *
*                                                                             *
* .DESCRIPTION:  List Box Sample Program:  Class Implementation               *
*                                                                             *
* .CLASSES:      AListBox                                                     *
*                ACommandHandler                                              *
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
#include <iapp.hpp>
#include <istattxt.hpp>
#include <ilistbox.hpp>
#include <irect.hpp>
#include <imenubar.hpp>
#include <istring.hpp>
#include <iinfoa.hpp>
#include <itrace.hpp>
#include <imsgbox.hpp>
#include <iexcbase.hpp>
#include <ireslib.hpp>
#include <icoordsy.hpp>
#include "alistbox.h"
#include "alistbox.hpp"

/*****************************************************************************
* main  - Application entry point                                            *
*****************************************************************************/
int main()
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::kOriginLowerLeft );
  AListBox mainWindow (WND_MAIN);
  IApplication::current().run();
  return 0;
} /* end main */


/******************************************************************************
* Class AListBox :: AListBox - constructor for main window                    *
*                                                                             *
* Define itself as an IFrame Window                                           *
* Create a listbox.                                                           *
* Create the trace listbox.                                                   *
* Create the info area, the status line, and the menu bar.                    *
******************************************************************************/
AListBox :: AListBox(unsigned long windowId)
  : IFrameWindow( IFrameWindow::defaultStyle()
            | IFrameWindow::accelerator
            | IFrameWindow::minimizedIcon,
            windowId),
    listbox(WND_HELLO, this, this, IRectangle(),  //Create listbox
            (IListBox::defaultStyle()
            | IListBox::multipleSelect)
            & ~IListBox::horizontalScroll),
    listbox2(WND_HELLO, this, this, IRectangle(), //Create trace listbox
            IListBox::defaultStyle()
            & ~IListBox::horizontalScroll),
    infoArea(this),
    statusLine(WND_STATUS, this, this),
    menuBar(WND_MAIN, this),
    commandhandler(this,&listbox)
{
/*----------------------------------------------------------------------------|
| Set the alignment of the status line and add it to the frame extension.     |
-----------------------------------------------------------------------------*/
  statusLine.setAlignment(
    IStaticText::centerLeft);
  addExtension(&statusLine,
    IFrameWindow::aboveClient, 30UL);
  setStatus();

/*----------------------------------------------------------------------------|
| Add the listbox as an extension 1/2 the size of the client and set the      |
| trace listbox as the rest of the client space.                              |
-----------------------------------------------------------------------------*/
  addExtension(&listbox,
    IFrameWindow::leftOfClient, 0.5);
  setClient(&listbox2);

  commandhandler.handleEventsFor(this);

/*----------------------------------------------------------------------------|
| Set the size of the main window, update the main window, set focus and then |
| show the main window.                                                       |
-----------------------------------------------------------------------------*/
  sizeTo(ISize(400,300));
  update();
  setFocus();
  show();

} /* end AListBox :: AListBox(...) */

/******************************************************************************
* class AListBox :: output - output status data to listbox2                   *
******************************************************************************/
AListBox& AListBox :: output( const IString& astr )
{
/*----------------------------------------------------------------------------|
| Add the string to listbox2                                                  |
| If the listbox has more than 7 lines, scroll                                |
-----------------------------------------------------------------------------*/
  listbox2.addAsLast( astr );
  if ( listbox2.count() > 7 )
    listbox2.setTop( listbox2.count()-7 );
  return *this;
}

/******************************************************************************
* class AListBox :: setStatus - set the status line text                      *
******************************************************************************/
AListBox& AListBox :: setStatus()
{
/*----------------------------------------------------------------------------|
| Get the resource library                                                    |
| Load a string from the resource library                                     |
| Concatenate the count to the string                                         |
| Set the infoarea text to the string                                         |
-----------------------------------------------------------------------------*/
  IResourceLibrary reslib;
  IString str=reslib.loadString(STR_INFO);
  str += listbox.count();
  statusLine.setText(str);
  return *this;
}

/******************************************************************************
* class ACommandHandler::ACommandHandler - Constructor for the command handler*
*                                                                             *
* Stores pointers to the main window and the listbox.                         *
******************************************************************************/
ACommandHandler::ACommandHandler(AListBox *alb,IListBox *lb1)
    : alistbox(alb)
    , listbox1(lb1)
{
}


/******************************************************************************
* AListBox :: command - command handler                                       *
******************************************************************************/
bool ACommandHandler :: command(ICommandEvent & cmdEvent)
{
  IResourceLibrary rlib;
  bool fProcessed = true;

  switch (cmdEvent.commandId()) {

    case MI_SELECT_ALL:
/*----------------------------------------------------------------------------|
| Select all the items in listbox1                                            |
-----------------------------------------------------------------------------*/
      listbox1->selectAll();
      break;

    case MI_DESELECT_ALL:
/*----------------------------------------------------------------------------|
| Deselect all the items in listbox1                                          |
-----------------------------------------------------------------------------*/
      listbox1->deselectAll();
      break;

    case MI_ADD_ITEMS:
/*----------------------------------------------------------------------------|
| Add string items from the resource library to listbox1                      |
| Update the status                                                           |
-----------------------------------------------------------------------------*/
      listbox1->addAsLast(STR_LIST_ITEM1);
      listbox1->addAsLast(STR_LIST_ITEM2);
      listbox1->addAsLast(STR_LIST_ITEM3);
      listbox1->addAsLast(STR_LIST_ITEM4);
      listbox1->addAsLast(STR_LIST_ITEM5);
      alistbox->setStatus();
      break;

    case MI_READ_SEL_ITEMS:
      {
/*----------------------------------------------------------------------------|
| Create a listbox cursor for selected items                                  |
| Output each line to alistbox                                                |
| Output the number of selected items                                         |
-----------------------------------------------------------------------------*/
        IListBox::Cursor lbCursor( *listbox1 );
        for ( lbCursor.setToFirst(); lbCursor.isValid(); lbCursor.setToNext() )
        {
          alistbox->output( IString(
                            IString( lbCursor.asIndex() )
                            + " - "
                            + listbox1->elementAt( lbCursor )));
        }
        alistbox->output( IString( rlib.loadString( STR_SELECTEDITEMS )
                          + IString( listbox1->numberOfSelections() )));
        break;
      }

    case MI_READ_ALL_ITEMS:
      {
/*----------------------------------------------------------------------------|
| Create a listbox cursor for selected items                                  |
| Output each line to alistbox                                                |
-----------------------------------------------------------------------------*/
        IListBox::Cursor lbCursor( *listbox1, IListBox::Cursor::allItems );
        for ( lbCursor.setToFirst(); lbCursor.isValid(); lbCursor.setToNext() )
        {
          alistbox->output( IString(
                            IString( lbCursor.asIndex() )
                            + " - "
                            + listbox1->elementAt( lbCursor )));
        }
        alistbox->output( IString( rlib.loadString( STR_NUMBERITEMS )
                          + IString( listbox1->count() )));
        break;
      }


    default:
      fProcessed = false;              // event not processed
      break;
  } /* end switch */

  return fProcessed;
} /* end command(...) */
