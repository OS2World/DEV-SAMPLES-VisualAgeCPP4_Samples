/*******************************************************************************
* .FILE:     lpagectl.cpp                                                     *
*                                                                             *
* .DESCRIPTION: Page buttons, Container buttons, range combobox.              *
*               These are generic page controls                               *
*                                                                             *
* .CLASSES                                                                    *
*    PageButtons                                                              *
*    PageCnr                                                                  *
*    PageScroll                                                               *
*    PageCnrSelHandler                                                        *
*    QueryRange                                                               *
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
*                                                                              *
* .NOTE: WE RECOMMEND USING A FIXED SPACE FONT TO LOOK AT THE SOURCE          *
*                                                                              *
*******************************************************************************/
#include <ireslib.hpp>
#include "lancelot.h"
#include "lpagectl.hpp"
#include "lacct.hpp"
#include "lskill.hpp"
#include "lproject.hpp"
#include "ltask.hpp"

//*****************************************************************************
// Class PageButtons :: PageButtons() contructor
//*****************************************************************************
PageButtons :: PageButtons ( unsigned long windowId,
                             IMultiCellCanvas* parent,
                             IMultiCellCanvas* owner,
                             bool aQueryButton )
    : ISetCanvas( windowId, parent, owner )
     ,selectHandler( parent )
{
    if ( aQueryButton )
    {
        queryButton = new AGraphicPushButton( ID_BUTTON_QUERY, this, this,
                                              ID_PAGE_QUERY);
        saveButton = new AGraphicPushButton( ID_BUTTON_SAVE,
                                             this,
                                             this,
                                             ID_PAGE_SAVE);
        undoButton = NULL;
    }
    else
    {
      undoButton = new AGraphicPushButton( ID_BUTTON_UNDO,
                                           this,
                                           this,
                                           ID_PAGE_UNDO);

      queryButton = NULL;
      saveButton  = NULL;
    }

    helpButton = new AGraphicPushButton( ID_BUTTON_HELP,
                                         this,
                                         this,
                                         ID_PAGE_HELP);
    gridCheckBox = new ICheckBox( ID_BUTTON_GRID,
                                  this,
                                  this );
    gridCheckBox->setText( ID_BUTTON_GRID );
    selectHandler.handleEventsFor( gridCheckBox );

    setDeckOrientation( ISetCanvas::horizontal );
}

//*****************************************************************************
// Class PageButtons :: ~PageButtons() destructor
//*****************************************************************************
PageButtons :: ~PageButtons()
{
    delete queryButton;
    delete saveButton;
    delete undoButton;
    delete helpButton;
    selectHandler.stopHandlingEventsFor( gridCheckBox );
    delete gridCheckBox;
}

//*****************************************************************************
// CLASS PageButtonsSelectHandler  - constructor
//*****************************************************************************
PageButtonsSelectHandler::PageButtonsSelectHandler( IMultiCellCanvas* pMulticell )
    : ISelectHandler()
     ,theParentMulticell( pMulticell )
{
}

//*****************************************************************************
// CLASS PageButtonsSelectHandler  - destructor
//*****************************************************************************
PageButtonsSelectHandler::~PageButtonsSelectHandler()
{
}

//*****************************************************************************
// CLASS GeneralPage :: selected() - select handler
//*****************************************************************************
bool PageButtonsSelectHandler::selected(IControlEvent& event)
{
  theParentMulticell->enableGridLines( !( theParentMulticell->hasGridLines() ) );
  return(false);
}


//*****************************************************************************
// Class PageCnrButtons :: PageCnrButtons() constructor
//*****************************************************************************
PageCnrButtons :: PageCnrButtons( unsigned long windowId,
                                  IWindow* parent,
                                  IWindow* owner,
                                  bool noChangeButton )
    : ISetCanvas( windowId, parent, owner )
{
    addButton = new AGraphicPushButton( ID_BUTTON_ADD,
                                        this,
                                        this,
                                        ID_PAGE_ADD);

    if ( !noChangeButton )
    {
        changeButton = new AGraphicPushButton( ID_BUTTON_CHANGE,
                                               this,
                                               this,
                                               ID_PAGE_CHANGE);

    }

   removeButton = new AGraphicPushButton( ID_BUTTON_REMOVE,
                                          this,
                                          this,
                                          ID_PAGE_REMOVE);


   setDeckOrientation( ISetCanvas::vertical );
}

//*****************************************************************************
// Class PageCnrButtons :: ~PageCnrButtons() destructor
//*****************************************************************************
PageCnrButtons :: ~PageCnrButtons()
{
    delete addButton;
    delete changeButton;
    delete removeButton;
}



//*****************************************************************************
// Class PageCnrButtons :: PageScrollButtons()
//*****************************************************************************
PageScrollButtons :: PageScrollButtons( unsigned long windowId,
                                        IWindow* parent,
                                        IWindow* owner )
    : ISetCanvas( windowId, parent, owner )
    , weekEndingText( ID_NO_ITEM, this, this )
    , dateText()
    , prevButton( ID_BUTTON_PREV, this, this,
                  ID_PAGE_PREVIOUS)
    , nextButton( ID_BUTTON_NEXT,  this, this,
                  ID_PAGE_NEXT)
    , displayText()
{
   setPackType(ISetCanvas::even);
   setDeckOrientation( ISetCanvas::horizontal );
}


//*****************************************************************************
// Class PageScrollButtons :: ~PageScrollButtons()
//*****************************************************************************
PageScrollButtons :: ~PageScrollButtons()
{
};


//*****************************************************************************
// Class PageScrollButtons :: setDisplayText() - week ending text string
// Used in TimeCard page.
//*****************************************************************************
PageScrollButtons& PageScrollButtons :: setDisplayText( const char* theStr )
{

   weekEndingText.setText( STR_TCD_WEEK_ENDING_TEXT );
   displayText = theStr;
   displayText += "      ";
   weekEndingText.setText( weekEndingText.text() + displayText );

   return *this;
}


//*****************************************************************************
// Class QuerryRange :: QueryRange()
//*****************************************************************************
QueryRange :: QueryRange( unsigned long windowId,
                          IWindow* parent,
                          IWindow* owner,
                          unsigned long id)
    : IComboBox( id,  parent, owner,
             IRectangle(),
             (IComboBox::classDefaultStyle &
            ~IComboBox::simpleType     |
             IComboBox::readOnlyDropDownType ) |
             IControl::tabStop)
{
   setLimit( DISPLAY_SMALL_RANGE );
   addAsFirst("=");
   addAsLast(">");
   addAsLast("<");
   addAsLast(">=");
   addAsLast("<=");
   setText("=");
}

//*****************************************************************************
// Class QuerryRange :: ~QueryRange()
//*****************************************************************************
QueryRange :: ~QueryRange()
{};


AGraphicPushButton :: AGraphicPushButton( unsigned long id,
                                             IWindow* parent,
                                             IWindow* owner,
                                             unsigned long iconId) :
   IGraphicPushButton( id, parent, owner, IResourceId(iconId), IRectangle(),
        (IGraphicPushButton::classDefaultStyle |
        IControl::tabStop))
{
}

AGraphicPushButton :: ~AGraphicPushButton()
{
}


/******************************************************************************
* Class PageCnrSelHandler :: PageCnrSelHandler - Constructor for a select     *
*  handler for a notebook page's container.                                   *
*                                                                             *
* Define yourself as a select handler.                                        *
* Set the page pointer in your private data.                                  *
* Set the type of notebook page.                                              *
******************************************************************************/
PageCnrSelHandler::PageCnrSelHandler( AccountPage* page )
     :ISelectHandler(),
      pPage( page ),
      pageType( accountPage )
{
};


PageCnrSelHandler::PageCnrSelHandler( SkillPage* page )
     :ISelectHandler(),
      pPage( page ),
      pageType( skillPage )
{
};


PageCnrSelHandler::PageCnrSelHandler( ProjectPage* page )
     :ISelectHandler(),
      pPage( page ),
      pageType( projectPage )
{
};


PageCnrSelHandler::PageCnrSelHandler( TasksPage* page )
     :ISelectHandler(),
      pPage( page ),
      pageType( taskPage )
{
};


/******************************************************************************
* Class PageCnrSelHandler :: ~PageCnrSelHandler - Destructor for the page's   *
*  container select handler.                                                  *
******************************************************************************/
PageCnrSelHandler::~PageCnrSelHandler()
{
};


/******************************************************************************
* Class PageCnrSelHandler :: selected - Handle the select events.             *
******************************************************************************/
bool PageCnrSelHandler::selected( IControlEvent& event )
{
   IContainerControl* pCnr = (IContainerControl*) event.controlWindow();
   IContainerControl::ObjectCursor
      soc( *pCnr,
          IContainerObject::selected );

   soc.setToFirst();
   if ( soc.isValid() )
   {
      switch ( pageType )
      {
         case accountPage :
         {
            ((AccountPage*)pPage)->fillEntryfields( (AcctCnrObj *) soc.current() );
            break;
         }
         case skillPage :
         {
            ((SkillPage*)pPage)->fillEntryfields( (SkillCnrObj *) soc.current() );
            break;
         }
         case projectPage :
         {
            ((ProjectPage*)pPage)->fillEntryfields( (ProjCnrObj *) soc.current() );
            break;
         }
         case taskPage :
         {
            ((TasksPage*)pPage)->fillEntryfields( (TaskCnrObj *) soc.current() );
            break;
         }
      }
   }

   return false;
}
