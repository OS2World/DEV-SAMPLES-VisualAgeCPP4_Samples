/******************************************************************************
* .FILE:         lentry.hpp                                                   *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Definition       *
*                                                                             *
* .CLASSES:      Entry                                                        *
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
#ifndef _LENTRY_
#define _LENTRY_

#include <iostream.h>
                                // Definition of bool:
#include <istring.hpp>
#include <iglobals.h>

#include "lancelot.h"


//----------------------------------------------------------------------------
// class Entry
//----------------------------------------------------------------------------
class Entry
{

public: // ---------------------- PUBLIC -------------------------------------

  Entry (char *atxt)  { init(atxt); };
  ~Entry () { };

     // another Entry copy
inline  Entry (Entry const& aTS)  { init(aTS.txt); };

inline  Entry& operator= (Entry const& aTS)  {
        if (& aTS != this)  {
           // deInit();
           init(aTS.txt);
        }
        return *this;
        };


inline bool operator== (Entry const& aTS) const  {
                            return txt==aTS.txt;
                           };

inline bool operator== (const char* acp) const  {
        return txt==acp;
       };

inline bool operator!= (Entry const& aTS) const  {
        return strcmp(txt, aTS.txt) != 0;
     };

inline IString text() const {return txt;};

friend ostream& operator<< (ostream& os, Entry const& aTS) {
        return os << aTS.txt;
     };

protected: // ---------------------- PROTECTED ----------------------------------

inline Entry& init (char* const& atxt)  {
       txt = atxt;
       return *this;
    };


private: // ---------------------- PRIVATE ----------------------------------

IString
  txt;


};
#endif
