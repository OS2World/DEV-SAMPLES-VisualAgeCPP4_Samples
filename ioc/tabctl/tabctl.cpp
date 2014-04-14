/******************************************************************************
* .FILE:         tabctl.cpp                                                   *
*                                                                             *
* .DESCRIPTION:  Tab Control Sample Program:  Class Implementation            *
*                                                                             *
* .CLASSES:      TabTest                                                      *
*                EnrollPage                                                   *
*                DataPage                                                     *
*                PhotoPage                                                    *
*                TabCommandHandler                                            *
*                                                                             *
* .COPYRIGHT:                                                                 *
*    Licensed Material - Program-Property of IBM                              *
*    (C) Copyright IBM Corp. 1998 - All Rights Reserved                       *
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
#include <ibase.hpp>
#include <iapp.hpp>
#include <ireslib.hpp>
#include <imsgbox.hpp>
#include <ipushbut.hpp>
#include <istring.hpp>
#include <itext.hpp>
#include "tabctl.hpp"
#include "tabctl.h"

/**************************************************************************
* main() - Application Entry Point                                        *
**************************************************************************/
int main()
{
/*------------------------------------------------------------------------|
|  If USE_IPF is defined, use IPF Help.                                   |
|  Otherwise, use the default help for this platform.                     |
|------------------------------------------------------------------------*/
  #ifdef USE_IPF
  IHelpWindow::setDefaultStyle( IHelpWindow::defaultStyle()
                                | IHelpWindow::ipfCompatible );
  #endif

/*------------------------------------------------------------------------|
|  Create a TabTest object with window ID WND_MAIN                        |
|------------------------------------------------------------------------*/
  TabTest
    mainWindow( WND_MAIN );

/*------------------------------------------------------------------------|
|  Show the frame window                                                  |
|  Start the message loop                                                 |
|------------------------------------------------------------------------*/
  mainWindow.setFocus().show();
  IApplication::current().run();
  return 0;
}

/**************************************************************************
* TabTest :: TabTest                                                      *
*                                                                         *
* TabTest is our main window class.  An ITabControl object is constructed *
* and set as the frame window's client.  Three different ITabPage derived *
* objects are constructed.  These three tab pages are then added to the   *
* tab control.  Help is initialized for the application and a command     *
* handler is constructed and attached to the tab control to handle        *
* command events from the tab control push buttons.                       *
**************************************************************************/
TabTest :: TabTest( unsigned long windowId )
 : IFrameWindow( windowId
                 ,classDefaultStyle
                  |shellPosition
                  |dialogBackground
                  |dialogBorder)
 , tabControl( WND_TABCONTROL,
               this,
               this,
               IRectangle(),
               ITabControl::defaultStyle()
                | ITabControl::buttons )
 , enrollPage( this )
 , dataPage( this )
 , helpWindow( HELP_TABLE,
               this )
 , tabCommandHandler( this )
{
/*------------------------------------------------------------------------|
| Add the three tab pages to the tab control.                             |
|------------------------------------------------------------------------*/
  tabControl.addLastPage( &enrollPage );
  tabControl.addLastPage( &dataPage );
  tabControl.addLastPage( &photoPage );

/*------------------------------------------------------------------------|
| Add three common buttons to the tab control.  These push buttons        |
|   are displayed for pages which don't have any page buttons set.        |
|------------------------------------------------------------------------*/
  tabControl.addCommonButton( ITabControl::kOk, true );
  tabControl.addCommonButton( ITabControl::kCancel );
  tabControl.addCommonButton( ITabControl::kHelp );

/*------------------------------------------------------------------------|
| Set the application icon.                                               |
| Set the tab control as the frame's client window.                       |
| Size the client area to the tab control's minimum size.                 |
| Size the frame window to the client size.                               |
|------------------------------------------------------------------------*/
  setIcon( WND_MAIN );
  setClient( &tabControl );
  IRectangle clientRect = clientRectFor( rect() );
  clientRect.sizeTo( tabControl.minimumSize() );
  moveSizeToClient( clientRect );

/*------------------------------------------------------------------------|
| Start handling command events from the tab control buttons.  You can    |
|   attach the command handler to either the tab control or the frame.    |
|   It is attached to the tab control here.                               |
|------------------------------------------------------------------------*/
  tabCommandHandler.handleEventsFor( &tabControl );

/*------------------------------------------------------------------------|
| Add the help library to the help window using addLibraries().           |
| Set the help window title from a string in the resource file.           |
|------------------------------------------------------------------------*/
   try
   {
     helpWindow.addLibraries( "tabctl.hlp" );
     helpWindow.setTitle( STR_HTITLE );
   }
   catch( ... )
   {
     IMessageBox
       msgBox( this );
     msgBox.setTitle( STR_HELP_NOT_FOUND_TITLE );
     msgBox.show( STR_HELP_NOT_FOUND, IMessageBox::information );
   }

}

/*******************************************************************************
* TabTest :: sponsor                                                           *
*                                                                              *
* Returns the sponsor data stored in our test window class.                    *
*******************************************************************************/
IString TabTest :: sponsor( ) const
{
  return sponsorName;
}

/*******************************************************************************
* TabTest :: setSponsor                                                        *
*                                                                              *
* Stores the sponsor data in our test window class.                            *
*******************************************************************************/
TabTest& TabTest :: setSponsor( const IString& currentSponsor )
{
  sponsorName = currentSponsor;
  return *this;
}

/**************************************************************************
* EnrollPage :: EnrollPage                                                *
*                                                                         *
* An ITabPage derived class used to encapsulate the data and windows      *
* used for the first page of our application's tab control.               *
**************************************************************************/
EnrollPage :: EnrollPage( TabTest *tabTest )
  : ITabPage( IText( IApplication::current().userResourceLibrary().loadString(STR_ENROLL) ))
  , tabTest( tabTest )
{
/*------------------------------------------------------------------------|
|  Set the help id for this page.  The help panel with this id is         |
|    displayed when the user requests help while focus is on the tab for  |
|    this page.                                                           |
|------------------------------------------------------------------------*/
  setHelpId( 200 );
}

/**************************************************************************
* EnrollPage :: createPageWindow                                          *
*                                                                         *
* createPageWindow is called by the ITabControl class when this page in   *
* the tab control is first displayed.  This delayed page window           *
* construction enables you to create windows only when and if they are    *
* to be displayed in your application.                                    *
**************************************************************************/
IWindow* EnrollPage :: createPageWindow( )
{
/*------------------------------------------------------------------------|
|  Create the controls for this notebook page using the new operator.     |
|    setAutoDeleteObject is called on each of these controls to ensure    |
|    that object destruction occurs when the corresponding window is      |
|    destroyed.  Since object destruction will occur automatically, we    |
|    will not store pointers to all of our controls.  We only store       |
|    pointers to the IWindow objects we need to access for data.          |
|------------------------------------------------------------------------*/
  IMultiCellCanvas
    *enrollCanvas =    new IMultiCellCanvas( WND_ENROLLPAGE,
                                             tabControl(),
                                             tabControl() );

  IStaticText
    *nameStatic =      new IStaticText( WND_NAMESTATIC,
                                        enrollCanvas,
                                        enrollCanvas ),
    *firstNameStatic = new IStaticText( WND_FIRSTNAMESTATIC,
                                        enrollCanvas,
                                        enrollCanvas ),
    *lastNameStatic =  new IStaticText( WND_LASTNAMESTATIC,
                                        enrollCanvas,
                                        enrollCanvas ),
    *cheetahStatic =   new IStaticText( WND_CHEETAHSTATIC,
                                        enrollCanvas,
                                        enrollCanvas );

  firstName = new IEntryField( WND_FIRSTNAME,
                               enrollCanvas,
                               enrollCanvas,
                               IRectangle(),
                               IEntryField::defaultStyle()
                               | IWindow::tabStop
                               | IWindow::group );

  lastName = new IEntryField( WND_LASTNAME,
                              enrollCanvas,
                              enrollCanvas,
                              IRectangle(),
                              IEntryField::defaultStyle()
                              | IWindow::tabStop );

  cheetahList = new IListBox( WND_CHEETAHLIST,
                              enrollCanvas,
                              enrollCanvas,
                              IRectangle(),
                              IListBox::defaultStyle()
                               | IWindow::tabStop );

/*------------------------------------------------------------------------|
| Set the control pointers to autodelete.                                 |
|------------------------------------------------------------------------*/
  enrollCanvas->setAutoDeleteObject();
  nameStatic->setAutoDeleteObject();
  firstNameStatic->setAutoDeleteObject();
  lastNameStatic->setAutoDeleteObject();
  cheetahStatic->setAutoDeleteObject();
  firstName->setAutoDeleteObject();
  lastName->setAutoDeleteObject();
  cheetahList->setAutoDeleteObject();

/*------------------------------------------------------------------------|
| Set the text for the controls.                                          |
|------------------------------------------------------------------------*/
  nameStatic->setText     ( WND_NAMESTATIC );
  firstNameStatic->setText( WND_FIRSTNAMESTATIC );
  lastNameStatic->setText ( WND_LASTNAMESTATIC );
  cheetahStatic->setText  ( WND_CHEETAHSTATIC );

/*------------------------------------------------------------------------|
| Set entries to the listbox.                                             |
|------------------------------------------------------------------------*/
  cheetahList->addAsLast( WND_INFO_CHEETAH     );
  cheetahList->addAsLast( WND_INFO_CHEETAH + 1 );
  cheetahList->addAsLast( WND_INFO_CHEETAH + 2 );
  cheetahList->addAsLast( WND_INFO_CHEETAH + 3 );
  cheetahList->addAsLast( WND_INFO_CHEETAH + 4 );

/*------------------------------------------------------------------------|
| Limit the entryfield text. This also has the affect on the entryfield's |
|   minimumSize used by the canvas.                                       |
|------------------------------------------------------------------------*/
  firstName->setLimit( 12 );
  lastName->setLimit ( 12 );

/*------------------------------------------------------------------------|
| Set characteristics for the listbox. This also has the affect on the    |
|   listbox's minimumSize used by the canvas.                             |
|------------------------------------------------------------------------*/
  cheetahList->setMinimumRows( 5 );
  cheetahList->setMinimumCharacters( 10 );

/*------------------------------------------------------------------------|
| Add the controls to the multicell canvas.                               |
| Allow the 6th column to expand for the long static text.                |
|------------------------------------------------------------------------*/
  enrollCanvas->addToCell( nameStatic,      2, 2, 5 );
  enrollCanvas->addToCell( firstNameStatic, 2, 4 );
  enrollCanvas->addToCell( firstName,       2, 5 );
  enrollCanvas->addToCell( lastNameStatic,  5, 4 );
  enrollCanvas->addToCell( lastName,        5, 5 );
  enrollCanvas->addToCell( cheetahStatic,   2, 7, 5 );
  enrollCanvas->addToCell( cheetahList,     2, 8 );
  enrollCanvas->setColumnWidth( 6, 0, true );

  return enrollCanvas;
}

/**************************************************************************
* EnrollPage :: validatePageWindow                                        *
*                                                                         *
* validatePageWindow is called by ITabControl when the user selects a     *
* new page.  We will ensure that the data entered on this page is valid.  *
* If it is not valid, false is returned to prevent the page selection     *
* from continuing.  If the data is valid, we will update the sponsor      *
* and cheetah names stored in our test class.                             *
**************************************************************************/
bool EnrollPage :: validatePageWindow( )
{
/*------------------------------------------------------------------------|
| Display a message box to indicate an incomplete enrollment.             |
| Return false to prevent the page turn.                                  |
|------------------------------------------------------------------------*/
  if (firstName->text() == IString() ||
      lastName->text() == IString() ||
      cheetahList->numberOfSelections() == 0)
  {
     IMessageBox
       msgBox( tabControl() );
     msgBox.setTitle( STR_ENROLL_ERROR_TITLE );
     msgBox.show( STR_ENROLL_ERROR_MSG, IMessageBox::information );
     return false;
  }

/*------------------------------------------------------------------------|
| The data is present.  Store the sponsor name and cheetah selection.     |
| Return true to allow the page turn to complete.                         |
|------------------------------------------------------------------------*/
  IString
    sponsorName( IString( firstName->text() ) +
                 IString( " " ) +
                 IString( lastName->text() ));
  tabTest->setSponsor( sponsorName );

  return true;
}

/*******************************************************************************
* TabTest :: cheetahIndex                                                      *
*                                                                              *
* Returns the cheetah selection index from the listbox                         *
*******************************************************************************/
unsigned long TabTest :: cheetahIndex( ) const
{
  return enrollPage.selectedCheetahIndex();
}

/**************************************************************************
* DataPage :: DataPage                                                    *
*                                                                         *
* An ITabPage derived class used to encapsulate the data and windows      *
* used for the second page of our application's tab control.  This tab    *
* page will display the vital statistics of the adopted cheetah.          *
**************************************************************************/
DataPage :: DataPage( TabTest *tabTest )
  : ITabPage( IText( IApplication::current().userResourceLibrary().loadString(STR_DATA) ))
  , tabTest( tabTest )
  , resLib( IApplication::current().userResourceLibrary() )
{
/*------------------------------------------------------------------------|
| Set the help panel id for this tab page.                                |
|------------------------------------------------------------------------*/
  setHelpId( 300 );
}


/**************************************************************************
* DataPage :: createPageWindow                                            *
*                                                                         *
* This createPageWindow override is called when the user selects this     *
* page for the first time.                                                *
**************************************************************************/
IWindow* DataPage :: createPageWindow ( )
{
/*------------------------------------------------------------------------|
| Create the page window and controls for this page.                      |
|------------------------------------------------------------------------*/
  IMultiCellCanvas
    *dataCanvas = new IMultiCellCanvas( WND_DATAPAGE,
                                        tabControl(),
                                        tabControl() );
  sponsorNameLabel =   new IStaticText( WND_INFO_SPONSOR_LABEL,
                                        dataCanvas,
                                        dataCanvas );
  sponsorName =        new IEntryField( WND_INFO_SPONSOR,
                                        dataCanvas,
                                        dataCanvas );
  cheetahNameLabel =   new IStaticText( WND_INFO_CHEETAH_LABEL,
                                        dataCanvas,
                                        dataCanvas );
  cheetahName =        new IEntryField( WND_INFO_CHEETAH,
                                        dataCanvas,
                                        dataCanvas );
  cheetahSexLabel =    new IStaticText( WND_INFO_SEX_LABEL,
                                        dataCanvas,
                                        dataCanvas );
  cheetahSexMale =     new IRadioButton( WND_INFO_SEX_MALE_LABEL,
                                        dataCanvas,
                                        dataCanvas );
  cheetahSexFemale =  new IRadioButton( WND_INFO_SEX_FEMALE_LABEL,
                                        dataCanvas,
                                        dataCanvas );
  cheetahDateOfBirthLabel = new IStaticText( WND_INFO_DOB_LABEL,
                                        dataCanvas,
                                        dataCanvas );
  cheetahDateOfBirth = new IEntryField( WND_INFO_DOB,
                                        dataCanvas,
                                        dataCanvas );
  cheetahWeightLabel = new IStaticText( WND_INFO_DOB_LABEL,
                                        dataCanvas,
                                        dataCanvas );
  cheetahWeight =      new IEntryField( WND_INFO_WEIGHT,
                                        dataCanvas,
                                        dataCanvas );

/*------------------------------------------------------------------------|
| Set the control pointers to autodelete.                                 |
|------------------------------------------------------------------------*/
  dataCanvas->setAutoDeleteObject();
  sponsorNameLabel->setAutoDeleteObject();
  sponsorName->setAutoDeleteObject();
  cheetahNameLabel->setAutoDeleteObject();
  cheetahName->setAutoDeleteObject();
  cheetahSexLabel->setAutoDeleteObject();
  cheetahSexMale->setAutoDeleteObject();
  cheetahSexFemale->setAutoDeleteObject();
  cheetahDateOfBirthLabel->setAutoDeleteObject();
  cheetahDateOfBirth->setAutoDeleteObject();
  cheetahWeightLabel->setAutoDeleteObject();
  cheetahWeight->setAutoDeleteObject();

/*------------------------------------------------------------------------|
| Limit the entryfield text. This also has the affect on the entryfield's |
|   minimumSize used by the canvas.                                       |
|------------------------------------------------------------------------*/
  sponsorName->setLimit       ( 25 );
  cheetahName->setLimit       ( 25 );
  cheetahDateOfBirth->setLimit( 25 );
  cheetahWeight->setLimit     ( 25 );

/*------------------------------------------------------------------------|
| Add the controls to the canvas.                                         |
|------------------------------------------------------------------------*/
  dataCanvas->addToCell( sponsorNameLabel,        2, 2  );
  dataCanvas->addToCell( sponsorName,             3, 2  );
  dataCanvas->addToCell( cheetahNameLabel,        2, 4  );
  dataCanvas->addToCell( cheetahName,             3, 4  );
  dataCanvas->addToCell( cheetahSexLabel,         2, 6  );
  dataCanvas->addToCell( cheetahSexMale,          3, 6  );
  dataCanvas->addToCell( cheetahSexFemale,        3, 7  );
  dataCanvas->addToCell( cheetahDateOfBirthLabel, 2, 9  );
  dataCanvas->addToCell( cheetahDateOfBirth,      3, 9  );
  dataCanvas->addToCell( cheetahWeightLabel,      2, 11 );
  dataCanvas->addToCell( cheetahWeight,           3, 11 );

/*------------------------------------------------------------------------|
| Set the static text data from the resources.                            |
|------------------------------------------------------------------------*/
  sponsorNameLabel->setText       ( WND_INFO_SPONSOR_LABEL );
  cheetahNameLabel->setText       ( WND_INFO_CHEETAH_LABEL );
  cheetahSexLabel->setText        ( WND_INFO_SEX_LABEL );
  cheetahSexMale->setText         ( WND_INFO_SEX_MALE_LABEL );
  cheetahSexFemale->setText       ( WND_INFO_SEX_FEMALE_LABEL );
  cheetahDateOfBirthLabel->setText( WND_INFO_DOB_LABEL );
  cheetahWeightLabel->setText     ( WND_INFO_WEIGHT_LABEL );

/*------------------------------------------------------------------------|
| Disable updating of the editable controls.                              |
|------------------------------------------------------------------------*/
  sponsorName->enableDataUpdate       ( false );
  cheetahName->enableDataUpdate       ( false );
  cheetahSexMale->enable              ( false );
  cheetahSexFemale->enable            ( false );
  cheetahDateOfBirth->enableDataUpdate( false );
  cheetahWeight->enableDataUpdate     ( false );

/*------------------------------------------------------------------------|
| Add three page buttons for this page.  These buttons will be the        |
|   buttons visible when this page is displayed.  Two of these buttons    |
|   are constructed by the application.  The other button is a standard   |
|   button provided by the ITabControl class.                             |
|------------------------------------------------------------------------*/
  IWindow
    *buttonArea = tabControl()->buttonParent();

/*------------------------------------------------------------------------|
| Create two application defined push buttons.  You must use the IWindow  |
|   returned by ITabControl::buttonParent as the parent of any tab control|
|   buttons you construct.                                                |
|------------------------------------------------------------------------*/
  IPushButton
    *previousButton = new IPushButton( ID_PREVIOUS,
                                       buttonArea,
                                       buttonArea ),
    *nextButton = new IPushButton( ID_NEXT,
                                   buttonArea,
                                   buttonArea );

  previousButton->setAutoDeleteObject();
  nextButton->setAutoDeleteObject();

  previousButton->setText( ID_PREVIOUS );
  nextButton->setText( ID_NEXT );

/*------------------------------------------------------------------------|
| Make the next button the default for this page.                         |
|------------------------------------------------------------------------*/
  nextButton->enableDefault();

/*------------------------------------------------------------------------|
| Add the page buttons.                                                   |
|------------------------------------------------------------------------*/
  addPageButton( previousButton );
  addPageButton( nextButton );

/*------------------------------------------------------------------------|
| Add a help button for this page.  This help button will generate        |
|   help messges.                                                         |
|------------------------------------------------------------------------*/
  addPageButton( ITabControl::kHelp );

/*------------------------------------------------------------------------|
| Initialize the fields for this page.                                    |
|------------------------------------------------------------------------*/
  updatePageWindow();

  return dataCanvas;
}

/**************************************************************************
* DataPage :: updatePageWindow                                            *
*                                                                         *
* ITabControl will call updatePageWindow when this page is selected and   *
* a page window has already been constructed for this page.  Your         *
* application can provide an updatePageWindow override to update the      *
* data in the controls on the page.                                       *
**************************************************************************/
void DataPage :: updatePageWindow ()
{
/*------------------------------------------------------------------------|
| Set the controls data.                                                  |
|------------------------------------------------------------------------*/
  unsigned long
    sexId,
    index = tabTest->cheetahIndex();
  IString
    sexStr,
    sponsor = tabTest->sponsor();
  sponsorName->setText            ( sponsor );
  cheetahName->setText            ( WND_INFO_CHEETAH + index );
  cheetahDateOfBirth->setText     ( WND_INFO_DOB + index );
  cheetahWeight->setText          ( WND_INFO_WEIGHT + index );
  sexStr = resLib.loadString      ( WND_INFO_SEX + index );
  sexId = sexStr.asUnsigned();
  cheetahSexMale->select          ( sexId == 0 );
  cheetahSexFemale->select        ( sexId == 1 );
}

/**************************************************************************
* PhotoPage :: PhotoPage                                                  *
*                                                                         *
* The third tab page class.  This page will have a bitmap on the tab.     *
* On the Windows platform, the tab will have both text and a bitmap.      *
* This page will be used to display a photo of the adopted cheetah (all   *
* cheetahs look alike in our zoo!).                                       *
**************************************************************************/
PhotoPage :: PhotoPage( )
  : ITabPage( IText( IApplication::current().userResourceLibrary().loadString(STR_PHOTO) ))
{
/*------------------------------------------------------------------------|
| Set the bitmap to be used on the tab.                                   |
|------------------------------------------------------------------------*/
  IResourceLibrary reslib;
  IBitmapHandle tabBitmap = reslib.loadBitmap( BM_CHEETAH,
                                               ISize( 40, 40 ));
  setTabBitmap( tabBitmap );

/*------------------------------------------------------------------------|
| Set the help panel id for this tab page.                                |
|------------------------------------------------------------------------*/
  setHelpId( 400 );
}

/**************************************************************************
* PhotoPage :: createPageWindow                                           *

* This createPageWindow override is called when the user selects this     *
* page for the first time.                                                *
**************************************************************************/
IWindow* PhotoPage :: createPageWindow( )
{
/*------------------------------------------------------------------------|
| Create an IViewPort page window.  This view port window will be         |
|   sized to fill the entire page window area since the page has the      |
|   ITabPage::autoPageSize style by default.  Its child window is our     |
|   cheetah bitmap.                                                       |
|------------------------------------------------------------------------*/
  photoViewer = new IViewPort( WND_PHOTOPAGE,
                               tabControl(),
                               tabControl() );
  photo = new IBitmapControl( WND_PHOTO,
                              photoViewer,
                              photoViewer,
                              BM_CHEETAH,
                              IRectangle(),
                              IBitmapControl::defaultStyle()
                              | IBitmapControl::sizeImageToWindow );

  photoViewer->setAutoDeleteObject();
  photo->setAutoDeleteObject();

  return photoViewer;
}

/**************************************************************************
* PhotoPage :: minimumPageWindowSize                                      *
*                                                                         *
* This member function is overridden to provide a minimum size for this   *
* tab page's window.                                                      *
**************************************************************************/
ISize PhotoPage :: minimumPageWindowSize( ) const
{

/*------------------------------------------------------------------------|
| If the page window for this page has already been set.                  |
|   Otherwise, call the inherited function.                               |
|------------------------------------------------------------------------*/
  if (pageWindow())
    return ITabPage::minimumPageWindowSize();
  else
/*------------------------------------------------------------------------|
| The page window for this page has not been set yet.  We provide an      |
|   approximate minimum size for the page window.  This size is used by   |
|   ITabControl to determine its minimum size.                            |
|------------------------------------------------------------------------*/
    return ISize( 400, 400 );
}

/*******************************************************************************
* TabCommandHandler :: TabCommandHandler                                       *
*                                                                              *
* Constructor for the application's command handler.                           *
*******************************************************************************/
TabCommandHandler :: TabCommandHandler( TabTest *tabTest )
  : tabTest( tabTest ) { }

/*******************************************************************************
* TabCommandHandler :: command                                                 *
*                                                                              *
* Process command events for our application.                                  *
*******************************************************************************/
bool TabCommandHandler :: command( ICommandEvent& commandEvent )
{
  bool commandProcessed = false;

  switch( commandEvent.commandId() )
  {
    case ITabControl::kOk:
    case ITabControl::kCancel:
    {
      tabTest->close();
      break;
    }

    case ID_PREVIOUS:
    {
/*------------------------------------------------------------------------|
| This command event was generated by one of the page buttons on the      |
|   second tab page.  Turn to the previous page in the tab control.       |
|------------------------------------------------------------------------*/
      ITabControl *tabControl =
            dynamic_cast<ITabControl*>(commandEvent.dispatchingWindow());
      if (tabControl)
      {
         ITabPage *previousPage = tabControl->previousPage(
                                     tabControl->topPage() );
         tabControl->setTopPage( previousPage );
      }
      commandProcessed = true;
      break;
    }

    case ID_NEXT:
    {
/*------------------------------------------------------------------------|
| This command event was generated by one of the page buttons on the      |
|   second tab page.  Turn to the next page in the tab control.           |
|------------------------------------------------------------------------*/
      ITabControl *tabControl =
            dynamic_cast<ITabControl*>(commandEvent.dispatchingWindow());
      if (tabControl)
      {
         ITabPage *nextPage = tabControl->nextPage( tabControl->topPage() );
         tabControl->setTopPage( nextPage );
      }
      commandProcessed = true;
      break;
    }

    default:
    {
      break;
    }
  }

  return commandProcessed;
}
