/******************************************************************************
* .FILE: acnr.hpp                                                             *
*                                                                             *
* .DESCRIPTION: Container sample application - Class defintions               *
*                                                                             *
* .CLASSES:                                                                   *
*   ACnrexWindow                                                              *
*   ACommandHandler                                                           *
*   Department                                                                *
*   ADepartmentView                                                           *
*   ACnrHandler                                                               *
*   ACnrMenuHandler                                                           *
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
******************************************************************************/
#ifndef ACNR_HPP
#define ACNR_HPP

#include <iframe.hpp>
#include <icmdhdr.hpp>
#include <icnrctl.hpp>
#include <icnrhdr.hpp>
#include <icnrehdr.hpp>
#include <icnrmhdr.hpp>
#include <imenuevt.hpp>

class ACnrexWindow;


/******************************************************************************
* Class ACnrMenuHandler - Container menu handler                              *
******************************************************************************/
class ACnrMenuHandler: public ICnrMenuHandler
{
  public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in only one way:                                       |
| 1) Parameter for IContainerControl                                          |
-----------------------------------------------------------------------------*/
    ACnrMenuHandler( IContainerControl* cnr ) { pcnr = cnr; };

  protected:
    virtual bool
      makePopUpMenu( IMenuEvent& event );

  private:
    IContainerControl
     *pcnr;
};


/******************************************************************************
* Class ACommandHandler - Command handler                                     *
******************************************************************************/
class ACommandHandler: public ICommandHandler
{
  public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in only one way:                                       |
| 1) Parameters for ACnrexWindow, IMenuBar, IContainerColumns                 |
-----------------------------------------------------------------------------*/
    ACommandHandler( ACnrexWindow* window,
                     IMenuBar* menubar,
                     IContainerControl* cnr,
                     IContainerColumn* nameColumn,
                     IContainerColumn* codeColumn,
                     IContainerColumn* addrColumn );

  protected:
    virtual bool
      command( ICommandEvent& event );

  private:
    ACnrexWindow
     *pwin;
    IContainerControl
     *pcnr;
    IMenuBar
     *pmenu;
    IContainerColumn
     *pcolName,
     *pcolCode,
     *pcolAddr;
};


/******************************************************************************
* Class ACnrHandler - Container handler                                       *
******************************************************************************/
class ACnrHandler: public ICnrHandler
{
  public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in only one way:                                       |
| 1) No parameters                                                            |
-----------------------------------------------------------------------------*/
    ACnrHandler() {};
};


/******************************************************************************
* Class ACnrEditHandler - Container edit handler                              *
******************************************************************************/
class ACnrEditHandler: public ICnrEditHandler
{
  public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in only one way:                                       |
| 1) No parameters                                                            |
-----------------------------------------------------------------------------*/
    ACnrEditHandler() {};
};


/******************************************************************************
* Class Department - Describes a department record                            *
******************************************************************************/
class Department : public IContainerObject
{
  friend class IContainerColumn;
  friend class ACnrexWindow;

  public:

    Department( const IString& Name,
                const IPointerHandle& Icon,
                const IString& Code,
                const IString& Address );

/*------------------------------- Accessors -----------------------------------
| These functions provide a means of getting and setting the accessible       |
| attributes of instances of this class:                                      |
|   Code                - Returns the Code string                             |
|   Address             - Returns the Address string                          |
|   setCode             - Sets the code to the given address                  |
|   setAddress          - Sets the address to the given address               |
-----------------------------------------------------------------------------*/
    IString
      Code() const {  return strCode; };
    IString
      Address() const {  return strAddress; };
    Department
     &setCode( IString code ) { strCode = code; return *this; };
    Department
     &setAddress( IString address ) { strAddress = address; return *this; };


/*----------------------------- Handler Callbacks -----------------------------
| These functions provide a means of processing handler callbacks:            |
|   handleOpen          - Handle opening a container object request           |
-----------------------------------------------------------------------------*/
    virtual void
      handleOpen( IContainerControl* container );

  private:
    IString       strAddress;
    IString       strCode;
};


/******************************************************************************
* Class ADepartmentView - Window for displaying department information        *
******************************************************************************/
class ADepartmentView : public IFrameWindow
{
  public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in only one way:                                       |
| 1) Parameter with a Cepartment and IContainerControl                        |
-----------------------------------------------------------------------------*/
    ADepartmentView( Department* aDept, IContainerControl* anOwner );
    virtual ~ADepartmentView();

  private:
    IStaticText
      stext;
    Department
     *saveDept;

};


/******************************************************************************
* Class ACnrexWindow - Main window for application                            *
******************************************************************************/
class ACnrexWindow : public IFrameWindow
{
  friend class ACnrMenuHandler;
  public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in only one way:                                       |
| 1) No parameters                                                            |
-----------------------------------------------------------------------------*/
    ACnrexWindow( unsigned long windowId );
    virtual ~ACnrexWindow() {};

  private:
    IContainerControl
      cnr;
    Department
     *dept1,
     *dept2,
     *dept3,
     *dept4,
     *dept5,
     *dept6;
    IContainerColumn
      colIcon,
      colName,
      colCode,
      colAddress;
    IMenuBar
      menuBar;
    ACommandHandler
      cmdHdr;
    ACnrHandler
      cnrHdr;
    ACnrMenuHandler
      cnrMenuHdr;
    ACnrEditHandler
      cnrEditHdr;
};


/******************************************************************************
* Class SelectedObjectsFilter - Filter function callback for selected objects *
******************************************************************************/
class SelectedObjectsFilter : public IContainerControl::FilterFn
{
  virtual bool
    isMemberOf( IContainerObject* object,
                IContainerControl* container ) const
    {
      return container->isSelected( object );
    }
};


/******************************************************************************
* Class AllObjectsFilter - Filter function callback for all objects           *
******************************************************************************/
class AllObjectsFilter : public IContainerControl::FilterFn
{
  virtual bool
    isMemberOf( IContainerObject* object,
                IContainerControl* container ) const
    {
      return true;
    }
};


/******************************************************************************
* Class SortByCode - Sorts objects by string found in Code column.            *
******************************************************************************/
class SortByCode : public IContainerControl::CompareFn
{
  virtual int
    isEqual( IContainerObject*  object1,
             IContainerObject*  object2,
             IContainerControl* container ) const;
};

#endif
