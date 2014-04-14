/*******************************************************************************
* FILE NAME: lproject.hpp                                                      *
*                                                                              *
* DESCRIPTION:                                                                 *
*                                                                              *
* Classes                                                                      *
*   ProjectPage                                                                *
*   ProjCnrObj                                                                 *
*                                                                              *
* COPYRIGHT:                                                                   *
*   Licensed Materials - Property of IBM                                       *
*   (C) Copyright IBM Corporation 1992, 1995                                   *
*   All Rights Reserved                                                        *
*   US Government Users Restricted Rights - Use, duplication, or disclosure    *
*   restricted by GSA ADP Schedule Contract with IBM Corp.                     *
*                                                                              *
* CHANGE HISTORY:                                                              *
*******************************************************************************/
#ifndef _LPROJECT_
#define _LPROJECT_

#include <imcelcv.hpp>
#include <icnrctl.hpp>
#include <icnrcol.hpp>
#include <icmdhdr.hpp>
#include <imsgbox.hpp>
#include <ientryfd.hpp>
#include <istring.hpp>
#include <icombobx.hpp>
#include <icheckbx.hpp>
#include <inotebk.hpp>

#include "ldbase.hpp"
#include "ldbqry.hpp"
#include "lpagectl.hpp"


/******************************************************************************
* Class ProjCnrObj - Project container object.                                *
******************************************************************************/
class ProjCnrObj : public IContainerObject
{
   public: 
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object given a project, description, manager, and active flag.|
-----------------------------------------------------------------------------*/
      ProjCnrObj( const IString& stProj,
                  const IString& stDesc,
                  const IString& stMgr,
                  const IString& stAct="Yes");
     ~ProjCnrObj();

/*------------------------------- Accessors -----------------------------------
| These functions provide a means of getting and setting the accessible        |
| attributes of instances of this class:                                       |
|   proj                - Returns the project.                                 |
|   desc                - Returns the description.                             |
|   mgr                 - Returns the responsible manager.                     |
|   act                 - Returns the active flag status.                      |
|   setProj             - Sets the project.                                    |
|   setDesc             - Sets the description.                                |
|   setMgr              - Sets the responsible manager.                        |
|   setAct              - Sets the active flag status.                         |
|   projOffset          - Returns the container offset for the project.        |
|   descOffset          - Returns the container offset for the description.    |
|   mgrOffset           - Returns the container offset for the manager.        |
|   actOffset           - Returns the container offset for the active status.  |
-----------------------------------------------------------------------------*/
      inline IString
         proj() const { return Proj; };
      inline IString
         desc() const { return Desc; };
      inline IString
         mgr()  const { return Mgr;  };
      inline IString
         act()  const { return Act;  };

      inline ProjCnrObj
        &setProj( const IString& pr )  { Proj=pr; return *this; };
      inline ProjCnrObj
        &setDesc( const IString& de ) { Desc=de; return *this; };
      inline ProjCnrObj
        &setMgr( const IString& m )   { Mgr=m; return *this; };
      inline ProjCnrObj
        &setAct( const IString& a )   { Act=a; return *this; };

      inline unsigned long
         projOffset() { return offsetof( ProjCnrObj, Proj ); };
      inline unsigned long
         descOffset() { return offsetof( ProjCnrObj, Desc ); };
      inline unsigned long
         mgrOffset()  { return offsetof( ProjCnrObj, Mgr ); };
      inline unsigned long
         actOffset()  { return offsetof( ProjCnrObj, Act ); };

   private:

      IString
         Proj,
         Desc,
         Mgr,
         Act;
};


/******************************************************************************
* Class ProjectPage - Project page.                                           *
******************************************************************************/
class ProjectPage : public IMultiCellCanvas,
                    public ICommandHandler,
                    public ISelectHandler
{
   public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in only one way:                                       |
| 1) IWindow*, IString.                                                       |
-----------------------------------------------------------------------------*/
      ProjectPage( IWindow* pParent,
                   const IString& aKey );

     ~ProjectPage();

/*------------------------ Database Functions ---------------------------------
| These functions are used to save data to the database:                      |
|   verifyAndSave       - Verify the page data and save to the database.      |
-----------------------------------------------------------------------------*/
      Boolean
         verifyAndSave( IString& pString,
                        IString& theEntry,
                        const IString saveName = NULL );

/*------------------------------ Accessors ------------------------------------
| These functions provide a means of getting and setting the accessible       |
| attributes of instances of this class:                                      |
|   pageSettings        - Return the page settings for this page.             |
|   key                 - Return the key.                                     |
|   projData            - Return the project data.                            |
|   setProjectData      - Sets the project data.                              |
-----------------------------------------------------------------------------*/
      inline INotebook::PageSettings
         pageSettings() { return thePageSettings; };

      inline IString
         &key() { return Key; };

      inline LProjectData
        &projData() { return projectData; };

      Boolean
         setProjectData();

/*----------------------------- Page Manipulation -----------------------------
| These functions provide a means of manipulating the instances of this class:|
|   fillEntryfields     - Fill the entryfields for the given container object.|
|   fillPage            - Fill the combobox with managers from database.      |
-----------------------------------------------------------------------------*/
      ProjectPage&
         fillEntryfields( ProjCnrObj* cnrObject );

      ProjectPage
         &fillPage();


   protected:
/*----------------------------- Event Processing ------------------------------
| Handle and process events:                                                  |
|   command             - Process command events.                             |
|   handleIt            - Start handling events.                              |
-----------------------------------------------------------------------------*/
      Boolean
         command( ICommandEvent& event );

      ProjectPage
        &handleIt();

   private:

      ProjectPage
         &setCells(),
         &fillCnr();

      Boolean
         addProj( IString& i1, IString& i2, IString& i3, IString& i4 ),
         changeProj( IString& i1, IString& i2, IString& i3, IString& i4,
                     ProjCnrObj* cnrObj );

      ProjectPage
        &unMark();

      PageButtons
         pageButtons;

      PageCnrButtons
         pageCnrButtons;

      IStaticText
         projText,
         activeText,
         descrText,
         respMgrText;

      IEntryField
         project;

      ICheckBox
         active;

      IEntryField
         descr;

      IComboBox
         respMgr;

      IContainerControl
        *pCnr;        

      ProjCnrObj
        *pProjCnrObj; 

      IContainerColumn
         *pColProj,
         *pColDesc,
         *pColMgr, 
         *pColAct; 

      LProjectData
         projectData,
         origProjectData;

      IString
         Key;

      INotebook::PageSettings
         thePageSettings;

      PageCnrSelHandler
         cnrSelHandler;
};
#endif
