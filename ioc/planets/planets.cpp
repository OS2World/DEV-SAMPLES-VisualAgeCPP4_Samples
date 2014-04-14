/******************************************************************************
* .FILE:         planets.cpp                                                  *
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

/*---------------------------------------------------------------*\
|  planets.CPP  -  All known planets are handled in a Sorted Set. |
|                                                     """"""""""  |
|     This example creates several sorted sets of planets.        |
|     The sort order is based on each planets distance from       |
|     the sun.                                                    |
\*---------------------------------------------------------------*/

#include <iostream.h>

                     // Let's use the Sorted Set Default Variant:
#include <iss.h>

                     // Get Class Planet:
#include "planet.h"



int main()
{ ISortedSet <Planet>  allPlanets, heavyPlanets, brightPlanets;
                      // A cursor to cursor through allPlanets:
  ISortedSet <Planet>::Cursor aPCursor (allPlanets);

  SayPlanetName showPlanet;

  allPlanets.add (Planet("Earth",   149.60f,   1.0000f, 99.9f));
  allPlanets.add (Planet("Jupiter",  778.3f,  317.818f, -2.4f));
  allPlanets.add (Planet("Mars",     227.9f,   0.1078f, -1.9f));
  allPlanets.add (Planet("Mercury",  57.91f,   0.0558f, -0.2f));
  allPlanets.add (Planet("Neptune",  4498.f,   17.216f, +7.6f));
  allPlanets.add (Planet("Pluto",    5910.f,     0.18f,+14.7f));
  allPlanets.add (Planet("Saturn",   1428.f,   95.112f, +0.8f));
  allPlanets.add (Planet("Uranus",   2872.f,   14.517f, +5.8f));
  allPlanets.add (Planet("Venus",   108.21f,   0.8148f, -4.1f));


  forICursor (aPCursor) {
    if (allPlanets.elementAt (aPCursor).isHeavy ())
      heavyPlanets.add (allPlanets.elementAt (aPCursor));

    if (allPlanets.elementAt (aPCursor).isBright ())
      brightPlanets.add (allPlanets.elementAt (aPCursor));
  }

  cout << endl << endl << "All Planets: " << endl;
  allPlanets.allElementsDo (showPlanet);

  cout << endl << endl << "Heavy Planets: " << endl;
  heavyPlanets.allElementsDo (showPlanet);

  cout << endl << endl << "Bright Planets: " << endl;
  brightPlanets.allElementsDo (showPlanet);

  cout << endl << endl << "Bright-or-Heavy Planets: " << endl;
  brightPlanets.unionWith (heavyPlanets);
  brightPlanets.allElementsDo (showPlanet);

  cout << endl << endl
       << "Did you notice that all these Sets are sorted"
       << " in the same order"
       << endl
       << " (distance of planet from sun) ? " << endl;

  return 0;
}
