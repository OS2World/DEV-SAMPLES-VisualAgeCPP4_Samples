/******************************************************************************
* .FILE:         alistbox.hpp                                                 *
*                                                                             *
* .DESCRIPTION:  List Box Sample Program:  Class Definition                   *
*                                                                             *
* .CLASSES:      AListBox                                                     *
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
#ifndef ALISTBOX_HPP
#define ALISTBOX_HPP

#include <iframe.hpp>
#include <icmdhdr.hpp>
#include <iwindow.hpp>

class AListBox;

class ACommandHandler: public ICommandHandler
{
  public:
/*--------------------------------------------------------------------------|
| Constructs the object with                                                |
| 1) a pointer to the main window and a pointer to the listbox on the left  |
---------------------------------------------------------------------------*/
    ACommandHandler(AListBox *, IListBox *);

    virtual bool
      command( ICommandEvent& event);

  private:
    AListBox
     *alistbox;
    IListBox
     *listbox1;
};


/******************************************************************************
* Class AListBox - Main window which contains a listbox.                      *
******************************************************************************/
class AListBox : public IFrameWindow,
                 public ICommandHandler
{
  public:
/*--------------------------------------------------------------------------|
| Constructs the object with                                                |
| 1) the window id                                                          |
---------------------------------------------------------------------------*/
    AListBox( unsigned long windowId );

/*--------------------------------------------------------------------------|
| output(IString &) -  outputs a string to the trace listbox.               |
| setStatus()       -  sets the initial status text                         |
---------------------------------------------------------------------------*/
    AListBox
     &output( const IString& astr ),
     &setStatus();

  private:
    IListBox
      listbox,
      listbox2;
    IInfoArea
      infoArea;
    IStaticText
      statusLine;
    IMenuBar
      menuBar;
    ACommandHandler
      commandhandler;
};
#endif
