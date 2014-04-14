/******************************************************************************
* .FILE:         tbar2.hpp                                                    *
*                                                                             *
* .DESCRIPTION:  Tool Bar Sample Program Version 2:    Class definitions      *
*                                                                             *
* .CLASSES:      Editor                                                       *
*                EditorCommandHandler                                         *
*                FontSelectHandler                                            *
*                EditorMLE                                                    *
*                ToolBarNotebook                                              *
*                ToolBarPage                                                  *
*                PageHandler                                                  *
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
#ifndef _TBAR2_
#define _TBAR2_

#include <iapp.hpp>
#include <iframe.hpp>
#include <ifont.hpp>
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
#include <idmhndlr.hpp>
#include <ifontdlg.hpp>
#include <inotebk.hpp>
#include <ititle.hpp>
#include <imcelcv.hpp>
#include <iradiobt.hpp>
#include <icheckbx.hpp>
#include <igroupbx.hpp>
#include <ifiledlg.hpp>
#include <icolor.hpp>

class Editor;

//-------------------------------------------------------------------
// EditorCommandHandler
//-------------------------------------------------------------------
class EditorCommandHandler : public ICommandHandler
{
public:
  EditorCommandHandler ( Editor& editor ) : editorFrame(editor) {}

bool
 command ( ICommandEvent& event );

private:
Editor
 &editorFrame;
};

//-------------------------------------------------------------------
// FontSelectHandler
//
// This class is used to handle selection of a new font from the font
// combo box on the tool bar.
//-------------------------------------------------------------------
class FontSelectHandler : public ISelectHandler
{
public:
  FontSelectHandler ( Editor& editor ) : editorFrame(editor) {}

protected:
virtual bool
  selected(IControlEvent& event);

private:
Editor
 &editorFrame;
};

//-------------------------------------------------------------------
// EditorMLE
//-------------------------------------------------------------------
class EditorMLE : public IMultiLineEdit
{
public:
  EditorMLE ( unsigned long id, Editor& editor )
            : IMultiLineEdit ( id, (IWindow*) &editor, (IWindow*) &editor ),
              editorFrame(editor) {}

virtual EditorMLE
  &setLayoutDistorted ( unsigned long layoutAttributesOn,
                        unsigned long layoutAttributesOff );
private:
Editor
 &editorFrame;
};

//-------------------------------------------------------------------
// Editor
//
// This class is the main window of the sample problem.  It is
// responsible for creating and managing all of the windows that
// are used.
//-------------------------------------------------------------------
class Editor : public IFrameWindow
{
public:
  Editor();

EditorMLE
 &editorWindow ( ) { return editWindow; }

IFont
 &editorFont ( ) { return editFont; }

Editor
 &updateFontToolBar ( );

IToolBar
 &toolBar ( unsigned long id );

private:
  ITitle
    title;
  IToolBar
    fileToolBar,
    editToolBar,
    fontToolBar;
IFlyText
  flyText;
IStaticText
  infoText;
IFlyOverHelpHandler
  flyHelpHandler;
EditorMLE
  editWindow;
EditorCommandHandler
  commandHandler;
FontSelectHandler
  fontSelectHandler;
IToolBarButton
  openButton,
  saveButton,
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
};

//-------------------------------------------------------------------
// ToolBarNotebook
//-------------------------------------------------------------------
class ToolBarNotebook : public IFrameWindow
{
public:
  ToolBarNotebook ( Editor&   editor );
private:
Editor
  &editorFrame;
INotebook
  notebook;
};

//-------------------------------------------------------------------
// PageHandler
//-------------------------------------------------------------------
class PageHandler : public ISelectHandler
{
public:
  PageHandler ( INotebook* notebook, Editor& editor )
              : toolbarNotebook(notebook),
                editorFrame(editor) {}

protected:
virtual bool
  selected ( IControlEvent& event );

private:
INotebook
 *toolbarNotebook;
Editor
 &editorFrame;
};

//-------------------------------------------------------------------
// ToolBarPage
//-------------------------------------------------------------------
class ToolBarPage : public IMultiCellCanvas
{
public:
  ToolBarPage ( unsigned long id, INotebook* nbk, Editor& editor );
private:
Editor
 &editorFrame;
IGroupBox
  locationBox;
IRadioButton
  topButton,
  leftButton,
  bottomButton,
  rightButton;
ICheckBox
  groupCheckBox;
IRadioButton
  floatingButton;
ICheckBox
  hiddenButton;
IGroupBox
  viewBox;
IRadioButton
  bitmapButton;
IRadioButton
  textButton;
IRadioButton
  bitmapAndTextButton;
PageHandler
  pageHandler;
};

#endif /* _TBAR2_ */
