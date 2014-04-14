/******************************************************************************
* .FILE:         linfowin.hpp                                                 *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Definition       *
*                                                                             *
* .CLASSES:      LInfoWindow                                                  *
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
#ifndef _LINFOWIN_
  #define _LINFOWIN_

#include <iframe.hpp>
#include <ititle.hpp>
#include <ipoint.hpp>
#include <icmdhdr.hpp>
#include <ihelp.hpp>
#include <ihelphdr.hpp>
#include "linfowin.hpp"
#include "linfonb.hpp"
#include "lcnrobj.hpp"

class LMainCnr;

/******************************************************************************
* Class LInfoWindow - LInfoWindow frame window                                *
******************************************************************************/
class LInfoWindow : public IFrameWindow,
                    protected ICommandHandler
{
   public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in one of two ways:                                    |
| 1) ResourceId, parent, owner, location, cnr object, employee, isQuery flag. |
| 2) ResourceId, parent, owner, location, cnr, cnr object, isQuery flag.      |
-----------------------------------------------------------------------------*/
      LInfoWindow( unsigned long id,
                   IWindow* parent,
                   IWindow* owner,
                   IPoint bottomLeft,
                   LCnrObject* object,
                   LEmployeeData& employee,
                   bool isQuery = true );

      LInfoWindow( unsigned long id,
                   IWindow* parent,
                   IWindow* owner,
                   IPoint bottomLeft,
                   LMainCnr* cnr,
                   LCnrObject* object,
                   IString queryName = NULL );
      virtual
        ~LInfoWindow();

    protected:
/*----------------------------- Event Processing ------------------------------
| Handle and process events:                                                  |
|   systemCommand       - Handle system command events like 'close'.          |
-----------------------------------------------------------------------------*/
      bool
         systemCommand( ICommandEvent& event );

   private:
      ITitle
         title;

      LInfoNotebook
         notebook;

      IHelpWindow
         help;

      LCnrObject
        *pObject;

      bool
         isAQuery;
};
#endif
