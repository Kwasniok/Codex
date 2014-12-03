//
//  VALWindow.m
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#import "VALWindow.h"

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
		NSLog(@"Cannot initialize VALWindow without a vaild handler");
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
#if VAL_DEBUG_OBJC_MEM_MANGEMENT
		NSLog(@"VALWindow init [%@]" , self);
#endif
	}
	return self;
}

-(void)sendEvent:(NSEvent *)theEvent
{
	//NSLog(@"Win Got Event: %@", theEvent);
	[super sendEvent:theEvent];
}

-(void)setContentSize:(NSSize)aSize
{
	NSLog(@"Win Resize x=%lf y=%lf", aSize.width, aSize.height);
	[super setContentSize:aSize];
}

#if VAL_DEBUG_OBJC_MEM_MANGEMENT
-(void)dealloc
{
	// TODO: SEND MESSAGE TO WINDOW HANDLER
	NSLog(@"VALWindow dealloc [%@]" , self);
	[super dealloc];
}
#endif

@end
