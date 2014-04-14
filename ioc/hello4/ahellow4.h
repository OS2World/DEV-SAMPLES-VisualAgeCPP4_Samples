/******************************************************************************
* .FILE:         ahellow4.h                                                   *
*                                                                             *
* .DESCRIPTION:  Hello World Sample Program Version 4:  Symbolic Definitions  *
*                                                                             *
* .CLASSES:                                                                   *
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
*                                                                             *
******************************************************************************/
#ifndef AHELLOWINDOW_H
#define AHELLOWINDOW_H

//**************************************************************************
// window IDs - used to construct windows, e.g. IStaticText, AHelloWindow  *
//**************************************************************************
#define WND_MAIN         0x1000

#define WND_HELLO        0x1010
#define WND_INFO         0x1020
#define WND_STATUS       0x1030
#define WND_TEXTDIALOG   0x1040
#define WND_MCCANVAS     0x1050
#define WND_STCANVAS     0x1060
#define WND_BUTTONS      0x1070


//**************************************************************************
// String IDs - used to relate resources to IStaticText and ITitle         *
//**************************************************************************
#define STR_HELLO        0x1200
#define STR_INFO         0x1220
#define STR_INFODLG      0x1221
#define STR_CENTER       0x1230
#define STR_LEFT         0x1231
#define STR_RIGHT        0x1232
#define STR_CENTERB      0x1240
#define STR_LEFTB        0x1241
#define STR_RIGHTB       0x1242

//**************************************************************************
// Menu IDs - used to relate command ID to menu items, buttons, and keys   *
//**************************************************************************
#define MI_ALIGNMENT     0x1500
#define MI_CENTER        0x1501
#define MI_LEFT          0x1502
#define MI_RIGHT         0x1503
#define MI_EDIT          0x1504
#define MI_TEXT          0x1505

//**************************************************************************
// Dialog IDs - window IDs used in ATextDialog class                       *
//**************************************************************************
#ifndef DID_OK
#define DID_OK           0x0001
#endif
#ifndef DID_CANCEL
#define DID_CANCEL       0x0002
#endif
#define DID_ENTRY        0x1603
#define DID_STATIC       0x1604

#endif
