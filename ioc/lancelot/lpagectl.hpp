/******************************************************************************
* .FILE:         lpagectl.hpp                                                 *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Definition       *
*                                                                             *
* .CLASSES:      PageButtons                                                  *
*                PageCnrButtons                                               *
*                PageScrollButtons                                            *
*                QueryRange                                                   *
*                AGraphicPushButton                                           *
*                PageCnrSelHandler                                            *
*                LPictureVerifyHandler                                        *
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
#ifndef _LPAGECTL_
#define _LPAGECTL_

#include <isetcv.hpp>
#include <igraphbt.hpp>
#include <icheckbx.hpp>
#include <icombobx.hpp>
#include <istring.hpp>
#include <istattxt.hpp>
#include <imsgbox.hpp>
#include <imcelcv.hpp>
#include <iselhdr.hpp>

class AccountPage;
class SkillPage;
class ProjectPage;
class TasksPage;

class AGraphicPushButton : public IGraphicPushButton
{
public:
  AGraphicPushButton( unsigned long windowId,
                       IWindow* parent,
                       IWindow* owner,
                       unsigned long iconid);

  ~AGraphicPushButton();
};

class PageButtonsSelectHandler : public ISelectHandler
{
public:

    PageButtonsSelectHandler( IMultiCellCanvas* parent );
    ~PageButtonsSelectHandler();
    bool
      selected( IControlEvent& event );

private:
    IMultiCellCanvas
     *theParentMulticell;
};

class PageCnrButtons : public ISetCanvas
{
public:

    PageCnrButtons( unsigned long windowId
                   ,IWindow* parent
                   ,IWindow* owner
                   ,bool noChangeButton= false );

    ~PageCnrButtons();

private:

IGraphicPushButton
  *addButton,
  *removeButton,
  *changeButton;

};

class PageButtons : public ISetCanvas
{
public:

    PageButtons( unsigned long windowId
                ,IMultiCellCanvas* parent
                ,IMultiCellCanvas* owner
                ,bool noQueryButton = false );

    ~PageButtons();

private:

AGraphicPushButton
  *queryButton,
  *saveButton,
  *undoButton,
  *helpButton;

ICheckBox
  *gridCheckBox;
PageButtonsSelectHandler
  selectHandler;
};

class PageScrollButtons : public ISetCanvas
{
public:

  PageScrollButtons( unsigned long windowId
                    ,IWindow* parent
                    ,IWindow* owner );

  ~PageScrollButtons();

PageScrollButtons&
    setDisplayText( const char* theStr );

private:

IStaticText
    weekEndingText;

IString
    dateText;

AGraphicPushButton
    prevButton,
    nextButton;

IString
    displayText;

};

/******************************************************************************
* Class PageCnrSelHandler - Page container select handler.                    *
******************************************************************************/
class PageCnrSelHandler : public ISelectHandler
{
   public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object given a page.                                          |
-----------------------------------------------------------------------------*/
      PageCnrSelHandler( AccountPage* page );
      PageCnrSelHandler( SkillPage* page );
      PageCnrSelHandler( ProjectPage* page );
      PageCnrSelHandler( TasksPage* page );
     ~PageCnrSelHandler();

   protected:

/*----------------------------- Event Processing ------------------------------
| Handle and process events:                                                  |
|   selected            - Process select events.                              |
-----------------------------------------------------------------------------*/
      bool
         selected( IControlEvent& event );

   private:

      enum
         PageType { accountPage, skillPage, projectPage, taskPage };

      IMultiCellCanvas
        *pPage;

      PageType
        pageType;
};


class QueryRange : public IComboBox
{
public:

    QueryRange( unsigned long windowId
               ,IWindow* parent
               ,IWindow* owner
               ,unsigned long id);

    ~QueryRange();

inline IString
    getRange() { return text();} ;

inline QueryRange&
    setRange(const IString& r ) { setText(r); return *this;} ;

};

#endif
