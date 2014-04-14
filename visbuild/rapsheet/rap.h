#ifndef _RAP_
#define _RAP_
/******************************************************************************
* .FILE:        rap.h                                                         *
*                                                                             *
* .DESCRIPTION: Symbolic definitions and structures for the Police Rap Sheet  *
*                                                                             *
* .CLASSES:                                                                   *
*                                                                             *
* .COPYRIGHT:                                                                 *
*    Licensed Material - Program-Property of IBM                              *
*    (C) Copyright IBM Corp. 1992, 1996 - All Rights Reserved                 *
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

/************************************************************************
 * Resource IDs
 ************************************************************************/
#define    NOPHOTO_FOUND                   7
#define    WAVES_FRONT                     1
#define    WAVES_LEFT                      2
#define    WAVES_RIGHT                     3
#define    HAMMER_LEFT                     4
#define    HAMMER_FRONT                    5
#define    HAMMER_RIGHT                    6
#define    FREE_BITMAP                  1000
#define    BOOKED_BITMAP                1001
#define    SUSPECT_BITMAP               1002
#define    LOCK_BITMAP                  1003

#define    SUSPECT_ICON                 2000
#define    WITNESS_ID_ICON              2001
#define    CASES_ICON                   2002
#define    MOST_WANTED_ICON             2003
#define    PERSON_ICON                  2004

/*-----------------------------------------------------------------------
 * Messages
 *----------------------------------------------------------------------*/
#define BUFFERFULL_WARNING  3000
#define NOSUSPECTFOUND_MSG  3001
#define NOSUSPECTSFOUND_MSG  3002
#define GETSUSPECTERROR_MSG  3003
#define GETSUSPECTSERROR_MSG  3004

/*-----------------------------------------------------------------------
 * String values
 *----------------------------------------------------------------------*/
#define BLUE_EYES_STR     5000
#define BROWN_EYES_STR    5001
#define GREEN_EYES_STR    5002
#define HAZEL_EYES_STR    5003

#define NO_HAIR_STR       5010
#define BLACK_HAIR_STR    5011
#define BLONDE_HAIR_STR   5012
#define BROWN_HAIR_STR    5013
#define GREY_HAIR_STR     5014
#define RED_HAIR_STR      5015

#define ARSON_STR                      5020
#define ACCOMPLICE_TO_MURDER_STR       5021
#define ASSAULT_STR                    5022
#define ASSAULT_W_DEADLY_WEAPON_STR    5023
#define BREAKING_AND_ENTERING_STR      5024
#define BURGLARY_STR                   5025
#define DWI_STR                        5026
#define EMBEZZLEMENT_STR               5027
#define FRAUD_STR                      5028
#define HIJACKING_STR                  5029
#define HIT_AND_RUN_STR                5030
#define KIDNAPPING_STR                 5031
#define MANSLAUGHTER_STR               5032
#define MURDER_STR                     5033
#define PERJURY_STR                    5034
#define TRESPASSING_STR                5035
#define VANDALISM_STR                  5036
#define WRECKLESS_DRIVING_STR          5037

#define ACQUITTED_STR                  5100
#define ARRESTED_STR                   5101
#define ARRAIGNED_STR                  5102
#define CONVICTED_STR                  5103
#define DROPPED_STR                    5104
#define ESCAPED_STR                    5105
#define FREE_ON_BOND_STR               5106
#define RELEASED_STR                   5107
#define RELEASED_ON_PAROLE_STR         5108
#define UNDER_SUSPICION_STR            5109
#define WANTED_STR                     5110

/************************************************************************
 * Common lengths
 ************************************************************************/
#define    LAST_NAME_LEN                  30
#define    FIRST_NAME_LEN                 20
#define    DATE_LEN                       10
#define    COMMENT_LEN                    50
/************************************************************************
 * Alias   lengths
 ************************************************************************/
#define    ALIAS_NAME_LEN                 50

/************************************************************************
 * Address lengths
 ************************************************************************/
#define    ADDRESS_STREET_LEN             30
#define    ADDRESS_CITY_LEN               20
#define    ADDRESS_COUNTY_LEN             20
#define    ADDRESS_STATE_LEN               2
#define    ADDRESS_ZIP_LEN                10
/************************************************************************
 * Arrest lengths
 ************************************************************************/
#define    ARREST_CHARGE_LEN              20
#define    ARREST_STATUS_LEN              15
#define    ARREST_REPORT_LEN             200      /*varchar             */
/************************************************************************
 * Suspect lengths
 ************************************************************************/
#define    SUSPECT_BOOK_NUM_LEN           10
#define    SUSPECT_COLOR_LEN              20
#define    SUSPECT_TRAIT_DESC_LEN         50      /*varchar             */
#define    SUSPECT_INFO_LEN              100      /*varchar             */
#define    SUSPECT_MO_DESC_LEN           100      /*varchar             */
/************************************************************************
 * Last seen lengths
 ************************************************************************/
#define    LS_LOC_LEN                     50
#define    LS_WITNESS_LEN                 50

/************************************************************************
 * Typedefs
 ************************************************************************/
typedef struct {
   unsigned long   book_number;
   unsigned short  gender;
   unsigned short  height;
   unsigned short  weight;
   unsigned short  hairColor;
   unsigned short  eyeColor;
   unsigned short  hasMole;
   unsigned short  hasScar;
   unsigned short  hasTattoo;
   unsigned short  mugFront;
   unsigned short  mugRight;
   unsigned short  mugLeft;

   char            firstName[FIRST_NAME_LEN+1];
   char            lastName[LAST_NAME_LEN+1];
   char            birthDate[DATE_LEN+1];
   char            info[SUSPECT_INFO_LEN+1];
   char            MO[SUSPECT_MO_DESC_LEN+1];
   char            moleDescription[SUSPECT_TRAIT_DESC_LEN+1];
   char            scarDescription[SUSPECT_TRAIT_DESC_LEN+1];
   char            tattooDescription[SUSPECT_TRAIT_DESC_LEN+1];
   char            street[ADDRESS_STREET_LEN+1];
   char            city[ADDRESS_CITY_LEN+1];
   char            county[ADDRESS_COUNTY_LEN+1];
   char            state[ADDRESS_STATE_LEN+1];
   char            zip[ADDRESS_ZIP_LEN+1];
   } SUSPECT_STRUCT, *SUSPECT_STRUCT_PTR;

typedef struct {
   unsigned short  arrestCharge;
   unsigned short  arrestStatus;
   char            arrestDate[DATE_LEN+1];
   char            arrestReport[ARREST_REPORT_LEN+1];
   } ARREST_STRUCT;

typedef struct {
   char            lastSeenLocation[LS_LOC_LEN+1];
   char            lastSeenWitness[LS_WITNESS_LEN+1];
   char            lastSeenDate[DATE_LEN+1];
   char            lastSeenStreet[ADDRESS_STREET_LEN+1];
   char            lastSeenCity[ADDRESS_CITY_LEN+1];
   char            lastSeenState[ADDRESS_STATE_LEN+1];
   char            lastSeenComment[COMMENT_LEN+1];
   } LAST_SEEN_STRUCT;

#endif

