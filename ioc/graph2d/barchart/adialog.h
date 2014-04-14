#ifndef _ADIALOG_
#define _ADIALOG_

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
* .FILE:         adialog.h                                                    *
*                                                                             *
* .DESCRIPTION:  BarChart Sample Program:  Symbolic Definition                *
*                                                                             *
* .CLASSES:                                                                   *
*                                                                             *
* .NOTE: WE RECOMMEND USING A FIXED SPACE FONT TO LOOK AT THE SOURCE          *
*                                                                             *
******************************************************************************/

//**************************************************************************
// window IDs - used to construct Dialog windows
//**************************************************************************
#define WND_TEXTDIALOG   0x1040
#define WND_MCCANVAS     0x1050
#define WND_STCANVAS     0x1060
#define WND_BUTTONS      0x1070




//**************************************************************************
// Dialog IDs - window IDs used in ATextDialog class                       *
//**************************************************************************
#ifndef DID_OK
#define DID_OK           0x0001
#endif
#ifndef DID_CANCEL
#define DID_CANCEL       0x0002
#endif
#define DID_FIRSTENTRY        0x1603
#define DID_FIRSTSTATIC       0x1604

#define DID_SECONDENTRY        0x1605
#define DID_SECONDSTATIC       0x1606
#endif // _ADIALOG_
