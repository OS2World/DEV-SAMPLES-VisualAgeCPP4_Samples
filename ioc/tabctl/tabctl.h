/******************************************************************************
* .FILE:         tabctl.h                                                     *
*                                                                             *
* .DESCRIPTION:  Tab Control Sample Program:  Symbolic Definitions            *
*                                                                             *
* .COPYRIGHT:                                                                 *
*    Licensed Material - Program-Property of IBM                              *
*    (C) Copyright IBM Corp. 1998 - All Rights Reserved                       *
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
#ifndef TABCTL_H
#define TABCTL_H

#define WND_MAIN                  1000
#define BM_CHEETAH                1002
#define WND_TABCONTROL            1010
#define STR_ENROLL                1020
#define STR_DATA                  1021
#define STR_PHOTO                 1022
#define STR_HELP_NOT_FOUND_TITLE  1200
#define STR_HELP_NOT_FOUND        1201
#define STR_ENROLL_ERROR_TITLE    1210
#define STR_ENROLL_ERROR_MSG      1211
#define STR_HTITLE                1300

/*------------------------------------------------------------------------|
| Enroll Page IDs                                                         |
|------------------------------------------------------------------------*/
#define WND_ENROLLPAGE            2100
#define WND_NAMESTATIC            2110
#define WND_FIRSTNAMESTATIC       2120
#define WND_FIRSTNAME             2130
#define WND_LASTNAMESTATIC        2140
#define WND_LASTNAME              2150
#define WND_CHEETAHSTATIC         2160
#define WND_CHEETAHLIST           2170

/*------------------------------------------------------------------------|
| Statistics Page IDs                                                     |
|------------------------------------------------------------------------*/
#define WND_DATAPAGE              2200
#define WND_INFO_SPONSOR_LABEL    2210
#define WND_INFO_SPONSOR          2211
#define WND_INFO_CHEETAH_LABEL    2220
#define WND_INFO_CHEETAH          2221
#define WND_INFO_SEX_LABEL        2230
#define WND_INFO_SEX_MALE_LABEL   2231
#define WND_INFO_SEX_MALE         2232
#define WND_INFO_SEX_FEMALE_LABEL 2233
#define WND_INFO_SEX_FEMALE       2234
#define WND_INFO_SEX              2235
#define WND_INFO_DOB_LABEL        2250
#define WND_INFO_DOB              2251
#define WND_INFO_WEIGHT_LABEL     2260
#define WND_INFO_WEIGHT           2261

/*------------------------------------------------------------------------|
| Photo Page IDs                                                          |
|------------------------------------------------------------------------*/
#define WND_PHOTOPAGE             2300
#define WND_PHOTO                 2310

/*------------------------------------------------------------------------|
| Button IDs                                                              |
|------------------------------------------------------------------------*/
#define ID_PREVIOUS               4000
#define ID_NEXT                   4010

/*------------------------------------------------------------------------|
| Help IDs                                                                |
|------------------------------------------------------------------------*/
#define HELP_TABLE                5000
#define SUBTABLE_MAIN             5010

#endif
