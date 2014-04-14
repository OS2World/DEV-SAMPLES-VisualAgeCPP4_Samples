/*******************************************************************************
* FILE NAME: ldbqry.hpp                                                        *
*                                                                              *
* DESCRIPTION:                                                                 *
*                                                                              *
* Class                                                                        *
*   QueryEmpl                                                                  *
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
class QueryEmpl : public IBase
{
public: // ---------------------- PUBLIC -------------------------------------


//----------------------- Contructor/Destructor ------------------------------
// Class QueryEmpl :: QueryEmpl()
//----------------------------------------------------------------------------
  QueryEmpl();
  ~QueryEmpl();

inline Boolean
  getNextId(){ itemsCur.setToNext();
               return itemsCur.isValid();};

inline Boolean setFirstId(){ itemsCur.setToFirst();
                             return itemsCur.isValid();};
QueryEmpl&
  deleteCurrentId();

Boolean
  getId(  IString& i1);

Boolean
  putId(   const IString& i1);

Boolean
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
class QueryInfo : public IBase
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

Boolean
  isDBempty();

Boolean
  getMatchId(IString& field);

inline Boolean
  getNextMatchId(){ matchCur.setToNext();
                    return matchCur.isValid();}

inline Boolean
  setFirstMatchId(){ matchCur.setToFirst();
                     return matchCur.isValid();}

inline INumber
  numberOfMatches(){ return matchIds.numberOfElements();};

inline Boolean
  isValid(){ return matchCur.isValid();}

QueryInfo&
  emptyBagMatchIds();

QueryInfo&
  addMatchId(const IString& anId);

Boolean
  getSearchItem( IString& field,
                 IString& data);

Boolean
  getSearchItem( IString& field,
                 IString& data,
                 IString& range);

QueryInfo&
  addSearchItem(const IString& field,
                const IString& data,
                const IString& range="");


inline
  Boolean getNextSearchItem(){ searchCur.setToNext();
                               return searchCur.isValid();
                              };

inline
  Boolean setFirstSearchItem(){ searchCur.setToFirst();
                                return searchCur.isValid();
                              };
QueryInfo&
  emptyBagSearchItems();

Boolean
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

Boolean
  compareIt( const ADate* d1,
             const ADate* d2,
             const IString& range) ;

Boolean
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

Boolean
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

Boolean
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

Boolean
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

Boolean
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

Boolean
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

Boolean
  aMatch( LStatusData* ac
         ,const IString& key
         ,const IString& value
         ,const IString& range="") ;



};


//----------------------------------------------------------------------------
// class QueryQry
//----------------------------------------------------------------------------
class QueryQry :public IBase
{
public: // ---------------------- PUBLIC -------------------------------------


//----------------------------------------------------------------------------
// class QueryQry
//----------------------------------------------------------------------------
    QueryQry();
    ~QueryQry();

inline Boolean
    setNextId(){ itemsCur.setToNext();
                 return itemsCur.isValid();};

inline Boolean
    setFirstId(){ itemsCur.setToFirst();
                   return itemsCur.isValid();};

inline Boolean
    isValid(){ return itemsCur.isValid();};

Boolean
    setLastId();

IString
    getQry() ;

Boolean
    putQry(  const IString& i1) ;

Boolean
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
class QueryIntersection : public Items,
                          public IBase
{
public: // ---------------------- PUBLIC -------------------------------------

    QueryIntersection( QueryGenl*   qg
                      ,QuerySkill*  qs
                      ,QueryAcct*   qa
                      ,QueryStatus* qst
                      ,QueryBadge*  qb);

    ~QueryIntersection();

inline Boolean
    setNextId(){ itemsCur.setToNext();
                 return itemsCur.isValid();};

inline Boolean
    setFirstId(){ itemsCur.setToFirst();
                  return itemsCur.isValid();};

inline Boolean
    isValid(){ return itemsCur.isValid();};

inline Boolean
    isIntersectionEmpty() { return !items.numberOfElements();};

IString
    getId() ;

Boolean
    putId(  const IString& i1) ;

Boolean
    emptyBagIntersection();

private:

      getQryIds();

ItemsBag
    items;

ItemsBag::Cursor
    itemsCur;

};


#endif
