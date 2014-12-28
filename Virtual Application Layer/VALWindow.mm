//
//  VALWindow.m
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#import "VALWindow.h"

using namespace val;

@implementation VALWindow
@synthesize windowHandler;

-(id)initWithContentRect:(NSRect)contentRect
			   styleMask:(NSUInteger)aStyle
				 backing:(NSBackingStoreType)bufferingType
				   defer:(BOOL)flag
				 handler:(val::Window*)handler
{
	// has valid parent window?
	if (handler == nullptr) {
		LOG_DEBUG("Cannot initialize VALWindow without a vaild handler");
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
#if VAL_DEBUG_MAC_MEM_MANGEMENT
		LOG_DEBUG("VALWindow <%p> init", self);
#endif
	}
	return self;
}

-(void)sendEvent:(NSEvent *)theEvent
{
	#if VAL_DEBUG_MAC_PRINT_WINDOW_EVENTS
	LOG_DEBUG("VALWindow <%p> event: %s", self, theEvent.description.UTF8String);
	#endif
	[super sendEvent:theEvent];
}

-(void)setContentSize:(NSSize)aSize
{
	LOG_DEBUG("VALWindow <%p> resize: x=%lf, y=%lf", self, aSize.width, aSize.height);
	[super setContentSize:aSize];
}

#if VAL_DEBUG_MAC_MEM_MANGEMENT
-(void)dealloc
{
	// TODO: SEND MESSAGE TO WINDOW HANDLER
	windowHandler->close();
	LOG_DEBUG("VALWindow <%p> dealloc", self);
	[super dealloc];
}
#endif // VAL_DEBUG_MAC_MEM_MANGEMENT

@end
