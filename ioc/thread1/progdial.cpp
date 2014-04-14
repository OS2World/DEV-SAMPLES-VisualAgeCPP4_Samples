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
// Class: ProgressDialog
// Purpose:
//      Dialog containing a progess indicator and a cancel button.
//-----------------------------------------------------------------------------

class ProgressDialog :
    public IFrameWindow
{
public:
    // PURPOSE: Construct a progress dialog with the given
    // window as owner.
    ProgressDialog(IWindow * owner, const char * title);

    // PURPOSE: Set the percentage for the progress indicator.
    void setPercent(unsigned long percent);
private:
    IMultiCellCanvas    fCanvas;
    IProgressIndicator  fIndicator;
    IPushButton         fCancelButton;
};

//-----------------------------------------------------------------------------

ProgressDialog::ProgressDialog(IWindow * owner, const char * title) :
    IFrameWindow(WND_PROG,
                 IWindow::desktopWindow(),
                 owner,
                 IRectangle(),
                 IFrameWindow::titleBar         |
                 IFrameWindow::dialogBorder     |
                 IFrameWindow::appDBCSStatus    |
                 IFrameWindow::dialogBackground,
                 title),
    fCanvas(WND_CAN, this, this),
    fIndicator(WND_IND, &fCanvas, &fCanvas, IRectangle(),
               5,       // Number of tick marks
               0,       // Space ticks evenly along the shaft
               IProgressIndicator::defaultStyle() |
               IProgressIndicator::alignBottom),
    fCancelButton(WND_CB, &fCanvas, &fCanvas)
{
    setClient(&fCanvas);

    // Add text and tick marks to the progress indicator.
    fIndicator.setTickLength(0, 1);
    fIndicator.setTickLength(1, 1);
    fIndicator.setTickLength(2, 1);
    fIndicator.setTickLength(3, 1);
    fIndicator.setTickLength(4, 1);
    fIndicator.setTickText(0, "0");
    fIndicator.setTickText(1, "25");
    fIndicator.setTickText(2, "50");
    fIndicator.setTickText(3, "75");
    fIndicator.setTickText(4, "100");

    // Size the progress indicator.
    ISize sz = fIndicator.minimumSize();
    sz.setWidth(250);
    fIndicator.setMinimumSize(sz);

    // Set up the cancel button.
    fCancelButton.setText("Cancel");
    fCancelButton.enableDefault();

    // Add the progress indicator and the cancel button to the canvas,
    // and provide a 10 pixel border around them.
    fCanvas.addToCell(&fIndicator, 2, 2, 3);
    fCanvas.addToCell(&fCancelButton, 3, 4, 1);
    fCanvas.setColumnWidth(1, 10);
    fCanvas.setColumnWidth(5, 10);
    fCanvas.setRowHeight(1, 10);
    fCanvas.setRowHeight(3, 10);
    fCanvas.setRowHeight(5, 10);

    // Center the cancel button in its row.
    fCanvas.setColumnWidth(2, IMultiCellCanvas::defaultCell().width(), true);
    fCanvas.setColumnWidth(4, IMultiCellCanvas::defaultCell().width(), true);

    // Size the dialog to its contents.
    moveSizeToClient(IRectangle(IPoint(0, 0), fCanvas.minimumSize()));
}

//-----------------------------------------------------------------------------

void
ProgressDialog::setPercent(unsigned long percent)
{
    unsigned long pos = percent * fIndicator.armRange() / 100;
    fIndicator.moveArmToPixel(pos);
}
