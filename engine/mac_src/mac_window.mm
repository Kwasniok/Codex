//
//  mac_window.cpp
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#include "mac_window.h"

using namespace cdx;

Window_Mac::~Window_Mac()
{
	close();
}

bool Window_Mac::is_valid()
{
	return _is_valid();
}

void Window_Mac::close()
{
	if (_is_valid()){
		[mac_win setReleasedWhenClosed:NO];
		[mac_win close];
		[mac_win autorelease];
		mac_win = nil;
	}
}

void Window_Mac::set_visible(bool vis)
{
	if (!_is_valid()) return;

	if (vis)
	{
		[mac_win makeKeyAndOrderFront:nil];
	}
	else{
		[mac_win orderOut:nil];
	}
}

bool Window_Mac::is_visible()
{
	if (!_is_valid()) return false;

	return [mac_win isVisible];
}

void Window_Mac::set_view(cdx::View *v)
{
	if (!_is_valid()) return;

	if (view)
	{
		view->~View();
		[mac_win setContentView:nil];
		view = nullptr;
	}

	view = v;

	if (v != nullptr)
	{
		View_Mac_GL* mac_gl_view = reinterpret_cast<View_Mac_GL*>(v);
		[mac_win setContentView:mac_gl_view->mac_gl_view];
	}
}
