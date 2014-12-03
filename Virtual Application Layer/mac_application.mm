//
//  mac_application.cpp
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#include "mac_application.h"

using namespace val;

bool Application_Mac::initialize()
{
	if (!Application::initialize())
		return false;

	// create autorelease pool
	autorelease_pool = [[NSAutoreleasePool alloc] init];

	// create and initialize application
	[VALApplication sharedApplication];

	if(!NSApp)
	{
		return false;
	}

	// make UI application (pop up in dock when finished launching etc.)
	[NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
	[NSApp activateIgnoringOtherApps:YES];

	// start application
	[NSApp finishLaunching];

	Window_Manager::set(new Window_Manager_Mac()); // TODO: fix mem leak
	Window_Manager::get()->initialize();

	return true;

}

void Application_Mac::destroy()
{
	Application::destroy();
	
	// destroy autorelease pool, releases all autorelease instances
	[autorelease_pool release];
}

void Application_Mac::poll_events()
{
	for (;;)
	{
		NSEvent* event = [NSApp nextEventMatchingMask:NSAnyEventMask
											untilDate:[NSDate distantPast] // past
											   inMode:NSDefaultRunLoopMode
											  dequeue:YES];
		if (event == nil)
			break;

		[NSApp sendEvent:event];
	}

	// TODO: optimize performance, maybe: move autorelease poll drain to better place and/or coulpe with timer
	// placed here to ensure regular drain
	[autorelease_pool release];
	autorelease_pool = [[NSAutoreleasePool alloc] init];
}

void Application_Mac::wait_events()
{
	NSEvent* event = [NSApp nextEventMatchingMask:NSAnyEventMask
										untilDate:[NSDate distantFuture] // future
										   inMode:NSDefaultRunLoopMode
										  dequeue:YES];

	[NSApp sendEvent:event];

	poll_events();
}
