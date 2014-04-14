// Revision: 62 1.5.1.6 samples/graph2d/2ddocs/examples.cpp, ocsamples-L1, ioc.v400, 981111 
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
#include <iexgrprt.hpp>         // IGrafPort, IExtendedRootGrafPort, EDeviceCoordinateSystem
#include <ipoint.hpp>           // IPoint
#include <iwindow.hpp>          // IWindow
#include "examples.hpp"         // the examples
#include "bolt.hpp"             // IBoltTop

const IBaseColor::EPredefinedColor Example::kDefaultFrameColor = IBaseColor::kBlack;
const IBaseColor::EPredefinedColor Example::kDefaultFillColor = IBaseColor::kPaleGray;
const GCoordinate Example::kDefaultPenWidth = 3;

const IBaseColor::EPredefinedColor WagonExample::kSelectionColor = IBaseColor::kRed;

//------------------------------------------------------------------------------
// BoltExample

void
BoltExample::draw(IGrafPort& port)
{
        IBoltTop bolt(75, 125, IGPoint2D(100,100));

        bolt.adoptAttributeState(new IFrameBundle(kDefaultFrameColor, kDefaultPenWidth));
        bolt.draw(port);
}


//------------------------------------------------------------------------------
// StarRotateCenterExample

void
StarRotateCenterExample::handleDraw(IGrafPort& port, IPolygon& starGraphic)
{
        // Rotate graphic by 15 degrees clockwise around its center.
        starGraphic.rotateBy(15, starGraphic.geometricBounds().center());
        starGraphic.draw(port);
}


//------------------------------------------------------------------------------
// StarRotateViewOriginExample

void
StarRotateViewOriginExample::handleDraw(IGrafPort& port, IPolygon& starGraphic)
{
        // Rotate graphic by 15 degrees clockwise around the view origin.
        starGraphic.rotateBy(15); // or starGraphic.rotateBy(-15, IGPoint2D::origin());
        starGraphic.draw(port);
}


//------------------------------------------------------------------------------
// StarRotateArbitraryPointExample

void
StarRotateArbitraryPointExample::handleDraw(IGrafPort& port, IPolygon& starGraphic)
{
        // Rotate graphic by 15 degrees clockwise around an arbitrary point.
        starGraphic.rotateBy(15, IGPoint2D(0,200));
        starGraphic.draw(port);
}


//------------------------------------------------------------------------------
// StarScaleCenterExample

void
StarScaleCenterExample::handleDraw(IGrafPort& port, IPolygon& starGraphic)
{
        // Scale the graphic to 1.5 times its width, and half its height.
        starGraphic.scaleBy(IGPoint2D(1.50,.50), starGraphic.geometricBounds().center());
        starGraphic.draw(port);
}


//------------------------------------------------------------------------------
// StarScaleViewOriginExample

void
StarScaleViewOriginExample::handleDraw(IGrafPort& port, IPolygon& starGraphic)
{
        // Scale the graphic to 1.5 times its width, and half its height.
        starGraphic.scaleBy(IGPoint2D(1.50,.50)); // or starGraphic.scaleBy(IGPoint2D(...), IGPoint2D::origin());
        starGraphic.draw(port);
}


//------------------------------------------------------------------------------
// StarScaleArbitraryPointExample

void
StarScaleArbitraryPointExample::handleDraw(IGrafPort& port, IPolygon& starGraphic)
{
        // Scale the graphic to 1.5 times its width, and half its height.
        starGraphic.scaleBy(IGPoint2D(1.50,.50), IGPoint2D(0,200));
        starGraphic.draw(port);
}


//------------------------------------------------------------------------------
// StarMirrorXExample

void
StarMirrorXExample::handleDraw(IGrafPort& port, IPolygon& starGraphic)
{
        // Mirror the graphic about its X-axis using a negative value for the Y scaling factor.
        starGraphic.scaleBy(IGPoint2D(1.0, -1.0), starGraphic.geometricBounds().center());
        starGraphic.draw(port);
}


//------------------------------------------------------------------------------
// StarMirrorYExample

void
StarMirrorYExample::handleDraw(IGrafPort& port, IPolygon& starGraphic)
{
        // Mirror the graphic about its Y-axis using a negative value for the X scaling factor.
        starGraphic.scaleBy(IGPoint2D(-1.0, 1.0), starGraphic.geometricBounds().center());
        starGraphic.draw(port);
}


//------------------------------------------------------------------------------
// StarMirrorXYExample

void
StarMirrorXYExample::handleDraw(IGrafPort& port, IPolygon& starGraphic)
{
        // Mirror the graphic about its X- and Y-axes using negative values for both
        // scaling factors.
        starGraphic.scaleBy(IGPoint2D(-1.0, -1.0), starGraphic.geometricBounds().center());
        starGraphic.draw(port);
}


//------------------------------------------------------------------------------
// StarTranslateExample

void
StarTranslateExample::handleDraw(IGrafPort& port, IPolygon& starGraphic)
{
        // Move the graphic down and to the right.
        starGraphic.translateBy(IGPoint2D(15,30));
        starGraphic.draw(port);
}


//------------------------------------------------------------------------------
// WagonExample

IGraphicGroup*
WagonExample::createWagon(bool moveIt)
{
        // Create the bundles which will be used later.
        IFillAndFrameBundle backBundle(IBaseColor(128), IBaseColor::kBlack);
        IFillAndFrameBundle frontAndLeftBundle(IBaseColor(192), IBaseColor::kBlack);
        IFillAndFrameBundle rightBundle(IBaseColor(64), IBaseColor::kBlack);
        IFillAndFrameBundle wheelBundle(IBaseColor::kWhite, IBaseColor::kBlack, 1.5);
        IFillBundle hubCapBundle(IBaseColor::kBlack);

        // Create the geometries.
        IGPolygon2D* backPanelGeometry = new IGPolygon2D(IGRect2D(50,60,170,110));
        IGPolygon2D* frontPanelGeometry = new IGPolygon2D(IGRect2D(70,80,190,130));
        IGPolygon2D* leftPanelGeometry = new IGPolygon2D;
        leftPanelGeometry->append(IGPoint2D(50,60));
        leftPanelGeometry->append(IGPoint2D(70,80));
        leftPanelGeometry->append(IGPoint2D(70,130));
        leftPanelGeometry->append(IGPoint2D(50,110));

        IGPolygon2D* rightPanelGeometry = new IGPolygon2D;
        rightPanelGeometry->append(IGPoint2D(170,60));
        rightPanelGeometry->append(IGPoint2D(190,80));
        rightPanelGeometry->append(IGPoint2D(190,130));
        rightPanelGeometry->append(IGPoint2D(170,110));

        IPolygon* backPanel = new IPolygon(backPanelGeometry, new IGrafBundle(backBundle));
        IPolygon* frontPanel = new IPolygon(frontPanelGeometry, new IGrafBundle(frontAndLeftBundle));
        IPolygon* leftPanel = new IPolygon(leftPanelGeometry, new IGrafBundle(frontAndLeftBundle));
        IPolygon* rightPanel = new IPolygon(rightPanelGeometry, new IGrafBundle(rightBundle));

        IEllipse* rearAwayWheel = new IEllipse(new IGEllipse2D(IGRect2D(40,100,90,150)));
        IEllipse* hubCap = new IEllipse(*rearAwayWheel);

        rearAwayWheel->adoptBundle(new IGrafBundle(wheelBundle));
        hubCap->adoptBundle(new IGrafBundle(hubCapBundle));
        hubCap->scaleBy(IGPoint2D(.75, .25), hubCap->geometricBounds().center());

        IGraphicGroup* rearAwayHubWheel = new IGraphicGroup;
        rearAwayHubWheel->adoptFirst(rearAwayWheel);
        rearAwayHubWheel->adoptLast(hubCap);

        IGraphicGroup* frontAwayHubWheel = new IGraphicGroup(*rearAwayHubWheel);
        frontAwayHubWheel->translateBy(IGPoint2D(90,0));

        IGraphicGroup* rearTowardHubWheel = new IGraphicGroup(*rearAwayHubWheel);
        rearTowardHubWheel->translateBy(IGPoint2D(20,10));

        IGraphicGroup* frontTowardHubWheel = new IGraphicGroup(*rearAwayHubWheel);
        frontTowardHubWheel->translateBy(IGPoint2D(110,10));

        IGraphicGroup* wagon = new IGraphicGroup;

        // Adopt the "away" wheels
        wagon->adoptFirst(rearAwayHubWheel);
        wagon->adoptLast(frontAwayHubWheel);

        // Adopt the body
        wagon->adoptLast(backPanel);
        wagon->adoptLast(leftPanel);
        wagon->adoptLast(rightPanel);
        wagon->adoptLast(frontPanel);

        // Adopt the "toward" wheels
        wagon->adoptLast(rearTowardHubWheel);
        wagon->adoptLast(frontTowardHubWheel);

        if (moveIt)
        {
                wagon->translateBy(IGPoint2D(200,0));
                rearAwayHubWheel->rotateBy(90, rearAwayHubWheel->geometricBounds().center());
                frontAwayHubWheel->rotateBy(90, frontAwayHubWheel->geometricBounds().center());
                rearTowardHubWheel->rotateBy(90, rearTowardHubWheel->geometricBounds().center());
                frontTowardHubWheel->rotateBy(90, frontTowardHubWheel->geometricBounds().center());
        }

        return wagon;
}

void
WagonExample::draw(IGrafPort& port)
{
        if (fOriginalWagon == NULL)
        {
                fOriginalWagon = createWagon();
        }

        if (fMovedWagon == NULL)
        {
                fMovedWagon = createWagon(true);
        }

        fOriginalWagon->draw(port);
        fMovedWagon->draw(port);

        if (fSelection != NULL)
        {
                fSelection->draw(port);
        }
}

bool
WagonExample::handleMouseClick(IMouseClickEvent& event)
{
        // This function will be called for each type of mouse action, but
        // we only care about clicks, so bail out if we aren't called to handle
        // a click.
        if (event.mouseAction() != IMouseClickEvent::click)
        {
                return false;
        }

        if (fOriginalWagon == NULL || fMovedWagon == NULL)
        {
                // If the wagons are NULL, something has gone wrong.
                return false;
        }

        IGPoint2D mousePos(event.mousePosition());

        IGraphicGroup* wagon = NULL;
        if (fOriginalWagon->geometricBounds().contains(mousePos))
        {
                wagon = fOriginalWagon;
        }
        else if (fMovedWagon->geometricBounds().contains(mousePos))
        {
                wagon = fMovedWagon;
        }

        // Toss the old selection graphic
        delete fSelection;
        fSelection = NULL;

        // If one of the wagons was hit, find out which graphic within it actually has the mouse.
        if (wagon != NULL)
        {
                IMGraphic* graphic;
                IGraphicIterator* iterator = wagon->createIterator();
                for (graphic = iterator->last(); graphic != NULL; graphic = iterator->previous())
                {
                        // Find the first, backmost graphic that contains the mouse position
                        IGRect2D bounds(wagon->matrix()->transformBounds(graphic->looseFitBounds()));
                        if (bounds.contains(mousePos))
                        {
                                // Construct the selection graphic
                                fSelection = new IPolygon(new IGPolygon2D(bounds));
                                fSelection->adoptAttributeState(new IFrameBundle(kSelectionColor));

                                // Exit the loop
                                break;
                        }
                }

                delete iterator;
        }

        // The selection changed, so redraw everything.
        window()->refresh();

        return true;
}

//------------------------------------------------------------------------------
// CAGArbitraryAreaExample

void
CAGArbitraryAreaExample::draw(IGrafPort& port)
{
        // Start with some IGArea.
        IGArea cag(IGRect2D(30,50,150,110));

        // Make an ellipse and add it to the CAG.
        IGEllipse2D ellipseGeometry(IGRect2D(70,70,140,140));
        cag += IGArea(ellipseGeometry);

        // Make funny shaped polygon.
        IGPolygon2D polygonGeometry;
        polygonGeometry.append(IGPoint2D(105,95));
        polygonGeometry.append(IGPoint2D(150,95));
        polygonGeometry.append(IGPoint2D(190,155));
        polygonGeometry.append(IGPoint2D(190,75));
        polygonGeometry.append(IGPoint2D(150,155));

        // Remove the polygon from the CAG.
        cag -= polygonGeometry;

        // Draw the result.
        port.draw(cag, IFillAndFrameBundle(kDefaultFillColor, kDefaultFrameColor, kDefaultPenWidth));
}


//------------------------------------------------------------------------------
// CAGAppleExample

void
CAGAppleExample::draw(IGrafPort& port)
{
        // Start with an IGArea defining the left side of the apple.
        IGArea apple(IGEllipse2D(IGRect2D(0,64,96,176)));

        // Add in the right side of the apple.
        apple += IGEllipse2D(IGRect2D(32,64,128,176));

        // And the apple stem.
        apple += IGRect2D(63,32,65,72);

        // Now, add the right leaf.
        IGArea leaf(IGEllipse2D(IGRect2D(40,16,88,64)));
        leaf *= IGEllipse2D(IGRect2D(64,40,112,88));
        apple += leaf;

        // Flip the right leaf around and use it as the left leaf.
        leaf.transformBy(IGrafMatrix(IGPoint2D(-1,1), IGPoint2D(64,0)));
        leaf.transformBy(IGrafMatrix(IGPoint2D(0,-16)));
        apple += leaf;

        // Draw the result.
        port.draw(apple, IFillAndFrameBundle(kDefaultFillColor, kDefaultFrameColor, kDefaultPenWidth));
}


//------------------------------------------------------------------------------
// CAGBananaExample

void
CAGBananaExample::draw(IGrafPort& port)
{
        // Start with an IGArea defining the left side of the banana.
        IGArea banana(IGEllipse2D(IGRect2D(0,48,192,240)));

        // Remove a large ellipse to define the right side of the banana.
        banana -= IGEllipse2D(IGRect2D(32,0,224,288));

        // Chop off the ends.
        banana *= IGRect2D(0,64,64,216);

        // Fix the stem.
        IGArea end(IGEllipse2D(IGRect2D(16,48,56,104)));
        end.transformBy(IGrafMatrix(38, IGPoint2D(56,48)));
        banana -= end;

        // Draw the result.
        port.draw(banana, IFillAndFrameBundle(kDefaultFillColor, kDefaultFrameColor, kDefaultPenWidth));
}


//------------------------------------------------------------------------------
// CAGLetterLExample

void
CAGLetterLExample::draw(IGrafPort& port)
{
        // Start with an IGArea defining the entire area in which the L will be constructed.
        IGArea letter(IGRect2D(0,1,64,192));

        // Cut away ...
        letter += IGRect2D(0,128,128,192);
        letter -= IGEllipse2D(IGRect2D(-24,8,24,32));
        letter -= IGRect2D(-24,20,24,172);
        letter -= IGEllipse2D(IGRect2D(-24,160,24,184));
        letter -= IGEllipse2D(IGRect2D(40,8,88,32));
        letter -= IGRect2D(40,20,88,164);
        letter -= IGEllipse2D(IGRect2D(40,152,64,176));
        letter -= IGRect2D(52,152,108,176);
        letter -= IGEllipse2D(IGRect2D(96,152,120,176));
        letter -= IGRect2D(80,128,120,164);

        // Draw the result.
        port.draw(letter, IFillAndFrameBundle(kDefaultFillColor, kDefaultFrameColor, kDefaultPenWidth));
}

//------------------------------------------------------------------------------
// PipelineSimpleLinkedPortExample

void
PipelineSimpleLinkedPortExample::draw(IGrafPort& port)
{
        IGrafBundle bundle(kDefaultFillColor, kDefaultFrameColor);
        ILinkedGrafPort bundlePort(&port, &bundle);

        IGPolygon2D polygon(IGRect2D(20,20,220,180));
        bundlePort.draw(polygon);
}

//------------------------------------------------------------------------------
// PipelineSimpleBundleExample

void
PipelineSimpleBundleExample::draw(IGrafPort& port)
{
        IGPolygon2D polygon(IGRect2D(20,20,220,180));
        IGrafBundle bundle(kDefaultFillColor, kDefaultFrameColor);

        port.draw(polygon, bundle);
}

//------------------------------------------------------------------------------
// PipelineClippingExample

void
PipelineClippingExample::draw(IGrafPort& port)
{
        IGArea clipArea(IGRect2D(140,100,300,300));
        ILinkedGrafPort clipPort(&port, &clipArea);

        IGEllipse2D ellipse(IGRect2D(20,20,220,180));
        IGrafBundle bundle(kDefaultFillColor, kDefaultFrameColor);

        clipPort.draw(ellipse, bundle);
}

//------------------------------------------------------------------------------
// PipelineConcatExample

void
PipelineConcatExample::draw(IGrafPort& port)
{
        IGrafMatrix matrix(15.0, IGPoint2D(140,100)); // 15 degree rotation matrix centered on (140,100)
        IGrafBundle bundle(kDefaultFillColor, kDefaultFrameColor);

        ILinkedGrafPort matrixPort(&port, kViewMatrix, &matrix);
        ILinkedGrafPort bundlePort(&matrixPort, &bundle);

        IGPolygon2D polygon(IGRect2D(20,20,220,180));
        IGEllipse2D ellipse(IGRect2D(20,20,220,180));

        bundlePort.draw(polygon);
        bundlePort.draw(ellipse);
}

//------------------------------------------------------------------------------
// PipelineMultipleLinkedPortExample

void
PipelineMultipleLinkedPortExample::draw(IGrafPort& port)
{
        IGrafMatrix matrix(15.0, IGPoint2D(140,100)); // 15 degree rotation matrix centered on (140,100)
        IGrafBundle grayBundle(IBaseColor::kPaleGray, IGrafBundle::kFillAndFrame);
        IGrafBundle frameBundle(kDefaultFrameColor);

        ILinkedGrafPort matrixPort(&port, kViewMatrix, &matrix);
        ILinkedGrafPort grayBundlePort(&matrixPort, &grayBundle);
        ILinkedGrafPort frameBundlePort(&matrixPort, &frameBundle);

        IGPolygon2D polygon(IGRect2D(20,20,220,180));
        IGEllipse2D ellipse(IGRect2D(20,20,220,180));
        grayBundlePort.draw(polygon);
        frameBundlePort.draw(ellipse);
}

//------------------------------------------------------------------------------
// PipelineDirectToScreenExample

void
PipelineDirectToScreenExample::run(IWindow& theWindow)
{
        EDeviceCoordinateSystem coordSystem;
        if (ICoordinateSystem::applicationOrientation() == ICoordinateSystem::originLowerLeft)
        {
                coordSystem = kRightHand;
        }
        else
        {
                coordSystem = kLeftHand;
        }

        IManagedPresSpaceHandle presSpace(&theWindow);
        IExtendedRootGrafPort port(presSpace, coordSystem);

        IGEllipse2D ellipse(IGRect2D(20,20,220,180));
        port.draw(ellipse);
}

//------------------------------------------------------------------------------
// PipelineDirectToScreenWithClipExample

void
PipelineDirectToScreenWithClipExample::run(IWindow& theWindow)
{
        EDeviceCoordinateSystem coordSystem;
        if (ICoordinateSystem::applicationOrientation() == ICoordinateSystem::originLowerLeft)
        {
                coordSystem = kRightHand;
        }
        else
        {
                coordSystem = kLeftHand;
        }

        IManagedPresSpaceHandle presSpace(&theWindow);
        IExtendedRootGrafPort rootPort(presSpace, coordSystem);

        IGArea clipArea(IGRect2D(140,100,300,300));
        ILinkedGrafPort clipPort(&rootPort, &clipArea);

        IGEllipse2D ellipse(IGRect2D(20,20,220,180));
        rootPort.draw(ellipse);

        IGPolygon2D polygon(IGRect2D(20,20,220,180));
        clipPort.draw(polygon, IFillBundle(IBaseColor::kPaleGray));
}

