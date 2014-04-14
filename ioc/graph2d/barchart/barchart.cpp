// Revision: 18  1.5.1.3  samples/graph2d/barchart/barchart.cpp, ocsamples-L1, ioc.v400, 981111  
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
* .FILE:         barchart.cpp                                                 *
*                                                                             *
* .DESCRIPTION:  BarChart Sample Program:  Class Implementation               *
*                                                                             *
* .CLASSES:      BarChart                                                     *
*                                                                             *
* .NOTE: WE RECOMMEND USING A FIXED SPACE FONT TO LOOK AT THE SOURCE          *
*                                                                             *
******************************************************************************/


#include "barchart.hpp"

#include <igraph2d.hpp>
#include <igrport.hpp>
#include <ibcolor.hpp>
#include <math.h>
#include <igraftxt.hpp>
#include <istyles.hpp>
#include <istylset.hpp>
#include <ifont.hpp>




/**********************************************************************
 * Function: BarChart::BarChart()
 *
 * Purpose: default constructor for class BarChart
 *
***********************************************************************/

  BarChart::BarChart()
 {
   fPosition.fX = 70;
         fPosition.fY = 100;
   fOrigin.fX= 0;
         fOrigin.fY=0;
         fChartHeight=275;
         fChartWidth=300;
         fNumOfBars = 0;
         fBarDistance=0;
         fBarWidth =0;
         fNumOfPosInterval = 0;
         fNumOfNegInterval = 0;
         fScale = 1 ;
 }


/**********************************************************************
 * Function: BarChart::BarChart()
 *
 * Purpose: copy constructor of  class BarChart
 *
***********************************************************************/

 BarChart::BarChart(const BarChart& n):Chart(n)
 {
   fPosition = n.fPosition ;
         fOrigin = n.fOrigin;
         fChartHeight=n.fChartHeight;
         fChartWidth=n.fChartWidth;
         fNumOfBars = n.fNumOfBars;
         fBarDistance=n.fBarDistance;
         fBarWidth =n.fBarWidth;
   fNumOfPosInterval = n.fNumOfPosInterval;
   fNumOfNegInterval = n.fNumOfNegInterval;
   fScale = n.fScale ;
}




/**********************************************************************
 * Function: BarChart::~BarChart()
 *
 * Purpose: destructor of class BarChart
***********************************************************************/

BarChart::~BarChart()
{

}




/**********************************************************************
 * Function: BarChart::GetBChartPosition()
 *
 * Parameters: None
 *
 * Return value: current bar chart position
 *
 * Purpose: get bar chart position
***********************************************************************/

IGPoint2D BarChart::GetBChartPosition() const
{
        return fPosition;
}



/**********************************************************************
 * Function: BarChart::GetBChartHeight()
 *
 * Parameters: None
 *
 * Return value: current bar chart height
 *
 * Purpose: get bar chart height
***********************************************************************/
GCoordinate BarChart::GetBChartHeight() const
{
        return fChartHeight;
}



/**********************************************************************
 * Function: BarChart::GetBChartWidth()
 *
 * Parameters: None
 *
 * Return value: current bar chart width
 *
 * Purpose: get bar chart position
***********************************************************************/
GCoordinate BarChart::GetBChartWidth()const
{
        return fChartWidth;
}




/**********************************************************************
 * Function: BarChart::SetBChartPosition()
 *
 * Parameters: the new position of bar chart
 *
 * Return value: None
 *
 * Purpose: set the value of bar chart position
***********************************************************************/
void BarChart::SetBChartPosition(IGPoint2D p)
{
        fPosition.fX=p.fX;
        fPosition.fY=p.fY;

        // recalute other related BarChart data members
        Recalculate() ;
}


/**********************************************************************
 * Function: BarChart::SetBChartHeight()
 *
 * Parameters: the new height of bar chart
 *
 * Return value: None
 *
 * Purpose: set the value of bar chart height
***********************************************************************/
void BarChart::SetBChartHeight(GCoordinate h)
{
        fChartHeight=h;

 // recalute other related BarChart data members
        Recalculate() ;
}


/**********************************************************************
 * Function: BarChart::SetBChartWidth()
 *
 * Parameters: the new width of bar chart
 *
 * Return value: None
 *
 * Purpose: set the value of bar chart width
***********************************************************************/
void BarChart::SetBChartWidth(GCoordinate w)
{
  fChartWidth=w;

        if (fNumOfBars != 0){
          fBarDistance=0.6*(fChartWidth/fNumOfBars);
          fBarWidth =0.4*(fChartWidth/fNumOfBars);
        }

  // recalute other related BarChart data members
        Recalculate() ;
}




/**********************************************************************
 * Function: BarChart::RecalAfterAdd()
 *
 * Purpose: recalculate BarChart data members after
 *          adding an element to the chart
***********************************************************************/
void BarChart::RecalAfterAdd()
{
                        fNumOfBars++;
                        Recalculate();
}

/**********************************************************************
 * Function: BarChart::RecalAfterRemove()
 *
 * Purpose: recalculate BarChart data members after
 *          removing an element to the chart
 **********************************************************************/

void BarChart::RecalAfterRemove()
{
                  fNumOfBars--;
                        Recalculate();
}

/*************************************************************************
 * Function: BarChart::GetBase()
 *
 * Return value: returns the base (3D) of the bar chart in graphic group form
 *
 * Purpose: constructs a 3D base for use with a bar chart
 *
**************************************************************************/

IGraphicGroup *BarChart::GetBase()
{
 // initialize an empty base
  IGraphicGroup *base = new IGraphicGroup();

  // 135 degrees = 2.3562 Radians
  IGPoint2D translator((-1)*fBarWidth*cos(2.3562), (-1)*fBarWidth*sin(2.3562));

        // left: the line indicating the left vertical side of the base
        IGLine2D left(fPosition
                      ,IGPoint2D(fPosition.fX ,fPosition.fY + fChartHeight));

  // construct the left panel
  IGPolygon2D baseLeft;
  baseLeft.append(left.startPoint());
  baseLeft.append(left.endPoint());
  baseLeft.append(left.endPoint()+translator);
  baseLeft.append(left.startPoint()+translator);

          //bottom: the line indicating the bottom side of the base
        IGLine2D bottom(IGPoint2D(fPosition.fX, fPosition.fY+fChartHeight)
                       ,IGPoint2D(fOrigin.fX+fChartWidth,fPosition.fY+fChartHeight));

        // construct the bottom panel
  IGPolygon2D baseBottom;
  baseBottom.append(bottom.startPoint());
  baseBottom.append(bottom.endPoint());
  baseBottom.append(bottom.endPoint()+translator);
  baseBottom.append(bottom.startPoint()+translator);

         //need to construct an origin base which is a horizontal panel passing
         // the barchart origin if there are negative data
  IGPolygon2D baseOrigin;
        if (fNumOfNegInterval != 0){
                //originLine: the line indicating the origin panel
                IGLine2D originLine(fOrigin
                                   ,IGPoint2D(fOrigin.fX+fChartWidth,fOrigin.fY));

          baseOrigin.append(originLine.startPoint());
          baseOrigin.append(originLine.endPoint());
          baseOrigin.append(originLine.endPoint()+translator);
          baseOrigin.append(originLine.startPoint()+translator);
        }

  // construct the back panel
        IGPoint2D tempPos = fPosition + translator ;
  IGPolygon2D baseBack;
  baseBack.append(tempPos);
  baseBack.append(tempPos+IGPoint2D(0,fChartHeight));
  baseBack.append(tempPos+IGPoint2D(fChartWidth, fChartHeight));
  baseBack.append(tempPos+IGPoint2D(fChartWidth, 0));

  //define fill color for back panel, origin panel and left panel
        IBaseColor bgColor(230);
        //define fill color for bottom panel
        IBaseColor bottomColor(100);

  IBaseColor frameColor;// default black color

  IGPolygon2D*  fPoly  ;

  // construct the bases by adding the panels to the graphic group
        if (fNumOfNegInterval != 0){
          //originPanel is needed if there are negative data
          fPoly = new IGPolygon2D(baseOrigin);
    base->adoptFirst(new IPolygon(fPoly, new IGrafBundle(bgColor,frameColor)));
        }

  fPoly = new IGPolygon2D(baseLeft);
  base->adoptFirst(new IPolygon(fPoly, new IGrafBundle(bgColor,frameColor)));

  fPoly = new IGPolygon2D(baseBottom);
  base->adoptFirst(new IPolygon(fPoly, new IGrafBundle(bottomColor,frameColor)));

        fPoly = new IGPolygon2D(baseBack);
  base->adoptFirst(new IPolygon(fPoly, new IGrafBundle(bgColor,frameColor)));

  return base;
}



/**********************************************************************
 * Function: BarChart::GetBar()
 *
 * Parameters:
 *   rect : indicates the height, and width of the bar
 *
 * Return value: returns the bar (3D) representing non_negative data in
 *               the form  of a graphic group
 *
 * Purpose: constructs a 3D bar from the specified rectangle and color
 *
***********************************************************************/

IGraphicGroup *BarChart::GetBar(IGRect2D rect)
{
  // initialize the empty bar
  IGraphicGroup *bar = new IGraphicGroup();

  // 135 degrees = 2.3562 Radians
  IGPoint2D translator((-1)*rect.width()*cos(2.3562), (-1)*rect.width()*sin(2.3562));

  // construct the main rectangle
  IGPolygon2D* rectPanel = new IGPolygon2D(rect);

  // construct the left panel
  IGPolygon2D* leftPanel = new IGPolygon2D(4);
  leftPanel->setPoint(0, rect.bottomRight());
  leftPanel->setPoint(1, rect.topRight());
  leftPanel->setPoint(2, rect.topRight()+translator);
  leftPanel->setPoint(3, rect.bottomRight()+translator);

  // construct the top panel
  IGPolygon2D* topPanel = new IGPolygon2D(4);
  topPanel->setPoint(0, rect.topLeft());
  topPanel->setPoint(1, rect.topLeft()+translator);
  topPanel->setPoint(2, rect.topRight()+translator);
  topPanel->setPoint(3, rect.topRight());

  // define color for rectPanel, leftPanel and topPanel
  IBaseColor rectColor(255, 0, 0); //Red color
        IBaseColor leftColor(128, 0, 0);
  IBaseColor topColor(255, 0, 0);

  IBaseColor frameColor;        // default black color

  // construct the bars by adding the panels to the graphic group
  bar->adoptFirst(new IPolygon(rectPanel, new IGrafBundle(rectColor,frameColor)));
  bar->adoptLast(new IPolygon(leftPanel, new IGrafBundle(leftColor,frameColor)));
  bar->adoptLast(new IPolygon(topPanel, new IGrafBundle(topColor,frameColor)));
  return bar;
}



/**********************************************************************
 * Function: BarChart::GetNegativeBar()
 *
 * Parameters:
 *   rect : indicates the height, and width of the bar
 *
 * Return value: returns the bar (3D) representing negative data in
 *               the form  of a graphic group
 *
 * Purpose: constructs a 3D bar from the specified rectangle and color
 *
***********************************************************************/

IGraphicGroup *BarChart::GetNegativeBar(IGRect2D rect)
{
  // initialize the empty bar
  IGraphicGroup *bar = new IGraphicGroup();

  // 135 degrees = 2.3562 Radians
  IGPoint2D translator((-1)*rect.width()*cos(2.3562), (-1)*rect.width()*sin(2.3562));

  // construct the main rectangle
  IGPolygon2D* rectPanel = new IGPolygon2D(rect);

  // construct the left panel
  IGPolygon2D* leftPanel = new IGPolygon2D(4);
  leftPanel->setPoint(0, rect.bottomRight());
  leftPanel->setPoint(1, rect.topRight());
  leftPanel->setPoint(2, rect.topRight()+translator);
  leftPanel->setPoint(3, rect.bottomRight()+translator);

   // construct the top panel
  IGPolygon2D* topPanel = new IGPolygon2D(4);
  topPanel->setPoint(0, rect.bottomLeft());
  topPanel->setPoint(1, rect.bottomLeft()+translator);
  topPanel->setPoint(2, rect.bottomRight()+translator);
  topPanel->setPoint(3, rect.bottomRight());

  // define color for rectPanel, leftPanel and topPanel
  IBaseColor rectColor(255, 0, 0); //Red color
        IBaseColor leftColor(128, 0, 0);
  IBaseColor topColor(10, 0, 0);

  IBaseColor frameColor;        // default black color

  // construct the bar by adding the panels to the graphic group
  bar->adoptFirst(new IPolygon(rectPanel, new IGrafBundle(rectColor,frameColor)));
  bar->adoptLast(new IPolygon(leftPanel, new IGrafBundle(leftColor,frameColor)));
  bar->adoptLast(new IPolygon(topPanel, new IGrafBundle(topColor,frameColor)));
  return bar;
}


/**********************************************************************
 * Function: BarChart::GetAllBars()
 *
 * Parameters: None
 *
 * Return value: returns all the bars representing all elements in barchart
 *               in the form of a graphic group
 *
 * Purpose: constructs 3D bars for the bar chart
 *
***********************************************************************/

IGraphicGroup *BarChart::GetAllBars()
{
  // initialize an empty group
  IGraphicGroup *allBars = new IGraphicGroup();

 //------------------------------------------------------------------
 // construct allBars group by going through each element in barchart
 //------------------------------------------------------------------

 //the distance between two adjacent ticks on Y direction
        GCoordinate tickDistance;
        tickDistance = fChartHeight /(fNumOfPosInterval +fNumOfNegInterval);

  GCoordinate current_pos; //position of current bar
        ChartType current_data; //data of current bar

        int i=1; //Note: A sequence starts from position 1 instead of 0
  current_pos= fOrigin.fX + 0.5 * fBarDistance; //position of the first bar

  while (i <= fNumOfBars){
           current_data= DataAtPosition(i);

           // rect  indicates the height and width of a current
           IGRect2D rect( current_pos
                              , fOrigin.fY- (current_data / fScale ) * tickDistance
                                                                        , current_pos + fBarWidth
                                                                        , fOrigin.fY);

           if (current_data >= 0)
                         allBars -> adoptLast(GetBar(rect)) ;
                 else
                         allBars -> adoptLast(GetNegativeBar(rect)) ;

    i++;
                current_pos +=fBarDistance+fBarWidth ;
 }

  return allBars;
}



/**********************************************************************
 * Function: BarChart::Draw()
 *
 * Parameters:
 *    DisplayPort: a grafport that barchart graphic draws to
 *
 * Return value: None
 *
 * Purpose: Draw the bar chart group
 *
***********************************************************************/
void BarChart::Draw(IGrafPort *DisplayPort)
{
  if ( IsEmpty() )
                return ;  // nothing will be drawn if the barchart is empty

        // initialize a barChart group
  IGraphicGroup *barChart = new IGraphicGroup();

  //construct the barChart group by adopting bases, ticks, labes and bars groups
        barChart->adoptFirst(GetBase());
        barChart->adoptLast(GetYTicks());
        barChart->adoptLast(GetYLabels());
        barChart->adoptLast(GetXTicks());
        barChart->adoptLast(GetXLabels());
        barChart->adoptLast(GetAllBars());

        // draw the bar chart
        barChart->draw(*DisplayPort) ;

        delete barChart ;
}



/**********************************************************************
 * Function: BarChart::Recalculate()
 *
 * Purpose: reccalculate other related BarChart data members after some of the
 *          data members are changed
***********************************************************************/

void BarChart::Recalculate()
{
    if ( fNumOfBars != 0){
                        fBarDistance=0.6*(fChartWidth/fNumOfBars);
                        fBarWidth=0.4*(fChartWidth/fNumOfBars);
                }
                else
                {
                  fBarDistance = 0;
                        fBarWidth = 0;
                        return ;
                }

    //find fNumOfPosInterval, fNumOfNegInterval and fScale
          FindIntervals();

                //distance between two adjacent ticks on Y direction
          GCoordinate tickDistance = fChartHeight /(fNumOfPosInterval +fNumOfNegInterval);

                //recalculate the barchart origin
                fOrigin.fX = fPosition.fX ;
          fOrigin.fY = fPosition.fY +  fNumOfPosInterval * tickDistance;
}


/**********************************************************************
 * Function: BarChart::FindIntervals()
 *
 * Purpose: Use an algorithm to find the proper number of  positive intervals
 *          and negative intervals on Y direction. The scale that one interval
 *          represents is also calculated.
***********************************************************************/
void BarChart::FindIntervals()
{
        ChartType  max ;
        ChartType  min;
        // max and min  are passed by reference
        MaxAndMin(max, min);

        // data range of the barchart
  ChartType range = max - min ;

        // initialize fScale to be 1
  fScale = 1 ;

        if (range == 0){
          fNumOfPosInterval = 1;
          fNumOfNegInterval = 0;
                fScale = 1 ;
    return ;
  }

        // let the range falls in [5, 50] by properly scaling it
        if ( range < 5){
                do {
                  fScale *= 0.1 ;
                  range *= 10; //scale up
                } while (range  < 5 );
        }
        else if (range >= 50)
        {
                do {
                  fScale *= 10 ;
      range *= 0.1 ; //scale down
                } while (range >= 50);
        }

  // determine whether the scale is a multiple of 1 , or 2, or 5
  int modd ;
        if (range <= 10 )
         // range falls in [5, 10]
    modd = 1;
        else if (range <= 20 )
          // range falls in  (10, 20]
          modd = 2;
        else
          // range falls in (20, 50]
          modd = 5;

 // get the fScale which represent the data value that one interval represents
 fScale *= modd ;

 //determine the number of positive intervals on Y direction
 if (max == 0.0)
         fNumOfPosInterval = 0;
 else
         fNumOfPosInterval = ceil(max / fScale) ;

 //determine the number of negative intervals on Y direction
 if ( min == 0.0)
         fNumOfNegInterval = 0 ;
 else
         fNumOfNegInterval = ceil(-min / fScale);

}



/**********************************************************************
 * Function: BarChart::GetYTicks()
 *
 * Purpose: construct all the ticks on Y direction into a graphic group
***********************************************************************/
IGraphicGroup* BarChart::GetYTicks()
{
   // initialize an empty tick group
   IGraphicGroup *tickGroup = new IGraphicGroup();

   IGLine2D* aLine;

         int i = 0;
         int sumOfInterval = fNumOfPosInterval +fNumOfNegInterval ;

   //distance between two adjacent ticks on Y direction
         GCoordinate tickDistance = fChartHeight /sumOfInterval;

         //construct ticks one by one from top to bottom
         while ( i <= sumOfInterval ){
                 IGLine2D  atick(IGPoint2D(fPosition.fX-3, fPosition.fY + tickDistance * i),
                                                  IGPoint2D(fPosition.fX, fPosition.fY + tickDistance * i));
                 aLine =  new IGLine2D(atick);
           tickGroup->adoptFirst(new ILine(aLine, new IGrafBundle(IBaseColor::kBlack)));
     i++ ;
         }

         return tickGroup ;
}


/**********************************************************************
 * Function: BarChart::GetYLabels()
 *
 * Purpose: construct all data labels on Y direction into a graphic group
***********************************************************************/
IGraphicGroup* BarChart::GetYLabels()
{
   // initialize an empty label group
   IGraphicGroup *labelGroup = new IGraphicGroup();

         //use IGraphicText to represent a  label
         IGraphicText* graText;

         // font used to display the label
         IFont  labelFont("Arial", 8);

         int i = 0;
         int sumOfInterval = fNumOfPosInterval +fNumOfNegInterval ;
         GCoordinate labelDistance =   fChartHeight  / sumOfInterval ;

         //construct labels one by one from top to bottom
         int j = fNumOfPosInterval;
         while ( i <= sumOfInterval ){
           // construct an IString from a double numeric data
                 IString str(fScale * j);

                 IText labelText(str);

                 // define the  font name and point size of the label text
                 labelText.addStyles(ITextTypefaceStyle(labelFont.name()));
                 labelText.addStyles(ITextPointSizeStyle(labelFont.pointSize()));

     graText = new IGraphicText(labelText, IGraphicText::kSingleLine);
                 graText->setLocation(IGPoint2D(fPosition.fX-30, fPosition.fY + labelDistance * i));

           labelGroup->adoptFirst(graText);

                 i++ ;
                 j-- ;
         }
         return labelGroup ;
}






/**********************************************************************
 * Function: BarChart::GetXTicks()
 *
 * Purpose: construct all the ticks on X direction into a graphic group
***********************************************************************/
IGraphicGroup* BarChart::GetXTicks()
{
   // initialize an empty tick group
   IGraphicGroup *tickGroup = new IGraphicGroup();

   IGLine2D* aLine;

         GCoordinate tickDistance = fBarDistance + fBarWidth ;

         //intersection point between left base and bottom base
         IGPoint2D bottomPos(fPosition.fX, fPosition.fY + fChartHeight);

         //construct ticks  from left to right on bottom base
         int i = 1;
         while ( i <= fNumOfBars ){
                 IGLine2D  atick(IGPoint2D(bottomPos.fX + tickDistance * i, bottomPos.fY ),
                                                  IGPoint2D(bottomPos.fX + tickDistance * i, bottomPos.fY + 4));

                 aLine =  new IGLine2D(atick);
           tickGroup->adoptFirst(new ILine(aLine, new IGrafBundle(IBaseColor::kBlack)));
     i++ ;
         }

         // need to construct ticks on origin base if there exist negative data
         if (fNumOfNegInterval != 0){
   i = 1;  // reset i to be 1
         while ( i <= fNumOfBars ){
                 IGLine2D  atick(IGPoint2D(fOrigin.fX + tickDistance * i, fOrigin.fY ),
                                                  IGPoint2D(fOrigin.fX + tickDistance * i, fOrigin.fY + 4));

                 aLine =  new IGLine2D(atick);
           tickGroup->adoptFirst(new ILine(aLine, new IGrafBundle(IBaseColor::kBlack)));
     i++ ;
         }

   }
         return tickGroup ;
}


/**********************************************************************
 * Function: BarChart::GetXLabels()
 *
 * Purpose: construct sequential labels on X direction into a graphic group
 *
***********************************************************************/
IGraphicGroup* BarChart::GetXLabels()
{
   // initialize an empty label group
   IGraphicGroup *labelGroup = new IGraphicGroup();

         //use IGraphicText to represent a  label
         IGraphicText* graText;

         // font used to display the label
         IFont  labelFont("Arial", 8);

         GCoordinate labelDistance = fBarDistance + fBarWidth ;

         //intersection point between left base and bottom base
         IGPoint2D bottomPos(fPosition.fX, fPosition.fY + fChartHeight);

         //construct labels one by one from left to rignt on bottom base
         int i = 1;
         while ( i <= fNumOfBars ){
           // construct an IString from a  numeric data
                 IString str(i);

                 IText labelText(str);

                 // define the  font name and point size of the label text
                 labelText.addStyles(ITextTypefaceStyle(labelFont.name()));
                 labelText.addStyles(ITextPointSizeStyle(labelFont.pointSize()));

     graText = new IGraphicText(labelText, IGraphicText::kSingleLine);
                 graText->setLocation(IGPoint2D(bottomPos.fX + i * labelDistance -0.5*labelDistance,
                                                bottomPos.fY + 15 ));

           labelGroup->adoptFirst(graText);

                 i++ ;
         }
         return labelGroup ;
}

