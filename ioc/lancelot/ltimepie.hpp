/******************************************************************************
* .FILE:         ltimepie.hpp                                                 *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Definition       *
*                                                                             *
* .CLASSES:      LTimeCardPieChart                                            *
*                LPieChartResizeHandler                                       *
*                TaskElement                                                  *
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
#include "ltimec.hpp"
#ifndef _LTIMEPIE_
#define _LTIMEPIE_

#include <imcelcv.hpp>
#include <idrawcv.hpp>
#include <isizehdr.hpp>
#include <ikeyset.h>
#include <istring.hpp>
#include <ifont.hpp>
#include <igraph2d.hpp>
#include <igloop2d.hpp>
#include <igraftxt.hpp>
#include "lancelot.h"

class LTimeCardPieChart;

/******************************************************************************
* Class TaskElement - Collection element with task name and hours.            *
******************************************************************************/
class TaskElement
{
   public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in only one way:                                       |
| 1) Task name and hours worked for the task.                                 |
-----------------------------------------------------------------------------*/
      TaskElement( IString theTask, unsigned short theHours )
           :aTask( theTask ), aHours( theHours ) {};

/*------------------------------- Accessors -----------------------------------
| These functions provide a means of getting and setting the accessible       |
| attributes of instances of this class:                                      |
|   task                - Returns the task name                               |
|   hours               - Returns the task hours                              |
-----------------------------------------------------------------------------*/
      IString const
         &task() const { return aTask; };

      unsigned short const
         &hours() const { return aHours; };

/*------------------------------- Operators -----------------------------------
| Arithmetic and comparative operations for instances of this class:          |
|   ==                  - Compares two TaskElements for equality              |
-----------------------------------------------------------------------------*/
      bool
         operator == (TaskElement const& k) const { return aTask == k.aTask; };

   private:
      IString
         aTask;

      unsigned short
         aHours;
};
/*------------------------------- Accessors -----------------------------------
| These functions provide a means of getting and setting the accessible       |
| attributes of instances of this class:                                      |
|   key                 - Defines and returns the key for a TaskElement       |
-----------------------------------------------------------------------------*/
inline IString const
   &key( TaskElement const& k ) { return k.task(); };

typedef
   IKeySet< TaskElement, IString > TaskSet;


/******************************************************************************
* Class LPieChartResizeHandler - Handle resize events for the pie chart.      *
******************************************************************************/
class LPieChartResizeHandler : public IResizeHandler
{
   public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in only one way:                                       |
| 1) LTimeCardPieChart                                                        |
-----------------------------------------------------------------------------*/
      LPieChartResizeHandler( LTimeCardPieChart* pie );

      virtual ~LPieChartResizeHandler();

/*----------------------------- Event Processing ------------------------------
| Handle and process events:                                                  |
|   windowResize        - Process resize events.                              |
-----------------------------------------------------------------------------*/
   protected:
      virtual bool
         windowResize( IResizeEvent& event );

   private:
      LTimeCardPieChart
        *ppieChart;
};


/******************************************************************************
* Class LTimeCardPieChart - Timecard pie chart class.                         *
******************************************************************************/
class LTimeCardPieChart : public IDrawingCanvas
{
   public:
/*------------------------ Constructors/Destructor ----------------------------
| Construct the object in only one way:                                       |
| 1) ResourceId, parent, owner, location, and LTimeCardData.                  |
-----------------------------------------------------------------------------*/
      LTimeCardPieChart( unsigned long windoId,
                         IWindow* parent, IWindow* owner,
                         const IRectangle& location = IRectangle(),
                         LTimeCardData* pTimeData = NULL );

     ~LTimeCardPieChart();

/*------------------------------- Actions -------------------------------------
| Actions for instances of this class:                                        |
|   resizePieChart      - Resize the pie chart and legend.                    |
|   refreshData         - Refresh the timecard data.                          |
|   drawPie             - Draw the pie chart and legend.                      |
|   calculatePieData    - Pie chart and legend calculations.                  |
-----------------------------------------------------------------------------*/
      LTimeCardPieChart
        &resizePieChart( const ISize& size );

      LTimeCardPieChart
        &refreshData( LTimeCardData * tcp ) { pTimeCardData = tcp; return *this; };

      LTimeCardPieChart
        &drawPie(),
        &calculatePieData();

   private:
      LTimeCardData
        *pTimeCardData;

      IGraphicGroup
         graphGroup;

      LPieChartResizeHandler
         pieChartResizeHandler;

      IFont
         legendFont;

      IGPie2D
        *ppieSliceDimensions[ ID_TIMECARD_ENTRIES ];
      ILoop
        ppieSlice[ ID_TIMECARD_ENTRIES ];

      IGRect2D
        ppieLegendKeyDimensions[ ID_TIMECARD_ENTRIES ];
      IPolygon
        ppieLegendKey[ ID_TIMECARD_ENTRIES ];

      IGraphicText
        ppieLegendKeyText[ ID_TIMECARD_ENTRIES ];

      double
        angles[ ID_TIMECARD_ENTRIES ];

      IGrafBundle
        graphBundles [ ID_TIMECARD_ENTRIES ];

      unsigned short
         numberSlices,
         totalHours;

      TaskSet
         tasks;

      TaskSet::Cursor
         tasksCursor;
};
#endif
