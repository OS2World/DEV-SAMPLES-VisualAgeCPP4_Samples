/*******************************************************************************
* FILE NAME: ldbase.hpp                                                        *
*                                                                              *
* DESCRIPTION:                                                                 *
*                                                                              *
* Class                                                                        *
*   LStatusData                                                                 *
*   LBadgeData                                                                  *
*   LEmployeeData                                                               *
*   LSkillData
*   LProjectData                                                                *
*   LTimeCardData                                                               *
*   LAcctData                                                                   *
*   LTaskData                                                                   *
*   LQueryData                                                                  *
*   LDeleteEmployee                                                             *
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
#ifndef _LDBASE_
#define _LDBASE_


#include <iostream.h>
#include <iprofile.hpp>
#include <idate.hpp>
#include <idate.hpp>
#include "litems.hpp"

#include <istring.hpp>
#include <ikeybag.h>
typedef IKeyBag<Item, Entry> Items;

// forward declarations
class LQueryData;
class TimeCardPage;

//----------------------------------------------------------------------------
// class LStatusData
//----------------------------------------------------------------------------
class LStatusData : public IBase
{
public: // ---------------------- PUBLIC -------------------------------------

//----------------------- Contructor/Destructor ------------------------------
// Class LStatusData :: LStatusData()
//----------------------------------------------------------------------------
  LStatusData(const IString empNum);
  LStatusData(LQueryData& qd);

  ~LStatusData();

LStatusData&
  save( const  IString  empNum,
        const IString statusRate,
        const IString statusStart,
        const IString statusEnd,
        Boolean tog);

inline IString
  statusActive() {return StatusActive;};

inline IString
  statusInactive() {return StatusInactive;};

inline IString
  statusRate()   {return StatusRate;};

inline IString
  statusStart()  {return StatusStart;};

inline IString
  statusEnd()    {return StatusEnd;};

inline IString
  theRateRange()  {return TheRateRange;;};

inline IString
  theStartRange() {return TheStartRange;}

inline IString
  theEndRange()   {return TheEndRange; ;};

protected://----------------------- PROTECTED --------------------------------

LStatusData&
  load(const  IString  empNum);

LStatusData&
  loadQueryData(LQueryData& qd);

private:  //----------------------- PRIVATE ----------------------------------


IString
  StatusInactive,
  StatusActive,
  StatusRate,
  StatusStart,
  StatusEnd,
  TheRateRange,
  TheStartRange,
  TheEndRange;

};


//----------------------------------------------------------------------------
// class LBadgeData
//----------------------------------------------------------------------------
class LBadgeData  : public IBase
{

public: // ---------------------- PUBLIC -------------------------------------

friend class GeneralPage;

//----------------------- Contructor/Destructor ------------------------------
// Class LBadgeData :: LBadgeData()
//----------------------------------------------------------------------------
  LBadgeData();
  LBadgeData(const  IString &eNum);
  LBadgeData(LQueryData& qd);

  ~LBadgeData();

LBadgeData&
  save(const  IString  eNum,
       const  IString  badgeNumber,
       const  IString  issueDate,
       const  IString  expDate );

inline IString   badgeNumber() {return BadgeNumber;};
inline IString   badgeIssue()  {return BadgeIssue;};
inline IString   badgeExpire() {return BadgeExpire;};
inline IString   theIssueRange() {return TheIssueRange;};
inline IString   theExpRange() {return TheExpRange;};

protected: //----------------------- PROTECTED  ----------------------------------

LBadgeData&
  load(const  IString  &eNum);

LBadgeData&
  loadQueryData(LQueryData& qd);

private:   //----------------------- PRIVATE ----------------------------------

IString     BadgeNumber,
            BadgeIssue,
            BadgeExpire,
            TheIssueRange,
            TheExpRange;

};



//----------------------------------------------------------------------------
// class LEmployeeData
//----------------------------------------------------------------------------
class LEmployeeData  : public IBase
{
public: // ---------------------- PUBLIC -------------------------------------

friend class LPersonnelCnr;


enum EmplType {
               Regular,
               Manager,
               Supplemental,
               Unemployed
               };

//----------------------- Contructor/Destructor ------------------------------
// Class LEmployeeData :: LEmployeeData()
//----------------------------------------------------------------------------

  LEmployeeData();
  LEmployeeData(const IString empNum);
  LEmployeeData(LQueryData& qd);

  ~LEmployeeData();

LEmployeeData&
  save(const  IString empNum);

inline IString employeeNumber()  const { return theEmployeeNum; }
inline IString lastName()        const { return theLastName; }
inline IString firstName()       const { return theFirstName; }
inline IString middleInitial()   const { return theMiddleInitial; }
inline IString internalPhone()   const { return theInternalPhone; }
inline IString externalPhone()   const { return theExternalPhone; }
inline IString internalAddress() const { return theInternalAddr; }
inline IString externalAddress() const { return theExternalAddr; }
inline IString room()            const { return theRoom; }
inline IString building()        const { return theBuilding; }
inline IString department()      const { return theDeptName; }
inline IString division()        const { return theDivision; }
inline EmplType employeeType()   const { return theEmployeeType; }
inline IString badgeNumber()     const { return theBadgeNumber; }
inline IString badgeIssue()      const { return theBadgeIssue; }
inline IString badgeExpires()    const { return theBadgeExpire; }
inline IString managerNumber()   const { return theManagerNum; }
inline IString managerName()     const { return theManagerName; }

inline LEmployeeData& setEmployeeNumber(IString st)  {  theEmployeeNum=st; return *this;}
inline LEmployeeData& setLastName(IString st)        {  theLastName=st; return *this;}
inline LEmployeeData& setFirstName(IString st)       {  theFirstName=st;return *this;}
inline LEmployeeData& setMiddleInitial(IString st)   {  theMiddleInitial=st;return *this;}
inline LEmployeeData& setInternalPhone(IString st)   {  theInternalPhone=st;return *this;}
inline LEmployeeData& setExternalPhone(IString st)   {  theExternalPhone=st;return *this;}
inline LEmployeeData& setInternalAddress(IString st) {  theInternalAddr=st;return *this;}
inline LEmployeeData& setExternalAddress(IString st) {  theExternalAddr=st;return *this;}
inline LEmployeeData& setRoom(IString st)            {  theRoom=st;return *this;}
inline LEmployeeData& setBuilding(IString st)        {  theBuilding=st;return *this;}
inline LEmployeeData& setDepartment(IString st)      {  theDeptName=st;return *this;}
inline LEmployeeData& setDivision(IString st)        {  theDivision=st;return *this;}
inline LEmployeeData& setEmployeeType(EmplType st)   {  theEmployeeType=st;return *this;}
inline LEmployeeData& setBadgeNumber(IString st)     {  theBadgeNumber=st;return *this;}
inline LEmployeeData& setBadgeIssue(IString st)      {  theBadgeIssue=st; return *this;}
inline LEmployeeData& setBadgeExpires(IString st)    {  theBadgeExpire=st;return *this;}
inline LEmployeeData& setManagerNumber(IString st)   {  theManagerNum=st; return *this;}
inline LEmployeeData& setManagerName(IString st)     {  theManagerName=st;return *this;}


protected: //----------------------- PROTECTED ----------------------------------

LEmployeeData&
  load(const  IString empNum);

LEmployeeData&
  loadQryData(LQueryData& qd);

private: //----------------------- PRIVATE ----------------------------------

IString
  theEmployeeNum,
  theLastName,
  theFirstName,
  theMiddleInitial,
  theInternalPhone,
  theExternalPhone,
  theInternalAddr,
  theExternalAddr,
  theRoom,
  theBuilding,
  theDeptName,
  theDivision;

EmplType
  theEmployeeType;

IString
  theBadgeNumber,
  theBadgeIssue,
  theBadgeExpire,
  theManagerNum,
  theManagerName;

LBadgeData
  badgeData;

};


//----------------------------------------------------------------------------
// Class LSkillData :: LSkillData()
//----------------------------------------------------------------------------
class LSkillData    : public IBase
{

public: // ---------------------- PUBLIC -------------------------------------

enum Rule {
           na,
           file,
           add,
           replace,
           remove
           };

//----------------------- Contructor/Destructor ------------------------------
// Class LSkillData
//----------------------------------------------------------------------------
  LSkillData(const IString empNum = NULL);
  LSkillData(LQueryData& sd);
  ~LSkillData();

LSkillData&
  save(const  IString empNum);

      inline Boolean
         getNext(){ itemsCur.setToNext();
                    return itemsCur.isValid();}

      inline Boolean 
         setFirst(){ itemsCur.setToFirst();
                     return itemsCur.isValid();}

inline Boolean isValid(){ return itemsCur.isValid();}

LSkillData&
  deleteCurrentItem();

Boolean
  getItem(  IString& i1,
            IString& i2,
            Rule& rule,
            Boolean useKey = true);

Boolean
  getItem(  IString& i1,
            IString& i2,
            Boolean useKey = true);

Boolean
  putItem( const IString& i1,
           const IString& i2,
           const Rule&  rule=add);

LSkillData&
  emptyBag();

inline IString theRange() const {return TheRange;};

inline IString employeeNumber() const {return employeeNum;};

LSkillData&
  operator = ( const LSkillData& from );

protected: //----------------------- PROTECTED --------------------------------

LSkillData&
  load(const  IString empNum);

LSkillData&
  loadQueryData(LQueryData& qd);

Items
  getItems() const {return items;};

Items::Cursor
  getItemsCursor() const {return itemsCur;};

private: //----------------------- PRIVATE ----------------------------------

Items
  items;

Items::Cursor
  itemsCur;

IString
  employeeNum,
  TheRange;

};


//----------------------------------------------------------------------------
// Class LProjectData :: LProjectData()
//----------------------------------------------------------------------------
class LProjectData   : public IBase
{
public: // ---------------------- PUBLIC -------------------------------------

enum Rule {
           na,
           file,
           add,
           replace,
           remove
           };

//----------------------- Contructor/Destructor ------------------------------
// Class LProjectData :: LProjectData()
//----------------------------------------------------------------------------
  LProjectData(const IString empNum = NULL);
  ~LProjectData();

LProjectData&
  save(const IString empNum);

LProjectData&
  deleteCurrentItem();

Boolean
  getItem(  IString& i1,
            IString& i2,
            IString& i3,
            IString& i4,
            Rule rule );

LProjectData&
  putItem( const IString& i1,
           const IString& i2,
           const IString& i3,
           const IString& i4,
           const Rule&  rule=add );

LProjectData&
  emptyBag();

      inline Boolean
         getNext(){ itemsCur.setToNext(); 
                    return itemsCur.isValid();}

      inline Boolean
         setFirst(){ return(itemsCur.setToFirst());}

inline IString employeeNumber() const {return employeeNum;};

LProjectData&
  operator = ( const LProjectData& from );

protected: //----------------------- PROTECTED --------------------------------

LProjectData&
  load(const  IString empNum);

Items
  getItems() const {return items;};

Items::Cursor
  getItemsCursor() const {return itemsCur;};

private: //----------------------- PRIVATE --------------------------------

Items
  items;

Items::Cursor
  itemsCur;

IString
  employeeNum; // the key

};

//----------------------------------------------------------------------------
// Class TCard :: TCard()
//----------------------------------------------------------------------------
class TCard  : public IBase
{
public: // ---------------------- PUBLIC -------------------------------------

friend class TimeCardPage;

//----------------------- Contructor/Destructor ------------------------------
// Class TCard :: TCard()
//----------------------------------------------------------------------------

  TCard();
  ~TCard();

inline TCard&  setDate(const IString & s)        { Date = s; return *this;};
inline TCard&  setProjectName(const IString & s) { ProjectName = s;return *this;};
inline TCard&  setTaskName(const IString & s)    { TaskName = s;return *this;};
inline TCard&  setHours(const IString & s)       { Hours = s;return *this;};

inline IString date()  { return Date; };
inline IString projectName()  { return ProjectName;};
inline IString taskName()     { return TaskName;};
inline IString hours()        { return Hours;};

private: //----------------------- PRIVATE ----------------------------------

IString
  Date,
  ProjectName,
  TaskName,
  Hours;

IString
  employeeNum; // the key

};


//----------------------------------------------------------------------------
// Class LTimeCardData :: LTimeCardData()
//----------------------------------------------------------------------------
class LTimeCardData  : public IBase
{
public: // ---------------------- PUBLIC -------------------------------------

friend class TimeCardPage;
friend class TimeCard;
friend class DrawingArea;
friend class TaskPage;
friend class LTimeCardPieChart;

//----------------------- Contructor/Destructor ------------------------------
// Class LTimeCardData :: LTimeCardData()
//----------------------------------------------------------------------------
  LTimeCardData(const char * empNum, const IDate &weekEnding);
  ~LTimeCardData();

inline IString employeeNumber() const {return employeeNum;};

protected: //----------------------- PROTECTED --------------------------------

LTimeCardData& load(const  IString empNum);
LTimeCardData& save(const  IString empNum);

private: //----------------------- PRIVATE ----------------------------------

IDate
  theWeek;

enum { tcEntries = 18 };

TCard
  tcard[tcEntries];

IString
  employeeNum;

};


//----------------------------------------------------------------------------
// Class LAcctData :: LAcctData()
//----------------------------------------------------------------------------
class LAcctData  : public IBase
{
public: // ---------------------- PUBLIC -------------------------------------

  enum Rule {
             na,
             file,
             add,
             replace,
             remove
             };

//----------------------- Contructor/Destructor ------------------------------
// Class LAcctData :: LAcctData()
//----------------------------------------------------------------------------

  LAcctData(const IString empNum = NULL);
  LAcctData(LQueryData& qd);

  ~LAcctData();

LAcctData&
  save(const IString empNum);

LAcctData&
  deleteCurrentItem();

Boolean
  getItem(  IString& i1,
            IString& i2,
            Rule& rule,
            Boolean useKey = true);

Boolean
  getItem(  IString& i1,
            IString& i2,
            Boolean useKey=true);

LAcctData&
  putItem(  const IString& i1,
            const IString& i2,
            const Rule&  rule=add );

LAcctData&
  emptyBag();

      inline Boolean
         getNext()  { itemsCur.setToNext();
                      return itemsCur.isValid();}
      inline Boolean
         setFirst() { itemsCur.setToFirst();
                      return itemsCur.isValid();}
inline Boolean
  isValid(){ return itemsCur.isValid();}

inline IString theRange() const {return TheRange;};

inline IString employeeNumber() const {return employeeNum;};

LAcctData&
  operator = ( const LAcctData& from );

protected: //----------------------- PROTECTED---------------------------------

LAcctData&
  load(const IString empNum);

LAcctData&
  loadQueryData(LQueryData& qd);

Items
  getItems() const {return items;};

Items::Cursor
  getItemsCursor() const {return itemsCur;};

private: //----------------------- PRIVATE ----------------------------------

Items
  items;

Items::Cursor
  itemsCur;

IString
  employeeNum,
  TheRange;

};



//----------------------------------------------------------------------------
// Class LTaskData :: LTaskData()
//----------------------------------------------------------------------------
class LTaskData : public IBase
{
public: // ---------------------- PUBLIC -------------------------------------

enum Rule {
           na,
           file,
           add,
           replace,
           remove
           };

//----------------------- Contructor/Destructor ------------------------------
// Class LTaskData :: LTaskData()
//----------------------------------------------------------------------------
  LTaskData(const IString empNum=NULL);
  ~LTaskData();

LTaskData&
  save(const IString empNum);

      inline Boolean
         getNext() { itemsCur.setToNext();
                     return itemsCur.isValid();}

      inline Boolean 
         setFirst() { return(itemsCur.setToFirst());}

LTaskData&
  deleteCurrentItem();

Boolean
  getItem(  IString& i1,
            IString& i2,
            IString& i3,
            Rule& rule);

Boolean
  putItem(   const IString& i1,
             const IString& i2,
             const IString& i3,
             const Rule&  rule=add );

LTaskData&
  emptyBag();

Boolean
  isInAndBillable(const IString& theKey, const IString& theTask );

inline IString employeeNumber() const {return employeeNum;};

LTaskData&
  operator = ( const LTaskData& from );

protected: //----------------------- PROTECTED---------------------------------

LTaskData&
  load(const  IString empNum);

Items
  getItems() const {return items;};

Items::Cursor
  getItemsCursor() const {return itemsCur;};

private: //----------------------- PRIVATE ----------------------------------

Items
  items;

Items::Cursor
  itemsCur;

IString
  employeeNum;

};


//----------------------------------------------------------------------------
// Class LQueryData :: LQueryData()
//----------------------------------------------------------------------------
class LQueryData : public IBase
{
public: // ---------------------- PUBLIC -------------------------------------
//----------------------- Contructor/Destructor ------------------------------
// Class LQueryData :: LQueryData()
//----------------------------------------------------------------------------
  LQueryData(const  IString qryName="");
  ~LQueryData();

Boolean 
  saveIni(const  IString qryName="");

Boolean
  setFirstWithKey(char*  aKey );

Boolean
  getNextWithKey(char*   akey);

LQueryData&
  deleteItem(IString& queryName );

Boolean
  getItem(  IString& i1,
            IString& i2,
            IString& i3);

LQueryData& putItem(  const IString& i1,
                     const IString& i2,
                     const IString& i3 = IString(""),
                     const IString& i4 = IString(""));

inline Boolean isValid() {return itemsCur.isValid();};
inline IString queryName() {return QueryName;};

LQueryData&  emptyBag();

protected: //----------------------- PROTECTED ---------------------------------

LQueryData&
  loadIni(const  IString qryName="");

private: //----------------------- PRIVATE---------------------------------

Items
  items;

Items::Cursor
  itemsCur;

IString             QueryName;    // the key

};


//----------------------------------------------------------------------------
// Class LDeleteEmployee :: LDeleteEmployee()
//----------------------------------------------------------------------------
class LDeleteEmployee : public IBase
{

public: // ---------------------- PUBLIC -------------------------------------

//----------------------- Contructor/Destructor ------------------------------
// Class LDeleteEmployee :: LDeleteEmployee()
//----------------------------------------------------------------------------
  LDeleteEmployee();
  ~LDeleteEmployee();

LDeleteEmployee&
  deleteFromDataBase(const IString& empNum);


IProfile
  emplDB,
  acctDB,
  badgeDB,
  projectDB,
  skillDB,
  statusDB,
  taskDB,
  timecDB,
  workDB;

};

#endif
