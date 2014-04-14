/******************************************************************************
* .FILE:         circle.h                                                     *
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

#include <istring.hpp>

class Circle : public Graphics
{
public:

  float ivXCenter;
  float ivYCenter;
  float ivRadius;


  Circle(int graphicsKey, IString id ,
         double xCenter, double yCenter,
         double radius)
                          : Graphics(graphicsKey, id),
                            ivXCenter(xCenter),
                            ivYCenter(yCenter),
                            ivRadius(radius)
                            { }


  IBoolean operator== (Circle const& circle) const
    {
     return (this->ivXCenter == circle.ivXCenter &&
             this->ivYCenter == circle.ivYCenter &&
             this->ivRadius == circle.ivRadius);
    }


  void          draw() const
    {
     cout << "drawing "
          << Graphics::id()
          << endl
          << "with center: "
          << "(" << this->ivXCenter << "|"
          << this->ivYCenter << ")"
          << " and with radius: "
          << this->ivRadius
          << endl;
    }


  void          circumference() const
    {
     cout << "The circumference of "
          << Graphics::id()
          << " is: "
          << ((this->ivRadius)*2*3.14)
          << endl;
    }

};
