// Revision: 64 1.4.1.2 samples/graph2d/2ddocs/exbase.cpp, ocsamples-L1, ioc.v400, 981111 
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

#include <icoordsy.hpp>         // ICoordinateSystem
#include <iexgrprt.hpp>         // IExtendedRootGrafPort
#include <iwindow.hpp>          // IWindow
#include "examples.hpp"         // WagonExample, StandardExample

//------------------------------------------------------------------------------
// StandardExample

void
StandardExample::run(IWindow& theWindow)
{
        EDeviceCoordinateSystem coordSystem = kLeftHand;
        if (ICoordinateSystem::applicationOrientation() == ICoordinateSystem::originLowerLeft)
        {
                coordSystem = kRightHand;
        }

        IManagedPresSpaceHandle dc(&theWindow);
        IExtendedRootGrafPort port(dc, coordSystem);
        draw(port);
}

//------------------------------------------------------------------------------
// StarExample

void
StarExample::draw(IGrafPort& port)
{
        // Construct a polygon geometry centered around the point (0,0).
        IGPolygon2D* star = new IGPolygon2D;
        star->append(IGPoint2D(0,-100));
        star->append(IGPoint2D(-20,-20));
        star->append(IGPoint2D(-100,-20));
        star->append(IGPoint2D(-30,20));
        star->append(IGPoint2D(-60,100));
        star->append(IGPoint2D(0,40));
        star->append(IGPoint2D(90,120));
        star->append(IGPoint2D(30,20));
        star->append(IGPoint2D(100,-20));
        star->append(IGPoint2D(20,-20));

        // Construct the polygon graphic from the geometry.
        IPolygon starGraphic(star);

        // Give the graphic a fat black frame.
        starGraphic.adoptAttributeState(new IFrameBundle(kDefaultFrameColor, kDefaultPenWidth));

        // Move the graphic so it is centered around the point (160,160).
        // [note: all of the points which make up this graphic are offset
        // from (0,0) so translating by a certain point moves the center
        // of the graphic to that point].
        starGraphic.translateBy(IGPoint2D(160,160));

        // Draw the original graphic.
        starGraphic.draw(port);

        // From now on, draw it filled with gray.
        starGraphic.adoptAttributeState(new IFillBundle(kDefaultFillColor));

        // Now, invoke the example code.
        handleDraw(port, starGraphic);
}

//------------------------------------------------------------------------------
// WagonExample constructor

WagonExample::WagonExample()
        : InteractiveExample(NULL)
{
        // A definition of this function must exist to prevent link errors.
}

