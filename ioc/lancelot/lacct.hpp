/******************************************************************************
* .FILE:         lacct.hpp                                                    *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Definition       *
*                                                                             *
* .CLASSES:      AccountPage                                                  *
*                AcctCnrObj                                                   *
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
#ifndef _LACCT_
#define _LACCT_

#include <icnrctl.hpp>
#include <icnrcol.hpp>
#include <imcelcv.hpp>
#include <ientryfd.hpp>
#include <icmdhdr.hpp>
#include <istring.hpp>
#include <istattxt.hpp>
#include <imsgbox.hpp>
#include <inotebk.hpp>
#include <iselhdr.hpp>

#include "ldbase.hpp"
#include "lpagectl.hpp"

/******************************************************************************
* Class AcctCnrObj - Account container object.                                *
******************************************************************************/
class AcctCnrObj : public IContainerObject
{
   public:

/*------------------------ Constructors/Destructor ----------------------------
| Construct the object given a user ID and node.                              |
-----------------------------------------------------------------------------*/
      AcctCnrObj( const IString& stCurrentUserId,
                  const IString& stNodeSystem );
      ~AcctCnrObj();

/*------------------------------- Accessors -----------------------------------
| These functions provide a means of getting and setting the accessible        |
| attributes of instances of this class:                                       |
|   getUserId           - Returns the user ID.                                 |
|   getNode             - Returns the node.                                    |
|   setUserId           - Sets the user ID.                                    |
|   setNode             - Sets the node.                                       |
|   currentUserIdOffset - Returns the container offset for the user ID.        |
|   nodeSysOffset       - Returns the container offset for the node/system.    |
-----------------------------------------------------------------------------*/
      inline IString
         getUserId() const { return ( currentUserId ); };
      inline IString
         getNode() const { return ( nodeSystem ); };

      inline AcctCnrObj
        &setUserId( const IString& uid ) { currentUserId=uid; return *this; };
      inline AcctCnrObj
        &setNode( const IString& node ) { nodeSystem=node; return *this; };

      inline unsigned long
         currentUserIdOffset() { return ICONTAINERCOLUMN_OFFSETOF( AcctCnrObj, currentUserId ); };
      inline unsigned long
         nodeSysOffset() { return ICONTAINERCOLUMN_OFFSETOF( AcctCnrObj, nodeSystem ); };

   private:

      IString
         currentUserId,
         nodeSystem;
};


/******************************************************************************
* Class AccountPage - Account page.                                           *
******************************************************************************/
class AccountPage : public IMultiCellCanvas,
                    public ICommandHandler,
                    public ISelectHandler
{
   public:
      friend class QueryAcct;

/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in one of two ways:                                    |
| 1) IWindow*, IString.                                                       |
| 2) IWindow*, LQueryData.                                                    |
-----------------------------------------------------------------------------*/
      AccountPage( IWindow* pParent,
                   const IString& theKey = NULL );
      AccountPage( IWindow* pParent,
                   LQueryData& qd );
      ~AccountPage();

/*------------------------ Database Functions ---------------------------------
| These functions are used to save data to the database:                      |
|   verifyAndSave       - Verify the page data and save to the database.      |
-----------------------------------------------------------------------------*/
      bool
         verifyAndSave( IString& pString,
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
         &key() { return Key; };

/*----------------------------- Page Manipulation -----------------------------
| These functions provide a means of manipulating the instances of this class:|
|   fillEntryfields     - Fill the entryfields for the given container object.|
-----------------------------------------------------------------------------*/
      AccountPage&
         fillEntryfields( AcctCnrObj* cnrObject );


   protected:

/*----------------------------- Event Processing ------------------------------
| Handle and process events:                                                  |
|   command             - Process command events.                             |
|   handleIt            - Start handling events.                              |
-----------------------------------------------------------------------------*/
      bool
         command( ICommandEvent& event );

      AccountPage
         &handleIt();

   private:

      AccountPage
         &setCells(),
         &fillCnr(),
         &unMark();

      bool
         addAcct( IString& userId, IString& node ),
         changeAcct( IString& userId, IString& node, AcctCnrObj* pCnrObj ),
         setAcctData();

      PageButtons
         pageButtons;

      PageCnrButtons
         pageCnrButtons;

      IStaticText
         userIdText,
         nodeSysText;

      IEntryField
         userId,
         nodeSys;

      IContainerControl
        *pCnr;

      AcctCnrObj
        *pAcctCnrObj;

      IContainerColumn
        *pColUserID,
        *pColNodeSys;

      LAcctData
         acctData,
         origAcctData;

      IString
         Key;

      bool
         isAquery;

      INotebook::PageSettings
         thePageSettings;

      PageCnrSelHandler
         cnrSelHandler;

};
#endif
