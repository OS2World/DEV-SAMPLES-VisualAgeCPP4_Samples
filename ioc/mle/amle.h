/******************************************************************************
* .FILE:         amle.h                                                       *
*                                                                             *
* .DESCRIPTION:  Multiline Edit Sample Program:    Symbolic Definitions       *
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
#ifndef AEDITORWINDOW_H
#define AEDITORWINDOW_H

                                         // this is defined in the OS/2
                                         // developer's toolkit
#define WM_USER             0x1000

/******************************************************************************/
/* constants                                                                  */
/******************************************************************************/
#define DEFAULT_FILE_SPEC   "*.cpp"

/******************************************************************************/
/* user define message id                                                     */
/******************************************************************************/
#define UWM_THREADEND       WM_USER

/******************************************************************************/
/* window ids                                                                 */
/******************************************************************************/
#define WND_MAIN            100          // frame window id
#define WND_MLE             101          // mle id

/******************************************************************************/
/* string table ids                                                           */
/******************************************************************************/
#define STR_FONTDLGT       2001
#define STR_OPENFAILED     2002
#define STR_OPENFAILEDTEXT 2003
#define STR_QUOTE          2004

//******************************************************************************
//* menu item ids                                                              *
//******************************************************************************
#define MI_FILE            1000
#define MI_OPEN            1001
#define MI_OPEN_THREAD2    1002
#define MI_SAVE            1003
#define MI_SAVEAS          1004

#define MI_EDIT            1010
#define MI_COPY            1011
#define MI_CUT             1012
#define MI_PASTE           1013

#define MI_OPTIONS         1020
#define MI_FONT            1021
#define MI_WORDWRAP        1022

#endif
