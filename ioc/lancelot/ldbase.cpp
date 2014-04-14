/******************************************************************************
* .FILE:         ldbase.cpp                                                   *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Implementation   *
*                                                                             *
* .CLASSES:      LStatusData                                                  *
*                LBadgeData                                                   *
*                LEmployeeData                                                *
*                LSkillData                                                   *
*                LProjectData                                                 *
*                LTimeCardData                                                *
*                LAcctData                                                    *
*                LTaskData                                                    *
*                LQueryData                                                   *
*                LDeleteEmployee                                              *
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
#include "lancelot.h"
#include <iprofile.hpp>
#include <icnrctl.hpp>
#include "lpagectl.hpp"
#include "ldbase.hpp"
#include "ldbqry.hpp"

// --------------------------------------------------------------------------------------------
// Class LEmployeeData :: LEmployeeData() - constructor
// --------------------------------------------------------------------------------------------

LEmployeeData :: LEmployeeData()
          :   theEmployeeNum()
           , theLastName()
           , theFirstName()
           , theMiddleInitial()
           , theInternalPhone()
           , theExternalPhone()
           , theInternalAddr()
           , theExternalAddr()
           , theRoom()
           , theBuilding()
           , theDeptName()
           , theDivision()
           , theEmployeeType(LEmployeeData::Unemployed)
           , theBadgeNumber()
           , theBadgeIssue()
           , theBadgeExpire()
           , theManagerNum()
           , theManagerName()
           , badgeData()
{
}


// --------------------------------------------------------------------------------------------
// Class LEmployeeData :: LEmployeeData() - constructor
// --------------------------------------------------------------------------------------------

LEmployeeData :: LEmployeeData(const IString empNum)
          :   theEmployeeNum()
           , theLastName()
           , theFirstName()
           , theMiddleInitial()
           , theInternalPhone()
           , theExternalPhone()
           , theInternalAddr()
           , theExternalAddr()
           , theRoom()
           , theBuilding()
           , theDeptName()
           , theDivision()
           , theEmployeeType(LEmployeeData::Unemployed)
           , theBadgeNumber()
           , theBadgeIssue()
           , theBadgeExpire()
           , theManagerNum()
           , theManagerName()
           , badgeData(empNum)
{
  load(empNum);
}


// --------------------------------------------------------------------------------------------
// Class LEmployeeData :: LEmployeeData() - constructor query data
// --------------------------------------------------------------------------------------------

LEmployeeData :: LEmployeeData(LQueryData& qd)
           : theEmployeeNum()
           , theLastName()
           , theFirstName()
           , theMiddleInitial()
           , theInternalPhone()
           , theExternalPhone()
           , theInternalAddr()
           , theExternalAddr()
           , theRoom()
           , theBuilding()
           , theDeptName()
           , theDivision()
           , theEmployeeType(LEmployeeData::Unemployed)
           , theBadgeNumber()
           , theBadgeIssue()
           , theBadgeExpire()
           , theManagerNum()
           , theManagerName()
           , badgeData(NULL)
{
  loadQryData(qd);
}


// --------------------------------------------------------------------------------------------
// Class LEmployeeData :: ~LEmployeeData() - destructor
// --------------------------------------------------------------------------------------------
LEmployeeData :: ~LEmployeeData()
{ }


// --------------------------------------------------------------------------------------------
// Class LEmployeeData :: loadQryData() - get query info
// --------------------------------------------------------------------------------------------
LEmployeeData& LEmployeeData :: loadQryData(LQueryData& qd)
{

   unsigned long empType ;
   IString key, value, mt;

   for ( qd.setFirstWithKey("GENERAL");
         qd.isValid() ;
         qd.getNextWithKey("GENERAL") ) {

         qd.getItem(key, value, mt);
         if (key =="employeeNum"  )
             theEmployeeNum   = value;
         else
         if (key =="lastName"     )
            theLastName = value;
         else
         if (key =="firstName"    )
            theFirstName = value;
         else
         if (key =="middleInitial")
            theMiddleInitial = value;
         else
         if (key =="internalPhone")
            theInternalPhone = value;
         else
         if (key =="externalPhone")
            theExternalPhone = value;
         else
         if (key =="internalAddr" )
            theInternalAddr = value;
         else
         if (key =="externalAddr" )
            theExternalAddr = value;
         else
         if (key =="room"         )
            theRoom = value;
         else
         if (key =="building"     )
            theBuilding = value;
         else
         if (key =="deptName"     )
            theDeptName = value;
         else
         if (key =="divName"     )
            theDivision = value;
         else

         if (key =="managerNum"  )
             theManagerNum    = value;
         else
         if (key =="managerName"  )
             theManagerName   = value;
         else
         if (key == "employeeType") {
             empType          = value.asInt();
             theEmployeeType  = (LEmployeeData::EmplType) empType;
         } /* endif */

    }
    return *this;
}

// --------------------------------------------------------------------------------------------
// Class LEmployeeData :: load() - get database (ini) data
// --------------------------------------------------------------------------------------------
LEmployeeData&  LEmployeeData :: load(const IString empNum)
{
   try
   {
     IProfile *p = new  IProfile("lempl.ini");
     unsigned long empType ;
     if (p->containsApplication(empNum)) {

       if (p->containsKeyName("employeeNum", empNum))
          theEmployeeNum   = p->elementWithKey("employeeNum",empNum ) ;

       if (p->containsKeyName("lastName", empNum))
          theLastName      = p->elementWithKey( "lastName", empNum) ;

       if (p->containsKeyName("firstName", empNum))
          theFirstName     = p->elementWithKey( "firstName", empNum) ;

       if (p->containsKeyName("middleInitial", empNum))
          theMiddleInitial = p->elementWithKey( "middleInitial", empNum) ;

       if (p->containsKeyName("internalPhone", empNum))
          theInternalPhone = p->elementWithKey( "internalPhone", empNum) ;

       if (p->containsKeyName("externalPhone", empNum))
          theExternalPhone = p->elementWithKey( "externalPhone", empNum) ;

       if (p->containsKeyName("internalAddr", empNum))
          theInternalAddr  = p->elementWithKey( "internalAddr", empNum) ;

       if (p->containsKeyName("externalAddr", empNum))
          theExternalAddr  = p->elementWithKey( "externalAddr", empNum) ;

       if (p->containsKeyName("room", empNum))
          theRoom          = p->elementWithKey( "room", empNum) ;

       if (p->containsKeyName("building", empNum))
          theBuilding      = p->elementWithKey( "building", empNum) ;

       if (p->containsKeyName("deptName", empNum))
          theDeptName      = p->elementWithKey( "deptName", empNum) ;

       if (p->containsKeyName("divName", empNum))
          theDivision     = p->elementWithKey( "divName", empNum) ;

       if (p->containsKeyName("employeeType", empNum)) {
          empType          = p->integerWithKey( "employeeType", empNum) ;
          theEmployeeType  = (LEmployeeData::EmplType) empType;
       }

       if (p->containsKeyName("managerNum", empNum))
          theManagerNum    = p->elementWithKey( "managerNum", empNum) ;

       if (p->containsKeyName("managerName", empNum))
          theManagerName   = p->elementWithKey( "managerName", empNum) ;
    }
    delete p;
  }
  catch(...)
  {}

  return *this;
}


// --------------------------------------------------------------------------------------------
// Class LEmployeeData :: save() - save database (ini) data
// --------------------------------------------------------------------------------------------
LEmployeeData& LEmployeeData :: save( const IString empNum)
{
   try
   {
     IProfile *p = new IProfile("lempl.ini");

     p->deleteElementWithApplication( empNum );

     if (theEmployeeNum.length()!=0)
       p->addOrReplaceElementWithKey("employeeNum",
                                theEmployeeNum,
                                empNum ) ;

     if (theLastName.length()!=0)
       p->addOrReplaceElementWithKey("lastName",
                                  theLastName,
                                  empNum) ;

     if (theFirstName.length()!=0)
       p->addOrReplaceElementWithKey("firstName" ,
                                  theFirstName,
                                  empNum ) ;

     if (theMiddleInitial.length()!=0)
       p->addOrReplaceElementWithKey("middleInitial" ,
                                  theMiddleInitial,
                                  empNum ) ;

     if (theInternalPhone.length()!=0)
       p->addOrReplaceElementWithKey("internalPhone" ,
                                  theInternalPhone,
                                  empNum ) ;

     if (theExternalPhone.length()!=0)
       p->addOrReplaceElementWithKey("externalPhone" ,
                                  theExternalPhone,
                                  empNum ) ;

     if (theInternalAddr.length()!=0)
        p->addOrReplaceElementWithKey("internalAddr" ,
                                    theInternalAddr,
                                    empNum ) ;

     if (theExternalAddr.length()!=0)
       p->addOrReplaceElementWithKey("externalAddr" ,
                                  theExternalAddr,
                                  empNum ) ;

     if (theRoom.length()!=0)
       p->addOrReplaceElementWithKey("room" ,
                                  theRoom,
                                  empNum ) ;

     if (theBuilding.length()!=0)
       p->addOrReplaceElementWithKey("building" ,
                                  theBuilding ,
                                  empNum) ;

     if (theDeptName.length()!=0)
       p->addOrReplaceElementWithKey("deptName",
                                   theDeptName,
                                   empNum) ;

     if (theDivision.length()!=0)
       p->addOrReplaceElementWithKey("divName",
                                   theDivision,
                                   empNum) ;

       long et = (long) theEmployeeType;
       p->addOrReplaceElementWithKey("employeeType" ,
                                  (long) theEmployeeType,
                                  empNum ) ;

     if (theBadgeNumber.length()!=0)
       p->addOrReplaceElementWithKey("badgeNumber" ,
                                  theBadgeNumber,
                                  empNum ) ;

     if (theManagerNum.length()!=0)
       p->addOrReplaceElementWithKey("managerNum" ,
                                  theManagerNum,
                                  empNum ) ;

     if (theManagerName.length()!=0)
       p->addOrReplaceElementWithKey("managerName" ,
                                  theManagerName,
                                  empNum ) ;

    delete p;
   }
   catch(...)
   {}

  return *this;

}


// --------------------------------------------------------------------------------------------
// Class LBadgeData :: LBadgeData() - constructor
// --------------------------------------------------------------------------------------------

LBadgeData :: LBadgeData ()
      : BadgeNumber()
       ,BadgeIssue()
       ,BadgeExpire()
       ,TheIssueRange()
       ,TheExpRange()
{

}

LBadgeData :: LBadgeData (const IString  &eNum)
      : BadgeNumber()
       ,BadgeIssue()
       ,BadgeExpire()
       ,TheIssueRange()
       ,TheExpRange()
{
   if (0 != eNum.length())
      load(eNum);

}


// --------------------------------------------------------------------------------------------
// Class LBadgeData :: LBadgeData() - constructor - query info
// --------------------------------------------------------------------------------------------
LBadgeData :: LBadgeData (LQueryData& qd)
      : BadgeNumber()
       ,BadgeIssue()
       ,BadgeExpire()
       ,TheIssueRange("=")
       ,TheExpRange("=")
{
      loadQueryData(qd);

}


// --------------------------------------------------------------------------------------------
// Class LBadgeData :: ~LBadgeData() - destructor
// --------------------------------------------------------------------------------------------
LBadgeData :: ~LBadgeData ()
{ }


// --------------------------------------------------------------------------------------------
// Class LBadgeData :: load() - database info
// --------------------------------------------------------------------------------------------
LBadgeData& LBadgeData :: load (const IString &empNum)
{
   try
   {
   IProfile
    *p = new  IProfile("lbadge.ini");

   if (p->containsApplication(empNum)) {

    if (p->containsKeyName("badge", empNum))
       BadgeNumber = p->elementWithKey("badge", empNum ) ;

    if (p->containsKeyName("issue", empNum))
       BadgeIssue = p->elementWithKey("issue", empNum ) ;

    if (p->containsKeyName("expire", empNum))
       BadgeExpire = p->elementWithKey("expire", empNum );

   }
   delete p;
   }
   catch(...)
   {}
   return *this;
}


// --------------------------------------------------------------------------------------------
// Class LBadgeData :: loadQueryData() - get query info
// --------------------------------------------------------------------------------------------
LBadgeData& LBadgeData :: loadQueryData(LQueryData& qd)
{

   IString key, value, mt;
   IString   badgeIssue
            ,expire;

   for ( qd.setFirstWithKey("BADGE");
         qd.isValid() ;
         qd.getNextWithKey("BADGE") ) {

         qd.getItem(key, value, mt);

         if (key == "badgeNumber")
            BadgeNumber = value ;

         if (key == "issueDate")
            BadgeIssue = value ;

         if (key == "expireDate")
            BadgeExpire = value;

         if (key == "issueDateRange")
             TheIssueRange = value;

         if (key == "expireDateRange")
            TheExpRange = value;


    }
    return *this;
}


// --------------------------------------------------------------------------------------------
// Class LBadgeData :: save() - save database info
// --------------------------------------------------------------------------------------------
LBadgeData& LBadgeData :: save(const IString  empNum,
                            const IString  badgeN,
                            const IString  issueD,
                            const IString  expD)

{
   try
   {
   IProfile
    *p = new  IProfile("lbadge.ini");

   p->deleteElementWithApplication( empNum );

   if ( badgeN.length() )
     p->addOrReplaceElementWithKey(
                          "badge",
                           badgeN, empNum) ;

   if ( issueD.length() )
     p->addOrReplaceElementWithKey(
                          "issue",
                           issueD, empNum) ;

   if ( expD.length() )
     p->addOrReplaceElementWithKey(
                                "expire",
                                 expD, empNum ) ;

   delete p;
   }
   catch(...)
   {}
   return *this;
}



// --------------------------------------------------------------------------------------------
// Class LStatusData :: LStatusData() constructor
// --------------------------------------------------------------------------------------------
LStatusData :: LStatusData (const IString empNum)
      :  StatusActive("new")
        ,StatusInactive("no")
        ,StatusRate()
        ,StatusStart()
        ,StatusEnd()
        ,TheRateRange()
        ,TheStartRange()
        ,TheEndRange()

{
   load(empNum);
}


// --------------------------------------------------------------------------------------------
// Class LStatusData :: LStatusData() constructor - query info
// --------------------------------------------------------------------------------------------
LStatusData :: LStatusData (LQueryData& qd)
       : StatusActive("no")
        ,StatusInactive("no")
        ,StatusRate()
        ,StatusStart()
        ,StatusEnd()
        ,TheRateRange("=")
        ,TheStartRange("=")
        ,TheEndRange("=")
{
   loadQueryData(qd);

};


// --------------------------------------------------------------------------------------------
// Class LStatusData :: ~LStatusData() destructor
// --------------------------------------------------------------------------------------------
LStatusData :: ~LStatusData ()
{ };



// --------------------------------------------------------------------------------------------
// Class LStatusData :: load() get database info
// --------------------------------------------------------------------------------------------
LStatusData& LStatusData :: load (const IString empNum)
{
   try
   {
   IProfile
    *p = new  IProfile("lstatus.ini");

   if (p->containsApplication(empNum)) {
     unsigned long act = p->integerWithKey(
                                  "statusActive", empNum ) ;
     StatusActive = (act==1 ? "yes" : "no" );

     if (p->containsKeyName("statusRate", empNum))
        StatusRate = p->elementWithKey("statusRate", empNum ) ;

     if (p->containsKeyName("statusStart", empNum))
        StatusStart = p->elementWithKey("statusStart", empNum );

     if (p->containsKeyName("statusEnd", empNum))
        StatusEnd = p->elementWithKey("statusEnd", empNum );
   }
   delete  p;
   }
   catch(...)
   {}
   return *this;
}



// --------------------------------------------------------------------------------------------
// Class LStatusData :: loadQueryData() get query info
// --------------------------------------------------------------------------------------------
LStatusData& LStatusData :: loadQueryData (LQueryData& qd)
{

   IString key, value, mt;


   for ( qd.setFirstWithKey("STATUS");
         qd.isValid() ;
         qd.getNextWithKey("STATUS") ) {

         qd.getItem(key, value, mt);

         if (key == "active")
         {
            StatusActive = value;
         }

         if (key == "hourlyRate")
            StatusRate = value;

         if (key == "startDate")
            StatusStart = value;

         if (key == "endDate")
            StatusEnd = value;

         if (key == "hourlyRateRange")
             TheRateRange = value;

         if (key == "startDateRange")
             TheStartRange = value;

         if (key == "endDateRange")
             TheEndRange=value;
    }
  return *this;

}


// --------------------------------------------------------------------------------------------
// Class LStatusData :: save() save database info
// --------------------------------------------------------------------------------------------
LStatusData& LStatusData :: save(const IString empNum
                             ,const IString sRate
                             ,const IString sStart
                             ,const IString sEnd
                             ,bool        sAct)
{
   try
   {
   IProfile
    *p = new  IProfile("lstatus.ini") ;

   p->deleteElementWithApplication( empNum );

    // p->addOrReplaceElementWithKey("statusActive",
    //                              ((StatusActive == "yes")  ? 1 : 0), empNum);
    p->addOrReplaceElementWithKey("statusActive",
                                  sAct, empNum);

    if (sRate.length() != 0)
        p->addOrReplaceElementWithKey("statusRate",
                                      sRate, empNum) ;

    if (sStart.length() != 0)
        p->addOrReplaceElementWithKey("statusStart",
                                      sStart, empNum ) ;

    if (sEnd.length() != 0)
       p->addOrReplaceElementWithKey("statusEnd",
                                     sEnd , empNum) ;

    if (StatusActive != sEnd)
       p->addOrReplaceElementWithKey("statusActive",
                                     sAct , empNum) ;
    delete p;
   }
   catch(...)
   {}
   return *this;

}


// --------------------------------------------------------------------------------------------
// Class LSkillData :: LSkillData() - contructor
// --------------------------------------------------------------------------------------------
LSkillData :: LSkillData (const IString empNum)
           : itemsCur(items)
             ,employeeNum(empNum)
             ,TheRange()
{
   load(empNum); // fill bag
}

// --------------------------------------------------------------------------------------------
// Class LSkillData :: LSkillData() - contructor - query info
// --------------------------------------------------------------------------------------------
LSkillData :: LSkillData (LQueryData& qd)
           : itemsCur(items)
             ,employeeNum(qd.queryName())
             ,TheRange("=")
{
   loadQueryData(qd); // fill bag
}

// --------------------------------------------------------------------------------------------
// Class LSkillData :: LSkillData() - destructor
// --------------------------------------------------------------------------------------------
LSkillData :: ~LSkillData ()
{
  emptyBag();

}


// --------------------------------------------------------------------------------------------
// Class LSkillData :: load() - get database info
// --------------------------------------------------------------------------------------------
LSkillData& LSkillData :: load (const IString empNum)
{
  if ( empNum != (IString)NULL )
  {
     IString  key=empNum;

     IString     skillName
                ,employeeNumber
                ,exp;
     int i=0;
     try
     {
     IProfile
      *p = new IProfile("lskill.ini");

     // concat to make multiple entries unique
     key  = empNum  + IString(i);

     items.removeAll();
     itemsCur.invalidate();

     while (p->containsApplication(key)) {

        if (p->containsKeyName("skillName", key))
           skillName = p->elementWithKey( "skillName",key ) ;
        else
           skillName = "";

        if (p->containsKeyName("exp", key))
           exp  = p->elementWithKey( "exp", key ) ;
        else
           exp = "";

        // add it to the bag
        items.add(Item(Item::file, skillName, exp, key ));

        // this is how multiple items are handled for a given user/employee
        key = empNum + IString(++i);

     } /* endwhile */
     delete p;
     }
     catch(...)
     {}
  }
  return *this;
}  // get


// --------------------------------------------------------------------------------------------
// Class LSkillData :: loadQueryData() - get query info
// --------------------------------------------------------------------------------------------
LSkillData& LSkillData :: loadQueryData(LQueryData& qd)
{

   IString key, value;
   IString   skill, years, range ;


   for ( qd.setFirstWithKey("SKILL");
         qd.isValid() ;
         qd.getNextWithKey("SKILL") ) {

         qd.getItem(skill, years, range);

         items.add(Item(skill, years, range));

    }
    return *this;
}

// --------------------------------------------------------------------------------------------
// Class LSkillData :: save() - save database info
// --------------------------------------------------------------------------------------------
LSkillData&  LSkillData :: save(const IString empNum)
{
   try
   {
     IProfile
      *p = new IProfile("lskill.ini");
     // put data in IProfile
     IString  appl=empNum;
     IString  projName, projDes, respMgr, projState;
     int i=0;

     Items::Cursor itemsCur1(items), itemsCur2(items);

     if (items.numberOfElements() == 0 )
        return *this;

     // concat to make multiple entries unique
     appl = empNum + IString(i);

     //IProfile delete them all and then put then back
     while (p->containsApplication(appl)) {
        p->deleteElementWithApplication( appl ) ;
        appl = empNum + IString(++i);
     } /* endwhile */

     // must now iterate thru bag and save

     i = 0;
     appl = empNum + IString(i);
     itemsCur1.setToFirst();
     do {
        Entry name = itemsCur1.element().item1();

        items.locateElementWithKey(name, itemsCur2);
        do  {
           Entry item1 = itemsCur2.element().item1();
           Entry item2 = itemsCur2.element().item2();

           p->addOrReplaceElementWithKey("skillName", item1.text(), appl);
           p->addOrReplaceElementWithKey("exp", item2.text(), appl);

           appl = empNum + IString(++i);

        } while (items.locateNextElementWithKey(name, itemsCur2));

     } while (items.setToNextWithDifferentKey(itemsCur1));

     delete p;
   }
   catch(...)
   {}
   return *this;
}


// --------------------------------------------------------------------------------------------
// Class LSkillData :: getItem() - get skill info
// --------------------------------------------------------------------------------------------
bool LSkillData :: getItem( IString& item1
                                    ,IString& item2
                                    ,Rule& rule
                                    , bool useKey)
{

   if (false == itemsCur.isValid())
      return false;  // none left

   Entry i1 = itemsCur.element().item1();

   Entry i2 = itemsCur.element().item2();

   item1 =  i1.text();
   item2 =  i2.text();
   rule  =  (LSkillData::Rule  )itemsCur.element().rule();

   return true;

}

// --------------------------------------------------------------------------------------------
// Class LSkillData :: getItem() - get skill info - query info
// --------------------------------------------------------------------------------------------
bool LSkillData ::getItem( IString& item1
                                   ,IString& item2
                                   ,bool useKey)
{
   if (false == itemsCur.isValid())
      return false;  // none left

   if (useKey) {
      Entry name = itemsCur.element().item1();
      items.locateElementWithKey(name, itemsCur);
   }
   Entry i1 = itemsCur.element().item1();
   Entry i2 = itemsCur.element().item2();
   item1 =  i1.text();
   item2 =  i2.text();

   return true;

}


// --------------------------------------------------------------------------------------------
// Class LSkillData :: putItem() - put skill info - query info
// --------------------------------------------------------------------------------------------
bool LSkillData :: putItem( const IString& item1
                                    ,const IString& item2
                                    ,const Rule& rule)
{

     bool done = false;
     Item::Rule iRule = (Item::Rule) rule;
     Items::Cursor  itemsC(items);


     itemsC.setToFirst();

     if (false == itemsC.isValid())
        items.add(Item(iRule, item1, item2));
     else {
       // search bag for a duplicate

       // Entry name = itemsCur.element().item1();
       // the key is the id concatenated with a number

       // loop thru the bag and see if there is a match
       do {
         Entry i1 = itemsC.element().item1();
         if (i1.text() == item1) {
             Entry i2 = itemsC.element().item2();
             if (i2.text() != item2) {
                // a duplicate entry was found, with something different

                // new entry, reflected in container

                items.add(Item(Item::replace, item1, i2.text()));

                done = true;
             }
             else {  // entry matches
                // if doing an ADD, CHANGE do nothing
                // if a REMOVE
                if (iRule == Item::replace) {
                    // udated entry
                    items.add(Item(iRule, item1, item2));
                    // delete old entry
                    items.removeAt(itemsC);
                }

             }
         }

       } while (done == false &&
                items.setToNextWithDifferentKey(itemsC)); /* enddo */

       if (done == false ) {
          // a unique one
          items.add(Item( iRule, item1, item2));
       } /* endif */

     }

   return  true;

}


// --------------------------------------------------------------------------------------------
// Class LSkillData :: emptyBag() - empty the skill bag
// --------------------------------------------------------------------------------------------
LSkillData&  LSkillData :: emptyBag()  {
 // attach to employee number

 items.removeAll();
 itemsCur.invalidate();
 return *this;
}


// --------------------------------------------------------------------------------------------
// Class LSkillData :: deleteCurrentItem() - delete current skill
// --------------------------------------------------------------------------------------------
LSkillData& LSkillData ::  deleteCurrentItem()
{
    if (itemsCur.isValid()) {
       items.removeAt(itemsCur);
    } /* endif */
    return *this;
}

// --------------------------------------------------------------------------------------------
// Class LSkillData :: operator=    - copy LSkillData contents to another
// --------------------------------------------------------------------------------------------
LSkillData& LSkillData::operator=( const LSkillData& from )
{
  items = from.getItems();
  itemsCur = from.getItemsCursor();
  employeeNum = from.employeeNumber();
  TheRange = from.theRange();
  return *this;
}


// --------------------------------------------------------------------------------------------
// Class LAcctData :: LAcctData() - contructor
// --------------------------------------------------------------------------------------------
LAcctData :: LAcctData (const IString empNum)
           : itemsCur(items)
             ,employeeNum(empNum)
{
   load(empNum);
}

// --------------------------------------------------------------------------------------------
// Class LAcctData :: LAcctData() - contructor - query
// --------------------------------------------------------------------------------------------
LAcctData :: LAcctData (LQueryData& qd)
           : itemsCur(items)
             ,employeeNum(NULL)
{
   loadQueryData(qd);
}

// --------------------------------------------------------------------------------------------
// Class LAcctData :: LAcctData() - destructor
// --------------------------------------------------------------------------------------------
LAcctData :: ~LAcctData ()
{
   emptyBag();
}


// --------------------------------------------------------------------------------------------
// Class LAcctData :: load() - get database data
// --------------------------------------------------------------------------------------------
LAcctData& LAcctData :: load (const IString empNum)
{
  if ( empNum != (IString)NULL )
  {
     try
     {
     IProfile
      *p = new IProfile("lacct.ini");

     IString
       userName,
       node,
       key=empNum;

     int i=0;

     // concat to make multiple entries unique
     key  = empNum  + IString(i);

     emptyBag();

     while (p->containsApplication(key)) {

        if (p->containsKeyName("userName", key))
           userName = p->elementWithKey( "userName",key ) ;
        else
           userName = "";


        if (p->containsKeyName("node", key))
           node = p->elementWithKey( "node", key ) ;
        else
           node = "";

        // add it to the bag
        items.add(Item(Item::file, userName, node, key ));

        // this is how multiple items are handled for a given user/employee
        key = empNum + IString(++i);

     } /* endwhile */
    delete p;
    }
    catch(...)
    {}
  }
  return *this;
}


// --------------------------------------------------------------------------------------------
// Class LAcctData :: loadQueryData() - get query data
// --------------------------------------------------------------------------------------------
LAcctData& LAcctData :: loadQueryData(LQueryData& qd)
{

   IString key, value;
   IString   userName, mt
            ,node;

   for ( qd.setFirstWithKey("ACCOUNT");
         qd.isValid() ;
         qd.getNextWithKey("ACCOUNT") ) {

         qd.getItem(userName, node, key);

         // add it to the bag
         if ((userName.length() >0) && (node.length() > 0) )
            items.add(Item(userName, node));
    }
    return *this;
}



// --------------------------------------------------------------------------------------------
// Class LAcctData :: save() - save db data
// --------------------------------------------------------------------------------------------
LAcctData& LAcctData :: save(const IString empNum)
{
   try
   {
     IProfile
      *p = new IProfile("lacct.ini");

     // put data in IProfile
     IString
       appl=empNum;
     int
       i=0;
     Items::Cursor itemsCur1(items), itemsCur2(items);

     if (items.numberOfElements()== 0) return *this;

     // concat to make multiple entries unique
     appl = empNum + IString(i);

     //IProfile delete them all and then put then back
     while (p->containsApplication(appl)) {
        p->deleteElementWithApplication( appl ) ;
        appl = empNum + IString(++i);
     } /* endwhile */

     // must now iterate thru bag and save


   i = 0;
   appl = empNum + IString(i);
   itemsCur1.setToFirst();
   do {
      Entry name = itemsCur1.element().item1();

      items.locateElementWithKey(name, itemsCur2);
      do  {
         Entry item1 = itemsCur2.element().item1();
         Entry item2 = itemsCur2.element().item2();

         p->addOrReplaceElementWithKey("userName", item1.text(), appl);
         p->addOrReplaceElementWithKey("node", item2.text(), appl);
         appl = empNum + IString(++i);

      } while (items.locateNextElementWithKey(name, itemsCur2));

   } while (items.setToNextWithDifferentKey(itemsCur1));

   delete p;
   }
   catch(...)
   {}
   return *this;
}


// --------------------------------------------------------------------------------------------
// Class LAcctData :: getItem() - get a db item
// --------------------------------------------------------------------------------------------
bool LAcctData :: getItem( IString& item1
                                   ,IString& item2
                                   , Rule& rule
                                   , bool useKey)
{


   if (false == itemsCur.isValid())
      return false;  // none left

   Entry i1 = itemsCur.element().item1();

   Entry i2 = itemsCur.element().item2();

   item1 =  i1.text();
   item2 =  i2.text();
   rule  =  (LAcctData::Rule  )itemsCur.element().rule();

   return  true;

}

// --------------------------------------------------------------------------------------------
// Class LAcctData :: getItem() - get a query item
// --------------------------------------------------------------------------------------------
bool LAcctData :: getItem( IString& item1
                                   ,IString& item2
                                   ,bool useKey)
{
   if (false == itemsCur.isValid())
      return false;  // none left

   if (useKey) {
      Entry name = itemsCur.element().item1();
      items.locateElementWithKey(name, itemsCur);
   }
   item1  = itemsCur.element().item1().text();
   item2  = itemsCur.element().item2().text();

   //item1 =  i1.text();

   return true;

}



// --------------------------------------------------------------------------------------------
// Class LAcctData :: putItem() - add an item to the bag
// --------------------------------------------------------------------------------------------
LAcctData& LAcctData :: putItem( const IString& item1
                              ,const IString& item2
                              ,const Rule& rule )
{

     Item::Rule iRule = (Item::Rule) rule;
     // duplicates allowed
     items.add(Item(iRule, item1, item2));

     return *this;

}


// --------------------------------------------------------------------------------------------
// Class LAcctData :: emptyBag() - empty the bag
// --------------------------------------------------------------------------------------------
LAcctData&  LAcctData :: emptyBag()  {
 // attach to employee number

 items.removeAll();
 itemsCur.invalidate();
 return  *this;
}


// --------------------------------------------------------------------------------------------
// Class LAcctData :: deleteCurrentItem() -
// --------------------------------------------------------------------------------------------
LAcctData& LAcctData ::  deleteCurrentItem()
{
    if (itemsCur.isValid()) {
       items.removeAt(itemsCur);
    } /* endif */
    return *this;
}

// --------------------------------------------------------------------------------------------
// Class LAcctData :: operator=    - copy LAcctData contents to another
// --------------------------------------------------------------------------------------------
LAcctData& LAcctData::operator=( const LAcctData& from )
{
  items = from.getItems();
  itemsCur = from.getItemsCursor();
  employeeNum = from.employeeNumber();
  return *this;
}


// --------------------------------------------------------------------------------------------
// Class LTaskData :: LTaskData() - contructor
// --------------------------------------------------------------------------------------------
LTaskData :: LTaskData (const IString empNum)
           : itemsCur(items)
             ,employeeNum(empNum)
{
   load(empNum);
}

// --------------------------------------------------------------------------------------------
// Class LTaskData :: LTaskData() - destructor
// --------------------------------------------------------------------------------------------
LTaskData :: ~LTaskData ()
{
   emptyBag();
}


// --------------------------------------------------------------------------------------------
// Class LTaskData :: load()
// --------------------------------------------------------------------------------------------
LTaskData& LTaskData :: load (const IString empNum)
{
  if ( empNum != (IString)NULL )
  {
     IString
       key=empNum,
       theTask,
       theDesc,
       theBill,
       employeeNumber;

     int
       i=0;

   try
   {
     IProfile
      *p = new IProfile("ltask.ini");

     // concat to make multiple entries unique
     key  = empNum  + IString(i);

     emptyBag();

     while (p->containsApplication(key)) {
        if (p->containsKeyName("Task", key))
           theTask = p->elementWithKey( "Task",key ) ;
        else
           theTask = "";
        if (p->containsKeyName("Desc", key))
           theDesc = p->elementWithKey( "Desc",key ) ;
        else
           theDesc = "";

        if (p->containsKeyName("Billable", key))
           theBill = p->elementWithKey( "Billable",key ) ;
        else
           theBill = "";

        // add it to the bag
        items.add(Item(Item::file, theTask, theDesc, theBill, key ));

        // this is how multiple items are handled for a given user/employee
        key = empNum + IString(++i);

     } /* endwhile */
     delete p;
   }
   catch(...)
   {}
  }
  return *this;
}



// --------------------------------------------------------------------------------------------
// Class LTaskData :: save () - save database info
// --------------------------------------------------------------------------------------------
LTaskData& LTaskData :: save(const IString empNum)
{
     // put data in IProfile
     IString
       appl=empNum,
       theTask,
       theDesc,
       theBill,
       employeeNumber;

     int
       i=0;

     Items::Cursor
       itemsCur1(items),
       itemsCur2(items);

     if (items.numberOfElements() == 0 )
        return *this;

   try
   {
     IProfile
      *p = new IProfile("ltask.ini");

     // concat to make multiple entries unique
     appl = empNum + IString(i);

     //IProfile delete them all and then put then back
     while (p->containsApplication(appl)) {
        p->deleteElementWithApplication( appl ) ;
        appl = empNum + IString(++i);
     } /* endwhile */

     // must now iterate thru bag and save

   i = 0;
   appl = empNum + IString(i);
   itemsCur1.setToFirst();
   do {
      Entry name = itemsCur1.element().item1();


      items.locateElementWithKey(name, itemsCur2);
      do  {
         Entry item1 = itemsCur2.element().item1();
         Entry item2 = itemsCur2.element().item2();
         Entry item3 = itemsCur2.element().item3();

         if ( item1.text().length() )
         {
           p->addOrReplaceElementWithKey("Task", item1.text(), appl);
           p->addOrReplaceElementWithKey("Billable", item3.text(), appl);

           if ( item2.text().length() )
             p->addOrReplaceElementWithKey("Desc", item2.text(), appl);

           appl = empNum + IString(++i);
         }

      } while (items.locateNextElementWithKey(name, itemsCur2));

   } while (items.setToNextWithDifferentKey(itemsCur1));

   delete p;
   }
   catch(...)
   {}
   return *this;
}


// --------------------------------------------------------------------------------------------
// Class LTaskData :: getItem() - get database info
// --------------------------------------------------------------------------------------------
bool LTaskData :: getItem( IString& item1
                                    ,IString& item2
                                    ,IString& item3
                                    ,Rule& rule)
{
   if (false == itemsCur.isValid())
      return false;  // none left

   Entry name = itemsCur.element().item1();

   items.locateElementWithKey(name, itemsCur);

   item1 = itemsCur.element().item1().text();
   item2 = itemsCur.element().item2().text();
   item3 = itemsCur.element().item3().text();

   rule  =  (LTaskData::Rule  )itemsCur.element().rule();

   return true;
}



// --------------------------------------------------------------------------------------------
// Class LTaskData :: putItem() - save database info
// --------------------------------------------------------------------------------------------
bool LTaskData :: putItem( const IString& item1,
                                    const IString& item2,
                                    const IString& item3,
                                    const Rule& rule )
{
     bool done = false;
     Item::Rule iRule = (Item::Rule) rule;
     Items::Cursor  itemsC(items);

     itemsC.setToFirst();

     if (false == itemsC.isValid())
        items.add(Item(iRule, item1, item2, item3));
     else {
       // search bag for a duplicate

       // Entry name = itemsCur.element().item1();
       // the key is the id concatenated with a number

       // loop thru the bag and see if there is a match
       do {
         Entry i1 = itemsC.element().item1();
         if (i1.text() == item1) {
             Entry i2 = itemsC.element().item2();
             Entry i3 = itemsC.element().item3();
             if ((i2.text() != item2) | (i3.text() != item3)) {
                // a duplicate entry was found, with something different

                // new entry, reflected in container

                items.add(Item(Item::replace,
                               item1,
                               item2,
                               item3 ));
                done = true;
             }
             else {  // entry matches
                // if doing an ADD, CHANGE do nothing
                // if a REMOVE
                if (iRule == Item::replace) {
                    // udated entry
                    items.add(Item(iRule, item1, item2, item3));
                    // delete old entry
                    items.removeAt(itemsC);
                }

             }
         }

       } while (done == false &&
                items.setToNextWithDifferentKey(itemsC)); /* enddo */

       if (done == false ) {
          // a unique one
          items.add(Item( iRule, item1, item2, item3));
       } /* endif */

     }

   return true;
}


// --------------------------------------------------------------------------------------------
// Class LTaskData :: emptyBag() - empty bag
// --------------------------------------------------------------------------------------------
LTaskData&  LTaskData :: emptyBag()  {

 items.removeAll();
 itemsCur.invalidate();
 return *this;
}


// --------------------------------------------------------------------------------------------
// Class LTaskData :: deletCurrentItem()
// --------------------------------------------------------------------------------------------
LTaskData& LTaskData ::  deleteCurrentItem()
{
    if (itemsCur.isValid()) {
       items.removeAt(itemsCur);
    } /* endif */
    return *this;
}


// --------------------------------------------------------------------------------------------
// Class LTaskData :: isInAndBillable() - see if its in
// --------------------------------------------------------------------------------------------
bool  LTaskData :: isInAndBillable( const IString& empNum,
                                               const IString& theTask )
{
  try
  {
  IProfile
   *p = new IProfile("ltask.ini");

  int i=0;
  IString idTask, appl, idBillable;

  // concat to make multiple entries unique
  appl = empNum  + IString(i);

  while (p->containsApplication(appl)) {
    if (p->containsKeyName("Task", appl)) {
        idTask = p->elementWithKey( "Task",appl) ;
        if (idTask == theTask) {

           if (p->containsKeyName("Billable", appl))
              idBillable = p->elementWithKey( "Billable",appl) ;
              if (idBillable == "yes")
                  return true;
              else
                  return false;
        }
    }

    // this is how multiple items are handled for a given user/employee
    appl = empNum + IString(++i);

  } /* endwhile */
  delete p;
  }
  catch(...)
  {}
  return false;
}

// --------------------------------------------------------------------------------------------
// Class LTaskData :: operator=    - copy LTaskData contents to another
// --------------------------------------------------------------------------------------------
LTaskData& LTaskData::operator=( const LTaskData& from )
{
  items = from.getItems();
  itemsCur = from.getItemsCursor();
  employeeNum = from.employeeNumber();
  return *this;
}


// --------------------------------------------------------------------------------------------
// Class LProjectData :: LProjectData() -
// --------------------------------------------------------------------------------------------
LProjectData :: LProjectData (const IString empNum)
           : itemsCur(items)
             ,employeeNum(empNum)
{
   load(empNum);
}

// --------------------------------------------------------------------------------------------
// Class LProjectData :: ~LProjectData() -
// --------------------------------------------------------------------------------------------
LProjectData :: ~LProjectData ()
{
  emptyBag();
}


// --------------------------------------------------------------------------------------------
// Class LProjectData :: load() - load database info
// --------------------------------------------------------------------------------------------
LProjectData& LProjectData :: load (const IString empNum)
{
  if ( empNum != (IString)NULL )
  {
     IString  key=empNum;

     IString     theProject
                ,cbActive
                ,theDesc
                ,theMgr
                ,employeeNumber ;
     int i=0;

   try
   {
     IProfile
      *p = new IProfile("lproject.ini");

     // concat to make multiple entries unique
     key  = empNum  + IString(i);

     emptyBag();

     while (p->containsApplication(key)) {

        if (p->containsKeyName("Project", key))
           theProject = p->elementWithKey( "Project",key ) ;
        else
           theProject = "";
        if (p->containsKeyName("Active", key))
           cbActive   = p->elementWithKey( "Active", key ) ;
        else
           cbActive = "";

        if (p->containsKeyName("Desc", key))
           theDesc    = p->elementWithKey( "Desc",key ) ;
        else
           theDesc = "";

        if (p->containsKeyName("Mgr", key))
           theMgr     = p->elementWithKey( "Mgr",key ) ;
        else
           theMgr = "";

        // add it to the bag
        items.add(Item(Item::file
                       ,theProject
                       ,theDesc
                       ,theMgr
                       ,cbActive
                       , key ));

        // this is how multiple items are handled for a given user/employee
        key = empNum + IString(++i);

     } /* endwhile */
     delete p;
   }
   catch(...)
   {}
  }
  return *this;
}



// --------------------------------------------------------------------------------------------
// Class LProjectData :: save() - save database info
// --------------------------------------------------------------------------------------------
LProjectData&  LProjectData :: save(const IString empNum)
{
   try
   {
     IProfile
      *p = new IProfile("lproject.ini") ;
     // put data in IProfile
     IString  appl=empNum;

     IString     theProject
                ,cbActive
                ,theDesc
                ,theMgr ;
     int i=0;
     Items::Cursor itemsCur1(items), itemsCur2(items);
     if (items.numberOfElements() == 0 )
        return *this;


     // concat to make multiple entries unique
     appl = empNum + IString(i);

     //IProfile delete them all and then put then back
     while (p->containsApplication(appl)) {
        p->deleteElementWithApplication( appl ) ;
        appl = empNum + IString(++i);
     } /* endwhile */

     // must now iterate thru bag and save

   i = 0;
   appl = empNum + IString(i);
   itemsCur1.setToFirst();
   do {
      Entry name = itemsCur1.element().item1();

      items.locateElementWithKey(name, itemsCur2);
      do  {
         Entry item1 = itemsCur2.element().item1();

         Entry item2 = itemsCur2.element().item2();

         Entry item3 = itemsCur2.element().item3();

         Entry item4 = itemsCur2.element().item4();

         if ( item1.text().length() )
         {
           p->addOrReplaceElementWithKey("Project"     , item1.text(), appl);

           p->addOrReplaceElementWithKey("Active"      , item4.text(), appl);

           if ( item2.text().length() )
             p->addOrReplaceElementWithKey("Desc"        , item2.text(), appl);

           if ( item3.text().length() )
             p->addOrReplaceElementWithKey("Mgr"         , item3.text(), appl);

           appl = empNum + IString(++i);
         }

      } while (items.locateNextElementWithKey(name, itemsCur2));

   } while (items.setToNextWithDifferentKey(itemsCur1));

   delete p;
   }
   catch(...)
   {}
   return *this;
}


// --------------------------------------------------------------------------------------------
// Class LProjectData :: getItem() - get info
// --------------------------------------------------------------------------------------------
bool  LProjectData :: getItem( IString& item1,
                                        IString& item2,
                                        IString& item3,
                                        IString& item4,
                                        Rule rule)
{

   if (false == itemsCur.isValid())
      return false;  // none left

   Entry name = itemsCur.element().item1();

   items.locateElementWithKey(name, itemsCur);

   item1 = itemsCur.element().item1().text();
   item2 = itemsCur.element().item2().text();
   item3 = itemsCur.element().item3().text();
   item4 = itemsCur.element().item4().text();

   rule  =  (LProjectData::Rule  )itemsCur.element().rule();

   return true;

}



// --------------------------------------------------------------------------------------------
// Class LProjectData :: putItem() - save info
// --------------------------------------------------------------------------------------------
LProjectData&  LProjectData :: putItem( const IString& item1,
                                      const IString& item2,
                                      const IString& item3,
                                      const IString& item4,
                                      const Rule& rule )
{
     bool done = false;
     Item::Rule iRule = (Item::Rule) rule;
     Items::Cursor  itemsC(items);


     itemsC.setToFirst();

     if (false == itemsC.isValid())
        items.add(Item(iRule, item1, item2, item3, item4 ));
     else {
       // search bag for a duplicate

       // Entry name = itemsCur.element().item1();
       // the key is the id concatenated with a number

       // loop thru the bag and see if there is a match
       do {
         Entry i1 = itemsC.element().item1();
         if (i1.text() == item1) {
             Entry i2 = itemsC.element().item2();
             Entry i3 = itemsC.element().item2();
             Entry i4 = itemsC.element().item2();
             if ((i2.text() != item2) &&
                 (i3.text() != item3) &&
                 (i4.text() != item4) )
              {

                // a duplicate entry was found, with something different

                // new entry, reflected in container

                items.add(Item(Item::replace
                          , item1
                          , i2.text()
                          , i3.text()
                          , i4.text() ));

                done = true;
             }
             else {  // entry matches
                // if doing an ADD, CHANGE do nothing
                // if a REMOVE
                if (iRule == Item::replace) {
                    // udated entry
                    items.add(Item(iRule, item1, item2, item3, item4 ));
                    // delete old entry
                    items.removeAt(itemsC);
                }
             }
         }

       } while (done == false &&
                items.setToNextWithDifferentKey(itemsC)); /* enddo */

       if (done == false ) {
          // a unique one
          items.add(Item( iRule, item1, item2, item3, item4));
       } /* endif */

     }

   return *this;
}

// --------------------------------------------------------------------------------------------
// Class LProjectData :: emptyBag() - empty the bag
// --------------------------------------------------------------------------------------------
LProjectData&  LProjectData :: emptyBag()  {

 items.removeAll();
 itemsCur.invalidate();
 return *this;
}


// --------------------------------------------------------------------------------------------
// Class LProjectData :: deleteCurrentItem() - delete an item
// --------------------------------------------------------------------------------------------
LProjectData&  LProjectData ::  deleteCurrentItem()
{
    if (itemsCur.isValid()) {
       items.removeAt(itemsCur);
    } /* endif */
    return *this;
}

// --------------------------------------------------------------------------------------------
// Class LProjectData :: operator=    - copy LProjectData contents to another
// --------------------------------------------------------------------------------------------
LProjectData& LProjectData::operator=( const LProjectData& from )
{
  items = from.getItems();
  itemsCur = from.getItemsCursor();
  employeeNum = from.employeeNumber();
  return *this;
}


// --------------------------------------------------------------------------------------------
// Class TCard :: TCard contructor
// --------------------------------------------------------------------------------------------
TCard :: TCard()
{
  Date        = IString();
  ProjectName = IString();
  TaskName    = IString();
  Hours       = IString();

}

// --------------------------------------------------------------------------------------------
// Class TCard :: TCard destructor
// --------------------------------------------------------------------------------------------
TCard :: ~TCard()
{

}


// --------------------------------------------------------------------------------------------
// Class TimeCard :: TCardData
// --------------------------------------------------------------------------------------------
LTimeCardData :: LTimeCardData(const char* empNum,
                                  const IDate &theDate)
                   : theWeek(theDate)
                    ,tcard()
                    ,employeeNum(empNum)
{
   IString k = empNum + theWeek.asString();
   load(k);
}

// --------------------------------------------------------------------------------------------
// Class TimeCard :: TCard destructor
// --------------------------------------------------------------------------------------------
LTimeCardData :: ~LTimeCardData()
{

}


// --------------------------------------------------------------------------------------------
// Class TimeCard :: load() - get dataabse info
// --------------------------------------------------------------------------------------------
LTimeCardData& LTimeCardData :: load (const IString IDandDate)
{
   try
   {
     IProfile
      *p = new IProfile("ltime.ini");

     IString
       key=IDandDate;

     IString
       theDate,
       theProj,
       theTask,
       theHours;

     int
       i=0;

     // concat to make multiple entries unique
     key  += IString(i);

     while (p->containsApplication(key)) {

        if (p->containsKeyName("Date", key))
            theDate = p->elementWithKey( "Date",key ) ;
        else
            theDate = "";

        if (p->containsKeyName("Project", key))
            theProj    = p->elementWithKey( "Project", key ) ;
        else
            theProj = "";

        if (p->containsKeyName("Task", key))
            theTask    = p->elementWithKey( "Task", key ) ;
        else
            theTask = "";

        if (p->containsKeyName("Hours", key))
            theHours   = p->elementWithKey( "Hours", key ) ;
        else
            theHours = "";

        tcard[i].setDate(theDate);
        tcard[i].setProjectName(theProj);
        tcard[i].setTaskName(theTask);
        tcard[i].setHours(theHours);

        // this is how multiple items are handled for a given user/employee
        key = IDandDate+ IString(++i);

     } /* endwhile */

    delete p;
   }
   catch(...)
   {}
    return *this;
}  // get



// --------------------------------------------------------------------------------------------
// Class TimeCard :: save() - get dataabse info
// --------------------------------------------------------------------------------------------
LTimeCardData&  LTimeCardData  :: save(const IString IDandDate)
{
   try
   {
     IProfile
      *p = new IProfile("ltime.ini");
     // put data in IProfile
     IString    appl
              , theProj
              , theDate
              , theTask
              , theHours;
     int i=0;

     // concat to make multiple entries unique
     appl = IDandDate + IString(i);

     //IProfile delete them all and then put then back
     while (p->containsApplication(appl)) {
        p->deleteElementWithApplication( appl ) ;
        appl = IDandDate + IString(++i);
     }

     i = 0;
     appl = IDandDate + IString(i);
     for (i = 0 ;i < tcEntries; i++) {

         theDate  = tcard[i].date();
         theProj  = tcard[i].projectName();
         theTask  = tcard[i].taskName();
         theHours = tcard[i].hours();

         appl = IDandDate + IString(i);

         if ( theDate.length() )
            p->addOrReplaceElementWithKey("Date",       theDate , appl);

         if ( theProj.length() )
            p->addOrReplaceElementWithKey("Project",    theProj , appl);

         if ( theTask.length() )
            p->addOrReplaceElementWithKey("Task",       theTask , appl);

         if ( theHours.asInt() )
            p->addOrReplaceElementWithKey("Hours",      theHours, appl);
     }

     delete p;
   }
   catch(...)
   {}
     return *this;
}


// --------------------------------------------------------------------------------------------
// Class LQueryData :: LQueryData() - constructor
// --------------------------------------------------------------------------------------------
LQueryData :: LQueryData (const IString queryName)
             : itemsCur(items)
             ,QueryName(queryName)
{
   loadIni(queryName); // fill bag
}

// --------------------------------------------------------------------------------------------
// Class LQueryData :: LQueryData() - destructor
// --------------------------------------------------------------------------------------------
LQueryData :: ~LQueryData ()
{
  emptyBag();

}


// --------------------------------------------------------------------------------------------
// Class LQueryData :: loadIni() - read save query info
// --------------------------------------------------------------------------------------------
LQueryData& LQueryData :: loadIni (const IString queryName)
{
     // go thru the ini getting all the query data
   int
      nd,
      i;

   IString
      page,
      key,
      value,
      theWord,
      range,
      i1="",
      i2="",
      i3="";

   if (queryName.length() == 0)
      return *this;

   try
   {
      IProfile
         theProfile = IProfile("lsaveqry.ini");

      IProfile::Cursor
         iniQueryCur = IProfile::Cursor(theProfile, queryName);

     for (iniQueryCur.setToFirst();
          iniQueryCur.isValid();
          iniQueryCur.setToNext())
     {
          // get the KEY data
          theWord  = theProfile.applicationOrKeyAt(iniQueryCur);
          switch (theWord.numWords()) {
            case 2 :

              page = theWord.word(1);
              key  = theWord.word(2);
              value = theProfile.elementWithKey(theWord, queryName);
              if (key.isDigits()) {
                 // data is for a container
                nd= value.numWords();
                if (nd >= 3 ) {
                   // handle a space. assumes 3 keywords
                   for (i=1;i < nd-1 ;++i ) {
                      i1 += " " + value.word(i);
                   } /* endfor */

                   i2 = value.word(nd-1); // something
                   i3 = value.word(nd);   // range
                   items.add(Item(page, i1, i2, i3 ));
                   i1 = "";
                } /* endif */
                else
                if (nd == 2 ) {
                   // this is an acct query
                   // handle a space. assumes 2 keywords
                   i1 = value.word(1);
                   i2 = value.word(2);
                   items.add(Item(page, i1, i2 ));
                   i1 = "";
                } /* endif */



              }
              else
                items.add(Item(page, key, value ));

              break;
            case 3:
              page   = theWord.word(1);
              key    = theWord.word(2);
              range  = theWord.word(3);
              value = theProfile.elementWithKey(theWord, queryName);

              items.add(Item(page, key, value, range ));
              break;

          }
     }
   }
   catch(...)
   {}

   return *this;
}  // get



// --------------------------------------------------------------------------------------------
// Class LQueryData :: saveIni() - save save query info
// --------------------------------------------------------------------------------------------
bool LQueryData :: saveIni(const IString queryName)
{
   bool
      rv = true;
   try
   {
     IProfile
       *p = new IProfile("lsaveqry.ini");

     //
     // pass in the title
     // put data in IProfile

     // IString  appl=fileName;
     // IString  projName, projDes, respMgr, projState;
     // int i=0;

     // go thru the bag and save in the ini


     // concat to make multiple entries unique


     //IProfile delete them all and then put then back
     if ( p->containsApplication( queryName ) )
       rv = false;
     p->deleteElementWithApplication( queryName ) ;

     // must now iterate thru bag and save

     Items::Cursor itemsCur1(items);

     IString i1,i2 ;

     for ( itemsCur1.setToFirst() ;
           itemsCur1.isValid();
           itemsCur1.setToNext()) {

          Entry key  = itemsCur1.element().item1();
          i1  = key.text();

          Entry data = itemsCur1.element().item2();

          Entry d1   = itemsCur1.element().item3();
          Entry d2   = itemsCur1.element().item4();
          if (d1.text().length() > 0 ) {
             i2 = data.text() + " " + d1.text() + " " + d2.text();

          } else {
             i2  = data.text();
          } /* endif */

          p->addOrReplaceElementWithKey(i1, i2 , queryName);
      }

      delete p;
   }
   catch(...)
   {}
   return rv;
}


// --------------------------------------------------------------------------------------------
// Class LQueryData :: getItem() - get a query item
// --------------------------------------------------------------------------------------------
bool LQueryData :: getItem( IString& item2
                                      ,IString& item3
                                      ,IString& item4)
{
   // get a query
   if (false == itemsCur.isValid())
      return false;  // none left


   // item 1 is a key
   // not used, delete later, its the PAGE
   Entry i2 = itemsCur.element().item2();
   Entry i3 = itemsCur.element().item3();
   Entry i4 = itemsCur.element().item4();

   item2 =  i2.text();
   item3 =  i3.text();
   item4 =  i4.text();
   return true;

}


// --------------------------------------------------------------------------------------------
// Class LQueryData :: emptyBag() - empty the bag
// --------------------------------------------------------------------------------------------
LQueryData&  LQueryData :: emptyBag()  {
 items.removeAll();
 itemsCur.invalidate();
 return *this;
}


// --------------------------------------------------------------------------------------------
// Class LQueryData :: deleteItem() - delete an item
// --------------------------------------------------------------------------------------------
LQueryData& LQueryData :: deleteItem(IString& queryName )
{
   if (queryName.length() != 0 ) {
      try
      {
         IProfile
            *p = new IProfile("lsaveqry.ini");

         p->deleteElementWithApplication(queryName);
         delete p;
      }
      catch(...)
      {}
   }
   return *this;
}

// --------------------------------------------------------------------------------------------
// Class LQueryData :: setFirstWithKey() - point to the first key
// --------------------------------------------------------------------------------------------
bool LQueryData :: setFirstWithKey(char*  key)
{
  Entry aKey = Entry(key);
  items.locateElementWithKey(aKey, itemsCur);
  return itemsCur.isValid();
}

// --------------------------------------------------------------------------------------------
// Class LQueryData :: getNextWithKey() - get next first key
// --------------------------------------------------------------------------------------------
bool LQueryData :: getNextWithKey(char*  key)
{
  Entry aKey = Entry(key);
  items.locateNextElementWithKey(aKey, itemsCur);
  return itemsCur.isValid();
}


// --------------------------------------------------------------------------------------------
// Class LQueryData :: putItem() - save item
// --------------------------------------------------------------------------------------------
LQueryData& LQueryData :: putItem( const IString& item1,
                                 const IString& item2,
                                 const IString& item3,
                                 const IString& item4)
{
     items.add(Item( item1, item2, item3, item4  ));
     return *this;
}


// --------------------------------------------------------------------------------------------
// Class LDeleteEmployee :: LDeleteEmployee() - constructor
// --------------------------------------------------------------------------------------------
LDeleteEmployee :: LDeleteEmployee()
                      : emplDB("lempl.ini"),
                        acctDB("lacct.ini"),
                        badgeDB("lbadge.ini"),
                        projectDB("lproj.ini"),
                        skillDB("lskill.ini"),
                        statusDB("lstatus.ini"),
                        taskDB("ltask.ini"),
                        timecDB("ltime.ini"),
                        workDB("lwork.ini")
{}

// --------------------------------------------------------------------------------------------
// Class LDeleteEmployee :: ~LDeleteEmployee() - destructor
// --------------------------------------------------------------------------------------------
LDeleteEmployee :: ~LDeleteEmployee()
{}


// --------------------------------------------------------------------------------------------
// Class LDeleteEmployee :: deleteFromDataBase() delete an employee from all db's (ini's)
// --------------------------------------------------------------------------------------------
LDeleteEmployee&  LDeleteEmployee :: deleteFromDataBase(const IString& empNum)
{
  // delete someone from the database

  // genl data base entry
  emplDB.deleteElementWithApplication(empNum);

  // badge database
  badgeDB.deleteElementWithApplication(empNum);

  // status database
  statusDB.deleteElementWithApplication(empNum);

  // These database ini's are container objects
  IString appl ;
  short i=0;

  // account database
  appl = empNum + IString(i);
  while (acctDB.containsApplication(appl)) {
        acctDB.deleteElementWithApplication( appl ) ;
        appl = empNum + IString(++i);
  } /* endwhile */

  i = 0;
  // skill   database
  appl = empNum + IString(i);
  while (skillDB.containsApplication(appl)) {
        skillDB.deleteElementWithApplication( appl ) ;
        appl = empNum + IString(++i);
  } /* endwhile */

  i = 0;
  // project database
  appl = empNum + IString(i);
  while (projectDB.containsApplication(appl)) {
        projectDB.deleteElementWithApplication( appl ) ;
        appl = empNum + IString(++i);
  } /* endwhile */

  i = 0;
  // task    database
  appl = empNum + IString(i);
  while (taskDB.containsApplication(appl)) {
        taskDB.deleteElementWithApplication( appl ) ;
        appl = empNum + IString(++i);
  } /* endwhile */

  i = 0;
  // time card database
  appl = empNum + IString(i);
  while (timecDB.containsApplication(appl)) {
        timecDB.deleteElementWithApplication( appl ) ;
        appl = empNum + IString(++i);
  } /* endwhile */

  i = 0;
  // work card database
  appl = empNum + IString(i);
  while (workDB.containsApplication(appl)) {
         workDB.deleteElementWithApplication( appl ) ;
         appl = empNum + IString(++i);
  } /* endwhile */
  return *this;

}
