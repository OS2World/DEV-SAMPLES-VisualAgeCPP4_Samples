/******************************************************************************
* .FILE:         notebook.cpp                                                 *
*                                                                             *
* .DESCRIPTION:  Notebook Sample Program:  Class Implementation               *
*                                                                             *
* .CLASSES:      ABitmapNotebook                                              *
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
#include <iapp.hpp>
#include <ifont.hpp>
#include <icolor.hpp>
#include <ireslib.hpp>
#include <icoordsy.hpp>
#include "notebook.hpp"
#include "notebook.h"

/**************************************************************************
* main() - Application Entry Point                                        *
**************************************************************************/
int main()
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::kOriginLowerLeft );

/*------------------------------------------------------------------------|
|  Change the default style for bitmaps that are about to be created.     |
|  Create an ABitmapNotebook object with window ID WND_MAIN.              |
|  Show the main window and begin processing events.                      |
|------------------------------------------------------------------------*/
   IBitmapControl::setDefaultStyle(IBitmapControl::defaultStyle() |
                                   IBitmapControl::sizeToBitmap);
   ABitmapNotebook mainWindow(WND_MAIN);
   mainWindow.show();
#ifdef IC_WIN
   INotebook::setDefaultStyle(INotebook::defaultStyle() |
                              INotebook::pmCompatible);
   ABitmapNotebook mainWindow2(WND_MAIN2);
   mainWindow2.show();
#endif
   IApplication::current().run();
   return 0;
}

/**************************************************************************
* ABitmapNotebook :: ABitmapNotebook - constuctor                         *
*                                                                         *
* Construct the IFrameWindow using the default style.                     *
* Create a resource library object for accessing the IResourceLibrary     *
*   loadBitmap function.                                                  *
* Create a size object to be used in creating the notebook tabs.          *
* Create each notebook major tab from a bitmap specified in the           *
*   application resource file and the previously created tabSize.         *
* Create the notebook as a child window of the frame and with a spiral    *
*   binding.  The binding is put at the top because the back pages are    *
*   located at the bottom left corner of the window.                      *
* Create each viewport as a child window of the notebook.                 *
* Create each bitmap as a child window of the corresponding viewport.     *
**************************************************************************/
ABitmapNotebook :: ABitmapNotebook(unsigned long windowId)
        :IFrameWindow(windowId)
        ,reslib()
        ,tabSize(50,50)
        ,tab1(reslib.loadBitmap(BM_PAGE1, tabSize))
        ,tab2(reslib.loadBitmap(BM_PAGE2, tabSize))
        ,tab3(reslib.loadBitmap(BM_PAGE3, tabSize))
        ,tab4(reslib.loadBitmap(BM_PAGE4, tabSize))
        ,notebook( WND_NB, this, this, IRectangle()
                 , INotebook::defaultStyle()
                 &~INotebook::majorTabsRight
                 | INotebook::majorTabsBottom
                 | INotebook::spiralBinding)
        ,viewport1(WND_VP1, &notebook, &notebook)
        ,viewport2(WND_VP2, &notebook, &notebook)
        ,viewport3(WND_VP3, &notebook, &notebook)
        ,viewport4(WND_VP4, &notebook, &notebook)
        ,bitmap1(BM_PAGE1, &viewport1, &viewport1, BM_PAGE1)
        ,bitmap2(BM_PAGE2, &viewport2, &viewport2, BM_PAGE2)
        ,bitmap3(BM_PAGE3, &viewport3, &viewport3, BM_PAGE3)
        ,bitmap4(BM_PAGE4, &viewport4, &viewport4, BM_PAGE4)
{
/*------------------------------------------------------------------------|
|  Load the font string from the resource and set the point size to 24.   |
|  Set bitmap 3 to the new font.                                          |
|  Set the color of the text to red.  Before major version 300, the       |
|    IStaticText setColor function was used to set the color of the       |
|    bitmap control.  Beginning in version 300, an IWindow function for   |
|    each color area is provided and should be used, instead.             |
|  Set the text in the bitmap to a string representing the sound of a cat.|
|  Align the text in the bitmap to the bottom center of the window.       |
|------------------------------------------------------------------------*/
  IResourceLibrary reslib;
  IFont font(reslib.loadString(STR_FONT),24);
  bitmap3.setFont(font);

  bitmap3.setForegroundColor(IColor::kRed);
  bitmap3.setText(reslib.loadString(STR_PRRR));
  bitmap3.setAlignment(IStaticText::bottomCenter);

/*------------------------------------------------------------------------|
|  Create a page settings object that specifies the type of tab to use,   |
|    that status text should be displayed, and that pages should be       |
|    automatically sized to fit the notebook.                             |
|  For each page to be added to the notebook,                             |
|    set the tab using a previously loaded bitmap,                        |
|    set the status text from a string in the resource file,              |
|    add the viewport containing the the appropriate bitmap to the        |
|      notebook using the page settings created previously.               |
|------------------------------------------------------------------------*/
  INotebook::PageSettings majorTab(INotebook::PageSettings::majorTab|
                                   INotebook::PageSettings::statusTextOn |
                                   INotebook::PageSettings::autoPageSize);

  majorTab.setTabBitmap(tab1);
  majorTab.setStatusText(BM_PAGE1);
  notebook.addLastPage(majorTab, &viewport1);

  majorTab.setTabBitmap(tab2);
  majorTab.setStatusText(BM_PAGE2);
  notebook.addLastPage(majorTab, &viewport2);

  majorTab.setTabBitmap(tab3);
  majorTab.setStatusText(BM_PAGE3);
  notebook.addLastPage(majorTab, &viewport3);

  majorTab.setTabBitmap(tab4);
  majorTab.setStatusText(BM_PAGE4);
  notebook.addLastPage(majorTab, &viewport4);

/*------------------------------------------------------------------------|
| Set the icon of the application and make the notebook the cleint of the |
| frame window.                                                           |
-------------------------------------------------------------------------*/
  setIcon(WND_MAIN);
  setClient(&notebook);
} /* end ABitmapNotebook::ABitmapNotebook(...) */
