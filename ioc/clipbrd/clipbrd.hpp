/******************************************************************************
* .FILE:         clipbrd.hpp                                                  *
*                                                                             *
* .DESCRIPTION:  Clipboard Sample Program : Class Definitions                 *
*                                                                             *
* .CLASSES:      ContainerCutPasteHandler                                     *
*                Department                                                   *
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
#ifndef _CLIPBRD_
  #define _CLIPBRD
#include <icliphdr.hpp>
#include <icmdhdr.hpp>
#include <istring.hpp>
#include <icnr.hpp>


//**************************************************************************
// Class:   Department                                                     *
//                                                                         *
// Purpose: Defines the data stored in the container for a Department.     *
//                                                                         *
//**************************************************************************
class Department : public IContainerObject {
  public:
    Department ( const IString& name=IString(),
                 const IString& address=IString())
      : IContainerObject (name),
        strAddress(address) {}

    // Add functions to query and set the data.
    virtual IString
      name       ( ) const,
      address    ( ) const;

    virtual Department
     &setName    ( const IString& name),
     &setAddress ( const IString& address);

    // Define the functions to render an object both as a
    // private format and as a normal text string, and to
    // re-construct the object from the private format.
    IString
      asString        ( ) const,
      text            ( ) const;
    Department
     &initializeFromString  ( const IString& renderedString);

    // Define the separator character (a tilde) that separates
    // the fields of the object in its string format.
    static const IString
      separator,
      renderedFormat;

    // Define a function to return the offset of the Address field.
    static unsigned long
      offsetOfAddress ( ) { return ICONTAINERCOLUMN_OFFSETOF(Department, strAddress); }



  private:
    IString
      strAddress;
};

class ICnrObjectSet;

//**************************************************************************
// Class:   ContainerCutPasteHandler                                       *
//                                                                         *
// Purpose: Adds Clipboard support to the container for a Department       *
//          object.  This includes:                                        *
//          1) A container menu handler to show a popup menu with          *
//             cut, copy, and paste choices.                               *
//          2) A command handler to process the cut, copy, and paste       *
//             requests.                                                   *
//          3) A clipboard handler to process requests from the clipboard  *
//             to render data not yet on the clipboard.                    *
//**************************************************************************
class ContainerCutPasteHandler : public ICommandHandler,
                                 public ICnrMenuHandler,
                                 public IClipboardHandler {
  public:
    ContainerCutPasteHandler (IContainerControl& container);
    ~ContainerCutPasteHandler ();
    
    IContainerControl
     &container  ( ) { return cnr; }

  protected:
    // Define the command handler callback.
    virtual bool
      command ( ICommandEvent& event);

    // Define the popup menu callback.
    bool
      makePopUpMenu(IMenuEvent& cnEvt);

    // Define the callbacks to render data on the
    // clipboard.
    virtual bool
      clipboardEmptied     ( IEvent&        event ),
      renderFormat         ( IEvent&        event,
                             const IString& format),
      renderAllFormats     ( IEvent&        event);

    // Define a string object to use as a separator between fields
    // for the private format.
    static const IString
      separator;

    IString
      selectedData ( );

  private:
    IContainerControl
     &cnr;
    ICnrObjectSet
     *objectList;
};

#endif
