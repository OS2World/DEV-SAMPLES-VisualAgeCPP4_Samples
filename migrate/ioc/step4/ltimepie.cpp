/******************************************************************************
* FILE NAME: ltimepie.cpp                                                     *
*                                                                             *
* Classes:                                                                    *
*   LTimeCardPieChart                                                         *
*                                                                             *
* COPYRIGHT:                                                                  *
*   Licensed Materials - Property of IBM                                      *
*   (C) Copyright IBM Corporation 1992, 1995                                  *
*   All Rights Reserved                                                       *
*   US Government Users Restricted Rights - Use, duplication, or disclosure   *
*   restricted by GSA ADP Schedule Contract with IBM Corp.                    *
******************************************************************************/

#ifndef _IBASE_                         //Make sure ibase.hpp is included
  #include <ibase.hpp>                  //  since that is where IC_<environ>
#endif                                  //  is defined.
#include <igrafctx.hpp>
#include <igbundle.hpp>
#include "ltimepie.hpp"
#include "lancelot.h"

/******************************************************************************
* Class LTimeCardPieChart :: LTimeCardPieChart - Constructor for the timecard *
*   pie chart.                                                                *
*                                                                             *
* Define yourself as an IDrawingCanvas                                        *
* Store a pointer to the timecard data                                        *
* Create a graph list                                                         *
* Create a resize handler for drawing the pie chart                           *
* Create a font for the pie chart's legend text                               *
* Initialize the number of pie slices to 0                                    *
* Initialize the total hours to 0                                             *
* Get the employee tasks                                                      *
* Define a cursor to the tasks                                                *
******************************************************************************/
LTimeCardPieChart::LTimeCardPieChart
                           ( unsigned long windowId, IWindow* parent,
                             IWindow* owner, const IRectangle& location,
                             LTimeCardData* tcp )
     :IDrawingCanvas       ( windowId, parent, owner, location ),
      pTimeCardData        ( tcp ),
      graphList            (),
      pieChartResizeHandler( this ),
      legendFont           ( "System Proportional", 4 ),
      numberSlices         ( 0 ),
      totalHours           ( 0 ),
      tasks                (),
      tasksCursor          ( tasks )

{
/*-----------------------------------------------------------------------------
| Handle resize events for the drawing canvas so that we can reposition       |
|  the graphics.                                                              |
-----------------------------------------------------------------------------*/
   pieChartResizeHandler.handleEventsFor( this );
   drawPie();
}


/******************************************************************************
* Class LTimeCardPieChart :: drawPie() - Draw the pie chart.                  *
******************************************************************************/
LTimeCardPieChart& LTimeCardPieChart::drawPie()
{
/*-----------------------------------------------------------------------------
| Create a graphics bundle.                                                   |
-----------------------------------------------------------------------------*/
   IGraphicBundle
      graphBundle;

/*-----------------------------------------------------------------------------
| Set the beginning pie location at angle zero (0).                           |
| Set the beginning pie color to red.                                         |
| Set the beginning pie pattern to solid.                                     |
| Initialize slice count to zero (0).                                         |
| Remove any previous graphics from graph list.                               |
-----------------------------------------------------------------------------*/
   double
      startAngle = 0;
   IColor
      theColor( IColor::red );
   unsigned long
      thePattern = IGraphicBundle::solid;
   unsigned short
      sliceCount = 0;
   graphList.removeAll();

/*-----------------------------------------------------------------------------
| Calculate the number of unique task names, unique task hours, and           |
|   total hours.                                                              |
| If no slices needed, leave.                                                 |
-----------------------------------------------------------------------------*/
   calculatePieData();

   if ( !numberSlices )
      return *this;

/*-----------------------------------------------------------------------------
| Iterate through 13 colors and then                                          |
|   iterate through 5 different patterns as needed.  Possible number of       |
|   unique pie slices is 65 (ie. 13 x 5)                                      |
-----------------------------------------------------------------------------*/
   for ( unsigned short whichPattern = 1;
         whichPattern < 6;
         whichPattern++ )
   {
      switch( whichPattern )
      {
         case 1:
         {
            thePattern = IGraphicBundle::solid;
            break;
         }
         case 2:
         {
            thePattern = IGraphicBundle::horizontal;
            break;
         }
         case 3:
         {
            thePattern = IGraphicBundle::dense1;
            break;
         }
         case 4:
         {
            thePattern = IGraphicBundle::vertical;
            break;
         }
         case 5:
         {
            thePattern = IGraphicBundle::hatchedDiag;
            break;
         }
      }

      for ( unsigned short whichColor = 1;
            whichColor < 14;
            whichColor++ )
      {
         switch( whichColor )
         {
            case 1:
            {
               theColor = IColor::red;
               break;
            }
            case 2:
            {
               theColor = IColor::blue;
               break;
            }
            case 3:
            {
               theColor = IColor::green;
               break;
            }
            case 4:
            {
               theColor = IColor::yellow;
               break;
            }
            case 5:
            {
               theColor = IColor::cyan;
               break;
            }
            case 6:
            {
               theColor = IColor::pink;
               break;
            }
            case 7:
            {
               theColor = IColor::darkRed;
               break;
            }
            case 8:
            {
               theColor = IColor::darkBlue;
               break;
            }
            case 9:
            {
               theColor = IColor::darkGreen;
               break;
            }
            case 10:
            {
               theColor = IColor::darkCyan;
               break;
            }
            case 11:
            {
               theColor = IColor::darkPink;
               break;
            }
            case 12:
            {
               theColor = IColor::darkGray;
               break;
            }
            case 13:
            {
               theColor = IColor::brown;
               break;
            }
         }

/*-----------------------------------------------------------------------------
| Set the bundle's pen color                                                  |
| Set the bundle's fill color                                                 |
| Set the bundle's fill pattern                                               |
-----------------------------------------------------------------------------*/
         graphBundle.setPenColor( theColor );
         graphBundle.setFillColor( theColor );
         graphBundle.setFillPattern( thePattern );

/*-----------------------------------------------------------------------------
| If there are no tasks or no hours worked, leave                             |
-----------------------------------------------------------------------------*/
         if ( !tasksCursor.isValid() || !totalHours )
            break;

/*-----------------------------------------------------------------------------
| Get the task name                                                           |
| Get the task hours                                                          |
| Calculate this pie slice's piece of the pie                                 |
-----------------------------------------------------------------------------*/
         IString
            aTaskName = tasksCursor.element().task();
         unsigned short
            aHours = tasksCursor.element().hours();
         double
            newAngle = 360.0 * aHours / totalHours;

/*-----------------------------------------------------------------------------
| Create a pie slice                                                          |
| Define the graphics bundle for this pie slice                               |
| Add the pie slice to the graph list                                         |
-----------------------------------------------------------------------------*/
         ppieSlice[sliceCount] =
            new IGPie( IRectangle(), startAngle, newAngle );
         ppieSlice[sliceCount]->setGraphicBundle( graphBundle );
         graphList.addAsLast( *ppieSlice[sliceCount] );

/*-----------------------------------------------------------------------------
| Create a graphics rectangle for the color key in the legend                 |
| Define the graphics bundle for this rectangle                               |
| Add the rectangle to the graph list                                         |
-----------------------------------------------------------------------------*/
         ppieLegendKey[sliceCount] = new IGRectangle( IRectangle() );
         ppieLegendKey[sliceCount]->setGraphicBundle( graphBundle );
         graphList.addAsLast( *ppieLegendKey[sliceCount] );

/*-----------------------------------------------------------------------------
| Create a graphics string for the text in the legend                         |
| Define the graphics bundle for this graphic string                          |
| Add the graphics string to the graph list                                   |
-----------------------------------------------------------------------------*/
         ppieLegendKeyText[sliceCount] =
            new IGString( tasksCursor.element().task(), IPoint(), legendFont );
         ppieLegendKeyText[sliceCount]->setGraphicBundle( graphBundle );
         graphList.addAsLast( *ppieLegendKeyText[sliceCount] );

/*-----------------------------------------------------------------------------
| Increment the starting angle from the previous starting position            |
| Increment the slice count                                                   |
| Increment to the next task in the tasks cursor                              |
| If no more slices needed, leave                                             |
-----------------------------------------------------------------------------*/
         startAngle = startAngle + newAngle;
         sliceCount++;
         tasksCursor.setToNext();
         if ( sliceCount >= numberSlices )
            break;
      }
/*-----------------------------------------------------------------------------
| If no more slices needed, leave                                             |
-----------------------------------------------------------------------------*/
      if ( sliceCount >= numberSlices )
         break;
   }

/*-----------------------------------------------------------------------------
| Revalidate tasks cursor to beginning                                        |
| Now begin using our graph list                                              |
| Resize and draw the pie chart                                               |
-----------------------------------------------------------------------------*/
   tasksCursor.setToFirst();

   setGraphicList( &graphList );

   resizePieChart( size() );

   return *this;
}


/*******************************************************************************
* LTimeCardPieChart :: calculatePieData                                        *
*   Determine the number of unique tasks, hours for each unique task, and      *
*   total hours in timecard data                                               *
*******************************************************************************/
LTimeCardPieChart& LTimeCardPieChart::calculatePieData()
{
   IString
      theTask;
   unsigned short
      entryNumber = 0;
   totalHours = 0;
   numberSlices = 0;

   tasks.removeAll();
   tasksCursor.invalidate();
   tasksCursor.setToFirst();

/*-----------------------------------------------------------------------------
| Iterate each task name until blank                                          |
-----------------------------------------------------------------------------*/
   while ( ( theTask = pTimeCardData->tcard[entryNumber].taskName() ) != "" )
   {
      unsigned short
         theHours = pTimeCardData->tcard[entryNumber].hours().asInt();
      totalHours += theHours;
/*-----------------------------------------------------------------------------
| If the task name is not in the tasks set, add it.                           |
| Increment number of unique pie slices.                                      |
-----------------------------------------------------------------------------*/
      if ( !tasks.containsElementWithKey( theTask ) )
      {
         tasks.add( TaskElement( theTask, theHours ) );
         numberSlices++;
      }
      else
/*-----------------------------------------------------------------------------
| Since the task name is not unique in the task set, add the hours to the     |
| existing task hours.                                                        |
-----------------------------------------------------------------------------*/
      {
         TaskElement
            theElement = tasks.elementWithKey( theTask );
         tasks.addOrReplaceElementWithKey( TaskElement(
                                           theTask,
                                           theElement.hours() + theHours ) );
      }
      entryNumber++;
   }
   tasksCursor.setToFirst();

   return *this;
}


/*******************************************************************************
* LTimeCardPieChart :: resizePieChart                                          *
*   Redraw the pie chart for any resizing that might occur                     *
*******************************************************************************/
LTimeCardPieChart& LTimeCardPieChart::resizePieChart( const ISize& theSize )
{
/*-----------------------------------------------------------------------------
| If no slices to draw, leave.                                                |
-----------------------------------------------------------------------------*/
   if ( !numberSlices )
      return *this;

/*-----------------------------------------------------------------------------
| Pie calculations...                                                         |
-----------------------------------------------------------------------------*/
   IPoint
      pieBegins( 2, theSize.height() / 3 );
   IRectangle
      pieRect( pieBegins,
               IPoint( theSize.width() - 4, theSize.height() - 4 ) );

   unsigned short index;
   for ( index = 0;
         index < numberSlices;
         index++ )
   {
      ppieSlice[ index ]->setEnclosingRect( pieRect );
   }

/*-----------------------------------------------------------------------------
| Legend calculations...                                                      |
-----------------------------------------------------------------------------*/
   IPoint
      legendEnds( theSize.width() - 2, theSize.height() / 3 - 10 );
   IRectangle
      legendRect( IPoint( 2, 2 ), legendEnds );
   unsigned short
      numLegendCols = 2;
   unsigned short
      numLegendRows = numberSlices / numLegendCols
                      + numberSlices % numLegendCols;
   unsigned short
      cellWidth = legendEnds.x() / numLegendCols;
   unsigned short
      cellHeight = legendEnds.y() / numLegendRows;

   for ( index = 0;
         index < numberSlices;
         index++ )
   {
      unsigned short
         theCol = index % numLegendCols;
      unsigned short
         theRow = index / numLegendCols;
      IRectangle
         legendPieceRect( IPoint( theCol * cellWidth,
                          theRow * cellHeight ),
                          ISize( cellWidth, cellHeight ) );

      IRectangle
         blockRect( legendPieceRect.bottomLeft(),
                    IPoint( legendPieceRect.left() +
                    ( (legendPieceRect.right() - legendPieceRect.left() ) / 4 ),
                    legendPieceRect.top() ) );
      IPoint
         textPoint( legendPieceRect.left() +
                    ( ( legendPieceRect.right() - legendPieceRect.left() ) / 4) + 2,
                      legendPieceRect.bottom() );

      ppieLegendKey[ index ]->setEnclosingRect( blockRect );
      ppieLegendKeyText[ index ]->moveTo( textPoint );
   }

   return *this;
}


/******************************************************************************
* Class LTimeCardPieChart :: ~LTimeCardPieChart - Destructor                  *
******************************************************************************/
LTimeCardPieChart::~LTimeCardPieChart()
{
/*-----------------------------------------------------------------------------
| Delete all pie slices, legend key rectangles, and legend text.              |
-----------------------------------------------------------------------------*/
   for ( unsigned short index = 0;
         index < numberSlices;
         index++ )
   {
      delete ppieSlice[ index ];
      delete ppieLegendKey[ index ];
      delete ppieLegendKeyText[ index ];
   }
}



/******************************************************************************
* Class LPieChartResizeHandler :: LPieChartResizeHandler - Constructor for    *
*   the timecard's pie chart                                                  *
*                                                                             *
* Define yourself as an IResizeHandler                                        *
* Store a pointer to the pie chart                                            *
******************************************************************************/
LPieChartResizeHandler::LPieChartResizeHandler( LTimeCardPieChart * pie )
     :IResizeHandler(),
      ppieChart( pie )
{}


/******************************************************************************
* Class LPieChartResizeHandler :: ~LPieChartResizeHandler - Destructor        *
******************************************************************************/
LPieChartResizeHandler::~LPieChartResizeHandler( )
{}


/******************************************************************************
* Class LPieChartResizeHandler :: windowResize() - Called when a resize       *
*   event occurs for the pie chart.                                           *
******************************************************************************/
Boolean LPieChartResizeHandler::windowResize( IResizeEvent& event )
{
/*-----------------------------------------------------------------------------
| Call our own resizing function.                                             |
-----------------------------------------------------------------------------*/
   ppieChart->resizePieChart( event.newSize() );
   return false;
}
