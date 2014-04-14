/*******************************************************************************
* FILE NAME: lentry.hpp                                                        *
*                                                                              *
* DESCRIPTION:                                                                 *
*                                                                              *
* Class                                                                        *
*   Entry                                                                      *
*                                                                              *
* COPYRIGHT:                                                                   *
*   Licensed Materials - Property of IBM                                       *
*   (C) Copyright IBM Corporation 1992, 1995                                   *
*   All Rights Reserved                                                        *
*   US Government Users Restricted Rights - Use, duplication, or disclosure    *
*   restricted by GSA ADP Schedule Contract with IBM Corp.                     *
*                                                                              *
* CHANGE HISTORY:                                                              *
*******************************************************************************/
#ifndef _LENTRY_
#define _LENTRY_

#include <iostream.h>
                                // Definition of Boolean:
#include <istring.hpp>
#include <iglobals.h>

#include "lancelot.h"


//----------------------------------------------------------------------------
// class Entry
//----------------------------------------------------------------------------
class Entry : public IBase {

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


inline Boolean operator== (Entry const& aTS) const  {
                            return txt==aTS.txt;
                           };

inline Boolean operator== (const char* acp) const  {
        return txt==acp;
       };

inline Boolean operator!= (Entry const& aTS) const  {
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
