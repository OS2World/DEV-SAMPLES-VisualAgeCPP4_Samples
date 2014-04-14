#ifndef _BCDEMO_HPP
#define _BCDEMO_HPP

/*
-------------------------------------------------------------------------------
Copyright (c) IBM Corporation 1997.
All Rights Reserved.

Permission is granted to copy, use, modify, and merge this software into your
applications and to permit others to do any of the foregoing. You must include
this permission and copyright notice in all copies and modified versions of
this software. THIS SOFTWARE IS PROVIDED IN ITS 'AS IS' CONDITION.
IBM DISCLAIMS ANY LIABILITY OF ANY KIND FOR DAMAGES WHATSOEVER RESULTING
FROM THE USE OF THIS SOFTWARE.
-------------------------------------------------------------------------------
*/

/******************************************************************************
* .FILE:         bcdemo.hpp                                                   *
*                                                                             *
* .DESCRIPTION:  BarChart Sample Program:  Class Header                       *
*                                                                             *
* .CLASSES:      MainWindow                                                   *
*                                                                             *
* .NOTE: WE RECOMMEND USING A FIXED SPACE FONT TO LOOK AT THE SOURCE          *
*                                                                             *
******************************************************************************/

#include "barchart.hpp"
#include "adialog.hpp"

// IBM OpenClass Header
#include <iframe.hpp>
#include <icmdhdr.hpp>
#include <imenubar.hpp>
#include <ipainhdr.hpp>
#include <ipainevt.hpp>
#include <icoordsy.hpp>
#include <icanvas.hpp>

#include <igraph2d.hpp>
#include <igrport.hpp>



class MainWindow : public IFrameWindow, public ICommandHandler, public IPaintHandler
{
  public:

          // constructor
    MainWindow(unsigned long windowId);

                //destructor
    virtual ~MainWindow();

    //initalize some data just for demo effect of a bar chart
    void demoIntialize();

  protected:

        //The command function is called to handle application command events.
    virtual bool command(ICommandEvent& event);

        //function is called to handle application paint events.
    virtual bool paintWindow(IPaintEvent& event);

  private:

                ICanvas             drawingArea; // the drawing space
    IMenuBar            menuBar;
                BarChart                                                *fBarChart;

    //display message in the MainWindow
                void displayMsg(unsigned long strID);
                void displayMsg(unsigned long strID, GCoordinate data);
                void displayMsg(unsigned long strID, GCoordinate data2, GCoordinate data3);
};


#endif // _BCDEMO_HPP
