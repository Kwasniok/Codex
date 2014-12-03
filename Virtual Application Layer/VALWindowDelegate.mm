//
//  VALWindowDelegate.m
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#import "VALWindowDelegate.h"

@implementation VALWindowDelegate

-(BOOL)windowShouldClose:(id)sender
{
	VALWindow* win = sender;
	[win windowHandler]->close();

	return TRUE;
}

#if VAL_DEBUG_OBJC_MEM_MANGEMENT
-(id)init
{
	if (self = [super init])
	{
		NSLog(@"VALWindowDelegate init [%@]" , self);
	}
	return self;
}

-(void)dealloc
{
	NSLog(@"VALWindowDelegate dealloc [%@]" , self);
	[super dealloc];
}
#endif

@end