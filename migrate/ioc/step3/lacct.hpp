/******************************************************************************
* FILE NAME: lacct.hpp                                                        *
*                                                                             *
* DESCRIPTION:                                                                *
*                                                                             *
* Classes                                                                     *
*   AcctPage                                                                  *
*   AcctCnrObj                                                                *
*                                                                             *
* COPYRIGHT:                                                                  *
*   Licensed Materials - Property of IBM                                      *
*   (C) Copyright IBM Corporation 1992, 1995                                  *
*   All Rights Reserved                                                       *
*   US Government Users Restricted Rights - Use, duplication, or disclosure   *
*   restricted by GSA ADP Schedule Contract with IBM Corp.                    *
*                                                                             *
* CHANGE HISTORY:                                                             *
*******************************************************************************/
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
         currentUserIdOffset() { return offsetof( AcctCnrObj, currentUserId ); };
      inline unsigned long
         nodeSysOffset() { return offsetof( AcctCnrObj, nodeSystem ); };

   private:

      IString
         currentUserId,  
         nodeSystem;        
};


/******************************************************************************
* Class AccountPage - Account page.                                           *
******************************************************************************/
class AccountPage : public IMultiCellCanvas,
                    public ICommandHandler
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
      Boolean
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
      Boolean
         command( ICommandEvent& event );

      AccountPage
         &handleIt();

   private:

      AccountPage
         &setCells(),
         &fillCnr(),
         &unMark();

      Boolean
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

      Boolean
         isAquery;

      INotebook::PageSettings
         thePageSettings;

      PageCnrSelHandler
         cnrSelHandler;

};
#endif
