/******************************************************************************
* .FILE:         amle.cpp                                                     *
*                                                                             *
* .DESCRIPTION:  Multiline Edit Sample Program:        Class Implementation   *
*                                                                             *
* .CLASSES:      AEditorWindow                                                *
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
#include <imsgbox.hpp>
#include <ireslib.hpp>
#include <ifiledlg.hpp>
#include <isubmenu.hpp>
#include <ifont.hpp>
#include <ifontdlg.hpp>
#include <itrace.hpp>
#include <icoordsy.hpp>
#include <ithread.hpp>
#include <imnitem.hpp>
#include <iexcbase.hpp>
#include "amle.h"
#include "amle.hpp"

/******************************************************************************/
/* main  - Application entry point                                            */
/******************************************************************************/
int main()
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::kOriginLowerLeft );
  AEditorWindow mainWindow(WND_MAIN);
  IApplication::current().run();

  return 0;
} /* end main */

/******************************************************************************/
/* AMultiCellCanvas :: AMultiCellCanvas - Constructor for our main window     */
/******************************************************************************/
AEditorWindow::AEditorWindow(unsigned long windowId)
  : IFrameWindow( windowId )
  , AUserMessageHandler( UWM_THREADEND )
  , mle( WND_MLE, this, this )
  , titleBar( this, IResourceId(WND_MAIN) )
  , menuBar( WND_MAIN, this )
  , infoArea( this )
  , primaryThreadId( IThread::current().id() )
{
  setIcon( id() );                           // Set icon
  setClient( &mle );                         // make mle the client
  ((ICommandHandler *)this)->handleEventsFor( this );
  ((AUserMessageHandler *)this)->handleEventsFor( this );
  ((IMenuHandler *)this)->handleEventsFor( this );

  menuBar.checkItem(MI_WORDWRAP);
  mle.enableWordWrap();

#ifdef IC_WIN                                // Wordwrap is ignored on Windows
  menuBar.enableItem( MI_WORDWRAP, false );
#endif
#ifdef IC_MOTIF
                                            // Since GUI operations are not thread
                                            // safe on Motif, do not use threads for
                                            // loading files into the MLE.
  menuBar.enableItem( MI_OPEN_THREAD2, false );
#endif

  mle.setFocus();                            // set focus to mle
  show();                                    // show main window

} /* end AEditorWindow :: AEditorWindow(...) */

/******************************************************************************/
/* AEditorWindow::command - command handler (menus and accelerators)          */
/******************************************************************************/
bool AEditorWindow::command(ICommandEvent& cmdEvent)
{
  bool fProcessed = true;

   switch( cmdEvent.commandId() )
     {
                // two open choices are provided to illustrate the difference
                // between using a thread for a long operation & not using one
     case MI_OPEN:
        openFile(false);
        break;
     case MI_OPEN_THREAD2:
        openFile(true);
        break;
     case MI_SAVE:
        saveFile();
        break;
     case MI_SAVEAS:
        saveAsFile();
        break;
     case MI_FONT:
        openFont();
        break;
     case MI_CUT:
        mle.cut();
        break;
     case MI_COPY:
        mle.copy();
        break;
     case MI_PASTE:
        try
        {
	        mle.paste();
        }
        catch( IException& exception )
        {
        }
        break;
     case MI_WORDWRAP:
        {
        bool f = menuBar.isItemChecked(MI_WORDWRAP);
        if (f)
           {
           menuBar.uncheckItem(MI_WORDWRAP);
           mle.disableWordWrap();
           }
        else
           {
           menuBar.checkItem(MI_WORDWRAP);
           mle.enableWordWrap();
           }
        }
        break;
     default:
        fProcessed = false;
        break;
     }
  return fProcessed;
}  /*  end AEditorWindow::command(...)  */

/******************************************************************************/
/* AEditorWindow::menuShowing - enable/disable edit menu choices              */
/******************************************************************************/
bool AEditorWindow::menuShowing( IMenuEvent& mnEvt
                                  , ISubmenu&   smnAboutToShow)
{
  switch ( smnAboutToShow.id() )
     {
     case MI_EDIT:
       if ( mle.hasSelectedText() )
          {
          menuBar.enableItem(MI_COPY);
          menuBar.enableItem(MI_CUT);
          }
       else
          {
          menuBar.disableItem(MI_COPY);
          menuBar.disableItem(MI_CUT);
          }
       try
       {
       		if ( mle.clipboardHasTextFormat() )
          		menuBar.enableItem(MI_PASTE);
         	else
          		menuBar.disableItem(MI_PASTE);
       }
       catch( IAccessError& exception )
       {
       		menuBar.disableItem(MI_PASTE);
       }
     break;
     default:
     break;
     }
  return false;
}  /* end  AEditorWindow::menuShowing(...)  */

/******************************************************************************/
/* AEditorWindow::openFile - display open file dialog and load file into mle  */
/******************************************************************************/
AEditorWindow& AEditorWindow::openFile(bool fUseThread)
{
  IFileDialog::Settings fdSettings;
  fdSettings.setOpenDialog();
  if ( filename.size() )
     fdSettings.setFileName(filename);
  else
     fdSettings.setFileName(DEFAULT_FILE_SPEC);

  IFileDialog fileDlg( desktopWindow(), this, fdSettings );
  if ( fileDlg.pressedOK() )
     {
       filename=fileDlg.fileName();
       titleBar.setObjectText( IResourceId( WND_MAIN ) );
       titleBar.setViewText( filename );
       if ( filename.size() )
          {
                                        // determine whether to use thread
                                        // Since GUI operations are not thread
                                        // safe on Motif, do not use threads for
                                        // loading files into the MLE.
          if (fUseThread)
             {
                                        // disable file menu items to avoid them
                                        // being reselected while thead running
             setFileMenuitemsState( false );
                                        // create our thread function and
                                        // specify the message id we want
                                        // posted back
             AThreadFn *atmFn = new AThreadFn( *this, UWM_THREADEND );
                                        // dispatch thread to run function
                                        // thread will have a PM environment
             IThread thread( atmFn, IThread::defaultAutoInitGUI() );
             }
          else
             {
             load();
             }
          }
     }
  return *this;
}  /* end  AEditorWindow::openFile(...)  */

/******************************************************************************/
/* AEditorWindow::saveFile - save file                                        */
/******************************************************************************/
AEditorWindow& AEditorWindow::saveFile()
{
  if ( filename.size() )                // if there is a filename then
     {                                  // save else call saveAs code
     mle.exportToFile(filename);
     }
  else
     {
     saveAsFile();
     }
  return *this;
}  /* end  AEditorWindow::saveFile()  */

/******************************************************************************/
/* AEditorWindow::saveAsFile - display 'Save As' file dialog and save mle     */
/******************************************************************************/
AEditorWindow& AEditorWindow::saveAsFile()
{
  IFileDialog::Settings fdSettings;
  fdSettings.setSaveAsDialog();
  fdSettings.setFileName(filename);

  IFileDialog fileDlg( desktopWindow(), this, fdSettings );
  if ( fileDlg.pressedOK() )
     {
       filename=fileDlg.fileName();
       if ( filename.size() )
          {
          mle.exportToFile(filename);
          titleBar.setObjectText( IResourceId( WND_MAIN ) );
          titleBar.setViewText( filename );
          }
     }
  return *this;
}  /* end  AEditorWindow::saveAsFile()  */

/******************************************************************************/
/* AEditorWindow::openFont - display font dialog and set font of mle          */
/******************************************************************************/
AEditorWindow& AEditorWindow::openFont()
{
  IFont curFont( &mle );
  IFontDialog::Settings fontSettings(&curFont);
  fontSettings.setTitle(STR_FONTDLGT);

  IFontDialog fontDlg( desktopWindow(), this,
                       IFontDialog::defaultStyle() | IFontDialog::bitmapOnly,
                       fontSettings );

  if ( fontDlg.pressedOK() )
     {
     mle.setFont(curFont);
     }
  return *this;
} /* end  AEditorWindow::openFont()  */

/******************************************************************************/
/* AEditorWindow::displayLoadFailedMsg - display an 'unable to load file' msg */
/*   A message box is only displayed if called from thread 1. This is because */
/*   owner / child windows must be created on the same thread                 */
/*   see the loadOnThread() comment for possible improvements                 */
/******************************************************************************/
AEditorWindow& AEditorWindow::displayLoadFailedMsg()
{
  if ( IThread::current().id() == primaryThreadId )
     {
     IMessageBox msgbox( this );
     IResourceLibrary  reslib =
                            IApplication::current().userResourceLibrary();
     IString  str( reslib.loadString(STR_OPENFAILEDTEXT) );
     str += reslib.loadString(STR_QUOTE);
     str += filename;
     str += reslib.loadString(STR_QUOTE);
     msgbox.setTitle( IResourceId(STR_OPENFAILED) );
     msgbox.show( str, IMessageBox::okButton         |
                       IMessageBox::informationIcon  |
                       IMessageBox::applicationModal |
                       IMessageBox::moveable         );
     }
  return *this;
}  /* end  AEditorWindow::displayLoadFailedMsg()  */

/******************************************************************************/
/* AEditorWindow::loadMLE - load mle and catch exception                      */
/*   If the import fails due to an invalid file name, an IAccessError is      */
/*   thrown. This is caught and an error message is displayed                 */
/******************************************************************************/
bool AEditorWindow::loadMLE()
{
  bool loaded = true;

  try
     {
     mle.importFromFile( filename );
     }
  catch ( IAccessError &exc )
     {
     displayLoadFailedMsg();
     loaded = false;
     }

  return loaded;
}  /* end  AEditorWindow::loadMLE()  */

/******************************************************************************/
/* AEditorWindow::load - load file into mle                                   */
/******************************************************************************/
AEditorWindow& AEditorWindow::load()
{
  mle.removeAll();
  loadMLE();
  mle.setCursorLinePosition( 0 );
  return *this;
}  /* end  AEditorWindow::load()  */

/******************************************************************************/
/* AEditorWindow::loadOnThread                                                */
/*   This function is designed to be called from a separate thread.           */
/*   The function posts an event back to thread one to signal completion      */
/*   If an error occurs no message box is displayed. One possible improvement */
/*   is to return a bool value back with the postEvent. The user message   */
/*   handler should then be altered to interrogate this value and call        */
/*   the message box code                                                     */
/******************************************************************************/
AEditorWindow& AEditorWindow::loadOnThread(unsigned long eventId)
{
  mle.removeAll();
  loadMLE();
  mle.setCursorLinePosition( 0 );
  postEvent( eventId );                   // post message back to frame window
  return *this;
} /* end  AEditorWindow::loadOnThread(...)  */

/******************************************************************************/
/* AEditorWindow::setFileMenuitemsState - enable/disable file menu items      */
/******************************************************************************/
bool AEditorWindow::setFileMenuitemsState(bool f)
{
  if (f)                                     // if true enable items
     {
     menuBar.enableItem( MI_OPEN );
     menuBar.enableItem( MI_OPEN_THREAD2 );
     menuBar.enableItem( MI_SAVE );
     menuBar.enableItem( MI_SAVEAS );
     }
  else
     {
     menuBar.disableItem( MI_OPEN );
     menuBar.disableItem( MI_OPEN_THREAD2 );
     menuBar.disableItem( MI_SAVE );
     menuBar.disableItem( MI_SAVEAS );
     }

  return f;
}  /* end  AEditorWindow::setFileMenuitemsState(...)  */

/******************************************************************************/
/* AEditorWindow::userMessage - handle user message events                    */
/******************************************************************************/
bool AEditorWindow::userMessage( IEvent& evt )
{
  setFileMenuitemsState(true);               // enable file menu items
  return true;
}  /* end  AEditorWindow::userMessage(...)  */
