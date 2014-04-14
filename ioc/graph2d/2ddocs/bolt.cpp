// Revision: 60  1.5.1.2  samples/graph2d/2ddocs/bolt.cpp, ocsamples-L1, ioc.v400, 981111  
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

#include "bolt.hpp"
#include <igrport.hpp>
#include <math.h>
#include <istrmmod.hpp>

const double kPi = 3.1415927;

IStreamModule gStreamModule("Bolt");
StreamableDefinitionsMacro(IBoltTop, gStreamModule);

IBoltTop::IBoltTop()
{
}

IBoltTop::IBoltTop(const IBoltTop& source)
        : fMatrix(source.fMatrix), fPolygon(source.fPolygon), fCircle(source.fCircle)
{
}

IBoltTop::IBoltTop(GCoordinate boltDiameter, GCoordinate outerDiameter, const IGPoint2D& center)
        : fCircle(center, boltDiameter / 2.0)
{
        // Calculate the hexagon polygon from these paramters
        // The side of the polygon = outerDiameter / 2.0
        IGPoint2DArray polygonPoints(6);
        IGPoint2D tmpPoint;
        unsigned long i;
        double theta;
        for (i = 0, theta = 0.0; i < 6; i++, theta += (2.0 * kPi) / 6.0)
        {
                tmpPoint.fX = center.fX + (outerDiameter / 2.0) * sin(theta);
                tmpPoint.fY = center.fY + (outerDiameter / 2.0) * cos(theta);
                polygonPoints.setPoint(i, tmpPoint);
        }

        fPolygon.setPoints(polygonPoints);
}

void
IBoltTop::draw(IGrafPort& port) const
{
        const IAttributeState* attrState = attributeState();
        if (attrState != NULL) {
                //
                // Draw the geometry with the bundle and the matrix
                // associated with this primitive.
                //
                port.draw(fPolygon, *attrState, fMatrix);
                port.draw(fCircle, *attrState, fMatrix);
        }
        else {
                // If there are a large number of primitives with same attributes
                // it is efficient to construct a local port and then render
                // geometries into this local port.
                //
                // ILinkedGrafPort concatenates the matrix with the state
                // information of the old port.
                //
                ILinkedGrafPort linkedPort(&port, kViewMatrix, &fMatrix);
                linkedPort.draw(fPolygon);
                linkedPort.draw(fCircle);
        }
}

IGPoint2D
IBoltTop::alignmentBasePoint() const
{
        // The alignment point is the center of the circle.
        IGPoint2D center(fCircle.center());
        return IGPoint2D(center.fX, center.fY);
}

IGRect2D
IBoltTop::geometricBounds() const
{
        // Get bounds of the polygon
        // pass the bounds to the bundle for altering.
        return fPolygon.bounds();
}

void
IBoltTop::transformBy(const IGrafMatrix& matrix)
{
        fMatrix.concatWith(matrix);
}

