/******************************************************************************
*                                                                             *
* .FILE:         alistbox.h                                                   *
*                                                                             *
* .DESCRIPTION:  List Box Sample Program:  Symbolic Definitions               *
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
#ifndef ALISTBOX_H
#define ALISTBOX_H

/***************************************************************************
| window ids - used by IWindow constructors (eg IStaticText, AHelloWindow) |
 **************************************************************************/
#define WND_MAIN         2000
#define WND_HELLO        2010
#define WND_INFO         2012
#define WND_STATUS       2011

/***************************************************************************
| string ids - used to relate resources to IStaticText and ITitle          |
 **************************************************************************/
#define STR_HELLO        1200
#define STR_INFO         1220
#define STR_CENTER       1230
#define STR_LEFT         1231
#define STR_RIGHT        1232

#define STR_LIST_ITEM1   1240
#define STR_LIST_ITEM2   1241
#define STR_LIST_ITEM3   1242
#define STR_LIST_ITEM4   1243
#define STR_LIST_ITEM5   1244

#define STR_SELECTEDITEMS 1250
#define STR_NUMBERITEMS 1251

/***************************************************************************
|  menu ids - used on relate command ID to Menu Items and Function Keys    |
 **************************************************************************/
#define MI_LISTBOX                1000
#define MI_ADD_ITEMS              1001
#define MI_READ_SEL_ITEMS         1002
#define MI_READ_ALL_ITEMS         1003
#define MI_EDIT                   1010
#define MI_SELECT_ALL             1011
#define MI_DESELECT_ALL           1012
#define MI_EXCEPTION              1020
#define MI_GEN_EXCPT              1021
#define MI_GEN_EXCPT_UNH          1022
#define MI_MSGBOX_TITLE           1023

#endif
