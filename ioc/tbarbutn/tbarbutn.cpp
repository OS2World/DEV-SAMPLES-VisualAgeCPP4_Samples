/******************************************************************************
* .FILE:         tbarbutn.cpp                                                 *
*                                                                             *
* .DESCRIPTION:  Tool Bar Button Sample:  Class Implementation                *
*                                                                             *
* .CLASSES:      MainWindow                                                   *
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
#include <iframe.hpp>
#include <ifont.hpp>
#include <itbar.hpp>
#include <itbarbut.hpp>
#include <icmdhdr.hpp>
#include <imenubar.hpp>
#include <iflytext.hpp>
#include <istattxt.hpp>
#include <iflyhhdr.hpp>
#include <icoordsy.hpp>
#include "tbarbutn.hpp"
#include "tbarbutn.h"

/******************************************************************************
* main - Application entry point                                              *
******************************************************************************/
int main()
{
   ICoordinateSystem::setApplicationOrientation(
           ICoordinateSystem::kOriginLowerLeft );


   //Note that the default button text for a small number of buttons
   //have 2 lines of text.  If you do not set setStandardTextLines to 2,
   //the second line of text will be truncated.  The default setting is
   //is still 1 (as in previous releases) because the majority of the
   //buttons have 1 line text.  Furthurmore, for buttons with 2 lines
   //of text, if the second line is truncated, the first line is
   //meaningfull enough, when combined with flyoverhelp text to still
   //be meaningful.

   //This line can be uncommented to view the toolbar with 2 lines of text
   //IToolBarButton::setStandardTextLines(2);

   MainWindow mainWin;
   IApplication::current().run();
   return 0;
}

/******************************************************************************
* class Editor::Editor - Constructor for main windows                         *
*                                                                             *
* Initialize the main window.                                                 *
* Initialize the title bar                                                    *
* Initialize the fly over help and text                                       *
* Initialize the static text (client)                                         *
* Initialize the toolbar and all of the controls associated with the toolbar  *
* Initialize the menu                                                         *
* Initialize the fontSelectHandler and the command Handler                    *
******************************************************************************/

MainWindow::MainWindow ()
       :IFrameWindow(ID_MAIN_WINDOW),
        title(this),
        menu(ID_MAIN_WINDOW,this),
        flyText(ID_FLYTEXT, &toolBar1),
        infoText(ID_INFOTEXT, this, this),
        flyHelpHandler(&flyText, &infoText, 0, 0),
        textClient(ID_TEXTCLIENT, this, this),
        toolBar1(ID_TOOLBAR+1, this, IToolBar::aboveClient, false,
                IToolBar::classDefaultStyle
                | IToolBar::dragDrop),
        toolBar2(ID_TOOLBAR+2, this, IToolBar::aboveClient, false,
                IToolBar::classDefaultStyle
                | IToolBar::dragDrop),
        toolBar3(ID_TOOLBAR+3, this, IToolBar::aboveClient, false,
                IToolBar::classDefaultStyle
                | IToolBar::dragDrop),
        toolBar4(ID_TOOLBAR+4, this, IToolBar::aboveClient, false,
                IToolBar::classDefaultStyle
                | IToolBar::dragDrop),
        toolBar5(ID_TOOLBAR+5, this, IToolBar::aboveClient, false,
                IToolBar::classDefaultStyle
                | IToolBar::dragDrop),
        toolBar6(ID_TOOLBAR+6, this, IToolBar::aboveClient, false,
                IToolBar::classDefaultStyle
                | IToolBar::dragDrop),
        toolBar7(ID_TOOLBAR+7, this, IToolBar::aboveClient, false,
                IToolBar::classDefaultStyle
                | IToolBar::dragDrop),
        commandhandler( this ),

        //The following are all the IOC supplied bmps
        //I have placed them in 6 different toolbars and made a quick
        //attempt at organizing them
        IC_ID_OPEN_button             (IC_ID_OPEN,
                                       &toolBar1, &toolBar1),
        IC_ID_NEW_button              (IC_ID_NEW,
                                       &toolBar1, &toolBar1),
        IC_ID_SAVE_button             (IC_ID_SAVE,
                                       &toolBar1, &toolBar1),
        IC_ID_SAVE_AS_button          (IC_ID_SAVE_AS,
                                       &toolBar1, &toolBar1),
        IC_ID_PRINT_button            (IC_ID_PRINT,
                                       &toolBar1, &toolBar1),
        IC_ID_PRINTPREVIEW_button     (IC_ID_PRINTPREVIEW,
                                       &toolBar1, &toolBar1),
        IC_ID_PRINTSETUP_button       (IC_ID_PRINTSETUP,
                                       &toolBar1, &toolBar1),
        IC_ID_SETTINGS_button         (IC_ID_SETTINGS,
                                       &toolBar1, &toolBar1),
        IC_ID_VPAPALETTE_button       (IC_ID_VPAPALETTE,
                                       &toolBar1, &toolBar1),

        IC_ID_SELECTALL_button        (IC_ID_SELECTALL,
                                       &toolBar2, &toolBar2),
        IC_ID_DESELECTALL_button      (IC_ID_DESELECTALL,
                                       &toolBar2, &toolBar2),
        IC_ID_CUT_button              (IC_ID_CUT,
                                       &toolBar2, &toolBar2),
        IC_ID_COPY_button             (IC_ID_COPY,
                                       &toolBar2, &toolBar2),
        IC_ID_PASTE_button            (IC_ID_PASTE,
                                       &toolBar2, &toolBar2),
        IC_ID_PASTESPECIAL_button     (IC_ID_PASTESPECIAL,
                                       &toolBar2, &toolBar2),
        IC_ID_PASTELINK_button        (IC_ID_PASTELINK,
                                       &toolBar2, &toolBar2),
        IC_ID_LOCATE_button           (IC_ID_LOCATE,
                                       &toolBar2, &toolBar2),

        IC_ID_BOLD_button             (IC_ID_BOLD,
                                       &toolBar3, &toolBar3),
        IC_ID_ITALIC_button           (IC_ID_ITALIC,
                                       &toolBar3, &toolBar3),
        IC_ID_UNDERSCORE_button       (IC_ID_UNDERSCORE,
                                       &toolBar3, &toolBar3),
        IC_ID_DOUBLEUNDERSCORE_button (IC_ID_DOUBLEUNDERSCORE,
                                       &toolBar3, &toolBar3),
        IC_ID_NORMAL_button           (IC_ID_NORMAL,
                                       &toolBar3, &toolBar3),
        IC_ID_JUSTIFY_button          (IC_ID_JUSTIFY,
                                       &toolBar3, &toolBar3),
        IC_ID_LEFT_button             (IC_ID_LEFT,
                                       &toolBar3, &toolBar3),
        IC_ID_CENTER_button           (IC_ID_CENTER,
                                       &toolBar3, &toolBar3),
        IC_ID_RIGHT_button            (IC_ID_RIGHT,
                                       &toolBar3, &toolBar3),

        IC_ID_SORTAZ_button           (IC_ID_SORTAZ,
                                       &toolBar4, &toolBar4),
        IC_ID_SORTZA_button           (IC_ID_SORTZA,
                                       &toolBar4, &toolBar4),
        IC_ID_SORTUP_button           (IC_ID_SORTUP,
                                       &toolBar4, &toolBar4),
        IC_ID_SORTDOWN_button         (IC_ID_SORTDOWN,
                                       &toolBar4, &toolBar4),
        IC_ID_LEFTALIGNOBJ_button     (IC_ID_LEFTALIGNOBJ,
                                       &toolBar4, &toolBar4),
        IC_ID_RIGHTALIGNOBJ_button    (IC_ID_RIGHTALIGNOBJ,
                                       &toolBar4, &toolBar4),
        IC_ID_CLEAR_button            (IC_ID_CLEAR,
                                       &toolBar4, &toolBar4),
        IC_ID_DELETE_button           (IC_ID_DELETE,
                                       &toolBar4, &toolBar4),
        IC_ID_CANCELOPERATION_button  (IC_ID_CANCELOPERATION,
                                       &toolBar4, &toolBar4),

        IC_ID_INSERTCOLUMN_button     (IC_ID_INSERTCOLUMN,
                                       &toolBar5, &toolBar5),
        IC_ID_INSERTROW_button        (IC_ID_INSERTROW,
                                       &toolBar5, &toolBar5),
        IC_ID_DELETECOLUMNS_button    (IC_ID_DELETECOLUMNS,
                                       &toolBar5, &toolBar5),
        IC_ID_DELETEROWS_button       (IC_ID_DELETEROWS,
                                       &toolBar5, &toolBar5),
        IC_ID_UNDO_button             (IC_ID_UNDO,
                                       &toolBar5, &toolBar5),
        IC_ID_REDO_button             (IC_ID_REDO,
                                       &toolBar5, &toolBar5),
        IC_ID_CHECKSPELLING_button    (IC_ID_CHECKSPELLING,
                                       &toolBar5, &toolBar5),
        IC_ID_TOOLBAR_button          (IC_ID_TOOLBAR,
                                       &toolBar5, &toolBar5),
        IC_ID_TOOLBARSETUP_button     (IC_ID_TOOLBARSETUP,
                                       &toolBar5, &toolBar5),

        IC_ID_ZOOM_button             (IC_ID_ZOOM,
                                       &toolBar6, &toolBar6),
        IC_ID_ZOOMIN_button           (IC_ID_ZOOMIN,
                                       &toolBar6, &toolBar6),
        IC_ID_ZOOMOUT_button          (IC_ID_ZOOMOUT,
                                       &toolBar6, &toolBar6),
        IC_ID_UPDATE_button           (IC_ID_UPDATE,
                                       &toolBar6, &toolBar6),
        IC_ID_MAILSEND_button         (IC_ID_MAILSEND,
                                       &toolBar6, &toolBar6),
        IC_ID_MOVEPAGES_button        (IC_ID_MOVEPAGES,
                                       &toolBar6, &toolBar6),
        IC_ID_RUNSCRIPT_button        (IC_ID_RUNSCRIPT,
                                       &toolBar6, &toolBar6),
        IC_ID_LOGON_button            (IC_ID_LOGON,
                                       &toolBar6, &toolBar6),
        IC_ID_LOGOFF_button           (IC_ID_LOGOFF,
                                       &toolBar6, &toolBar6),

        IC_ID_HELP_button             (IC_ID_HELP,
                                       &toolBar7, &toolBar7),
        IC_ID_GENERALHELP_button      (IC_ID_GENERALHELP,
                                       &toolBar7, &toolBar7),
        IC_ID_HELPINDEX_button        (IC_ID_HELPINDEX,
                                       &toolBar7, &toolBar7),
        IC_ID_HELPTUTORIAL_button     (IC_ID_HELPTUTORIAL,
                                       &toolBar7, &toolBar7),
        IC_ID_USINGHELP_button        (IC_ID_USINGHELP,
                                       &toolBar7, &toolBar7),
        IC_ID_TOUR_button             (IC_ID_TOUR,
                                       &toolBar7, &toolBar7),
        IC_ID_ABOUT_button            (IC_ID_ABOUT,
                                       &toolBar7, &toolBar7),
        IC_ID_EXIT_button             (IC_ID_EXIT,
                                       &toolBar7, &toolBar7),

        //This is what happens when a user creates a button that has
        //no ID assigned.  IOC has a default button that it loads on
        //the user's behalf.
        //0x9999 is an ID that has no bitmap assigned
        IC_ID_DEFAULT_button          (0x9999,
                                       &toolBar7, &toolBar7)
{

/*----------------------------------------------------------------------------|
| Set the icon and title text                                                 |
-----------------------------------------------------------------------------*/
   setIcon( id() );
   title.setTitleText(ID_MAIN_WINDOW);


/*----------------------------------------------------------------------------|
| Add the buttons to the toolbar                                              |
-----------------------------------------------------------------------------*/
   /* ---------------- ToolBar 1 --------------------*/
   toolBar1.addAsLast(&IC_ID_OPEN_button, true);
   toolBar1.addAsLast(&IC_ID_NEW_button);
   toolBar1.addAsLast(&IC_ID_SAVE_button);
   toolBar1.addAsLast(&IC_ID_SAVE_AS_button);
   toolBar1.addAsLast(&IC_ID_PRINT_button, true);
   toolBar1.addAsLast(&IC_ID_PRINTPREVIEW_button);
   toolBar1.addAsLast(&IC_ID_PRINTSETUP_button);
   toolBar1.addAsLast(&IC_ID_SETTINGS_button, true);
   toolBar1.addAsLast(&IC_ID_VPAPALETTE_button);

   /* ---------------- ToolBar 2 --------------------*/
   toolBar2.addAsLast(&IC_ID_SELECTALL_button);
   toolBar2.addAsLast(&IC_ID_DESELECTALL_button);
   toolBar2.addAsLast(&IC_ID_CUT_button, true);
   toolBar2.addAsLast(&IC_ID_COPY_button);
   toolBar2.addAsLast(&IC_ID_PASTE_button);
   toolBar2.addAsLast(&IC_ID_PASTESPECIAL_button);
   toolBar2.addAsLast(&IC_ID_PASTELINK_button);
   toolBar2.addAsLast(&IC_ID_LOCATE_button, true);

   /* ---------------- ToolBar 3 --------------------*/
   toolBar3.addAsLast(&IC_ID_BOLD_button);
   toolBar3.addAsLast(&IC_ID_ITALIC_button);
   toolBar3.addAsLast(&IC_ID_UNDERSCORE_button);
   toolBar3.addAsLast(&IC_ID_DOUBLEUNDERSCORE_button);
   toolBar3.addAsLast(&IC_ID_NORMAL_button);
   toolBar3.addAsLast(&IC_ID_JUSTIFY_button, true);
   toolBar3.addAsLast(&IC_ID_LEFT_button);
   toolBar3.addAsLast(&IC_ID_CENTER_button);
   toolBar3.addAsLast(&IC_ID_RIGHT_button);

   /* ---------------- ToolBar 4 --------------------*/
   toolBar4.addAsLast(&IC_ID_SORTAZ_button);
   toolBar4.addAsLast(&IC_ID_SORTZA_button);
   toolBar4.addAsLast(&IC_ID_SORTUP_button);
   toolBar4.addAsLast(&IC_ID_SORTDOWN_button);
   toolBar4.addAsLast(&IC_ID_LEFTALIGNOBJ_button, true);
   toolBar4.addAsLast(&IC_ID_RIGHTALIGNOBJ_button);
   toolBar4.addAsLast(&IC_ID_CLEAR_button, true);
   toolBar4.addAsLast(&IC_ID_DELETE_button);
   toolBar4.addAsLast(&IC_ID_CANCELOPERATION_button);

   /* ---------------- ToolBar 5 --------------------*/
   toolBar5.addAsLast(&IC_ID_INSERTCOLUMN_button);
   toolBar5.addAsLast(&IC_ID_DELETECOLUMNS_button);
   toolBar5.addAsLast(&IC_ID_INSERTROW_button);
   toolBar5.addAsLast(&IC_ID_DELETEROWS_button);
   toolBar5.addAsLast(&IC_ID_UNDO_button, true);
   toolBar5.addAsLast(&IC_ID_REDO_button);
   toolBar5.addAsLast(&IC_ID_CHECKSPELLING_button, true);
   toolBar5.addAsLast(&IC_ID_TOOLBAR_button, true);
   toolBar5.addAsLast(&IC_ID_TOOLBARSETUP_button);

   /* ---------------- ToolBar 6 --------------------*/
   toolBar6.addAsLast(&IC_ID_ZOOM_button);
   toolBar6.addAsLast(&IC_ID_ZOOMIN_button);
   toolBar6.addAsLast(&IC_ID_ZOOMOUT_button);
   toolBar6.addAsLast(&IC_ID_UPDATE_button, true);
   toolBar6.addAsLast(&IC_ID_MAILSEND_button);
   toolBar6.addAsLast(&IC_ID_MOVEPAGES_button);
   toolBar6.addAsLast(&IC_ID_RUNSCRIPT_button);
   toolBar6.addAsLast(&IC_ID_LOGON_button, true);
   toolBar6.addAsLast(&IC_ID_LOGOFF_button);

   /* ---------------- ToolBar 7 --------------------*/
   toolBar7.addAsLast(&IC_ID_HELP_button);
   toolBar7.addAsLast(&IC_ID_GENERALHELP_button);
   toolBar7.addAsLast(&IC_ID_HELPINDEX_button);
   toolBar7.addAsLast(&IC_ID_HELPTUTORIAL_button);
   toolBar7.addAsLast(&IC_ID_USINGHELP_button);
   toolBar7.addAsLast(&IC_ID_TOUR_button, true);
   toolBar7.addAsLast(&IC_ID_ABOUT_button);
   toolBar7.addAsLast(&IC_ID_EXIT_button, true);
   toolBar7.addAsLast(&IC_ID_DEFAULT_button, true);

/*----------------------------------------------------------------------------|
| Set up title for toolbar when floating                                      |
-----------------------------------------------------------------------------*/
   toolBar1.setFloatingTitle(STR_TOOLBAR+1);
   toolBar2.setFloatingTitle(STR_TOOLBAR+2);
   toolBar3.setFloatingTitle(STR_TOOLBAR+3);
   toolBar4.setFloatingTitle(STR_TOOLBAR+4);
   toolBar5.setFloatingTitle(STR_TOOLBAR+5);
   toolBar6.setFloatingTitle(STR_TOOLBAR+6);
   toolBar7.setFloatingTitle(STR_TOOLBAR+7);

/*----------------------------------------------------------------------------|
| Set alignment of the static text to center                                  |
| Set the client                                                              |
-----------------------------------------------------------------------------*/
   textClient.setAlignment( IStaticText::centerCenter );
   setClient(&textClient);

/*----------------------------------------------------------------------------|
| Add the info frame extension                                                |
-----------------------------------------------------------------------------*/
   addExtension(&infoText, IFrameWindow::belowClient);

/*----------------------------------------------------------------------------|
| Set up and add the help handler                                             |
-----------------------------------------------------------------------------*/
//Note that IOC supplies default short and long text for each of
//these bitmaps.  This samples does not supply its own text, it sets
//the resource library and table offsets to use the IOC supplied short and
//long text.
   flyHelpHandler.setResourceLibrary(
     IApplication::current().resourceLibrary().fileName() );
   flyHelpHandler.setFlyTextStringTableOffset(IC_FLYTEXTOFFSET);
   flyHelpHandler.setLongStringTableOffset(IC_LONGTEXTOFFSET);

   flyHelpHandler.handleEventsFor(&toolBar1);
   flyHelpHandler.handleEventsFor(&toolBar2);
   flyHelpHandler.handleEventsFor(&toolBar3);
   flyHelpHandler.handleEventsFor(&toolBar4);
   flyHelpHandler.handleEventsFor(&toolBar5);
   flyHelpHandler.handleEventsFor(&toolBar6);
   flyHelpHandler.handleEventsFor(&toolBar7);

/*----------------------------------------------------------------------------|
| For Motif, disable the Floating menuitem.                                   |
-----------------------------------------------------------------------------*/
#ifdef IC_MOTIF
                                            // On Motif, changing a toolbar location
                                            // to floating is not allowed.  Only
                                            // the initial location can be set
                                            // to floating.  Therefore, disable
                                            // the menuitem on Motif since it
                                            // would have no effect.
  menu.enableItem( ID_TOOLBAR_FLOATING, false );
#endif

/*----------------------------------------------------------------------------|
| Attach the Command Handler to the frame                                     |
-----------------------------------------------------------------------------*/
   commandhandler.handleEventsFor(this);

/*-----------------------------------------------------------------------------
| Resize the frame window based on the minimum width of toolbar 7             |
-----------------------------------------------------------------------------*/
   IRectangle
      clientRect = clientRectFor( rect() );
   moveSizeToClient( IRectangle( clientRect.bottomLeft(),
                     IPoint( clientRect.left() + toolBar7.minimumSize().width(),
                     clientRect.top() ) ) );

   setFocus().show();
}


/******************************************************************************
* class ACommandHandler::command - Handles menu bar selections and toolbar    *
*   selections.                                                               *
******************************************************************************/
bool ACommandHandler::command(ICommandEvent &event)
{
   switch (event.commandId())
   {
     case ID_SHOWTEXT:
     {
         mainWin->tbar1()->setButtonView(IToolBarButton::textView);
         mainWin->tbar2()->setButtonView(IToolBarButton::textView);
         mainWin->tbar3()->setButtonView(IToolBarButton::textView);
         mainWin->tbar4()->setButtonView(IToolBarButton::textView);
         mainWin->tbar5()->setButtonView(IToolBarButton::textView);
         mainWin->tbar6()->setButtonView(IToolBarButton::textView);
         mainWin->tbar7()->setButtonView(IToolBarButton::textView);
         break;
     }
     case ID_SHOWBITMAPS:
     {
         mainWin->tbar1()->setButtonView(IToolBarButton::bitmapView);
         mainWin->tbar2()->setButtonView(IToolBarButton::bitmapView);
         mainWin->tbar3()->setButtonView(IToolBarButton::bitmapView);
         mainWin->tbar4()->setButtonView(IToolBarButton::bitmapView);
         mainWin->tbar5()->setButtonView(IToolBarButton::bitmapView);
         mainWin->tbar6()->setButtonView(IToolBarButton::bitmapView);
         mainWin->tbar7()->setButtonView(IToolBarButton::bitmapView);
         break;
     }
     case ID_SHOWTEXTANDBITMAPS:
     {
         mainWin->tbar1()->setButtonView(IToolBarButton::bitmapAndTextView);
         mainWin->tbar2()->setButtonView(IToolBarButton::bitmapAndTextView);
         mainWin->tbar3()->setButtonView(IToolBarButton::bitmapAndTextView);
         mainWin->tbar4()->setButtonView(IToolBarButton::bitmapAndTextView);
         mainWin->tbar5()->setButtonView(IToolBarButton::bitmapAndTextView);
         mainWin->tbar6()->setButtonView(IToolBarButton::bitmapAndTextView);
         mainWin->tbar7()->setButtonView(IToolBarButton::bitmapAndTextView);
         break;
     }
     case ID_TOOLBAR_TOP:
     {
         if ( mainWin->tbar1()->isMoveValid(IToolBar::aboveClient) )
         {
           mainWin->tbar1()->setLocation(IToolBar::aboveClient);
           mainWin->tbar2()->setLocation(IToolBar::aboveClient);
           mainWin->tbar3()->setLocation(IToolBar::aboveClient);
           mainWin->tbar4()->setLocation(IToolBar::aboveClient);
           mainWin->tbar5()->setLocation(IToolBar::aboveClient);
           mainWin->tbar6()->setLocation(IToolBar::aboveClient);
           mainWin->tbar7()->setLocation(IToolBar::aboveClient);
         }
         break;
     }
     case ID_TOOLBAR_BOTTOM:
     {
         if ( mainWin->tbar1()->isMoveValid(IToolBar::belowClient) )
         {
           mainWin->tbar1()->setLocation(IToolBar::belowClient);
           mainWin->tbar2()->setLocation(IToolBar::belowClient);
           mainWin->tbar3()->setLocation(IToolBar::belowClient);
           mainWin->tbar4()->setLocation(IToolBar::belowClient);
           mainWin->tbar5()->setLocation(IToolBar::belowClient);
           mainWin->tbar6()->setLocation(IToolBar::belowClient);
           mainWin->tbar7()->setLocation(IToolBar::belowClient);
         }
         break;
     }
     case ID_TOOLBAR_LEFT:
     {
         if ( mainWin->tbar1()->isMoveValid(IToolBar::leftOfClient) )
         {
           mainWin->tbar1()->setLocation(IToolBar::leftOfClient);
           mainWin->tbar2()->setLocation(IToolBar::leftOfClient);
           mainWin->tbar3()->setLocation(IToolBar::leftOfClient);
           mainWin->tbar4()->setLocation(IToolBar::leftOfClient);
           mainWin->tbar5()->setLocation(IToolBar::leftOfClient);
           mainWin->tbar6()->setLocation(IToolBar::leftOfClient);
           mainWin->tbar7()->setLocation(IToolBar::leftOfClient);
         }
         break;
     }
     case ID_TOOLBAR_RIGHT:
     {
         if ( mainWin->tbar1()->isMoveValid(IToolBar::rightOfClient) )
         {
           mainWin->tbar1()->setLocation(IToolBar::rightOfClient);
           mainWin->tbar2()->setLocation(IToolBar::rightOfClient);
           mainWin->tbar3()->setLocation(IToolBar::rightOfClient);
           mainWin->tbar4()->setLocation(IToolBar::rightOfClient);
           mainWin->tbar5()->setLocation(IToolBar::rightOfClient);
           mainWin->tbar6()->setLocation(IToolBar::rightOfClient);
           mainWin->tbar7()->setLocation(IToolBar::rightOfClient);
         }
         break;
     }
     case ID_TOOLBAR_FLOATING:
     {
         if ( mainWin->tbar1()->isMoveValid(IToolBar::floating) )
         {
           mainWin->tbar1()->setLocation(IToolBar::floating);
           mainWin->tbar2()->setLocation(IToolBar::floating);
           mainWin->tbar3()->setLocation(IToolBar::floating);
           mainWin->tbar4()->setLocation(IToolBar::floating);
           mainWin->tbar5()->setLocation(IToolBar::floating);
           mainWin->tbar6()->setLocation(IToolBar::floating);
           mainWin->tbar7()->setLocation(IToolBar::floating);
         }
         break;
     }
     case ID_TOOLBAR_HIDE:
     {
         bool isVis = mainWin->tbar1()->isVisible();
         mainWin->menuBar()->checkItem( ID_TOOLBAR_HIDE, isVis );
         mainWin->tbar1()->show( !isVis );
         mainWin->tbar2()->show( !isVis );
         mainWin->tbar3()->show( !isVis );
         mainWin->tbar4()->show( !isVis );
         mainWin->tbar5()->show( !isVis );
         mainWin->tbar6()->show( !isVis );
         mainWin->tbar7()->show( !isVis );
         break;
     }

     default:
     {
         mainWin->textWindow()->setText(
           IResourceId( STR_BUTTONID_BASE + event.commandId() ) );
         break;
     }
   }
   return false;
}
