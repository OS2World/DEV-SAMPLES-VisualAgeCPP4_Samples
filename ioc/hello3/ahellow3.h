/******************************************************************************
* .FILE:         ahellow3.h                                                   *
*                                                                             *
* .DESCRIPTION:  Hello World Sample Program Version 3:  Symbolic Definitions  *
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
#ifndef AHELLOWINDOW_H
#define AHELLOWINDOW_H

//**************************************************************************
// window IDs - used to construct windows, e.g. IStaticText, AHelloWindow  *
//**************************************************************************

#define WND_MAIN         1000

#define WND_HELLO        1010
#define WND_INFO         1020
#define WND_STATUS       1030


//**************************************************************************
// String IDs - used to relate resources to IStaticText and ITitle         *
//**************************************************************************
#define STR_HELLO        1200
#define STR_INFO         1220
#define STR_CENTER       1230
#define STR_LEFT         1231
#define STR_RIGHT        1232

//**************************************************************************
// Menu IDs - used to relate command ID to menu items, buttons, and keys   *
//**************************************************************************
#define MI_ALIGNMENT     1500
#define MI_CENTER        1501
#define MI_LEFT          1502
#define MI_RIGHT         1503

#endif
