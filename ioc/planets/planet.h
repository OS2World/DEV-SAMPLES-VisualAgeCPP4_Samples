/******************************************************************************
* .FILE:         planet.h                                                     *
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

/*-------------------------------------------------------------*\
|  planet.h  -  Class Planet for use in our Sorted Set example  |
\*-------------------------------------------------------------*/
#include <iostream.h>
#include <iappl.h>

class Planet   {
 private:
   char* plname;
   float dist;
   float mass;
   float bright;

 public:
     // Let's use the compiler generated default for
     // the copy constructor

   Planet(char* aname, float adist, float amass, float abright) :
     plname(aname), dist(adist),  mass(amass), bright(abright) {}

     // For any Set we need to provide element equality.
   IBoolean operator== (Planet const& aPlanet) const
      { return plname == aPlanet.plname; }

     // For a Sorted Set we need to provide element comparision.
   IBoolean operator< (Planet const& aPlanet) const
      { return dist < aPlanet.dist; }

   char*   name()     { return  plname; }

   IBoolean isHeavy()  { return (mass   > 1.0); }
   IBoolean isBright() { return (bright < 0.0); }
};


/*-------------------------------------------------------------*\
|   Applicator                                                  |
\*-------------------------------------------------------------*/

class SayPlanetName : public IApplicator<Planet>   {
 public:
   virtual IBoolean applyTo(Planet& p)
         { cout << " " << p.name() << " "; return True;}
};

