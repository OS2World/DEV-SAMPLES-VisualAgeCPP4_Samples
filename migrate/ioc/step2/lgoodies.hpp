/******************************************************************************
* FILE NAME: lgoodies.hpp                                                     *
*                                                                             *
* DESCRIPTION: Assortment of goody classes                                    *
*                                                                             *
* Classes:                                                                    *
*   LAskUser                                                                  *
*   LAskUserCommandHandler                                                    *
*                                                                             *
* COPYRIGHT:                                                                  *
*   Licensed Materials - Property of IBM                                      *
*   (C) Copyright IBM Corporation 1992, 1995                                  *
*   All Rights Reserved                                                       *
*   US Government Users Restricted Rights - Use, duplication, or disclosure   *
*   restricted by GSA ADP Schedule Contract with IBM Corp.                    *
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
      Boolean
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
      inline Boolean
         pressedOk() { return ok; };

      LAskUser
        &setOk( Boolean pressedOk = false ) { ok = pressedOk; return *this; };

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

      Boolean
         ok;
};


/******************************************************************************
* Class LFrameWindow - Frame window goody functions.                          *
******************************************************************************/
class LFrameWindow : public IBase
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
