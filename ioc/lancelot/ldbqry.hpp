/******************************************************************************
* .FILE:         ldbqry.hpp                                                   *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Definition       *
*                                                                             *
* .CLASSES:      QueryEmpl                                                    *
*                QueryInfo                                                    *
*                ADate                                                        *
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
#ifndef _LDBQRY_
#define _LDBQRY_


#include <iostream.h>

#include <idate.hpp>
#include "litems.hpp"
#include "lacct.hpp"
#include "lskill.hpp"
#include "lbadge.hpp"
#include "lstatus.hpp"
#include "ldbase.hpp"
#include "ldbqry.hpp"
#include "lgenl.hpp"

#include <istring.hpp>

// forward reference
class GeneralPage;


class  ADate : public IDate
{
public:
    ADate(const IString theDate);
    ~ADate();

inline const IDate
  *date() {return pDate;};

ADate&
    setDate(const IString theDate);

private: // ---------------------- PRIVATE-------------------------------------

ADate&
    extractDate(const IString theDate);

IDate
  *pDate;

};


// ========================================================================================
// DB Query operations
// Obtains a list of unique ids in lempl.ini
// With an employee number an LEmployeeData object can be created
// ========================================================================================

//----------------------------------------------------------------------------
// class QueryEmpl
//----------------------------------------------------------------------------
class QueryEmpl
{
public: // ---------------------- PUBLIC -------------------------------------


//----------------------- Contructor/Destructor ------------------------------
// Class QueryEmpl :: QueryEmpl()
//----------------------------------------------------------------------------
  QueryEmpl();
  ~QueryEmpl();

inline bool
  getNextId(){ itemsCur.setToNext();
               return itemsCur.isValid();};

inline bool setFirstId(){ itemsCur.setToFirst();
                             return itemsCur.isValid();};
QueryEmpl&
  deleteCurrentId();

bool
  getId(  IString& i1);

bool
  putId(   const IString& i1);

bool
  emptyBagId();

private: //----------------------- PRIVATE ----------------------------------

  get();

Items
    items;

Items::Cursor
    itemsCur;

inline IString
  deptQuery() {return aDeptQuery;};

IString
    aDeptQuery;

};



//----------------------------------------------------------------------------
// class QueryInfo
//----------------------------------------------------------------------------
class QueryInfo
{
public: // ---------------------- PUBLIC -------------------------------------

friend class QueryGenl;
friend class QueryMgrs;
friend class QueryAcct;
friend class QuerySkill;
friend class QueryBadge;
friend class QueryStatus;
friend class QueryIntersection;

//----------------------- Contructor/Destructor ------------------------------
// Class QueryInfo :: QueryInfo()
//----------------------------------------------------------------------------
  QueryInfo(const char *);
  ~QueryInfo();

bool
  isDBempty();

bool
  getMatchId(IString& field);

inline bool
  getNextMatchId(){ matchCur.setToNext();
                    return matchCur.isValid();}

inline bool
  setFirstMatchId(){ matchCur.setToFirst();
                     return matchCur.isValid();}

inline INumber
  numberOfMatches(){ return matchIds.numberOfElements();};

inline bool
  isValid(){ return matchCur.isValid();}

QueryInfo&
  emptyBagMatchIds();

QueryInfo&
  addMatchId(const IString& anId);

bool
  getSearchItem( IString& field,
                 IString& data);

bool
  getSearchItem( IString& field,
                 IString& data,
                 IString& range);

QueryInfo&
  addSearchItem(const IString& field,
                const IString& data,
                const IString& range="");


inline
  bool getNextSearchItem(){ searchCur.setToNext();
                               return searchCur.isValid();
                              };

inline
  bool setFirstSearchItem(){ searchCur.setToFirst();
                                return searchCur.isValid();
                              };
QueryInfo&
  emptyBagSearchItems();

bool
  inRange(const IString &d1,
          const IString &d2,
          const IString &range);

QueryInfo&
  saveToQueryData(LQueryData *queryData,const IString& pageName);

inline
  unsigned numberOfMatchElements(){return searchItems.numberOfElements();};

IString
  chopOff( const IString& c2);

private: //----------------------- PRIVATE ----------------------------------

bool
  compareIt( const ADate* d1,
             const ADate* d2,
             const IString& range) ;

bool
  compareIt( const long   d1,
             const long   d2,
             const IString& range) ;

QueryEmpl
  idList;

ItemsBag
  matchIds;

Items
  searchItems; // items to match up (the Queries)

ItemsBag::Cursor
  matchCur;

Items::Cursor
  searchCur;

IString
  theDB;

} ;


//----------------------------------------------------------------------------
// class QueryGenl
//----------------------------------------------------------------------------
class QueryGenl : public QueryInfo
{
public: // ---------------------- PUBLIC -------------------------------------

enum EmplType {
                Regular,
                Manager,
                Supplemental,
                Unemployed};


//----------------------- Contructor/Destructor ------------------------------
// Class QueryGenl :: QueryGenl()
//----------------------------------------------------------------------------
    QueryGenl();
    ~QueryGenl();

QueryGenl&
    fillPage(GeneralPage & gp);

QueryGenl&
    getMatchList(GeneralPage &genlPage);

bool
    aMatch(const LEmployeeData* ed,
           const IString& key,
           const IString& value) ;
inline IString
  deptQuery() {return aDeptQuery;};

private: // ---------------------- PRIVATE-------------------------------------

IString
    aDeptQuery;


};

//----------------------------------------------------------------------------
// class QueryMgrs - query manager
//----------------------------------------------------------------------------
class QueryMgrs  : public QueryInfo
{
public: // ---------------------- PUBLIC -------------------------------------

enum EmplType {
                Regular,
                Manager,
                Supplemental,
                Unemployed};


//----------------------- Contructor/Destructor ------------------------------
// Class QueryMgrs  :: QueryMgr()
//----------------------------------------------------------------------------
    QueryMgrs();
    ~QueryMgrs();

// QueryGenl&
//    fillPage(GeneralPage & gp);

QueryMgrs&
    getMatchList();

bool
    aMatch(const LEmployeeData* ed,
           const IString& key,
           const IString& value) ;


};


//----------------------------------------------------------------------------
// class AcctPage
//----------------------------------------------------------------------------
class QueryAcct : public QueryInfo
{
public: // ---------------------- PUBLIC -------------------------------------

//----------------------- Contructor/Destructor ------------------------------
// Class QueryAcct :: QueryAcct()
//----------------------------------------------------------------------------
  QueryAcct();
  ~QueryAcct();

QueryAcct&
  fillPage(AccountPage & ac);

QueryAcct&
  getMatchList(AccountPage &acctPage);

bool
  aMatch( LAcctData* ac,
          const IString& key,
          const IString& value) ;


};


//----------------------------------------------------------------------------
// class QuerySkill
//----------------------------------------------------------------------------
class QuerySkill: public QueryInfo
{
public: // ---------------------- PUBLIC -------------------------------------

//----------------------------------------------------------------------------
// class QuerySkill
//----------------------------------------------------------------------------
  QuerySkill();
  ~QuerySkill();

QuerySkill&
  fillPage(SkillPage & sk);

QuerySkill&
  getMatchList(SkillPage &skillPage);

bool
  aMatch( LSkillData* ac
         ,const IString& key
         ,const IString& value
         ,const IString& range="") ;

};


//----------------------------------------------------------------------------
// class QueryBadge
//----------------------------------------------------------------------------
class QueryBadge: public QueryInfo
{
public: // ---------------------- PUBLIC -------------------------------------

//----------------------------------------------------------------------------
// class QueryBadge
//----------------------------------------------------------------------------
  QueryBadge();
  ~QueryBadge();

QueryBadge&
  fillPage(BadgePage & bd);

QueryBadge&
  getMatchList(BadgePage &badgePage);

bool
  aMatch( LBadgeData* ac
         ,const IString& key
         ,const IString& value
         ,const IString& range="") ;


};


//----------------------------------------------------------------------------
// class QueryStatus
//----------------------------------------------------------------------------
 class QueryStatus : public QueryInfo
 {
//----------------------------------------------------------------------------
// class QueryStatus
//----------------------------------------------------------------------------

public: // ---------------------- PUBLIC -------------------------------------

  QueryStatus();
  ~QueryStatus();

QueryStatus&
  fillPage(StatusPage & bd);

QueryStatus&
  getMatchList(StatusPage &statusPage);

bool
  aMatch( LStatusData* ac
         ,const IString& key
         ,const IString& value
         ,const IString& range="") ;



};


//----------------------------------------------------------------------------
// class QueryQry
//----------------------------------------------------------------------------
class QueryQry
{
public: // ---------------------- PUBLIC -------------------------------------


//----------------------------------------------------------------------------
// class QueryQry
//----------------------------------------------------------------------------
    QueryQry();
    ~QueryQry();

inline bool
    setNextId(){ itemsCur.setToNext();
                 return itemsCur.isValid();};

inline bool
    setFirstId(){ itemsCur.setToFirst();
                   return itemsCur.isValid();};

inline bool
    isValid(){ return itemsCur.isValid();};

bool
    setLastId();

IString
    getQry() ;

bool
    putQry(  const IString& i1) ;

bool
    emptyBagQry();

private:

   getQryNames();

Items
    items;

Items::Cursor
    itemsCur;

};

//----------------------------------------------------------------------------
// class QueryIntersection
//----------------------------------------------------------------------------
class QueryIntersection : public Items
{
public: // ---------------------- PUBLIC -------------------------------------

    QueryIntersection( QueryGenl*   qg
                      ,QuerySkill*  qs
                      ,QueryAcct*   qa
                      ,QueryStatus* qst
                      ,QueryBadge*  qb);

    ~QueryIntersection();

inline bool
    setNextId(){ itemsCur.setToNext();
                 return itemsCur.isValid();};

inline bool
    setFirstId(){ itemsCur.setToFirst();
                  return itemsCur.isValid();};

inline bool
    isValid(){ return itemsCur.isValid();};

inline bool
    isIntersectionEmpty() { return !items.numberOfElements();};

IString
    getId() ;

bool
    putId(  const IString& i1) ;

bool
    emptyBagIntersection();

private:

      getQryIds();

ItemsBag
    items;

ItemsBag::Cursor
    itemsCur;

};


#endif
