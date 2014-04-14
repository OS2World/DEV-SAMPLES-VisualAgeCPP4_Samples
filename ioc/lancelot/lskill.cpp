/******************************************************************************
* .FILE:         lskill.cpp                                                   *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Implementation   *
*                                                                             *
* .CLASSES:      SkillPage                                                    *
*                SkillCnrObj                                                  *
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
#include <iexcbase.hpp>
#include <ireslib.hpp>
#include <ihelp.hpp>
#include "lancelot.h"
#include "lskill.hpp"

/******************************************************************************
* Class SkillPage :: SkillPage - Constructor for the skill page               *
*                                                                             *
* Define yourself as an IMultiCellCanvas                                      *
* Create generic page buttons                                                 *
* Create generic page container buttons                                       *
* Define a null skill range combobox                                          *
* Create static text for the skill                                            *
* Create static text for the months experience                                *
* Create entryfield for the skill                                             *
* Create spinbutton for the months experience                                 *
* Define a null container pointer                                             *
* Define a null container object pointer                                      *
* Define a null container column pointer                                      *
* Define a null container column pointer                                      *
* Create an account data object given the key                                 *
* Create a empty account data object                                          *
* Set the key in your private data                                            *
* Set the isQuery in your private data                                        *
* Create the notebook page settings                                           *
******************************************************************************/
SkillPage::SkillPage(      IWindow* pParent,
                           const IString& aKey )
     :IMultiCellCanvas     ( ID_SKILL_PAGE, pParent, pParent ),
      pageButtons          ( ID_STATUS_PAGE_BUTTONS,
                             this, this, false ),
      pageCnrButtons       ( ID_STATUS_PAGE_CNRBUTTONS,
                             this, this, false ),
      pSkillRange          ( NULL ),
      skillText            ( ID_NO_ITEM, this, this ),
      monthsExpText        ( ID_NO_ITEM, this, this ),
      skill                ( ID_SKI_SKILL_EF, this, this,
                             IRectangle(),
                             IEntryField::classDefaultStyle
                             | IControl::tabStop ),
      monthsExp            ( ID_SKI_YRS_EXP_CBX, this, this,
                             IRectangle(),
                             INumericSpinButton:: classDefaultStyle
                             | IControl::tabStop ),
      pCnr                 ( (IContainerControl*) NULL ),
      pSkillCnrObj         ( (SkillCnrObj*) NULL ),
      pColSkill            ( (IContainerColumn*) NULL ),
      pColExp              ( (IContainerColumn*) NULL ),
      skillData            ( aKey ),
      origSkillData        (),
      Key                  ( aKey ),
      thePageSettings      ( IApplication::current().userResourceLibrary().
                             loadString( STR_SKI_SKILL_TAB ), NULL,
                             INotebook::PageSettings::autoPageSize
                             | INotebook::PageSettings::majorTab ),
       isAquery            ( false ),
       cnrSelHandler       ( this )
{
/*-----------------------------------------------------------------------------
| Save the skill data to another object in case the user wishes to            |
|  undo any changes.                                                          |
| Label the static text objects.                                              |
| Set the limit for the entryfield and combobox.                              |
| Set the combobox range.                                                     |
-----------------------------------------------------------------------------*/
   origSkillData = skillData;
   skillText.setText( STR_SKI_SKILL );
   monthsExpText.setText( STR_SKI_YEARS_EXP );
   skill.setLimit( DISPLAY_LARGE );
   monthsExp.setLimit( DISPLAY_SMALL_RANGE );
   monthsExp.setRange( IRange( 0, 99 ) );

/*-----------------------------------------------------------------------------
| Fill the container from the database.                                       |
| Set the objects on yourself (IMultiCellCanvas).                             |
| Start handling the events.                                                  |
-----------------------------------------------------------------------------*/
   fillCnr();
   setCells();
   handleIt();
};


/******************************************************************************
* Class SkillPage :: SkillPage - Constructor for the skill page               *
*                                                                             *
* Define yourself as an IMultiCellCanvas                                      *
* Create generic page buttons                                                 *
* Create generic page container buttons                                       *
* Define a null skill range combobox                                          *
* Create static text for the skill                                            *
* Create static text for the months experience                                *
* Create entryfield for the skill                                             *
* Create spinbutton for the months experience                                 *
* Define a null container pointer                                             *
* Define a null container object pointer                                      *
* Define a null container column pointer                                      *
* Define a null container column pointer                                      *
* Create an account data object given the key                                 *
* Create a empty account data object                                          *
* Set the key in your private data                                            *
* Set the isQuery in your private data                                        *
* Create the notebook page settings                                           *
******************************************************************************/
SkillPage::SkillPage(      IWindow* pParent,
                           LQueryData& qd )
     :IMultiCellCanvas     ( ID_SKILL_PAGE, pParent, pParent ),
      pageButtons          ( ID_STATUS_PAGE_BUTTONS,
                             this, this, true),
      pageCnrButtons       ( ID_STATUS_PAGE_CNRBUTTONS,
                             this, this, false ),
      pSkillRange          ( NULL ),
      skillText            ( ID_NO_ITEM, this, this ),
      monthsExpText        ( ID_NO_ITEM, this, this ),
      skill                ( ID_SKI_SKILL_EF, this, this,
                             IRectangle(),
                             IEntryField::classDefaultStyle
                             | IControl::tabStop ),
      monthsExp            ( ID_SKI_YRS_EXP_CBX, this, this,
                             IRectangle(),
                             INumericSpinButton::classDefaultStyle
                             | IControl::tabStop),
      pCnr                 ( (IContainerControl*) NULL ),
      pSkillCnrObj         ( (SkillCnrObj*) NULL ),
      pColSkill            ( (IContainerColumn*) NULL ),
      pColExp              ( (IContainerColumn*) NULL ),
      skillData            ( qd ),
      origSkillData        (),
      Key                  ( qd.queryName() ),
      thePageSettings      ( IApplication::current().userResourceLibrary().
                             loadString( STR_SKI_SKILL_TAB ), NULL,
                             INotebook::PageSettings::autoPageSize
                             | INotebook::PageSettings::majorTab ),
      isAquery             ( true ),
      cnrSelHandler        ( this )
{
/*-----------------------------------------------------------------------------
| Save the skill data to another object in case the user wishes to            |
|  undo any changes.                                                          |
| Label the static text objects.                                              |
| Set the limit for the entryfield and combobox.                              |
| Set the combobox range.                                                     |
-----------------------------------------------------------------------------*/
   origSkillData = skillData;
   skillText.setText( STR_SKI_SKILL  );
   monthsExpText.setText( STR_SKI_YEARS_EXP );
   skill.setLimit( DISPLAY_LIMIT );
   monthsExp.setLimit( DISPLAY_SMALL_RANGE );
   monthsExp.setRange( IRange( 0, 99 ) );

/*-----------------------------------------------------------------------------
| Fill the container from the database.                                       |
-----------------------------------------------------------------------------*/
   fillCnr();

/*-----------------------------------------------------------------------------
| Create the skill range combobox.                                            |
| Set the skill range if valid.                                               |
-----------------------------------------------------------------------------*/
   pSkillRange = new QueryRange( ID_SKILL_PAGE_RANGE,
                                 this, this,
                                 ID_SKILL_RANGE);

   if ( skillData.theRange().length() )
      pSkillRange->setRange( skillData.theRange() );

/*-----------------------------------------------------------------------------
| Set the objects on yourself (IMultiCellCanvas).                             |
| Start handling the events.                                                  |
-----------------------------------------------------------------------------*/
   setCells();
   handleIt();
};


/******************************************************************************
* Class SkillPage :: ~SkillPage - Destructor for the skill page               *
******************************************************************************/
SkillPage :: ~SkillPage()
{
/*-----------------------------------------------------------------------------
| Stop handling events.                                                       |
-----------------------------------------------------------------------------*/
   ICommandHandler::stopHandlingEventsFor( &pageButtons );
   ICommandHandler::stopHandlingEventsFor( &pageCnrButtons );
   ISelectHandler::stopHandlingEventsFor( &pageButtons );
   cnrSelHandler.stopHandlingEventsFor( pCnr );
};


/******************************************************************************
* Class SkillPage :: handleIt - Handle events for the skill page              *
******************************************************************************/
SkillPage&  SkillPage :: handleIt()
{
/*-----------------------------------------------------------------------------
| Start handling events.                                                      |
| Return yourself.                                                            |
-----------------------------------------------------------------------------*/
   ICommandHandler::handleEventsFor( &pageButtons );
   ICommandHandler::handleEventsFor( &pageCnrButtons );
   ISelectHandler::handleEventsFor( &pageButtons );
   return *this;
}


/******************************************************************************
* Class SkillPage :: fillCnr - Set up the container                           *
******************************************************************************/
SkillPage&  SkillPage :: fillCnr()
{
/*-----------------------------------------------------------------------------
| If the container already exists,                                            |
|  delete all the objects                                                     |
| Else create a new container.                                                |
-----------------------------------------------------------------------------*/
   if ( pCnr )
      pCnr->deleteAllObjects();
   else
   {
      pCnr = new IContainerControl( ID_SKI_CNR,
                                    this, this,
                                    IRectangle(),
                                    IContainerControl::classDefaultStyle
                                    | IContainerControl::readOnly | IContainerControl::pmCompatible,
                                    IContainerControl::readOnlyTitle
                                    | IContainerControl::detailsView );

/*-----------------------------------------------------------------------------
| Handle selection events for the new container.                              |
-----------------------------------------------------------------------------*/
      cnrSelHandler.handleEventsFor( pCnr );

/*-----------------------------------------------------------------------------
| Delete the objects when the container is deleted.                           |
| Tell the container to allow multiple selection.                             |
| Tell the container to automatically refresh upon changes.                   |
-----------------------------------------------------------------------------*/
      pCnr->setDeleteObjectsOnClose();
      pCnr->setDeleteColumnsOnClose();
      pCnr->setMultipleSelection();

/*-----------------------------------------------------------------------------
| Create two container columns.                                               |
-----------------------------------------------------------------------------*/
      pColSkill =
         new IContainerColumn( pSkillCnrObj->skillOffset(),
                               IContainerColumn::defaultHeadingStyle(),
                               IContainerColumn::string );

      pColExp =
         new IContainerColumn( pSkillCnrObj->expOffset(),
                               IContainerColumn::defaultHeadingStyle(),
                               IContainerColumn::string );

/*-----------------------------------------------------------------------------
| Label the container column headings.                                        |
| Show the headings.                                                          |
| Show the headings.                                                          |
-----------------------------------------------------------------------------*/
      pColSkill->setHeadingText(STR_SKI_CURRENT_SKILLS);
      pColExp->setHeadingText(STR_SKI_YEARS_EXP);
      pCnr->showDetailsViewTitles();

/*-----------------------------------------------------------------------------
| Add the columns to the container.                                           |
| Add column separators between the columns.                                  |
-----------------------------------------------------------------------------*/
     pCnr->addColumn(pColSkill);
     pCnr->addColumn(pColExp);
     pColSkill->showSeparators( IContainerColumn::verticalSeparator
                                | IContainerColumn::horizontalSeparator );
     pColExp->showSeparators( IContainerColumn::horizontalSeparator );
   }

/*-----------------------------------------------------------------------------
| Start from the beginning of the skill data.                                 |
| While there exists items,                                                   |
|   add objects to the container.                                             |
| Refresh the container.                                                      |
| Return yourself.                                                            |
-----------------------------------------------------------------------------*/
   IString
      skill,
      exp;
   LSkillData::Rule
      rule;

   skillData.setFirst();
   while ( skillData.getItem( skill, exp, rule ) )
   {
      addSkill( skill, exp );
      skillData.getNext();
   }

   pCnr->refresh();

   return *this;
};


/******************************************************************************
* Class SkillPage :: setCells - Set up your multicell canvas cells            *
******************************************************************************/
SkillPage&  SkillPage :: setCells()
{
/*-----------------------------------------------------------------------------
| Add the objects to your multicell canvas.                                   |
| Allow the container to expand horizontally.                                 |
| Allow the page buttons to expand horizontally.                              |
| Return yourself.                                                            |
-----------------------------------------------------------------------------*/
   addToCell( &skillText,         2,  2 );
   addToCell( &skill,             2,  3 );

   addToCell( &monthsExpText,     2,  4 );
   addToCell( &monthsExp,         2,  5 );

   if ( pSkillRange )
      addToCell( pSkillRange,     3,  5,  5,  1 );

   addToCell( pCnr,               2,  7,  8,  3 );
   addToCell( &pageCnrButtons,   10,  9 );
   setColumnWidth(                9,  0,  true );

   addToCell( &pageButtons,       2, 12,  7,  3 );
   setColumnWidth(                8,  0,  true );

   return *this;
};


/******************************************************************************
* Class SkillPage :: verifyAndSave - Save page information to the database    *
******************************************************************************/
bool SkillPage::verifyAndSave( IString& theString,
                                         IString& theEntry,
                                         const IString theName )
{
/*-----------------------------------------------------------------------------
| If there is no data or is a query, return.                                  |
-----------------------------------------------------------------------------*/
   if ( ( ! theName.length() )
        && ( ! Key.length() )
        || isAquery )
      return true;

/*-----------------------------------------------------------------------------
| If able to retrieve the container information,                              |
|  save the information to the database based on the key or query name.       |
-----------------------------------------------------------------------------*/
   if ( setSkillData() )
   {
      if ( ( theName.length() ) && ( theName.isAlphanumeric() ) )
         skillData.save( theName );
       else
         if ( ( Key.length() ) && ( Key.isAlphanumeric() ) )
            skillData.save( Key );
   }

   return true;
};

/******************************************************************************
* Class SkillPage :: setSkillData - Retrieve the page information             *
******************************************************************************/
bool SkillPage::setSkillData()
{
   IContainerControl::ObjectCursor
      iterator( *pCnr );

   iterator.setToFirst();
   if ( ! iterator.isValid() )
      return false;

   SkillCnrObj
     *cnrEntry;
   IString
      it1,
      it2;

/*-----------------------------------------------------------------------------
| Empty the bag.                                                              |
| Iterate through the cursor and add objects to the bag.                      |
-----------------------------------------------------------------------------*/
   skillData.emptyBag();
   while ( iterator.isValid() )
   {
      cnrEntry = (SkillCnrObj *) iterator.current();
      this->skillData.putItem( cnrEntry->getSkill(), cnrEntry->getExp() );
      cnrEntry = (SkillCnrObj *) iterator.next();
   }

   return true;
};


/******************************************************************************
* Class SkillPage :: fillEntryfields - Fill the entryfields for the object    *
******************************************************************************/
SkillPage& SkillPage::fillEntryfields( SkillCnrObj* pCnrObject )
{
/*-----------------------------------------------------------------------------
| Set the entryfields for the given skill container object.                   |
| Return yourself.                                                            |
-----------------------------------------------------------------------------*/
   skill.setText( pCnrObject->getSkill() );
   monthsExp.setValue( pCnrObject->getExp().asInt() );

   return *this;
};


/******************************************************************************
* Class SkillPage :: command - Catch and process command events.              *
******************************************************************************/
bool SkillPage::command( ICommandEvent& cmdEvent )
{
   IString
      theMonthsExp = monthsExp.value(),
      theSkill = skill.text();
   LSkillData::Rule
      theRule = LSkillData::na;
   bool
      rc = false;
   unsigned int
      count = 0;

/*-----------------------------------------------------------------------------
| Create a container object cursor based on the selected objects.             |
| Process the command events.                                                 |
-----------------------------------------------------------------------------*/
   IContainerControl::ObjectCursor
      soc( *pCnr, IContainerObject::selected );

   switch ( cmdEvent.commandId() )
   {
/*-----------------------------------------------------------------------------
| User pressed the UNDO button.                                               |
| Reset the skill data to the original skill data.                            |
| Reset the container.                                                        |
| Reset the entryfields.                                                      |
-----------------------------------------------------------------------------*/
      case ID_BUTTON_UNDO:
      {
         skillData = origSkillData;
         fillCnr();
         skill.setText( "" );
         monthsExp.setValue( 0 );
         rc = true;
         break;
      }

/*-----------------------------------------------------------------------------
| User pressed the REMOVE button.                                             |
| Iterate through the selected objects,                                       |
|  remove the object from the the database.                                   |
-----------------------------------------------------------------------------*/
      case ID_BUTTON_REMOVE:
      {
         for ( soc.setToFirst();
               soc.isValid();
               soc.setToNext() )
         {
            SkillCnrObj
               *pObj = (SkillCnrObj *) soc.current();
            skillData.putItem( pObj->getSkill(),
                               pObj->getExp(),
                               LSkillData::remove );
           ++count;
         }

/*-----------------------------------------------------------------------------
| If no container objects were selected,                                      |
|  notify the user.                                                           |
-----------------------------------------------------------------------------*/
         if ( ! count )
         {
            IMessageBox
               warning( owner() );
            warning.show( STR_MSG_REMOVE,
                          IMessageBox::enterButton
                          | IMessageBox::informationIcon );
         }
/*-----------------------------------------------------------------------------
| Else remove the selected objects from the container.                        |
| Refresh the container.                                                      |
-----------------------------------------------------------------------------*/
         else
         {
            pCnr->removeSelectedObjects();
            skill.setText( "" );
            monthsExp.setValue( 0 );
            pCnr->refresh();
         }
         rc = true;
         break;
      }

/*-----------------------------------------------------------------------------
| User pressed the CHANGE button.                                             |
| Ignore all but the first selected container object.                         |
| Update the entryfields with the selected container object information.      |
-----------------------------------------------------------------------------*/
      case ID_BUTTON_CHANGE:
      {
         soc.setToFirst();
         if ( soc.isValid() )
         {
            if ( theSkill.length() )
            {
               changeSkill( theSkill, theMonthsExp, (SkillCnrObj*) soc.current() );
               skill.setText( "" );
               monthsExp.setValue( 0 );
            }
         }

/*-----------------------------------------------------------------------------
| If no container objects were selected,                                      |
|  notify the user.                                                           |
-----------------------------------------------------------------------------*/
         else
         {
            IMessageBox
               warning( owner() );
            warning.show( STR_MSG_CHANGE,
                          IMessageBox::enterButton
                          | IMessageBox::informationIcon );
         }

/*-----------------------------------------------------------------------------
| Deselect any container objects.                                             |
-----------------------------------------------------------------------------*/
         unMark();
         rc = true;
         break;
      }

/*-----------------------------------------------------------------------------
| User pressed the ADD button.                                                |
| Add the entryfield information to the database and container.               |
| Reset the entryfields.                                                      |
-----------------------------------------------------------------------------*/
      case ID_BUTTON_ADD:
      {
         if ( theSkill.length() )
         {
            addSkill( theSkill, theMonthsExp );
            skill.setText( "" );
            monthsExp.setValue( 0 );
         }

/*-----------------------------------------------------------------------------
| Deselect any container objects.                                             |
-----------------------------------------------------------------------------*/
         unMark();
         rc = true;
         break;
      }


/*-----------------------------------------------------------------------------
| User pressed the HELP button.                                               |
| Show the help for the account page.                                         |
-----------------------------------------------------------------------------*/
      case ID_BUTTON_HELP:
      {
         IHelpWindow::helpWindow( this )->
            show( IResourceId( ID_SKILL_PAGE ) );
         rc = true;
         break;
      }
  }

  return rc;
};


/******************************************************************************
* Class SkillPage :: addSkill - Add the skill information to the container    *
******************************************************************************/
bool SkillPage::addSkill( IString& skill, IString& exp )
{
   bool
      rc = true;

/*-----------------------------------------------------------------------------
| Create a container text cursor based on the skill.                          |
-----------------------------------------------------------------------------*/
   IContainerControl::TextCursor
      txtCur( *pCnr, IString( skill ), true, false, true );

/*-----------------------------------------------------------------------------
| Start at the beginning of the cursor.                                       |
| If the cursor contains a duplicate, set the return code to false.           |
-----------------------------------------------------------------------------*/
   for ( txtCur.setToFirst();
         txtCur.isValid();
         txtCur.setToNext() )
   {
      if ( ( (SkillCnrObj*) txtCur.current() )->getExp() == exp )
      {
         rc = false;
         break;
      }
   }

/*-----------------------------------------------------------------------------
| If the object doesn't exist,                                                |
|  Add the object to the database.                                            |
|  Create an skill container object.                                          |
|  Add the object to the container.                                           |
|  Refresh the container.                                                     |
-----------------------------------------------------------------------------*/
   if ( rc )
   {
      if ( isAquery )
      {
         if ( ! skill.length() )
            skill = "*";
         if ( ! exp.length() )
            exp = "*";
      }

      skillData.putItem( skill, exp, LSkillData::add );
      pSkillCnrObj = new SkillCnrObj( skill, exp );
      pCnr->addObject( pSkillCnrObj );
      pCnr->refresh();
   }

   return rc;
}

/******************************************************************************
* Class SkillPage :: changeSkill - Change the skill information for the       *
*  selected container object.                                                 *
******************************************************************************/
bool SkillPage::changeSkill( IString& skill, IString& exp,
                                       SkillCnrObj* pCnrObj )
{
   bool
      rc = true;

/*-----------------------------------------------------------------------------
| Create a container text cursor based on the skill.                          |
-----------------------------------------------------------------------------*/
   IContainerControl::TextCursor
      txtCur( *pCnr, IString( skill ), true, false, true );

/*-----------------------------------------------------------------------------
| Start at the beginning of the cursor.                                       |
| If the cursor contains a duplicate, set the return code to false.           |
-----------------------------------------------------------------------------*/
   for ( txtCur.setToFirst();
         txtCur.isValid();
         txtCur.setToNext() )
   {
      if ( ( (SkillCnrObj*) txtCur.current() )->getExp() == exp )
      {
         rc = false;
         break;
      }
   }

   txtCur.setToFirst();
   if ( !txtCur.isValid() )
      rc = false;

/*-----------------------------------------------------------------------------
| If the container object exists -and- the skill exists,                      |
|  Set the container object's data.                                           |
|  Reset the entryfields.                                                     |
|  Deselect the container objects.                                            |
-----------------------------------------------------------------------------*/
   if ( pCnrObj && rc )
   {
      pCnrObj->setSkill( skill );
      pCnrObj->setExp( exp );
   }

   return rc;
}


/******************************************************************************
* Class SkillPage :: unMark - Deselect the selected container objects.        *
******************************************************************************/
SkillPage&  SkillPage ::  unMark()
{
   IContainerControl::ObjectCursor
      co( *pCnr );
   for ( co.setToFirst();
         co.isValid();
         co.setToNext() )
   {
      try
      {
         pCnr->removeSelected( pCnr->objectAt( co ) );
      }
      catch ( IException& exc )
      {}
   }
   pCnr->refresh();
   return *this;
};


/******************************************************************************
* Class SkillCnrObj :: SkillCnrObj - Constructor for skill container objects  *
*                                                                             *
* Define yourself as a container object.                                      *
* Set the skill in your private data.                                         *
* Set the experience in your private data.                                    *
******************************************************************************/
SkillCnrObj::SkillCnrObj( const IString& stSkill,
                          const IString& stExp )
     :IContainerObject(),
      skill( stSkill ),
      exp( stExp )
{};


/******************************************************************************
* Class SkillCnrObj :: ~SkillCnrObj - Destructor for skill container objects  *
******************************************************************************/
SkillCnrObj :: ~SkillCnrObj()
{};
