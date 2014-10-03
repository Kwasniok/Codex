//
//  mac_window.cpp
//  Game Test
//
//  Created by Jens Kwasniok on 15.09.14.
//  Copyright (c) 2014 Jens Kwasniok. All rights reserved.
//

#include "_window.h"

#ifndef __OBJC__
#error Objective-C++ file cannot be compiled as non-Objectice-C file.
#endif


using namespace application_layer;


// -----------
//   Objective-C Class Declarations
// -----------

@interface _ALWindow : NSWindow
//! pointer to the window handler
@property (nonatomic, readonly) Window* windowHandler;

// init functions
-(id)initWithContentRect:(NSRect)contentRect
			   styleMask:(NSUInteger)aStyle
				 backing:(NSBackingStoreType)bufferingType
				   defer:(BOOL)flag
				 handler:(Window*)handler;

// supressed super init functions (they would allow initialization without setting windowHandler)
-(id)init _AL_UNAVAILABLE("this method leaks setting the handler");
-(id)initWithCoder:(NSCoder *)aDecoder
_AL_UNAVAILABLE("this method leaks setting the handler");
-(id)initWithContentRect:(NSRect)contentRect
			   styleMask:(NSUInteger)aStyle
				 backing:(NSBackingStoreType)bufferingType
				   defer:(BOOL)flag
_AL_UNAVAILABLE("this method leaks setting the handler");
-(id)initWithContentRect:(NSRect)contentRect
			   styleMask:(NSUInteger)aStyle
				 backing:(NSBackingStoreType)bufferingType
				   defer:(BOOL)flag
				  screen:(NSScreen *)screen
_AL_UNAVAILABLE("this method leaks setting the handler");

// setter & getter
-(Window*)windowHandler;

@end

@implementation _ALWindow
@synthesize windowHandler;

-(id)initWithContentRect:(NSRect)contentRect
			   styleMask:(NSUInteger)aStyle
				 backing:(NSBackingStoreType)bufferingType
				   defer:(BOOL)flag
				  handler:(Window*)handler
{
	// has valid parent window?
	if (handler == nullptr) {
		NSLog(@"Cannot initialize _ALWindow without a vaild handler");
		return NULL;
	}

	// initialize
	if (self = [super initWithContentRect:contentRect
								styleMask:aStyle
								  backing:bufferingType
									defer:flag]
		)
	{
		// store pointer to parent window
		windowHandler = handler;
		[self setReleasedWhenClosed:YES];
#if _AL_DEBUG_OBJC_MEM_MANGEMENT
		NSLog(@"_ALWindow init [%@]" , self);
#endif
	}
	return self;
}

#if _AL_DEBUG_OBJC_MEM_MANGEMENT
-(void)dealloc
{
	NSLog(@"_ALWindow dealloc [%@]" , self);
	[super dealloc];
}
#endif

@end


@interface _ALWindowDelegate : NSObject <NSWindowDelegate>
@end


@implementation _ALWindowDelegate

-(BOOL)windowShouldClose:(id)sender
{
	_ALWindow* win = sender;
	win.windowHandler->destroy();

	return TRUE;
}

#if _AL_DEBUG_OBJC_MEM_MANGEMENT
-(id)init
{
	if (self = [super init])
	{
		NSLog(@"_ALWindowDelegate init [%@]" , self);
	}
	return self;
}

-(void)dealloc
{
	NSLog(@"_ALWindowDelegate dealloc [%@]" , self);
	[super dealloc];
}
#endif

@end


// -----------
//   Global Variables
// -----------

namespace application_layer {
	_ALWindowDelegate* _platform_window_delegate;
}


// -----------
//   Global Functions
// -----------

bool application_layer::_platform_initialize_windows()
{
	// create global delegate for all windows
	_platform_window_delegate = [[_ALWindowDelegate alloc] init];

	return _platform_window_delegate != nil;
}

void application_layer::_platform_destroy_windows()
{
	[_platform_window_delegate autorelease];
}


// -----------
//   Member Functions
// -----------

void Window::_platform_create_window(const util::Rect& bounds, std::string title, bool closable, bool resizable, bool borderless)
{
	// parameters
	NSRect frame = NSMakeRect(bounds.x, bounds.y, bounds.width, bounds.height);
	NSUInteger styleMask = 0;
	if (closable) {
		styleMask |= NSClosableWindowMask;
	}
	if (resizable) {
		styleMask |= NSResizableWindowMask;
	}
	styleMask |=  borderless ? NSBorderlessWindowMask : NSTitledWindowMask;

	// initialize
	_ALWindow* win = [[_ALWindow alloc] initWithContentRect:frame
												  styleMask:styleMask
													backing:NSBackingStoreBuffered
													  defer:NO
													handler:this];

	// set delegate
	[win setDelegate:_platform_window_delegate];

	// further paramters
		// TODO: ensure: which encoding was used?
	NSString* _title = [[NSString alloc] initWithCString:title.c_str()
												encoding:NSUTF8StringEncoding];
	[win setTitle:_title]; // TODO: optimize for more comfort, allways: replace by title parameter
	[_title release];


	// store pointer to platform-specific window
	_platform_window = (__bridge void*) win;
}

void Window::_platform_destroy_window()
{
	// restore pointer to platform-specific window
	//_ALWindow* win = (__bridge _ALWindow*) _platform_window;
}

void Window::_platform_window_set_visible(bool vis)
{
	// restore pointer to platform-specific window
	_ALWindow* win = (__bridge _ALWindow*) _platform_window;

	// change visability
	if (vis)
	{
		[win makeKeyAndOrderFront:nil];
	}
	else{
		[win orderOut:nil];
	}
}

bool Window::_platform_is_visible() const
{
	// restore pointer to platform-specific window
	_ALWindow* win = (__bridge _ALWindow*) _platform_window;

	// get visability
	return [win isVisible];
}
