/******************************************************************************
* .FILE:         tbar1.hpp                                                    *
*                                                                             *
* .DESCRIPTION:  Tool Bar Example 1:  Class Header                            *
*                                                                             *
* .CLASSES:      FontSelectHandler                                            *
*                ACommandHandler                                              *
*                Editor                                                       *
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
#ifndef _TBAR1_
#define _TBAR1_
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

class Editor;

/******************************************************************************
* Class  FontSelectHandler - Handles the selection of a font from the font    *
*   font combo box on the tool bar.                                           *
******************************************************************************/
class FontSelectHandler : public ISelectHandler
{
public:
/*------------------------------- Constructor --------------------------------|
| Constructs the object with:                                                 |
| 1) A reference to the Editor (main window)                                  |
-----------------------------------------------------------------------------*/
  FontSelectHandler ( Editor& editor ) : editorFrame(editor) {}

protected:
/*-----------------------------------------------------------------------------
| enter - an overloaded function that process selections                      |
-----------------------------------------------------------------------------*/
virtual bool
  enter ( IControlEvent& event );

private:
  Editor
   &editorFrame;
};


/******************************************************************************
* Class ACommandHandler - Processes command events                            *
******************************************************************************/
class ACommandHandler: public ICommandHandler {
public:
/*------------------------------- Constructor --------------------------------|
| Constructs the object with:                                                 |
| 1) Pointers to the mle, toolbar, and edit font.                             |
-----------------------------------------------------------------------------*/
  ACommandHandler ( IFont * f,IToolBar *t, IMultiLineEdit *m, IMenuBar *menuBar )
     : editWindow(m)
     , toolBar(t)
     , menu(menuBar)
     , editFont(f)
     , under(0)
     , bold(0)
     , italic(0)
     {}
/*-----------------------------------------------------------------------------
| command - an overloaded function that processes command events              |
-----------------------------------------------------------------------------*/
  bool
    command ( ICommandEvent& event );

private:
  IToolBar
   *toolBar;
  IMultiLineEdit
   *editWindow;
  IMenuBar
   *menu;
  IFont
   *editFont;
  int
    bold,
    italic,
    under;

};

/******************************************************************************
* Class Editor - Main window                                                  *
******************************************************************************/
class Editor : public IFrameWindow
{
public:
/*------------------------------- Constructor --------------------------------|
| Constructs the object with:                                                 |
| 1) No parameters                                                            |
-----------------------------------------------------------------------------*/
    Editor();

/*-----------------------------------------------------------------------------
| editorWindow - returns a reference to the mle                               |
| editorFont   - returns the current font of the editor                       |
-----------------------------------------------------------------------------*/
  IMultiLineEdit
   &editorWindow ( ) { return editWindow; }

  IFont
   &editorFont ( ) { return editFont; }

private:
  ITitle
    title;
  IToolBar
    toolBar;
  IFlyText
    flyText;
  IStaticText
    infoText;
  IFlyOverHelpHandler
    flyHelpHandler;
  IMultiLineEdit
    editWindow;
  FontSelectHandler
    fontSelectHandler;
  IToolBarButton
    cutButton,
    copyButton,
    pasteButton,
    boldButton,
    italicButton,
    underscoreButton;
  IComboBox
    fontCombo;
  IMenuBar
    menu;
  IFont
    editFont;
  ACommandHandler
    commandhandler;
};

#endif /* _TBAR1_ */
