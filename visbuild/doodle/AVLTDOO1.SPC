











                                                          SPECIFICATION FOR THE
                                                             DOODLE APPLICATION
                                                                    VERSION 1.0







                                                                    May 8, 1995


                                                                            IBM


                                                            RTP, North Carolina
                                                                   avltdoo1.spc










































  CONTENTS
  ________





  CREATING A SIMPLE GRAPHICS DRAWING APPLICATION (V1)  . . . . . . . . . . .  1
  What You Should Be Able To Do  . . . . . . . . . . . . . . . . . . . . . .  1
  Specification  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  3















































                                                                    Contents  2









  CREATING A SIMPLE GRAPHICS DRAWING APPLICATION (V1)
  ___________________________________________________





  This scenario shows you how to build an application that uses the following:

  o   Modal windows

  o   Primitive parts

  o   Toolbars

  o   Toolbar buttons

  o   Radio buttons

  o   Push buttons

  o   Sliders

  o   Numeric spin buttons

  o   Text entry fields

  o   Static text

  o   Colors

  o   User provided parts

  o   Object factories

  o   Variables

  o   Parameterized connections


  WHAT YOU SHOULD BE ABLE TO DO
  _____________________________

  o   Start Visual Builder.

  o   Upgrade the V1 Doodle application.

  o   Import user provided part.

  o   Use the Public Interface Editor.

  o   Use the Composition Editor to update views of the V1 Doodle application.

      -   Add/remove visual and non-visual parts on the layout surface.
      -   Add/remove user provided parts on the layout surface.
      -   Make/change connections between parts and subparts.


                         Creating a Simple Graphics Drawing Application (V1)  1









  o   Will learn functional concepts about the following parts:

      -   Modal windows (dialogs)

          -   How to use a Visual Builder "factory"
          -   How to use a Visual Builder "variable"
          -   How to connect to a window
          -   How to create a modal window
          -   How to pass in data to the window
          -   How to return data from the window
          -   How to validate by range checking
          -   How to handle "Cancel"
          -   How to handle "Set"
          -   How to reuse a modal window

      -   Primitive parts

          -   Creating a part
          -   Creating a variable
          -   Setting limits
          -   Setting default values
          -   Creating conditional logic with connections
          -   Performing range checking using parts

      -   Toolbars

          -   Locating
          -   Horizontal orientation
          -   Vertical orientation
          -   Adding controls

      -   Toolbar buttons

          -   Latching
          -   Autolatching in groups
          -   Connect to non-visual parts
          -   Specify button bitmaps

      -   Radio buttons

          -   Latching
          -   Autolatching in groups
          -   Connect to non-visual parts

      -   Push buttons

          -   Connect to non-visual parts
          -   Connect to visual parts

      -   Sliders

          -   Initialize
          -   Set range
          -   Get/put data


                         Creating a Simple Graphics Drawing Application (V1)  2









          -   Connect to non-visual parts

      -   Numeric spin buttons

          -   Initialize
          -   Set range
          -   Get/put data
          -   Connect to non-visual parts

      -   Text entry fields

          -   Initialize
          -   Get/put data
          -   Set text limits

      -   Static text

          -   Initialize
          -   Get/put data
          -   Set colors
          -   Connect to non-visual parts
          -   Connect to visual parts

      -   Colors

          -   Initialize
          -   Get/put data
          -   Connect to non-visual parts
          -   Connect to visual parts

  o   Test the completed application

  o   Save the Doodle views.


  SPECIFICATION
  _____________

  This version of the Doodle application will have the following features:

  o   The Drawing Area - a drawing canvas used to display drawn graphic objects
      created with the defined graphic creation tools.

  o   The Drawing Tools Toolbar - contains selected object creation and manipu-
      lation tools

  o   The Colors Toolbar - contains buttons for frame and fill color dialogs,
      and direct color buttons for Red/Green/Blue fill.

  o   The Drawing Styles Toolbar - contains a button for drawing style dialog,
      and direct button- indicators for frame & fill, frame only, and fill only
      styles.

  o   The Pen Width Toolbar - contains a button for pen width dialog, and spin
      button-indicator for pen width value.


                         Creating a Simple Graphics Drawing Application (V1)  3









  o   The Titlebar Label Toolbar - contains a button for titlebar label dialog,
      and text entry field for titlebar label.

  o   The Pen/Fill Color Dialog Window - contains sliders for Red/Green/Blue
      components, numeric values, current color swatch, and set and cancel
      buttons.

  o   The Pen Width Dialog Window - contains entry field for pen width, value
      range checking, and set and cancel buttons.

  o   The Drawing Style Dialog Window - contains grouped radio buttons for
      drawing style, and set and cancel buttons.

  o   The Titlebar Label Window - contains text entry field for titlebar label,
      and set and cancel buttons.

  o   The Flyover Help Information - provides context-sensitive brief help
      information for participating controls and windows in the Doodle applica-
      tion.

  o   The Information Area - provides context-sensitive detailed help informa-
      tion for participating controls and windows in the Doodle application.

  This version of the Doodle application will provide drawing tools to create a
  variety of graphic objects.  Currently defined tools include:

  o   rectangle
  o   ellipse
  o   polygon
  o   line
  o   polyline
  o   freehand

  Drawing style may be specified for an object:

  o   Frame and Fill
  o   Frame only
  o   Fill only

  Colors may be specified for an object's frame and fill.

  Pen width may be specified for an object's frame.

  Current values for drawing style, colors, and pen width are displayed in the
  toolbars.

  An existing object may have new style attributes applied to it using the
  stylecan tool.

  An existing object may be removed using the eraser tool.

  An existing object may be moved by two methods:

  o   Drag with mouse button 1 using move tool


                         Creating a Simple Graphics Drawing Application (V1)  4









  o   Drag with mouse button 2 using any tool

  Additional tools may be added to the toolbar.  The drawing area has logic for
  additional tools:

  o   arc
  o   chord
  o   pie
  o   bitmap
  o   text

  END OF DOCUMENT
  _______________












































                         Creating a Simple Graphics Drawing Application (V1)  5



