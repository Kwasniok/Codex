//
//  VALApplicationDelegate.m
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#import "VALApplicationDelegate.h"

@implementation VALApplicationDelegate

#if VAL_DEBUG_OBJC_MEM_MANGEMENT
-(id)init
{
	if (self = [super init])
	{
		NSLog(@"VALApplicationDelegate init [%@]" , self);
	}
	return self;
}

-(void)dealloc
{
	NSLog(@"VALApplicationDelegate dealloc [%@]" , self);
	[super dealloc];
}
#endif

@end
