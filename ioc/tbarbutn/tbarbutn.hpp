/******************************************************************************
* .FILE:         tbarbutn.hpp                                                 *
*                                                                             *
* .DESCRIPTION:  Tool Bar Button Sample:  Class Header                        *
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
#ifndef _TBARBUTN_HPP_
#define _TBARBUTN_HPP_
#include <ifont.hpp>
#include <iframe.hpp>
#include <itbar.hpp>
#include <itbarbut.hpp>
#include <imle.hpp>
#include <icmdhdr.hpp>
#include <imenubar.hpp>
#include <iflytext.hpp>
#include <istattxt.hpp>
#include <iflyhhdr.hpp>
#include <icombobx.hpp>
#include <iselhdr.hpp>
#include <ititle.hpp>

class MainWindow;

/******************************************************************************
* Class ACommandHandler - Processes command events                            *
******************************************************************************/
class ACommandHandler: public ICommandHandler
{
  public:
/*------------------------------- Constructor --------------------------------|
| Constructs the object with:                                                 |
| 1) Pointers to the mle, toolbar, and edit font.                             |
-----------------------------------------------------------------------------*/
    ACommandHandler ( MainWindow * win )
      : mainWin( win )
    {
    }
/*-----------------------------------------------------------------------------
| command - an overloaded function that processes command events              |
-----------------------------------------------------------------------------*/
    virtual bool
      command ( ICommandEvent& event );

  private:
    MainWindow
     *mainWin;
};

/******************************************************************************
* Class MainWindow - Main window                                              *
******************************************************************************/
class MainWindow : public IFrameWindow
{
  public:
/*------------------------------- Constructor --------------------------------|
| Constructs the object with:                                                 |
| 1) No parameters                                                            |
-----------------------------------------------------------------------------*/
    MainWindow();

/*-----------------------------------------------------------------------------
| tbar1 - returns a reference to the toolbar 1                                |
| tbar2 - returns a reference to the toolbar 2                                |
| tbar3 - returns a reference to the toolbar 3                                |
| tbar4 - returns a reference to the toolbar 4                                |
| tbar5 - returns a reference to the toolbar 5                                |
| tbar6 - returns a reference to the toolbar 6                                |
| tbar7 - returns a reference to the toolbar 7                                |
| textWindow - returns a reference to the text window                         |
| menu  - returns a reference to the menubar                                  |
-----------------------------------------------------------------------------*/
    IToolBar
     *tbar1 ( ) { return &toolBar1; }
    IToolBar
     *tbar2 ( ) { return &toolBar2; }
    IToolBar
     *tbar3 ( ) { return &toolBar3; }
    IToolBar
     *tbar4 ( ) { return &toolBar4; }
    IToolBar
     *tbar5 ( ) { return &toolBar5; }
    IToolBar
     *tbar6 ( ) { return &toolBar6; }
    IToolBar
     *tbar7 ( ) { return &toolBar7; }
    IStaticText
     *textWindow ( ) { return &textClient; }
    IMenuBar
     *menuBar  ( ) { return &menu; }

  private:
    ITitle
      title;
    IMenuBar
      menu;
    IToolBar
      toolBar1,
      toolBar2,
      toolBar3,
      toolBar4,
      toolBar5,
      toolBar6,
      toolBar7;
    IFlyText
      flyText;
    IStaticText
      infoText;
    IFlyOverHelpHandler
      flyHelpHandler;
    IStaticText
      textClient;
    ACommandHandler
      commandhandler;

/*-----------------------------------------------------------------------------
| These are all the IOC supplies toolbar buttons                              |
-----------------------------------------------------------------------------*/
    //These are all the IOC supplied buttons:
    IToolBarButton
      IC_ID_OPEN_button,
      IC_ID_NEW_button,
      IC_ID_SAVE_button,
      IC_ID_SAVE_AS_button,
      IC_ID_PRINT_button,
      IC_ID_PRINTPREVIEW_button,
      IC_ID_PRINTSETUP_button,
      IC_ID_SETTINGS_button,
      IC_ID_VPAPALETTE_button,

      IC_ID_SELECTALL_button,
      IC_ID_DESELECTALL_button,
      IC_ID_CUT_button,
      IC_ID_COPY_button,
      IC_ID_PASTE_button,
      IC_ID_PASTESPECIAL_button,
      IC_ID_PASTELINK_button,
      IC_ID_LOCATE_button,

      IC_ID_BOLD_button,
      IC_ID_ITALIC_button,
      IC_ID_UNDERSCORE_button,
      IC_ID_DOUBLEUNDERSCORE_button,
      IC_ID_NORMAL_button,
      IC_ID_JUSTIFY_button,
      IC_ID_LEFT_button,
      IC_ID_CENTER_button,
      IC_ID_RIGHT_button,

      IC_ID_SORTAZ_button,
      IC_ID_SORTZA_button,
      IC_ID_SORTUP_button,
      IC_ID_SORTDOWN_button,
      IC_ID_LEFTALIGNOBJ_button,
      IC_ID_RIGHTALIGNOBJ_button,
      IC_ID_CLEAR_button,
      IC_ID_DELETE_button,
      IC_ID_CANCELOPERATION_button,

      IC_ID_INSERTCOLUMN_button,
      IC_ID_INSERTROW_button,
      IC_ID_DELETECOLUMNS_button,
      IC_ID_DELETEROWS_button,
      IC_ID_UNDO_button,
      IC_ID_REDO_button,
      IC_ID_CHECKSPELLING_button,
      IC_ID_TOOLBAR_button,
      IC_ID_TOOLBARSETUP_button,

      IC_ID_ZOOM_button,
      IC_ID_ZOOMIN_button,
      IC_ID_ZOOMOUT_button,
      IC_ID_UPDATE_button,
      IC_ID_MAILSEND_button,
      IC_ID_MOVEPAGES_button,
      IC_ID_RUNSCRIPT_button,
      IC_ID_LOGON_button,
      IC_ID_LOGOFF_button,

      IC_ID_HELP_button,
      IC_ID_GENERALHELP_button,
      IC_ID_HELPINDEX_button,
      IC_ID_HELPTUTORIAL_button,
      IC_ID_USINGHELP_button,
      IC_ID_TOUR_button,
      IC_ID_ABOUT_button,
      IC_ID_EXIT_button,
      IC_ID_DEFAULT_button;
};

#endif /* _TBARBUTN_HPP_ */
