/******************************************************************************
* .FILE:         linfonb.hpp                                                  *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Definition       *
*                                                                             *
* .CLASSES:      LInfoNotebook                                                *
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
#ifndef _LINFONB_
  #define _LINFONB_

#include <iwindow.hpp>
#include <inotebk.hpp>
#include <icmdhdr.hpp>
#include <ipagehdr.hpp>
#include <ihelp.hpp>
#include <ihelphdr.hpp>
#include "lpagectl.hpp"
#include "lacct.hpp"
#include "lbadge.hpp"
#include "lskill.hpp"
#include "lgenl.hpp"
#include "lstatus.hpp"
#include "lproject.hpp"
#include "ltask.hpp"
#include "ltimec.hpp"
#include "ldbqry.hpp"

class LMainCnr;

/******************************************************************************
* Class LInfoNotebook - Information notebook for a person or query            *
******************************************************************************/
class LInfoNotebook : public INotebook,
                      protected ICommandHandler,
                      protected IPageHandler
{
   public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in one of two ways:                                    |
| 1) Parent, owner, employee, and query flag.                                 |
| 2) Parent, owner, container, and query flag.          .                     |
-----------------------------------------------------------------------------*/
      LInfoNotebook( IWindow* parent,
                     IWindow* owner,
                     LEmployeeData& employee,
                     bool isQuery = true );

      LInfoNotebook( IWindow* parent,
                     IWindow* owner,
                     LMainCnr* cnr = NULL,
                     const IString queryName = NULL );

     ~LInfoNotebook();

/*------------------------ Database Functions ---------------------------------
| These functions are used to save data to the database:                      |
|   verifyPages         - Verify all notebook page data and save to database. |
-----------------------------------------------------------------------------*/
      bool
         verifyPages( IString queryName );

   protected:
/*----------------------------- Event Processing ------------------------------
| Handle and process events:                                                  |
|   command             - Process command events.                             |
|   select              - Process select events.                              |
-----------------------------------------------------------------------------*/
      bool
         command( ICommandEvent& event ),
         select (IPageSelectEvent& pageevt);

   private:

      LQueryData
         queryData;

      GeneralPage
         generalPage;

      AccountPage
         accountPage;

      BadgePage
         badgePage;

      SkillPage
         skillPage;

      StatusPage
         statusPage;

      ProjectPage
        *pProjectPage;

      TasksPage
        *pTasksPage;

      TimeCardPage
        *pTimeCardPage;

      QueryGenl
        *pQueryGenl;

      QueryAcct
        *pQueryAcct;

      QuerySkill
        *pQuerySkill;

      QueryBadge
        *pQueryBadge;

      QueryStatus
        *pQueryStatus;

      IPageHandle
         phTimeCardPage;

      LMainCnr
        *pCnr;
};
#endif
