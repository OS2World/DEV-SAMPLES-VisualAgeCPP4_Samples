#ifndef TWOD_H
#define TWOD_H
/*
-------------------------------------------------------------------------------
Copyright (c) IBM Corporation 1996, 1997.
All Rights Reserved.

Permission is granted to copy, use, modify, and merge this software into your
applications and to permit others to do any of the foregoing. You must include
this permission and copyright notice in all copies and modified versions of
this software. THIS SOFTWARE IS PROVIDED IN ITS 'AS IS' CONDITION.
IBM DISCLAIMS ANY LIABILITY OF ANY KIND FOR DAMAGES WHATSOEVER RESULTING
FROM THE USE OF THIS SOFTWARE.
-------------------------------------------------------------------------------
*/

#define ICON_ID             11

//**************************************************************************
// window ids - used by IWindow constructors                               *
//**************************************************************************
#define ID_NULL             -1
#define WND_MAIN            0x1000         //Main Window ID
#define WND_DRAW            0x8008         //Drawing Area ID
#define WND_TOOLBAR1        0x1002         //Tool Bar ID
#define WND_TEXT            0x1003
#define STR_HELLO           0x1004
#define STR_INFO            0x1005
#define WND_TOOLBAR2        0x1006
#define ID_POPUP_MENU       0x1007
#define WND_PALLET          0x1008

// Defines for graphic pushbuttons.  Do not move these out of order!

#define PALLET_STYLE        0x3001
#define PALLET_NORM         0x3002
#define PALLET_ROTATE       0x3003
#define PALLET_SCALE        0x3004
#define PALLET_CLIP         0x3005
#define PALLET_AREA         0x3006
#define PALLET_LINE         0x3007
#define PALLET_DRAW         0x3008
#define PALLET_RECTANGLE    0x3009
#define PALLET_ELLIPSE      0x300A
#define PALLET_POLYLINE     0x300B
#define PALLET_POLYGON      0x300C
#define PALLET_CURVE        0x300D
#define PALLET_LOOP         0x300E
#define PALLET_TEXT         0x300F
#define PALLET_BITMAP       0x3010

#define PALLET_ARC          0x3011
#define PALLET_PIE          0x3012
#define PALLET_CHORD        0x3013
#define PALLET_CBEZIER      0x3014
#define PALLET_ACURVE       0x3015
#define PALLET_LBEZIER      0x3016
#define PALLET_ALOOP        0x3017
#define PALLET_ADD          0x3018
#define PALLET_SUBTRACT     0x3019
#define PALLET_MULTIPLY     0x301A
#define PALLET_XOR          0x301B

#define EAGLE               0x3200
#define TAJMAHAL            0x3201

// defines for the mouse pointers
#define POINTER_LINE        0x4001
#define POINTER_DRAW        0x4002
#define POINTER_RECTANGLE   0x4003
#define POINTER_ELLIPSE     0x4004
#define POINTER_POLYLINE    0x4005
#define POINTER_POLYGON     0x4006
#define POINTER_ARC         0x4007
#define POINTER_PIE         0x4008
#define POINTER_CHORD       0x4009
#define POINTER_ROTATE      0x400A
#define POINTER_SCALE       0x400B
#define POINTER_CLIP        0x400C
#define POINTER_TEXT        0x400D
#define POINTER_BITMAP      0x400E
// POINTER_NONE must be the last one
#define POINTER_NONE        0x400F

#define TOOLBAR_SYSTEM1      0x6201
#define LONG_OFFSET         100

// Defines for menu items.
#define ID_OPERATIONS       0x4001
#define ID_GRAPHICS         0x4002
#define ID_PENSTYLE         0x4003
#define ID_PEN              0x4004
#define ID_FPATTERN         0x4005
#define ID_LOOP             0x4006
#define ID_CURVE            0x4007
#define ID_FILL_MIXMODE     0x4008
#define ID_FILL_PAINT       0x4009
#define ID_FRAME_MIXMODE    0x400A
#define ID_FRAME_PAINT      0x400B

#define ID_FILEMENU                        2000
#define ID_VIEWMENU                        2001
#define ID_TOOLMENU                        2002
#define ID_FLCOLORS                        2003
#define ID_COLORS                          2004
#define ID_PATTERN                         2005
#define ID_LINETYPE                        2006
#define ID_LINEWIDTH                       2007
#define ID_STYLEMENU                       2008
#define ID_OPTIONSMENU                     2009
#define ID_SETBITMAP                       2010
#define ID_DRAWOPERATION                   2016
#define ID_FILL                            2017
#define ID_FRAME                           2018
#define ID_FILLANDFRAME                    2019
#define ID_PENTYPE_SOLID                   2101
#define ID_PENTYPE_INVISIBLE               2102
#define ID_PENTYPE_DASHDOT                 2103
#define ID_PENTYPE_SHORTDASH               2104
#define ID_PENTYPE_DOT                     2105
#define ID_PENTYPE_DASHDOUBLEDOT           2106
#define ID_PENTYPE_HAIRLINE                2107
#define ID_OK                              2109
#define ID_CANCEL                          2110
#define ID_RED                             2111
#define ID_GREEN                           2112
#define ID_BLUE                            2113
#define ID_PRINT                           2114
#define ID_CORRECTION                      3000
#define ID_PENWIDTH_1                      3001
#define ID_PENWIDTH_2                      3002
#define ID_PENWIDTH_3                      3003
#define ID_PENWIDTH_4                      3004
#define ID_PENWIDTH_5                      3005
#define ID_PENWIDTH_6                      3006
#define ID_PENWIDTH_7                      3007
#define ID_PENWIDTH_8                      3008
#define ID_PENWIDTH_9                      3009
#define ID_PENWIDTH_10                     3010
#define ID_CLEAR                           3011
#define ID_RESET                           3013
#define ID_SC_FRAME_TMODE                  3014
#define ID_IS_FRAME_TMODE                  3015
#define ID_DC_FRAME_TMODE                  3016
#define ID_ID_FRAME_TMODE                  3017
#define ID_SORD_FRAME_TMODE                3018
#define ID_SANDD_FRAME_TMODE               3019
#define ID_SXORD_FRAME_TMODE               3020
#define ID_ISANDD_FRAME_TMODE              3021
#define ID_ISORD_FRAME_TMODE               3022
#define ID_SANDID_FRAME_TMODE              3023
#define ID_SORID_FRAME_TMODE               3024
#define ID_IRSANDD_FRAME_TMODE             3025
#define ID_IRSORD_FRAME_TMODE              3026
#define ID_IRSXORD_FRAME_TMODE             3027
#define ID_ONE_FRAME_TMODE                 3028
#define ID_ZERO_FRAME_TMODE                3029
#define ID_SC_FILL_TMODE                   3030
#define ID_IS_FILL_TMODE                   3031
#define ID_DC_FILL_TMODE                   3032
#define ID_ID_FILL_TMODE                   3033
#define ID_SORD_FILL_TMODE                 3034
#define ID_SANDD_FILL_TMODE                3035
#define ID_SXORD_FILL_TMODE                3036
#define ID_ISANDD_FILL_TMODE               3037
#define ID_ISORD_FILL_TMODE                3038
#define ID_SANDID_FILL_TMODE               3039
#define ID_SORID_FILL_TMODE                3040
#define ID_IRSANDD_FILL_TMODE              3041
#define ID_IRSORD_FILL_TMODE               3042
#define ID_IRSXORD_FILL_TMODE              3043
#define ID_ONE_FILL_TMODE                  3044
#define ID_ZERO_FILL_TMODE                 3045
#define ID_CCOLORS                         3046
#define ID_PATTERN_SOLID                   3049
#define ID_PATTERN_BDIAGONAL               3050
#define ID_PATTERN_FDIAGONAL               3051
#define ID_PATTERN_CROSS                   3052
#define ID_PATTERN_DIAGONALCROSS           3053
#define ID_PATTERN_HORIZONTAL              3054
#define ID_PATTERN_VERTICAL                3055
#define ID_PATTERN_EAGLE                   3056
#define ID_PATTERN_TAJMAHAL                3057
#define ID_FPATTERN_SOLID                  3058
#define ID_FPATTERN_BDIAGONAL              3059
#define ID_FPATTERN_FDIAGONAL              3060
#define ID_FPATTERN_CROSS                  3061
#define ID_FPATTERN_DIAGONALCROSS          3062
#define ID_FPATTERN_HORIZONTAL             3063
#define ID_FPATTERN_VERTICAL               3064
#define ID_FPATTERN_EAGLE                  3065
#define ID_FPATTERN_TAJMAHAL               3066

// Printing menu defines
#define MI_MIS_PRINT          5000
#define MI_PREVIEWER          5001
#define MI_DIALOG             5002

// Menu defines for OS2
#define ID_OPTIONS_MENU         6000
#define ID_STYLES_MENU          6001
#define ID_FRAME_PAINT_MENU     6002
#define ID_MIX_MODE_MENU        6003
#define ID_PATTERN_MENU         6004
#define ID_FILL_PAINT_MENU      6005
#define ID_FILL_MIX_MODE_MENU   6006
#define ID_FILL_PATTERN_MENU    6007
#define ID_PEN_MENU             6008
#define ID_PEN_STYLE_MENU       6009
#define ID_PEN_WIDTH_MENU       6010
#define ID_DRAWING_OPERATION_MENU       6011
#define ID_GRAPHICS_MENU        6012
#define ID_CURVE_MENU           6013
#define ID_LOOP_MENU            6014
#define ID_OPERATIONS_MENU      6015
#define ID_AREA_MENU            6016
#define ID_PRINT_MENU           6017

// Sizes of the controls on the Palette dialog
#define PALLETDIALOG_SPACER        10 // spacing between controls
#define PALLETCANVAS_SQUARE         8 // 8x8 palette square
#define PALLETCANVAS_SQUAREWIDTH   17 // 17x17 pixels per square
#define PALLETCANVAS_SIZE          (PALLETCANVAS_SQUARE)*(PALLETCANVAS_SQUAREWIDTH)+1
#define COLORSELECTOR_WIDTH        69 // width of colour selector
#define COLORSELECTOR_HEIGHT       20 // height of colour selector
#define COLORSELECTOR_COLORS       51 // number of colours in colour selector
#define COLORSQUARE_WIDTH          40 // 40x40 pixels in sample colour square

#endif
