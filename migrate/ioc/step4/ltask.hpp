/*******************************************************************************
* FILE NAME: ltask.hpp                                                         *
*                                                                              *
* DESCRIPTION:                                                                 *
*                                                                              *
* Classes                                                                      *
*   TaskPage                                                                   *
*   TaskCnrObj                                                                 *
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
#ifndef _LTASK_
#define _LTASK_

#include <imcelcv.hpp>
#include <icnrctl.hpp>
#include <icnrcol.hpp>
#include <istring.hpp>
#include <icombobx.hpp>
#include <ientryfd.hpp>
#include <icmdhdr.hpp>
#include <icheckbx.hpp>
#include <imsgbox.hpp>
#include <ipoint.hpp>
#include <inotebk.hpp>
#include <iapp.hpp>

#include "ldbase.hpp"
#include "lproject.hpp"
#include "lpagectl.hpp"


/******************************************************************************
* Class TaskCnrObj - Task container object.                                   *
******************************************************************************/
class TaskCnrObj : public IContainerObject
{
   public: 
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object given a task, description, and billable flag.          |
-----------------------------------------------------------------------------*/
      TaskCnrObj( const IString& stTask,
                  const IString& stDesc,
                  const IString& stBill );

     ~TaskCnrObj();

/*------------------------------- Accessors -----------------------------------
| These functions provide a means of getting and setting the accessible        |
| attributes of instances of this class:                                       |
|   task                - Returns the task.                                    |
|   desc                - Returns the description.                             |
|   bill                - Returns the billable status.                         |
|   setTask             - Sets the task.                                       |
|   setDesc             - Sets the description.                                |
|   setBill             - Sets the billable status.                            |
|   taskOffset          - Returns the container offset for the task.           |
|   descOffset          - Returns the container offset for the description.    |
|   billOffset          - Returns the container offset for the billable status.|
-----------------------------------------------------------------------------*/
      inline IString
         task() const { return Task; };
      inline IString
         desc() const { return Desc; };
      inline IString
         bill() const { return Bill; };

      inline TaskCnrObj
         &setTask( const IString& ta ) { Task=ta; return *this; };
      inline TaskCnrObj
         &setDesc( const IString& de ) { Desc=de; return *this; };
      inline TaskCnrObj
         &setBill( const IString& bi ) { Bill=bi; return *this; };

      inline unsigned long
         taskOffset() { return offsetof( TaskCnrObj, Task ); };
      inline unsigned long
         descOffset() { return offsetof( TaskCnrObj, Desc ); };
      inline unsigned long
         billOffset() { return offsetof( TaskCnrObj, Bill ); };

   private: 

      IString
         Task,          
         Desc,
         Bill;
};


/******************************************************************************
* Class TasksPage - Task page.                                                *
******************************************************************************/
class TasksPage : public IMultiCellCanvas,
                  public ICommandHandler,
                  public ISelectHandler
{
   public:
      friend class TimeCard;

/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in only one way:                                       |
| 1) IWindow*, IString.                                                       |
-----------------------------------------------------------------------------*/
      TasksPage( IWindow* pParent,
                 const IString& theKey = NULL );

     ~TasksPage();

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
|   getTaskData         - Return the task data.                               |
|   setTaskData         - Set the task data.                                  |
-----------------------------------------------------------------------------*/
      inline INotebook::PageSettings
         pageSettings() { return thePageSettings; };

      inline IString
         &key() { return Key; };

      inline LTaskData
        &getTaskData() { return taskData; };

      Boolean
         setTasksData();  

/*----------------------------- Page Manipulation -----------------------------
| These functions provide a means of manipulating the instances of this class:|
|   fillEntryfields     - Fill the entryfields for the given container object.|
-----------------------------------------------------------------------------*/
      TasksPage&
         fillEntryfields( TaskCnrObj* cnrObject );


   protected: 

/*----------------------------- Event Processing ------------------------------
| Handle and process events:                                                  |
|   command             - Process command events.                             |
|   handleIt            - Start handling events.                              |
-----------------------------------------------------------------------------*/
      Boolean
         command( ICommandEvent& event );

      TasksPage
        &handleIt();

   private: 

      TasksPage
        &setCells(),
        &fillCnr();

      Boolean
         addTask( IString& i1, IString& i2, IString& i3 ),
         changeTask( IString& i1, IString& i2, IString& i3, TaskCnrObj* cnrObj );

      TasksPage
         &unMark();

      PageButtons
         pageButtons;

      PageCnrButtons
         pageCnrButtons;

      IStaticText
         taskText,
         billableText,
         descrText;
//  currentTasksText,
//  descr2Text,
//  billable2Text;

      IEntryField
         task;

      ICheckBox
         billable;

      IEntryField
         descr;

      IContainerControl
        *pCnr;            

      TaskCnrObj
        *pTaskCnrObj;     

      IContainerColumn
        *pColTask;        

      IContainerColumn
        *pColDesc,        
        *pColBill;

      LTaskData
         taskData,
         origTaskData;

      IString
         Key;             

      INotebook::PageSettings
         thePageSettings;

      PageCnrSelHandler
         cnrSelHandler;
};
#endif
