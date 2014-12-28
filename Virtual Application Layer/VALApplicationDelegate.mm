//
//  VALApplicationDelegate.m
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#import "VALApplicationDelegate.h"

using namespace val;

@implementation VALApplicationDelegate

#if VAL_DEBUG_MAC_MEM_MANGEMENT
-(id)init
{
	if (self = [super init])
	{
		LOG_DEBUG("VALApplicationDelegate <%p> init", self);
	}
	return self;
}

-(void)dealloc
{
	LOG_DEBUG("VALApplicationDelegate <%p> dealloc", self);
	[super dealloc];
}
#endif // VAL_DEBUG_MAC_MEM_MANGEMENT

@end
