/******************************************************************************
* FILE NAME: ltimepie.hpp                                                     *
*                                                                             *
* DESCRIPTION: Timecard pie chart                                             *
*                                                                             *
* Classes:                                                                    *
*   LTimeCardPieChart                                                         *
*   LPieChartResizeHandler                                                    *
*   TaskElement                                                               *
*                                                                             *
* COPYRIGHT:                                                                  *
*   Licensed Materials - Property of IBM                                      *
*   (C) Copyright IBM Corporation 1992, 1995                                  *
*   All Rights Reserved                                                       *
*   US Government Users Restricted Rights - Use, duplication, or disclosure   *
*   restricted by GSA ADP Schedule Contract with IBM Corp.                    *
*                                                                             *
******************************************************************************/
#include "ltimec.hpp"
#ifndef _LTIMEPIE_
#define _LTIMEPIE_

#include <igpie.hpp>
#include <igrect.hpp>
#include <igstring.hpp>
#include <imcelcv.hpp>
#include <iglist.hpp>
#include <idrawcv.hpp>
#include <isizehdr.hpp>
#include <ikeyset.h>
#include <istring.hpp>
#include <ifont.hpp>
#include "lancelot.h"

class LTimeCardPieChart;

/******************************************************************************
* Class TaskElement - Collection element with task name and hours.            *
******************************************************************************/
class TaskElement : public IBase
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
      Boolean 
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
      virtual Boolean
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

      IGList
         graphList;

      LPieChartResizeHandler
         pieChartResizeHandler;

      IFont
         legendFont;

      IGPie
        *ppieSlice[ ID_TIMECARD_ENTRIES ];

      IGRectangle
        *ppieLegendKey[ ID_TIMECARD_ENTRIES ];

      IGString
        *ppieLegendKeyText[ ID_TIMECARD_ENTRIES ];

      unsigned short
         numberSlices,
         totalHours;

      TaskSet
         tasks;

      TaskSet::Cursor
         tasksCursor;
};
#endif
