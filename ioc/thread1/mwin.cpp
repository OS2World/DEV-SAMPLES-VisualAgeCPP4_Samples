/*
    COPYRIGHT:
    ----------
    Copyright (C) International Business Machines Corp., 1998

    DISCLAIMER OF WARRANTIES:
    -------------------------
    The following [enclosed] code is sample code created by IBM
    Corporation. This sample code is not part of any standard IBM
    product and is provided to you solely for the purpose of assisting
    you in the development of your applications.  The code is provided
    "AS IS", without warranty of any kind.  IBM shall not be liable
    for any damages arising out of your use of the sample code, even
    if they have been advised of the possibility of such damages.
*/

//-----------------------------------------------------------------------------
// Class: MainWindow
// Purpose:
//      Application's main window
//-----------------------------------------------------------------------------

class MainWindow :
    public IFrameWindow,
    public ICommandHandler,
    public IPaintHandler,
    public IMouseHandler,
    public MandelbrotImage::Observer
{
public:
    // PURPOSE: Initialize the object.
    MainWindow(unsigned long id);

    // PURPOSE: Finalize the object.
    virtual ~MainWindow();
protected:
    // PURPOSE: Process command events.
    virtual bool command(ICommandEvent & event);

    // PURPOSE: Process system command events
    virtual bool systemCommand(ICommandEvent & event);

    // PURPOSE: Process paint events -- redraw the contents of the
    // drawing area.
    virtual bool paintWindow(IPaintEvent& event);

    // PURPOSE: Change the appearance of the mouse pointer when the
    // mouse enters the window.
    virtual bool mouseEnter(IEvent & event);

    // PURPOSE: Change the appearance of the mouse pointer when the
    // mouse leaves the window.
    virtual bool mouseLeave(IEvent & event);

    // PURPOSE: Called to notify this object as to how much of the
    // image has been generated.
    virtual void imageProgress(unsigned percent);

    // PURPOSE: Called to discover if image generation should be
    // Canceled.
    virtual bool cancelImage();

private:

    // The following are states that the primary thread can be in.
    // assume.
    enum PrimaryState
    {
        PRIMARY_IDLE,
        PRIMARY_GENERATING,
        PRIMARY_CANCELING,
        PRIMARY_EXITING
    };

    // The following are states that the secondary thread can be in.
    enum SecondaryState
    {
        SECONDARY_IDLE,
        SECONDARY_GENERATING
    };

    ICanvas             fDrawingArea;
    IMenuBar            fMenuBar;
    PrimaryState        fPrimaryState;
    SecondaryState      fSecondaryState;
    INonGUIThread	fWorkThread;
    ITimer		fTimer;
    unsigned		fProgress;
    ProgressDialog *    fIndicator;
    MandelbrotImage *   fImage;

    static const int ITERATION_LIMIT;

    static const ISystemPointerHandle fWaitPointer;
    static const IPointerHandle fReadyPointer;

    // PURPOSE: Stop the secondary thread and close the application.
    void exitApp();

    // PURPOSE: Start a secondary thread which will create an image of
    // the Mandelbrot set.
    void startGenThrd();

    // PURPOSE: Create an image of the Mandelbrot Set.  This function
    // will be run on a secondary thread.
    void genImage();

    // PURPOSE: Update the progress indicator to show how much of the
    // image has been generated.
    void checkProgress();
};

//-----------------------------------------------------------------------------

const int MainWindow::ITERATION_LIMIT = 1000;

const ISystemPointerHandle MainWindow::fWaitPointer = ISystemPointerHandle(ISystemPointerHandle::kWait);
const IPointerHandle MainWindow::fReadyPointer = IPointerHandle();

//-----------------------------------------------------------------------------

MainWindow::MainWindow(unsigned long id) :
    IFrameWindow (IFrameWindow::defaultStyle() | IFrameWindow::animated, id),
    IMouseHandler(IMouseHandler::mouseEntersLeaves),
    fDrawingArea(WND_DRAW, this, this),
    fMenuBar(WND_MAIN, this),
    fPrimaryState(PRIMARY_IDLE),
    fSecondaryState(SECONDARY_IDLE),
    fIndicator(0),
    fImage(0)
{
    setClient(&fDrawingArea);
    fDrawingArea.setBackgroundColor(IColor::black);

    // Create the progress indicator dialog.
    fIndicator = new ProgressDialog(this, "Generating Image...");

    // Start up the event handlers.
    ICommandHandler::handleEventsFor(this);
    ICommandHandler::handleEventsFor(fIndicator);
    IPaintHandler::handleEventsFor(&fDrawingArea);
    IMouseHandler::handleEventsFor(&fDrawingArea);

    // Specify coordinate system with the origin at the upper left.
    ICoordinateSystem::setApplicationOrientation(ICoordinateSystem::originUpperLeft);

    setFocus();
    show();
}

//-----------------------------------------------------------------------------

MainWindow::~MainWindow()
{
    // Shut down the event handlers.
    ICommandHandler::stopHandlingEventsFor(this);
    ICommandHandler::stopHandlingEventsFor(fIndicator);
    IPaintHandler::stopHandlingEventsFor(&fDrawingArea);
    IMouseHandler::stopHandlingEventsFor(&fDrawingArea);

    delete fIndicator;
    delete fImage;
}

//-----------------------------------------------------------------------------

bool
MainWindow::command(ICommandEvent& event)
{
    bool rc = true;
    switch (event.commandId()) {
    case ID_GENERATE:           // Generate Image menu item
	startGenThrd();
	break;

    case ID_EXIT:               // Exit menu item
	exitApp();
	break;

    case WND_CB:                // Cancel button on the progress dialog

        // Set the flag telling the secondary thread to cancel image
        // generation, and return to the processing the message queue
        // while waiting for it to do so.  This gives the secondary
        // thread the opportunity to release any resources it has
        // allocated, and destroy any objects it has created.  On
        // OS/2, the message queue must continue to be processed while
        // canceling the task (if canceling might take some time),
        // since there is only one message queue.  Not processing the
        // queue blocks input to other running applications.
        fPrimaryState = PRIMARY_CANCELING;
        break;

    default:
	rc = false;
	break;
    }
    return rc;
}

//-----------------------------------------------------------------------------

bool
MainWindow::systemCommand(ICommandEvent & event)
{
    if (event.commandId() == ISystemMenu::idClose) {
	exitApp();
	return true;
    }
    return false;
}

//-----------------------------------------------------------------------------

bool
MainWindow::paintWindow(IPaintEvent& event)
{
    IPresSpaceHandle presSpace = fDrawingArea.presSpace();

    // Clear the drawing area.
    IGPoint2D p1(0, 0);
    IGPoint2D p2(client()->size().width(), client()->size().height());
    IGRect2D  rect(p1, p2);
    IExtendedRootGrafPort port(presSpace);
    port.draw(rect, IFillBundle(IBaseColor::kBlack));

    // If image generation has completed, display the image.
    if (fPrimaryState == PRIMARY_IDLE && fImage != 0)
        fImage->draw(presSpace);

    return true;
}

//-----------------------------------------------------------------------------

bool
MainWindow::mouseEnter(IEvent & event)
{
    if (fPrimaryState == PRIMARY_GENERATING)
        setMousePointer(fWaitPointer);
    else
        setMousePointer(fReadyPointer);
    return true;
}

//-----------------------------------------------------------------------------

bool
MainWindow::mouseLeave(IEvent & event)
{
    setMousePointer(fReadyPointer);
    return true;
}

//-----------------------------------------------------------------------------

void
MainWindow::imageProgress(unsigned percent)
{
    fProgress = percent;
}

//-----------------------------------------------------------------------------

bool
MainWindow::cancelImage()
{
    return fPrimaryState == PRIMARY_CANCELING || fPrimaryState == PRIMARY_EXITING;
}

//-----------------------------------------------------------------------------

void
MainWindow::exitApp()
{
    if (fPrimaryState == PRIMARY_GENERATING) {
        // Set the flag telling the secondary thread to cancel image
        // generation, and return to the processing the message queue
        // while waiting for it to do so.  This gives the secondary
        // thread the opportunity to release any resources it has
        // allocated, and destroy any objects it has created.  On
        // OS/2, the message queue must continue to be processed while
        // canceling the task (if canceling might take some time),
        // since there is only one message queue.  Not processing the
        // queue blocks input to other running applications.
        fPrimaryState = PRIMARY_EXITING;
    }
    else {
        close();
    }
}

//-----------------------------------------------------------------------------

void
MainWindow::startGenThrd()
{
    fPrimaryState = PRIMARY_GENERATING;
    fSecondaryState = SECONDARY_GENERATING;
    fProgress = 0;
    setMousePointer(fWaitPointer);
    fIndicator->setPercent(0);

    // Position the indicator dialog in the center of the screen.
    ISize sz = fIndicator->size();
    IRectangle crect = IWindow::desktopWindow()->rect();
    IPoint pos(crect.minX() + (crect.width() - sz.width()) / 2,
               crect.minY() + (crect.height() - sz.height()) / 2);
    fIndicator->moveTo(pos);
    fIndicator->show();
    fIndicator->setFocus();

    fMenuBar.disableItem(ID_GENERATE);

    // Define the portion of the complex plane to be drawn.  Ensure it
    // includes the Mandelbrot set, and has the same aspect ratio as
    // the drawing area.  Center the image at complex(-0.7, 0.0).  For
    // the area that should be included, the upper left is at
    // complex(-2.0, 1.3) and the lower right is at complex(0.6, -1.3).
    complex upperLeft;
    complex lowerRight;
    unsigned long width = client()->size().width();
    unsigned long height = client()->size().height();
    if (width > height) {
	double d = 1.3 * width / height;
	upperLeft = complex(-0.7 - d, 1.3);
	lowerRight = complex(-0.7 + d, -1.3);
    }
    else {
	double d = 1.3 * height / width;
	upperLeft = complex(-2.0, d);
	lowerRight = complex(0.6, -d);
    }

    // Create a new image object representing the portion of the
    // complex plane to be drawn.
    delete fImage;
    fImage = new MandelbrotImage(upperLeft, lowerRight,
                                 width, height,
                                 ITERATION_LIMIT);

    // Start another thread and have it run the member function which
    // will generate the image.
    fWorkThread.start(new IThreadMemberFn<MainWindow>(*this,
                                                      &MainWindow::genImage));

    // Start the timer which will check on the progress of the image
    // generation twice per second.
    fTimer.setInterval(500);
    fTimer.start(new ITimerMemberFn0<MainWindow>(*this,
						 &MainWindow::checkProgress));
}

//-----------------------------------------------------------------------------

void
MainWindow::genImage()
{
    // Generate the image.  This object is passes as the Observer; it
    // will be notified of the progress of the image generation (via a
    // call to imageProgress).
    fImage->generate(*this);
    fSecondaryState = SECONDARY_IDLE;
}

//-----------------------------------------------------------------------------

void
MainWindow::checkProgress()
{
    if (fSecondaryState == SECONDARY_GENERATING) {
        fIndicator->setPercent(fProgress);
    }
    else {
        switch (fPrimaryState) {
        case PRIMARY_CANCELING:
            delete fImage;
            fImage = 0;

            // Fall through to next case.

        case PRIMARY_GENERATING:
            fPrimaryState = PRIMARY_IDLE;
            fTimer.stop();
            fIndicator->hide();
            fMenuBar.enableItem(ID_GENERATE);
            setFocus();
            setMousePointer(fReadyPointer);
            fDrawingArea.refresh(IWindow::paintAll);
            break;

        case PRIMARY_EXITING:
            close();
            break;

        default:
            break;
        }
    }
}

//-----------------------------------------------------------------------------

int
main(int argc, char * argv[])
{
    MainWindow  mainWindow(WND_MAIN);
    IApplication::current().run();
    return 0;
}
