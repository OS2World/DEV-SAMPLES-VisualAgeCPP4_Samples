/******************************************************************************
* .FILE:         tbar2.cpp                                                    *
*                                                                             *
* .DESCRIPTION:  Tool Bar Sample Program Version 2:    Class Implementation   *
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
#include <isubmenu.hpp>
#include <ifontdlg.hpp>
#include <inotebk.hpp>
#include <ititle.hpp>
#include <imcelcv.hpp>
#include <iradiobt.hpp>
#include <icheckbx.hpp>
#include <igroupbx.hpp>
#include <ifiledlg.hpp>
#include <icolor.hpp>
#include <icoordsy.hpp>
#include <imsgbox.hpp>
#include "tbar2.hpp"
#include "tbar2.h"

/******************************************************************************
* main -  creates and shows the editor window                                 *
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
* Class Editor::Editor - Constructor for the editor window                    *
******************************************************************************/
Editor::Editor ()
  : IFrameWindow(ID_MAIN_WINDOW)
  , title(this)
  , fileToolBar(ID_FILE, this, IToolBar::aboveClient, false,
                IToolBar::classDefaultStyle
                | IToolBar::dragDrop)
  , editToolBar(ID_EDIT, &fileToolBar, true,
                IToolBar::classDefaultStyle
                | IToolBar::dragDrop)
  , fontToolBar(ID_FONT, &editToolBar, true,
                IToolBar::classDefaultStyle
                | IToolBar::dragDrop)
  , flyText(ID_FLYTEXT, this)
  , infoText(ID_INFOTEXT, this, this)
  , flyHelpHandler(&flyText, &infoText, 0, 0)
  , editWindow(ID_EDITOR, *this)
  , commandHandler(*this)
  , fontSelectHandler(*this)
  , openButton(IC_ID_OPEN,&fileToolBar, &fileToolBar,
               IRectangle(), IToolBarButton::defaultStyle() |
               IToolBarButton::dragDelete )
  , saveButton(IC_ID_SAVE,&fileToolBar, &fileToolBar,
               IRectangle(), IToolBarButton::defaultStyle() |
               IToolBarButton::dragDelete )
  , cutButton(IC_ID_CUT,&editToolBar, &editToolBar,
               IRectangle(), IToolBarButton::defaultStyle() |
               IToolBarButton::dragDelete )
  , copyButton(IC_ID_COPY,&editToolBar, &editToolBar,
               IRectangle(), IToolBarButton::defaultStyle() |
               IToolBarButton::dragDelete )
  , pasteButton(IC_ID_PASTE,&editToolBar, &editToolBar,
               IRectangle(), IToolBarButton::defaultStyle() |
               IToolBarButton::dragDelete )
  , boldButton(IC_ID_BOLD,       &fontToolBar, &fontToolBar,
               IRectangle(), IToolBarButton::defaultStyle() |
               IToolBarButton::transparentBitmap )
  , italicButton(IC_ID_ITALIC,     &fontToolBar, &fontToolBar,
               IRectangle(), IToolBarButton::defaultStyle() |
               IToolBarButton::transparentBitmap )
  , underscoreButton(IC_ID_UNDERSCORE, &fontToolBar, &fontToolBar,
               IRectangle(), IToolBarButton::defaultStyle() |
               IToolBarButton::transparentBitmap )
  , fontCombo(ID_FONTCOMBO, &fontToolBar, &fontToolBar, IRectangle(),
               IComboBox::classDefaultStyle &~IComboBox::simpleType |
               IComboBox::readOnlyDropDownType)
  , menu(ID_MAIN_WINDOW,this)
  , editFont()
{
/*-----------------------------------------------------------------------------|
| Set the icon and the title                                                   |
------------------------------------------------------------------------------*/
   setIcon( id() );
   title.setTitleText(ID_MAIN_WINDOW);

/*-----------------------------------------------------------------------------|
| Add buttons to the file toolbar                                              |
------------------------------------------------------------------------------*/
   fileToolBar.addAsLast(&openButton,true)
              .addAsLast(&saveButton);

/*-----------------------------------------------------------------------------|
| Add buttons to the edit toolbar                                              |
------------------------------------------------------------------------------*/
   editToolBar.addAsLast(&cutButton,true)
              .addAsLast(&copyButton)
              .addAsLast(&pasteButton);

/*-----------------------------------------------------------------------------|
| Add buttons to the font toolbar                                              |
------------------------------------------------------------------------------*/
   fontToolBar.addAsLast(&boldButton,true)
              .addAsLast(&italicButton)
              .addAsLast(&underscoreButton)
              .addAsLast(&fontCombo,true);

/*-----------------------------------------------------------------------------|
| Set up the latchabable style for font property buttons                       |
| Note: When in bitmapAndTextView, latching a toolbar button will show the     |
| gray background for the bitmap.  To eliminate the gray background, set       |
| the transparent color to gray and turn on the transparent style for the      |
| button.  If you do not use the bitmapAndTextView and you have many buttons   |
| with the latchable style, consider not enabling the transparent style as     |
| transparency incurs additional overhead and increases performance time.      |
------------------------------------------------------------------------------*/
   boldButton.enableLatching();
   italicButton.enableLatching();
   underscoreButton.enableLatching();

   boldButton.setTransparentColor(IColor::kPaleGray);
   italicButton.setTransparentColor(IColor::kPaleGray);
   underscoreButton.setTransparentColor(IColor::kPaleGray);

/*-----------------------------------------------------------------------------|
| Load up front combo box with face names                                      |
------------------------------------------------------------------------------*/
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
   updateFontToolBar();

/*-----------------------------------------------------------------------------|
| Set up titles for toolbars when floating                                     |
------------------------------------------------------------------------------*/
   fileToolBar.setFloatingTitle(ID_FILE);
   editToolBar.setFloatingTitle(ID_EDIT);
   fontToolBar.setFloatingTitle(ID_FONT);

/*-----------------------------------------------------------------------------|
| Setup the editor                                                             |
------------------------------------------------------------------------------*/
   setClient(&editWindow);
   editWindow.setFont(editFont);
   try
   {
     editWindow.importFromFile("toolbar2.not");
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

/*-----------------------------------------------------------------------------|
| Add the info frame extension                                                 |
------------------------------------------------------------------------------*/
   addExtension(&infoText, IFrameWindow::belowClient);

/*-----------------------------------------------------------------------------|
| Set up and add the help handler                                              |
------------------------------------------------------------------------------*/
   flyHelpHandler.setLongStringTableOffset(OFFSET_INFOTEXT);
   flyHelpHandler.setDefaultText("\0");
   flyHelpHandler.handleEventsFor(&fileToolBar);
   flyHelpHandler.handleEventsFor(&editToolBar);
   flyHelpHandler.handleEventsFor(&fontToolBar);

/*-----------------------------------------------------------------------------|
| Attach the Command Handler to frame and toolbar                              |
------------------------------------------------------------------------------*/
   commandHandler.handleEventsFor(this);
   commandHandler.handleEventsFor(&fileToolBar);
   commandHandler.handleEventsFor(&editToolBar);
   commandHandler.handleEventsFor(&fontToolBar);

/*-----------------------------------------------------------------------------|
| Add the handler to change the font                                           |
------------------------------------------------------------------------------*/
   fontSelectHandler.handleEventsFor(&fontCombo);

   moveSizeToClient(IRectangle(IPoint(100,100),
                               ISize(editFont.avgCharWidth()*80,
                                     editFont.maxCharHeight()*15)));
}

/******************************************************************************
* EditorCommandHandler::command - Handle user menu bar selections             *
******************************************************************************/
bool EditorCommandHandler::command(ICommandEvent &event)
{
   switch (event.commandId())
   {
     case IC_ID_OPEN:
     {
        IFileDialog::Settings settings;
        settings.setOpenDialog();
        IFileDialog openDlg(IWindow::desktopWindow(),&editorFrame,settings);
        if ( openDlg.pressedOK() )
        {
           editorFrame.disableUpdate();
           editorFrame.editorWindow().removeAll();
           editorFrame.editorWindow().importFromFile(openDlg.fileName());
           editorFrame.enableUpdate();
           editorFrame.editorWindow().setTop(1);
           editorFrame.setTitleText(openDlg.fileName());
        }
        break;
     }
     case IC_ID_SAVE:
     {
        IFileDialog::Settings settings;
        settings.setSaveAsDialog();
        IFileDialog saveDlg(IWindow::desktopWindow(),&editorFrame,settings);
        if ( saveDlg.pressedOK() )
        {
           editorFrame.editorWindow().exportToFile(saveDlg.fileName());
           editorFrame.setTitleText(saveDlg.fileName());
        }
        break;
     }
     case IC_ID_CUT:
     {
         if(editorFrame.editorWindow().hasSelectedText())
            editorFrame.editorWindow().cut();
         break;
     }
     case IC_ID_COPY:
     {
         if(editorFrame.editorWindow().hasSelectedText())
            editorFrame.editorWindow().copy();
         break;
     }
     case IC_ID_PASTE:
     {
         if(editorFrame.editorWindow().clipboardHasTextFormat())
            editorFrame.editorWindow().paste();
         break;
     }
     case IC_ID_BOLD:
     {
         editorFrame.editorFont().setBold(!editorFrame.editorFont().isBold());
         editorFrame.editorWindow().setFont(editorFrame.editorFont());
         break;
     }
     case IC_ID_ITALIC:
     {
         editorFrame.editorFont().setItalic(!editorFrame.editorFont().isItalic());
         editorFrame.editorWindow().setFont(editorFrame.editorFont());
         break;
     }
     case IC_ID_UNDERSCORE:
     {
         editorFrame.editorFont().setUnderscore(!editorFrame.editorFont().isUnderscore());
         editorFrame.editorWindow().setFont(editorFrame.editorFont());
         break;
     }
     case ID_FONT:
     {
         IFontDialog::Settings settings(&editorFrame.editorFont());

         IFontDialog dlg(IWindow::desktopWindow(),&editorFrame,settings);
         if ( dlg.pressedOK() )
         {
           editorFrame.updateFontToolBar();
           editorFrame.editorWindow().setFont(editorFrame.editorFont());
         }
         break;
     }
     case ID_TOOLBARS:
     {
         ToolBarNotebook nbk(editorFrame);
         break;
     }
   }
   return true;
}

//-------------------------------------------------------------------
// Update font toolbar to reflect the current font
//-------------------------------------------------------------------
Editor& Editor::updateFontToolBar()
{
/*-----------------------------------------------------------------------------|
|                                                                              |
------------------------------------------------------------------------------*/
   // Update toolbar buttons (if they have not been dragged to the shredder)
   if (boldButton.isValid())
     boldButton.latch(editFont.isBold());
   if (italicButton.isValid())
     italicButton.latch(editFont.isItalic());
   if (underscoreButton.isValid())
     underscoreButton.latch(editFont.isUnderscore());

/*-----------------------------------------------------------------------------|
|                                                                              |
------------------------------------------------------------------------------*/
   // Update the combo box with the correct face name
   unsigned long cbLocation = fontCombo.locateText(editFont.name());
   if ( cbLocation != IBaseComboBox::notFound )
     fontCombo.select(fontCombo.locateText(editFont.name()));

   return *this;
}

//-------------------------------------------------------------------
// Get the toolbar
//-------------------------------------------------------------------
IToolBar& Editor::toolBar ( unsigned long id )
{
   if ( id == ID_FILE )
      return fileToolBar;
   if ( id == ID_EDIT )
      return editToolBar;
   return fontToolBar;
}

//-------------------------------------------------------------------
// Handle combo box selections
//-------------------------------------------------------------------
bool FontSelectHandler::selected( IControlEvent& event)
{
  IString fontChoice =  ((IComboBox*)event.controlWindow())->text();
  if(fontChoice.length())
  {
     // Set the new font
     editorFrame.editorFont().setName(fontChoice);
     editorFrame.editorWindow().setFont(editorFrame.editorFont());
  }
  return true;
}

//-------------------------------------------------------------------
// If the user drops a font onto the MLE from the system's font palette,
// update the MLE.  This is only necessary for OS/2 PM MLEs since they
// have their own presentation space.
//-------------------------------------------------------------------
EditorMLE& EditorMLE::setLayoutDistorted ( unsigned long layoutAttributesOn,
                                           unsigned long layoutAttributesOff )
{
#ifdef IC_PM
   IMultiLineEdit::setLayoutDistorted(layoutAttributesOn,layoutAttributesOff);
   if ( layoutAttributesOn & IWindow::fontChanged )
   {
     IFont newFont(editorFrame.editorWindow().presSpace());
     editorFrame.editorFont() = newFont;
     editorFrame.updateFontToolBar();
     editorFrame.editorWindow().setFont(editorFrame.editorFont());
   }
#endif
   return *this;
}

//-------------------------------------------------------------------
// ToolBarNotebook::ToolBarNotebook
//-------------------------------------------------------------------
ToolBarNotebook::ToolBarNotebook ( Editor&   editor )
                :IFrameWindow ( ID_TOOLBAR_WINDOW, IWindow::desktopWindow(),
                                (IWindow*) &editor, IRectangle(),
                                IFrameWindow::titleBar |
                                IFrameWindow::systemMenu |
                                IFrameWindow::dialogBorder |
                                IFrameWindow::dialogBackground |
                                IFrameWindow::appDBCSStatus ),
                 editorFrame(editor),
                 notebook(ID_NOTEBOOK,this,this)
{
  setClient(&notebook);

  ITitle title(this);
  title.setText(ID_TOOLBARS);

  notebook.setBinding(INotebook::spiral);
  notebook.setMinorTabSize(ISize(0,0));

/*-----------------------------------------------------------------------------|
|                                                                              |
------------------------------------------------------------------------------*/
  // Add notebook pages
  ToolBarPage filePage(ID_FILE,&notebook,editor);
  ToolBarPage editPage(ID_EDIT,&notebook,editor);
  ToolBarPage fontPage(ID_FONT,&notebook,editor);

/*-----------------------------------------------------------------------------|
|                                                                              |
------------------------------------------------------------------------------*/
  // Center the notebook on the screen
  IRectangle  clientRect;
  clientRect.sizeTo(notebook.minimumSize());
  clientRect.moveTo(IPoint((IWindow::desktopWindow()->size().width() -
                            clientRect.width())/2,
                           (IWindow::desktopWindow()->size().height() -
                            clientRect.height())/2));

  moveSizeToClient(clientRect);
  setFocus();
  showModally();

}

//-------------------------------------------------------------------
// ToolBarPage::ToolBarPage
//-------------------------------------------------------------------
ToolBarPage::ToolBarPage ( unsigned long id, INotebook* nbk, Editor& editor )
            :IMultiCellCanvas(id,nbk,nbk),
             editorFrame(editor),
             locationBox(ID_LOCATION,this,this),
             topButton(ID_TOP,this,this,IRectangle(),
                       IRadioButton::defaultStyle()|IControl::group),
             leftButton(ID_LEFT,this,this),
             bottomButton(ID_BOTTOM,this,this),
             rightButton(ID_RIGHT,this,this),
             groupCheckBox(ID_GROUP,this,this),
             floatingButton(ID_FLOATING,this,this),
             hiddenButton(ID_HIDDEN,this,this),
             viewBox(ID_VIEW,this,this),
             bitmapButton(ID_BITMAP,this,this,IRectangle(),
                          IRadioButton::defaultStyle()|IControl::group),
             textButton(ID_TEXT,this,this),
             bitmapAndTextButton(ID_BITMAP_AND_TEXT,this,this),
             pageHandler(nbk,editor)
{
/*-----------------------------------------------------------------------------|
|                                                                              |
------------------------------------------------------------------------------*/
   INotebook::PageSettings settings(INotebook::PageSettings::autoPageSize |
                                    INotebook::PageSettings::majorTab);

   settings.setTabText(id);

/*-----------------------------------------------------------------------------|
|                                                                              |
------------------------------------------------------------------------------*/
   locationBox.setText(ID_LOCATION);
   topButton.setText(ID_TOP);
   leftButton.setText(ID_LEFT);
   bottomButton.setText(ID_BOTTOM);
   rightButton.setText(ID_RIGHT);
   groupCheckBox.setText(ID_GROUP);
   floatingButton.setText(ID_FLOATING);
   hiddenButton.setText(ID_HIDDEN);
   viewBox.setText(ID_VIEW);
   bitmapButton.setText(ID_BITMAP);
   textButton.setText(ID_TEXT);
   bitmapAndTextButton.setText(ID_BITMAP_AND_TEXT);

/*----------------------------------------------------------------------------|
| For Motif, disable the Floating radio button.                               |
-----------------------------------------------------------------------------*/
#ifdef IC_MOTIF
                                            // On Motif, changing a toolbar location
                                            // to floating is not allowed.  Only
                                            // the initial location can be set
                                            // to floating.  Therefore, disable
                                            // the option on Motif since it
                                            // would have no effect.
  floatingButton.enable( false );
#endif

/*-----------------------------------------------------------------------------|
|                                                                              |
------------------------------------------------------------------------------*/
   addToCell(&locationBox,2,2,6,13);
   addToCell(&topButton,4,4,2);
   addToCell(&leftButton,4,5,2);
   addToCell(&bottomButton,4,6,2);
   addToCell(&rightButton,4,7,2);
   addToCell(&groupCheckBox,5,8);
   addToCell(&floatingButton,4,10,2);
   addToCell(&hiddenButton,4,12,2);

   addToCell(&viewBox,9,2,5,7);
   addToCell(&bitmapButton,11,4);
   addToCell(&textButton,11,5);
   addToCell(&bitmapAndTextButton,11,6);

/*-----------------------------------------------------------------------------|
|                                                                              |
------------------------------------------------------------------------------*/
   switch ( editorFrame.toolBar(this->id()).location() )
   {
      case IToolBar::aboveClient:
         topButton.select();
         break;
      case IToolBar::belowClient:
         bottomButton.select();
         break;
      case IToolBar::leftOfClient:
         leftButton.select();
         break;
      case IToolBar::rightOfClient:
         rightButton.select();
         break;
      case IToolBar::floating:
         floatingButton.select();
         break;
   }

/*-----------------------------------------------------------------------------|
|                                                                              |
------------------------------------------------------------------------------*/
   switch ( editorFrame.toolBar(this->id()).buttonView() )
   {
      case IToolBarButton::bitmapView:
         bitmapButton.select();
         break;
      case IToolBarButton::textView:
         textButton.select();
         break;
      case IToolBarButton::bitmapAndTextView:
         bitmapAndTextButton.select();
         break;
   }

   if ( !editorFrame.toolBar(this->id()).isGroup() )
      groupCheckBox.select();

   if ( !editorFrame.toolBar(this->id()).isVisible() )
      hiddenButton.select();

   pageHandler.handleEventsFor(this);
   nbk->addLastPage(settings,this);
   sizeTo(minimumSize());
}

//-------------------------------------------------------------------
// Handle selection events for controls on the page
//-------------------------------------------------------------------
bool PageHandler::selected ( IControlEvent& event )
{
   switch ( event.controlWindow()->id() )
   {
      case ID_TOP:
         {
           if ( editorFrame.toolBar(event.window()->id()).isMoveValid(IToolBar::aboveClient) )
             editorFrame.toolBar(event.window()->id()).setLocation
                            (IToolBar::aboveClient);
           break;
         }
      case ID_BOTTOM:
         {
           if ( editorFrame.toolBar(event.window()->id()).isMoveValid(IToolBar::belowClient) )
             editorFrame.toolBar(event.window()->id()).setLocation
                            (IToolBar::belowClient);
           break;
         }
      case ID_LEFT:
         {
           if ( editorFrame.toolBar(event.window()->id()).isMoveValid(IToolBar::leftOfClient) )
             editorFrame.toolBar(event.window()->id()).setLocation
                            (IToolBar::leftOfClient);
           break;
         }
      case ID_RIGHT:
         {
           if ( editorFrame.toolBar(event.window()->id()).isMoveValid(IToolBar::rightOfClient) )
             editorFrame.toolBar(event.window()->id()).setLocation
                            (IToolBar::rightOfClient);
           break;
         }
      case ID_FLOATING:
         {
           if ( editorFrame.toolBar(event.window()->id()).isMoveValid(IToolBar::floating) )
             editorFrame.toolBar(event.window()->id()).setLocation
                            (IToolBar::floating);
           break;
         }
      case ID_HIDDEN:
         editorFrame.toolBar(event.window()->id()).show
                            (! editorFrame.toolBar(event.window()->id()).
                             isVisible());
         break;
      case ID_GROUP:
         {
           ICheckBox* checkBox = (ICheckBox*) event.controlWindow();
           editorFrame.toolBar(event.window()->id()).enableGroup
                              (!checkBox->isSelected());

           switch (editorFrame.toolBar(event.window()->id()).location())
           {
             case IToolBar::aboveClient:
             case IToolBar::belowClient:
             case IToolBar::leftOfClient:
             case IToolBar::rightOfClient:
                editorFrame.toolBar(event.window()->id()).parent()->
                            setLayoutDistorted(IWindow::layoutChanged |
                                               IWindow::immediateUpdate,0);
                break;
           }
         }
         break;
      case ID_BITMAP:
         editorFrame.toolBar(event.window()->id()).setButtonView
                            (IToolBarButton::bitmapView);
         break;
      case ID_TEXT:
         editorFrame.toolBar(event.window()->id()).setButtonView
                            (IToolBarButton::textView);
         break;

/*----------------------------------------------------------------------------|
| Note: When in bitmapAndTextView, latching a toolbar button will show the    |
| gray background for the bitmap.  To eliminate the gray background, you can  |
| set the transparent color to gray and turn on the transparent style for the |
| button.  But enabling transparency incurs additional overhead and increases |
| performance time.                                                           |
-----------------------------------------------------------------------------*/
      case ID_BITMAP_AND_TEXT:
         editorFrame.toolBar(event.window()->id()).setButtonView
                            (IToolBarButton::bitmapAndTextView);
         break;
   }
   return false;
}

