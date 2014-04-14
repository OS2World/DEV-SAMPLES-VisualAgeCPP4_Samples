/******************************************************************************
* .FILE:         ltimepie.cpp                                                 *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Implementation   *
*                                                                             *
* .CLASSES:      LTimeCardPieChart                                            *
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
#include <ipaints.hpp>
#include <istyles.hpp>
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
      graphGroup           (),
      pieChartResizeHandler( this ),
      legendFont           ( "System Proportional", 10 ),
      numberSlices         ( 0 ),
      totalHours           ( 0 ),
      tasks                (),
      tasksCursor          ( tasks )

{
/*-----------------------------------------------------------------------------
| Handle resize events for the drawing canvas so that we can reposition       |
|  the graphics.                                                              |
-----------------------------------------------------------------------------*/
   ppieSliceDimensions[0] = NULL;
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
   IFillBundle
      *fillBundle;

/*-----------------------------------------------------------------------------
| Set the beginning pie location at angle zero (0).                           |
| Set the beginning pie color to red.                                         |
| Set the beginning pie pattern to solid.                                     |
| Initialize slice count to zero (0).                                         |
-----------------------------------------------------------------------------*/
   double
      startAngle = 0;
   IPaint
      thePaint(IBaseColor::kRed, IMaskPattern::solid());
   unsigned short
      sliceCount = 0;

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
            thePaint.setMaskPattern(IMaskPattern::solid());
            break;
         }
         case 2:
         {
            thePaint.setMaskPattern(IMaskPattern::horizontal());
            break;
         }
         case 3:
         {
            thePaint.setMaskPattern(IMaskPattern::cross());
            break;
         }
         case 4:
         {
            thePaint.setMaskPattern(IMaskPattern::vertical());
            break;
         }
         case 5:
         {
            thePaint.setMaskPattern(IMaskPattern::diagonalUp());
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
               thePaint.setColor(IColor::kRed);
               break;
            }
            case 2:
            {
               thePaint.setColor(IColor::kBlue);
               break;
            }
            case 3:
            {
               thePaint.setColor(IColor::kGreen);
               break;
            }
            case 4:
            {
               thePaint.setColor(IColor::kYellow);
               break;
            }
            case 5:
            {
               thePaint.setColor(IColor::kCyan);
               break;
            }
            case 6:
            {
               thePaint.setColor(IColor::kPink);
               break;
            }
            case 7:
            {
               thePaint.setColor(IColor::kDarkRed);
               break;
            }
            case 8:
            {
               thePaint.setColor(IColor::kDarkBlue);
               break;
            }
            case 9:
            {
               thePaint.setColor(IColor::kDarkGreen);
               break;
            }
            case 10:
            {
               thePaint.setColor(IColor::kDarkCyan);
               break;
            }
            case 11:
            {
               thePaint.setColor(IColor::kDarkPink);
               break;
            }
            case 12:
            {
               thePaint.setColor(IColor::kDarkGray);
               break;
            }
            case 13:
            {
               thePaint.setColor(IColor::kBrown);
               break;
            }
         }

/*-----------------------------------------------------------------------------
| Set the bundle's pen color                                                  |
| Set the bundle's fill color                                                 |
| Set the bundle's fill pattern                                               |
-----------------------------------------------------------------------------*/
         graphBundles[sliceCount].setFrameColor(*thePaint.color());
         graphBundles[sliceCount].setFillPaint(thePaint);
         graphBundles[sliceCount].setDrawingOperation(IAttributeState::kFillAndFrame);


/*-----------------------------------------------------------------------------
| If there are no tasks or no hours worked, leave                             |
-----------------------------------------------------------------------------*/
         if ( !tasksCursor.isValid() || !totalHours )
            break;

/*-----------------------------------------------------------------------------
| Get the task name                                                           |
| Get the task hours                                                          |
| Calculate this pie slice's piece of the pie                                 |
| Set the angle for this pie slice.                                           |
-----------------------------------------------------------------------------*/
         IString
            aTaskName = tasksCursor.element().task();
         unsigned short
            aHours = tasksCursor.element().hours();
         double
            newAngle = 360.0 * aHours / totalHours;

         angles[sliceCount] = startAngle;

/*-----------------------------------------------------------------------------
| Create a graphics string for the text in the legend                         |
-----------------------------------------------------------------------------*/
         IText *tempText = new IText(tasksCursor.element().task());
         tempText->addStyles(ITextTypefaceStyle(legendFont.name()));
         ppieLegendKeyText[sliceCount].setText(*tempText);
         ppieLegendKeyText[sliceCount].setLineBreak(IGraphicText::kSingleLine);

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
| Complete the last entry in the angles array                                 |
| Now begin using our graph list                                              |
| Resize and draw the pie chart                                               |
-----------------------------------------------------------------------------*/
   tasksCursor.setToFirst();

   angles[sliceCount] = startAngle;

   setGraphicGroup( &graphGroup );

   resizePieChart( size() );

   return *this;
}


/******************************************************************************
* LTimeCardPieChart :: calculatePieData                                       *
*   Determine the number of unique tasks, hours for each unique task, and     *
*   total hours in timecard data                                              *
******************************************************************************/
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


/******************************************************************************
* LTimeCardPieChart :: resizePieChart                                         *
*   Redraw the pie chart for any resizing that might occur                    *
******************************************************************************/
LTimeCardPieChart& LTimeCardPieChart::resizePieChart( const ISize& theSize )
{
   bool deletePies = true;
/*-----------------------------------------------------------------------------
| If no slices to draw or invalid theSize, leave.                             |
-----------------------------------------------------------------------------*/
   if ( !numberSlices || (theSize.height() == 0) || (theSize.width() == 0))
      return *this;

/*-----------------------------------------------------------------------------
| Remove any previous graphics from graph list.                               |
-----------------------------------------------------------------------------*/
   IGraphicGroupIterator emptyCheck(&graphGroup);
   while (emptyCheck.first()) {
      graphGroup.orphanFirst(); }

/*-----------------------------------------------------------------------------
| Pie calculations...                                                         |
-----------------------------------------------------------------------------*/
   IPoint
      pieBegins( 2, theSize.height() / 3 );
   IRectangle
      pieRect( pieBegins,
               IPoint( theSize.width() - 4, theSize.height() - 4 ) );
   IGEllipse2D
      sizeEllipse(pieRect);

   if (ppieSliceDimensions[0] == NULL)
      deletePies = false;

   for ( unsigned short which = 0;
         which < numberSlices;
         which++ )
   {
      if (deletePies)
         delete ppieSliceDimensions[which];
      ppieSliceDimensions[which] =
          new IGPie2D( sizeEllipse, angles[which], angles[which + 1] );

      ppieSlice[which].orphanGeometry();
      ppieSlice[which].adoptGeometry(ppieSliceDimensions[which]);
      ppieSlice[which].orphanBundle();
      ppieSlice[which].adoptBundle(&graphBundles[which]);
      graphGroup.adoptLast(&ppieSlice[which]);
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
   int
      cellWidth = legendEnds.x() / numLegendCols;
   int
      cellHeight = legendEnds.y() / numLegendRows;

   for ( int index = 0;
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

      ppieLegendKeyDimensions[index]
         .setBottomLeft(legendPieceRect.bottomLeft());
      ppieLegendKeyDimensions[index]
         .setTopRight(IPoint(legendPieceRect.left() +
                             ((legendPieceRect.right() -
                               legendPieceRect.left()) /4),
                             legendPieceRect.top()));

      ppieLegendKey[index].orphanGeometry();
      ppieLegendKey[index]
         .adoptGeometry(new IGPolygon2D(ppieLegendKeyDimensions[index]));
      ppieLegendKey[index].orphanBundle();
      ppieLegendKey[index].adoptBundle(&graphBundles[index]);
      graphGroup.adoptLast(&ppieLegendKey[index]);

      IGPoint2D
         textPoint(legendPieceRect.left() +
                   ((legendPieceRect.right() - legendPieceRect.left()) / 4) + 2,
                      legendPieceRect.bottom()+5);

      ppieLegendKeyText[index].setLocation( textPoint );
      graphGroup.adoptLast(&ppieLegendKeyText[index]);
   }

   return *this;
}


/******************************************************************************
* Class LTimeCardPieChart :: ~LTimeCardPieChart - Destructor                  *
******************************************************************************/
LTimeCardPieChart::~LTimeCardPieChart()
{
/*-----------------------------------------------------------------------------
| Empty the graph group.                                                      |
| Orphan all geometry and bundles of ppieSlice and ppieLegendKey.             |
| Note:  this must be done before these objects are deleted.                  |
-----------------------------------------------------------------------------*/
   IGraphicGroupIterator emptyCheck(&graphGroup);
   while (emptyCheck.first()) {
      graphGroup.orphanFirst(); }

   for ( unsigned short index = 0;
         index < numberSlices;
         index++ )
   {
      ppieSlice[index].orphanGeometry();
      ppieSlice[index].orphanBundle();

      ppieLegendKey[index].orphanGeometry();
      ppieLegendKey[index].orphanBundle();

      delete ppieSliceDimensions[index];
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
bool LPieChartResizeHandler::windowResize( IResizeEvent& event )
{
/*-----------------------------------------------------------------------------
| Call our own resizing function.                                             |
-----------------------------------------------------------------------------*/
   ppieChart->resizePieChart( event.newSize() );
   return false;
}
