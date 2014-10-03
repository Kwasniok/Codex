//
//  init.mm
//  Game Test
//
//  Created by Jens Kwasniok on 15.09.14.
//  Copyright (c) 2014 Jens Kwasniok. All rights reserved.
//

#include "_init.h"

#ifndef __OBJC__
#error Objective-C++ file cannot be compiled as non-Objectice-C file.
#endif


using namespace application_layer;


// -----------
//   Objective-C Class Declarations
// -----------

@interface _ALApplication : NSApplication
@end

@implementation _ALApplication

/*
- (void)sendEvent:(NSEvent *)event
{
	NSLog(@"Got Event %@", event);
	[super sendEvent:event];
}
*/

#if _AL_DEBUG_OBJC_MEM_MANGEMENT
-(id)init
{
	if (self = [super init])
	{
		NSLog(@"_ALApplication init [%@]" , self);
	}
	return self;
}

-(void)dealloc
{
	NSLog(@"_ALApplication dealloc [%@]" , self);
	[super dealloc];
}
#endif

@end


@interface _ALApplicationDelegate : NSObject <NSApplicationDelegate>
@end

@implementation _ALApplicationDelegate

#if _AL_DEBUG_OBJC_MEM_MANGEMENT
-(id)init
{
	if (self = [super init])
	{
		NSLog(@"_ALApplicationDelegate init [%@]" , self);
	}
	return self;
}

-(void)dealloc
{
	NSLog(@"_ALApplicationDelegate dealloc [%@]" , self);
	[super dealloc];
}
#endif

@end


// -----------
//   Global Variables
// -----------

namespace application_layer {
	NSAutoreleasePool* _platfrom_autorelease_pool;
}


// -----------
//   Global Functions
// -----------

bool application_layer::_platform_initialize()
{
	// create autorelease pool
	_platfrom_autorelease_pool = [[NSAutoreleasePool alloc] init];

	// create and initialize application
	[_ALApplication sharedApplication];

	if(!NSApp)
	{
		return false;
	}

	// make UI application (pop up in dock when finished launching etc.)
	[NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
	[NSApp activateIgnoringOtherApps:YES];

	// start application
	[NSApp finishLaunching];

	return true;
}

void application_layer::_platform_destroy()
{
	// destroy autorelease pool, releases all autorelease instances
	[_platfrom_autorelease_pool release];

	// [NSApp release];
}

void application_layer::_platform_poll_events()
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
	[_platfrom_autorelease_pool release];
	_platfrom_autorelease_pool = [[NSAutoreleasePool alloc] init];
}

void application_layer::_platform_wait_events()
{
	NSEvent* event = [NSApp nextEventMatchingMask:NSAnyEventMask
										untilDate:[NSDate distantFuture] // future
										   inMode:NSDefaultRunLoopMode
										  dequeue:YES];

	[NSApp sendEvent:event];

	poll_events();
}
