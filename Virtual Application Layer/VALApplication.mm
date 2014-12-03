//
//  VALApplication.m
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#import "VALApplication.h"

@implementation VALApplication

/*
 - (void)sendEvent:(NSEvent *)event
 {
	NSLog(@"Got Event %@", event);
	[super sendEvent:event];
 }
 */

#if VAL_DEBUG_OBJC_MEM_MANGEMENT
-(id)init
{
	if (self = [super init])
	{
		NSLog(@"VALApplication init [%@]" , self);
	}
	return self;
}

-(void)dealloc
{
	NSLog(@"VALApplication dealloc [%@]" , self);
	[super dealloc];
}
#endif

@end
