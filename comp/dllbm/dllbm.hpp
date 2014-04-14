/*
 * IBM VisualAge C++ Professional, Version 4.0
 *
 * Licensed Materials - Property of IBM
 *
 * (C) Copyright IBM Corp. 1998. All Rights Reserved.
 *
 * The following [enclosed] code is sample code created by IBM
 * Corporation.  This sample code is not part of any standard IBM product
 * and is provided to you solely for the purpose of assisting you in the
 * development of your applications.  The code is provided 'AS IS',
 * without warranty of any kind.  IBM shall not be liable for any damages
 * arising out of your use of the sample code, even if they have been
 * advised of the possibility of such damages.
 */

#ifndef DLLBM_HPP

#define DLLBM_HPP

#include <iframe.hpp>
#include <inotebk.hpp>
#include <ivport.hpp>
#include <ibmpctl.hpp>

#include "dllbm.h"

class ABitmapNotebook : public IFrameWindow {
	IDynamicLinkLibrary idll;			// the resource DLL
	INotebook notebook;
	ISize tabSize;
	IViewPort viewport1, viewport2, viewport3;	// viewports
	IBitmapHandle tab1, tab2, tab3;			// bitmap handles
	IBitmapControl bitmap1, bitmap2, bitmap3;	// bitmap controls
public:
	ABitmapNotebook();
	virtual ~ABitmapNotebook() { };
};

#endif
