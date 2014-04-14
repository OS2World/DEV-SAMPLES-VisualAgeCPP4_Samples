 
 
 
 
 
 
 
 
 
 
 
 
                                                          SPECIFICATION FOR THE
                                                         CALCULATOR APPLICATION
                                                                    VERSION 2.1
 
 
 
 
 
 
 
                                                                   May 15, 1995
 
 
                                                            Alpha Omega Company
 
 
                                                           Cary, North Carolina
                                                                   avltcal2.spc
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
  CONTENTS
  ________
 
 
 
 
 
                      Document Description   . . . . . . . . . . . . . . . .  1
                      Document Control   . . . . . . . . . . . . . . . . . .  1
 
                      CREATING A SIMPLE CALCULATOR APPLICATION (V2)  . . . .  3
                      What You Should Be Able To Do  . . . . . . . . . . . .  3
                      Specification  . . . . . . . . . . . . . . . . . . . .  5
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
                                                                    Contents  2
 
 
 
 
 
 
 
 
 
  DOCUMENT DESCRIPTION
  ____________________
 
  
   CREATING A SIMPLE CALCULATOR APPLICATION (V2)
  _____________________________________________
 
 
 
 
 
                      This scenario shows you how to build an application that
                      uses the following:
 
                      o   Text Entry Field
 
                      o   Multiline Edit Field
 
                      o   Push buttons
 
                      o   File dialog box
 
                      o   An imbedded view
 
                      o   Parameterized connections
 
                      o   User provided non-visual parts
 
                      o   Message Box
 
                      o   Simple exception handling (divide by zero)
 
                      o   Command handler
 
                      o   Keyboard handler
 
 
  WHAT YOU SHOULD BE ABLE TO DO
  _____________________________
 
                      o   Start Visual Builder.
 
                      o   Upgrade the V1 calculator application.
 
                      o   Import user provided non-visual parts.
 
                      o   Use the Public Interface Editor.
 
                      o   Use the Composition Editor to update the views of V1
                          Calculator.
 
                          -   Add/remove non-visual parts on the layout
                              surface.
                          -   Add/remove user provided parts on the layout
                              surface.
                          -   Make/change connections between parts and sub-
                              parts.
                          -   Attach/remove handlers to ICanvas
 
                      o   Use the Class Editor to add the handler header files.
 
 
                               Creating a Simple Calculator Application (V2)  3
 
 
 
 
 
 
 
 
 
                      o   Will learn functional concepts about the following
                          parts:
 
                          -   Text Entry Field
 
                              -   Initialize
                              -   Get/put data
                              -   Maintain right justification
 
                          -   Multiline Edit Field (MLE)
 
                              -   Clear (Reset)
                              -   Update (append line)
                              -   Query (get) data
                              -   Put data to ASCII flat file
 
                          -   Push buttons
 
                              -   Make labels connection parameters
                              -   Connect to non-visual parts
                              -   Connect to visual parts
                                  o   Save Tally to File Dialog
                                  o   Clear All to MLE
 
                          -   Imbedded views
 
                              -   How to use Visual Builder "variable"
 
                          -   File Dialog Box
 
                              -   How to connect to one (display)
                              -   Get file name from one (name entered)
                              -   How to handle "Cancel"
                              -   Show filename syntax checking
 
                          -   Message Box
 
                              -   How to connect to one (display)
                              -   How to use in conjunction with simple excep-
                                  tion handling
 
                          -   Handlers
 
                              -   How to attach a handler to a control in the
                                  Composition Editor
                              -   How to add the associated handler .hpp
                                  file(s) via the Class Editor
 
                      o   Test the completed application
 
                      o   Save the Calculator views.
 
 
 
 
 
                               Creating a Simple Calculator Application (V2)  4
 
 
 
 
 
 
 
 
 
  SPECIFICATION
  _____________
 
                      This version of the calculator will have the following
                      features:
 
                      o   The Display - a single line display used to display
                          the numeric digits being entered.
 
                      o   The Tally Sheet - a multiple line display for holding
                          a track of entered data, operators, functions, and
                          calculations.
 
                      o   Display a message box when a divide by zero exception
                          is detected.
 
                      o   A keypad with ten numeric keys (0-9).
 
                      o   Four arithmetic operator keys (+, -, *, /).
 
                      o   Four function keys (Clear, Clear All, =, Save Tally).
 
                      This version of the calculator will perform only integer
                      arithmetic and does not support operator precedence.
 
                      As numeric keys are pushed, the appropriate numeric digit
                      will be displayed in the rightmost position of the
                      display.
 
                      Pressing an arithmetic operator key specifies the opera-
                      tion to be performed on the current running total with
                      the next number entered.  The tally sheet will be updated
                      with the contents of the display, if any, and the symbol
                      for the operator pressed.
 
                      When a function key is pressed, that function is per-
                      formed immediately as defined below:
 
                      o   "=" means to evaluate and display the result of any
                          pending operation/expression.  If there is nothing
                          pending then this causes the last
                          operation/expression to be evaluated and its result
                          displayed.  For example, pressing the following push
                          buttons (in the order listed), 7 + 2 =, will cause 7
                          to be added to 2 and 9 to be displayed.  Pressing the
                          equal push button two more times would result in 9 +
                          2 being evaluated and 11 displayed, and then 11 + 2
                          being evaluated and 13 displayed.
 
                      o   "Clear Display" means to reset the display to blank.
 
                      o   "Clear All" means to reset everything to zero.
 
                      o   "Save Tally" means to save the current tally sheet to
                          a user designated ASCII flat file.
 
 
                               Creating a Simple Calculator Application (V2)  5
 
 
 
 
 
 
 
 
 
                      END OF DOCUMENT
                      _______________
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
                               Creating a Simple Calculator Application (V2)  6
 
 
 
