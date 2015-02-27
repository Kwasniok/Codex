//
//  mac_gl_view.mm
//  Codex
//
//  Created by Jens Kwasniok on 06.02.15.
//  Copyright (c) 2015 Codex Soft. All rights reserved.
//

#include "mac_gl_view.h"

using namespace cdx;


bool View_Mac_GL::initialize(Window* win)
{
	Window_Mac* mac_win = reinterpret_cast<Window_Mac*>(win);

	mac_gl_view = [[CDXGLView alloc] initWithWindow:mac_win];

	if (!mac_gl_view)
	{
		LOG_NORMAL("[VIEW_MAC] Could not initialize view, "
				   "because no Cocoa view was created!");
		return false;
	}

#if MAC_OS_X_VERSION_MAX_ALLOWED >= 1070
	if (floor(NSAppKitVersionNumber) > NSAppKitVersionNumber10_6)
	{
		[mac_gl_view setWantsBestResolutionOpenGLSurface:YES];
	}
#endif /*MAC_OS_X_VERSION_MAX_ALLOWED*/

	return true;
}

bool View_Mac_GL::is_valid()
{
	return _is_valid();
}

View_Mac_GL::~View_Mac_GL()
{
	if (_is_valid())
	{
		[mac_gl_view autorelease];
		mac_gl_view = nil;
	}
}
