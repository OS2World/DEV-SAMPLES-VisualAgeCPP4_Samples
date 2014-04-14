/******************************************************************************
* .FILE:         aclient.h                                                    *
*                                                                             *
* .DESCRIPTION:  Dynamic Data Exchange Client Program: Symbolic Definitions   *
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
#define WND_CLIENT          1000
#define WND_STATUS          1010
#define WND_TODOSTA         1011
#define WND_WORKSTA         1012
#define WND_DONESTA         1013
#define WND_WORKW           1020
#define WND_CAREA           1030
#define WND_MLE             1040

#define MI_CONV_OPTIONS     2001
#define MI_START_CONV       2002
#define MI_END_CONV         2003
#define MI_DATA_OPTIONS     2004
#define MI_REQUEST_DATA     2005
#define MI_POKE_DATA        2006
#define MI_HOTLINK_OPTIONS  2007
#define MI_BEGIN_HOTLINK    2008
#define MI_END_HOTLINK      2009
#define MI_BEGIN_SENT       2020
#define MI_APP              2021
#define MI_TOPIC            2022
#define MI_END_HOT_SENT     2023
#define MI_END_SENT         2024
#define MI_REQDATA_SENT     2025
#define MI_NEXTTODO         2026
#define MI_BEGIN_HOTLINK_HOTTODO_SENT   2027
#define MI_HOTTODO          2028
#define MI_BEGIN_HOTLINK_HOTWORK_SENT  2029
#define MI_HOTWORK          2030
#define MI_BEGIN_HOTLINK_HOTDONE_SENT  2031
#define MI_HOTDONE          2032
#define MI_POKEDATA_SENT    2033
#define MI_DONEPOKE         2034
#define MI_TODO_COUNT       2035
#define MI_WORK_COUNT       2036
#define MI_DONE_COUNT       2037
#define MI_DATA_HOTLINK     2038
#define MI_RECEIVED         2039
#define MI_DATA             2040
#define MI_TOPIC_END        2041
#define MI_IN_APP           2042
#define MI_BY_SERVER        2043
#define MI_BY_CLIENT        2044
#define MI_BY_ERROR         2045
#define MI_ACK_RECEIVED     2046

#define STR_HOTYES       3000
#define STR_HOTNO        3001
