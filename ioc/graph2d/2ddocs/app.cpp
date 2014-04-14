// Revision: 59 1.6.1.4 samples/graph2d/2ddocs/app.cpp, ocsamples-L1, ioc.v400, 981111 
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

#include <icanvas.hpp>  // ICanvas
#include <icmdhdr.hpp>  // ICommandConnectionTo
#include <ifont.hpp>    // IFont
#include <iframe.hpp>   // IFrameWindow
#include <igenexc.hpp>  // ICannotProceed
#include <iinfoa.hpp>   // IInfoArea
#include <imenubar.hpp> // IMenuBar
#include <ipainhdr.hpp> // IPaintConnectionTo, IPaintEvent
#include "examples.hpp" // Example

//
// ExampleFrameWindow
//

class ExampleFrameWindow : public IFrameWindow {
public:
                                ExampleFrameWindow();
    virtual                     ~ExampleFrameWindow();

protected:
        virtual bool            handleMenuCmd(ICommandEvent& event);
        virtual bool            handlePaintEvent(IPaintEvent& event);

        void                            adoptExample(Example* adoptee);
        Example*                        example();
        virtual Example*        createExample(unsigned long shapeId);

        void                            reportMessage(unsigned long stringId);
        void                            reportError(unsigned long stringId);
        void                            reportError(const IString& errorMessage);

private:
                                                ExampleFrameWindow(const ExampleFrameWindow&);
    ExampleFrameWindow& operator=(const ExampleFrameWindow&);

        IMenuBar                        fMenuBar;
    IInfoArea           fInfoArea;
        ICanvas                         fDrawingCanvas;

        // We need a command handler to process menu commands.
        ICommandConnectionTo<ExampleFrameWindow>        fCmdHandler;

        // And a paint connection to receive and process paint events.
        IPaintConnectionTo<ExampleFrameWindow>          fPaintHandler;

        Example*                        fObj;
};

ExampleFrameWindow::ExampleFrameWindow()
        : IFrameWindow(IFrameWindow::defaultStyle() | IFrameWindow::clipChildren, IC_ID_WND_MAIN)
        , fMenuBar(IC_ID_WND_MAIN, this)
        , fInfoArea(this)
        , fDrawingCanvas(IC_ID_WND_DRAW, this, this)
        , fCmdHandler(*this, &ExampleFrameWindow::handleMenuCmd)
        , fPaintHandler(*this, &ExampleFrameWindow::handlePaintEvent)
        , fObj(NULL)
{
        fCmdHandler.handleEventsFor(this);
        fPaintHandler.handleEventsFor(&fDrawingCanvas);

#ifndef IC_MOTIF
        IFont font("MS Sans Serif", 8);
        font.setWindowFont(&fInfoArea);
#endif // IC_MOTIF

        setClient(&fDrawingCanvas);

        // This is a little bit redundant, but forces some things to happen that
        // make the UI nicer, like putting the right initial message in the info
        // area.
        adoptExample(NULL);
}

ExampleFrameWindow::ExampleFrameWindow(const ExampleFrameWindow&)
        : IFrameWindow(IFrameWindow::defaultStyle() | IFrameWindow::clipChildren, IC_ID_WND_MAIN)
        , fMenuBar(IC_ID_WND_MAIN, this)
        , fInfoArea(this)
        , fDrawingCanvas(IC_ID_WND_DRAW, this, this)
        , fCmdHandler(*this, &ExampleFrameWindow::handleMenuCmd)
        , fPaintHandler(*this, &ExampleFrameWindow::handlePaintEvent)
        , fObj(NULL)
{
        throw ICannotProceed("ExampleFrameWindow copy constructor should not be called");
}

ExampleFrameWindow::~ExampleFrameWindow()
{
        fCmdHandler.stopHandlingEventsFor(this);
        fPaintHandler.stopHandlingEventsFor(this);

        delete fObj;
}

bool
ExampleFrameWindow::handleMenuCmd(ICommandEvent& event)
{
        bool handled = true;

        try
        {
                unsigned long cmd = event.commandId();
                if (cmd == IC_ID_EXIT)
                {
                        // Quit by closing the main window.

                        close();
                }
                else if (cmd >= IC_ID_EXAMPLE__FIRST && cmd <= IC_ID_EXAMPLE__LAST)
                {
                        adoptExample(createExample(cmd));
#ifndef IC_MOTIF
                        refresh();
#else
                        fDrawingCanvas.refresh();
#endif
                }
                else
                {
                        // Let someone else handle the event.

                        handled = false;
                }
        }
        catch (const IException& e)
        {
                printf("### exception %s\n", e.name());
        }

        return handled;
}

bool
ExampleFrameWindow::handlePaintEvent(IPaintEvent& event)
{
        event.clearBackground(IColor::white);

        Example* exampleObj = example();
        if (exampleObj != NULL)
        {
                exampleObj->run(fDrawingCanvas);
        }

        return true;
}

Example*
ExampleFrameWindow::example()
{
        return fObj;
}

void
ExampleFrameWindow::adoptExample(Example* adoptee)
{
        Example* old = fObj;
        fObj = adoptee;
        delete old;

        // Look up the string corresponding to the selected object and display
        // it in the info area.

        if (fObj == NULL)
        {
                reportError(IC_ID_ERROR_NO_EXAMPLE_SELECTED);
        }
        else
        {
                reportMessage(fObj->nameId());
        }
}

Example*
ExampleFrameWindow::createExample(unsigned long shapeId)
{
        switch (shapeId)
        {
                #define EXAMPLE_CASE(id) case IC_ID_EXAMPLE_ ## id: return new ExampleFor<IC_ID_EXAMPLE_ ## id>
                #define STANDARD_EXAMPLE_CASE(id) case IC_ID_EXAMPLE_ ## id: return new StandardExampleFor<IC_ID_EXAMPLE_ ## id>
                #define STAREXAMPLE_CASE(id) case IC_ID_EXAMPLE_ ## id: return new StarExampleFor<IC_ID_EXAMPLE_ ## id>;
                #define INTERACTIVE_EXAMPLE_CASE(T,id) case IC_ID_EXAMPLE_ ## id: return new T(&fDrawingCanvas);

                STANDARD_EXAMPLE_CASE(BOLT);
                STAREXAMPLE_CASE(STAR_ROTATE_CENTER);
                STAREXAMPLE_CASE(STAR_ROTATE_VIEWORIGIN);
                STAREXAMPLE_CASE(STAR_ROTATE_ARBITRARYPOINT);
                STAREXAMPLE_CASE(STAR_SCALE_CENTER);
                STAREXAMPLE_CASE(STAR_SCALE_VIEWORIGIN);
                STAREXAMPLE_CASE(STAR_SCALE_ARBITRARYPOINT);
                STAREXAMPLE_CASE(STAR_MIRRORX);
                STAREXAMPLE_CASE(STAR_MIRRORY);
                STAREXAMPLE_CASE(STAR_MIRRORXY);
                STAREXAMPLE_CASE(STAR_TRANSLATE);
                INTERACTIVE_EXAMPLE_CASE(WagonExample,WAGON);
                STANDARD_EXAMPLE_CASE(CAG_ARBITRARY);
                STANDARD_EXAMPLE_CASE(CAG_APPLE);
                STANDARD_EXAMPLE_CASE(CAG_BANANA);
                STANDARD_EXAMPLE_CASE(CAG_L);
                STANDARD_EXAMPLE_CASE(PIPELINE_SIMPLE_LINKED);
                STANDARD_EXAMPLE_CASE(PIPELINE_SIMPLE_BUNDLE);
                STANDARD_EXAMPLE_CASE(PIPELINE_COMPLEX_CLIP);
                STANDARD_EXAMPLE_CASE(PIPELINE_COMPLEX_CONCAT);
                STANDARD_EXAMPLE_CASE(PIPELINE_COMPLEX_MULTILINKED);
                EXAMPLE_CASE(PIPELINE_DIRECT);
                EXAMPLE_CASE(PIPELINE_DIRECT_CLIP);
        }

        return NULL;
}

void
ExampleFrameWindow::reportMessage(unsigned long stringId)
{
        try
        {
                fInfoArea.setInactiveText(IResourceLibrary().loadString(stringId));
        }
        catch (...)
        {
                printf("### internal error while displaying message\n");
        }
}

void
ExampleFrameWindow::reportError(unsigned long stringId)
{
        try
        {
                reportError(IResourceLibrary().loadString(stringId));
        }
        catch (...)
        {
                printf("### internal error while displaying error\n");
        }
}

void
ExampleFrameWindow::reportError(const IString& errorMessage)
{
        try
        {
                fInfoArea.setInactiveText(errorMessage);
        }
        catch (...)
        {
                printf("### internal error while displaying error\n");
        }
}

//
// main
//

int main()
{
        try
        {
                ExampleFrameWindow mainWindow;
                mainWindow.sizeTo(ISize(300,300));
                mainWindow.setFocus();
                mainWindow.show();
                IApplication::current().run();
        }
        catch (const IException& e)
        {
                printf("### Uncaught exception: %s\n", e.name());
        }
        catch (...)
        {
                printf("### Uncaught unknown exception\n");
        }

        return 0;
}

