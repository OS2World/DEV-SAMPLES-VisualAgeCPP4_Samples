/******************************************************************************
* .FILE:         lprdinfo.hpp                                                 *
*                                                                             *
* .DESCRIPTION:  Lancelot Sample Program:              Class Definition       *
*                                                                             *
* .CLASSES:      LProdInfoDialog                                              *
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
#include <iframe.hpp>
#include <icmdhdr.hpp>
#include <iiconctl.hpp>
#include <istattxt.hpp>
#include <ipushbut.hpp>
#include <isetcv.hpp>

class IWindow;

/*************************************************/
/* Class: LProdInfoDialog                         */
/*                                               */
/* Purpose: Encapsulates the Product information */
/*          dialog shown when the user selects   */
/*          Product information from the Help    */
/*          pull-down menu. This class is a      */
/*          subclass of IFrameWindow and         */
/*          ICommandHandler.                     */
/*************************************************/
class LProdInfoDialog : public IFrameWindow,
                       public ICommandHandler
{
  public:

    LProdInfoDialog (IWindow *owner);
    ~LProdInfoDialog ();

  protected:
    virtual bool
      command( ICommandEvent& cmdevt);

  private:
    ISetCanvas
      canvas;
    IIconControl
      iconCtl;
    IStaticText
      text1,
      text2,
      text3,
      text4,
      text5;
    IPushButton
      button;
};

