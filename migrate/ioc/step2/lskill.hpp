/******************************************************************************
* FILE NAME: lskill.hpp                                                       *
*                                                                             *
* DESCRIPTION:                                                                *
*                                                                             *
* Class                                                                       *
*   SkillPage                                                                 *
*   SkillCnrObj                                                               *
*                                                                             *
* COPYRIGHT:                                                                  *
*   Licensed Materials - Property of IBM                                      *
*   (C) Copyright IBM Corporation 1992, 1995                                  *
*   All Rights Reserved                                                       *
*   US Government Users Restricted Rights - Use, duplication, or disclosure   *
*   restricted by GSA ADP Schedule Contract with IBM Corp.                    *
*                                                                             *
* CHANGE HISTORY:                                                             *
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
         skillOffset() { return offsetof(SkillCnrObj, skill); };
      inline unsigned long
         expOffset() { return offsetof(SkillCnrObj, exp); };

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
      Boolean
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
      Boolean
         command( ICommandEvent& event );

      SkillPage&
         handleIt();

   private:

      SkillPage
        &setCells(),
        &fillCnr(),
        &unMark();

      Boolean
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

      Boolean
         isAquery;

      PageCnrSelHandler
         cnrSelHandler;
};
#endif
