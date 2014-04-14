











                                                          SPECIFICATION FOR THE
                                                   POLICE RAP SHEET APPLICATION
















































                                                                -- Page 1 of 10









  CONTENTS
  ________





  THE POLICE RAP SHEET APPLICATION   3
  What You Should Be Able To Do   4
  Specification   8















































                                                       Contents -- Page 2 of 10









  THE POLICE RAP SHEET APPLICATION
  ________________________________





  This application retrieves information about suspects from .ini files and
  displays the list of suspects in a container.  A notebook is used to display
  detailed information about a suspect.

  In building this application, the following was used:

  o   Frame Windows and using the IVBFactory part to create instances of them
      (frame window subclasses that represent composite visual parts).

  o   Canvas, which one of the visual parts imbeds

  o   Container (native and pmCompatible), including use of a menu handler to
      dynamically update the popup menu

  o   Notebook

  o   Menu Bar and Menu Item

  o   Collection View List Box

  o   IVSequences

  o   Factories

  o   Sample parts (e.g., IAddress and IVBBooleanPart)

  o   Variables

  o   Text Entry Fields

  o   Multiline Edit Field

  o   Text Push Buttons

  o   Graphic Push Buttons

  o   Animated Button

  o   Radio Buttons

  o   Numeric Spin Buttons

  o   Check Boxes

  o   String Combo Boxes

  o   Bitmap Controls



                               The Police Rap Sheet Application -- Page 3 of 10









  o   Group Boxes

  o   User provided Nonvisual Parts

  o   Parameterized Connections

  o   Event-to-Custom Logic Connections

  o   Event-to-Member Function Connections (see the ISuspectCnrView visual
      part)


  WHAT YOU SHOULD BE ABLE TO DO
  _____________________________

  The following identifies what parts were used to build the visual composite
  parts and how these parts were used.

  o   Frame Windows

      -   Create subclasses of a frame window to represent application views
          (e.g., IRapMainView, ISuspectCnrView, and ISuspectNotebook)

  o   Canvas (see the IAddressView part)

      -   Visually construct for reuse
      -   Encapsulate access by using a variable
      -   Imbed into another view

  o   Container

      -   Identify class of items
      -   Identify icon to represent items
      -   Identify item data to be displayed as the icon text
      -   Enable users to switch between an Icon view and a Details view
      -   Identify attributes to display as columns in the Details View
      -   Get items thru a nonvisual part connection
      -   Select and deselect all objects in the container using event-to-
          member custom logic connections
      -   Attach a user-created menu handler (that subclasses ICnrMenuHandler)
          to control what menu items should appear in the popup menu (based on
          the position of the mouse pointer - whether it's over an object or
          not).  

          (NOTE: Do not make the container the client of a frame window - if
          so, commandEvent will fire twice each time an item is selected from
          the popup menu.  Recommend placing a IMultiCellCanvas part in the
          client area of the frame window and then placing the container on the
          IMultiCellCanvas part and identifying it as expandable).



                               The Police Rap Sheet Application -- Page 4 of 10









      -   Identify what should happen when the user double-clicks on an object
          or selects one or more objects and hits Enter.
      -   Use a pmCompatible container to represent the list of arrests on the
          Priors page of the ISuspectNotebook part (NOTE: a pmCompatible part
          was used because the details view headings for the native container
          can not be hidden). A details view container is a better choice than
          a collection view list box in this case since need to display mul-
          tiple attributes of the arrest part.

  o   Notebook

      -   Define the layout of the notebook
      -   Define the pages and subpages of a notebook
      -   Enable tabbing between the notebook tabs and the pages (Alt+down
          arrow to tab from a notebook tab to a control within its corre-
          sponding page, and Alt+up arrow to tab from a page to its corre-
          sponding notebook tab).

  o   Menu Bar and Menu Items

      See the ISuspectCnrView visual part for examples of how to:

      -   Identify a menu bar for a window
      -   Define the pull-down menu items for the menu bar
      -   Identify what should happen when a menu item is selected
      -   Dynamically grey out a menu item
      -   Check and uncheck a menu item

  o   Collection View List Box

      See the ISuspectNotebook visual part for examples of how to:

      -   Identify class of items
      -   Identify item data to be displayed (via the asString member function
          of the class that is specified for the items)
      -   Get the items by connecting to an (IVSequence *) attribute of a non-
          visual part
      -   Allow data about a selected item to be updated (see the Priors page
          of the ISuspectNotebook part).
      -   Allow new items to be added (see the Priors page of the
          ISuspectNotebook part).

  o   IVSequences

      See the ISuspectNotebook visual part for examples of how to:

      -   Map to the items of an ICollectionViewListBox or an
          IVBContainerControl part
      -   Use custom logic to invoke member functions against an IVSequence
          (e.g., to prime it or refresh it from another IVSequence)
      -   Add to and update elements in an IVSequence (see the Priors page)

  o   Factories



                               The Police Rap Sheet Application -- Page 5 of 10









      Use an IVBFactory part from the parts palette to:

      -   New a user-created visual part, set its focus and show it (see the
          IRapMainView and ISuspectCnrView visual parts).
      -   New a nonvisual part (IArrest in ISuspectNotebook)
      -   Set a part's variable or attributes prior to newing it

  o   Sample parts

      -   Use IVBBooleanPart to dynamically disable/enbable menu items (see the
          ISuspectCnrView visual parts) or to support the mutual exclusion of
          two radio buttons (see the ISuspectNotebook visual part)
      -   Use the IAddress model part

  o   Variables

      -   Create a variable to represent a visual part and set it (the this
          attribute) from the actionResult of the new action of a factory part
          (see the ISuspectCnrView or the ISuspectNotebook visual parts)
      -   Create a variable to represent a nonvisual part and set it from from
          an attribute of a visual part (see the ISuspectNotebook and
          ISuspectCnrView visual parts, respectively).
      -   Use a variable to show data about an item that a user selects from an
          IVBContainerControl part (see the Priors page of the ISuspectNotebook
          visual part)

  o   Text Entry Fields

      -   Get/put data
      -   Limit size of text
      -   Specify default text
      -   Enable auto scroll and auto tab
      -   Specify read only fields

  o   Multiline Edit Field (MLE)

      See the ISuspectNotebook visual part for an example of how to:

      -   Connect to a nonvisual part

  o   Text Push Buttons

      See the UPDATE button on the Priors page of the ISuspectNotebook for an
      example of how to:

      -   Dynamically disable
      -   Connect to custom logic
      -   Connect to a visual part

  o   Graphic Button

      See the IRapMainView visual part for an example of how to:




                               The Police Rap Sheet Application -- Page 6 of 10









      -   Identify the icon for the graphic button in the settings notebook of
          the part
      -   Perform an action when a user clicks on it

  o   Animated Button

      See the BOOK button on the Priors page of the ISuspectNotebook part for
      an example of how to:

      -   Identify in the settings notebook the initial resource ID, number of
          bitmaps, and the resource library
      -   Start and stop animation

  o   Radio Buttons

      See the radio buttons on the Personal page of the ISuspectNotebook part
      for an example of how to:

      -   Group radio buttons (to support their mutual exclusion) and enable
          tabbing for each
      -   Identify the default radio button

  o   Numeric Spin Buttons

      See the IHeightSpinButton and ISuspectNotebook visual parts for an
      example of how to:

      -   Identify the lower and upper range in the settings notebook of the
          part
      -   Map the value attribute of the numeric spin button to the attribute
          of a nonvisual user part
      -   Support a master and servant spin button, and use a handler to enable
          the servant to automatically spin up or down whenever the master is
          spun past one of its bounds.

  o   Check Boxes

      -   Use check boxes to represent Boolean attributes in a nonvisual part.

  o   String Combo boxes

      -   Specify the initial contents of the combo boxes using the settings
          notebook.
      -   Ensure the initial contents of the combo boxes get generated out as
          resource strings by selecting the "Starting resource id" check box in
          the Class Editor.
      -   Since strings are not stored in the database, map the selection
          attribute of the combination boxes to the appropriate nonvisual part
          attributes (that accept an enumerated value).

  o   Bitmap Controls

      -   Identify which bitmap should be displayed by connecting to the bitmap
          attribute.


                               The Police Rap Sheet Application -- Page 7 of 10









  o   Group Boxes

      -   Update the label/text of the group boxes
      -   Place parts within the group boxes  (

          NOTE:  If you place a group box over the parts you want it to group,
          you need to update the tabbing and depth order to ensure that the
          group box is higher in the depth order).


  SPECIFICATION
  _____________

  This application enables users to browse information about suspects - from
  those who have not been charged yet, to those who have been charged and con-
  victed.

  Since the main intent of this sample application is to show how to use other
  parts to construct the views of an application, database support was kept to
  a minimum.  Data is stored in .ini files, which on Windows, is stored as
  Software in the Windows registry.  No updates to data (e.g., on the Priors
  page of the ISuspectNotebook part) are written out to the .ini files.  The
  .ini files are just used to simulate a primed database.

  Selection of the Witness Identification push button initiates the retrieval
  of suspect information from the database.

  A container is used to display the list of known suspects. This container
  supports extended selection so one or more suspects may be selected.

  You can view detailed information about one or more suspects, by opening the
  suspects.  You can open one or more suspects by either:

  o   selecting mouse button 2 while the cursor is over a suspect and then
      selecting Open from the popup menu
  o   double-clicking on a suspect
  o   selecting the suspects and then hitting Enter
  o   selecting the suspects and then selecting SELECTED->OPEN
  o   selecting the suspects and then selecting mouse button 2 while the cursor
      is over one of the selected suspects

  Some of the information that may be displayed for a suspect are the suspect's
  arrest history, current address, mug shots (if available), physical
  description, and aliases.  (

  NOTE:   mug shots are available for the suspects that have a book number of 0
  and 3)

  This application consists of the following visual parts:

  o   IRapMainView - a window that provides law enforcement officers and per-
      sonnel with access to various functions.  Since this application is
      limited in scope, only the Witness Identification function is supported.




                               The Police Rap Sheet Application -- Page 8 of 10









  o   ISuspectCnrView - a window used for displaying an icon or details view of
      known suspects.

  o   ISuspectNotebook - a window used to display detailed information about a
      suspect.  This information includes a suspect's name, aliases, arrest
      history, character description, and the suspect's birthdate.  The note-
      book consists of the following pages:

      -   General page - used to display the suspect's first and last name,
          book number, modus operandi, and general information.  The following
          subpages provide additional information:

          --  Address page - displays the address of the suspect's residence
          --  Personal page - displays physical information about the suspect,
              such as their hair and eye color, weight and height, and gender.
              The suspect's birthdate is also displayed if known.
          --  Marks page - identifies any known distinguishing marks that the
              suspect has
          --  Mug Shots page - displays any mug shots that have been taken of
              the suspect

      -   Aliases page - displays a list of aliases the suspect is known by

      -   Priors page - displays the suspect's arrest history.  The status and
          status date fields of an arrest record can be updated as well.  The
          suspect can also be booked on additional charges by specifying values
          for the fields at the top of the page and then selecting the BOOK
          animated push button (

          NOTE:   since this application is limited in scope, the updates and
          the specification of additional charges are not saved to the .ini
          files; they are only temporarily saved in the suspect object).

  o   IAddressView - a canvas created for reuse.  This part was added to the
      Address subpage of the ISuspectNotebook part.

  o   IHeightSpinButton - a part that can be used to identify the height of an
      object.  Two numeric spin buttons are used to represent the height.  One
      represents the height in terms of feet, and the other in terms of inches.
      The total height of the object (in inches) is calculated from the value
      of these two buttons and is represented by the height attribute.  This
      part was added to the Personal subpage of the ISuspectNotebook part.

  The nonvisual parts that support this application are:

   -   Parts that represent model parts.  These parts consist of the
       following: IAlias, IArrest, IPerson, and ISuspect.
   -   Parts that subclass the IRecord part (e.g., ISuspectRecord).  These
       parts were created to facilitate expanding the Police Rap Sheet
       application into a client-server application.


                               The Police Rap Sheet Application -- Page 9 of 10









   -   Parts that serve to hide knowledge of where data is stored (e.g.,
       ISuspectClientMgr).



  END OF DOCUMENT















































                              The Police Rap Sheet Application -- Page 10 of 10



