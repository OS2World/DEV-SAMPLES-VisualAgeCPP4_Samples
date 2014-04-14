/******************************************************************************
* FILE NAME: linfonb.hpp                                                      *
*                                                                             *
* DESCRIPTION: Notebook with information pages for an employee or query       *
*                                                                             *
* Classes:                                                                    *
*   LInfoNotebook                                                             *
*                                                                             *
* COPYRIGHT:                                                                  *
*   Licensed Materials - Property of IBM                                      *
*   (C) Copyright IBM Corporation 1992, 1995                                  *
*   All Rights Reserved                                                       *
*   US Government Users Restricted Rights - Use, duplication, or disclosure   *
*   restricted by GSA ADP Schedule Contract with IBM Corp.                    *
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
                     Boolean isQuery = true );

      LInfoNotebook( IWindow* parent,
                     IWindow* owner,
                     LMainCnr* cnr = NULL,
                     const IString queryName = NULL );

     ~LInfoNotebook();

/*------------------------ Database Functions ---------------------------------
| These functions are used to save data to the database:                      |
|   verifyPages         - Verify all notebook page data and save to database. |
-----------------------------------------------------------------------------*/
      Boolean
         verifyPages( IString queryName );

   protected:
/*----------------------------- Event Processing ------------------------------
| Handle and process events:                                                  |
|   command             - Process command events.                             |
|   select              - Process select events.                              |
-----------------------------------------------------------------------------*/
      Boolean
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
