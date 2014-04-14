/******************************************************************************
* .FILE:         magnify.cpp                                                  *
*                                                                             *
* .DESCRIPTION:  Magnify Sample Program:  Class Implementation                *
*                                                                             *
* .CLASSES:      MagnifyWindow                                                *
*                MagnifyHandler                                               *
*                                                                             *
* .NOTE: WE RECOMMEND USING A FIXED SPACE FONT TO LOOK AT THE SOURCE          *
*                                                                             *
******************************************************************************/
/*
-------------------------------------------------------------------------------
Copyright (c) IBM Corporation 1992, 1997.
All Rights Reserved.

Permission is granted to copy, use, modify, and merge this software into your
applications and to permit others to do any of the foregoing. You must include
this permission and copyright notice in all copies and modified versions of
this software. THIS SOFTWARE IS PROVIDED IN ITS 'AS IS' CONDITION. TALIGENT
AND IBM DISCLAIM ANY LIABILITY OF ANY KIND FOR DAMAGES WHATSOEVER RESULTING
FROM THE USE OF THIS SOFTWARE.
-------------------------------------------------------------------------------
*/
#include <ibase.hpp>
#include <i2dghand.hpp>
#include <iapp.hpp>
#include <icoordsy.hpp>
#include <ifiledlg.hpp>
#include <igimage.hpp>
#include <igrport.hpp>
#include <imsgbox.hpp>
#include "magnify.hpp"
#include "magnify.h"

/******************************************************************************
* main - Application entry point                                              *
******************************************************************************/
int main()
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::originUpperLeft );
  MagnifyWindow win;
  IApplication::current().run();

  return 0;
}

/******************************************************************************
* MagnifyWindow::MagnifyWindow - Constructor for the main window              *
*                                                                             *
* Define itself as an IFrameWindow                                            *
* Create the title for the window                                             *
* Define a control for a bitmap                                               *
* Define a canvas to put the spin buttons, pushbuttons and text.              *
* Define the spin buttons, pushbuttons, and the text.                         *
******************************************************************************/
MagnifyWindow::MagnifyWindow ()
              :IFrameWindow (ID_MAIN,0,0,IRectangle(),
                  IFrameWindow::defaultStyle() | IFrameWindow::dialogBackground),
               title(this),
               bitmapControl(0,this,this),
               canvas(ID_CANVAS,this,this),
               xText(ID_TEXTX,&canvas,&canvas),
               xSpin(ID_SPINX,&canvas,&canvas),
               yText(ID_TEXTY,&canvas,&canvas),
               ySpin(ID_SPINY,&canvas,&canvas),
               button(ID_BUTTON,&canvas,&canvas),
               savebut(ID_SAVEAS,&canvas,&canvas),
               bitmap(0)
{
/*----------------------------------------------------------------------------|
| Set the icon and title for the main window                                  |
-----------------------------------------------------------------------------*/
  setIcon( id() );
  title.setTitleText(TITLE_MAGNIFY);

/*----------------------------------------------------------------------------|
| Set the bitmap as the client area.                                          |
-----------------------------------------------------------------------------*/
  setClient(&bitmapControl);

/*----------------------------------------------------------------------------|
| Install command handler to process button selections.                       |
-----------------------------------------------------------------------------*/
  handler.handleEventsFor(this);

/*----------------------------------------------------------------------------|
| Enable latching for the magnify button.                                     |
| Set the text of the buttons, and set them as tab stops.                     |
-----------------------------------------------------------------------------*/
  button.setText(STR_MAGNIFY).enableTabStop();
  savebut.setText(STR_SAVEAS).enableTabStop().disable();

/*----------------------------------------------------------------------------|
| Set up the spin buttons with their text and the range of values.            |
-----------------------------------------------------------------------------*/
  xText.setText(STR_X);
  yText.setText(STR_Y);
  xSpin.setRange(IRange(1,desktopWindow()->size().width())).setLimit(4);
  xSpin.setValue(32).enableTabStop();
  ySpin.setRange(IRange(1,desktopWindow()->size().height())).setLimit(4);
  ySpin.setValue(32).enableTabStop();

/*----------------------------------------------------------------------------|
| Define the margins and alignment of the set canvas.                         |
| Add the set canvas as an extension of the main frame window.                |
| Resize the frame window around the bitmap control.  Size the frame so that  |
| the client area is a square just large enough for the set canvas to fit     |
| across the top.                                                             |
-----------------------------------------------------------------------------*/
  canvas.setMargin(ISize(2,2)).setAlignment(ISetCanvas::centerCenter);
  addExtension(&canvas,aboveClient);
  int widthHeight = canvas.minimumSize().width();
  moveSizeToClient(IRectangle(IPoint(100,100), ISize(widthHeight, widthHeight)));

/*----------------------------------------------------------------------------|
| The uninitialized bitmap will not paint.  The result is a see-through       |
|   client area.  Therefore, set the bitmap to an IImage with white fill.     |
-----------------------------------------------------------------------------*/
  bitmap = new IImage( 10L, 10L, IGImage::kTrueColor24Bit);
  IBaseColor fillColor( IBaseColor::kWhite );
  IFillBundle fillBundle( fillColor );
  bitmap->grafPort()->draw( IGRect2D(0,0,10,10), fillBundle );
  bitmapControl.setBitmap( bitmap->image()->handle() );

/*----------------------------------------------------------------------------|
|  Set focus and show the window.                                             |
-----------------------------------------------------------------------------*/
  show();
  button.setFocus();
}

/******************************************************************************
* MagnifyWindow::MagnifyWindow - Destructor for the main window               *
******************************************************************************/
MagnifyWindow::~MagnifyWindow()
{
  if ( timer.isStarted() )
    timer.stop();
  if (bitmap)
    delete bitmap;
}

/******************************************************************************
* MagnifyWindow::timerFunction - Called when the timer expires and grabs      *
*   a new bitmap of the section of the window that is being magnified.        *
******************************************************************************/
void MagnifyWindow::timerFunction ()
{
/*----------------------------------------------------------------------------|
| Create a rectangle with the size specified by the spin buttons.             |
-----------------------------------------------------------------------------*/
  unsigned long xSize = xSpin.value();
  unsigned long ySize = ySpin.value();

  if ( !xSpin.isSpinFieldValid() )
  {
    xSize = 1;
    xSpin.setValue( 1);
  }
  if ( !ySpin.isSpinFieldValid() )
  {
    ySize = 1;
    ySpin.setValue( 1);
  }
  IRectangle rect(0,0,xSize,ySize);

/*----------------------------------------------------------------------------|
| Reposition the rectangle so that the mouse is at the center of the rectangle|
-----------------------------------------------------------------------------*/
  ISize desktopSize = desktopWindow()->size();
  IPoint mousePosition = IWindow::pointerPosition();
  rect.centerAt(mousePosition);
  if (rect.minX() < 0)
    rect.moveTo(IPoint(0, rect.minY()));
  if (rect.minY() < 0)
    rect.moveTo(IPoint(rect.minX(),0));
  if (rect.maxX() >= desktopSize.width())
    rect.moveTo(IPoint(desktopSize.width()-xSize, rect.minY()));
  if (rect.maxY() >= desktopSize.height())
    rect.moveTo(IPoint(rect.minX(), desktopSize.height()-ySize));


/*----------------------------------------------------------------------------|
| Convert the rectangle to native coordinates.                                |
| For graphics, this function should be used for portable graphics.           |
-----------------------------------------------------------------------------*/
  IGRect2D grect( ICoordinateSystem::convertToNative( rect, desktopSize ) );

/*----------------------------------------------------------------------------|
| Create a new bitmap from the desktop in the area specified by the rectangle.|
| Delete the old bitmap and reset its pointer to the new bitmap.              |
-----------------------------------------------------------------------------*/
  IPresSpaceHandle ps = IWindow::desktopWindow()->presSpace();
  IImage* newBitmap = new IImage( IGImage::captureImage( ps, grect) );
  IWindow::desktopWindow()->releasePresSpace(ps);
  bitmapControl.setBitmap(newBitmap->image()->handle());
  if (bitmap)
    delete bitmap;
  bitmap = newBitmap;
}

/******************************************************************************
* MagnifyWindow::magnify - called when the magnify button is pressed.         *
******************************************************************************/
void MagnifyWindow::magnify( )
{
/*----------------------------------------------------------------------------|
| If the timer is not started, start it to begin capturing images.            |
| Otherwise, stop the timer to stop capturing images.                         |
-----------------------------------------------------------------------------*/
   if (!timer.isStarted())
   {
     savebut.disable();
     timer.start(new ITimerMemberFn0<MagnifyWindow>(*this,&MagnifyWindow::timerFunction),
                 200);
     button.setText(STR_CAPTURE);
   }
   else
   {
     timer.stop();
     button.setText(STR_MAGNIFY);
     if (bitmap)
       savebut.enable();
   }
}

/******************************************************************************
* MagnifyHandler::command - Command handler to process button selections.     *
******************************************************************************/
bool MagnifyHandler::command(ICommandEvent& event)
{
  bool result(true);
  switch ( event.commandId() )
  {
    case ID_BUTTON:
    {
      MagnifyWindow *win =
          dynamic_cast<MagnifyWindow*>(event.dispatchingWindow());
      if (win)
         win->magnify();
      break;
    }
    case ID_SAVEAS:
    {
      MagnifyWindow *win =
          dynamic_cast<MagnifyWindow*>(event.dispatchingWindow());
      if ( win && !win->saveFile() )
      {
        IMessageBox
          msgbox( win );
        msgbox.show( STR_WRITE_ERROR, IMessageBox::action );
      }
      break;
    }
    default:
      result = false;
  }
  return result;
}


/******************************************************************************
* SaveAsFormat - This structure contains a supported file extenstion and      *
* the associated image format.                                                *
******************************************************************************/
typedef struct {
  char*                              extension;
  IGImagePixelAccessor::EImageFormat format;
} SaveAsFormat;

/******************************************************************************
* MagnifyWindow::saveFile - This function prompts for a file name and saves   *
* the image that has been captured.                                           *
******************************************************************************/
bool MagnifyWindow::saveFile()
{
  bool
    rc = false;
  IResourceLibrary
    reslib;
  IFileDialog::Settings
    fileSettings;

/*----------------------------------------------------------------------------|
| Construct a list of the supported formats and display a file dialog         |
| with these formats and the associated extensions listed.  Use the extension |
| from the file name returned by the dialog  to determine the format in which |
| to save the file.                                                           |
-----------------------------------------------------------------------------*/
  static const SaveAsFormat saveAsFormats[] = {
    "gif",  IGImagePixelAccessor::kGIF,
    "xpm",  IGImagePixelAccessor::kXPM,
    "bmp",  IGImagePixelAccessor::kBMP,
#ifdef IC_MOTIF
    "jpg",  IGImagePixelAccessor::kJPG,
#endif
    0    ,  IGImagePixelAccessor::kBMP    // default
  };

  for (int i=0; saveAsFormats[i].extension; i++)
  {
     IString filter = IString("*.") + saveAsFormats[i].extension;
     fileSettings.addFileType(
         reslib.loadString( STR_SAVETYPES+i ), filter );
  }
  fileSettings.setSaveAsDialog();

  IFileDialog fileDlg( IWindow::desktopWindow(), this, fileSettings );

  if ( fileDlg.pressedOK() )
  {
    IString
      filename = fileDlg.fileName();

    const SaveAsFormat* saveFormat(0);
    for (int i=0; saveFormat == 0; i++)
    {
       if (saveAsFormats[i].extension)
       {
          IString ext(IString(".") + saveAsFormats[i].extension);
          if (filename.lastIndexOf(ext) == filename.length() - ext.length()+1)
             saveFormat = &saveAsFormats[i];
       }
       else
          saveFormat = &saveAsFormats[i];   //default
    }

/*----------------------------------------------------------------------------|
| Write the image to the file specified.  The captured image needs to be      |
| converted to 256 colors in order to save it in some formats.  Do the        |
| conversion by drawing the image into a new IImage with the correct color    |
| depth, and then write this new image to the file.                           |
-----------------------------------------------------------------------------*/
    try
    {
      if ( bitmap )
      {
        unsigned long numColors =
           bitmap->image()->imageColorTable().numberOfColors();

        if ((numColors == 0) || (numColors > 256))
        {
           // Image is true color or > 256 colors.  Convert to 256 colors.
           long x = bitmap->geometricBounds().height();
           long y = bitmap->geometricBounds().width();
           IImage image256( x, y, IGImage::k256Color8Bit);
           bitmap->draw( *image256.grafPort() );
           IGImagePixelAccessor::writeImageToFile(
              filename,
              saveFormat->format,
              (IGImage*)image256.image() );
        }
        else
        {
           // Image has 256 colors or less.
           IGImagePixelAccessor::writeImageToFile(
              filename,
              saveFormat->format,
              (IGImage*)bitmap->image() );
        }
        rc = true;
      }
    }
    catch(...)
    {
    }
  }
  else
  {
     rc = true;
  }

  return rc;
}
