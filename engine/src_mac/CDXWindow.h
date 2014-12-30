//
//  CDXWindow.h
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#ifndef __Codex__CDXWindow__
#define __Codex__CDXWindow__

#include "mac_config.h"
#include "window.h"
#include "window_manager.h"
#import <AppKit/AppKit.h>

@interface CDXWindow : NSWindow
//! pointer to the window handler
@property (nonatomic, readonly) cdx::Window* windowHandler;

// init functions
-(id)initWithContentRect:(NSRect)contentRect
			   styleMask:(NSUInteger)aStyle
				 backing:(NSBackingStoreType)bufferingType
				   defer:(BOOL)flag
				 handler:(cdx::Window*)handler;

// supressed super init functions (they would allow initialization without setting windowHandler)
-(id)init MAC_UNAVAILABLE("this method leaks setting the handler");
-(id)initWithCoder:(NSCoder *)aDecoder
MAC_UNAVAILABLE("this method leaks setting the handler");
-(id)initWithContentRect:(NSRect)contentRect
			   styleMask:(NSUInteger)aStyle
				 backing:(NSBackingStoreType)bufferingType
				   defer:(BOOL)flag
MAC_UNAVAILABLE("this method leaks setting the handler");
-(id)initWithContentRect:(NSRect)contentRect
			   styleMask:(NSUInteger)aStyle
				 backing:(NSBackingStoreType)bufferingType
				   defer:(BOOL)flag
				  screen:(NSScreen *)screen
MAC_UNAVAILABLE("this method leaks setting the handler");

// setter & getter
-(cdx::Window*)windowHandler;

@end

#endif // __Codex__CDXWindow__