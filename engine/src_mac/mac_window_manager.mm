//
//  mac_window_manager.cpp
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#include "mac_window_manager.h"

using namespace cdx;

bool Window_Manager_Mac::initialize()
{
	if (!Window_Manager_Mac::delegate) {
		delegate = [[CDXWindowDelegate alloc] init];
	}

	return delegate != NULL;
}

Window_Manager_Mac::~Window_Manager_Mac()
{
	delegate = NULL;
}

Window* Window_Manager_Mac::create_window(const cdx::Rect& bounds,
										  const String_UTF8& title,
										  bool closable,
										  bool resizable,
										  bool borderless)
{
	Window_Mac* win = NEW Window_Mac();

	// parameters
	NSRect frame = NSMakeRect(bounds.x, bounds.y, bounds.width, bounds.height);
	NSUInteger styleMask = 0;
	if (closable)
	{
		styleMask |= NSClosableWindowMask;
	}
	if (resizable)
	{
		styleMask |= NSResizableWindowMask;
	}
	styleMask |=  borderless ? NSBorderlessWindowMask : NSTitledWindowMask;

	CDXWindow* mac_win = [[CDXWindow alloc] initWithContentRect:frame
													  styleMask:styleMask
														backing:NSBackingStoreBuffered
														  defer:NO
														handler:win];

	// set delegate
	[mac_win setDelegate:delegate];

	// further paramters
	NSString* _title = [[NSString alloc] initWithCString:title.c_str()
												encoding:NSUTF8StringEncoding];
	[mac_win setTitle:_title];
	[_title release];

	if(mac_win)
	{
		win->set_mac_window(mac_win);
		add_window_to_list(win);
	}
	else
	{
		delete win;
		win = nullptr;
	}

	return win;
}

void Window_Manager_Mac::destroy_window(Window *win)
{
	if (!win) return;

	win->close();
	remove_window_from_list(win);
	delete win;
}
