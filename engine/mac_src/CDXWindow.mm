//
//  CDXWindow.m
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#import "CDXWindow.h"

using namespace cdx;

@implementation CDXWindow
@synthesize windowHandler;

-(id)initWithContentRect:(NSRect)contentRect
			   styleMask:(NSUInteger)aStyle
				 backing:(NSBackingStoreType)bufferingType
				   defer:(BOOL)flag
				 handler:(cdx::Window*)handler
{
	// has valid parent window?
	if (handler == nullptr) {
		LOG_DEBUG("Cannot initialize CDXWindow without a vaild handler");
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
#if CDX_DEBUG_MAC_MEM_MANGEMENT
		LOG_DEBUG("CDXWindow <%p> init", self);
#endif
	}
	return self;
}

-(void)sendEvent:(NSEvent *)theEvent
{
	#if CDX_DEBUG_MAC_PRINT_WINDOW_EVENTS
	LOG_DEBUG("CDXWindow <%p> event: %s", self, theEvent.description.UTF8String);
	#endif
	[super sendEvent:theEvent];
}

-(void)setContentSize:(NSSize)aSize
{
	LOG_DEBUG("CDXWindow <%p> resize: x=%lf, y=%lf", self, aSize.width, aSize.height);
	[super setContentSize:aSize];
}

#if CDX_DEBUG_MAC_MEM_MANGEMENT
-(void)dealloc
{
	LOG_DEBUG("CDXWindow <%p> dealloc", self);
	[super dealloc];
}
#endif // CDX_DEBUG_MAC_MEM_MANGEMENT

@end
