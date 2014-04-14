#ifndef DAREA_H
#define DAREA_H
/******************************************************************************
* .FILE:        darea.h                                                       *
*                                                                             *
* .DESCRIPTION: Header file for the Doodle DAREA                              *
*                                                                             *
* .CLASSES:     None                                                          *
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

//**************************************************************************
// window ids - used by IWindow constructors                               *
//**************************************************************************

// Tools Palette
#define BITMAP_ARROW          1
#define BITMAP_STYLECAN       2
#define BITMAP_ERASER         3
#define BITMAP_RECTANGLE      4
#define BITMAP_ELLIPSE        5
#define BITMAP_POLYGON        6
#define BITMAP_LINE           7
#define BITMAP_POLYLINE       8
#define BITMAP_FREEHAND       9

// Tools which are present in the DrawingArea
// But do not yet have Toolbar buttons
#define BITMAP_ARC            20
#define BITMAP_BITMAP         21
#define BITMAP_CHORD          22
#define BITMAP_PIE            23
#define BITMAP_TEXT           24

// Color Palette
#define BITMAP_PENCOLOR       40
#define BITMAP_FILCOLOR       41
#define BITMAP_REDFIL         42
#define BITMAP_GREENFIL       43
#define BITMAP_BLUEFIL        44

// Pen Width Palette
#define BITMAP_WIDTH          50

// Style Palette
#define BITMAP_STYLE          60
#define BITMAP_FRAMFILL       61
#define BITMAP_FRAMONLY       62
#define BITMAP_FILLONLY       63

// Title Palette
#define BITMAP_TTLTEXT        70

// Sample Bitmaps
#define BITMAP_SAMPLE1        80
#define BITMAP_SAMPLE2        81
#define BITMAP_SAMPLE3        82
#define BITMAP_SAMPLE4        83

// Sample Text Strings
#define STRING_SAMPLE1        1
#define STRING_SAMPLE2        2
#define STRING_SAMPLE3        3
#define STRING_SAMPLE4        4

// Defines for pointers
#define POINTER_MOVE         3001
#define POINTER_LINE         3002
#define POINTER_FREEHAND     3003
#define POINTER_RECTANGLE    3004
#define POINTER_ELLIPSE      3005
#define POINTER_POLYLINE     3006
#define POINTER_POLYGON      3007
#define POINTER_ARC          3008
#define POINTER_PIE          3009
#define POINTER_CHORD        3010
#define POINTER_TEXT         3011
#define POINTER_BITMAP       3012
#define POINTER_STYLECAN     3013
#define POINTER_ERASER       3014

#define LONG_OFFSET          100
#define FLYOVERTEXT_BLANK    3050


#define ICON_VB              4050
#endif

