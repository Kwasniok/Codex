//
//  VALApplication.m
//  Codex
//
//  Created by Jens Kwasniok on 02.12.14.
//  Copyright (c) 2014 Codex Soft. All rights reserved.
//

#import "VALApplication.h"

using namespace val;

@implementation VALApplication


- (void)sendEvent:(NSEvent *)event
{
	#if VAL_DEBUG_MAC_PRINT_APPLICATION_EVENTS
	LOG_DEBUG("VALApplication %p event: %s", self, event.description.UTF8String);
	#endif
	[super sendEvent:event];
}

#if VAL_DEBUG_MAC_MEM_MANGEMENT
-(id)init
{
	if (self = [super init])
	{
		LOG_DEBUG("VALApplication <%p> init", self);
	}
	return self;
}

-(void)dealloc
{
	LOG_DEBUG("VALApplication <%p> dealloc", self);
	[super dealloc];
}
#endif // VAL_DEBUG_MAC_MEM_MANGEMENT

@end
