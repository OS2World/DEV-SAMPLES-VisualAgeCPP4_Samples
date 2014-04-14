/******************************************************************************
* .FILE:         tbar1.cpp                                                    *
*                                                                             *
* .DESCRIPTION:  Tool Bar Example 1:  Class Implementation                    *
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
#include <icoordsy.hpp>
#include <imsgbox.hpp>
#include "tbar1.hpp"
#include "tbar1.h"

/******************************************************************************
* main - Application entry point                                              *
******************************************************************************/
int main()
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::kOriginLowerLeft );
   Editor editor;
   editor.show();
   editor.setFocus();
   IApplication::current().run();
   return 0;
}

/******************************************************************************
* class Editor::Editor - Constructor for main windows                         *
*                                                                             *
* Initialize the main window.                                                 *
* Initialize the title bar                                                    *
* Initialize the fly over help and text                                       *
* Initialize the multi line editor                                            *
* Initialize the toolbar and all of the controls associated with the toolbar  *
* Initialize the menu                                                         *
* Initialize the fontSelectHandler and the command Handler                    *
******************************************************************************/

Editor::Editor ()
       :IFrameWindow(ID_MAIN_WINDOW),
        title(this),
        flyText(ID_FLYTEXT, &toolBar),
        infoText(ID_INFOTEXT, this, this),
        flyHelpHandler(&flyText, &infoText, 0, 0),
        editWindow(ID_EDITOR, this, this),
        toolBar(ID_TOOLBAR, this, IToolBar::aboveClient, false,
                IToolBar::classDefaultStyle
                | IToolBar::dragDrop),
        cutButton       (IC_ID_CUT,        &toolBar, &toolBar,
               IRectangle(), IToolBarButton::defaultStyle() |
               IToolBarButton::dragDelete ),
        copyButton      (IC_ID_COPY,       &toolBar, &toolBar,
               IRectangle(), IToolBarButton::defaultStyle() |
               IToolBarButton::dragDelete ),
        pasteButton     (IC_ID_PASTE,      &toolBar, &toolBar,
               IRectangle(), IToolBarButton::defaultStyle() |
               IToolBarButton::dragDelete ),
        boldButton      (IC_ID_BOLD,       &toolBar, &toolBar,
               IRectangle(), IToolBarButton::defaultStyle() |
               IToolBarButton::transparentBitmap ),
        italicButton    (IC_ID_ITALIC,     &toolBar, &toolBar,
               IRectangle(), IToolBarButton::defaultStyle() |
               IToolBarButton::transparentBitmap ),
        underscoreButton(IC_ID_UNDERSCORE, &toolBar, &toolBar,
               IRectangle(), IToolBarButton::defaultStyle() |
               IToolBarButton::transparentBitmap ),
        fontCombo(ID_FONTCOMBO, &toolBar, &toolBar, IRectangle(),
                  IBaseComboBox::classDefaultStyle &
                  ~IBaseComboBox::simpleType |
                  IBaseComboBox::readOnlyDropDownType),
        menu(ID_MAIN_WINDOW,this),
        fontSelectHandler(*this),
        editFont(),
        commandhandler(&editFont, &toolBar, &editWindow, &menu)
{
/*----------------------------------------------------------------------------|
| Set the icon and title text                                                 |
-----------------------------------------------------------------------------*/
   setIcon( id() );
   title.setTitleText(ID_MAIN_WINDOW);



/*----------------------------------------------------------------------------|
| Add the buttons to the toolbar                                              |
-----------------------------------------------------------------------------*/
   toolBar.addAsLast(&cutButton,true);
   toolBar.addAsLast(&copyButton);
   toolBar.addAsLast(&pasteButton);
   toolBar.addAsLast(&boldButton,true);
   toolBar.addAsLast(&italicButton);
   toolBar.addAsLast(&underscoreButton);
   toolBar.addAsLast(&fontCombo,true);

/*----------------------------------------------------------------------------|
| Set up latchable style for font property buttons                            |
| Note: When in bitmapAndTextView, latching a toolbar button will show the    |
| gray background for the bitmap.  To eliminate the gray background, set      |
| the transparent color to gray and turn on the transparent style for the     |
| button.  If you do not use the bitmapAndTextView and you have many buttons  |
| with the latchable style, consider not enabling the transparent style as    |
| transparency incurs additional overhead and increases performance time.     |
-----------------------------------------------------------------------------*/
   boldButton.enableLatching();
   italicButton.enableLatching();
   underscoreButton.enableLatching();

   boldButton.setTransparentColor(IColor::kPaleGray);
   italicButton.setTransparentColor(IColor::kPaleGray);
   underscoreButton.setTransparentColor(IColor::kPaleGray);

/*----------------------------------------------------------------------------|
| Load up font combo box with face names                                      |
-----------------------------------------------------------------------------*/
   fontCombo.setLimit(10);
#ifndef IC_MOTIF
   IFont::FaceNameCursor fontCursor;
   for ( fontCursor.setToFirst(); fontCursor.isValid(); fontCursor.setToNext())
   {
     IString faceName = IFont::faceNameAt(fontCursor);
     fontCombo.addAsLast(faceName);
     if (faceName.length() > fontCombo.limit())
       fontCombo.setLimit(faceName.length());
   }
#endif

/*----------------------------------------------------------------------------|
| Set up title for toolbar when floating                                      |
-----------------------------------------------------------------------------*/
   toolBar.setFloatingTitle(STR_TOOLBAR);

/*----------------------------------------------------------------------------|
| Setup the editor                                                            |
-----------------------------------------------------------------------------*/
   setClient(&editWindow);
   editWindow.setFont(editFont);
   try
   {
     editWindow.importFromFile("toolbar.not");
   }
   catch( ... )
   {
      IMessageBox
         msgBox( this );
      msgBox.setTitle( STR_MSGBOX_TITLE );
      msgBox.show( STR_FILE_NOT_FOUND,
                   IMessageBox::okButton |
                   IMessageBox::warningIcon);
   }
   editWindow.setTop(1);

/*----------------------------------------------------------------------------|
| Add the info frame extension                                                |
-----------------------------------------------------------------------------*/
   addExtension(&infoText, IFrameWindow::belowClient);

/*----------------------------------------------------------------------------|
| Set up and add the help handler                                             |
-----------------------------------------------------------------------------*/
   flyHelpHandler.setLongStringTableOffset(OFFSET_INFOTEXT);
   flyHelpHandler.handleEventsFor(&toolBar);

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

/*----------------------------------------------------------------------------|
| Allow the font select handler to handle events for font combo box.          |
-----------------------------------------------------------------------------*/
   fontSelectHandler.handleEventsFor(&fontCombo);

   moveSizeToClient(IRectangle(IPoint(100,100),
                               ISize(editFont.avgCharWidth()*80,
                                     editFont.maxCharHeight()*15)));
}


/******************************************************************************
* class ACommandHandler::command - Handles menu bar selections and toolbar    *
*   selections.                                                               *
******************************************************************************/
bool ACommandHandler::command(ICommandEvent &event)
{
   switch (event.commandId())
   {
     case IC_ID_CUT:
     {
         if(editWindow->hasSelectedText())
            editWindow->cut();
         break;
     }
     case IC_ID_COPY:
     {
         if(editWindow->hasSelectedText())
            editWindow->copy();
         break;
     }
     case IC_ID_PASTE:
     {
         if(editWindow->clipboardHasTextFormat())
            editWindow->paste();
         break;
     }
     case IC_ID_BOLD:
     {
         bold=!bold;
         editFont->setBold(bold/*Button.isLatched()*/);
         editWindow->setFont(*editFont);
         break;
     }
     case IC_ID_ITALIC:
     {
         italic=!italic;
         editFont->setItalic(italic/*Button.isLatched()*/);
         editWindow->setFont(*editFont);
         break;
     }
     case IC_ID_UNDERSCORE:
     {
         under=!under;
         editFont->setUnderscore(under/*scoreButton.isLatched()*/);
         editWindow->setFont(*editFont);
         break;
     }
     case ID_SHOWTEXT:
     {
         toolBar->setButtonView(IToolBarButton::textView);
         break;
     }
     case ID_SHOWBITMAPS:
     {
         toolBar->setButtonView(IToolBarButton::bitmapView);
         break;
     }

/*----------------------------------------------------------------------------|
| Note: When in bitmapAndTextView, latching a toolbar button will show the    |
| gray background for the bitmap.  To eliminate the gray background, you can  |
| set the transparent color to gray and turn on the transparent style for the |
| button.  But enabling transparency incurs additional overhead and increases |
| performance time.                                                           |
-----------------------------------------------------------------------------*/
     case ID_SHOWTEXTANDBITMAPS:
     {
         toolBar->setButtonView(IToolBarButton::bitmapAndTextView);
         break;
     }
     case ID_TOOLBAR_TOP:
     {
         if ( toolBar->isMoveValid(IToolBar::aboveClient) )
           toolBar->setLocation(IToolBar::aboveClient);
         break;
     }
     case ID_TOOLBAR_BOTTOM:
     {
         if ( toolBar->isMoveValid(IToolBar::belowClient) )
           toolBar->setLocation(IToolBar::belowClient);
         break;
     }
     case ID_TOOLBAR_LEFT:
     {
         if ( toolBar->isMoveValid(IToolBar::leftOfClient) )
           toolBar->setLocation(IToolBar::leftOfClient);
         break;
     }
     case ID_TOOLBAR_RIGHT:
     {
         if ( toolBar->isMoveValid(IToolBar::rightOfClient) )
           toolBar->setLocation(IToolBar::rightOfClient);
         break;
     }
     case ID_TOOLBAR_FLOATING:
     {
         if ( toolBar->isMoveValid(IToolBar::floating) )
           toolBar->setLocation(IToolBar::floating);
         break;
     }
     case ID_TOOLBAR_HIDE:
     {
         menu->checkItem( ID_TOOLBAR_HIDE, toolBar->isVisible() );
         toolBar->show( !toolBar->isVisible() );
         break;
     }
   }
   return false;
}

/******************************************************************************
* class FontSelectHandler::enter - Handle combo box selections
******************************************************************************/
bool FontSelectHandler::enter( IControlEvent& event)
{
  IString fontChoice =  ((IComboBox*)event.controlWindow())->text();
  if(fontChoice.length())
  {
/*----------------------------------------------------------------------------|
| Set the new font                                                            |
-----------------------------------------------------------------------------*/
     editorFrame.editorFont().setName(fontChoice);
     editorFrame.editorWindow().setFont(editorFrame.editorFont());
  }
  return true;
}

