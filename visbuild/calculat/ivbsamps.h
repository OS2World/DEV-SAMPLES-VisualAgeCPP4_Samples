#ifndef _IVBSAMPS_
  #define _IVBSAMPS_

/******************************************************************************
* .FILE:        ivbsamps.h                                                    *
*                                                                             *
* .DESCRIPTION: Declaration of the defines and macros for the Visual Builder  *
*                                                                             *
* .CLASSES:                                                                   *
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
#ifndef IVBSAMP_IMPORT
  #if defined(__WINDOWS__) && defined(__IMPORTLIB__)
    #define IVBSAMP_IMPORT  _Import
  #else
    #define IVBSAMP_IMPORT
  #endif
  #if defined(__OS2__)
    #define IVBSAMP_IMPORT  _Export
  #endif
#endif

#endif
