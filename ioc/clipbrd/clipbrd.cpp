/******************************************************************************
* .FILE:         clipbrd.cpp                                                  *
*                                                                             *
* .DESCRIPTION:  Clipboard Sample Program :            Class Implementation   *
*                                                                             *
* .CLASSES:      ContainerCutPasteHandler                                     *
*                Department                                                   *
*                                                                             *
* .COPYRIGHT:                                                                 *
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
#include <iframe.hpp>
#include <ipopmenu.hpp>
#include <iclipbrd.hpp>
#include <icliphdr.hpp>
#include <icmdhdr.hpp>
#include <icnr.hpp>
#include <icnrolst.hpp>
#include <istring.hpp>
#include <istparse.hpp>
#include <iexcept.hpp>
#include <itrace.hpp>
#include <ireslib.hpp>
#include <icoordsy.hpp>
#include "clipbrd.h"
#include "clipbrd.hpp"

// Define our static Separator objects:
//   The first separates fields in the Department object string;
//   the second separates multiple Department object strings.


const IString Department::separator("~");
const IString ContainerCutPasteHandler::separator("^");

// Define the private format of our Department object.
const IString Department::renderedFormat("Department_rendered");


//*************************************************************************
// main  - Application entry point                                        *
//*************************************************************************
int main()
{
  ICoordinateSystem::setApplicationOrientation(
          ICoordinateSystem::kOriginLowerLeft );
  IResourceLibrary reslib;
  IFrameWindow frame(reslib.loadString(WND_MAIN), WND_MAIN);

  // Create the details view container with columns that
  // displays the Department name and address.
  IContainerControl container(0x8008, &frame, &frame);
  IContainerColumn name(IContainerColumn::isIconViewText);
  IContainerColumn address( Department::offsetOfAddress());
  name.setHeadingText( STR_HEAD_1 );
  address.setHeadingText( STR_HEAD_2 );
  container.addColumn(&name);
  container.addColumn(&address);

  // Create the Department objects and add them to
  // the container.
  Department* department;
  department = new Department(reslib.loadString(STR_ITEM_1_1),
                              reslib.loadString(STR_ITEM_1_2));
  container.addObject(department);
  department = new Department(reslib.loadString(STR_ITEM_2_1),
                              reslib.loadString(STR_ITEM_2_2));
  container.addObject(department);

  // Create the cut and paste handler (the handlers are
  // added in the constructor).
  ContainerCutPasteHandler handler(container);

  // Enable extended selection, switch to details view, and
  // give the container the focus.
  container.setExtendedSelection();
  container.showDetailsView();
  container.setFocus();

  // Add an icon to the frame, put the container in the
  // client, and show the frame window.
  frame.setIcon( frame.id() );
  frame.setClient(&container);
  frame.show();

  // Start processing events.
  IApplication::current().run();

  return 0;
}


/*------------------------------------------------------------------------------
| ContainerCutPasteHandler::ContainerCutPasteHandler                           |
|                                                                              |
| Construct the handlers, register our private clipboard format, and           |
| attach the handlers to the container.                                        |
------------------------------------------------------------------------------*/
ContainerCutPasteHandler :: ContainerCutPasteHandler ( IContainerControl& container)
      : cnr(container),
        objectList(new ICnrObjectSet())
{
  // Enable the command, menu, and clipboard handlers.
  ICommandHandler::handleEventsFor(&container);
  ICnrMenuHandler::handleEventsFor(&container);
  IClipboardHandler::handleEventsFor(&container);

  // Register the Department object's private format.
  IClipboard::registerFormat( Department::renderedFormat);
}

/*------------------------------------------------------------------------------
| ContainerCutPasteHandler::~ContainerCutPasteHandler                          |
|                                                                              |
| Destruct the object list.                                                    |
------------------------------------------------------------------------------*/
ContainerCutPasteHandler :: ~ContainerCutPasteHandler ()
{
  delete objectList;
}

/*------------------------------------------------------------------------------
| ContainerCutPasteHandler::command                                            |
|                                                                              |
| Handle the command events associated with the clipboard (Cut, Copy,          |
| and Paste).                                                                  |
------------------------------------------------------------------------------*/
bool ContainerCutPasteHandler::command ( ICommandEvent& event)
{
  switch(event.commandId())
  {
    case MI_CUT           :
    case MI_COPY          :
    {

      // Create a clipboard object.
      IClipboard clipboard(event.controlWindow()->handle());


      // Find the cursored object in the container.
      Department* cursoredObject = (Department*)(container().cursoredObject());

      // If a Copy request, utilize delayed rendering to put the data of
      // of the private format on the clipboard. If a Cut request, put
      // the data directly on the clipboard since the object won't be
      // around later when the renderFormat code needs it.
      // We maintain an "objectList" collection to keep track of 
      // the objects copied onto the clipboard so that renderFormat
      // knows which objects to render.
      // We also store text data for the objects so that applications
      // that don't support the private format can paste the data into a
      // text editor.

      // Clear the collection used to keep track of clipboard objects.
      objectList->removeAll();

      // If the cursored object is selected, loop through all other
      // selected objects and store the objects in our set.
      if (container().isSelected(cursoredObject))
      {
        unsigned long count = 0;
        IString objectsAsText("\0");
        IContainerControl::ObjectCursor cursor(container(), IContainerObject::selected);
        for (cursor.setToFirst(); cursor.isValid(); cursor.setToNext())
        {
          count++;
          Department* selectedObject = (Department*)(container().objectAt(cursor));
          objectList->add(selectedObject);
          objectsAsText = objectsAsText +  selectedObject->text();
        }


        // Empty the clipboard to establish ownership
        clipboard.empty();

        // Put the data on the clipboard.  We put our private
        // format first since it has the most information.
        // We use 0 for the data on a Copy request because
        // we want to delay the rendering until
        // the paste operation.
        // If this is a Cut, put the data on the clipboard
        // instead of using delayed rendering because we delete
        // the object.

        if (event.commandId() == MI_CUT)
        {
          IString string = selectedData();
          clipboard.setData(Department::renderedFormat, (const char*)string, string.length()+1);
          objectList->removeAll();
          container().deleteSelectedObjects();
        }
        else
          clipboard.setData(Department::renderedFormat, 0, 0);
        
        clipboard.setText(objectsAsText);
      }
      else
      {
        // If the object is not selected, repeat the above procedure
        // for the cursored object.
        objectList->add(cursoredObject);

        // Empty the clipboard to establish ownership
        clipboard.empty();

        // Put the data on the clipboard (using
        // delayed rendering for a Copy. Delete the object
        // if a Cut request.
        IString objectAsText = cursoredObject->text();
        if (event.commandId() == MI_CUT)
        {
           IString string = selectedData();
           clipboard.setData(Department::renderedFormat, (const char*)string, string.length()+1);
           objectList->removeAll();
           container().removeObject(cursoredObject);
           delete cursoredObject;
        }
        else
          clipboard.setData(Department::renderedFormat, 0,0);

        clipboard.setText(objectAsText);
      }
      return true;
    }
    case MI_PASTE         :
    {
      IClipboard clipboard(event.controlWindow()->handle());

      // If the clipboard has data of the private format,
      // get the data and build objects from it.
      // Note:  To see the text format of the data, paste
      // from the clipboard using any text editor that
      // supports the clipboard.
      if (clipboard.hasData(Department::renderedFormat))
      {
         IString strCount, strObject, objectsAsString;

         // Query the data on the clipboard.
         char* data = (char*)clipboard.data(Department::renderedFormat);

         // Parse the string into our data fields.
         data >> strCount >> separator >> objectsAsString;

         // Extract the number of objects stored in the string.
         unsigned long count = strCount.asUnsigned();

         // Turn refresh off to eliminate multiple painting.
         container().setRefreshOff();

         // Construct new objects from the data.
         for( int i=0; i<count; i++)
         {
           objectsAsString >> strObject >> separator >> objectsAsString;
           Department* department = new Department();
           department->initializeFromString(strObject);
           container().addObject(department);
         }

         // Enable refresh and refresh the container.
         container().setRefreshOn();
         container().refresh();
      }
      return true;
    }
  }
return false;
}


/*------------------------------------------------------------------------------
| ContainerCutPasteHandler::makePopUpMenu                                      |
|                                                                              |
| Create a pop-up menu with the clipboard actions.                             |
------------------------------------------------------------------------------*/
bool ContainerCutPasteHandler::makePopUpMenu(IMenuEvent& event)
{
  IPopUpMenu* popUpMenu = new IPopUpMenu(CNR_POPUPMENU,
                                         event.controlWindow());

  // Enable the allowable menu items in the pop-up menu.
  if (popupMenuObject()) {
    ((IContainerControl*)event.controlWindow())->setCursor(popupMenuObject());
    popUpMenu->disableItem(MI_PASTE);
  }
  else
  {
    popUpMenu->disableItem(MI_CUT);
    popUpMenu->disableItem(MI_COPY);
  }

  //  Show the menu.
  popUpMenu->setAutoDeleteObject();
  popUpMenu->show(event.mousePosition());
  return true;
}

/*------------------------------------------------------------------------------
| ContainerCutPasteHandler::clipboardEmptied                                   |
|                                                                              |
| This function is responsible for cleaning up data when the clipboard is      |
| emptied and has nothing to do for now.                                       |
------------------------------------------------------------------------------*/
bool ContainerCutPasteHandler::clipboardEmptied ( IEvent& )
{
  return true;
}

/*------------------------------------------------------------------------------
| ContainerCutPasteHandler::renderFormat                                       |
|                                                                              |
| Put our private format data on the clipboard.                                |
------------------------------------------------------------------------------*/
bool ContainerCutPasteHandler::renderFormat( IEvent& event,
                                               const IString&  format)
{
  // Use the handler's collection to find the Department objects
  // whose data we need to put on the clipboard.
  IClipboard clipboard(event.controlWindow()->handle());
  if (format == Department::renderedFormat)
  {
    IString objectsAsString = selectedData();
    setDelayedData(event,
                   Department::renderedFormat,
                  (const char*)objectsAsString,
                  objectsAsString.size());  
    return true;
  }
  return false;

}


/*------------------------------------------------------------------------------
| ContainerCutPasteHandler::selectedData                                       |
|                                                                              |
| Return an IString containing the data to put on the clipboard.               |
------------------------------------------------------------------------------*/
IString ContainerCutPasteHandler::selectedData( ) 
{
  // Use the handler's collection to find the Department objects
  // whose data we need to put on the clipboard.

   // Cursor the objects and build the string.
   ICnrObjectSet::Cursor cursor(*objectList);

   IString objectsAsString("\0");
   unsigned long count = 0;

   // Loop through our collection and query the object for
   // its data.
   for( cursor.setToFirst(); cursor.isValid(); cursor.setToNext())
   {
     count++;
     Department* department = (Department*)objectList->elementAt(cursor);

     // Document that no support is present for rendering objects
     // after they are removed from the container.
     IASSERTSTATE(container().containsObject(department));

     objectsAsString = objectsAsString + separator
                                    + department->asString();
   }
   // Build the final string for the clipboard and return it.
   objectsAsString  =  IString(count) + objectsAsString;

   return objectsAsString;
}

/*------------------------------------------------------------------------------
| ContainerCutPasteHandler::renderAllFormats                                   |
|                                                                              |
| Pass this on to our function to render a single format since we only use     |
| one format with delayed rendering.                                           |
------------------------------------------------------------------------------*/
bool ContainerCutPasteHandler::renderAllFormats( IEvent& event)
{
  return renderFormat(event, Department::renderedFormat);
}


/*------------------------------------------------------------------------------
| Department::name                                                             |
|                                                                              |
| Return the name of the Department object.                                    |
------------------------------------------------------------------------------*/
IString Department::name( ) const
{
  return iconText();
}

/*------------------------------------------------------------------------------
| Department::address                                                          |
|                                                                              |
| Return the address of the Department object.                                 |
------------------------------------------------------------------------------*/
IString Department::address( ) const
{
  return strAddress;
}

/*------------------------------------------------------------------------------
| Department::setName                                                          |
|                                                                              |
| Set the name of the Department object.                                       |
------------------------------------------------------------------------------*/
Department& Department::setName( const IString& name)
{
  setIconText(name);
  return *this;
}

/*------------------------------------------------------------------------------
| Department::setAddress                                                       |
|                                                                              |
| Set the address of the Department object.                                    |
------------------------------------------------------------------------------*/
Department& Department::setAddress( const IString& address)
{
  strAddress = address;
  return *this;
}

/*------------------------------------------------------------------------------
| Department::asString                                                         |
|                                                                              |
| Render the Department object as a String that we can later use to            |
| reconstruct a Department object.                                             |
------------------------------------------------------------------------------*/
IString Department::asString ( ) const
{
  IString strObject = name() + separator + address();
  return strObject;
}

/*------------------------------------------------------------------------------
| Department::text                                                             |
|                                                                              |
| Render the Department object as a text string with Name formatted to         |
| 30 characters, and address formatted to 50 characters with both              |
| followed by a new line character.  Use this format for storing a plain       |
| text format of our object on the clipboard.                                  |
------------------------------------------------------------------------------*/
IString Department::text ( ) const
{
  IString strObject(name().subString(1,30) + address().subString(1,50) + "\n");
  return strObject;
}


/*------------------------------------------------------------------------------
| Department::initializeFromString                                             |
|                                                                              |
| Set the fields of the object by parsing the passed string.                   |
------------------------------------------------------------------------------*/
Department& Department::initializeFromString ( const IString& renderedString )
{
  IString strName, strAddress;
  renderedString >> strName >> separator >> strAddress;
  setName (strName);
  setAddress(strAddress);

  return *this;
}


