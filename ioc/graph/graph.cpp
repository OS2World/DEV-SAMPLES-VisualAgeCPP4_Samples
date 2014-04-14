/******************************************************************************
* .FILE:         graph.cpp                                                    *
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
/*--------------------------------------------------------------*\
|  graph.CPP  - demonstrate how to use collection class pointers |
|                                      """"""""""""""""""""""""" |
|  Different graphical shapes (curves, circles, lines)           |
|  inherit from an abstract class  "graph".                      |
|  Managed element pointers for these different shapes are       |
|  stored in one collection, a key sorted set.                   |
|  These pointers are used to draw the different shapes.         |
\*--------------------------------------------------------------*/

#include <iostream.h>
#include "graph.h"
#include "line.h"
#include "circle.h"
#include "curve.h"

#include <iptr.h>
#include <ikss.h>

typedef IMngElemPointer <Graphics> MngGraphicsPointer;
typedef IKeySortedSet <MngGraphicsPointer, int> MngPointerKSet;

ostream & operator <<
         (ostream & sout,
          MngPointerKSet
          const& mgdPointerKSet)
{
        MngGraphicsPointer drawObject;
        MngPointerKSet::Cursor
        gpsCursor(mgdPointerKSet);

   forICursor(gpsCursor)
     {
        drawObject = gpsCursor.element();

        sout << endl
             << " Key is: " <<  drawObject->graphicsKey()
             << endl
             << " ID is: " <<  drawObject->id()
             << endl;

        drawObject->draw();

     } /* endfor */


   return sout;
}


 int main ()

 {

     MngPointerKSet graphMngPointerKSet;

     /**********************************************************/
     /*   Adding  curve pointers, circle pointers and line     */
     /*   pointers to the graphMngPointerKSet.                 */
     /**********************************************************/

      //Creating curve objects and adding pointers to the collections

      MngGraphicsPointer pcurve1 (new Curve
       (10, "Curve 1",
       1.1, 4.3,
       2.1, 6.4,
       3.1, 9.7,
       4.1, 6.5,
       5.1, 7.4), IINIT);
      MngGraphicsPointer pcurve2 (new Curve
       (20 ,"Curve 2",
       1.2, 3.9,
       2.2, 5.9,
       3.2, 8.8,
       4.2, 7.5,
       5.2, 9.4), IINIT);

      graphMngPointerKSet.add(pcurve1);
      graphMngPointerKSet.add(pcurve2);


      //Creating circle objects and adding pointers to the collections

      MngGraphicsPointer pcircle1 (new Circle
       (40 , "Circle 1" , 1.0, 1.0, 1.0), IINIT);
      MngGraphicsPointer pcircle2 (new Circle
       (50 , "Circle  2", 2.0, 2.0, 2.0), IINIT);

      graphMngPointerKSet.add(pcircle1);
      graphMngPointerKSet.add(pcircle2);

      //Creating line objects and adding pointers to the collections

      MngGraphicsPointer pline1 (new Line
       (70 , "Line 1" , 1.1 , 1.1 , 5.1 , 5.1), IINIT);
      MngGraphicsPointer pline2 (new Line
       (80 , "Line 2" , 2.2 , 2.2 , 5.2 , 5.2), IINIT);
      /** if you want to have a normal C-pointer: **/
      Line* cPointerToLine = new Line
       (90 , "Line 3" , 3.3 , 3.3 , 5.3 , 5.3);
      MngGraphicsPointer pline3 (cPointerToLine, IINIT);

      graphMngPointerKSet.add(pline1);
      graphMngPointerKSet.add(pline2);
      graphMngPointerKSet.add(pline3);

      cout << "Drawing the shapes from the key set "
           << "of Managed Pointers: "
           << endl
           << graphMngPointerKSet
           << endl << " " << endl;

      graphMngPointerKSet.elementWithKey(70)->draw();
      cPointerToLine->draw();
      pline3->draw();

  /********************************************************/
  /* Now we are about to end the program.                 */
  /* The objects referenced by managed pointers are       */
  /* automatically deleted. See what happens in the       */
  /* output of the program.                               */
  /********************************************************/

  return 0;

 }
