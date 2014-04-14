/******************************************************************************
* .FILE:         dmsamp3.hpp                                                  *
*                                                                             *
* .DESCRIPTION:  Direct Manipulation Sample Program 4: Class definitions      *
*                                                                             *
* .CLASSES:      Customer                                                     *
*                MyWindow                                                     *
*                MySourceWin                                                  *
*                MyTargetWin                                                  *
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
#include <iframe.hpp>
#include <ititle.hpp>
#include <icnr.hpp>
#include <idmhndlr.hpp>

#include "dmsamp3.h"

class MyWindow;


class Customer : public IContainerObject {
/*******************************************************************************
* Objects of this class are used to show direct manipulation support for       *
* containers.  Instances of this object are created to allow demonstrations    *
* of moves and copies of this object between intra-process containers.         *
*******************************************************************************/
public:
friend class IContainerColumn;
friend class MyWindow;

/*-------------------------- Constructors/Destructor ---------------------------
| Objects of this class are constructed by providing the following:            |
|   o A reference to a customer object (a copy constructor)                    |
|   o A IString for the icon text, an icon resource id, an IString for the     |
|     customer name, address, and phone number, and a pointer to a MyWindow    |
|     object                                                                   |
------------------------------------------------------------------------------*/
  Customer  ( const Customer &cnrobj );

  Customer  ( const IString  &iconText,
              unsigned long  iconID,
              const IString  &name,
              const IString  &address,
              const IString  &phone,
              MyWindow       *window );

  ~Customer ( ) {};

/*-------------------------------- Accessors -----------------------------------
| Instances of the Customer class have attributes that can be accessed by the  |
| following functions:                                                         |
|   name       - Returns the customer name                                     |
|   address    - Returns the customer address.                                 |
|   phone      - Returns the customer phone number.                            |
|   iconId     - Returns the custmoer's icon id.                               |
|   setName    - Sets the customer name.                                       |
|   setAddress - Sets the customer address.                                    |
|   setPhone   - Sets the customer phone number.                               |
------------------------------------------------------------------------------*/
  IString name    ( ) const  { return this->strName; }
  IString address ( ) const  { return this->strAddress; }
  IString phone   ( ) const  { return this->strPhone; }
  unsigned long iconId ( ) const { return this->ulIconId; }

  void setName    ( const IString &name )     { this->strName = name; }
  void setAddress ( const IString &address )  { this->strAddress = address; }
  void setPhone   ( const IString &phone )    { this->strPhone = phone; }

/*-------------------------------- Overrides -----------------------------------
| The following function overrides the objectCopy function defined in the      |
| base IContainerObject class:                                                 |
|  objectCopy - Called when it is necessary to make a copy of the Customer     |
|               object.  This is invoked when IContainerControl::copyObjectTo  |
|               is called.                                                     |
------------------------------------------------------------------------------*/
  IContainerObject* objectCopy( );

private:
  IString   strName,
            strAddress,
            strPhone;
  unsigned long ulIconId;
  MyWindow  *myWin;
};


class MyWindow : public IFrameWindow {
/*******************************************************************************
* This is the common base class for the demo source window class, MySourceWin, *
* and the demo target window class, MyTargetWin.                               *
*******************************************************************************/
friend class Customer;

public:
/*-------------------------- Constructor/Destructor ----------------------------
| Objects of this class are constructed by providing the following:            |
|   o A window ID                                                              |
------------------------------------------------------------------------------*/
  MyWindow  ( unsigned long windowId );
  ~MyWindow ( ) {};

protected:
  IContainerControl *cnrCtl;
  Customer          *car,
                    *space,
                    *bolt,
                    *starfleet;
  IResourceLibrary  reslib;
};


class MySourceWin : public MyWindow {
/*******************************************************************************
* This is the demo source window class.                                        *
*******************************************************************************/
public:
/*------------------------------ Constructor -----------------------------------
| Objects of this class are constructed by providing the following:            |
|   o A window ID                                                              |
------------------------------------------------------------------------------*/
  MySourceWin ( unsigned long windowId );
};

class MyTargetWin : public MyWindow {
/*******************************************************************************
* This is the demo source window class.                                        *
*******************************************************************************/
public:
/*------------------------------ Constructor -----------------------------------
| Objects of this class are constructed by providing the following:            |
|   o A window ID                                                              |
------------------------------------------------------------------------------*/
  MyTargetWin ( unsigned long windowId );
};

