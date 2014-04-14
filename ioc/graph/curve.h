/******************************************************************************
* .FILE:         curve.h                                                      *
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


class Curve : public Graphics
{
public:

  float ivXStart;
  float ivYStart;
  float ivXFix1;
  float ivYFix1;
  float ivXFix2;
  float ivYFix2;
  float ivXFix3;
  float ivYFix3;
  float ivXEnd;
  float ivYEnd;


  Curve(int graphicsKey, IString id,
        float xstart, float ystart,
        float xfix1, float yfix1,
        float xfix2, float yfix2,
        float xfix3, float yfix3,
        float xend, float yend)
                                  :  Graphics(graphicsKey, id),
                                     ivXStart(xstart),
                                     ivYStart(ystart),
                                     ivXFix1(xfix1),
                                     ivYFix1(yfix1),
                                     ivXFix2(xfix2),
                                     ivYFix2(yfix2),
                                     ivXFix3(xfix3),
                                     ivYFix3(yfix3),
                                     ivXEnd(xend),
                                     ivYEnd(yend)
                                     { }



  IBoolean operator== (Curve const& curve) const
    {
     return (this->ivXStart == curve.ivXStart &&
             this->ivYStart == curve.ivYStart &&
             this->ivXFix1  == curve.ivXFix1  &&
             this->ivYFix1  == curve.ivYFix1  &&
             this->ivXFix2  == curve.ivXFix2  &&
             this->ivYFix2  == curve.ivYFix2  &&
             this->ivXFix3  == curve.ivXFix3  &&
             this->ivYFix3  == curve.ivYFix3  &&
             this->ivXEnd   == curve.ivXEnd   &&
             this->ivYEnd   == curve.ivYEnd);
    }


  void           draw() const
    {
     cout << "drawing "
          << Graphics::id()
          << endl
          << "with starting point: "
          << "(" << this->ivXStart << "|"
          << this->ivYStart << ")"
          << endl
          << "and with fix points: "
          << "(" << this->ivXFix1 << "|" << this->ivYFix1 << ")"
          << "(" << this->ivXFix2 << "|" << this->ivYFix2 << ")"
          << "(" << this->ivXFix3 << "|" << this->ivYFix3 << ")"
          << endl
          << "and with ending point: "
          << "(" << this->ivXEnd << "|" << this->ivYEnd << ")"
          << endl;
    }


  void           lengthOfCurve() const
    {
     cout << "Length of "
          << Graphics::id()
          << " is: "
          << (sqrt(pow(((this->ivXFix1) - (this->ivXStart)),2)
                 + pow(((this->ivYFix1) - (this->ivYStart)),2))
            + sqrt(pow(((this->ivXFix2) - (this->ivXFix1)),2)
                 + pow(((this->ivYFix2) - (this->ivYFix1)),2))
            + sqrt(pow(((this->ivXFix3) - (this->ivXFix2)),2)
                 + pow(((this->ivYFix3) - (this->ivYFix2)),2))
            + sqrt(pow(((this->ivXEnd) -  (this->ivXFix3)),2)
                 + pow(((this->ivYEnd) - (this->ivYFix3)),2)))
          << endl;
    }
};
