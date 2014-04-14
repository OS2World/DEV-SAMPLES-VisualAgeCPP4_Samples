// Revision: 63  1.7.1.2  samples/graph2d/2ddocs/examples.hpp, ocsamples-L1, ioc.v400, 981111  
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

#ifndef _EXAMPLES_
#define _EXAMPLES_

#include <igraph2d.hpp>         // GCoordinate, IBaseColor, IGrafPort
#include <imoushdr.hpp>         // IMouseClickConnectionTo, IMouseClickEvent
#include "2ddocs.h"             // resource identifiers

//------------------------------------------------------------------------------
// Example
//
//  This is the base class for all examples in the 2ddocs example program.
//  Each individual example derives from this class, in order to be selectable
//  and executable by the user.
//

class Example {
public:
        virtual ~Example() {}

        // nameId() returns the numeric ID associated with a particular instance of
        // this class.
        virtual unsigned long nameId() = 0;

        // run() runs the example.
        virtual void run(IWindow& theWindow) = 0;

        // These are some predefined constants for subclasses to use.
        static const IBaseColor::EPredefinedColor       kDefaultFrameColor;
        static const IBaseColor::EPredefinedColor       kDefaultFillColor;
        static const GCoordinate                                        kDefaultPenWidth;
};

//------------------------------------------------------------------------------
// ExampleFor<ExampleID>
//
//  This template class defines an implementation of the nameId function, but
//  essentially leaves the implementation of draw empty. It is up to the author
//  of any example to write a specialized implementation of the draw function
//  for each particular example class. In examples.cpp, you will find specialized
//  implementations such as PipelineDirectToScreenExample which is the same as
//  ExampleFor<ID_IC_EXAMPLE_PIPELINE_DIRECT>).
//

template <unsigned long ExampleID>
class ExampleFor : public Example {
public:
        virtual                                 ~ExampleFor() {}

        virtual unsigned long   nameId() { return ExampleID; }
        virtual void                    run(IWindow& theWindow);
};

template <unsigned long ExampleID>
void
ExampleFor<ExampleID>::run(IWindow& theWindow)
{
        // A definition of this function must exist to prevent link errors.
}

//------------------------------------------------------------------------------
// StandardExample
//

class StandardExample : public Example {
public:
        virtual ~StandardExample() {}

        virtual void run(IWindow& theWindow);

        // draw renders the example's output into the given IGrafPort.
        virtual void draw(IGrafPort& port) = 0;
};

//------------------------------------------------------------------------------
// StandardExampleFor<ExampleID>
//
//  This template class defines an implementation of the nameId function, but
//  essentially leaves the implementation of draw empty. It is up to the author
//  of any example to write a specialized implementation of the draw function
//  for each particular example class. In examples.cpp, you will find many such
//  specialized implementations (e.g., CAGAppleExample which is the same as
//  StandardExampleFor<ID_IC_EXAMPLE_CAG_APPLE>).
//

template <unsigned long ExampleID>
class StandardExampleFor : public StandardExample {
public:
        virtual                                 ~StandardExampleFor() {}

        virtual unsigned long   nameId() { return ExampleID; }
        virtual void                    draw(IGrafPort& port);
};

template <unsigned long ExampleID>
void
StandardExampleFor<ExampleID>::draw(IGrafPort& port)
{
        // A definition of this function must exist to prevent link errors.
}

//------------------------------------------------------------------------------
// StarExample
//
//  This class provides some default behavior which makes the
//  scale/rotate/translate examples clearer. The draw function creates a
//  standard polygon, draws it, and passes it to handleDraw.
//

class StarExample : public StandardExample {
public:
        virtual                                 ~StarExample() {}

        virtual void                    draw(IGrafPort& port);
        virtual void                    handleDraw(IGrafPort& port, IPolygon& starGraphic) = 0;
};

//------------------------------------------------------------------------------
// StarExampleFor<ExampleID>
//

template <unsigned long ExampleID>
class StarExampleFor : public StarExample {
public:
        virtual                                 ~StarExampleFor() {}

        virtual unsigned long   nameId() { return ExampleID; }
        virtual void                    handleDraw(IGrafPort& port, IPolygon& starGraphic);
};

//------------------------------------------------------------------------------
// InteractiveExample
//
//  This is the base class for examples with which the user can interact using
//      the mouse.
//

class InteractiveExample : public StandardExample {
public:
        InteractiveExample(IWindow* eventSource)
                : fWindow(eventSource)
                , fClickHandler(*this, &InteractiveExample::handleMouseClick)
        {
                fClickHandler.handleEventsFor(fWindow);
        }

        virtual ~InteractiveExample()
        {
                fClickHandler.stopHandlingEventsFor(fWindow);
        }

        IWindow* window() { return fWindow; }

        virtual bool handleMouseClick(IMouseClickEvent& event) = 0; // handler

private:
        IWindow*                                                                        fWindow;        // source of events
        IMouseClickConnectionTo<InteractiveExample>     fClickHandler;
};

//------------------------------------------------------------------------------
// WagonExample
//
//  This example shows mouse hit detection, as well as graphic groups.
//

class WagonExample : public InteractiveExample {
public:
        WagonExample(IWindow* eventSource)
                : InteractiveExample(eventSource)
                , fOriginalWagon(NULL)
                , fMovedWagon(NULL)
                , fSelection(NULL)
        {
        }

        virtual ~WagonExample()
        {
                delete fOriginalWagon;
                delete fMovedWagon;
                delete fSelection;
        }

        // createWagon creates a graphic group. Passing in true causes the wagon to be translated
        // and its wheels rotated.
        IGraphicGroup* createWagon(bool moveIt = false);

        virtual unsigned long nameId() { return IC_ID_EXAMPLE_WAGON; }

        // draw renders the wagon into the given grafport.
        virtual void draw(IGrafPort& port);

        // handleMouseClick handles mouse events and does hit detection.
        virtual bool handleMouseClick(IMouseClickEvent& event);

        static const IBaseColor::EPredefinedColor kSelectionColor;

private:
        WagonExample();

        IGraphicGroup* fOriginalWagon;
        IGraphicGroup* fMovedWagon;     // translated and wheels rotated
        IMGraphic* fSelection;
};


//------------------------------------------------------------------------------
// Typedefs and class declarations for the rest of the examples
//

typedef StandardExampleFor<IC_ID_EXAMPLE_BOLT> BoltExample;
typedef StarExampleFor<IC_ID_EXAMPLE_STAR_ROTATE_CENTER> StarRotateCenterExample;
typedef StarExampleFor<IC_ID_EXAMPLE_STAR_ROTATE_VIEWORIGIN> StarRotateViewOriginExample;
typedef StarExampleFor<IC_ID_EXAMPLE_STAR_ROTATE_ARBITRARYPOINT> StarRotateArbitraryPointExample;
typedef StarExampleFor<IC_ID_EXAMPLE_STAR_SCALE_CENTER> StarScaleCenterExample;
typedef StarExampleFor<IC_ID_EXAMPLE_STAR_SCALE_VIEWORIGIN> StarScaleViewOriginExample;
typedef StarExampleFor<IC_ID_EXAMPLE_STAR_SCALE_ARBITRARYPOINT> StarScaleArbitraryPointExample;
typedef StarExampleFor<IC_ID_EXAMPLE_STAR_MIRRORX> StarMirrorXExample;
typedef StarExampleFor<IC_ID_EXAMPLE_STAR_MIRRORY> StarMirrorYExample;
typedef StarExampleFor<IC_ID_EXAMPLE_STAR_MIRRORXY> StarMirrorXYExample;
typedef StarExampleFor<IC_ID_EXAMPLE_STAR_TRANSLATE> StarTranslateExample;
typedef StandardExampleFor<IC_ID_EXAMPLE_CAG_ARBITRARY> CAGArbitraryAreaExample;
typedef StandardExampleFor<IC_ID_EXAMPLE_CAG_APPLE> CAGAppleExample;
typedef StandardExampleFor<IC_ID_EXAMPLE_CAG_BANANA> CAGBananaExample;
typedef StandardExampleFor<IC_ID_EXAMPLE_CAG_L> CAGLetterLExample;
typedef StandardExampleFor<IC_ID_EXAMPLE_PIPELINE_SIMPLE_LINKED> PipelineSimpleLinkedPortExample;
typedef StandardExampleFor<IC_ID_EXAMPLE_PIPELINE_SIMPLE_BUNDLE> PipelineSimpleBundleExample;
typedef StandardExampleFor<IC_ID_EXAMPLE_PIPELINE_COMPLEX_CLIP> PipelineClippingExample;
typedef StandardExampleFor<IC_ID_EXAMPLE_PIPELINE_COMPLEX_CONCAT> PipelineConcatExample;
typedef StandardExampleFor<IC_ID_EXAMPLE_PIPELINE_COMPLEX_MULTILINKED> PipelineMultipleLinkedPortExample;
typedef ExampleFor<IC_ID_EXAMPLE_PIPELINE_DIRECT> PipelineDirectToScreenExample;
typedef ExampleFor<IC_ID_EXAMPLE_PIPELINE_DIRECT_CLIP> PipelineDirectToScreenWithClipExample;

#endif // _EXAMPLES_
