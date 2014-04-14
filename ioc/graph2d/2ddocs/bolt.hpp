// Revision: 61 1.6.1.2 samples/graph2d/2ddocs/bolt.hpp, ocsamples-L1, ioc.v400, 981111 
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

#ifndef _BOLT_HPP
#define _BOLT_HPP

#include <igraph2d.hpp>

class IBoltTop : public IMGraphic {
        StreamableDeclarationsMacro(IBoltTop);

public:
                                                IBoltTop();             // For streaming purposes only.
                                                IBoltTop(const IBoltTop& source);
                                                IBoltTop(GCoordinate boltDiameter, GCoordinate outerDiameter, const IGPoint2D& center);

        IBoltTop&                       operator=(const IBoltTop& source);

        virtual void            draw(IGrafPort& port) const;
        virtual IGPoint2D       alignmentBasePoint() const;
        virtual IGRect2D        geometricBounds() const;

        virtual void            transformBy(const IGrafMatrix& matrix);

private:
        IGrafMatrix                     fMatrix;
        IGPolygon2D                     fPolygon;       // This is the outer polygon
        IGEllipse2D                     fCircle;        // This is the inner circle
};

#endif // _BOLT_HPP
