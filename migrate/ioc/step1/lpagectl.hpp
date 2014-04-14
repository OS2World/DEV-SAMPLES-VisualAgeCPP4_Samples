/*******************************************************************************
* FILE NAME: lpagectl.hpp                                                      *
*                                                                              *
* DESCRIPTION:                                                                 *
*                                                                              *
* Classes                                                                      *
*    PageButtons                                                               *
*    PageCnrButtons                                                            *
*    PageScrollButtons                                                         *
*    QueryRange                                                                *
*                                                                              *
* COPYRIGHT:                                                                   *
*   Licensed Materials - Property of IBM                                       *
*   (C) Copyright IBM Corporation 1992, 1995                                   *
*   All Rights Reserved                                                        *
*   US Government Users Restricted Rights - Use, duplication, or disclosure    *
*   restricted by GSA ADP Schedule Contract with IBM Corp.                     *
*                                                                              *
*******************************************************************************/
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

protected:

inline  virtual
 ISize calcMinimumSize() const {
   return (ISize(40, 40)); }
 };

class PageButtonsSelectHandler : public ISelectHandler
{
public:

    PageButtonsSelectHandler( IMultiCellCanvas* parent );
    ~PageButtonsSelectHandler();
    Boolean
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
                   ,Boolean noChangeButton= false );

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
                ,Boolean noQueryButton = false );

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
      Boolean
         selected( IControlEvent& event );

   private:

      enum
         PageType { accountPage, skillPage, projectPage, taskPage };

      IMultiCellCanvas
        *pPage;

      PageType
        pageType;
};


class QueryRange : public ISetCanvas
{
public:

    QueryRange( unsigned long windowId
               ,IWindow* parent
               ,IWindow* owner
               ,unsigned long id);

    ~QueryRange();

inline IString
    getRange() { return range.text();} ;

inline QueryRange&
    setRange(const IString& r ) { range.setText(r); return *this;} ;


private:

IComboBox
    range;

};

#endif
