/******************************************************************************
* .FILE:         adialog6.h                                                   *
*                                                                             *
* .DESCRIPTION:  Hello World Sample Program Version 6: Symbolic Definitions   *
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
// window ids - used by IWindow constructors (eg IStaticText, AHelloWindow)*
//**************************************************************************
#define WND_MAIN         0x1000

#define WND_HELLO        0x1010
#define WND_INFO         0x1012
#define WND_STATUS       0x1011
#define WND_TEXTDIALOG   0x1013
#define WND_EARTH        0x1014
#define WND_CANVAS       0x8008
#define WND_MCCANVAS     0x8008
#define WND_STCANVAS     0x1015
#define WND_BUTTONS      0x1021
#define WND_HCANVAS      0x1040
#define WND_LISTBOX      0x1050
#define WND_STATUSCANVAS 0x1060
#define WND_TIME         0x1061
#define WND_DATE         0x1062
#define WND_HELLOPOPUP   0x1070
#define WND_EARTHPOPUP   0x1071

//******************************************************************************
// window ids - used by ANotebookWindow class (the names describe the purpose) *
//******************************************************************************
#define WND_NOTEBOOKFRAME       0x2000
#define WND_NOTEBOOK            0x8008
#define WND_EARTHPAGE           0x2100
#define WND_EARTHPAGEHEADING    0x2101
#define WND_STARSHEADING        0x2110
#define WND_STARSSETTINGS       0x2111
#define WND_TWINKLEBOX          0x2112
#define WND_BRIGHTBOX           0x2113
#define WND_LAYERSHEADING       0x2120
#define WND_LAYERSSPIN          0x2121
#define WND_EARTHCOLORHEADING   0x2130
#define WND_EARTHCOLORSETTINGS  0x2131
#define WND_CYANBUTTON          0x2132
#define WND_GREENBUTTON         0x2133
#define WND_WHITEBUTTON         0x2134
#define WND_YELLOWBUTTON        0x2135
#define WND_EARTHPAGEBUTTONS    0x2140
#define DID_EARTHAPPLY          0x2141
#define DID_EARTHRESET          0x2142
#define WND_DATETIMEPAGE        0x2150
#define WND_DATETIMEPAGEHEADING 0x2151
#define WND_DATEHEADING         0x2160
#define WND_DATESETTINGS        0x2161
#define WND_DATELONGBOX         0x2162
#define WND_DATESHORTBOX        0x2163
#define WND_DATEEXAMPLES        0x2164
#define WND_DATELONGEXAMPLE     0x2165
#define WND_DATESHORTEXAMPLE    0x2166
#define WND_TIMEHEADING         0x2170
#define WND_TIMESETTINGS        0x2171
#define WND_TIMELONGBOX         0x2172
#define WND_TIMESHORTBOX        0x2173
#define WND_TIMEEXAMPLES        0x2174
#define WND_TIMELONGEXAMPLE     0x2175
#define WND_TIMESHORTEXAMPLE    0x2176
#define WND_DATETIMEPAGEBUTTONS 0x2180
#define DID_DATETIMEAPPLY       0x2181
#define DID_DATETIMERESET       0x2182
#define DID_NOTEBOOKCLOSE       0x2183

//**************************************************************************
// string ids - used to relate resources to IStaticText and ITitle         *
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
#define STR_HELPB        0x1243
#define STR_HTITLE       0x1250
#define STR_HELP_NOT_FOUND 0x1251
#define STR_FONTDLGT     0x1261

//******************************************************************************
// string ids - used by ANotebookWindow class (the names describe the purpose) *
//******************************************************************************
#define STR_EARTHTAB            0x2200
#define STR_DATETIMETAB         0x2201
#define STR_EARTHPAGEHEADING    0x2210
#define STR_STARSHEADING        0x2220
#define STR_TWINKLEBOX          0x2221
#define STR_BRIGHTBOX           0x2222
#define STR_LAYERSHEADING       0x2230
#define STR_EARTHCOLORHEADING   0x2240
#define STR_CYAN                0x2241
#define STR_GREEN               0x2242
#define STR_WHITE               0x2243
#define STR_YELLOW              0x2244
#define STR_DATETIMEPAGEHEADING 0x2250
#define STR_DATEHEADING         0x2260
#define STR_DATELONGBOX         0x2261
#define STR_DATESHORTBOX        0x2262
#define STR_DATELONGEXAMPLE     0x2263
#define STR_DATESHORTEXAMPLE    0x2264
#define STR_TIMEHEADING         0x2270
#define STR_TIMELONGBOX         0x2271
#define STR_TIMESHORTBOX        0x2272
#define STR_TIMELONGEXAMPLE     0x2273
#define STR_TIMESHORTEXAMPLE    0x2274
#define STR_APPLY               0x2280
#define STR_RESET               0x2281
#define STR_CLOSE               0x2282
#define STR_READOK              0x2283
#define STR_SAVEDOK             0x2284

//**************************************************************************
// Menu IDs - used to relate command ID to menu items, buttons, and keys   *
//**************************************************************************
#define MI_ALIGNMENT     0x1500
#define MI_CENTER        0x1501
#define MI_LEFT          0x1502
#define MI_RIGHT         0x1503
#define MI_EDIT          0x1504
#define MI_TEXT          0x1505
#define MI_HELP          0x1510
#define MI_FONT          0x1507
#define MI_SETTINGS      0x1511
#define MI_READSETS      0x1512
#define MI_OPENSETS      0x1513
#define MI_SAVESETS      0x1508
#define MI_TWINKLE       0x1520
#define MI_BRIGHT        0x1521
#define MI_DIM           0x1522

//**************************************************************************
// Hello IDs - used for different language versions of Hello World text    *
//**************************************************************************
#define HI_WORLD         0x1700
#define HI_COUNT         8

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

//**************************************************************************
// Help IDs - used to relate resources to IHelp class                      *
//**************************************************************************
#define HELP_TABLE       0x1800
#define SUBTABLE_MAIN    0x1801
#define SUBTABLE_DIALOG  0x1802
#endif
