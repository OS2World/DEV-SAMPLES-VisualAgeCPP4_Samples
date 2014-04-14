/******************************************************************************
* .FILE:         msgbox.cpp                                                   *
*                                                                             *
* .DESCRIPTION:  Message Box Sample Program:  Class Implementation            *
*                                                                             *
* .CLASSES:      AMsgBoxDemo                                                  *
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
#include <iapp.hpp>
#include <ireslib.hpp>
#include <icoordsy.hpp>
#include "msgbox.hpp"
#include "msgbox.h"

int main()
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::kOriginLowerLeft );
  #ifdef USE_IPF
  IHelpWindow::setDefaultStyle( IHelpWindow::defaultStyle()
                                | IHelpWindow::ipfCompatible );
  #endif
  AMsgBoxDemo mbDisplay(WND_MAIN);
  mbDisplay.sizeTo(ISize(800,300));
  mbDisplay.runDemo();
  IApplication::current().run();
  return 0;
} /* end main() */

/**************************************************************************
* AMsbBoxDemo :: AMsgBoxDemo - Constructor                                *
*                                                                         *
* Construct the IFrameWindow using the default style.                     *
* Create the IMultiLineEdit object with the default style and make it     *
*   read only it is used only to display status.                          *
* Create the message box owned by the frame window.                       *
* Create the help window also owned by the frame window.                  *
**************************************************************************/

AMsgBoxDemo :: AMsgBoxDemo( unsigned long windowId )
        :IFrameWindow(windowId)
        ,mbResponses(WND_MLE, this, this, IRectangle(),
                IMultiLineEdit::defaultStyle() | IMultiLineEdit::readOnly)
        ,mb(this)
        ,mbHelp(this)
{

/*--------------------- Setup the User Interface Objects -----------------|
|  Set the icon for the application.                                      |
|  Use the addLibraries member function to identify which IPF help file   |
|    contains the help information.                                       |
|  Set the client window of the frame to the IMultiLineEdit window,       |
|    size the frame, and show it.                                         |
|  Set the titles for the help and message box windows.                   |
|------------------------------------------------------------------------*/
   setIcon( windowId );
   try
   {
      mbHelp.addLibraries( "msgbox.hlp" );
      mbHelp.setTitle(IResourceId(STR_HELPT));
   }
   catch( ... )
   {
      IMessageBox
         msgBox( this );
      msgBox.setTitle( IResourceId( MSGBOX_HELP_NOT_FOUND_TITLE ) );
      msgBox.show( STR_HELP_NOT_FOUND, IMessageBox::warning );
   }

   setClient(&mbResponses);
   mb.setTitle(IResourceId(MSGBOX_TITLE));
} /* AMsgBoxDemo::AMsgBoxDemo( ... ) */

AMsgBoxDemo& AMsgBoxDemo :: runDemo()
{
   show();
/*--------------------- Message Box Samples Display Loop -----------------|
|  Each time the message box is to be shown:                              |
|    write a line to the status window describing the message box type,   |
|    show the message box,                                                |
|    trace the response to both the ITrace destination and status window. |
|  Use a message box to determine whether to repeat the loop.             |
|------------------------------------------------------------------------*/
  IMessageBox::Response reply;
  IResourceLibrary reslib;
  do
  {
    mbResponses.addLineAsLast(reslib.loadString(MSGBOX_SAMPLE_1));
    reply = mb.show( IResourceId( MSGBOX_OKCANCEL ),
                     IMessageBox::okCancelButton |
                     IMessageBox::informationIcon);
    traceReply(reply);

    mbResponses.addLineAsLast(reslib.loadString(MSGBOX_SAMPLE_2));
    reply = mb.show( IResourceId( MSGBOX_OKWARNING ),
                     IMessageBox::okButton |
                     IMessageBox::warningIcon);
    traceReply(reply);

    mbResponses.addLineAsLast(reslib.loadString(MSGBOX_SAMPLE_3));
    reply = mb.show( IResourceId( MSGBOX_CANCELERROR ),
                     IMessageBox::cancelButton |
                     IMessageBox::errorIcon);
    traceReply(reply);

    mbResponses.addLineAsLast(reslib.loadString(MSGBOX_SAMPLE_4));
    reply = mb.show( IResourceId( MSGBOX_YESNOCANCEL ),
                     IMessageBox::yesNoCancelButton |
                     IMessageBox::queryIcon);
    traceReply(reply);

    mbResponses.addLineAsLast(reslib.loadString(MSGBOX_SAMPLE_5));
    reply = mb.show( IResourceId( MSGBOX_YESNOCANCELHELP ),
                     IMessageBox::yesNoCancelButton |
                     IMessageBox::queryIcon |
                     IMessageBox::moveable,
                     MB_HELPID);
    traceReply(reply);

    mbResponses.addLineAsLast(reslib.loadString(MSGBOX_SAMPLE_6));
    reply = mb.show( IResourceId( MSGBOX_SYSMODAL ),
                     IMessageBox::enterButton | IMessageBox::systemModal |
                     IMessageBox::errorIcon);
    traceReply(reply);

/*--------------------- Demonstrate Exception Messages -------------------|
|  Call the throwException function to throw an IAccessError type of      |
|    exception.                                                           |
|  Catch the exception and show it in a message box.                      |
|------------------------------------------------------------------------*/
    mbResponses.addLineAsLast(reslib.loadString(MSGBOX_SAMPLE_7));
    try
    {
      throwException();
    }
    catch( IException &exc)
    {
      reply = mb.show( exc );
    }
    traceReply(reply);

    reply = mb.show( IResourceId( MSGBOX_CONTINUE ),
                      IMessageBox::yesNoButton |
                      IMessageBox::queryIcon);

  } while (reply == IMessageBox::yes);

/*--------------------- Display Final Message Box ------------------------|
|  Use the message box to display instructions for how to close the frame.|
|------------------------------------------------------------------------*/
  reply = mb.show( IResourceId( MSGBOX_END ),
                   IMessageBox::okButton |
                   IMessageBox::informationIcon);

  return (*this);
} /* end AMsgBoxDemo :: runDemo() */


/**************************************************************************
* Class AMsgBoxDemo :: traceReply -  Generates IStrings corresponding to  *
*   each IMessageBox enumeration and add the strings to the end of the    *
*   status windows.                                                       *
**************************************************************************/
AMsgBoxDemo& AMsgBoxDemo :: traceReply( IMessageBox::Response response )
{
  IResourceLibrary reslib;
  IString traceLine(reslib.loadString(STR_TRACE_LINE));
  IString stringReply(reslib.loadString(STR_TRACE_REPLY));
  switch (response)
  {
    case IMessageBox::enter:
      stringReply += IString(reslib.loadString(STR_TRACE_ENTER));
      break;
    case IMessageBox::ok:
      stringReply += IString(reslib.loadString(STR_TRACE_OK));
      break;
    case IMessageBox::cancel:
      stringReply += IString(reslib.loadString(STR_TRACE_CANCEL));
      break;
    case IMessageBox::abort:
      stringReply += IString(reslib.loadString(STR_TRACE_ABORT));
      break;
    case IMessageBox::retry:
      stringReply += IString(reslib.loadString(STR_TRACE_RETRY));
      break;
    case IMessageBox::ignore:
      stringReply += IString(reslib.loadString(STR_TRACE_IGNORE));
      break;
    case IMessageBox::yes:
      stringReply += IString(reslib.loadString(STR_TRACE_YES));
      break;
    case IMessageBox::no:
      stringReply += IString(reslib.loadString(STR_TRACE_NO));
      break;
    case IMessageBox::unknown:
      stringReply += IString(reslib.loadString(STR_TRACE_UNKNOWN));
      break;
    default:
      stringReply += IString(reslib.loadString(STR_TRACE_BAD));
      break;
  }
  traceLine += stringReply;
  IMODTRACE_ALL(traceLine);
  mbResponses.addLineAsLast(stringReply)
             .setCursorLinePosition(mbResponses.numberOfLines()-1)
             .addLineAsLast(reslib.loadString(STR_SPACE));
  return (*this);
} /* end AMsgBoxDemo :: traceReply() */


/**************************************************************************
* Class AMsgBoxDemo::throwException - Generates an IAccessError type of   *
*   exception to demonstrate use of the  IException type of message box.  *
**************************************************************************/
AMsgBoxDemo& AMsgBoxDemo :: throwException()
{
  ITHROWLIBRARYERROR( IC_MEMBER_ACCESS_ERROR ,
                      IBaseErrorInfo::accessError,
                      IException::recoverable);
  return *this;
} /* end AMsgBoxDemo :: throwException() */
