// Revision: 86 1.4.2.3 samples/graph2d/2dcombo/2dcombo.hpp, ocsamples-L1, ioc.v400, 981111 
/******************************************************************************/
/* 2DCOMBO SAMPLE PROGRAM -- Version 1: Class Header (2DCOMBO.HPP)            */
/******************************************************************************/

/*
-------------------------------------------------------------------------------
Copyright (c) IBM Corporation 1996, 1997.
All Rights Reserved.

Permission is granted to copy, use, modify, and merge this software into your
applications and to permit others to do any of the foregoing. You must include
this permission and copyright notice in all copies and modified versions of
this software. THIS SOFTWARE IS PROVIDED IN ITS 'AS IS' CONDITION.
IBM DISCLAIMS ANY LIABILITY OF ANY KIND FOR DAMAGES WHATSOEVER RESULTING
FROM THE USE OF THIS SOFTWARE.
-------------------------------------------------------------------------------
*/

#include <iframe.hpp>              // IBM Open Class Headers
#include <icmdhdr.hpp>
#include <imenubar.hpp>
#include <ipainhdr.hpp>
#include <ipainevt.hpp>
#include <icoordsy.hpp>
#include <icanvas.hpp>


//**************************************************************************
// Class:   MainWindow                                                     *
//                                                                         *
// Purpose: Main Window for C++ 2DCOMBO 2D Graphics sample application     *
//**************************************************************************

class MainWindow : public IFrameWindow, public ICommandHandler, public IPaintHandler
{
  public:
    MainWindow(unsigned long windowId);
    virtual ~MainWindow();
  protected:
    virtual bool command(ICommandEvent& event);
    virtual bool paintWindow(IPaintEvent& event);
  private:
    ICanvas             drawingArea;                  // the drawing space
    IMenuBar            menuBar;
    unsigned long       drawSetting;
};
