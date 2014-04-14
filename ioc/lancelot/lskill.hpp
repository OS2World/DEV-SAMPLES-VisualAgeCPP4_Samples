/******************************************************************************
* .FILE:         lskill.hpp                                                   *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Definition       *
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
#ifndef _LSKILL_
#define _LSKILL_

#include <icnrctl.hpp>
#include <icnrcol.hpp>
#include <imcelcv.hpp>
#include <ientryfd.hpp>
#include <icmdhdr.hpp>
#include <ispinnum.hpp>
#include <imsgbox.hpp>
#include <inotebk.hpp>

#include "ldbase.hpp"
#include "lpagectl.hpp"

/******************************************************************************
* Class SkillCnrObj - Skill container object.                                 *
******************************************************************************/
class SkillCnrObj : public IContainerObject
{
   public:

/*------------------------ Constructors/Destructor ----------------------------
| Construct the object given a skill and experience.                          |
-----------------------------------------------------------------------------*/
      SkillCnrObj( const IString& stSkill,
                   const IString& stExp );
     ~SkillCnrObj();

/*------------------------------- Accessors -----------------------------------
| These functions provide a means of getting and setting the accessible        |
| attributes of instances of this class:                                       |
|   getSkill            - Returns the skill.                                   |
|   getExp              - Returns the experience.                              |
|   setSkill            - Sets the skill.                                      |
|   setExp              - Sets the experience.                                 |
|   skillOffset         - Returns the container offset for the skill.          |
|   expOffset           - Returns the container offset for the experience.     |
-----------------------------------------------------------------------------*/
      inline IString
         getSkill() const {return (skill); };
      inline IString
         getExp()   const {return (exp); };

      inline SkillCnrObj
        &setSkill( const IString& sk ) {skill=sk; return *this;};
      inline SkillCnrObj
        &setExp( const IString& ex ) {exp=ex; return *this;};

      inline unsigned long
         skillOffset() { return ICONTAINERCOLUMN_OFFSETOF(SkillCnrObj, skill); };
      inline unsigned long
         expOffset() { return ICONTAINERCOLUMN_OFFSETOF(SkillCnrObj, exp); };

   private:

      unsigned long
         unDoNum;

      IString
         skill,
         exp;
};


/******************************************************************************
* Class SkillPage - Skill page.                                               *
******************************************************************************/
class SkillPage : public IMultiCellCanvas,
                  public ICommandHandler,
                  public ISelectHandler
{
   public:
      friend class QuerySkill;

/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in one of two ways:                                    |
| 1) IWindow*, IString.                                                       |
| 2) IWindow*, LQueryData.                                                    |
-----------------------------------------------------------------------------*/
      SkillPage( IWindow* pParent,
                 const IString& aKey = NULL );

      SkillPage( IWindow* pParent,
                 LQueryData& qd );

     ~SkillPage();

/*------------------------ Database Functions ---------------------------------
| These functions are used to save data to the database:                      |
|   verifyAndSave       - Verify the page data and save to the database.      |
-----------------------------------------------------------------------------*/
      bool
         verifyAndSave( IString& theString,
                        IString& theEntry,
                        const IString saveName = NULL );

/*------------------------------ Accessors ------------------------------------
| These functions provide a means of getting and setting the accessible       |
| attributes of instances of this class:                                      |
|   pageSettings        - Return the page settings for this page.             |
|   key                 - Return the key.                                     |
-----------------------------------------------------------------------------*/
      inline INotebook::PageSettings
         pageSettings() { return thePageSettings; };

      inline IString
         &key() {return Key;};

/*----------------------------- Page Manipulation -----------------------------
| These functions provide a means of manipulating the instances of this class:|
|   fillEntryfields     - Fill the entryfields for the given container object.|
-----------------------------------------------------------------------------*/
      SkillPage&
         fillEntryfields( SkillCnrObj* cnrObject );


   protected:

/*----------------------------- Event Processing ------------------------------
| Handle and process events:                                                  |
|   command             - Process command events.                             |
|   handleIt            - Start handling events.                              |
-----------------------------------------------------------------------------*/
      bool
         command( ICommandEvent& event );

      SkillPage&
         handleIt();

   private:

      SkillPage
        &setCells(),
        &fillCnr(),
        &unMark();

      bool
         addSkill( IString& i1, IString& i2 ),
         changeSkill( IString& i1, IString& i2, SkillCnrObj* cnrObj ),
         setSkillData();

      PageButtons
         pageButtons;

      PageCnrButtons
         pageCnrButtons;

      QueryRange
        *pSkillRange;

      IStaticText
         skillText,
         monthsExpText;

      IEntryField
         skill;

      INumericSpinButton
         monthsExp;

      IContainerControl
        *pCnr;

      SkillCnrObj
        *pSkillCnrObj;

      IContainerColumn
        *pColSkill,
        *pColExp;

      LSkillData
         skillData,
         origSkillData;

      IString
         Key;

      INotebook::PageSettings
         thePageSettings;

      bool
         isAquery;

      PageCnrSelHandler
         cnrSelHandler;
};
#endif
