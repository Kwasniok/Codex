//
//  mac_application.cpp
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#include "mac_application.h"

using namespace cdx;

bool Application_Mac::initialize()
{
	[CDXApplication sharedApplication]; // creates & initializes the application

	if(!NSApp)
	{
		LOG_NORMAL("[APP_MAC] Application could not be initialized, "
				   "because no Cocoa application was created!");
		return false;
	}

	delegate = [[CDXApplicationDelegate alloc] init];
	if (!delegate)
	{
		LOG_NORMAL("[APP_MAC] Application could not be initialized, "
				   "because no application delegate was created!");
		return false;
	}

	[NSApp setDelegate:(id)delegate];


	// make UI application (pop up in dock when finished launching etc.)
	[NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
	[NSApp activateIgnoringOtherApps:YES];

	// start application
	[NSApp finishLaunching];

	return true;
}

Application_Mac::~Application_Mac()
{
	if (_is_valid())
	{
		[delegate autorelease];
		//[NSApp terminate:nil]; // calls exit() --> stops clean up!
	}
}

bool Application_Mac::is_valid()
{
	return _is_valid();
}

void Application_Mac::poll_events()
{
	for (;;)
	{
		NSEvent* event = [NSApp nextEventMatchingMask:NSAnyEventMask
											untilDate:[NSDate distantPast] // past
											   inMode:NSDefaultRunLoopMode
											  dequeue:YES];
		if (!event)
			break;

		[NSApp sendEvent:event];
	}

	Root::perform_garbage_collection();
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
