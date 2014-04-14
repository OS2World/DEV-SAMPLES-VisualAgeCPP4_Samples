/******************************************************************************
* .FILE:         line.h                                                       *
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
#include <math.h>


class Line : public Graphics
{
public:

  double ivXStart;
  double ivYStart;
  double ivXEnd;
  double ivYEnd;


  Line(int graphicsKey, IString id, double xstart, double ystart,
                                    double xend,   double yend)

                                  : Graphics(graphicsKey, id),
                                    ivXStart(xstart),
                                    ivYStart(ystart),
                                    ivXEnd(xend),
                                    ivYEnd(yend)
                                    { }


  IBoolean operator== (Line const& line) const
    {
     return (this->ivXStart == line.ivXStart &&
             this->ivYStart == line.ivYStart &&
             this->ivXEnd == line.ivXEnd &&
             this->ivYEnd == line.ivYEnd);
    }


  void           draw() const
    {
     cout << "drawing "
          << Graphics::id()
          << endl
          << "with starting point: "
          << "(" << this->ivXStart
          << "|" << this->ivYStart << ")"
          << " and with ending point: "
          << "(" << this->ivXEnd
          << "|" << this->ivYEnd << ")"
          << endl;
    }


  void           lengthOfLine() const
    {
     cout << "The length of line "
          << Graphics::id()
          << " is: "
          << sqrt(pow(((this->ivXEnd) - (this->ivXStart)),2)
                + pow(((this->ivYEnd) - (this->ivYStart)),2))
          << endl;
    }

};
