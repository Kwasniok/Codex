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

#if VAL_DEBUG_MAC_PRINT_APPLICATION_EVENTS
- (void)sendEvent:(NSEvent *)event
{
	Log::log(Log_Type::DBUG, "VALApplication <%p> event: %s", self, event.description.UTF8String);
	[super sendEvent:event];
}
#endif // VAL_DEBUG_MAC_PRINT_APPLICATION_EVENTS

#if VAL_DEBUG_MAC_MEM_MANGEMENT
-(id)init
{
	if (self = [super init])
	{
		val::Log::log(val::Log_Type::MEM, "VALApplication <%p> init", self);
	}
	return self;
}

-(void)dealloc
{
	val::Log::log(val::Log_Type::MEM, "VALApplication <%p> dealloc", self);
	[super dealloc];
}
#endif // VAL_DEBUG_MAC_MEM_MANGEMENT

@end
