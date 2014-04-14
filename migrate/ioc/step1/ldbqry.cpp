/*******************************************************************************
* FILE NAME: ldbqry.cpp                                                        *
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

#ifndef _IBASE_                         //Make sure ibase.hpp is included
  #include <ibase.hpp>                  //  since that is where IC_<environ>
#endif                                  //  is defined.
#include <idate.hpp>
#include <istring.hpp>
#include "ldbqry.hpp"

// -------------------------------------------------------------------------
// ADate Class
// -------------------------------------------------------------------------
ADate :: ADate(const IString theDate)
{
   extractDate(theDate);
};

// -------------------------------------------------------------------------
// ADate Class destructor
// -------------------------------------------------------------------------
ADate :: ~ADate()
{

};

// -------------------------------------------------------------------------
// ADate Class setDate
// -------------------------------------------------------------------------
ADate& ADate :: setDate(const IString theDate)
{
   extractDate(theDate);
   return *this;
};

// -------------------------------------------------------------------------
// ADate Class extractDate
// -------------------------------------------------------------------------
ADate& ADate :: extractDate(const IString theDate)
{
   unsigned int ix, iy , yr , d1, d2 ;
   /// a valid date is passed in

   // assume mm dd yr

   if (theDate.subString(1,2).isDigits() ) {
      d1  = 4 ;
      ix = theDate.subString(1,2).asInt();
   }
   else {
      ix = theDate.subString(0,1).asInt();
      d1 = 3;
   }

   if (theDate.subString(d1,2).isDigits() ) {
      iy = theDate.subString(d1,2).asInt();
      d2 = 3 ;
   }
   else {
      iy = theDate.subString(d1,1).asInt();
      d2 = 2;

   }

   if (theDate.subString(d1+d2,2).isDigits() )
      yr = theDate.subString(d1+d2,2).asInt();
   else
      yr = theDate.subString(d1+d2,1).asInt();


   pDate = new IDate((Month)ix, iy, yr) ;
   return *this;

};

// -------------------------------------------------------------------------
// QueryEmpl Class
// -------------------------------------------------------------------------
QueryEmpl :: QueryEmpl ()
           : itemsCur(items)
{
   get(); // fill bag
};

// -------------------------------------------------------------------------
// QueryEmpl Class destructor
// -------------------------------------------------------------------------
QueryEmpl :: ~QueryEmpl()
{
  emptyBagId();
};


// -------------------------------------------------------------------------
// QueryEmpl Class get() - get the employee database
// -------------------------------------------------------------------------
QueryEmpl :: get ()
{
   IString     
      id;
   try
   {
      IProfile emplIni = IProfile("lempl.ini");

      IProfile::Cursor IniCursor(emplIni);
      for (IniCursor.setToFirst();
           IniCursor.isValid();
           IniCursor.setToNext() ) 
      {
         id = emplIni.applicationOrKeyAt(IniCursor);
         putId(id) ;
      }
   }
   catch(...)
   {}

   return true;
};


// -------------------------------------------------------------------------
// QueryEmpl Class getId() - get the employee number
// -------------------------------------------------------------------------
IBase :: Boolean QueryEmpl :: getId( IString& item1)
{

   if (false == itemsCur.isValid())
      return false;  // empty

   Entry name = itemsCur.element().item1();

   items.locateElementWithKey(name, itemsCur);

   item1 =  itemsCur.element().item1().text();

   return true;

}; //getId



// -------------------------------------------------------------------------
// QueryEmpl Class putId() - add an id to the list
// -------------------------------------------------------------------------
IBase :: Boolean QueryEmpl :: putId( const IString& item1)
{
   items.add(Item(item1));

   return true;

};    // putId


// -------------------------------------------------------------------------
// QueryEmpl Class emptyBagId() - empty the bag of ids
// -------------------------------------------------------------------------
IBase :: Boolean  QueryEmpl :: emptyBagId()  {
 items.removeAll();
 itemsCur.invalidate();
 return (true);
};


// -------------------------------------------------------------------------
// QueryEmpl Class deleteCurrentId()
// -------------------------------------------------------------------------
QueryEmpl& QueryEmpl ::  deleteCurrentId()
{
    if (itemsCur.isValid()) {
       items.removeAt(itemsCur);
    }
    return *this;
};

// -------------------------------------------------------------------------
// QueryInfo Class - QueryInfo
// -------------------------------------------------------------------------
QueryInfo :: QueryInfo(const char * iniFile)
             : idList(),                          // get the current employees
               matchCur(matchIds),
               searchCur(searchItems),
               theDB(iniFile)
{
   searchCur.invalidate();
   matchCur.invalidate();

};


// -------------------------------------------------------------------------
// QueryInfo Class :: ~QueryInfo -
// -------------------------------------------------------------------------
QueryInfo :: ~QueryInfo ()
{
 emptyBagSearchItems();
 emptyBagMatchIds();
 searchCur.invalidate();
 matchCur.invalidate();

};


// -------------------------------------------------------------------------
// QueryInfo Class :: isDbempty() - is the DB(ini) empty
// -------------------------------------------------------------------------
IBase :: Boolean QueryInfo :: isDBempty()
{
   Boolean  retCode;

   if (theDB.length() == 0)
      return true;

   IProfile *p = new IProfile(theDB);

   if (p->numberOfApplications() == 0)
        retCode = true;
   else
     retCode = false;

   delete p;
   return retCode;
};



// -------------------------------------------------------------------------
// QueryInfo Class :: getSearchItem() - get a item to search on, has a range
// -------------------------------------------------------------------------
IBase :: Boolean QueryInfo :: getSearchItem( IString& field
                                            , IString& data
                                            , IString& range)
{
   Boolean retCode=false;
   if (searchCur.isValid()) {
      retCode = true;

      field = searchCur.element().item1().text();
      data  = searchCur.element().item2().text();
      range = searchCur.element().item3().text();

   }
   else retCode = false;

   return retCode;

};

// -------------------------------------------------------------------------
// QueryInfo Class :: getSearchItem() - get a item to search on
// -------------------------------------------------------------------------
IBase :: Boolean QueryInfo :: getSearchItem( IString& field,
                                             IString& data)
{
   Boolean retCode=false;
   if (searchCur.isValid()) {
      retCode = true;

      field = searchCur.element().item1().text();
      data  = searchCur.element().item2().text();

   }
   else retCode = false;

   return retCode;

};


// -------------------------------------------------------------------------
// QueryInfo Class :: emptyBagSearchItems() empty the search items bag
// -------------------------------------------------------------------------
QueryInfo& QueryInfo ::emptyBagSearchItems()
{
   if (searchCur.isValid()) {
      searchItems.removeAll();
      searchCur.invalidate();
   }
   return *this;

};


// -------------------------------------------------------------------------
// QueryInfo Class :: addSearchItem() - add an item to search
// -------------------------------------------------------------------------

QueryInfo& QueryInfo ::addSearchItem(const IString& field
                              , const IString& data
                              , const IString& range)
{
  searchItems.add(Item(field, data, range ));
  return *this;
};


// -------------------------------------------------------------------------
// QueryInfo Class :: getMatchId() - get an id that matched the query
// -------------------------------------------------------------------------
IBase :: Boolean  QueryInfo :: getMatchId(IString& theID )
{

   Boolean retCode=false;
   if (matchCur.isValid()) {
      retCode = true;
      theID = matchCur.element().asString();
   }
   else retCode = false;

   return retCode;
};


// -------------------------------------------------------------------------
// QueryInfo Class :: emptyBagMatchIds() - initialize the bag of match ids
// -------------------------------------------------------------------------
QueryInfo& QueryInfo :: emptyBagMatchIds()
{
   if (matchCur.isValid()) {
      matchIds.removeAll();
      matchCur.invalidate();
   }
   return *this;
};


// -------------------------------------------------------------------------
// QueryInfo Class :: addMatchId() - add a match id
// -------------------------------------------------------------------------
QueryInfo& QueryInfo ::addMatchId(const IString& anId)
{
  matchIds.add(anId );
  return *this;
};



// -------------------------------------------------------------------------
// QueryInfo Class :: inRange() - match check having a range
// -------------------------------------------------------------------------
IBase :: Boolean QueryInfo :: inRange(const IString &c1
                                     ,const IString &c2
                                     ,const IString &range)
{

   if (c2.length() == 0)
      return false;

    IString matchItem, compareItem;

    matchItem   = chopOff(c1);
    compareItem = chopOff(c2);

   if ( (c1.isDigits()) && (c2.isDigits()) ) {
      // compare 2 numbers
      long d1=c1.asInt();
      long d2=c2.asInt();
      return compareIt(d1, d2, range);
   }
   else {
      ADate *date1 = new ADate(c1);
      ADate *date2 = new ADate(c2);
      return compareIt(date1, date2, range);
   } /* endif */

};


// -------------------------------------------------------------------------
// QueryInfo Class :: saveToQueryData() - save the search list to composite
//                                        list
// -------------------------------------------------------------------------
QueryInfo& QueryInfo :: saveToQueryData(LQueryData *queryData,const IString& pageName)
{
   // save to IProfile

   IString key, value, range, saveKey;
   short i = 1;
   for ( searchCur.setToFirst();
         searchCur.isValid();
         searchCur.setToNext()) {

         getSearchItem(key, value, range);

         // these are container objects
         if ((pageName == "SKILL ") |
             (pageName == "ACCOUNT ")) {

             saveKey = pageName + IString(i);
             queryData->putItem(saveKey, key, value, range);
             ++i;
         } /* endif */
         else
           if ((pageName == "STATUS ") ||
               (pageName == "BADGE "))   {

               saveKey = pageName + key;
               // for these pages date and range are saved in the bag
               if ((key == "saveDate") ||
                   (key == "endDate")  ||
                   (key == "issueDate")||
                   (key == "expireDate") ) {
                  queryData->putItem(saveKey, value );
                  queryData->putItem(saveKey+"Range", range );
               } else
                  queryData->putItem(saveKey, value );


           }
           else {
             saveKey = pageName + key;
             if (range.length() > 0  ) {
                saveKey = pageName + key + "Range";
                queryData->putItem(saveKey, range);
             }
             queryData->putItem(saveKey, value );
           }

   }
   return *this;
};


// -------------------------------------------------------------------------
// QueryInfo Class :: compareItData() - compare dates for a match
// -------------------------------------------------------------------------
IBase :: Boolean QueryInfo :: compareIt( const ADate* d1,
                                         const ADate* d2,
                                         const IString& range)
{
   Boolean retCode = false;
   // now compare the date or integer
   if (d1 == d2 )
       if (range.indexOfAnyOf("="))
          retCode=true;
       else
          retCode=false;
   else
     if (d2 > d1 )
       if (range.indexOfAnyOf(">"))
          retCode=true;
       else
          retCode=false;
     else
        if (d2 < d1 )
          if (range.indexOfAnyOf("<"))
             retCode=true;
          else
             retCode=false;

    return retCode;
};

// -------------------------------------------------------------------------
// QueryInfo Class :: compareItData() - compare integers for a match
// -------------------------------------------------------------------------
IBase :: Boolean QueryInfo :: compareIt( const long  d1
                                        ,const long  d2
                                        ,const IString& range)
{
   Boolean retCode = false;
   // now compare the date or integer
   if (d1 == d2 )
       if (range.indexOfAnyOf("="))
          retCode=true;
       else
          retCode=false;
   else
     if (d2 > d1 )
       if (range.indexOfAnyOf(">"))
          retCode=true;
       else
          retCode=false;
     else
        if (d2 < d1 )
          if (range.indexOfAnyOf("<"))
             retCode=true;
          else
             retCode=false;

    return retCode;
};


// -------------------------------------------------------------------------
// QueryInfo Class :: chopOff() - ignore decimal points
// -------------------------------------------------------------------------
IString QueryInfo :: chopOff( const IString& c2) {
   unsigned i = c2.indexOf(".");
   if (i > 0)
      return (c2.subString(1, i-1));
   return c2;

};



// -------------------------------------------------------------------------
// QueryGenl Class :: QueryGenl() - constuctor
// -------------------------------------------------------------------------
QueryGenl :: QueryGenl()
           : QueryInfo("lempl.ini"),
             aDeptQuery()
{ };


// -------------------------------------------------------------------------
// QueryGenl Class :: ~QueryGenl() - constuctor
// -------------------------------------------------------------------------
QueryGenl :: ~QueryGenl()
{ };

// -------------------------------------------------------------------------
// QueryGenl Class :: fillPage() - obtain page info and save as search items
// -------------------------------------------------------------------------
QueryGenl& QueryGenl :: fillPage(GeneralPage &genlPage)
{
// assume that setEmployeeData()
   emptyBagSearchItems();
   genlPage.setEmployeeData();
    emptyBagSearchItems();
    if (genlPage.employeeData.employeeNumber().length() > 0)
        addSearchItem( "employeeNum"
                       ,genlPage.employeeData.employeeNumber());
    if (genlPage.employeeData.lastName().length() > 0 )
        addSearchItem( "lastName"
                       ,genlPage.employeeData.lastName());

    if (genlPage.employeeData.firstName().length() > 0 )
        addSearchItem( "firstName"
                       ,genlPage.employeeData.firstName());

    if (genlPage.employeeData.middleInitial().length() > 0 )
        addSearchItem( "middleInitial"
                       ,genlPage.employeeData.middleInitial());

    if (genlPage.employeeData.internalPhone().length() > 0 )
        addSearchItem( "internalPhone"
                       ,genlPage.employeeData.internalPhone());

    if (genlPage.employeeData.externalPhone().length() > 0 )
        addSearchItem( "externalPhone"
                       ,genlPage.employeeData.externalPhone());

    if (genlPage.employeeData.room().length() > 0 )
        addSearchItem( "room"
                       ,genlPage.employeeData.room());

    if (genlPage.employeeData.building().length() > 0 )
        addSearchItem( "building"
                       ,genlPage.employeeData.building());

    if (genlPage.employeeData.department().length() > 0 ) {
        addSearchItem( "deptName"
                       ,genlPage.employeeData.department());
        if ( genlPage.employeeData.department().isAlphanumeric() )
           aDeptQuery = genlPage.employeeData.department();

    }

    if (genlPage.employeeData.division().length() > 0 )
        addSearchItem( "divName"
                       ,genlPage.employeeData.division());

    if (genlPage.employeeData.managerNumber().length() > 0 )
        addSearchItem( "internalPhone"
                       ,genlPage.employeeData.internalPhone());

    if (genlPage.employeeData.managerName().length() > 0 )
        addSearchItem( "managerName"
                       ,genlPage.employeeData.managerName());

    if (genlPage.employeeData.managerNumber().length() > 0 )
        addSearchItem( "managerNum"
                       ,genlPage.employeeData.managerNumber());


    QueryGenl :: EmplType emplType = (QueryGenl::EmplType)
                          genlPage.employeeData.employeeType();

    if ((QueryGenl :: Unemployed) != emplType )
        addSearchItem( "employeeType"
                       ,IString(emplType));

    return *this;
};


// -------------------------------------------------------------------------
// QueryGenl Class :: getMatchList() - get a list of ids that match
// -------------------------------------------------------------------------
QueryGenl& QueryGenl :: getMatchList(GeneralPage &genlPage)
{
  // for each id get employeeData and see if a match
  IString
    matchId,
    key,
    value;

  Boolean
    match = false;
  LEmployeeData
   *ed = NULL;

  //  no verification of valid input
  genlPage.setEmployeeData();
  //  get the stuff from general page
  fillPage(genlPage);
  emptyBagMatchIds();


  idList.setFirstId();
  while (idList.getId(matchId)) {
    ed = new LEmployeeData(matchId);

    // see if a match by looping thru searchList

    // must match up on all items
    // while ( done && getSearchItem(key, value)) {

    if (setFirstSearchItem())
       match = true;

    while (match && getSearchItem(key, value)) {
      match = aMatch(ed, key, value);
      getNextSearchItem();
    }

    // put this ID in the MatchList
    if  (match)
       addMatchId(matchId);

    idList.getNextId();
    delete ed;
  } /* endwhile */
  return *this;

};


// -------------------------------------------------------------------------
// QueryGenl Class :: aMatch() - checks for a match
// -------------------------------------------------------------------------
IBase :: Boolean  QueryGenl :: aMatch(const LEmployeeData* ed,
                                      const IString& key,
                                      const IString& value)
{
  if (key == "employeeNum" )
    if (ed->employeeNumber().length() > 0)
       return ed->employeeNumber().isLike(value);

  if (key == "lastName" )
    if (ed->lastName().length() > 0)
       return ed->lastName().isLike(value);

  if (key == "firstName" )
    if (ed->firstName().length() > 0)
       return ed->firstName().isLike(value);

  if (key == "middleInitial" )
    if (ed->middleInitial().length() > 0)
       return ed->middleInitial().isLike(value);

  if (key == "internalPhone" )
    if (ed->internalPhone().length() > 0)
       return ed->internalPhone().isLike(value);

  if (key == "externalPhone" )
    if (ed->externalPhone().length() > 0)
       return ed->externalPhone().isLike(value);

  if (key == "room" )
    if (ed->room().length() > 0)
       return ed->room().isLike(value);

  if (key == "building" )
    if (ed->building().length() > 0)
       return ed->building().isLike(value);

  if (key == "deptName" )
    if (ed->department().length() > 0)
       return ed->department().isLike(value);

  if (key == "divName" )
    if (ed->division().length() > 0)
       return ed->division().isLike(value);

  if (key == "managerName" )
    if (ed->managerName().length() > 0)
       return ed->managerName().isLike(value);

  if (key == "managerNum" )
    if (ed->managerNumber().length() > 0)
       return ed->managerNumber().isLike(value);

  if (key == "employeeType" )
     return value.isLike(IString(ed->employeeType()) );

  return false;
};

// -------------------------------------------------------------------------
// QueryMgr Class :: QueryMgr() - constuctor
// -------------------------------------------------------------------------
QueryMgrs :: QueryMgrs()
           : QueryInfo("lempl.ini")
{
   emptyBagSearchItems();
   addSearchItem( "employeeType" ,IString(QueryMgrs:: Manager));
};


// -------------------------------------------------------------------------
// QueryMgrs Class :: ~QueryMgrs() - constuctor
//                                 Obtain a list of managers
// -------------------------------------------------------------------------
QueryMgrs :: ~QueryMgrs()
{ };

// -------------------------------------------------------------------------
// QueryMgrs Class :: fillPage() - obtain page info and save as search items
// -------------------------------------------------------------------------
/*
QueryMgrs& QueryMgrs :: fillPage(GeneralPage &genlPage)
{
   emptyBagSearchItems();

   addSearchItem( "employeeType" ,IString(QueryMgr:: Manager));

    return *this;
};
*/

// -------------------------------------------------------------------------
// QueryMgrs Class :: getMatchList() - get a list of ids that match
// -------------------------------------------------------------------------
QueryMgrs& QueryMgrs :: getMatchList()
{
  // for each id get employeeData and see if a match
  IString
    matchId,
    key,
    value;

  Boolean
    match = false;
  LEmployeeData
   *ed = NULL;

  emptyBagMatchIds();

  idList.setFirstId();
  while (idList.getId(matchId)) {
    ed = new LEmployeeData(matchId);

    // see if a match by looping thru searchList

    // must match up on all items
    // while ( done && getSearchItem(key, value)) {

    if (setFirstSearchItem())
       match = true;

    while (match && getSearchItem(key, value)) {
      match = aMatch(ed, key, value);
      getNextSearchItem();
    }

    // put this ID in the MatchList
    if  (match)
       addMatchId(matchId);

    idList.getNextId();
    delete ed;
  } /* endwhile */
  return *this;

};


// -------------------------------------------------------------------------
// QueryMgrs Class :: aMatch() - checks for a match
// -------------------------------------------------------------------------
IBase :: Boolean  QueryMgrs :: aMatch(const LEmployeeData* ed,
                                      const IString& key,
                                      const IString& value)
{

  if (key == "employeeType" )
     return value.isLike(IString(ed->employeeType()) );

  return false;
};


// -------------------------------------------------------------------------
// QueryAcct :: QueryAcct()
// -------------------------------------------------------------------------
QueryAcct :: QueryAcct()
           : QueryInfo("lacct.ini")
{};

// -------------------------------------------------------------------------
// QueryAcct :: ~QueryAcct()
// -------------------------------------------------------------------------
QueryAcct :: ~QueryAcct()
{};


// -------------------------------------------------------------------------
// QueryAcct :: fillPage() page to data
// -------------------------------------------------------------------------
QueryAcct& QueryAcct :: fillPage(AccountPage &acctPage)
{
    emptyBagSearchItems();
    acctPage.setAcctData();
    // take data out of the container and put it in the bag

     // iterate thru the container and put it in the BAG
     IContainerControl::ObjectCursor   iterator(*acctPage.pCnr);

     iterator.setToFirst();
     // return false only if an error
     if (false==iterator.isValid()) return *this;

     AcctCnrObj *cnrEntry;           // an IContainerObject
     IString  name="", node="";
     // only use data from the container

     while (iterator.isValid()) {
        cnrEntry = (AcctCnrObj *)iterator.current();

        if (cnrEntry->getUserId().length() > 0)
            name = cnrEntry->getUserId();

        if (cnrEntry->getNode().length() > 0);
            node = cnrEntry->getNode();

         addSearchItem (name, node );

        // get the next one
        cnrEntry = (AcctCnrObj *)iterator.next();

     } /* endwhile */
     return *this;
};

// -------------------------------------------------------------------------
// QueryAcct :: getMatchList() get the search list
// -------------------------------------------------------------------------
QueryAcct& QueryAcct :: getMatchList(AccountPage &acctPage)
{

  IString
    matchId,
    key,
    value;

  Boolean
    lp = false;
  LAcctData
   *ed = NULL;

  //  no verification of valid input
  acctPage.setAcctData();
  //  get the stuff from general page
  fillPage(acctPage);
  if (numberOfMatchElements() == 0) return *this;

  emptyBagMatchIds();

  // for each id get employeeData and see if a match

  idList.setFirstId();
  while (idList.getId(matchId)) {
    ed = new LAcctData(matchId);
    // see if a match by looping thru searchList
    if (setFirstSearchItem())
       lp = true;
    while ( lp && getSearchItem(key, value)) {
      lp = !aMatch(ed, key, value);
      getNextSearchItem();
    }
    if (!lp)
       // put this ID in the MatchList
       addMatchId(matchId);
    idList.getNextId();
    delete ed;
  }
  return *this;
};

// -------------------------------------------------------------------------
// QueryAcct :: aMatch() see if a match
// -------------------------------------------------------------------------
IBase :: Boolean  QueryAcct :: aMatch(LAcctData* ed,
                                      const IString& matchID,
                                      const IString& matchNode)
{
  IString
    user,
    node;

  Boolean
    Done = false;

  ed->setFirst();
  // loop thru and see if a match
  while ( true == ed->isValid() ) {

       ed->getItem(  user ,node, false);
       Done = ( (user.isLike(matchID)) &&
                (node.isLike(matchNode))) ;
       if (Done)  return Done;

    ed->getNext();
  } /* endwhile */


  return Done;
};


// -------------------------------------------------------------------------
// QuerySkill :: QuerySkill
// -------------------------------------------------------------------------
QuerySkill :: QuerySkill()
           : QueryInfo("lskill.ini")
{};

// -------------------------------------------------------------------------
// QuerySkill :: QuerySkill destructor
// -------------------------------------------------------------------------
QuerySkill :: ~QuerySkill()
{};

// -------------------------------------------------------------------------
// QuerySkill :: fillPage()
// -------------------------------------------------------------------------
QuerySkill& QuerySkill :: fillPage(SkillPage &skillPage)
{

     IString
       skill="*",
       years="0",
       range="=";

     emptyBagSearchItems();
     // take data out of the container and put it in the bag

     skillPage.setSkillData();
     emptyBagSearchItems();

     // iterate thru the container and put it in the BAG
     IContainerControl::ObjectCursor
       iterator(*skillPage.pCnr);

     iterator.setToFirst();
     // return false only if an error
     if (false==iterator.isValid()) return *this;

     SkillCnrObj
      *cnrEntry;           // an IContainerObject

     IString
       it1,
       it2;

     // only use data from the container

     while (iterator.isValid()) {
        cnrEntry = (SkillCnrObj *)iterator.current();

          if (cnrEntry->getSkill().length() > 0)
             skill = cnrEntry->getSkill();

          if (cnrEntry->getExp().length() > 0);
             years =  cnrEntry->getExp() ;

          if (skillPage.pSkillRange->getRange().length() > 0);
              range = skillPage.pSkillRange->getRange();

          addSearchItem ( skill, years, range) ;

        // get the next one
        cnrEntry = (SkillCnrObj *)iterator.next();

     } /* endwhile */

    return *this;
};


// -------------------------------------------------------------------------
// QuerySkill :: getMatchList()
// -------------------------------------------------------------------------
QuerySkill& QuerySkill :: getMatchList(SkillPage &skillPage)
{

  //  no verification of valid input
  skillPage.setSkillData();
  //  get the stuff from general page
  fillPage(skillPage);
  if (numberOfMatchElements() == 0) return *this;

  emptyBagMatchIds();

  // for each id get employeeData and see if a match
  IString
    matchId,
    key,
    range,
    value;

  Boolean
    lp = true ;
  LSkillData
   *ed = NULL;

  idList.setFirstId();
  while (idList.getId(matchId)) {
    ed = new LSkillData(matchId);
    // see if a match by looping thru searchList
    if (setFirstSearchItem())
       lp = true;
    while ( lp && getSearchItem(key, value, range)) {
      lp = !aMatch(ed, key, value, range);
      getNextSearchItem();
    }
    if (!lp)
       // put this ID in the MatchList
       addMatchId(matchId);
    idList.getNextId();
    delete ed;
  }
  return *this;
};

// -------------------------------------------------------------------------
// QuerySkill :: aMatch()
// -------------------------------------------------------------------------
IBase :: Boolean  QuerySkill :: aMatch(LSkillData* ed
                                     ,const IString& matchSkill
                                     ,const IString& matchYears
                                     ,const IString& matchRange)
{
  IString
    skill,
    years;

  Boolean
    Done = false;

  // loop thru and see if a match
  LSkillData::Rule
    rule;

  ed->setFirst();
  while (true == ed->isValid() ) {
       ed->getItem(  skill ,years, false );

       Done = ( (skill.isLike(matchSkill) ) &
                (inRange(matchYears, years, matchRange) ));
       if (Done) return Done;

    ed->getNext();
  } /* endwhile */


  return Done ;
};

// -------------------------------------------------------------------------
// QueryBadge :: QueryBadge()
// -------------------------------------------------------------------------
QueryBadge :: QueryBadge()
            : QueryInfo("lbadge.ini")
{};

// -------------------------------------------------------------------------
// QueryBadge :: ~QueryBadge()
// -------------------------------------------------------------------------
QueryBadge :: ~QueryBadge()
{};


// -------------------------------------------------------------------------
// QueryBadge :: fillPage()
// -------------------------------------------------------------------------
QueryBadge& QueryBadge :: fillPage(BadgePage &badgePage)
{

    emptyBagSearchItems();
    if (badgePage.badgeNumber().IString::length() > 0 )
        addSearchItem( "badgeNumber"
                       ,badgePage.badgeNumber());

    if (badgePage.issueDate().IString::length() > 0 )
        addSearchItem( "issueDate"
                       ,badgePage.issueDate()
                       ,badgePage.pIssueRange->getRange());

    if (badgePage.expDate().IString::length() > 0 )
        addSearchItem( "expireDate"
                       ,badgePage.expDate()
                       ,badgePage.pExpRange->getRange());

    return *this;
};


// -------------------------------------------------------------------------
// QueryBadge :: getMatchList()
// -------------------------------------------------------------------------
QueryBadge& QueryBadge :: getMatchList(BadgePage &badgePage)
{
  //  no verification of valid input

  //  get the stuff from general page
  fillPage(badgePage);

  emptyBagMatchIds();

  // for each id get employeeData and see if a match
  IString
    matchId,
    key,
    range,
    value;

  Boolean
    match = false;

  LBadgeData
   *bd = NULL;

  idList.setFirstId();
  while (idList.getId(matchId)) {
    bd = new LBadgeData(matchId);
    // see if a match by looping thru searchList
    if (setFirstSearchItem())
       match = true;
    while ( match && getSearchItem(key, value, range)) {
      match = aMatch(bd, key, value, range);
      getNextSearchItem();
    }
    if (match)
       // put this ID in the MatchList
       addMatchId(matchId);
    idList.getNextId();
    delete bd;
  } /* endwhile */
  return *this;

};

// -------------------------------------------------------------------------
// QueryBadge :: aMatch()
// -------------------------------------------------------------------------
IBase :: Boolean  QueryBadge :: aMatch(LBadgeData* bd,
                                       const IString& key,
                                       const IString& value,
                                       const IString& range)
{

   if (key == "badgeNumber")
       return bd->badgeNumber().isLike(value);

   if (key == "issueDate")
      return inRange(value,bd->badgeIssue(), range);

   if (key == "expireDate")
      return inRange(value,bd->badgeExpire(), range);

  return false;
};



// -------------------------------------------------------------------------
// QueryStatus :: QueryStatus()
// -------------------------------------------------------------------------
QueryStatus :: QueryStatus()
            : QueryInfo("lstatus.ini")
{};


// -------------------------------------------------------------------------
// QueryStatus :: ~QueryStatus()
// -------------------------------------------------------------------------
QueryStatus :: ~QueryStatus()
{};



// -------------------------------------------------------------------------
// QueryStatus :: fillPage()
// -------------------------------------------------------------------------
QueryStatus& QueryStatus :: fillPage(StatusPage &statusPage)
{

    emptyBagSearchItems();

    if (statusPage.pQueryActive->isSelected())
        addSearchItem( "active"
                       ,"yes");

    if (statusPage.pQueryInactive->isSelected())
        addSearchItem( "inactive"
                       ,"yes");

    if (statusPage.startDate.text().length() > 0 )
        addSearchItem( "startDate"
                       ,statusPage.startDate.text()
                       ,statusPage.pStartRange->getRange());

    if (statusPage.endDate.text().length() > 0 )
        addSearchItem( "endDate"
                       ,statusPage.endDate.text()
                       ,statusPage.pEndRange->getRange());

    if (statusPage.hourlyRate.text().length() > 0 )
        addSearchItem( "hourlyRate"
                       ,statusPage.hourlyRate.text()
                       ,statusPage.pPayRange->getRange());

    return *this;

};


// -------------------------------------------------------------------------
// QueryStatus :: getMatchList()
// -------------------------------------------------------------------------
QueryStatus& QueryStatus :: getMatchList(StatusPage &statusPage)
{
  //  no verification of valid input

  fillPage(statusPage);

  emptyBagMatchIds();

  // for each id get employeeData and see if a match
  IString
    matchId,
    key,
    range,
    value;

  Boolean
    match = false;

  LStatusData
   *bd = NULL;

  idList.setFirstId();
  while (idList.getId(matchId)) {
    bd = new LStatusData(matchId);
    // see if a match by looping thru searchList
    if (setFirstSearchItem())
       match = true;
    while ( match && getSearchItem(key, value, range)) {
      match = aMatch(bd, key, value, range);
      getNextSearchItem();
    }
    if (match)
       // put this ID in the MatchList
       addMatchId(matchId);

    idList.getNextId();
    delete bd;
  } /* endwhile */
  return *this;

};

// -------------------------------------------------------------------------
// QueryStatus :: aMatch()
// -------------------------------------------------------------------------
IBase :: Boolean  QueryStatus :: aMatch(LStatusData* sd
                                       , const IString& key
                                       , const IString& value
                                       , const IString& range)
{
   if (key == "active")
       return ((sd->statusActive()=="yes") ? true :false);

   if (key == "inactive")
      return ((sd->statusActive()=="no") ? true :false);

   if (key == "startDate")
      return inRange(value,sd->statusStart(), range);

   if (key == "endDate")
      return inRange(value,sd->statusEnd(), range);

   if (key == "hourlyRate")
      return inRange(value,sd->statusRate(), range);

   return false;

};



// -------------------------------------------------------------------------
// QueryQry :: QueryQry() - get all the saved queries
// -------------------------------------------------------------------------
QueryQry :: QueryQry()
          : itemsCur(items)
{
    emptyBagQry();
    getQryNames();                      // fill bag
};

// -------------------------------------------------------------------------
// QueryQry :: ~QueryQry() destructor
// -------------------------------------------------------------------------
QueryQry :: ~QueryQry()
{
  emptyBagQry();
};


// -------------------------------------------------------------------------
// QueryQry :: getQryNames()
// -------------------------------------------------------------------------
QueryQry :: getQryNames()
{
   IString
      id;

// get all lsaveqry.ini query
   try
   {
      IProfile
         savIni = IProfile("lsaveqry.ini");

      IProfile::Cursor
         IniCursor(savIni);
      for (IniCursor.setToFirst();
           IniCursor.isValid();
           IniCursor.setToNext() ) 
      {
         id = savIni.applicationOrKeyAt(IniCursor);
         putQry(id) ;
      }
   }
   catch(...)
   {}

   return 0;
}


// -------------------------------------------------------------------------
// QueryQry :: emptyBagQry()
// -------------------------------------------------------------------------
IBase :: Boolean  QueryQry  :: emptyBagQry()  {
 items.removeAll();
 itemsCur.invalidate();
 return (true);
};


// -------------------------------------------------------------------------
// QueryQry :: putQry()
// -------------------------------------------------------------------------
IBase :: Boolean QueryQry :: putQry( const IString& item1)
{
   items.add(Item(item1));

   return true;

}     // putQry


// -------------------------------------------------------------------------
// QueryQry :: getQry()
// -------------------------------------------------------------------------
IString QueryQry :: getQry()
{

   if (false == itemsCur.isValid())
      return "";  // none left

   Entry name = itemsCur.element().item1();

   items.locateElementWithKey(name, itemsCur);

   Entry i1 = itemsCur.element().item1();

   return ( i1.text() );

}; //getId



// -------------------------------------------------------------------------
// QueryIntersection  :: QueryIntersection()
// -------------------------------------------------------------------------
QueryIntersection :: QueryIntersection( QueryGenl*   pGenl
                                       ,QuerySkill*  pSkill
                                       ,QueryAcct*   pAcct
                                       ,QueryStatus* pStatus
                                       ,QueryBadge*  pBadge)
          : itemsCur(items)
{
    IString id;
    emptyBagIntersection();
    if (pGenl->numberOfMatchElements() > 0 ) {

        items.unionWith(pGenl->matchIds);

        if (pSkill->numberOfMatchElements() > 0 )
           items.intersectionWith(pSkill->matchIds);
        if (pAcct->numberOfMatchElements() > 0 )
           items.intersectionWith(pAcct->matchIds);
        if (pStatus->numberOfMatchElements() > 0 )
           items.intersectionWith(pStatus->matchIds);
        if (pBadge->numberOfMatchElements() > 0 )
           items.intersectionWith(pBadge->matchIds);

    } else
      if (pSkill->numberOfMatchElements() > 0 ) {
          items.unionWith(pSkill->matchIds);

          if (pAcct->numberOfMatchElements() > 0 )
             items.intersectionWith(pAcct->matchIds);
          if (pStatus->numberOfMatchElements() > 0 )
             items.intersectionWith(pStatus->matchIds);
          if (pBadge->numberOfMatchElements() > 0 )
             items.intersectionWith(pBadge->matchIds);
      }
      else
       if (pAcct->numberOfMatchElements() > 0 ) {
           items.unionWith(pAcct->matchIds);

           if (pStatus->numberOfMatchElements() > 0 )
              items.intersectionWith(pStatus->matchIds);
           if (pBadge->numberOfMatchElements() > 0 )
              items.intersectionWith(pBadge->matchIds);
       }
       else
         if (pStatus->numberOfMatchElements() > 0 ) {
             items.unionWith(pStatus->matchIds);

             if (pBadge->numberOfMatchElements() > 0 )
                items.intersectionWith(pBadge->matchIds);
         }
         if (pBadge->numberOfMatchElements() > 0 )
             items.unionWith(pBadge->matchIds);

};


// -------------------------------------------------------------------------
// QueryIntersection  :: ~QueryIntersection()
// -------------------------------------------------------------------------
QueryIntersection :: ~QueryIntersection()
{
  emptyBagIntersection();
};


// -------------------------------------------------------------------------
// QueryIntersection  :: emptyBagIntersection()
// -------------------------------------------------------------------------
IBase :: Boolean  QueryIntersection :: emptyBagIntersection()  {
 items.removeAll();
 itemsCur.invalidate();
 return (true);
};


// -------------------------------------------------------------------------
// QueryIntersection  :: putId()
// -------------------------------------------------------------------------
IBase :: Boolean QueryIntersection :: putId( const IString& item1)
{
   items.add(item1);

   return true;

};    // putQry


// -------------------------------------------------------------------------
// QueryIntersection  :: getId()
// -------------------------------------------------------------------------
IString QueryIntersection :: getId()
{

   if (false == itemsCur.isValid())
      return "";  // none left

   itemsCur.element().asString();

   return ( itemsCur.element().asString()  );

}; //getId

