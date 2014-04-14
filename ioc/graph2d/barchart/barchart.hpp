#ifndef _BARCHART_
#define _BARCHART_

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
* .FILE:         barchart.hpp                                                 *
*                                                                             *
* .DESCRIPTION:  BarChart Sample Program:  Class Header                       *
*                                                                             *
* .CLASSES:      BarChart                                                     *
*                                                                             *
* .NOTE: WE RECOMMEND USING A FIXED SPACE FONT TO LOOK AT THE SOURCE          *
*                                                                             *
******************************************************************************/

#include "chart.hpp"
#include <igraph2d.hpp>


class BarChart : public Chart
{
public:
          //default constructor
                BarChart();

                 //copy constructor
                BarChart(const BarChart& n);

                //destructor
                ~BarChart();


                //return the position of the barchart
                IGPoint2D GetBChartPosition() const;

                // return the height of the barchart
                GCoordinate GetBChartHeight() const;

                //return the width of the barchart
                GCoordinate GetBChartWidth()const;

                //set the position of the barchart
                void SetBChartPosition(IGPoint2D p);

                // set the height of the barchart
                void SetBChartHeight(GCoordinate h);

          // set the width of the barchart
                void SetBChartWidth(GCoordinate w);

                // draw the barchart
                virtual void Draw(IGrafPort *DisplayPort);

protected:
    // recalculate after adding an element to the barchart
                virtual void RecalAfterAdd();

    // recalculate after removing an element to the barchart
          virtual       void RecalAfterRemove();

private:

                //----------------------------------------------------------
                // member functions
                //----------------------------------------------------------
                // return the bases(3D) of the barchart
                IGraphicGroup *GetBase();

                //return a bar(3D) representing non_negative data in the barchart
                IGraphicGroup *GetBar(IGRect2D rect);

                //return a bar(3D) representing a negative data in the barchart
                IGraphicGroup *GetNegativeBar(IGRect2D rect);

                //return all the bars representing all data in barchart
                IGraphicGroup *GetAllBars();

                // return the tick marks on Y direction
                IGraphicGroup  *GetYTicks();

                // return the data labels on Y direction
                IGraphicGroup  *GetYLabels();

                //return the tick marks on X direction
                IGraphicGroup  *GetXTicks();

                // return sequential labels on X direction
                // in this sample, the labels on X direction are sequential
                // numbers : 1 , 2, 3 ...
                IGraphicGroup  *GetXLabels();

                // recalculate some data members of barchart
                void  Recalculate();

                // Find the proper intervals on Y direction according
                // to the data range of the bar chart
                void  FindIntervals();

                //Assignment operator
                BarChart& operator=(const BarChart& n);

          //----------------------------------------------------------
                // data members
                //----------------------------------------------------------

                // position of the barchart is defined
          // to be the left top corner of the barchart area
                IGPoint2D fPosition ;

                //the origin of the barchart
                IGPoint2D fOrigin;

                // the X, Y dimensions of the barchart
                GCoordinate  fChartWidth, fChartHeight;

                // the distance between two adjacent bars;
                GCoordinate fBarDistance;

                //the width of each bar;
                GCoordinate fBarWidth;

                //number of bars which is the same as number of data in the barchart
                int fNumOfBars;

          // number of intervals in positive y direction
                int fNumOfPosInterval;

                // number of intervals in negative y direction
                int fNumOfNegInterval;

                //the data scale that each interval represents
                ChartType fScale;
}       ;
#endif // _BARCHART_
