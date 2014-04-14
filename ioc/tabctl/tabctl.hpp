/******************************************************************************
* .FILE:         tabctl.hpp                                                   *
*                                                                             *
* .DESCRIPTION:  Tab Control Sample Program:  Class Header                    *
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
#ifndef TABCTL_HPP
#define TABCTL_HPP

#include <ibmpctl.hpp>
#include <icmdhdr.hpp>
#include <iframe.hpp>
#include <ihelp.hpp>
#include <ilistbox.hpp>
#include <imcelcv.hpp>
#include <itabctl.hpp>
#include <ientryfd.hpp>
#include <iradiobt.hpp>
#include <istattxt.hpp>
#include <ivport.hpp>
#include <istring.hpp>
#include "tabctl.h"

class TabTest;

/**************************************************************************
* Class TabCommandHandler                                                 *
*                                                                         *
* Handler to process command events                                       *
**************************************************************************/
class TabCommandHandler : public ICommandHandler
{
  public:
/*------------------------------ Constructor -----------------------------|
| Construct the object in only one way:                                   |
| 1) A pointer to a TabTest frame window.                                 |
|------------------------------------------------------------------------*/
    TabCommandHandler( TabTest *tabTest );

/*------------------------------ Destructor ------------------------------|
| Destruct the object with:                                               |
| 1) No parameters                                                        |
-------------------------------------------------------------------------*/
    virtual
     ~TabCommandHandler( ) { };

  protected:
/*------------------------ Override Command Function ---------------------|
| The command function is called to handle application command events.    |
-------------------------------------------------------------------------*/
    virtual bool
      command( ICommandEvent& commandEvent );

  private:
    TabTest 
     *tabTest;
};

/**************************************************************************
* Class EnrollPage                                                        *
*                                                                         *
* Enrollment tab page class.                                              *
**************************************************************************/
class EnrollPage : public ITabPage
{
  public:
/*------------------------------ Constructor -----------------------------|
| Construct the object in only one way:                                   |
| 1) A pointer to a TabTest frame window.                                 |
|------------------------------------------------------------------------*/
    EnrollPage( TabTest *tabTest );

/*------------------------------ Destructor ------------------------------|
| Destruct the object with:                                               |
| 1) No parameters                                                        |
-------------------------------------------------------------------------*/
    virtual
     ~EnrollPage( ) { };

/*------------------------------ Accessors -------------------------------|
| These functions provide a means of getting and settings the accessible  |
| attributes of instances of this class:                                  |
|   validatePageWindow     - Returns true if required page information    |
|                            is satisfied.                                |
|   selectedCheetahIndex   - Returns the selected cheetah index from the  |
|                            listbox.                                     |
-------------------------------------------------------------------------*/
    bool
      validatePageWindow( );

    unsigned long
      selectedCheetahIndex( ) const 
        { return cheetahList->selection(); }

  protected:
    IWindow
     *createPageWindow( );

  private:
    IEntryField
     *firstName,
     *lastName;

    IListBox
     *cheetahList;

    TabTest
     *tabTest;
};

/**************************************************************************
* Class DataPage                                                          *
*                                                                         *
* Statics tab page class.                                                 *
**************************************************************************/
class DataPage : public ITabPage
{
  public:
/*------------------------------ Constructor -----------------------------|
| Construct the object in only one way:                                   |
| 1) A pointer to a TabTest frame window.                                 |
|------------------------------------------------------------------------*/
    DataPage( TabTest *tabTest );

/*------------------------------ Destructor ------------------------------|
| Destruct the object with:                                               |
| 1) No parameters                                                        |
-------------------------------------------------------------------------*/
    virtual
     ~DataPage() { };

  protected:
    virtual IWindow
     *createPageWindow( );

    virtual void
      updatePageWindow( );

  private:

    IStaticText
     *sponsorNameLabel,
     *cheetahNameLabel,
     *cheetahSexLabel,
     *cheetahDateOfBirthLabel,
     *cheetahWeightLabel;

    IRadioButton
     *cheetahSexMale,
     *cheetahSexFemale;

    IEntryField
     *sponsorName,
     *cheetahName,
     *cheetahDateOfBirth,
     *cheetahWeight;

    TabTest
     *tabTest;

    IResourceLibrary
      resLib;
};

/**************************************************************************
* Class PhotoPage                                                         *
*                                                                         *
* Photo viewer tab page class.                                            *
**************************************************************************/
class PhotoPage : public ITabPage
{
  public:
/*------------------------------ Constructor -----------------------------|
| Construct the object in only one way:                                   |
| 1) No parameters.                                                       |
|------------------------------------------------------------------------*/
    PhotoPage( );

/*------------------------------ Destructor ------------------------------|
| Destruct the object with:                                               |
| 1) No parameters                                                        |
-------------------------------------------------------------------------*/
    virtual
     ~PhotoPage() { };

  protected:
    IWindow
     *createPageWindow( );

    ISize
      minimumPageWindowSize( ) const;

  private:
    IViewPort
     *photoViewer;

    IBitmapControl
     *photo;
};

/**************************************************************************
* Class TabTest                                                           *
*                                                                         *
* Tab control sample main window.                                         *
**************************************************************************/
class TabTest : public IFrameWindow
{
  public:
/*------------------------------ Constructor -----------------------------|
| Construct the object in only one way:                                   |
| 1) A window IDrs.                                                       |
|------------------------------------------------------------------------*/
    TabTest( unsigned long windowId );

/*------------------------------ Destructor ------------------------------|
| Destruct the object with:                                               |
| 1) No parameters                                                        |
-------------------------------------------------------------------------*/
    virtual
     ~TabTest( ) { };

/*------------------------------ Accessors -------------------------------|
| These functions provide a means of getting and settings the accessible  |
| attributes of instances of this class:                                  |
|   sponsor          - Returns the name of the sponsor.                   |
|   setSponsor       - Sets the name of the sponsor.                      |
|   cheetahIndex     - Returns the selected cheetah index from enroll page|
-------------------------------------------------------------------------*/
    IString
      sponsor( ) const;

    TabTest
     &setSponsor( const IString& currentSponsor );

    unsigned long
      cheetahIndex( ) const;

  private:
    ITabControl
      tabControl;

    EnrollPage
      enrollPage;

    DataPage
      dataPage;

    PhotoPage
      photoPage;

    TabCommandHandler
      tabCommandHandler;

    IHelpWindow
      helpWindow;

    IString
      sponsorName;
};

#endif
