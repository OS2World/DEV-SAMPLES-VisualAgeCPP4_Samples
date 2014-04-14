/* Filename:   chkmark.c						*/

/* This	module contains	an example installable control that can	be used	*/
/* within applications where additional	facilities are provided	that	*/
/* are not found within	the default controls of	OS/2 PM.		*/
/*									*/
/* For complete	details	regarding the PM Control Extensions (PMCX)	*/
/* consult the User's Guide.                                            */


/* Routines:   BOOL EXPENTRY ChkMarkRegister(HAB hAB);			*/
/*	       BOOL EXPENTRY ChkMarkQuery(PUSERINFO pUserInfo);		*/
/*	       MRESULT EXPENTRY	ChkMarkWndProc(HWND hWnd, ULONG	msg,	*/
/*					       MPARAM mp1, MPARAM mp2);	*/
/*	       MRESULT EXPENTRY	ChkMarkStyles(HWND hWnd, ULONG msg,	*/
/*					      MPARAM mp1, MPARAM mp2);	*/

/* --------------------------------------------------------------------------- */

/* IBM VisualAge C++ Professional, Version 4.0                                 */
/* Licensed Materials - Property of IBM                                        */
/* (C) Copyright IBM Corp. 1997, 1998. All Rights Reserved.                    */

/* --------------------------------------------------------------------------- */

/*******************************************************************************/
/*******************************************************************************/
/*		       DISCLAIMER OF WARRANTIES.			        */
/*******************************************************************************/
/*******************************************************************************/
/* DISCLAIMER:                                                                 */
/*   The following [enclosed] code is sample code created by IBM               */
/*   Corporation.  This sample code is not part of any standard IBM product    */
/*   and is provided to you solely for the purpose of assisting you in the     */
/*   development of your applications.  The code is provided 'AS IS',          */
/*   without warranty of any kind.  IBM shall not be liable for any damages    */
/*   arising out of your use of the sample code, even if they have been        */
/*   advised of the possibility of such damages.                               */
/*******************************************************************************/
/*******************************************************************************/


#pragma	title("Check Mark Control  --  Version 1.00 -- (ChkMark.C)")
#pragma	subtitle("  Check Mark Control Control DLL - Interface Definitions")

#pragma	info(noext)

#define	INCL_GPI		   /* Include OS/2 PM GPI Interface	*/
#define	INCL_WIN		   /* Include OS/2 PM Windows Interface	*/

static char *MODID = "@(#)chkmark.c:1.02";

#include <os2.h>
#include <string.h>

#include "..\pmcx.h"

#include "chkmark.h"


/* --- Control Data Structures ----------------------------------------	*/

typedef	struct _CHECKMARK	   /* cmrk */
   {
   HWND	   hwndOwner;		   /* Owner Window Handle		*/
   CHAR	   szText[512];		   /* Text Holder			*/
   BOOL	   fChecked;		   /* Check Mark State Flag		*/
   RECTL   rclChecked;		   /* Bitmap Rectangle Checked		*/
   RECTL   rclUnChecked;	   /* Bitmap Rectangle UnChecked	*/
   POINTL  ptlChkMark;		   /* Bitmap Rectangle UnChecked	*/
   POINTL  ptlText;		   /* Text Display Point		*/
   RECTL   rclText;		   /* Text Display Rectangle		*/
   RECTL   rcl;			   /* Bitmap Display Rectangle		*/
   HBITMAP hbm;			   /* Check Mark Bitmap	Handle		*/
   LONG	   aClr[3];		   /* Presentation Colours Array	*/
   } CHECKMARK ;

typedef	CHECKMARK *PCHECKMARK;

/* --- Module Prototype	Definitions -----------------------------------	*/

static VOID SetDefaultColours(HWND hWnd, PCHECKMARK pcmrk);
static LONG lGetPresParam(HWND hWnd, ULONG ulID1, ULONG	ulID2, LONG lDefault);

BOOL	EXPENTRY ChkMarkRegister(HAB hAB);
BOOL	EXPENTRY ChkMarkQuery(PUSERINFO	pUserInfo);
MRESULT	EXPENTRY ChkMarkWndProc(HWND hWnd, ULONG msg, MPARAM mp1, MPARAM mp2);
MRESULT	EXPENTRY ChkMarkStyles(HWND hWnd, ULONG	msg, MPARAM mp1, MPARAM	mp2);

#define	CLENpszClassname 10
static PSZ pszClassname	= "CheckMark";
static HMODULE hmodDLL;

#pragma	subtitle("   Check Mark Control - DLL Initialization/Termination Procedure")
#pragma	page( )

/* --- _Dll_InitTerm ----------------------------------- [ Public ] ---	*/
/*									*/
/*     This function is	used to	provide	the DLL	initialization and	*/
/*     termination.  The function is called by the C startup code	*/
/*     and allows the control to register itself and provide any	*/
/*     necessary startup.						*/
/*									*/
/*     This function is	designed for IBM C Set/2 Version 1.0,		*/
/*     IBM C Set++ Version 2.x and IBM VisualAge C++ Version 3.		*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     ULONG hModule; =	DLL Module Handle				*/
/*     ULONG fl;      =	Startup	/ Termination Flag			*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     _Dll_InitTerm =	0 : Error Return				*/
/*		     =	1 : Successful Startup / Termination		*/
/*									*/
/* --------------------------------------------------------------------	*/

ULONG _System _Dll_InitTerm(ULONG hModule, ULONG fl)

{
		       /* Determine if in startup or termination mode	*/
if ( fl	== 0 )
		       /* DLL being initialized, save the DLL module	*/
		       /* handle to allow the bitmap loading routines	*/
		       /* routines a means of loading the default	*/
		       /* bitmaps when required				*/
   hmodDLL = hModule;

return(1UL);
}
#pragma	subtitle("   Check Mark Control DLL - Control Initialization Function")
#pragma	page ( )

/* --- ChkMarkRegister --------------------------------- [ Public ] ---	*/
/*									*/
/*     This function is	used to	register the installable control class	*/
/*     with OS/2 Presentation Manager.	The registration must use the	*/
/*     USER_CWINDOWWORDS to reserve memory for the control to allow for	*/
/*     proper usage by Resource	Editor and for use by the control	*/
/*     dialog and window procedures.  The information for the control	*/
/*     containing the style, presentation parameters and control data	*/
/*     is pointed to by	a pointer that can be referenced by the		*/
/*     control's dialog and window procedure as required.  The memory   */
/*     for the structure is allocated and controlled through Resource	*/
/*     Editor.	 The control can reserve more memory for its use	*/
/*     by adding the memory required to	that of	the USER_CWINDOWWORDS	*/
/*     constant.							*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     HAB hAB;	= Application Anchor Block Handle			*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     ChkMarkRegister =  TRUE : Class Registration Successful		*/
/*		       = FALSE : Class Registration Failed		*/
/*									*/
/* --------------------------------------------------------------------	*/

BOOL EXPENTRY ChkMarkRegister(HAB hAB)

{
		       /* Register the control class with OS/2		*/
		       /* Presentation Manager and return registration	*/
		       /* result					*/

return(WinRegisterClass(hAB, pszClassname, ChkMarkWndProc, CS_SYNCPAINT	| CS_SIZEREDRAW, USER_CWINDOWWORDS));

}
#pragma	subtitle("   Check Mark Control DLL - Query Control Information Function")
#pragma	page ( )

/* --- ChkMarkQuery ------------------------------------ [ Public ] ---	*/
/*									*/
/*     This function is	used to	return to the caller information	*/
/*     regarding the installable control and its capabilities.	The	*/
/*     function	should return a	true value otherwise Resource		*/
/*     Editor will not register	the control as being usable.		*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     PUSERINFO pUserInfo; = User Information Pointer			*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     ChkMarkQuery =  TRUE : User Information Being Returned		*/
/*		    = FALSE : No User Information Available		*/
/*									*/
/* --------------------------------------------------------------------	*/

BOOL EXPENTRY ChkMarkQuery(PUSERINFO pUserInfo)

{
		       /* Complete the User Information	structure	*/
		       /* passed to the	function by Resource Editor	*/

		       /* Complete the version and number of control	*/
		       /* types.  In Version 1.00 of PMCX, only	one	*/
		       /* control type is used.				*/
pUserInfo->ulMajor = 2UL;
pUserInfo->ulMinor = 0UL;
		       /* Complete the author and control classname	*/

memcpy(pUserInfo->szAuthor,    "Prominare Inc.", 15);
memcpy(pUserInfo->szClassname, pszClassname, CLENpszClassname);
memcpy(pUserInfo->szName,      "ChkMark", 8);

		       /* Complete the default size and	style of the	*/
		       /* first	user control type			*/

pUserInfo->utDefined[0].cx	     = 25L;
pUserInfo->utDefined[0].cy	     = 10L;
pUserInfo->utDefined[0].flStyle	     = WS_VISIBLE;

		       /* Set the maximum amount of text control can	*/
		       /* accept including NULL	termination byte	*/

pUserInfo->utDefined[0].cMaxText     = CCHTEXTMAX;

		       /* Save the style's dialogue ID, type, control   */
		       /* data size and	count of style masks		*/

pUserInfo->utDefined[0].idDlg	     = DLG_CTRLUSER;
pUserInfo->utDefined[0].flOptions    = PMCXOPT_REFRESH;
pUserInfo->utDefined[0].ulType	     = UTYPE_PRIVATE;
pUserInfo->utDefined[0].cCtlData     = 0UL;
pUserInfo->utDefined[0].cMasks	     = 1UL;
pUserInfo->utDefined[0].flStyleType  = STYLETYPE_BITFLAGS;
pUserInfo->utDefined[0].stMasks[0].flStyleMask = CMS_CHECKED;
pUserInfo->utDefined[0].stMasks[0].idStyle     = IDS_CMS_CHECKED;

		       /* Save the description of the control		*/

memcpy(pUserInfo->utDefined[0].szDescription, "Check Mark", 11);

		       /* Return the success flag back to Resource	*/
		       /* Editor					*/
return(TRUE);
}
#pragma	subtitle("   Check Mark Control DLL - Control Window Procedure")
#pragma	page( )

/* --- lGetPresParam ----------------------------------	[ Private } ---	*/
/*									*/
/*     This function is	used to	retrieve a presentation	parameter	*/
/*     that may	be present.  If	the presentation parameter is not,	*/
/*     the default colour passed to the	function will be used.		*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     HWND  hWnd;     = Window	Handle					*/
/*     ULONG ulID1;    = Presentation Parameter	1 ID			*/
/*     ULONG ulID2;    = Presentation Parameter	2 ID			*/
/*     LONG  lDefault; = Default Colour					*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     lGetPresParam = Colour to Use					*/
/*									*/
/* --------------------------------------------------------------------	*/

LONG lGetPresParam(HWND	hWnd, ULONG ulID1, ULONG ulID2,	LONG lDefault)

{
HPS   hPS;			   /* Presentation Space Handle		*/
LONG  lClr;			   /* Presentation Parameter Colour	*/
ULONG ulID;			   /* Presentation Parameter ID		*/

if ( WinQueryPresParam(hWnd, ulID1, ulID2, &ulID, 4UL, (PVOID)&lClr, QPF_NOINHERIT | QPF_ID2COLORINDEX | QPF_PURERGBCOLOR) )
   return(lClr);
else
   if (	(lDefault >= SYSCLR_SHADOWHILITEBGND) && (lDefault <= SYSCLR_HELPHILITE) )
       return(WinQuerySysColor(HWND_DESKTOP, lDefault, 0L));
   else
       if ( (lClr = GpiQueryRGBColor(hPS = WinGetPS(hWnd), LCOLOPT_REALIZED, lDefault))	== GPI_ALTERROR	)
	   {
	   WinReleasePS(hPS);
	   return(lDefault);
	   }
       else
	   {
	   WinReleasePS(hPS);
	   return(lClr);
	   }
}
#pragma	subtitle("   Check Mark Control DLL - Default Colours Procedure")
#pragma	page( )

/* --- SetDefaultColours ------------------------------	[ Private ] ---	*/
/*									*/
/*     This function is	used to	set the	default	colours	that the	*/
/*     image button should use within the internal paint routines.	*/
/*     The colour can either be	a presentation parameter that has	*/
/*     been set	or it can be the default colour	as defined within	*/
/*     control.								*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     HWND	  hWnd;	 = Window Handle				*/
/*     PCHECKMARK pcmrk; = Check Mark Structure	Pointer			*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     Nothing								*/
/*									*/
/* --------------------------------------------------------------------	*/

static VOID SetDefaultColours(HWND hWnd, PCHECKMARK pcmrk)

{
		       /* Set up the colours that will be used within	*/
		       /* the painting of the control.	The colour	*/
		       /* indices are:					*/
		       /*						*/
		       /* 0 : Foreground (PP_FOREGROUND*)		*/
		       /* 1 : Background (PP_BACKGROUND*)		*/
		       /* 2 : Border (PP_BORDER*)			*/

pcmrk->aClr[0] = lGetPresParam(hWnd, PP_FOREGROUNDCOLOR, PP_FOREGROUNDCOLORINDEX, SYSCLR_OUTPUTTEXT);
pcmrk->aClr[1] = lGetPresParam(hWnd, PP_BACKGROUNDCOLOR, PP_BACKGROUNDCOLORINDEX, SYSCLR_FIELDBACKGROUND);
pcmrk->aClr[2] = lGetPresParam(hWnd, PP_BORDERCOLOR,	 PP_BORDERCOLORINDEX,	  SYSCLR_BUTTONDARK);
}
#pragma	subtitle("   Check Mark Control DLL - Display Point Calculation Procedure")
#pragma	page ( )

/* --- CalcDisplayPoints ------------------------------	[ Private ] ---	*/
/*									*/
/*     This function is	used to	calculate the display points for the	*/
/*     installed control.						*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     HWND	  hWnd;	 = Control Window Handle			*/
/*     PCHECKMARK pcmrk; = Control Data	Structure Pointer		*/
/*     LONG	  cx;	 = control Width				*/
/*     LONG	  cy;	 = Control Height				*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     Nothing								*/
/*									*/
/* --------------------------------------------------------------------	*/

static VOID CalcDisplayPoints(HWND hWnd, PCHECKMARK pcmrk, LONG	cx, LONG cy)

{
BITMAPINFOHEADER bmp;		   /* Bitmap Information Holder		*/
HPS		 hPS;		   /* Presentation Space Handle		*/
FONTMETRICS	 fm;		   /* Font Metrics			*/

GpiQueryBitmapParameters(pcmrk->hbm, &bmp);

GpiQueryFontMetrics(hPS	= WinGetPS(hWnd), sizeof(FONTMETRICS), &fm);

WinReleasePS(hPS);
pcmrk->rclChecked.xRight = bmp.cx;
pcmrk->rclChecked.xLeft	= (bmp.cx = (USHORT)(bmp.cx / 2));

pcmrk->rclUnChecked.xRight = bmp.cx;
pcmrk->rclChecked.yTop = pcmrk->rclUnChecked.yTop = bmp.cy;

pcmrk->ptlChkMark.y = cy / 2L -	bmp.cy / 2L;

pcmrk->ptlText.x = bmp.cx + fm.lAveCharWidth / 2L;
pcmrk->ptlText.y = (cy / 2L) - (fm.lMaxBaselineExt / 2L) + fm.lMaxDescender;

pcmrk->rclText.xLeft  =	bmp.cx;
pcmrk->rclText.xRight =	pcmrk->rcl.xRight = cx;
pcmrk->rclText.yTop   =	pcmrk->rcl.yTop	  = cy;

}
#pragma	subtitle("   Check Mark Control DLL - Check Mark Window Procedure")
#pragma	page ( )

/* --- ChkMarkWndProc ---------------------------------	[ Private ] ---	*/
/*									*/
/*     This function is	used to	handle the messages sent to the		*/
/*     installed control.  The window procedure	is designed to		*/
/*     allow for multiple instances and	to be totally re-entrant.	*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     HWND   hWnd; = Window Handle					*/
/*     ULONG  msg;  = PM Message					*/
/*     MPARAM mp1;  = Message Parameter	1				*/
/*     MPARAM mp2;  = Message Parameter	2				*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     ChkMarkWndProc =	Message	Handling Result				*/
/*									*/
/* --------------------------------------------------------------------	*/

MRESULT	EXPENTRY ChkMarkWndProc(HWND hWnd, ULONG msg, MPARAM mp1, MPARAM mp2)

{
HPS		 hPS;		   /* Presentation Space Handle		*/
PCREATESTRUCT	 pcrst;		   /* Create Structure Pointer		*/
PCHECKMARK	 pcmrk;		   /* Check Mark Structure Pointer	*/
PWNDPARAMS	 pwprm;		   /* Window Parameters	Pointer		*/

switch ( msg )
   {

/************************************************************************/
/************************************************************************/
/*									*/
/* Part	1: Control creation						*/
/*									*/
/************************************************************************/
/************************************************************************/

   /*********************************************************************/
   /*  Creation	sequence						*/
   /*********************************************************************/

   case	WM_CREATE :
		       /* Create a private control data	area		*/

       DosAllocMem((PPVOID)(PVOID)&pcmrk, 4096UL, PAG_READ | PAG_WRITE | PAG_COMMIT);

		       /* Save the address of the text string pointer	*/
		       /* in the control's reserved memory to allow it  */
		       /* to be	referenced as required by the control	*/

       WinSetWindowPtr(hWnd, QWW_CDATA,	(PVOID)pcmrk);

		       /* Get the control's creation structure address  */
		       /* to copy the default text of the control to	*/
		       /* the memory in	the heap			*/

       pcrst = (PCREATESTRUCT)PVOIDFROMMP(mp2);

       pcmrk->hwndOwner	= pcrst->hwndOwner;

       if ( pcrst->flStyle & CMS_CHECKED )
	   pcmrk->fChecked = TRUE;

		       /* Set up the colours that will be used within	*/
		       /* the painting of the control			*/

       SetDefaultColours(hWnd, pcmrk);

       if ( pcrst->pszText )
       strcpy(pcmrk->szText, pcrst->pszText);
       pcmrk->hbm = GpiLoadBitmap(hPS =	WinGetPS(hWnd),	hmodDLL, IDB_CHECKMARKS, 0L, 0L);

       WinReleasePS(hPS);

       CalcDisplayPoints(hWnd, pcmrk, pcrst->cx, pcrst->cy);
       break;

/************************************************************************/
/************************************************************************/
/*									*/
/* Part	2: Sizing and Placement						*/
/*									*/
/************************************************************************/
/************************************************************************/

   /*********************************************************************/
   /*  Control being resized						*/
   /*********************************************************************/

   case	WM_SIZE	:
       CalcDisplayPoints(hWnd, (PCHECKMARK)WinQueryWindowPtr(hWnd, QWW_CDATA),
			 (LONG)(SHORT)SHORT1FROMMP(mp2), (LONG)(SHORT)SHORT2FROMMP(mp2));
       break;

/************************************************************************/
/************************************************************************/
/*									*/
/* Part	3: Focus/Enable	Management					*/
/*									*/
/************************************************************************/
/************************************************************************/


/************************************************************************/
/************************************************************************/
/*									*/
/* Part	4: Text	Input/Output and Presentation Parameter	Interface	*/
/*									*/
/************************************************************************/
/************************************************************************/

   /*********************************************************************/
   /*  Process window parameters setting				*/
   /*********************************************************************/

   case	WM_SETWINDOWPARAMS :

		       /* Get the address for the windows parameters	*/
		       /* structure					*/

       pwprm = (PWNDPARAMS)PVOIDFROMMP(mp1);

		       /* Check	to see if the text for the control is	*/
		       /* being	set					*/

       if ( pwprm->fsStatus & WPM_TEXT )
	   {
		       /* Get the address of the control info from the	*/
		       /* control's reserved memory                     */

	   pcmrk = (PCHECKMARK)WinQueryWindowPtr(hWnd, QWW_CDATA);

		       /* Check	to see if any text is being set		*/

	   if (	pwprm->cchText )

		       /* Check	to make	sure that the text that	is to	*/
		       /* be set is not	greater	than the memory		*/
		       /* allocated					*/

	       if ( pwprm->cchText > 511 )
		   {
		   memcpy(pcmrk->szText, pwprm->pszText, 511);
		   pcmrk->szText[511] =	(CHAR)0;
		   }
	       else
		   memcpy(pcmrk->szText, pwprm->pszText, pwprm->cchText	+ 1);
	   else
		       /* No text is being set,	clear any existing text	*/

	       pcmrk->szText[0]	= (CHAR)0;
	   return(MRFROMLONG(TRUE));
	   }
       break;

   /*********************************************************************/
   /*  Process window parameters query					*/
   /*********************************************************************/

   case	WM_QUERYWINDOWPARAMS :

		       /* Get the address for the windows parameters	*/
		       /* structure					*/

       pwprm = (PWNDPARAMS)PVOIDFROMMP(mp1);

		       /* Determine the	type of	query			*/

       if ( pwprm->fsStatus & (WPM_TEXT	| WPM_CCHTEXT) )
	   {
		       /* Get the address of the control info from the	*/
		       /* control's reserved memory                     */

	   pcmrk = (PCHECKMARK)WinQueryWindowPtr(hWnd, QWW_CDATA);

		       /* Copy the text	from the string	to the		*/
		       /* structure					*/

	   strcpy(pwprm->pszText, pcmrk->szText);

		       /* Place	the length the string within the	*/
		       /* structure					*/

	   pwprm->cchText = (ULONG)strlen(pcmrk->szText);
	   }
       else
	   if (	pwprm->fsStatus	& WPM_TEXT )
	       {
		       /* Get the address of the control info from the	*/
		       /* control's reserved memory                     */

	       pcmrk = (PCHECKMARK)WinQueryWindowPtr(hWnd, QWW_CDATA);

		       /* Copy the text	from the string	to the		*/
		       /* structure					*/

	       strcpy(pwprm->pszText, pcmrk->szText);
	       }
	   else
	       if ( pwprm->fsStatus & WPM_CCHTEXT )
		   {
		       /* Text length being asked for, get the address	*/
		       /* of the text string stored in the heap		*/

		   pcmrk = (PCHECKMARK)WinQueryWindowPtr(hWnd, QWW_CDATA);

		       /* Place	the length the string within the	*/
		       /* structure					*/

		   pwprm->cchText = (ULONG)strlen(pcmrk->szText);
		   }
	       else
		   return(WinDefWindowProc(hWnd, msg, mp1, mp2));
       return(MRFROMLONG(TRUE));

   /*********************************************************************/
   /*  Presentation parameters changed,	record the changes		*/
   /*********************************************************************/

   case	WM_PRESPARAMCHANGED :

		       /* Get the address of the control info from the	*/
		       /* control's reserved memory                     */

       pcmrk = (PCHECKMARK)WinQueryWindowPtr(hWnd, QWW_CDATA);

		       /* Get the new presentation parameter colour for	*/
		       /* the presentation parameter that has changed.	*/
		       /* Get the colour as a RGB value	so as to be	*/
		       /* able to get an exact value and not an		*/
		       /* approximation	which could happen if the	*/
		       /* presentation parameter was set as a RGB but	*/
		       /* queried as an	index.	When WinQueryPresParam	*/
		       /* returns a 0, it indicates that no		*/
		       /* presentation parameter set and the default	*/
		       /* colours should be used.			*/

       switch (	LONGFROMMP(mp1)	)
	   {
	   case	0 :
	       SetDefaultColours(hWnd, pcmrk);
	       break;

	   case	PP_FOREGROUNDCOLOR :
	   case	PP_FOREGROUNDCOLORINDEX	:
	       pcmrk->aClr[0] =	lGetPresParam(hWnd, PP_FOREGROUNDCOLOR,	PP_FOREGROUNDCOLORINDEX, SYSCLR_OUTPUTTEXT);
	       break;

	   case	PP_BACKGROUNDCOLOR :
	   case	PP_BACKGROUNDCOLORINDEX	:
	       pcmrk->aClr[1] =	lGetPresParam(hWnd, PP_BACKGROUNDCOLOR,	PP_BACKGROUNDCOLORINDEX, SYSCLR_DIALOGBACKGROUND);
	       break;

	   case	PP_BORDERCOLOR :
	   case	PP_BORDERCOLORINDEX :
	       pcmrk->aClr[2] =	lGetPresParam(hWnd, PP_BORDERCOLOR, PP_BORDERCOLORINDEX, SYSCLR_BUTTONDARK);
	       break;

	   default :
	       return(0L);
	   }
		   /* Invalidate the button to force to	use the	    */
		   /* new colours just set or removed		    */

       WinInvalidateRect(hWnd, (PRECTL)NULL, TRUE);
       break;

/************************************************************************/
/************************************************************************/
/*									*/
/* Part	5: Mouse interface						*/
/*									*/
/************************************************************************/
/************************************************************************/

   /*********************************************************************/
   /*  Hit test	request							*/
   /*********************************************************************/

   case	WM_HITTEST :
		       /* Mouse	being passed over the control, imply	*/
		       /* that the control is transparent to the	*/
		       /* system					*/

       return(MRFROMLONG(HT_TRANSPARENT));

/************************************************************************/
/************************************************************************/
/*									*/
/* Part	6: Keyboard interface						*/
/*									*/
/************************************************************************/
/************************************************************************/

/************************************************************************/
/************************************************************************/
/*									*/
/* Part	7: Control Message interface					*/
/*									*/
/************************************************************************/
/************************************************************************/

   /*********************************************************************/
   /*  Set check							*/
   /*********************************************************************/

   case	CKM_SETCHECK :
		       /* Get the address of the control info from the	*/
		       /* control's reserved memory                     */

       pcmrk = (PCHECKMARK)WinQueryWindowPtr(hWnd, QWW_CDATA);
       pcmrk->fChecked = (BOOL)LONGFROMMP(mp1);
       WinInvalidateRect(hWnd, (PRECTL)NULL, TRUE);
       break;

/************************************************************************/
/************************************************************************/
/*									*/
/* Part	8: Painting							*/
/*									*/
/************************************************************************/
/************************************************************************/

   /*********************************************************************/
   /*  Erase control background						*/
   /*********************************************************************/

   case	WM_ERASEBACKGROUND :
       return(MRFROMLONG(TRUE));

   /*********************************************************************/
   /*  Control painting							*/
   /*********************************************************************/

   case	WM_PAINT :
		       /* Get the address of the control info from the	*/
		       /* control's reserved memory                     */

       pcmrk = (PCHECKMARK)WinQueryWindowPtr(hWnd, QWW_CDATA);

		       /* Get the presentation space for the control	*/
		       /* and set the colour table to RGB mode		*/

       GpiCreateLogColorTable(hPS = WinBeginPaint(hWnd,	(HPS)NULL, (PRECTL)NULL), 0L, LCOLF_RGB, 0L, 0L, (PLONG)NULL);

       WinFillRect(hPS,	&pcmrk->rcl, pcmrk->aClr[1]);

       WinDrawBitmap(hPS, pcmrk->hbm, pcmrk->fChecked ?	&pcmrk->rclChecked : &pcmrk->rclUnChecked,
		     &pcmrk->ptlChkMark, 0L, 0L, DBM_IMAGEATTRS	| DBM_NORMAL);

       GpiCharStringPosAt(hPS, &pcmrk->ptlText,	&pcmrk->rclText, CHS_CLIP, (LONG)strlen(pcmrk->szText),	pcmrk->szText, NULL);

       WinEndPaint(hPS);
       break;

/************************************************************************/
/************************************************************************/
/*									*/
/* Part	9: Control being destroyed					*/
/*									*/
/************************************************************************/
/************************************************************************/

   /*********************************************************************/
   /*  Control being destroy, perform necessary	cleanup			*/
   /*********************************************************************/

   case	WM_DESTROY :
		       /* Get the address of the control info from the	*/
		       /* control's reserved memory                     */

       pcmrk = (PCHECKMARK)WinQueryWindowPtr(hWnd, QWW_CDATA);

		       /* Delete the check mark	bitmap			*/

       GpiDeleteBitmap(pcmrk->hbm);

		       /* Release the heap allocated for use by	the	*/
		       /* control					*/

       DosFreeMem((PVOID)pcmrk);
       break;
		       /* Default message processing			*/
   default :
       return(WinDefWindowProc(hWnd, msg, mp1, mp2));
   }

return(0L);
}
#pragma	subtitle("   Check Mark Control DLL - Control Styles Dialogue Procedure")
#pragma	page ( )

/* --- ChkMarkStyles --------------------------------------------------	*/
/*									*/
/*     This function is	used for the custom control's styles dialogue   */
/*     box procedure.							*/
/*									*/
/*     When the	dialogue is invoked from Resource Editor, the		*/
/*     address of the user style information is	contained in message	*/
/*     parameter 2.  The dialogue is responsible for saving the		*/
/*     address.	 The best method to do this is to save the pointer	*/
/*     in the dialogue's reserved memory where it can be retrieved as   */
/*     needed.								*/
/*									*/
/*     Upon Entry:							*/
/*									*/
/*     HWND   hWnd; = Dialog Window Handle				*/
/*     ULONG  msg;  = PM Message					*/
/*     MPARAM mp1;  = Message Parameter	1				*/
/*     MPARAM mp2;  = Message Parameter	2				*/
/*									*/
/*     Upon Exit:							*/
/*									*/
/*     ChkMarkStyles = Message Handling	Result				*/
/*									*/
/* --------------------------------------------------------------------	*/

MRESULT	EXPENTRY ChkMarkStyles(HWND hWnd, ULONG	msg, MPARAM mp1, MPARAM	mp2)

{
PUSERSTYLE   pust;		   /* User Style Pointer		*/
SWP	     swp;		   /* Screen Window Position Holder	*/

switch ( msg )
   {
		       /* Perform dialogue initialization		*/
   case	WM_INITDLG :
		       /* Save the pointer to user style information	*/
		       /* within the dialog's reserved memory           */

       WinSetWindowPtr(hWnd, QWL_USER, (PVOID)mp2);

		       /* Get the pointer to the user style information	*/

       if ( (pust = (PUSERSTYLE)mp2) !=	NULL )
	   {
		       /* Set the text,	ID symbol and value for	the	*/
		       /* control					*/

	   WinSetDlgItemText(hWnd, EF_TEXT, pust->pszText);
	   pust->pfnSetSymbolID(hWnd, IDBX_SYMBOLVALUE,	pust);

	   if (	pust->flStyle &	CMS_CHECKED )
	       WinSendDlgItemMsg(hWnd, CB_CMS_CHECKED, BM_SETCHECK, MPFROMSHORT(TRUE), 0L);

	   if (	pust->flStyle &	WS_VISIBLE )
	       WinSendDlgItemMsg(hWnd, CB_VISIBLE, BM_SETCHECK,	MPFROMSHORT(TRUE), 0L);

	   if (	pust->flStyle &	WS_GROUP )
	       WinSendDlgItemMsg(hWnd, CB_GROUP, BM_SETCHECK, MPFROMSHORT(TRUE), 0L);

	   if (	pust->flStyle &	WS_DISABLED )
	       WinSendDlgItemMsg(hWnd, CB_DISABLED, BM_SETCHECK, MPFROMSHORT(TRUE), 0L);

	   if (	pust->flStyle &	WS_TABSTOP )
	       WinSendDlgItemMsg(hWnd, CB_TABSTOP, BM_SETCHECK,	MPFROMSHORT(TRUE), 0L);
	   }
		       /* Centre dialog	on the screen			*/

       WinQueryWindowPos(hWnd, (PSWP)&swp);
       WinSetWindowPos(hWnd, HWND_TOP,
		       (WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN) - swp.cx) /	2L,
		       (WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN) - swp.cy) /	2L,
		       0L, 0L, SWP_MOVE);
       break;
		       /* Process push button selections		*/
   case	WM_COMMAND :
       switch (	SHORT1FROMMP(mp1) )
	   {
		       /* Font & colours push button selected		*/

	   case	DID_FONTCLR :

		       /* Get the pointer to the user style information	*/

	       if ( (pust = PDATAFROMDLG(hWnd))	!= NULL	)

		       /* Get the address of the look up function from	*/
		       /* user style information structure and display	*/
		       /* the dialog.  The value selected within the	*/
		       /* dialogue will	be automatically placed	within	*/
		       /* the required entry fields			*/

		   pust->pfnGetFontClr(hWnd);
	       break;
		       /* Bidi push button selected			*/

	   case	DID_BIDI :

		       /* Get the pointer to the user style information	*/

	       if ( (pust = PDATAFROMDLG(hWnd))	!= NULL	)

		       /* Get the address of the look up function from	*/
		       /* user style information structure and display	*/
		       /* the dialog.  The value selected within the	*/
		       /* dialogue will	be automatically placed	within	*/
		       /* the required entry fields			*/

		   pust->pfnGetBidi(hWnd);
	       break;
		       /* Enter	push button selected get the		*/
		       /* definitions for the control			*/
	   case	DID_OK :

		       /* Get the pointer to the user style information	*/

	       if ( (pust = PDATAFROMDLG(hWnd))	!= NULL	)
		   {
		       /* Get the address of the CUA compliance		*/
		       /* function from	the user style information	*/
		       /* structure.  The function will	check the text	*/
		       /* for CUA compliance according to index	value	*/
		       /* selected.  A return value of TRUE from the	*/
		       /* compliance function indicates	that the text	*/
		       /* entered is acceptable.  Conversely, a	FALSE	*/
		       /* return value indicates that text is non-	*/
		       /* compliant.  In this case, the	dialogue should	*/
		       /* not be exited	from and the values within the	*/
		       /* the entry fields should not be saved.		*/

		   if (	!pust->pfnCUACheck(hWnd, EF_TEXT, CUACHK_CAPS) )
		       break;

		       /* Get the address of the symbol	validation	*/
		       /* function from	the user style information	*/
		       /* structure.  The function will	validate the	*/
		       /* symbol and will check	for duplications of	*/
		       /* values.  A return value of TRUE from the	*/
		       /* validation function indicates	that the symbol	*/
		       /* and value are	acceptable.  Conversely, a	*/
		       /* FALSE	return value indicates that symbol or	*/
		       /* value	was not	acceptable.  In	this case,	*/
		       /* the dialogue should not be exited from and	*/
		       /* the values within the	entry fields should not	*/
		       /* be saved.					*/

		   if (	!pust->pfnGetSymbolID(hWnd, IDBX_SYMBOLVALUE, pust) )
		       break;
		   else
		       {
		       /* Symbol and value validated, get the text of	*/
		       /* the control and save within the user style	*/
		       /* information structure	for use	by Resource	*/
		       /* Editor					*/

		       pust->cText = WinQueryDlgItemText(hWnd, EF_TEXT,	CCHTEXTMAX, pust->pszText);

		       /* Mask out current edit	field styles clearing	*/
		       /* selectable styles and	save new style		*/

		       pust->flStyle = 0UL;

		       /* Get raised/depressed style			*/

		       if ( SHORT1FROMMR(WinSendDlgItemMsg(hWnd, CB_CMS_CHECKED, BM_QUERYCHECK,	0L, 0L)) )
			   pust->flStyle |= CMS_CHECKED;

		       /* Save completed edit field style in internal	*/
		       /* window information				*/

		       if ( WinSendDlgItemMsg(hWnd, CB_VISIBLE,	BM_QUERYCHECK, 0L, 0L) )
			   pust->flStyle |= WS_VISIBLE;

		       if ( WinSendDlgItemMsg(hWnd, CB_GROUP, BM_QUERYCHECK, 0L, 0L) )
			   pust->flStyle |= WS_GROUP;

		       if ( WinSendDlgItemMsg(hWnd, CB_DISABLED, BM_QUERYCHECK,	0L, 0L)	)
			   pust->flStyle |= WS_DISABLED;

		       if ( WinSendDlgItemMsg(hWnd, CB_TABSTOP,	BM_QUERYCHECK, 0L, 0L) )
			   pust->flStyle |= WS_TABSTOP;
		       }
		   }
		       /* Exit the dialogue indicating changes made	*/

	       WinDismissDlg(hWnd, TRUE);
	       break;
		       /* Cancel selected, exit	the dialogue without	*/
		       /* changing anything				*/

	   case	DID_CANCEL :
	       WinDismissDlg(hWnd, FALSE);
	       break;
	   }
       break;
		       /* Close	received, exit dialog			*/
   case	WM_CLOSE :
       WinDismissDlg(hWnd, FALSE);
       break;
		       /* Pass through unhandled messages		*/
   default :
       return(WinDefDlgProc(hWnd, msg, mp1, mp2));
   }
return(0L);

}
