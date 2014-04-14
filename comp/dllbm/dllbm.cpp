/*
 * IBM VisualAge C++ Professional, Version 4.0
 *
 * Licensed Materials - Property of IBM
 *
 * (C) Copyright IBM Corp. 1998. All Rights Reserved.
 *
 * The following [enclosed] code is sample code created by IBM
 * Corporation.  This sample code is not part of any standard IBM product
 * and is provided to you solely for the purpose of assisting you in the
 * development of your applications.  The code is provided 'AS IS',
 * without warranty of any kind.  IBM shall not be liable for any damages
 * arising out of your use of the sample code, even if they have been
 * advised of the possibility of such damages.
 */

#include <iapp.hpp>
#include <ifont.hpp>
#include <icolor.hpp>
#include <ireslib.hpp>
#include <icoordsy.hpp>
#include "dllbm.hpp"
#include "dllbm.h"

/**************************************************************************
* main() - Application Entry Point                                        *
**************************************************************************/

int main()
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::kOriginLowerLeft);

/*------------------------------------------------------------------------|
|  Change the default style for bitmaps that are about to be created.     |
|  Create an ABitmapNotebook object.                                      |
|  Show the main window and begin processing events.                      |
|------------------------------------------------------------------------*/

   IBitmapControl::setDefaultStyle(IBitmapControl::defaultStyle() |
                                   IBitmapControl::sizeToBitmap);

   ABitmapNotebook mainWindow;

   mainWindow.show();

   IApplication::current().run();

   return 0;
}

/**************************************************************************
* ABitmapNotebook :: ABitmapNotebook - constuctor                         *
*                                                                         *
* Construct the IFrameWindow using the default style.                     *
* Create an IDynamicLinkLibrary object for accessing the resource DLL.    *
* Create a size object to be used in creating the notebook tabs.          *
* Create each notebook major tab from a bitmap specified in the           *
*   application resource file and the previously created tabSize.         *
* Create each viewport as a child window of the notebook.                 *
* Create each bitmap as a child window of the corresponding viewport.     *
**************************************************************************/

ABitmapNotebook :: ABitmapNotebook()
        :IFrameWindow()
#ifdef __TOS_AIX__
        ,idll("share.a")  // initialize resource DLL
#else
        ,idll("share")  // initialize resource DLL
#endif
        ,tabSize(50,50)
        ,tab1(idll.loadBitmap(BM_PAGE1, tabSize))   // load bitmaps from DLL
        ,tab2(idll.loadBitmap(BM_PAGE2, tabSize))
        ,tab3(idll.loadBitmap(BM_PAGE3, tabSize))
        ,notebook( WND_NB, this, this, IRectangle()
                 , INotebook::defaultStyle()
                 &~INotebook::majorTabsRight
                 | INotebook::majorTabsBottom
                 | INotebook::spiralBinding)
        ,viewport1(WND_VP1, &notebook, &notebook)
        ,viewport2(WND_VP2, &notebook, &notebook)
        ,viewport3(WND_VP3, &notebook, &notebook)
	,bitmap1(BM_PAGE1, &viewport1, &viewport1, tab1)
	,bitmap2(BM_PAGE2, &viewport2, &viewport2, tab2)
	,bitmap3(BM_PAGE3, &viewport3, &viewport3, tab3)
{

/*------------------------------------------------------------------------|
|  Create a page settings object that specifies the type of tab to use,   |
|    and that pages should be automatically sized to fit the notebook.    |
|  For each page to be added to the notebook,                             |
|    set the tab using a previously loaded bitmap,                        |
|    and add the viewport containing the the appropriate bitmap to the    |
|      notebook using the page settings created previously.               |
|------------------------------------------------------------------------*/

  INotebook::PageSettings majorTab(INotebook::PageSettings::majorTab|
                                   INotebook::PageSettings::autoPageSize);

  majorTab.setTabBitmap(tab1);
  notebook.addLastPage(majorTab, &viewport1);

  majorTab.setTabBitmap(tab2);
  notebook.addLastPage(majorTab, &viewport2);

  majorTab.setTabBitmap(tab3);
  notebook.addLastPage(majorTab, &viewport3);

  setClient(&notebook);
}
