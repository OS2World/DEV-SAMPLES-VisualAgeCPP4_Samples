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
* .FILE:         chart.cpp                                                    *
*                                                                             *
* .DESCRIPTION:  BarChart Sample Program:  Class Implementation               *
*                                                                             *
* .CLASSES:      Chart                                                        *
*                                                                             *
* .NOTE: WE RECOMMEND USING A FIXED SPACE FONT TO LOOK AT THE SOURCE          *
*                                                                             *
******************************************************************************/

#include "chart.hpp"

// The maximun number of elements that a chart can have
const int  gMaxNumOfElements = 10 ;



/**********************************************************************
 * Function: Chart::Chart()
 *
 * Purpose: default constructor for class Chart
 *
***********************************************************************/

Chart::Chart()
{

}



/**********************************************************************
 * Function: Chart::Chart(const Chart&n)
 *
 * Purpose: copy constructor for class Chart
 *
***********************************************************************/

Chart::Chart(const Chart& n)
{
  fChartData = n.fChartData;
}


/**********************************************************************
 * Function: Chart::~Chart()
 *
 * Purpose: destructor constructor for class Chart
 *
***********************************************************************/

Chart::~Chart()
{

}



/**********************************************************************
 * Function:  Chart::operator=()
 *
 * Purpose: assignment operator for class Chart
 *
***********************************************************************/

Chart& Chart::operator=(const Chart& n)
{
  if ( &n != this)
        fChartData = n.fChartData;
        return *this;

}




/**********************************************************************
 * Function:  Chart::AddAsFirst()
 *
 * Parameter:  element to be added to the chart
 *
 * Return Value:
 *               return true if  succeed, otherwise
 *               return  false if the chart is full
 *
 * Purpose: add an element as the first element to the chart
 *
***********************************************************************/

IBoolean Chart::AddAsFirst(ChartType const& elem)
{

        if (! IsFull()){
                fChartData.addAsFirst(elem);
                RecalAfterAdd();
                return true;
        }
        else
          return false;
}



/**********************************************************************
 * Function:  Chart::AddAsLast()
 *
 * Parameter:  element to be added to the chart
 *
 * Return Value:
 *               return true if  succeed, otherwise
 *               return  false if the chart is full
 *
 * Purpose: add an element as the last element to the chart
 *
***********************************************************************/
IBoolean Chart::AddAsLast(ChartType const& elem)
{
        if (! IsFull()){
                fChartData.addAsLast(elem);
                RecalAfterAdd();
                return true;
        }
        else
          return false;
}




/**********************************************************************
 * Function:  Chart::AddAtPosition()
 *
 * Parameter:
 *           i)   position at which the element is added
 *           ii)  element to be added to the chart
 *
 * Return Value:
 *               return true if  succeed, otherwise
 *               return  false if the position is invalid or chart is full
 *
 * Purpose: add an element at a poistion  to  the chart
 *
***********************************************************************/
IBoolean Chart::AddAtPosition(IPosition i,ChartType const& elem)
{
  // an element can be added as last whose position is one more
        // than the number of elements of the chart data
  if (i<1 || i > (fChartData.numberOfElements()+1))
    return false;

        if (! IsFull()){
                        fChartData.addAtPosition(i, elem);
                RecalAfterAdd();
                        return true;
                }
        else
                  return false;
}





/**********************************************************************
 * Function:  Chart::RemoveAsFirst()
 *
 * Return Value:
 *               return true if  succeed, otherwise
 *               return  false if the chart is empty
 *
 * Purpose: remove the first element from the chart
 *
***********************************************************************/

IBoolean Chart::RemoveAsFirst()
{
 if  (IsEmpty()){
                        return false;
  }
 else
 {
      fChartData.removeFirst();
                        RecalAfterRemove();
                        return true;
  }
}



/**********************************************************************
 * Function:  Chart::RemoveAsLast()
 *
 * Return Value:
 *               return true if  succeed, otherwise
 *               return  false if the chart is empty
 *
 * Purpose: remove the last element from the chart
 *
***********************************************************************/

IBoolean Chart::RemoveAsLast()
{
         if  (IsEmpty()){
                        return false;
  }
 else
 {
      fChartData.removeLast();
                        RecalAfterRemove();
                        return true;
  }
}



/**********************************************************************
 * Function:  Chart::RemoveAtPosition()
 *
 * Parameter:  position at which the element is  removed
 *
 * Return Value:
 *               return true if  succeed, otherwise
 *               return  false if the position is invalid or chart is empty
 *
 * Purpose: remove an element at a poistion from the chart
 *
***********************************************************************/
IBoolean Chart::RemoveAtPosition(IPosition i)
{
        if (i<1 || i>fChartData.numberOfElements())
                return false;

        if  (IsEmpty())
                        return false;
        else
  {
      fChartData.removeAtPosition(i);
                        RecalAfterRemove();
                        return true;
         }
}




/**********************************************************************
 * Function:  Chart::PosCheck()
 *
 * Parameter:  position that needs to be check
 *
 * Return Value:  return true if the position is valid , otherwise
 *                return false.
 *
 * Purpose: check whether a position given is valid or not
 *
***********************************************************************/
IBoolean  Chart::PosCheck(IPosition i) const
{
         if (i<1 || i>fChartData.numberOfElements())
                return false;
        else
          return true;
}



/**********************************************************************
 * Function:  Chart::DataAtPosition()
 *
 * Parameter:  position at which the element is  retrieved
 *
 * Return Value:  the element at a specified position
 *
 * Purpose: retrieve an element at a poistion of the chart
 *
***********************************************************************/
ChartType  Chart::DataAtPosition(IPosition i) const
{
        return fChartData.elementAtPosition(i);
}



/**********************************************************************
 * Function:  Chart::ReplaceAtPosition()
 *
 * Parameter:
 *            i)  position at which the element need to be replaced
 *            ii) the new element used to replace
 *
 * Return Value:
 *            return true if  succeed, otherwise
 *            return  false if the position is invalid
 *
 * Purpose: replace  an element at a poistion of the chart
 *
***********************************************************************/
IBoolean Chart::ReplaceAtPosition( IPosition i, ChartType const& elem)
{
  if (i<1 || i>fChartData.numberOfElements())
                return false ;
        else{
                RemoveAtPosition(i);
                AddAtPosition(i,elem);
                return true ;
        }
}


/**********************************************************************
 * Function:  Chart::IsFull()
 *
 * Return Value:  return true if the chart is full, otherwise return false
 *
 * Purpose:  test whether the chart is full or not
 *
***********************************************************************/
IBoolean Chart::IsFull() const
{
        if( fChartData.numberOfElements() >= gMaxNumOfElements)
                return true;
        else
                return false;
}


/**********************************************************************
 * Function:  Chart::isEmpty()
 *
 * Return Value:  return true if the chart is empty, otherwise return false
 *
 * Purpose:  test whether the chart is empty or not
 *
***********************************************************************/
IBoolean Chart::IsEmpty() const
{
  return (fChartData.isEmpty());
}




/**********************************************************************
 * Function:  Chart::MaxAndMin()
 *
 * Parameter:
 *             i)  a reference to the maximum element of the chart
 *             ii) a reference to the minimum element of the chart
 *
 * Return Value: None
 *
 * Purpose: find the maximum and minimum element by reference
 *
***********************************************************************/
void Chart::MaxAndMin(ChartType& max, ChartType& min) const
{
        max = 0;
        min = 0;

        if (!IsEmpty()){
    ChartType temp ;
                for(int i=1; i<= fChartData.numberOfElements(); i++){
                        temp = fChartData.elementAtPosition(i);
                        if (temp > max)
                                max = temp ;
                        else if (temp < min )
                                min = temp ;
                }
        }
}
