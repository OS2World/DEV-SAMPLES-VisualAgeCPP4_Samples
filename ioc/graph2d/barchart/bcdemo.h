#ifndef _BCDEMO_
#define _BCDEMO_

/*
-------------------------------------------------------------------------------
Copyright (c) IBM Corporation 1997.
All Rights Reserved.

Permission is granted to copy, use, modify, and merge this software into your
applications and to permit others to do any of the foregoing. You must include
this permission and copyright notice in all copies and modified versions of
this software. THIS SOFTWARE IS PROVIDED IN ITS 'AS IS' CONDITION.
IBM DISCLAIMS ANY LIABILITY OF ANY KIND FOR DAMAGES WHATSOEVER RESULTING
FROM THE USE OF THIS SOFTWARE.
-------------------------------------------------------------------------------
*/

/******************************************************************************
* .FILE:         bcdemo.h                                                     *
*                                                                             *
* .DESCRIPTION:  BarChart Sample Program:  Symbolic Definition                *
*                                                                             *
* .CLASSES:                                                                   *
*                                                                             *
* .NOTE: WE RECOMMEND USING A FIXED SPACE FONT TO LOOK AT THE SOURCE          *
*                                                                             *
******************************************************************************/

//**************************************************************************
// window IDs - used to construct main windows
//**************************************************************************
#define WND_MAIN              0x1000
#define WND_DRAW              0x8008



//************************************************************************
//MenuIDs - used to relate command ID to menu item
//************************************************************************
#define   ID_SETBCHARTPOSITION  101
#define   ID_SETBCHARTHEIGHT    102
#define   ID_SETBCHARTWIDTH       103
#define   ID_REPLACEATPOSITION  104

#define   ID_ADDLAST    105
#define   ID_ADDFIRST   106
#define   ID_ADDATPOSITION      107

#define   ID_REMOVEFIRST        108
#define   ID_REMOVELAST   109
#define   ID_REMOVEATPOSITION   110

#define   ID_GETBCHARTPOSITION  111
#define   ID_GETBCHARTHEIGHT    112
#define   ID_GETBCHARTWIDTH     113
#define   ID_SHOWATPOSITION  114

#define   STR_POSINVALID  0x1701
#define         STR_ISFULL    0x1702
#define         STR_ISEMPTY  0x1703
#define         STR_HEIGHT   0x1705
#define         STR_WIDTH    0x1706
#define         STR_POSITION    0x1707


#define   STR_ENTERXPOS  0x1708
#define         STR_ENTERYPOS   0x1709
#define         STR_ENTERPOS  0x1710
#define         STR_ENTERDATA    0x1711
#define         STR_ENTERHEIGHT   0x1712
#define         STR_ENTERWIDTH    0x1713
#define   STR_BARDATA    0x1714
#endif // _BCDEMO_
