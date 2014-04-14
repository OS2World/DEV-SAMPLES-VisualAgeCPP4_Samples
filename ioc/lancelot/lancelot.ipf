:userdoc.
:title.Lancelot &colon. A Valiant Example
:h1.What is Lancelot?
:i1.Description
:p.Lancelot is a personnel data tracking tool.
It tracks general personnel information, badge, status, skills,
system account information, projects, tasks, and your timecard.
This sample application is
intended to show integration rather than optimum
performance or coding.
:p.Lancelot was written by our QA group to utilize some of the more
complex objects provided by the :hp3.IBM Open Class&colon. User
Interface Class Library:ehp3..  Lancelot primarily utilizes these objects&colon.
:ul compact.
:li.IFrameWindow
:li.IMenuBar
:li.Infoarea
:li.IHelp
:li.IFont
:li.IResourceLibrary
:li.IContainerControl
:li.IContainerObject
:li.IPopupMenu
:li.INotebook
:li.IMultiCellCanvas
:li.ISetCanvas
:li.IProfile
:li.IEntryField
:li.IPushButton
:li.IGraphicPushButton
:li.INumericSpinButton
:li.IComboBox
:li.ICheckBox
:li.IMenuBar
:li.ITitle
:li.IString
:li.ICommandHandler
:li.ICnrHandler
:li.ICnrMenuHandler
:li.IDM*   <Direct Manipulation (i.e. Drag/Drop)>
:li.IToolBar
:li.IToolBarButton
:li.IFlyOverHelp
:li.IFlyOverHelpHandler
:li.IGPie
:li.IGRectangle
:li.IGString
:eul.
:p.In addition, Lancelot uses a simple flat database implemented with
IProfile.  However, this flat database is used only to show data
interaction with the GUI objects and avoid requiring a relational database
installed on your system.
:note.You should :hp4.NOT:ehp4. use the flat database provided for any
of your own applications!  We suggest you don't even look at the internals
of the database code.  The files you should avoid are ld*.*pp.
You should use a true relational database for
your applications.
.***********************
:h1.Lancelot Usage
:i1.Usage
:p.To create Lancelot, you must first compile and link the
application and it's components.
:ul.
:li.On AIX, issue
:xmp.
   make
:exmp.
:li.On OS/2, issue
:xmp.
   nmake
:exmp.
:li.For other environments, issue
:xmp.
   make
:exmp.
:eul.
:p.To execute Lancelot, simply issue
:xmp.
   lancelot
:exmp.
:h2.Lancelot Main window
:i1.Main Window
:p.Lancelot's main view is what you see when the application
first comes up.  It contains the :hp3.Query Personnel:ehp3. object
and any private query objects you may have created.
The :hp3.Query Personnel:ehp3. object queries employee information
dependent on your search criteria.  You have the option of saving the
search criteria in the main view for faster access next time.
:h2.Lancelot Query Information window
:i1.Information Window
:p.Lancelot's Query Information window contains a notebook with pages
for specifying personnel search criteria.
The pages available are&colon.
:dl tsize=30.
:dt.:hp3.General Page:ehp3.
:dd.General information for a person.
:dt.:hp3.Accounts Page:ehp3.
:dd.User accounts and systems for a person.
:dt.:hp3.Skills Page:ehp3.
:dd.Individual skills for a person.
:dt.:hp3.Badge Page:ehp3.
:dd.Badge information for a person.
:dt.:hp3.Status Page:ehp3.
:dd.Employement status information for a person.
:edl.
:p.The buttons available are&colon.
:dl tsize=30.
:dt.:hp3.Query:ehp3.
:dd.Query the personnel database given your search criteria.
If persons are found matching your criteria, a window appears with
objects representing each person.
:dt.:hp3.Save:ehp3.
:dd.Save your search criteria to the main view window for each access
next time.
:dt.:hp3.Help:ehp3.
:dd.Provide help for a specific page
:edl.
:h2.Lancelot Personnel window
:i1.Personnel Window
:p.Lancelot's Personnel view is what you see when the application
finds personnel matching your search criteria.
It contains an object for each person. By opening an object,
the Employee Information window appears with
specific information for this person.
:h2.Lancelot Employee Information window
:p.Lancelot's Employee Information window is displayed to show
employee information for a single employee.  Any changes to
the employee information will be saved in the database.  However,
the :hp3.Undo:ehp3. button can undo any changes you entered.
:p.The pages available are&colon.
:dl tsize=30.
:dt.:hp3.General Page:ehp3.
:dd.General information for the person.
:dt.:hp3.Accounts Page:ehp3.
:dd.User accounts and systems for the person.
:dt.:hp3.Skills Page:ehp3.
:dd.Individual skills for the person.
:dt.:hp3.Badge Page:ehp3.
:dd.Badge information for the person.
:dt.:hp3.Status Page:ehp3.
:dd.Employement status information for the person.
:dt.:hp3.Project Page:ehp3.
:dd.Projects the person has worked on.
:dt.:hp3.Tasks Page:ehp3.
:dd.Work tasks the person has worked on.
:dt.:hp3.Timecard Page:ehp3.
:dd.Timecard for the person.
:edl.
:p.The buttons available are&colon.
:dl tsize=30.
:dt.:hp3.Undo:ehp3.
:dd.Undo any changes to the employee's information you entered.
:dt.:hp3.Help:ehp3.
:dd.Provide help for a specific page
:edl.
.***********************
:h1.Lessons Learned
:i1.Lessons
:p.In coding Lancelot, we learned alot by the fine nuances of coding
GUI applications.
:h2.General
:i1.General Lessons
:p.There are several general things we learned in coding Lancelot.
:ul.
:li.When instantiating IWindow objects with the :hp3.new:ehp3. operator,
you must make sure to delete these objects when finished.  However,
there are times when you don't know how many windows you will have.
Therefore, you can use setAutoDeleteObject().  This function
deletes the IWindow object for you.
:p.Example&colon.
:xmp.
   IFrameWindow* myFrame = new IFrameWindow( ID_FRAME );
   myFrame->setAutoDeleteObject( true );
:exmp.
:li.IProfile changes are not visible until the IProfile object is
destroyed.
:li.There are two methodologies to using event handlers.
:ol.
:li.Create your own event handler class that inherits from an
event handler
:li.Multiply inherit from some visual object and from an event
handler
:eol.
The first method is preferred.
See LMainWindow (lmainwin.cpp) for an example.
However, the second method requires less coding.
See LInfoWindow (linfowin.cpp) for an example.
:li.If you do not specify a title string or define an ITitle for a
frame window, the frame window will get its title from the resource
file if the resource Id for the frame window is specified in
the string table.
:eul.
:h2.Containers
:i1.Container Lessons
:p.There are several things we learned about containers in coding Lancelot.
Here are some of the items we learned.
:ul.
:li.In order for a container to show detailsView, the container
must know about offset (binary location) information for
individual fields in a data class (data structure).  There are
two approaches for the container to query a data class' fields&colon.
:ol.
:li.Make the data class a friend of the container.  Then the container
can use something like this when creating it's columns&colon.
:xmp.
   IContainerColumn lastNameColumn(
           offsetof( EmployeeCnrObject, theLastName ) );
:exmp.
:li.-or- A better solution is to create a function in the
data class for each data field.  The function would do the following&colon.
:xmp.
   unsigned long EmployeeObject&colon.&colon.lastNameOffset()
   {
      return ( offsetof( EmployeeCnrObject, theLastName ) );
   }
:exmp.
The container column would then look like this&colon.
:xmp.
   IContainerColumn nameColumn(
           EmployeeCnrObject&colon.&colon.lastNameOffset() );
:exmp.
:eol.
:p.The only advantage to using option 2 is that any container can
get the data class field offsets without having to be friends.
The disadvantage is that if you have alot of data fields, you will
have to code query functions for each.  A good example of each
can be found in the class LMainCnr (lmainwin.cpp) and LPersonnelCnr
(lperswin.cpp).
:li.If you have a container object that contains your own data class object
and you want your data class object's private data fields to appear in
the container, do not specify the offset for your data class object itself.
Instead, specify the offset of the container object's variable name
representing your your data class and reference the data class object's
internal data field.
:p.Example&colon.
:xmp.
   IContainerColumn lastNameColumn(
             offsetof( EmployeeCnrObject, privateData.theLastName ) );
:exmp.
:li.In TreeIconView, the container allows only single selection.
Therefore, we must disallow the Select All function since only the last
cnr object will be selected.  And we must disallow the Deselect All
function since an exception will be thrown.
:eul.
:h2.Notebooks
:i1.Notebook Lessons
:p.There are several things we learned about notebooks in coding Lancelot.
Here are some of the items we learned.
:ul.
:li.When a page is added to a notebook and using the
autoPageSize style, the pages are automatically
resized to the current notebook size.  Therefore,
we need to resize the notebook pages to their
minimum size so that the notebook can
properly calculate it's minimum size.  See LInfoNotebook (linfonb.cpp)
for an example.
:li.In order to property size notebook tabs based on the current
font size, we sized the major tab width to be the
:p.( average character width for the current font ) X
( number of characters we want to display ).
:p.ISized the major tab height to be the
:p.( average uppercase height for the current font ) X 2.
:xmp.
   setMajorTabSize( ISize( notebookFont.avgCharWidth() *
                           ID_INFO_NOTEBOOK_TAB_CHARS,
                           notebookFont.avgUppercase() * 2 ) );
:exmp.
See LInfoNotebook (linfonb.cpp) for an example.
:eul.
:h2.Canvases
:i1.Canvas Lessons
:p.There are several things we learned about canvases in coding Lancelot.
Here are some of the items we learned.
:ul.
:li.For aligning like objects such as radio buttons,
ISetCanvas does the best job aligning.
:li.For aligning unlike objects such as entryfields and static text,
IMultiCellCanvas does the best job aligning.
:li.When aligning unlike objects, a minimum size for one object is usually
too large for an unlike object in the same column.  Therefore, place
the unlike object in a different column (usually one column more is
sufficient).
:eul.
:h2.Help
:i1.Help Lessons
:p.There are several things we learned about help in coding Lancelot.
Here are some of the items we learned.
:ul.
:li.General help is simply the panel associated with the HELPITEM in
the help table.
:p.Example&colon.
:xmp.
   HELPITEM      ID_MAIN, ......
:exmp.
:li.Help index and using help are usually generic.  So we can
use the generic system help by getting the id from
IHelpWindow&colon.&colon.index and IHelpWindow&colon.&colon.using.
:li.Keys help is always specific to the application.  Therefore,
we must write our own in the .IPF file.  There can be two approaches
to making keys help work&colon.
:ol compact.
:li.In the command() function, case off the id defined in the .RC
for the user selecting "Keys help" and then calling
help.show( id ) that is defined in the .IPF file.
However, if the user selects "Help/Keys help" inside the
Keys Help help window, an error can occur since the help
window itself doesn't know about the id in the .IPF file.
:li.-or- A better way is&colon.
:ol compact.
:li.Identify the "Keys help" menu with
SC_HELPKEYS and specify the MIS_SYSCOMMAND attribute.
:li.Create an IHelpHandler in your source code
:li.Have the IHelpHandler object handleEventsFor the main window
:li.Override the keysHelpId() function to specify the .IPF
id for keys help.
:p.Example&colon.
:xmp.
   event.setResult( id-in-IPF-file );
:exmp.
:eol.
:eol.
:li.Product information is your own dialog defined in the .CPP.
:li.F1 help for Keys Help must match the id for SC_HELPKEYS.
It is defined for OS/2 PM in pmwin.h.
It is defined for AIX Motif in ipmrc2X.
:li.You don't have to create a new IHelpWindow object for each secondary
frame window you create.  However if you don't, the following
will occur&colon.
:ol compact.
:li.When closing the secondary window, the help window doesn't close
:li.When closing the help window, focus returns to the owner of
the secondary window.
Nevertheless, these situations can be overcome by using
IHelpWindow&colon.&colon.setAssociateWindow() for the current window
that has focus.
:li.In order to have each notebook page show help when the Help button
is pressed, the notebook page must know about the frame window's
help window object so that it can call help.show(...).
The static function IHelpWindow&colon.&colon.helpWindow() returns this object.
:p.Example&colon.
:xmp.
   helpWin = IHelpWindow&colon.&colon.helpWindow( this );
   if ( helpWin )
        helpWin->show( IResourceId( ID_xxx ) );
:exmp.
:eol.
:eul.
:h2.Toolbar
:i1.Toolbar Lessons
:p.There are several things we learned about toolbars and toolbar buttons
in coding Lancelot.  Here are some of the items we learned.
:ul.
:li.If the toolbar appears in the header definition (.HPP) before the client,
the toolbar will take the focus.
:li.Toolbar buttons by default have a standard size.   But some words will
not fit inside the space provided.  Therefore, we allowed each button to
size itself based on it's needs.
:li.Since there doesn't exist a standard toolbar button bitmap for
some of Lancelot's functions, we created our own bitmaps.
These bitmaps must be 20x17 in order to match height and width of
the predefined library toolbar button bitmaps.
:eul.
:h2.2D Graphics
:i1.2D Graphics Lessons
:p.There are several things we learned about drawing with 2D graphics
in coding Lancelot.  Here are some of the items we learned.
:ul.
:li.If you don't use the setClippingRect() function to explicity set the
boundardy of a graphic string (IGString),
a graphic string may expand into the area of another graphic string.
Then the graphic string can be seen through the other graphic string.
:eul.
:h2.Profiles
:i1.Profile Lessons
:p.Lancelot stores data in a pseudo database.  The database is
implemented using IProfile.  On PM and Motif, profile data is
stored directly in &period.INI files.  On Windows, profile data is stored
in the Windows registry HKEY_LOCAL_MACHINE/Software with the key
as the &period.INI file name.
:euserdoc.
