/******************************************************************************
* FILE NAME: linfowin.hpp                                                     *
*                                                                             *
* DESCRIPTION: Frame window with a notebook of information pages              *
*                                                                             *
* Class                                                                       *
*   LInfoWindow                                                               *
*                                                                             *
* COPYRIGHT:                                                                  *
*   Licensed Materials - Property of IBM                                      *
*   (C) Copyright IBM Corporation 1992, 1995                                  *
*   All Rights Reserved                                                       *
*   US Government Users Restricted Rights - Use, duplication, or disclosure   *
*   restricted by GSA ADP Schedule Contract with IBM Corp.                    *
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
                   Boolean isQuery = true );

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
      Boolean
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

      Boolean
         isAQuery;
};
#endif
