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

	return delegate != nil;
}

Window_Manager_Mac::~Window_Manager_Mac()
{
	[delegate autorelease];
	delegate = nil;
}

Window* Window_Manager_Mac::create_window(const cdx::Rect& bounds,
										  const String_UTF8& title,
										  bool closable,
										  bool resizable,
										  bool borderless,
										  bool center)
{
	Window_Mac* win = NEW Window_Mac;

	CDXWindow* mac_win;

	NSRect frame = NSMakeRect(bounds.x, bounds.y, bounds.width, bounds.height);
	NSUInteger styleMask = 0;
	styleMask |= closable ? NSClosableWindowMask : 0;
	styleMask |= resizable ? NSResizableWindowMask : 0;
	styleMask |=  borderless ? NSBorderlessWindowMask : NSTitledWindowMask;

	mac_win = [[CDXWindow alloc] initWithContentRect:frame
										   styleMask:styleMask
											 backing:NSBackingStoreBuffered
											   defer:NO
											 handler:win];

	if (!mac_win)
	{
		delete win;
		win = nullptr;
	}
	else
	{

		// further paramters
		NSString* _title = [[NSString alloc] initWithCString:title.c_str()
													encoding:NSUTF8StringEncoding];
		[mac_win setTitle:_title];
		[_title release];

		[mac_win setAcceptsMouseMovedEvents:YES];
		[mac_win center];
#if MAC_OS_X_VERSION_MAX_ALLOWED >= 1070
		if (floor(NSAppKitVersionNumber) > NSAppKitVersionNumber10_6)
			[mac_win setRestorable:NO];
#endif /*MAC_OS_X_VERSION_MAX_ALLOWED*/

		[mac_win setDelegate:delegate];

		win->set_mac_window(mac_win);
		add_window_to_list(win);
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
