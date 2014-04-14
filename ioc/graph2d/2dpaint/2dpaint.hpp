#ifndef TWOD_HPP
#define TWOD_HPP

/*
-------------------------------------------------------------------------------
Copyright (c) IBM Corporation 1996, 1997.
All Rights Reserved.

Permission is granted to copy, use, modify, and merge this software into your
applications and to permit others to do any of the foregoing. You must include
this permission and copyright notice in all copies and modified versions of
this software. THIS SOFTWARE IS PROVIDED IN ITS 'AS IS' CONDITION.
IBM DISCLAIMS ANY LIABILITY OF ANY KIND FOR DAMAGES WHATSOEVER RESULTING
FROM THE USE OF THIS SOFTWARE.
-------------------------------------------------------------------------------
*/

#include <iexcept.hpp>
#include <iframe.hpp>              // IBM Open Class Headers
#include <iinfoa.hpp>
#include <isizehdr.hpp>
#include <icmdhdr.hpp>
#include <imenubar.hpp>
#include <ireslib.hpp>
#include <imoushdr.hpp>
#include <imousevt.hpp>
#include <istattxt.hpp>
#include <itbar.hpp>
#include <itbarbut.hpp>
#include <ipainhdr.hpp>
#include <ipainevt.hpp>
#include <ititle.hpp>
#include <ipushbut.hpp>
#include <icoordsy.hpp>
#include <ifontdlg.hpp>
#include <ifont.hpp>
#include <ientryfd.hpp>
#include <ipopmenu.hpp>
#include <imcelcv.hpp>

#include <igraph2d.hpp>
#include <igrport.hpp>
#include <iimage.hpp>
#include <igraftxt.hpp>

#include <itrace.hpp>

#ifndef FVT_NOPRINT
// Printing headers
#ifndef Taligent_PRINT
#ifndef IC_MOTIF
#include <iprint.hpp>
#endif //IC_MOTIF
#endif
#ifndef IC_PAGECOMPOSITOR
#ifndef IC_MOTIF
#include <ipgcmp.hpp>
#endif //IC_MOTIF
#endif
#ifndef Taligent_PRINTBUTLER
#ifndef IC_MOTIF
#include <iprtbtlr.hpp>
#endif //IC_MOTIF
#endif
#endif

#include "2dpaint.h"

extern "C" { void PerfStart(void); }
extern "C" { void PerfStop(void); }

//**************************************************************************
// Class:   IColorSelector                                                 *
//                                                                         *
// Purpose: Control for varying the R,G,B, and Gray values of the selected *
//          color.  Used with IPalletDialog.                               *
//**************************************************************************

class IColorSelector : public ICanvas, public IPaintHandler, public IMouseHandler
{
  public:
    enum ColorType { Red_type, Green_type, Blue_type, Gray_type };
    IColorSelector(long id, IWindow* parent, IWindow* owner,
                   IColorSelector::ColorType t, bool h);
    ~IColorSelector();
    CharIntensity GetValue();
    CharIntensity SetValue(CharIntensity val);
  protected:
    virtual bool paintWindow(IPaintEvent& event);
    virtual bool mouseClicked(IMouseClickEvent&   event),
                    mouseMoved(IMouseEvent& event);
  private:
    IManagedPresSpaceHandle *managedPresSpacePtr;
    IWindow* win;
    CharIntensity value;
    ColorType type;
    bool capturing;
    bool horizontal;
};

//**************************************************************************
// Class:   IColorSquare                                                   *
//                                                                         *
// Purpose: Class draws a square of the color selected in the              *
//          IColorPalletCanvas (see below) for use with IPalletDialog      *
//**************************************************************************

class IColorSquare : public ICanvas, public IPaintHandler
{
  public:
    IColorSquare(const unsigned long id, IWindow* parent, IWindow* owner);
    ~IColorSquare();
  protected:
    virtual bool paintWindow(IPaintEvent& event);
  private:
    IManagedPresSpaceHandle *managedPresSpacePtr;
    IWindow* win;
};

//**************************************************************************
// Class:   IPalletCanvas                                                  *
//                                                                         *
// Purpose: Acts as a control for handling color selection in the          *
//          IPalletDialog                                                  *
//**************************************************************************

class IPalletCanvas : public ICanvas, public IPaintHandler, public IMouseHandler
{
  public:
    IPalletCanvas(const unsigned long id, IWindow* parent, IWindow* owner, int& pX, int& pY);
    ~IPalletCanvas();
    IBaseColor color();
    void SetColor();
    int GetPosX() { return *posX; }
    int GetPosY() { return *posY; }
  protected:
    virtual bool paintWindow(IPaintEvent& event);
    virtual bool mouseClicked(IMouseClickEvent& event);
  private:
    IManagedPresSpaceHandle *managedPresSpacePtr;
    void InitTables();
    IWindow* win;
    IGRect2D* squareTable[8][8];
    int paintAllFlag;
    int* posX;
    int* posY;
};

//**************************************************************************
// Class:   IControlCanvas                                                 *
//                                                                         *
// Purpose: This class holds the controls for the IPalletDialog            *
//**************************************************************************

class IControlCanvas : public ICanvas, public ICommandHandler
{
  public:
    IControlCanvas(const unsigned long id, IWindow* parent, IWindow* owner)
      : ICanvas(id,parent,owner),
       win(owner)
      { handleEventsFor(this); }
    ~IControlCanvas()
      { stopHandlingEventsFor(this); }
  protected:
    virtual bool command(ICommandEvent& event);
  private:
    IWindow* win;
};

//**************************************************************************
// Class:   IPalletDialog                                                  *
//                                                                         *
// Purpose: Class is used as a dialog to allow the user to select a color  *
//          for framing of filling a graphic                               *
//**************************************************************************

class IPalletDialog : public IFrameWindow
{
  public:
    IPalletDialog(const char* title, int& pX, int& pY, IWindow * ownerWnd);
    ~IPalletDialog();
    IBaseColor color();
    void SetValues(CharIntensity rV, CharIntensity gV, CharIntensity bV, CharIntensity grV);
    void SetValue(CharIntensity val, IColorSelector::ColorType t);
    void SetColor(IBaseColor color);
  private:
    IControlCanvas controlCanvas;
    IPalletCanvas palletCanvas;
    IColorSquare colorSquare;
    IPushButton OkBut,CancelBut;
    IBaseColor currentColor;
    IColorSelector rSelector,gSelector,bSelector,grSelector;
    ITitle dialogTitle;
    bool grayColor;
    CharIntensity rVal,gVal,bVal,grVal;
    IBaseColor fColor;
};

//**************************************************************************
// Class:   ITextDialog                                                    *
//                                                                         *
// Purpose: Class is used as a dialog to allow the user to enter text to   *
//          be placed on the drawing canvas.                               *
//**************************************************************************

class ITextDialog : public IFrameWindow, public ICommandHandler
{
  public:
    ITextDialog(const char* title, IWindow * ownerWnd);
    ~ITextDialog() { stopHandlingEventsFor(this); }
    IString getText() { return entryField.text(); }
  protected:
    virtual bool command(ICommandEvent& event);
  private:
    IMultiCellCanvas controlCanvas;
    IEntryField entryField;
    IPushButton OkBut;
    ITitle dialogTitle;
};

//**************************************************************************
// Class:   DrawingArea                                                    *
//                                                                         *
// Purpose: Class contains the handlers necessray for interactive drawing  *
//          and manipulation of graphical objects                          *
//**************************************************************************

class DrawingArea : public ICanvas, public IMouseHandler, public IPaintHandler, public IResizeHandler
{
  public:
    DrawingArea(unsigned long windowId, IWindow* parent,
                IWindow* owner, const IRectangle& intial = IRectangle() );
    virtual ~DrawingArea ( );

    enum DrawingState { drawing, waitForInput, notDrawing };

    DrawingArea &SetDrawState(const DrawingState newState = drawing);
    DrawingState GetDrawState( ) const { return dState; }

    enum DrawObject { attribStyle = PALLET_STYLE, pointer, rotate,
                      scale, clip, area, line, freeHand, rectangle,
                      ellipse, polyline, polygon, curve, loop,  text,
                      bitmap, arc, pie, chord, cbezier, acurve,
                      lbezier, aloop, add, subtract, multiply, Xor};

    virtual DrawingArea &SetDrawObject( const DrawObject drawObject)
            { currentObj = drawObject; return *this; }

    // window management methods
    void Init();
    void Clear();
    void ResetDrawingDevices();
    void Draw(IRectangle invalidRect);

    // transfer mode set methods
    void SetFrameTransferMode(unsigned long mode);
    void SetFillTransferMode(unsigned long mode);

    // pattern set methods
    void SetFramePattern(unsigned long mode);
    void SetFillPattern(unsigned long mode);

    // attribute color set methods
    void SetPenColor(IBaseColor color);
    void SetFillColor(IBaseColor color);

    // miscelaneous attribute set methods
    void SetDrawingOp(IAttributeState::EDrawOperation op);
    void SetPenWidth(int width);

    // graphic text set methods
    void SetGraphicText(IText text) { graphicText = text; }

    // set methods for the information text
    void SetInfoText(IString text);
    void SetInfoText(unsigned long id);

    // Get/Create methods
    void setPenType(int type);

    IGraphicGroup *GetGraphicGroup() { return fGraphicGroup; }
  protected:
    bool paintWindow(IPaintEvent&);

    virtual bool mouseClicked(IMouseClickEvent&   event),
#ifndef IC_MOTIF
                    mousePointerChange(IMousePointerEvent& event),
#endif
                    mouseMoved(IMouseEvent& event);
    virtual bool windowResize(IResizeEvent& event);                    

    virtual DrawingArea &button1Down(const IPoint& point),
                        &button1Up(const IPoint& point),
                        &button1DoubleClick(const IPoint& point),
                        &button2or3DoubleClick(const IPoint& point),
                        &button2or3Down(const IPoint& point);

  private:
    IRectangle& convertGraphicToView( IRectangle& graphicRect );
    IMGraphic* getTopGraphicUnderPoint(const IGPoint2D& point, IGraphicGroup* group);
    IGArea *GraphicToArea(IMGraphic *mgraphic);

    IManagedPresSpaceHandle *managedPresSpacePtr;
    IGrafPort*         myDisplayPort;      // rendering graphics to the window
    IGrafPort*         parentPort;         // the parent port is used when clipping

    IGraphicGroup*     fGraphicGroup;      // the list of graphics on the canvas

    unsigned long      clickCount;         // tracks different stages of curve definition
    unsigned long      pointCount;         // tracks the number of the number of control points

    bool               clipping;           // specifies whether clipping is on/off
    bool               paintedLastResize;  // used to determine whether this window was visible before resize
    const IGArea       *clipArea;          // the clipping area (when clipping is on)

    DrawingState          dState;             // the drawing state
    DrawObject         currentObj;         // the current object to be drawn

#ifndef IC_MOTIF
#define kNumberOfPointers 14
    IPointerHandle     ptrArray[kNumberOfPointers];       // the mouse pointers
#endif
    IGPoint2D            startingPoint;      // points used for defining graphic
    IGPoint2D            previousPoint;      //
    IGPoint2D            c1,c2,c3,c4;        // control points for curves

    IMGraphic*          currentGraphic;     // current graphic being defined or selected
    IMGraphic*          moveGraphic;        // used for moving graphics

    IGrafBundle         drawingBundle;      // black framing bundle

    // use IGrafBundle to hold all frame and fill info
    IGrafBundle         currentBundle;

    IPolygon*          tempPolygon;        // used for the defining of polygons
    IPolyline*         tempPolyline;       // used for the defining of polylines
    IPolygon*          moveRect;           // used in moving graphics

    IGRPoint2DArray      pointArray;         // used for defining nurbs/loops
    IText            graphicText;        // the current string for a text graphic

};

//**************************************************************************
// Class:   MainWindow                                                     *
//                                                                         *
// Purpose: Main Window for C++ Starter Set 2D Graphics Application        *
//**************************************************************************

class MainWindow : public IFrameWindow, public ICommandHandler,
        public IResizeHandler
{
  public:
    MainWindow(unsigned long windowId);
    virtual ~MainWindow();
    // set methods for the information text
    void SetInfoText(IString text);
    void SetInfoText(unsigned long id);
    // pallete management methods
    void InitPallet();
    void ClearPallet();
    const IToolBar& toolbar(){ return toolBar1; }
  protected:
    virtual bool command(ICommandEvent& event);
    virtual bool windowResize(IResizeEvent& event);
  private:
    DrawingArea         drawingArea;                  // the drawing space
    IToolBar            toolBar1;                     // the tool bar
    IMenuBar            menuBar;                      // the information (help) text
    IStaticText         infoText;                     // the flyover text control
    unsigned long       lastPenTypeId;                // used to unmark menu items
    unsigned long       lastPenWidthId;               // ect.
    unsigned long       lastDrawOperationId;
    int                 frameX,frameY,fillX,fillY;    // color table indexes
    int                 canvasX,canvasY;
    int                 bframeX,bframeY,bfillX,bfillY;
#define kNumberOfButtons  16
    IToolBarButton      *buttonArray[kNumberOfButtons];             // the tool bar buttons
    IToolBarButton      *lastButton;                  // the last tool bar button used
    int                 groupButtIndex;               // determines where to split the tool bar

};
#endif
