/******************************************************************************
* .FILE:         aserver.h                                                    *
*                                                                             *
* .DESCRIPTION:  Dynamic Data Exchange Server Program: Symbolic Definitions   *
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
#define WND_SERVER       1000
#define WND_STATUS       1010
#define WND_TODOSTA      1011
#define WND_WORKSTA      1012
#define WND_DONESTA      1013
#define WND_DAREA        1020
#define WND_TODO         1021
#define WND_DONE         1022
#define WND_WORK         1023
#define WND_CAREA        1030
#define WND_MLE          1040

#define WIN_ICON         2001
#define WIN_OPTIONS      2002
#define WIN_START_CONV   2003
#define WIN_REQUEST_DATA 2004
#define WIN_END_CONV     2005
#define WIN_SERVER_INIT  2006

#define STR_HOTYES       3000
#define STR_HOTNO        3001

#define MI_APP           2018
#define MI_TOPIC         2019
#define MI_HOTLINKUPDATE_HOTWORK   2020
#define MI_HOTWORK       2021
#define MI_HOTLINKUPDATE_HOTDONE   2022
#define MI_HOTDONE       2023
#define MI_HOTLINKUPDATE_HOTTODO   2024
#define MI_HOTTODO       2025
#define MI_NEXTTODO      2070
#define MI_BUY_GIFTS     2026
#define MI_PAY_PHONE     2027
#define MI_PAY_TAXES     2028
#define MI_PAPERS        2029
#define MI_TRASH         2030
#define MI_WASH_CAR      2031
#define MI_WASH_DISH     2032
#define MI_TODO_COUNT    2033
#define MI_WORK_COUNT    2034
#define MI_DONE_COUNT    2035
#define MI_REQDATA       2036
#define MI_RETURNING     2037
#define MI_REQDATA2      2038
#define MI_UNABLE_PROVIDE 2039
#define MI_BEGIN_HOTLINK 2041
#define MI_FROM          2042
#define MI_BEGINDATA2    2043
#define MI_UNABLE_HANDLE 2044
#define MI_END_HOTLINK   2045
#define MI_DONEPOKE      2046
#define MI_POKEDATA      2047
#define MI_REQDATA3      2048
#define MI_REQDATA4      2049
#define MI_DATA          2050
#define MI_POKEDATA2     2051
#define MI_TO            2052
#define MI_ACCEPT        2053
#define MI_END_CONV      2054
#define MI_BY_SERVER     2055
#define MI_BY_CLIENT     2056
#define MI_BY_ERROR      2057
#define MI_END_CONV2     2058
