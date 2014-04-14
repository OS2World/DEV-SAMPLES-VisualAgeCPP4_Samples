
 **********************************************************************
 * DISCLAIMER OF WARRANTIES:                                          *
 *                                                                    *
 * The following enclosed code is sample code created by IBM          *
 * Corporation.  This sample code is not part of any standard IBM     *
 * product and is provided to you solely for the purpose of assisting *
 * you in the development of your applications.  The code is provided *
 * "AS IS", without warranty of any kind.  IBM shall not be liable    *
 * for any damages arising out of your use of the sample code, even   *
 * if they have been advised of the possibility of such damages       *
 *                                                                    *
 **********************************************************************

 NAME: CHKMARK - Samples PMCX Control

 FEATURE/CONCEPTS:
 Using Custom Controls with IRE

 DESCRIPTION:
The sample create a custom check mark box which can used with
IRE's PMCX control interface when designing dialogs.

 HOW TO BUILD THE SAMPLE FROM THE COMMAND LINE:
 From the chkmark directory simply type:

 nmake

HOW TO USE THE CUSTOM CONTROL WITH IRE

Open IRE and create a new dialog box. Under the Configure menu
select the "PMCX and Temporary Controls" menu item. In
the PMCX dialog box select Private Control then using find the chkmark.dll
using the Directories and Files list boxes. Select it and then select
the Add button. You should see in the Controls list 'ChkMark'
Select the save button. From the Control Menu select the
User Define menu item. You will see the chkmark control in the
list. Select it to add to the design.

