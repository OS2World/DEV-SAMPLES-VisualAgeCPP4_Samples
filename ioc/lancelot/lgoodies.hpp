/******************************************************************************
* .FILE:         lgoodies.hpp                                                 *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Definition       *
*                                                                             *
* .CLASSES:      LAskUser                                                     *
*                LAskUserCommandHandler                                       *
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
#ifndef _LGOODIES_
  #define _LGOODIES_

#include <iframe.hpp>
#include <ititle.hpp>
#include <imcelcv.hpp>
#include <isetcv.hpp>
#include <istattxt.hpp>
#include <ientryfd.hpp>
#include <ipushbut.hpp>
#include <icmdhdr.hpp>
#include <istring.hpp>

class LAskUser;

/******************************************************************************
* Class LAskUserCommandHandler - Command handler for LAskUser window          *
******************************************************************************/
class LAskUserCommandHandler : public ICommandHandler
{
   public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in only one way:                                       |
| 1) Owner window                                                             |
-----------------------------------------------------------------------------*/
      LAskUserCommandHandler( LAskUser* owner );

     ~LAskUserCommandHandler();


   protected:
/*----------------------------- Event Processing ------------------------------
| Handle and process events:                                                  |
|   command             - Process command events.                             |
-----------------------------------------------------------------------------*/
      bool
         command( ICommandEvent& event );

   private:
      LAskUser
        *theOwner;
};


/******************************************************************************
* Class LAskUser - Standard looking dialog but with an entryfield for user    *
*   input.                                                                    *
******************************************************************************/
class LAskUser : public IFrameWindow
{
   public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in only one way:                                       |
| 1) ResourceId, parent, owner, text1, text2, text3, text4.                   |
-----------------------------------------------------------------------------*/
      LAskUser( unsigned long id, IWindow* parent, IWindow* owner,
                const IString& askText,
                const IString& askText2 = "",
                const IString& askText3 = "",
                const IString& askText4 = "" );

     ~LAskUser();

/*------------------------------- Accessors -----------------------------------
| These functions provide a means of getting and setting the accessible        |
| attributes of instances of this class:                                       |
|   pressedOk           - Returns true if the OK button was pressed by the     |
|                         user.                                                |
|   setOk               - Manually set the pressed OK flag.                    |
|   text                - Returns the user entered text from the entryfield.   |
-----------------------------------------------------------------------------*/
      inline bool
         pressedOk() { return ok; };

      LAskUser
        &setOk( bool pressedOk = false ) { ok = pressedOk; return *this; };

      inline IString
         text() { return entry.text(); };


   private:
      ITitle
         title;

      IMultiCellCanvas
         canvas;

      ISetCanvas
         bCanvas;

      IStaticText
         staticText1,
         staticText2,
         staticText3,
         staticText4;

      IEntryField
         entry;

      IPushButton
         okButton,
         cancelButton;

      LAskUserCommandHandler
         cmdHdr;

      bool
         ok;
};


/******************************************************************************
* Class LFrameWindow - Frame window goody functions.                          *
******************************************************************************/
class LFrameWindow
{
   public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in only one way:                                       |
| 1) No parameters.                                                           |
-----------------------------------------------------------------------------*/
      LFrameWindow();

     ~LFrameWindow();

/*------------------------------- Accessors -----------------------------------
| These functions provide a means of getting and setting the accessible        |
| attributes of instances of this class:                                       |
|   bestFit             - If the frame window is clipped off the screen,       |
|                         return a new position that avoids clipping.          |
-----------------------------------------------------------------------------*/
      static IPoint
         bestFit( IFrameWindow* frameWin );
};
#endif
