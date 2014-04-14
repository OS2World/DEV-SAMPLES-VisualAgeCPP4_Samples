/****************************************************************************
* LANCELOT SAMPLE PROGRAM - lancelot.h                                      *
*                                                                           *
* Header / Definitions file                                                 *
*                                                                           *
* DISCLAIMER OF WARRANTIES:                                                 *
*   The following [enclosed] code is sample code created by IBM             *
*   Corporation.  This sample code is not part of any standard IBM product  *
*   and is provided to you solely for the purpose of assisting you in the   *
*   development of your applications.  The code is provided "AS IS",        *
*   without warranty of any kind.  IBM shall not be liable for any damages  *
*   arising out of your use of the sample code, even if they have been      *
*   advised of the possibility of such damages.                             *
****************************************************************************/

#ifndef _LANCELOT_H_
#define _LANCELOT_H_
/************************************************************************/
/*                           Window and Control IDs                     */
/************************************************************************/
// Icons
#define ID_ICON_MAIN                    101
#define ID_ICON_QUERY                   102
#define ID_ICON_PROJECT                 103
#define ID_ICON_QUERY2                  104
#define ID_ICON_PERSON1                 105
#define ID_ICON_PERSON2                 106
#define ID_ICON_PERSON3                 107
#define ID_ICON_PERSON4                 108
#define ID_ICON_PERSON_UNKNOWN          109
#define ID_ICON_INFO                    115
#define ID_ICON_TIMECARD                116
#define ID_MAIN_TITLE                   120
#define ID_MAIN_CNR                     121
#define ID_MAIN_OFFSET_INFOAREA        6000
#define ID_MAIN_TOOLBAR                 122
#define ID_MAIN_FLYTEXT                 123
#define ID_MAIN_OFFSET_FLYTEXT         8000
#define ID_PERSONNEL_TITL               160
#define ID_PERSONNEL_CNR                161
#define ID_PERSONNEL_OFFSET_INFOAREA  10000
#define ID_PERSONNEL_TOOLBAR            162
#define ID_PERSONNEL_FLYTEXT            163
#define ID_PERSONNEL_OFFSET_FLYTEXT   13000
#define ID_PAGE_NEXT                    200
#define ID_PAGE_PREVIOUS                201
#define ID_PAGE_HELP                    202
#define ID_PAGE_UNDO                    203
#define ID_PAGE_SAVE                    204
#define ID_PAGE_QUERY                   205
#define ID_PAGE_ADD                     206
#define ID_PAGE_REMOVE                  207
#define ID_PAGE_CHANGE                  208

#define ID_MAIN_MAX_CNROBJECTS          250
#define ID_PERSONNEL_MAX_CNROBJECTS     250
#define ID_MAIN_CNR_TITLE_WIDTH         26
#define ID_PERSONNEL_CNR_TITLE_WIDTH    30

#define ID_MAIN                         1000
#define ID_MAIN_C                       1001
#define ID_MAIN_VIEW                    1100
#define ID_MAIN_VIEW_OPEN               1110
#define ID_MAIN_VIEW_OPEN_ICON          1111
#define ID_MAIN_VIEW_OPEN_TREE          1112
#define ID_MAIN_VIEW_OPEN_DETAILS       1113
#define ID_MAIN_VIEW_SELECT             1120
#define ID_MAIN_VIEW_SELECT_ALL         1121
#define ID_MAIN_VIEW_SELECT_DE          1122
#define ID_MAIN_VIEW_SORT               1130
#define ID_MAIN_VIEW_SORT_ASC           1131
#define ID_MAIN_VIEW_SORT_DESC          1132
#define ID_MAIN_VIEW_ARRANGE            1140
#define ID_MAIN_VIEW_CLOSE              1150
#define ID_MAIN_SELECTED                1200
#define ID_MAIN_SELECTED_OPEN           1205
#define ID_MAIN_SELECTED_DELETE         1206
#define ID_MAIN_OBJECT_POP_OPEN         1208
#define ID_MAIN_OBJECT_POP_DELETE       1209
#define ID_MAIN_FUNC_POP                1210
#define ID_MAIN_QUERY_POP               1230
#define ID_MAIN_VIEW_OPEN_ICON_BTN      1250
#define ID_MAIN_VIEW_OPEN_TREE_BTN      1251
#define ID_MAIN_VIEW_OPEN_DETAILS_BTN   1252
#define ID_MAIN_VIEW_SELECT_ALL_BTN     1253
#define ID_MAIN_VIEW_SELECT_DE_BTN      1254
#define ID_MAIN_VIEW_SORT_ASC_BTN       1255
#define ID_MAIN_VIEW_SORT_DESC_BTN      1256
#define ID_MAIN_VIEW_ARRANGE_BTN        1257
#define ID_MAIN_SELECTED_DELETE_BTN     1258

#define ID_MAIN_HELP                    1300
#define ID_MAIN_HELP_KEYS_HELP          1340

#define ID_MAIN_HELP_INDEX              1410
#define ID_MAIN_HELP_GENERAL            1420
#define ID_MAIN_HELP_USING              1430
#define ID_MAIN_HELP_KEYS               1440
#define ID_MAIN_HELP_PRODUCT            1450
#define ID_MAIN_HELP_KEYS_PANEL         1540

#define ID_MAIN_POP                     1800
#define ID_MAIN_POPULATE                1895

// Personnel menu bar
#define ID_PERSONNEL                         2000
#define ID_PERSONNEL_C                       2001

#define ID_PERSONNEL_VIEW                    2100
#define ID_PERSONNEL_VIEW_OPEN               2110
#define ID_PERSONNEL_VIEW_OPEN_ICON          2111
#define ID_PERSONNEL_VIEW_OPEN_TREE          2112
#define ID_PERSONNEL_VIEW_OPEN_DETAILS       2113
#define ID_PERSONNEL_VIEW_SELECT             2120
#define ID_PERSONNEL_VIEW_SELECT_ALL         2121
#define ID_PERSONNEL_VIEW_SELECT_DE          2122
#define ID_PERSONNEL_VIEW_SORT               2130
#define ID_PERSONNEL_VIEW_SORT_ASC           2131
#define ID_PERSONNEL_VIEW_SORT_DESC          2132
#define ID_PERSONNEL_VIEW_ARRANGE            2140
#define ID_PERSONNEL_VIEW_CLOSE              2150
#define ID_PERSONNEL_SELECTED                2200
#define ID_PERSONNEL_SELECTED_OPEN           2210
#define ID_PERSONNEL_SELECTED_DELETE         2220
#define ID_PERSONNEL_SELECTED_CREATE         2230
#define ID_PERSONNEL_SELECTED_TRANSFER       2240
#define ID_PERSONNEL_OBJECT_POP              2280
#define ID_PERSONNEL_OBJECT_POP_OPEN         2281
#define ID_PERSONNEL_OBJECT_POP_DELETE       2282
#define ID_PERSONNEL_OBJECT_POP_CREATE       2283
#define ID_PERSONNEL_OBJECT_POP_TRANSFER     2284
#define ID_PERSONNEL_DELETE_HELP             2276
#define ID_PERSONNEL_HELP                    2300
#define ID_PERSONNEL_HELP_KEYS_HELP          2340
#define ID_PERSONNEL_HELP_INDEX              2410
#define ID_PERSONNEL_HELP_GENERAL            2420
#define ID_PERSONNEL_HELP_USING              2430
#define ID_PERSONNEL_HELP_KEYS               2440
#define ID_PERSONNEL_HELP_PRODUCT            2450
#define ID_PERSONNEL_HELP_KEYS_PANEL         2540
#define ID_PERSONNEL_POP                     2800

#define ID_HELP_TABLE                        5010
#define ID_MAIN_SUBTABLE                     5020
#define ID_HELP_TABLE2                       5030
#define ID_PERSONNEL_SUBTABLE                5040
#define ID_HELP_TABLE3                       5050
#define ID_LINFOWINDOW_SUBTABLE              5060
#define STR_MAIN_TITLE                       5040
#define STR_MAIN_TITLE2                      5041
#define STR_PERSONNEL_TITLE                  5042
#define STR_QUERY_PERSONNEL_OBJECT           5043
#define STR_QUERY_PERSONNEL_DESC             5044
#define STR_CUSTOM_QUERY_DESC                5045
#define STR_ENTER_QUERY_NAME                 5046
#define STR_SAVED_QUERY_NAME                 5047
#define STR_REPLACED_QUERY_NAME              5048
#define STR_HELP_TITLE                       5050
#define STR_ASKUSER_TITLE                    5051
#define STR_HELP_NOT_FOUND                   5052
#define STR_PERSONNEL_DELETE_MSG             5053
#define STR_PERSONNEL_DELETED_MSG            5054
#define STR_PERSONNEL_INACTIVE_MSG           5055
#define STR_INCOMPLETE_DATA                  5056
#define STR_DB_EMPTY                         5057
#define STR_DB_NO_MATCH                      5058
#define STR_DB_ERROR                         5059
#define STR_DB_UNKNOWN_ERROR                 5060
#define STR_TRANSFER_MSG1                    5061
#define STR_TRANSFER_MSG2                    5062
#define STR_TRANSFER_MSG3                    5063
#define STR_TRANSFER_MSG4                    5064
#define STR_TRANSFER_MSG5                    5065
#define STR_TRANSFER_MSG6                    5066
#define STR_MAIN_DELETE_MSG1                 5067
#define STR_MAIN_DELETE_MSG2                 5068
#define STR_PERSON                           5069
#define STR_LASTNAME                         5070
#define STR_FIRSTNAME                        5071
#define STR_MI                               5072
#define STR_EMPLOYEENUM                      5073
#define STR_INTPHONE                         5074
#define STR_EXTPHONE                         5075
#define STR_INTADDR                          5076
#define STR_EXTADDR                          5077
#define STR_ROOM                             5078
#define STR_BUILDING                         5079
#define STR_DEPT                             5080
#define STR_TYPE                             5081
#define STR_MGRNUM                           5082
#define STR_TITLE                            5083
#define STR_DESC                             5084
#define STR_MGR                              5085
#define STR_OK                               5086
#define STR_CANCEL                           5087
#define STR_TIMECARD_NOSAVE                  5088
#define STR_NO_DB_ACCESS                     5090
#define STR_ABOUT_MSG                        5099

// LMainCnr identifiers
#define ID_MAIN_CNROBJECT               200
#define ID_PERSONNEL_CNROBJECT          500
#define ID_ASKUSER                      549

#define  ID_ICON                      10
#define  ID_NOTEBOOK                  12
#define  ID_TEXT                      13
#define  ID_PAGE                      14
#define  ID_PAGE_NO                   15
#define  ID_CHECK_BOX                 20

// PAGE
#define ID_BUTTONS_CANVAS              880
#define ID_CNR_CANVAS                  881
#define ID_SCROLL_CANVAS               882
#define ID_BUTTON_QUERY                883
#define ID_BUTTON_UNDO                 884
#define ID_BUTTON_HELP                 885
#define ID_BUTTON_GRID                 886
#define ID_BUTTON_ADD                  887
#define ID_BUTTON_CHANGE               888
#define ID_BUTTON_REMOVE               889
#define ID_BUTTON_NEXT                 890
#define ID_BUTTON_PREV                 891
#define ID_BUTTON_SAVE                 892
#define ID_ASKUSER_CANVAS              893
#define ID_ASKUSER_BUTTON_CANVAS       894
#define ID_ASKUSER_TEXT                895
#define ID_ASKUSER_ENTRY               896
#define ID_BUTTON_OK                   897
#define ID_BUTTON_CANCEL               898

// ACCOUNT PAGE
#define  ID_ACCOUNT_PAGE               30
#define  ID_ACCOUNT_PAGE_BUTTONS       31
#define  ID_ACCOUNT_PAGE_CNRBUTTONS    32
#define  ID_ACC_USERID_EF              33
#define  ID_ACC_NODESYS_EF             34
#define  ID_ACC_CNR                    35

// BADGE PAGE
#define  ID_BADGE_PAGE                 40
#define  ID_BADGE_PAGE_BUTTONS         41
#define  ID_BDG_BADGE_NUMBER_EF        42
#define  ID_BDG_ISSUE_DATE_EF          43
#define  ID_BDG_EXP_DATE_EF            44
#define  ID_BADGE_RANGE_1              45
#define  ID_BADGE_RANGE_2              46
#define  ID_BADGE_PAGE_RANGE_EF1       47
#define  ID_BADGE_PAGE_RANGE_EF2       48

// GENERAL PAGE
#define  ID_EMPLOYEE_TYPE_GROUP_BOX    50
#define  ID_GENERAL_PAGE               51
#define  ID_GENERAL_PAGE_BUTTONS       52
#define  ID_GENERAL_EMPL_TYPE          53
#define  ID_GEN_EMPLOYEE_ID_EF         54
#define  ID_GEN_LAST_NAME_EF           55
#define  ID_GEN_FIRST_NAME_EF          56
#define  ID_GEN_MIDDLE_INITIAL_EF      57
#define  ID_GEN_INT_PHONE_EF           58
#define  ID_GEN_EXT_PHONE_EF           59
#define  ID_GEN_ROOM_EF                60
#define  ID_GEN_BUILDING_EF            61
#define  ID_GEN_DEPT_EF                62
#define  ID_GEN_DIVISION_EF            63
#define  ID_GEN_MGR_EMP_ID_EF          64
#define  ID_GEN_MGR_NAME_EF            65
#define  ID_GEN_REG_BT                 66
#define  ID_GEN_MGR_BT                 67
#define  ID_GEN_SUP_BT                 68

// SKILL PAGE
#define  ID_SKILL_PAGE                 70
#define  ID_SKILL_PAGE_BUTTONS         71
#define  ID_SKILL_PAGE_CNRBUTTONS      72
#define  ID_SKI_CNR                    73
#define  ID_SKI_SKILL_EF               74
#define  ID_SKI_YRS_EXP_CBX            75
#define  ID_SKILL_PAGE_RANGE           76
#define  ID_SKILL_RANGE                77

// STATUS PAGE
#define  ID_STATUS_PAGE                80
#define  ID_STATUS_PAGE_BUTTONS        81
#define  ID_STATUS_PAGE_CNRBUTTONS     82
#define  ID_STA_ACTIVE_CB              83
#define  ID_STA_START_DATE_EF          84
#define  ID_STA_END_DATE_EF            85
#define  ID_STA_HOURLY_RATE_EF         86
#define  ID_STATUS_QUERY_ACTIVE        87
#define  ID_STATUS_QUERY_INACTIVE      88
#define  ID_STATUS_PAGE_ACTIVE         89
#define  ID_SKILL_ACTIVE               90
#define  ID_STATUS_PAGE_START          91
#define  ID_STATUS_START               92
#define  ID_STATUS_PAGE_END            93
#define  ID_STATUS_END                 94
#define  ID_STATUS_PAGE_PAY            95
#define  ID_STATUS_PAY                 96

// TASK page
#define  ID_TASK_PAGE                      90
#define  ID_TASK_PAGE_BUTTONS              91
#define  ID_TASK_PAGE_CNRBUTTONS           92
#define  ID_TSK_CNR                        93
#define  ID_TSK_TASK_EF                    94
#define  ID_TSK_BILLABLE_CB                95
#define  ID_TSK_DESCR_EF                   96

// WORK page
#define  ID_WORK_PAGE                      100
#define  ID_WORK_PAGE_BUTTONS              101
#define  ID_WORK_PAGE_CNRBUTTONS           102
#define  ID_WRK_CNR                        103
#define  ID_WRK_PROJECT_CBX                104
#define  ID_WRK_DESC_CBX                   105
#define  ID_WRK_TASK_CBX                   106

// PROJECT page
#define  ID_PROJECT_PAGE                   110
#define  ID_PROJECT_PAGE_BUTTONS           111
#define  ID_PROJECT_PAGE_CNRBUTTONS        112
#define  ID_PRJ_CNR                        113
#define  ID_PRJ_PROJ_EF                    114
#define  ID_PRJ_ACTIVE_CB                  115
#define  ID_PRJ_DESCR_EF                   116
#define  ID_WRK_RESP_MGR_CBX               117

// TIMECARD
#define  ID_TIMECARD_ENTRIES               17
#define  ID_TIMECARD_PAGE                  120
#define  ID_TIMECARD_PAGE_BUTTONS          121
#define  ID_TIMECARD_PAGE_SCROLL_BUTTONS   122
#define  ID_TIMECARD_VP                    123
#define  ID_TCD_DATE0_EF                   124
#define  ID_TCD_PROJ0_CBX                  125
#define  ID_TCD_TASK0_CBX                  126
#define  ID_TCD_HOURS0_EF                  127
#define  ID_TIMECARD_PIECHART              128
#define  ID_TIMECARD_CANVAS2               129
#define  ID_TIMECARD_DATE_HEADER           130
#define  ID_TIMECARD_PROJECT_HEADER        131
#define  ID_TIMECARD_TASK_HEADER           132
#define  ID_TIMECARD_HOUR_HEADER           133

// LInfoNotebook
#define ID_INFO_NOTEBOOK                   900
#define ID_INFO_NOTEBOOK_TAB_CHARS         13
#define ID_NOTEBOOK_HELP_PANEL             905

// LInfoWindow
#define ID_INFO_WINDOW                     950
#define STR_QUERY_INFO_WINDOW              951
#define STR_NEW_INFO_WINDOW                952
#define  ID_TAB_MENU                       3000
#define  ID_MAJOR_ITEM                     3100
#define  ID_MINOR_ITEM                     3200
#define  ID_NO_ITEM                        3300
#define  ID_HELP_MENU                      9000
#define  ID_ABOUT_ITEM                     9100

/************************************************************************/
/*                           String Table IDs                           */
/************************************************************************/

#define  PSZ_OBJECT                 300
#define  PSZ_VIEW                   310

// Default Page  buttons
#define  STR_BT_UNDO                410
#define  STR_BT_HELP                411
#define  STR_BT_NEXT                412
#define  STR_BT_PREV                413
#define  STR_CNR_ADD                415
#define  STR_CNR_REMOVE             416
#define  STR_CNR_CHANGE             417

// BADGE PAGE
#define  STR_BDG_BADGE_TAB           420
#define  STR_BDG_BADGE_NUMBER        421
#define  STR_BDG_ISSUE_DATE          422
#define  STR_BDG_EXP_DATE            423

// STATUS PAGE
#define  STR_STA_STATUS_TAB          430
#define  STR_STA_TITLE               431
#define  STR_STA_ACTIVE              432
#define  STR_STA_START               433
#define  STR_STA_END                 434
#define  STR_STA_HOURLY              435
#define  STR_STA_INACTIVE            436

// ACCOUNT PAGE
#define  STR_ACC_ACCOUNT_TAB         440
#define  STR_ACC_USERID              441
#define  STR_ACC_NODESYS             442
#define  STR_ACC_CURRENTUSERID       443

// SKILLS PAGE
#define  STR_SKI_SKILL_TAB           450
#define  STR_SKI_SKILL               451
#define  STR_SKI_YEARS_EXP           452
#define  STR_SKI_CURRENT_SKILLS      453

// GENERAL PAGE
#define  STR_GEN_GENERAL_TAB          550
#define  STR_GEN_EMPLOYEE_ID_TEXT     551
#define  STR_GEN_LAST_NAME_TEXT       552
#define  STR_GEN_FIRST_NAME_TEXT      553
#define  STR_GEN_MIDDLE_NAME_TEXT     554
#define  STR_GEN_INT_PHONE_TEXT       555
#define  STR_GEN_EXT_PHONE_TEXT       556
#define  STR_GEN_ROOM_TEXT            557
#define  STR_GEN_DEPT_TEXT            558
#define  STR_GEN_BLD_TEXT             559
#define  STR_GEN_DIV_TEXT             560
#define  STR_GEN_EMPLOYEE_TYPE_TEXT   561
#define  STR_GEN_REG_TEXT             562
#define  STR_GEN_MGR_TEXT             563
#define  STR_GEN_SUP_TEXT             564
#define  STR_GEN_MGR_EMP_NUM_TEXT     565
#define  STR_GEN_MGR_EMP_NAME_TEXT    566


// WORKING PROJECTS PAGE
//
#define  STR_WRK_PROJECT_TAB          570
#define  STR_WRK_PROJECT_TITLE        571
#define  STR_WRK_PROJECT              572
#define  STR_WRK_TASK                 573
#define  STR_WRK_PROJECT2             574
#define  STR_WRK_DESCRIPTION          575
#define  STR_WRK_TASKS                576
//
// PROJECTS PAGE
//
#define  STR_PRJ_PROJECT_TAB          580
#define  STR_PRJ_PROJ                 581
#define  STR_PRJ_ACTIVE               582
#define  STR_PRJ_DESCRIPTION          583
#define  STR_PRJ_RESP_MGR             584
#define  STR_PRJ_PROJECT2             585
#define  STR_PRJ_DESCRIPTION2         586
#define  STR_PRJ_MGR                  587
#define  STR_PRJ_ACTIVE2              588
//
// TASKS PAGE
//
#define  STR_TSK_TASKS_TAB            590
#define  STR_TSK_TASK                 591
#define  STR_TSK_BILLABLE             592
#define  STR_TSK_DESCR                593
#define  STR_TSK_CURR                 594
#define  STR_TSK_DESCR2               595
#define  STR_TSK_BILLABLE2            596

//
// TIMECARD PAGE
//
#define  STR_TCD_DATE                       600
#define  STR_TCD_DATE_HEADER                601
#define  STR_TCD_TIMECARD_TAB               602
#define  STR_TCD_WEEK_ENDING_TEXT           603
#define  STR_TCD_PROJECT_HEADER             604
#define  STR_TCD_TASK_HEADER                605
#define  STR_TCD_HOUR_HEADER                606
#define  STR_TCD_TOTAL_HOURS_TEXT           607
#define  STR_TCD_TOTAL_BILLABLE_HOURS_TEXT  608

// Generic page control messages
#define  STR_MSG_REMOVE                     700
#define  STR_MSG_CHANGE                     710
#define  STR_MSG_SKILL_REMOVE               720
#define  STR_MSG_ACCT_REMOVE                730
#define  STR_MSG_NOT_IN_DB                  740

// Picture string handler messages
#define  STR_MSG_ALPHA_NUMERIC              760
#define  STR_MSG_ALPHA                      761
#define  STR_MSG_NUMERIC                    762
#define  STR_MSG_PHONE                      763
#define  STR_MSG_DATE                       764
#define  STR_MSG_CURRENCY                   765

// Generic Controls - for all pages
#define DISPLAY_LIMIT               10
#define DISPLAY_LARGE               20
#define DISPLAY_TEXT                30
#define DISPLAY_PHONE               14
#define DISPLAY_VERY_SMALL          1
#define DISPLAY_LIMIT_DATE          8
#define DISPLAY_LIMIT_HOURS         2
#define DISPLAY_SMALL               4
#define DISPLAY_SMALL_RANGE         2

#endif
