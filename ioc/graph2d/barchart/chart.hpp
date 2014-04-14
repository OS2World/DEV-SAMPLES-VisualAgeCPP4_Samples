#ifndef _CHART_
#define _CHART_

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
* .FILE:         chart.hpp                                                    *
*                                                                             *
* .DESCRIPTION:  BarChart Sample Program:  Class Header                       *
*                                                                             *
* .CLASSES:      Chart                                                        *
*                                                                             *
* .NOTE: WE RECOMMEND USING A FIXED SPACE FONT TO LOOK AT THE SOURCE          *
*                                                                             *
******************************************************************************/

#include <igrport.hpp>

//Use the default Sequence called ISequence.
#include <iseq.h>
typedef double  ChartType;
typedef ISequence <ChartType> ChartSequence;


class Chart{
 public:
  // constructors
        Chart();
        Chart(const Chart& n);

        // destructor
        ~Chart();

        //assignment operator
        Chart& operator=(const Chart& n);

        // Add an  element to the chart
        IBoolean AddAsFirst(ChartType const& elem);
        IBoolean AddAsLast(ChartType const& elem);
        IBoolean AddAtPosition(IPosition i, ChartType const& elem);

 // Remove an element from the chart
        IBoolean RemoveAtPosition(IPosition i);
        IBoolean RemoveAsFirst();
        IBoolean RemoveAsLast();

        // change an element in a chart
        IBoolean ReplaceAtPosition(IPosition i,ChartType const& elem );

        // Test whether the chart is full.
  IBoolean IsFull() const;

  // Test whether the chart is empty.
  IBoolean IsEmpty() const;

        // check whether the position given is valid or not.
        IBoolean PosCheck(IPosition i) const;


        // return an element in the chart at one particular position
        ChartType DataAtPosition(IPosition i)const;

        // Get the maximum and minimum element in the chart
  void MaxAndMin(ChartType& max, ChartType& min) const;

protected:
  // recalculate after adding an element
  virtual void RecalAfterAdd()=0;

        //recalculate after removing an element
        virtual void RecalAfterRemove()=0;

        // draw the chart
        virtual void Draw(IGrafPort *DisplayPort) = 0;

 private:
   //use a sequence to represent the elements of a chart
        ChartSequence fChartData;
} ;
#endif // _CHART_
